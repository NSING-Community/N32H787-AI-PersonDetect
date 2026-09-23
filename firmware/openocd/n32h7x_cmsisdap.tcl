# Copyright (c) 2025 Nations Technologies Inc.
# SPDX-License-Identifier: Apache-2.0

# Nations N32H78x/H76x NRP-1A, Cortex-M7, CMSIS-DAP NSLink (HID).
# Validated board: N32H787XIB7. This is not a universal N32H7 Flash driver.
# Keep flash_op/n32h7xx_flash_op.bin beside this configuration.

adapter driver cmsis-dap
cmsis_dap_vid_pid 0x19f5 0x3106
# cmsis_dap_backend hid
transport select swd
adapter speed 1000
source [find mem_helper.tcl]

swd newdap n32h7x cpu -irlen 4 -ircapture 0x1 -irmask 0xf -expected-id 0x2ba01477
dap create n32h7x.dap -chain-position n32h7x.cpu
target create n32h7x.cpu0 cortex_m -endian little -dap n32h7x.dap -ap-num 0
# BOOT may temporarily disable AP0. Call n32h7x_connect before core access.
n32h7x.cpu0 configure -defer-examine
reset_config none connect_deassert_srst
cortex_m reset_config sysresetreq
adapter srst pulse_width 100
adapter srst delay 1000
gdb_memory_map enable
gdb_flash_program enable
gdb_breakpoint_override hard
n32h7x.cpu0 configure -event gdb-attach {n32h7x_connect; halt 3000}
n32h7x.cpu0 configure -event gdb-detach {resume}

# OpenOCD 0.12.0 releases SRST even for software reset (reset_config none).
# Keep SELECT=0 immediately before that native deassert path as well.
# This complements the hardware assertion sequence below.
n32h7x.cpu0 configure -event reset-deassert-pre {n32h7x.dap dpreg 8 0}

# The NSLink/N32H787 hardware-reset sequence requires SELECT=0 immediately
# before NRST assertion. Their native core reset handling is preserved.
proc n32h7x_assert_run {} {
    set ::n32h7x_assert_result [catch {
        mww 0xe000edf8 0
        mww 0xe000edf0 0xa05f0003
        set dfsr [mrw 0xe000ed30]
        mww 0xe000ed30 $dfsr
        mww 0xe000edf0 0xa05f0001
        n32h7x.dap dpreg 8 0
        adapter assert srst
        sleep 50
    } ::n32h7x_assert_error]
}

# Preserve OpenOCD's outer recursion guard, deassert and reconnect handling.
if {[llength [info procs n32h7x_original_reset_inner]] == 0} {
    rename ocd_process_reset_inner n32h7x_original_reset_inner
}
proc ocd_process_reset_inner {mode} {
    set cfg [reset_config]
    set has_srst [expr {[lsearch -exact $cfg srst_only] >= 0 ||
                       [lsearch -exact $cfg trst_and_srst] >= 0}]
    if {$mode ne "run" || !$has_srst || [transport select] ne "swd" ||
        [target names] ne "n32h7x.cpu0"} {
        return [n32h7x_original_reset_inner $mode]
    }
    set old_assert [n32h7x.cpu0 cget -event reset-assert]
    if {$old_assert ne ""} {return [n32h7x_original_reset_inner $mode]}
    set ::n32h7x_assert_result -1
    set ::n32h7x_assert_error "reset-assert was not reached"
    set rc [catch {
        n32h7x.cpu0 configure -event reset-assert {n32h7x_assert_run}
        n32h7x_original_reset_inner $mode
        # The native event dispatcher does not propagate Tcl callback errors.
        if {$::n32h7x_assert_result != 0} {error $::n32h7x_assert_error}
    } result]
    n32h7x.cpu0 configure -event reset-assert $old_assert
    unset ::n32h7x_assert_result
    unset ::n32h7x_assert_error
    if {$rc != 0} {error $result}
    return $result
}

