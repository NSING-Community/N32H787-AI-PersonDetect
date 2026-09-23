# N32H7x CMSIS-DAP

One configuration is used by Linux and Windows: `n32h7x_cmsisdap.tcl`.
Keep `flash_op/n32h7xx_flash_op.bin` in its relative location. No other
project cfg is needed.

## Supported Setup

- Tested MCU: N32H787XIB7, Cortex-M7 / AP0.
- Algorithm: the vendor `flash_op.bin` shipped with N32Studio's N32H7 OpenOCD
  configuration, 528 bytes. It wraps the chip's ROM flash routines (`0x1FFF7A01`
  init, `0x1FFF7C81` erase sector, `0x1FFF7B81` program page) and adds a
  RAM-buffer `Verify`. It holds no absolute RAM reference, so the load base is
  ours to choose. Do not assume other N32H7 parts share this Flash geometry or
  algorithm.
- Flash range: `0x15000000..0x151dffff`, sector size 4096 bytes.
- Probe: NSLink CMSIS-DAP HID, VID:PID `19f5:3106`, SWD.
- OpenOCD: Linux 0.12.0 or N32Studio's Windows distribution.
- SWD speed: 100 kHz for connection/reset, 2000 kHz for programming and
  verification. NRST may remain connected. Flash preparation does not reset
  the CPU; a software reset is issued only after successful verification.

## Linux

From the repository root:

```sh
make -C firmware/Makefile probe
make -C firmware/Makefile flash
```

`flash` builds, writes the occupied sectors, verifies the image, and resets
the application to run. A programming or verification failure stops the
command before the final reset. `flash_verify` is an alias for `flash`.
`probe` connects and polls without requesting a halt or reset.

Flash preparation halts the core, stops SysTick, and uses the debug-only
AIRCR VECTCLRACTIVE operation to clear active exceptions without restarting
BOOT. It verifies Thread mode, disables/clears NVIC interrupts and the MPU,
and sets Thumb state, the FlashOS stack and interrupt masks before executing
the algorithm. It does not use `VECTRESET` / `reset halt`, which previously
made AP0 inaccessible on this board. This is destructive to the application's
RAM/debug execution state, as expected for flashing, not a general resume
operation. Peripherals are not reset by this preparation.

The current path requires instruction and data caches to be disabled. If
either is enabled, preparation aborts before Flash is erased or programmed;
cache-enabled firmware needs a separately validated cache-maintenance path.

A successful run must reach `Flash verified: N bytes (on-target per-chunk
compare)` and exit with status 0. Nothing is read back over SWD to verify: each
16 KiB chunk is programmed and then compared against the staging buffer by the
algorithm's own `Verify` call while that buffer still holds the chunk. That
compare reads Flash and walks RAM, and it cannot detect a chunk corrupted
identically in both, so it is not a substitute for a host read-back on a board
whose SRAM is suspect.

AHB SRAM1 is laid out inside the M4 `QuickCodes` window, and still relies on
`n32h7x_stop_m4_camera` holding M4 in reset before any of it is reused:

| Region | Range |
| --- | --- |
| algorithm code | `0x30010000..0x3001020f` (528 bytes) |
| FlashOS stack, growing down | below `0x30010fe0` |
| return breakpoint | `0x30010ff0` |
| 16 KiB chunk buffer | `0x30011000..0x30014fff` |
| OpenOCD work area | `0x30015000..0x300153ff` |
| M4 mailbox (`SHARED`) | `0x30000000..0x300003ff`, untouched |
| inference snapshot | `0x30016000..`, untouched |

`0x30010210..0x30010fe0` (3.5 KiB) is the stack headroom, matching what the
vendor's own cfg allows for the same binary. These addresses are also
asserted by the `n32h7x_cmsisdap.tcl` layout checks; move them together.

The algorithm's `EraseChip` entry (`0x30010091`) is a stub that returns success
**without erasing anything**. Never wire a mass-erase command to it.

### Reverting The Algorithm

This checkout has no version control (`.git` is an empty directory), so the
previous binary is kept on disk and the rollback is by hand. Point
`FLASH_ALGO_BIN` back at `flash_op/n32h78x_h76x_nrp_1a.bin` and restore:

