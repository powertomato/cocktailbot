.PHONY: all clean install download erase cpu-info debug gdb_server

##############
#   config   #
##############

# paths #
OBJPATH=./obj
SRCPATH=./src
# http://www.st.com/web/catalog/tools/FM147/CL1794/SC961/SS1743/PF257884#
SPLIBPATH=./stm32f0_std_periph_lib/Libraries/STM32F0xx_StdPeriph_Driver
CMSISPATH=./stm32f0_std_periph_lib/Libraries/CMSIS
CMSISDEV=./stm32f0_std_periph_lib/Libraries/CMSIS/Device/ST/STM32F0xx
# https://github.com/texane/stlink
STLINK_PATH=~/.software/stlink
# https://launchpad.net/gcc-arm-embedded
TOOLCHAIN_PATH=~/.software/gcc-arm-none-eabi-4_7-2013q3/

# project #
MAIN=main.bin
OBJ=main.o stm32f0xx_system.o startup_stm32f0xx.o

# flags #
DEFINES=-DDEBUG -DUSE_FULL_ASSERT=1 -DUSE_STDPERIPH_DRIVER
CFLAGS=-fomit-frame-pointer -g -gdwarf-2 -mcpu=cortex-m0 -mthumb -mno-thumb-interwork -msoft-float -fdata-sections -ffunction-sections -Wl,--gc-sections -Os
LDFLAGS=-lnosys -Wl,--gc-sections -nostartfiles -T./stm32f0_std_periph_lib/linker_script/stm32f0_linker.ld

#################################################
#                 !! WARNING !!                 #
## warranty void if you scroll past this line  ##
#################################################

ECHO=@/bin/echo -e

STFLASH=$(STLINK_PATH)/st-flash
STINFO=$(STLINK_PATH)/st-info
STUTIL=$(STLINK_PATH)/st-util

GCC=$(TOOLCHAIN_PATH)/bin/arm-none-eabi-gcc
AS=$(TOOLCHAIN_PATH)/bin/arm-none-eabi-as
GDB=$(TOOLCHAIN_PATH)/bin/arm-none-eabi-gdb
OBJCPY=$(TOOLCHAIN_PATH)/bin/arm-none-eabi-objcopy
SIZE=$(TOOLCHAIN_PATH)/bin/arm-none-eabi-size

RAMSIZE=`$(STINFO) --flash 2>/dev/null`

#OBJ+=

DEFINES+=-DRAMSIZE=$(RAMSIZE)
CFLAGS+=-I./inc
CFLAGS+=-I$(SPLIBPATH)/inc
CFLAGS+=-I$(CMSISPATH)/Include
CFLAGS+=-I$(CMSISDEV)/Include


SPLIBSRC=$(shell find $(SPLIBPATH)/src -name '*.c')
SPLIBOBJ=$(SPLIBSRC:$(SPLIBPATH)/src/%.c=%.o)
OBJ+=$(SPLIBOBJ)
OBJECTS=$(OBJ:%=$(OBJPATH)/%)
MAINELF=$(MAIN:%.bin=%.elf)

ifdef VERBOSE
STFU=
STFUERR=
else
STFU=2>/dev/null >/dev/null
STFUERR=2>/dev/null
endif

RED="\e[01;31m"
GREEN="\e[01;32m"
YELLOW="\e[33m"
CLR="\e[00m"


all: $(MAIN) size


gdb_server:
	$(STUTIL) $(STFU)

debug:
	$(GDB) $(MAINELF) -ex "target remote localhost:4242"

$(MAIN): $(MAINELF)
	$(ECHO) Converting:"\t" $(YELLOW)\"$<\"$(CLR)
	@$(OBJCPY) $(MAINELF) -Obinary $(MAIN)
$(MAINELF): $(OBJECTS)
	$(ECHO) Linking:"\t" $(YELLOW)\"$<\"$(CLR)
	@$(GCC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(MAINELF)

size: $(MAINELF)
	@$(SIZE) $(MAINELF)

$(OBJPATH)/%.o : $(SRCPATH)/%.c
	$(ECHO) $(GREEN)[Application] $(CLR) Compiling:"\t" $(YELLOW)\"$<\"$(CLR)
	@$(GCC) $(CFLAGS) $(DEFINES) -c $< -o $@
$(OBJPATH)/%.o : $(SRCPATH)/%.s
	$(ECHO) $(GREEN)[Application] $(CLR) Compiling:"\t" $(YELLOW)\"$<\"$(CLR)
	@$(GCC) -x assembler-with-cpp $(CFLAGS) -c $< -o $@


$(OBJPATH)/%.o : $(SPLIBPATH)/src/%.c
	$(ECHO) $(GREEN)[STD_Periph Lib] $(CLR) Compiling:"\t" $(YELLOW)\"$<\"$(CLR)
	@$(GCC) $(CFLAGS) $(DEFINES) -c $< -o $@


cpu-info:
	$(ECHO) $(YELLOW)CPU name:$(CLR)"\t" `$(STINFO) --descr $(STFUERR)`
	$(ECHO) $(YELLOW)chip ID:$(CLR)"\t" `$(STINFO) --chipid $(STFUERR)`
	$(ECHO) $(YELLOW)flash size:$(CLR)"\t" `$(STINFO) --flash $(STFUERR)`
	$(ECHO) $(YELLOW)sram size:$(CLR)"\t" `$(STINFO) --sram $(STFUERR)`
	$(ECHO) $(YELLOW)pagesize:$(CLR)"\t" `$(STINFO) --pagesize $(STFUERR)`

erase:
	$(ECHO) $(GREEN)Erasing...$(CLR)
	@$(STFLASH) erase $(STFU)
	$(ECHO) $(GREEN)done$(CLR)

download:
	$(ECHO) $(GREEN)Reading flash...$(CLR)
	$(STFLASH) --reset read $(MAIN).`date +%F_%T` 0x8000000 $(RAMSIZE) $(STFU)
	$(ECHO) $(GREEN)done$(CLR)

install: erase $(MAIN)
	$(ECHO) $(GREEN)Flashing...$(CLR)
	@$(STFLASH) --reset write $(MAIN) 0x8000000 $(STFU)
	$(ECHO) $(GREEN)done$(CLR)

clean:
	@rm -f $(MAIN) $(MAINELF)
	@rm -f $(OBJECTS)