# BOOT holds AP0 disabled for the first ~120 ms after the debugger's nRESET
# pulse, so the old flat 2000 ms wait was mostly margin. Keep a short floor for
# that measured window, then poll for AP0 instead of sleeping the rest.
set N32H7X_AP0_SETTLE_MS 150
set N32H7X_AP0_TIMEOUT_MS 3000
set N32H7X_AP0_POLL_MS 10

proc n32h7x_wait_ap0 {} {
    set waited 0
    set csw 0
    set dap_error ""
    while {1} {
        if {$waited >= $::N32H7X_AP0_SETTLE_MS} {
            set dap_error ""
            if {[catch {set csw [n32h7x.dap apreg 0 0]} err]} {
                set csw 0
                set dap_error $err
            } elseif {($csw & 0x40) != 0} {
                return $csw
            }
        }
        if {$waited >= $::N32H7X_AP0_TIMEOUT_MS} {break}
        sleep $::N32H7X_AP0_POLL_MS
        incr waited $::N32H7X_AP0_POLL_MS
    }
    set detail "CSW=[format 0x%08x $csw]"
    if {$dap_error ne ""} {append detail ", last DAP error: $dap_error"}
    error "AP0 is disabled after BOOT wait ($detail); power-cycle the board before reconnecting"
}

proc n32h7x_connect {} {
    init
    n32h7x_wait_ap0
    n32h7x.cpu0 arp_examine
}

# Vendor flash_op.bin from N32Studio's N32H7 OpenOCD configuration, in AHB SRAM1.
# Position-independent: its only absolute literals are peripheral and system-memory
# addresses, never RAM, so the load base is ours to choose.
# M4 must be held in reset before reusing its RAM. AXI SRAM1 may be unusable
# after the camera application's fault, so neither code nor stack lives there.
set FLASH_START 0x15000000
set FLASH_SIZE 0x001e0000
set FLASH_PAGE 0x1000
set FLASH_ALGO_BASE 0x30010000
set FLASH_ALGO_BIN [file join [file dirname [info script]] flash_op n32h7xx_flash_op.bin]
# AHB SRAM1 layout, inside the M4 QuickCodes window (0x30000800..0x30016000):
#   0x30010000-0x3001020f : algorithm code (528 bytes)
#   0x30010210-0x30010fdf : FlashOS stack, growing down from the top below
#   0x30010ff0            : BKPT instruction for function return
#   0x30011000-0x30014fff : 16 KiB page buffer, one chunk per program call
#   0x30015000-0x300153ff : OpenOCD work area
#   0x30016000..          : shared inference snapshot, never touched
# The 3.5 KiB of stack headroom is the vendor layout's own figure: its cfg puts
# the 528-byte algorithm at 0x24000000 and the stack top at 0x24000fe0.
set FOS_BUF_ADDR 0x30011000
set FOS_BUF_SIZE 0x4000
set FOS_STACK_TOP 0x30010fe0
set FOS_BKPT_ADDR 0x30010ff0
set FOS_Init 0x30010041
set FOS_UnInit 0x30010071
set FOS_EraseSector 0x300100e1
set FOS_ProgramPage 0x30010139
set FOS_Verify 0x30010199
# This algorithm's EraseChip (0x30010091) is a stub that returns success without
# erasing anything. Never wire a mass-erase command to it.

proc n32h7x_stop_m4_camera {} {
    # Give a healthy application a chance to finish its serial transfer.
    # Recovery must not depend on a faulted application acknowledging a request.
    if {([mrw 0x58030174] & 1) != 0 && [mrw 0x30000000] == 0x4d344951} {
        mww 0x300002a8 0x4d344951
        set paused 0
        for {set attempt 0} {$attempt < 150} {incr attempt} {
            if {[mrw 0x300002ac] == 0x4d344951} {set paused 1; break}
            sleep 20
        }
        if {!$paused} {echo "M4 did not acknowledge; stopping it through RCC reset"}
    }
    # RCC_M4RSTREL=0 is also the first operation in the vendor FlashOS Init.
    mww 0x58030174 0
    if {([mrw 0x58030174] & 1) != 0} {error "M4 could not be held in reset"}
    # Reset the camera's independent bus masters, not just their owning CPU.
    # RCC_AXIRST2.DVP2RST and RCC_AXIRST1.JPEGERST.
    foreach {address mask} {0x58030154 0x100 0x58030150 0x100000} {
        set saved [mrw $address]
        mww $address [expr {$saved | $mask}]
        sleep 1
        mww $address $saved
    }
}

