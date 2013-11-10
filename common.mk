
ECHO=@/bin/echo -e

STFLASH=$(STLINK_PATH)/st-flash
STINFO=$(STLINK_PATH)/st-info
STUTIL=$(STLINK_PATH)/st-util

GCC=$(TOOLCHAIN_PATH)/bin/arm-none-eabi-gcc
AS=$(TOOLCHAIN_PATH)/bin/arm-none-eabi-as
GDB=$(TOOLCHAIN_PATH)/bin/arm-none-eabi-gdb
OBJCPY=$(TOOLCHAIN_PATH)/bin/arm-none-eabi-objcopy
SIZE=$(TOOLCHAIN_PATH)/bin/arm-none-eabi-size

RAMSIZE=`$(STINFO) --flash 2>/dev/null)`
REALTARGET=`$(STINFO) --descr $(STFUERR)`

DEFINES+=-DRAMSIZE=$(RAMSIZE)
CFLAGS+=-I$(INCPATH)
CFLAGS+=-I$(INCHWPATH)
CFLAGS+=-I$(SPLIBPATH)/inc
CFLAGS+=-I$(CMSISPATH)/Include
CFLAGS+=-I$(CMSISDEV)/Include


SPLIBSRC+=$(shell find $(SPLIBPATH)/src -name '*.c')
SPLIBOBJ+=$(SPLIBSRC:$(SPLIBPATH)/src/%.c=%.o)
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


all: $(OBJPATH) $(MAIN) size

$(OBJPATH):
	mkdir -p $(OBJPATH)

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

#
# hardware independent source-file rules
#
$(OBJPATH)/%.o : $(SRCPATH)/%.c
	$(ECHO) $(GREEN)[Application] $(CLR) Compiling:"\t" $(YELLOW)\"$<\"$(CLR)
	@$(GCC) $(CFLAGS) $(DEFINES) -c $< -o $@
$(OBJPATH)/%.o : $(SRCPATH)/%.s
	$(ECHO) $(GREEN)[Application] $(CLR) Assembling:"\t" $(YELLOW)\"$<\"$(CLR)
	@$(GCC) -x assembler-with-cpp $(CFLAGS) -c $< -o $@
#
# hardware dependent source-file rules
# 
$(OBJPATH)/%.o : $(SRCHWPATH)/%.c
	$(ECHO) $(GREEN)[Application HW dep.] $(CLR) Compiling:"\t" $(YELLOW)\"$<\"$(CLR)
	@$(GCC) $(CFLAGS) $(DEFINES) -c $< -o $@
$(OBJPATH)/%.o : $(SRCHWPATH)/%.s
	$(ECHO) $(GREEN)[Application HW dep.] $(CLR) Assembling:"\t" $(YELLOW)\"$<\"$(CLR)
	@$(GCC) -x assembler-with-cpp $(CFLAGS) -c $< -o $@

#
# std periph library rules
#
$(OBJPATH)/%.o : $(SPLIBPATH)/src/%.c
	$(ECHO) $(GREEN)[STD_Periph Lib] $(CLR) Compiling:"\t" $(YELLOW)\"$<\"$(CLR)
	@$(GCC) $(CFLAGS) $(DEFINES) -c $< -o $@


cpu-info:
	$(ECHO) $(YELLOW)TARGET name:$(CLR)"\t" `$(STINFO) --descr $(STFUERR)`
	$(ECHO) $(YELLOW)chip ID:$(CLR)"\t" `$(STINFO) --chipid $(STFUERR)`
	$(ECHO) $(YELLOW)flash size:$(CLR)"\t" `$(STINFO) --flash $(STFUERR)`
	$(ECHO) $(YELLOW)sram size:$(CLR)"\t" `$(STINFO) --sram $(STFUERR)`
	$(ECHO) $(YELLOW)pagesize:$(CLR)"\t" `$(STINFO) --pagesize $(STFUERR)`

check_target:
	$(ECHO) -n Expecting TARGET: $(YELLOW)\"$(TARGET)\"$(CLR)
	$(shell if [ "$(REALTARGET)" != $(TARGET) ];then return 1; fi )
	$(ECHO) $(GREEN) [OK] $(CLR)

erase: check_target
	$(ECHO) -n Erasing...
	@$(STFLASH) erase $(STFU)
	$(ECHO) $(GREEN) [OK] $(CLR)

download: check_target
	$(ECHO) -n Reading flash...
	$(STFLASH) --reset read $(MAIN).`date +%F_%T` 0x8000000 $(RAMSIZE) $(STFU)
	$(ECHO) $(GREEN) [OK] $(CLR)

install: erase $(MAIN)
	$(ECHO) -n Flashing...
	@$(STFLASH) --reset write $(MAIN) 0x8000000 $(STFU)
	$(ECHO) $(GREEN) [OK]  $(CLR)

clean:
	@rm -f $(MAIN) $(MAINELF)
	@rm -f $(OBJECTS)
