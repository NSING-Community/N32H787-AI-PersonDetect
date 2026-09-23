/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

/* Entry Point */
ENTRY(Reset_Handler)

/* NTFx CODE START */
/* Highest address of the user mode stack */
/* AXI SRAM1 is the always-present 128 KiB bank at 0x24000000.  TCM sizing
   changes the other banks, but never extends this contiguous region.  Reset
   code calls SystemInit before any application setup, so an out-of-range MSP
   here faults on that very first BL instruction. */
_estack = 0x24020000;
/* Generate a link error if heap and stack don't fit into RAM */
/* This image has no dynamic allocation.  Keep a 4 KiB link-time stack guard
   while restoring boot; the camera diagnostic buffers occupy most AXI SRAM1. */
_Min_Heap_Size = 0x0;
_Min_Stack_Size = 0x1000;

/* Specify the memory areas */
MEMORY
{
/* The N32H787 device pack places the CM7 image at 0x15000000.
   Keep the Cube-generated 512 KB application region. */
FLASH (rx)     : ORIGIN = 0x15000000, LENGTH = 0x80000 
CM4_FLASH (rx) : ORIGIN = 0x15080000, LENGTH = 0x80000
SHARED (rw)    : ORIGIN = 0x30000000, LENGTH = 0x400
SNAPSHOT (rw) : ORIGIN = 0x30016000, LENGTH = 0xa000
QuickCodes_SRAM (rx)     : ORIGIN = 0x400 , LENGTH = 0x3fc00 
RW_SRAM (xrw)     : ORIGIN = 0x2401e000, LENGTH = 0x2000
MODEL_DTCM (r) : ORIGIN = 0x20000000, LENGTH = 0x50000
DTCM (rw)     : ORIGIN = 0x20050000, LENGTH = 0x30000
SDRAM (xrw)   : ORIGIN = 0xC0000000, LENGTH = 0x2000000
/* NTFx CODE END */

}

/* Define output sections */
SECTIONS
{
  .m4_shared (NOLOAD) : { KEEP(*(.m4_shared)) } >SHARED
  .inference_shared (NOLOAD) : { KEEP(*(.inference_shared)) } >SNAPSHOT
  .cm4_image : { KEEP(*(.cm4_image)) } >CM4_FLASH
  /* The startup code goes first into FLASH */
  .start_flash :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    KEEP (*(.init))
    KEEP (*(.fini))
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)
    /* GCC emits startup_n32h73x_76x_gcc.o (lowercase); keep reset code in
       Flash so Reset_Handler is executable before RAM/ITCM is initialized. */
    *startup_n32h7*.o (.text .text.* .rodata .rodata.* .gnu.linkonce.t.* .gnu.linkonce.r.*)
    *system_n32h7xx.o (.text .text.* .rodata .rodata.* .gnu.linkonce.t.* .gnu.linkonce.r.*)
    . = ALIGN(4);
  } >FLASH

  /* Initialized QuickCodes sections goes into SRAM, load from FLASH */
 _siQuickCodes = LOADADDR(.QuickCodes);
  .QuickCodes :
  {
    . = ALIGN(4);
    _sQuickCodes = .;        /* create a global symbol at QuickCodes start */
    *(.text .text.*)          /* .text .text.* sections (code) */
    *(.rodata .rodata.* )        /* .rodata .rodata.*  sections (constants, strings, etc.) */
    *(EXCLUDE_FILE(*startup_n32h7*.o *system_n32h7xx.o ) .text .text.* .rodata .rodata.* .gnu.linkonce.t.* .gnu.linkonce.r.*)
    . = ALIGN(4);
    _eQuickCodes = .;        /* define a global symbols at end of QuickCodes */
  } >QuickCodes_SRAM AT> FLASH

  /* Flash holds only the load image. Inference reads the DTCM copy. */
  _siperson_model = LOADADDR(.person_model);
  .person_model :
  {
    . = ALIGN(16);
    _sperson_model = .;
    KEEP(*(.person_model))
    . = ALIGN(16);
    _eperson_model = .;
  } >MODEL_DTCM AT>FLASH

  ASSERT(_sperson_model == ORIGIN(MODEL_DTCM), "Model must run from DTCM")
  ASSERT(_siperson_model >= ORIGIN(FLASH) &&
         _siperson_model + SIZEOF(.person_model) <= ORIGIN(FLASH) + LENGTH(FLASH),
         "Model load image overlaps M4 Flash")
  ASSERT(_eperson_model <= ORIGIN(DTCM), "Model overlaps inference workspace")

  .person_arena (NOLOAD) :
  {
    . = ALIGN(16);
    _sperson_arena = .;
    *(.person_arena)
    *(.person_state)
    *(.inference_private)
    *(.m7_diagnostics)
    . = ALIGN(16);
    _eperson_arena = .;
  } >DTCM

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH

  /* Initialized at runtime after SDRAM_Configuration(), so this must remain
     NOLOAD and must not be touched by reset-time .bss clearing. */
  .sdram_bss (NOLOAD) :
  {
    . = ALIGN(32);
    *(.sdram_bss .sdram_bss.*)
    . = ALIGN(32);
  } >SDRAM
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH
  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections goes into RW_SRAM, load LMA copy after code */
  .data : /*可读写且需要初始化数据 */
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RW_SRAM AT> FLASH

  
  /* Uninitialized data section */
  . = ALIGN(4);
  .bss :/*可读写的置零初始化数据  */
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RW_SRAM

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RW_SRAM

  

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