proc n32h7x_quiesce_cached_m7 {} {
    if {([mrw 0xe000ed14] & 0x30000) == 0} {return}
    # Only resume firmware explicitly implementing this non-cacheable ABI.
    # Never run injected cache maintenance against arbitrary/faulted firmware.
    if {[mrw 0x30000000] != 0x4d344951 || [mrw 0x300002b4] != 0x4d374331} {
        error "Enabled caches without M7 flash-pause ABI; stop/clean caches in firmware before flashing"
    }
    mww 0x300002b0 0
    mww 0x300002a8 0x4d344951
    set paused 0
    set rc [catch {
        resume
        for {set attempt 0} {$attempt < 400} {incr attempt} {
            if {[mrw 0x300002b0] == 0x4d344951} {set paused 1; break}
            sleep 20
        }
    } result]
    halt 3000
    wait_halt 3000
    if {$rc != 0} {error $result}
    if {!$paused || ([mrw 0xe000ed14] & 0x30000) != 0} {
        error "M7 cache shutdown was not acknowledged; Flash untouched"
    }
    echo "M7 paused with caches cleaned and disabled"
}

proc n32h7x_get_core_regs {{names {pc msp xPSR}}} {
    # Linux OpenOCD names this xPSR; N32Studio's Windows build uses xpsr.
    set compatible {}
    foreach name $names {
        lappend compatible [expr {$name eq "xPSR" ? "xpsr" : $name}]
    }
    if {[catch {get_reg -force $names} result]} {
        set result [get_reg -force $compatible]
    }
    return $result
}

proc n32h7x_xpsr {registers} {
    if {[dict exists $registers xPSR]} {return [dict get $registers xPSR]}
    return [dict get $registers xpsr]
}

proc n32h7x_flash_profile_enabled {} {
    return [expr {[info exists ::N32H7X_FLASH_PROFILE] &&
                  $::N32H7X_FLASH_PROFILE}]
}

proc n32h7x_flash_profile_begin {} {
    if {![n32h7x_flash_profile_enabled]} {return ""}
    mww 0xe000edfc [expr {[mrw 0xe000edfc] | 0x01000000}]
    mww 0xe0001fb0 0xc5acce55
    mww 0xe0001000 [expr {[mrw 0xe0001000] | 1}]
    mww 0xe0001004 0
    return [clock milliseconds]
}

proc n32h7x_flash_profile_end {func started} {
    if {$started eq ""} {return}
    set elapsed [expr {[clock milliseconds] - $started}]
    set cycles [mrw 0xe0001004]
    set name unknown
    set func_key [format 0x%08x $func]
    foreach pair [list [list init $::FOS_Init] \
                       [list erase $::FOS_EraseSector] \
                       [list program $::FOS_ProgramPage] \
                       [list verify $::FOS_Verify] \
                       [list uninit $::FOS_UnInit]] {
        if {$func_key eq [format 0x%08x [lindex $pair 1]]} {
            set name [lindex $pair 0]
            break
        }
    }
    if {![info exists ::N32H7X_FLASH_STATS]} {set ::N32H7X_FLASH_STATS [dict create]}
    dict incr ::N32H7X_FLASH_STATS ${name}_calls
    dict incr ::N32H7X_FLASH_STATS ${name}_ms $elapsed
    dict incr ::N32H7X_FLASH_STATS ${name}_cycles $cycles
}