| Constant | Old value |
| --- | --- |
| `FOS_Init` | `0x3001001b` |
| `FOS_UnInit` | `0x30010049` |
| `FOS_EraseSector` | `0x30010079` |
| `FOS_ProgramPage` | `0x3001008f` |
| `FOS_Verify` | did not exist — drop its call |
| `FOS_STACK_TOP` | `0x30013fe0` |
| `FOS_BKPT_ADDR` | `0x30013000` |
| `FOS_BUF_ADDR` | `0x30014000` |
| `FOS_BUF_SIZE` | did not exist — chunk over `FLASH_PAGE` again |

That algorithm has no `Verify`, so reverting also means restoring the host-side
`verify_image` of the image. `tools/tests/openocd_config.tcl` asserts the new
addresses and flow shape and has to be moved back with it.

To program an existing binary without rebuilding:

```sh
openocd -f firmware/openocd/n32h7x_cmsisdap.tcl \
  -c 'n32h7x_flash {firmware/Makefile/build/n32h787_person_detect_demo.bin}; shutdown'
```

The optional second argument to `n32h7x_flash` is the transfer speed in kHz.
Normal `make flash` uses 2000 kHz. `flash_fast` is an alias for `flash`; use
`ADAPTER_KHZ=1000` to select the older conservative transfer rate. The
measured full-image times on this NSLink/Windows setup are 65.82 s at 1 MHz and
48.14 s at 2 MHz. A 4 MHz trial caused CMSIS-DAP HID timeouts and wedged the
probe, so it is not a supported setting.

## Windows

From `firmware\Makefile`:

```
build.cmd flash
```

This builds the single M7+M4 image and flashes it at `0x15000000` (no
bootloader; the board boots this image directly). `build.cmd` locates the
N32Studio GCC/OpenOCD toolchain under `%USERPROFILE%\.n32studio`; set
`OPENOCD` to override the OpenOCD executable.

## Reset And Debug

`n32h7x_connect` initializes OpenOCD, then examines the core once AP0 is usable.
It waits `N32H7X_AP0_SETTLE_MS` (150 ms) to clear the measured BOOT window in
which AP0 reads back disabled, then polls AP0 CSW bit 6 every 10 ms up to
`N32H7X_AP0_TIMEOUT_MS` (3000 ms) instead of burning a flat wait. Raise the
settle floor if a board ever reports AP0 disabled on a connection that used to
succeed. Examination is deferred during `init`. After a manual reset, wait for
BOOT and explicitly examine again before accessing core memory. GDB attachment
performs this connection step automatically. This cfg provides the
`n32h7x_flash` command, not a native Flash bank for GDB `load`.

With NRST connected, an explicit hardware reset can be requested:

```sh
openocd -f firmware/openocd/n32h7x_cmsisdap.tcl \
  -c 'n32h7x_connect; reset_config srst_only; reset run; sleep 2000; shutdown'
```

The cfg applies the verified NSLink SELECT=0 sequence immediately before
hardware `reset run`. It also selects DP bank zero in `reset-deassert-pre`:
Linux OpenOCD 0.12.0 releases SRST even during software reset. This additional
release-side workaround alone did not prevent the former VECTRESET preparation
failure. Replacing that preparation with VECTCLRACTIVE passed two consecutive
1 MHz downloads: one from HardFault and one from a running application. After
each final software reset, a separate connection read all 19240 bytes back
identically and observed advancing camera counters. Cold-power-cycle readback
is still pending; the cause of the older incomplete Flash snapshot has not
been established. Do not treat the earlier timing measurements as a repeated
cold-boot reliability test.

The assertion workaround does not apply to hardware `reset halt`
or `reset init`, custom reset-assert handlers, or multi-target sessions.
It is not a recovery method for an already inaccessible AP0. If CPUID remains
unreadable after a fresh connection, stop and power-cycle the whole board.

No application-specific frame counters, register dumps, bypass-success flags,
or diagnostic reset cfg files are needed for normal use.
