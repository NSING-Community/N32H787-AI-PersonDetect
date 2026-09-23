# Copyright (c) 2025 Nations Technologies Inc.
# SPDX-License-Identifier: Apache-2.0

######################################
# target
######################################
SHELL := /bin/sh

TARGET = n32h787_person_detect_demo
OPENOCD ?= openocd
OPENOCD_CONFIG := ../openocd/n32h7x_cmsisdap.tcl
# Connect conservatively, then use the validated NSLink transfer rate.
CONNECT_KHZ ?= 1000
# 2 MHz completes about 27% faster than 1 MHz. 4 MHz wedges the NSLink HID.
ADAPTER_KHZ ?= 2000

######################################
# building variables
######################################
# debug build
ifeq ($(release), y)
DEBUG = 0
else
DEBUG = 1
endif
# optimization
OPT = -O2

#######################################
# Build path
#######################################
BUILD_DIR = build

#####################################
# chip platform info
######################################
TARGET_STARTUP  := n32h78x_cm7
## NTFx CODE START Define ##
DEFS += -DCORE_CM7
# Required by CMSIS cache APIs; the vendor device header omits them.
DEFS += -D__DCACHE_PRESENT=1U -D__ICACHE_PRESENT=1U
DEFS += -DN32H78x
DEFS += -DUSE_STDPERIPH_DRIVER
DEFS += -DUSING_TCM
# The prebuilt TensorFlow Lite Micro library was built with this reduced
# TfLiteTensor/TfLiteNode ABI.  Every translation unit including TFLM headers
# must use the identical ABI.
DEFS += -DTF_LITE_STATIC_MEMORY
## NTFx CODE END Define ##
######################################
# Algo libs
######################################
#USELIB = 0

######################################
#TOOLS CHAIN
######################################
# The gcc path can be defined by 3 methods:
# 1.Define it in make command via GCC_PATH variable (> make GCC_PATH="D:\\Program Files (x86)\\GNU Arm Embedded Toolchain\\10 2020-q4-major\\bin\\")
# 2.Added it to the PATH environment variable
# 3.Define it in makefile ,such as :
#GCC_PATH = 'D:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2020-q4-major\bin\'
ifdef GCC_PATH
CROSS_COMPILE = $(GCC_PATH)arm-none-eabi-
else 
CROSS_COMPILE = arm-none-eabi-
endif


######################################
# C sources
######################################
## NTFx CODE START C sources ##
C_DIRS += ../USER/src
C_DIRS += ../Driver/CMSIS/core
C_DIRS += ../Driver/CMSIS/device
C_DIRS += ../Driver/n32h7xx_std_periph_driver/src
## NTFx CODE END C sources ##

# TensorFlow Lite Micro classifier sources (compiled as C++).
CPP_DIRS += ../USER/src

PYTHON ?= python3