proc n32h7x_wait_flashos_halt {} {
    if {![info exists ::N32H7X_FLASH_FAST_HALT] || !$::N32H7X_FLASH_FAST_HALT} {
        sleep 10
        wait_halt 30000
        return
    }
    # OpenOCD's wait_halt polls on a coarse interval. FlashOS calls are short,
    # so poll frequently when the caller explicitly enables this path.
    set deadline [expr {[clock milliseconds] + 30000}]
    while {1} {
        poll
        if {[n32h7x.cpu0 curstate] eq "halted"} {return}
        if {[clock milliseconds] >= $deadline} {error "FlashOS halt timeout"}
        sleep 1
    }
}

proc n32h7x_flashos_call {func args} {
    set profile_started [n32h7x_flash_profile_begin]
    mww $::FOS_BKPT_ADDR 0x0000be00
    set i 0
    foreach name {r0 r1 r2 r3} {
        if {$i < [llength $args]} {
            reg $name [lindex $args $i]
        } else {
            reg $name 0
        }
        incr i
    }
    reg sp $::FOS_STACK_TOP
    reg lr [expr {$::FOS_BKPT_ADDR | 1}]
    reg pc $func
    reg primask 1
    resume
    if {[catch {n32h7x_wait_flashos_halt} result]} {
        catch {halt 3000}
        error "FlashOS timeout at [format 0x%08x $func]: $result"
    }
    set returned [n32h7x_get_core_regs {r0 pc xPSR}]
    set pc [dict get $returned pc]
    if {($pc != $::FOS_BKPT_ADDR && $pc != $::FOS_BKPT_ADDR + 2) ||
        ([n32h7x_xpsr $returned] & 0x010001ff) != 0x01000000} {
        error "FlashOS stopped outside its return breakpoint: $returned"
    }
    set value [dict get $returned r0]
    if {$value != 0} {
        error "FlashOS failed at [format 0x%08x $func], status=$value"
    }
    n32h7x_flash_profile_end $func $profile_started
}

