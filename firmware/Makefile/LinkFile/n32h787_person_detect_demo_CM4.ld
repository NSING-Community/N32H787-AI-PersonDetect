/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

/* Entry Point */
ENTRY(Reset_Handler)

/* NTFx CODE START */
/* Highest address of the user mode stack */
_estack = 0x30022000;    /* initially use only 8 KiB of SRAM2 */
/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x500;      /* required amount of heap  */
_Min_Stack_Size = 0x500;     /* required amount of stack */

/* Specify the memory areas */
MEMORY
{
FLASH (rx)     : ORIGIN = 0x15080000, LENGTH = 0x80000
SHARED (rw)   : ORIGIN = 0x30000000, LENGTH = 0x400
VECTORS (rw)  : ORIGIN = 0x30000400, LENGTH = 0x400
QuickCodes_SRAM (xrw)     : ORIGIN = 0x30000800, LENGTH = 0x15800
SNAPSHOT (rw) : ORIGIN = 0x30016000, LENGTH = 0xa000
CAMERA_DMA (rw) : ORIGIN = 0x24000000, LENGTH = 0x1e000
JPEG_PIXELS (rw) : ORIGIN = 0x24020000, LENGTH = 0x40000
/* Contiguous AHB SRAM2 remainder + SRAM3; leave M4 data/stack untouched. */
CAMERA_FRAME (rw) : ORIGIN = 0x30022000, LENGTH = 0x26000
RW_SRAM (xrw)     : ORIGIN = 0x30020000, LENGTH = 0x2000
/* NTFx CODE END */

}

/* Define output sections */
SECTIONS
{
  .m4_shared (NOLOAD) : { KEEP(*(.m4_shared)) } >SHARED
  .m4_vectors (NOLOAD) : { KEEP(*(.m4_vectors)) } >VECTORS
  .inference_shared (NOLOAD) : { KEEP(*(.inference_shared)) } >SNAPSHOT
  .camera_dma (NOLOAD) : { *(.camera_dma) } >CAMERA_DMA
  .jpeg_pixels (NOLOAD) : { *(.jpeg_pixels) } >JPEG_PIXELS
  .camera_frame (NOLOAD) : { *(.camera_frame) } >CAMERA_FRAME
  /* The startup code goes first into FLASH */
  .start_flash :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(1024);
    KEEP (*(.init))
    KEEP (*(.fini))
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)
    *startup_n32h7*.o (.text.Reset_Handler)
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

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
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

  .ARM.attributes 0 : { *(.ARM.attributes) }
}