C_SOURCES = $(foreach DIR, $(C_DIRS), $(wildcard $(DIR)/*.c))
CPP_SOURCES = $(foreach DIR, $(CPP_DIRS), $(wildcard $(DIR)/*.cc))

######################################
# ASM sources
######################################
ASM_SOURCES =../Driver/CMSIS/device/startup/startup_$(TARGET_STARTUP)_gcc.s

######################################
# C includes
######################################
## NTFx CODE START C includes ##
C_INCS += ../USER/inc
C_INCS += ../Driver/CMSIS/core
C_INCS += ../Driver/CMSIS/device
C_INCS += ../Driver/n32h7xx_std_periph_driver/inc
## NTFx CODE END C includes ##
TFLM_INCLUDES = -I../USER/tflm_sdk \
                -I../USER/tflm_sdk/third_party/flatbuffers/include \
                -I../USER/tflm_sdk/third_party/gemmlowp \
                -I../USER/tflm_sdk/third_party/ruy

INCS_OBJS_DIR = $(foreach DIR2, $(C_INCS), $(wildcard $(DIR2)/*.h))
INCS_OBJS_PATH = $(sort $(dir $(INCS_OBJS_DIR)))
C_INCLUDES = $(addprefix -I,$(INCS_OBJS_PATH))
C_INCLUDES += $(TFLM_INCLUDES)

######################################
# Lib files
######################################
ifeq ($(USELIB), 1)
SRC_LIB_DIR += ../Driver/n32h7xx_algo_lib/lib
INC_LIB_DIR += ../Driver/n32h7xx_algo_lib/inc
LIB_SOURCES = $(foreach DIR3, $(SRC_LIB_DIR), $(wildcard $(DIR3)/*.lib))
LIB_SOURCES_L = $(addprefix -L,$(LIB_SOURCES))
C_LIBS = $(LIB_SOURCES_L)
LIB_INCS = $(foreach DIR4, $(INC_LIB_DIR), $(wildcard $(DIR4)/*.h))
LIB_INCS_PATH = $(sort $(dir $(LIB_INCS)))
LIB_INCS_PATH_I = $(addprefix -I,$(LIB_INCS_PATH))
C_INCLUDES += $(LIB_INCS_PATH_I)
endif

######################################
# Compile & Link flags
######################################
# cpu
CPU = -mcpu=cortex-m7
FPU = -mfpu=fpv5-d16
FLOAT-ABI = -mfloat-abi=hard
# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

#CFLAGS
CFLAGS += $(MCU) -Wall
CFLAGS += $(OPT)
CFLAGS += -ffunction-sections -fdata-sections
#DEBUG
ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif
# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
CXXFLAGS = $(CFLAGS) -std=gnu++17 -fno-exceptions -fno-rtti
#LFLAGS
LFLAGS += $(MCU)
LFLAGS += -Wl,--gc-sections 
LFLAGS += --specs=nosys.specs
LFLAGS += -Xlinker -Map=$(BUILD_DIR)/$(TARGET).map
# link script
LDSCRIPT = LinkFile/n32h787_person_detect_demo_CM7.ld

######################################
# Objects
######################################
.PHONY: all app flash flash_fast flash_verify probe benchmark debug
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
app: $(BUILD_DIR)/$(TARGET).bin

# No bootloader: the image starts at 0x15000000 and is flashed as a single
# combined M7+M4 binary (the M4 image is embedded via .cm4_image).
flash: $(BUILD_DIR)/$(TARGET).bin
	$(OPENOCD) -d1 -c 'gdb_port disabled' -f $(OPENOCD_CONFIG) -c 'adapter speed $(CONNECT_KHZ); n32h7x_flash {$(abspath $(BUILD_DIR)/$(TARGET).bin)} $(ADAPTER_KHZ); shutdown'

# No-write connection check.  Run this first when programming gets stuck.
probe:
	$(OPENOCD) -d1 -c 'gdb_port disabled' -f $(OPENOCD_CONFIG) -c 'adapter speed $(CONNECT_KHZ); n32h7x_connect; poll; shutdown'

# Compatibility alias: normal flashing already uses the faster transfer rate.
flash_fast: flash

# Compatibility alias: every normal flash now verifies before restarting.
flash_verify: flash

# Reads run counters after allowing time for initialization and inference.
benchmark: $(BUILD_DIR)/$(TARGET).bin
	@BENCH_ADDR=`$(CROSS_COMPILE)nm -n $(BUILD_DIR)/$(TARGET).elf | awk '$$3 == "g_model_benchmark" {print "0x" $$1}'`; \
	test -n "$$BENCH_ADDR"; \
	$(OPENOCD) -d0 -c 'gdb_port disabled' -f $(OPENOCD_CONFIG) -c "n32h7x_connect; reset run; sleep 5000; n32h7x.cpu0 arp_examine; halt 3000; echo init_error=[mrw [expr {$$BENCH_ADDR + 4}]]; echo sdram_status=[mrw [expr {$$BENCH_ADDR + 16}]]; echo arena_used_bytes=[mrw [expr {$$BENCH_ADDR + 20}]]; echo invoke_last_cycles=[mrw [expr {$$BENCH_ADDR + 24}]]; echo invoke_max_cycles=[mrw [expr {$$BENCH_ADDR + 28}]]; echo scores=[mrw [expr {$$BENCH_ADDR + 32}]]; echo frames_ok=[mrw [expr {$$BENCH_ADDR + 36}]]; echo preprocess_cycles=[mrw [expr {$$BENCH_ADDR + 40}]]; echo invoke_cycles=[mrw [expr {$$BENCH_ADDR + 44}]]; resume; shutdown"

# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of C++ objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cc=.o)))
vpath %.cc $(sort $(dir $(CPP_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
OBJECTS += $(BUILD_DIR)/cm4_image.o
vpath %.s $(sort $(dir $(ASM_SOURCES)))

# M4 has its own ABI, startup and SRAM. Do not reuse any M7 objects.
M4_BUILD = $(BUILD_DIR)/cm4
M4_FLAGS = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard \
           -O2 -g -Wall -ffunction-sections -fdata-sections -MMD -MP
M4_DEFS = -DCORE_CM4 -DN32H78x -DUSE_STDPERIPH_DRIVER
M4_OBJECTS = $(M4_BUILD)/main.o $(M4_BUILD)/startup_n32h78x_cm4_gcc.o
M4_C_SOURCES = ../CM4/src/camera_app.c ../USER/src/ov5640.c \
    ../USER/src/n32h7xx_cfg.c \
    ../USER/src/camera_color.c ../USER/src/jpeg_encoder.c \
    ../USER/src/jpeg_encoder_tables.c \
    $(addprefix ../Driver/n32h7xx_std_periph_driver/src/,n32h7xx_rcc.c \
    n32h7xx_gpio.c n32h7xx_i2c.c n32h7xx_usart.c n32h7xx_dvp.c \
    n32h7xx_mmu.c n32h7xx_jpeg.c n32h7xx_dma.c n32h7xx_dmamux.c)
M4_OBJECTS += $(addprefix $(M4_BUILD)/,$(notdir $(M4_C_SOURCES:.c=.o)))
vpath %.c ../CM4/src

$(M4_BUILD)/%.o: %.c Makefile | $(M4_BUILD)
	"$(CROSS_COMPILE)gcc" $(M4_FLAGS) $(M4_DEFS) $(C_INCLUDES) -c $< -o $@

$(M4_BUILD):
	@mkdir -p $@

$(M4_BUILD)/main.o: ../CM4/src/main.c Makefile | $(M4_BUILD)
	"$(CROSS_COMPILE)gcc" $(M4_FLAGS) $(M4_DEFS) $(C_INCLUDES) -c $< -o $@

$(M4_BUILD)/startup_n32h78x_cm4_gcc.o: ../Driver/CMSIS/device/startup/startup_n32h78x_cm4_gcc.s Makefile | $(M4_BUILD)
	"$(CROSS_COMPILE)gcc" $(M4_FLAGS) -c $< -o $@

$(M4_BUILD)/$(TARGET)_CM4.elf: $(M4_OBJECTS) LinkFile/n32h787_person_detect_demo_CM4.ld Makefile
	"$(CROSS_COMPILE)gcc" $(M4_FLAGS) $(M4_OBJECTS) --specs=nosys.specs \
	    -Wl,--gc-sections,-Map=$(M4_BUILD)/$(TARGET)_CM4.map -TLinkFile/n32h787_person_detect_demo_CM4.ld -o $@
	"$(CROSS_COMPILE)size" $@

$(M4_BUILD)/$(TARGET)_CM4.bin: $(M4_BUILD)/$(TARGET)_CM4.elf
	"$(CROSS_COMPILE)objcopy" -O binary -S $< $@

$(BUILD_DIR)/cm4_image.o: ../CM4/image.s $(M4_BUILD)/$(TARGET)_CM4.bin Makefile
	"$(CROSS_COMPILE)gcc" $(MCU) -c $< -o $@

.PHONY: cm4
cm4: $(M4_BUILD)/$(TARGET)_CM4.bin

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	"$(CROSS_COMPILE)gcc" $(CFLAGS) $(DEFS) $(C_INCLUDES) $(C_LIBS) -c -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cc Makefile | $(BUILD_DIR)
	"$(CROSS_COMPILE)g++" $(CXXFLAGS) $(DEFS) $(C_INCLUDES) -c -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cc=.lst)) $< -o $@
    
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	"$(CROSS_COMPILE)gcc" $(CFLAGS) -c $< -o $@
    
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile $(LDSCRIPT) ../USER/tflm_sdk/lib/libtensorflow-microlite.a
	"$(CROSS_COMPILE)g++" $(OBJECTS) ../USER/tflm_sdk/lib/libtensorflow-microlite.a $(LFLAGS) -T$(LDSCRIPT) -o $@
	"$(CROSS_COMPILE)size" $@
	
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	"$(CROSS_COMPILE)objcopy" -O binary -S $< $@

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	"$(CROSS_COMPILE)objcopy" -O ihex -S $< $@
    
$(BUILD_DIR):
	@-mkdir $@

# The person_detect model is 294 KB, which would be a 1.8 MB source file if it
# were written out by hand, so it is generated from the .tflite instead.  It
# lands in USER/src, where the CPP_SOURCES wildcard above picks it up.  This
# rule deliberately sits after `all:` -- make takes the first rule in the file
# as its default goal.
PERSON_MODEL = ../../models/person_detect.tflite

../USER/src/person_model_data.cc: $(PERSON_MODEL) ../../tools/embed_tflite.py ../USER/inc/person_model_data.h
	$(PYTHON) ../../tools/embed_tflite.py $< $@ --symbol g_person_model_data \
	    --header person_model_data.h --section .person_model

#######################################
# clean up
#######################################
clean:
	rm -rf $(BUILD_DIR)

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)
-include $(wildcard $(M4_BUILD)/*.d)

#######################################
# gdb server (optional; flashing uses OpenOCD via `make flash`)
#######################################
CHIP_TYPE = N32H760xIx7

debug:
	@JLinkGDBServer.exe -select USB -device $(CHIP_TYPE) -if SWD -speed auto -noir -LocalhostOnly

# *** EOF ***