# High-level entry point: prepare, program, verify, then software-reset to run.
# Only the image's occupied sectors are erased. The start must be page-aligned.
proc n32h7x_flash {image {transfer_khz 1000} {start_addr 0x15000000}} {
    if {![file isfile $image]} {error "Image not found: $image"}
    if {![file isfile $::FLASH_ALGO_BIN]} {error "Flash algorithm not found: $::FLASH_ALGO_BIN"}
    set length [file size $image]
    if {$length == 0 || $start_addr < $::FLASH_START ||
        $start_addr + $length > $::FLASH_START + $::FLASH_SIZE ||
        ($start_addr % $::FLASH_PAGE) != 0} {
        error "Image must fit in Flash and start on a 4096-byte boundary"
    }
    if {![string is integer -strict $transfer_khz] || $transfer_khz <= 0} {
        error "Transfer speed must be a positive integer in kHz"
    }
    set stage "connect"
    set rc [catch {
        n32h7x_connect
        set stage "halt"
        halt 3000
        wait_halt 3000
        set stage "halted CPU validation"
        set cpuid [mrw 0xe000ed00]
        set dhcsr [mrw 0xe000edf0]
        set core [n32h7x_get_core_regs]
        if {($cpuid & 0xff0ffff0) != 0x410fc270 ||
            ($dhcsr & 0x30000) != 0x30000 ||
            ([n32h7x_xpsr $core] & 0x01000000) == 0 ||
            [dict get $core msp] == 0} {
            error "Invalid halted CPU state: CPUID=[format 0x%08x $cpuid], DHCSR=[format 0x%08x $dhcsr], $core"
        }
        set stage "cache check"
        n32h7x_quiesce_cached_m7
        if {([mrw 0xe000ed14] & 0x30000) != 0} {
            error "FlashOS preparation with enabled instruction/data caches is not supported"
        }
        set stage "M4 and camera reset"
        n32h7x_stop_m4_camera
        set stage "stop SysTick"
        mww 0xe000e010 0
        # Debug-only VECTCLRACTIVE clears Handler state without restarting BOOT.
        # VECTRESET/reset halt can disable AP0 on this chip during secure BOOT.
        set stage "clear active exceptions"
        set aircr [mrw 0xe000ed0c]
        mww 0xe000ed0c [expr {0x05fa0002 | ($aircr & 0x700)}]
        set stage "post-clear poll"
        poll
        set stage "Thread-mode check"
        if {([mrw 0xe000ed04] & 0x1ff) != 0} {
            error "Refusing to execute FlashOS outside Thread mode"
        }
        set stage "interrupt and MPU preparation"
        set banks [expr {([mrw 0xe000e004] & 0xf) + 1}]
        for {set i 0} {$i < $banks} {incr i} {
            mww [expr {0xe000e180 + 4 * $i}] 0xffffffff
            mww [expr {0xe000e280 + 4 * $i}] 0xffffffff
        }
        mww 0xe000ed04 0x0a000000
        mww 0xe000ed28 0xffffffff
        mww 0xe000ed2c 0xffffffff
        mww 0xe000ed94 0
        set stage "core register preparation"
        # Register 16 is xPSR; its spelling differs between OpenOCD versions.
        reg 16 0x01000000
        reg control 0
        reg msp $::FOS_STACK_TOP
        reg sp $::FOS_STACK_TOP
        reg basepri 0
        reg faultmask 0
        reg primask 1
    } result]
    set restore_rc [catch {cortex_m reset_config sysresetreq} restore_result]
    if {$rc != 0} {
        if {$result eq ""} {set result "OpenOCD returned an error without details"}
        error "Flash preparation failed at $stage: $result. Flash was not erased or programmed."
    }
    if {$restore_rc != 0} {
        error "Cannot restore SYSRESETREQ mode: $restore_result. Flash was not erased or programmed."
    }
    adapter speed $transfer_khz
    # A separate AHB scratch area lets OpenOCD verify with its CRC routine.
    # It does not overlap FlashOS code, stack, page buffer or snapshot RAM.
    n32h7x.cpu0 configure -work-area-phys 0x30015000 -work-area-size 0x400 -work-area-backup 0
    # A successful SWD write is not proof that SRAM stored the algorithm.
    # Verify before executing Init or allowing any Flash erase/program calls.
    if {[catch {
        load_image $::FLASH_ALGO_BIN $::FLASH_ALGO_BASE bin
        verify_image $::FLASH_ALGO_BIN $::FLASH_ALGO_BASE bin
    } result]} {
        error "FlashOS RAM load/verification failed: $result. Flash was not erased or programmed."
    }
    n32h7x_flashos_call $::FOS_Init $start_addr 0 1
    set end [expr {$start_addr + $length}]
    for {set address $start_addr} {$address < $end} {incr address $::FLASH_PAGE} {
        n32h7x_flashos_call $::FOS_EraseSector $address
    }
    for {set address $start_addr} {$address < $end} {incr address $::FOS_BUF_SIZE} {
        set offset [expr {$address - $start_addr}]
        set count [expr {$end - $address}]
        if {$count > $::FOS_BUF_SIZE} {set count $::FOS_BUF_SIZE}
        # For raw binaries, load_image takes min_addr/max_length, not a file
        # offset. Relocate the base to select this chunk without Tcl byte strings.
        load_image $image [expr {$::FOS_BUF_ADDR - $offset}] bin $::FOS_BUF_ADDR $count
        n32h7x_flashos_call $::FOS_ProgramPage $address $count $::FOS_BUF_ADDR
        # Verify on the target while the chunk is still staged, so no Flash is
        # ever read back over SWD. This compares the buffer against Flash; it
        # cannot detect a chunk that was corrupted identically in both.
        n32h7x_flashos_call $::FOS_Verify $address $count $::FOS_BUF_ADDR
        echo "Programmed and verified [format 0x%08x $address] ($count bytes)"
    }
    n32h7x_flashos_call $::FOS_UnInit 0
    echo "Flash verified: $length bytes (on-target per-chunk compare)"
    # Keep reset/BOOT communication at the conservative connection speed.
    adapter speed 100
    reset run
    echo "Reset complete; application released to run"
}
