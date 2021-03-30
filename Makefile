# Make file created to simplify building process

# declare our source and output folders
OUTPUT = build
SOURCE = src

CMD_PREFIX = 

# a BUNCH of flags required in order for our compiled files to not have unnecessary extra code
# ALSO treat all warnings as errors
CFLAGS = -nostdlib -ffreestanding -fno-stack-protector \
             -Iinclude -c
LD_FLAGS = -T link.ld

ifeq ($(OS), Windows_NT)
	CMD_PREFIX = aarch64-none-elf-
else
	uname = $(shell uname -s)
	ifeq ($(uname), Darwin)
		CMD_PREFIX = aarch64-none-elf-
	endif
endif

# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# wildcard to find all c source and header files and assembly object files required to build
C_SOURCES = $(call rwildcard,$(SOURCE)/,*.c)
ARM_SOURCES = $(call rwildcard,$(SOURCE)/,*.S)

# generate a list of all the compiled files
OBJ = ${C_SOURCES:${SOURCE}/%.c=${OUTPUT}/%.o}
OBJ += ${ARM_SOURCES:${SOURCE}/%.S=${OUTPUT}/%.o}

# do not delete build output folders if make is stopped abruptly
.PRECIOUS: $(OUTPUT)/. $(OUTPUT)%/.

# declare our compiler and debugger depending on the OS
CC = $(CMD_PREFIX)gcc
GDB = gdb
LD = $(CMD_PREFIX)ld
OBJCPY = $(CMD_PREFIX)objcopy

# default: build the iso file
kernel8.img: $(OUTPUT)/kernel.elf $(MODULES)
	$(OBJCPY) -O binary $(OUTPUT)/kernel.elf $@

# a bunch of extra targets to create the build folders
$(OUTPUT)/.:
ifeq ($(OS), Windows_NT)
	mkdir $(MKDIR_FLAGS) $(subst /,\,$@)
else
	mkdir -p $@
endif

$(OUTPUT)%/.:
ifeq ($(OS), Windows_NT)
	mkdir $(MKDIR_FLAGS) $(subst /,\,$@)
else
	mkdir -p $@
endif

# kernel
$(OUTPUT)/kernel.elf: $(OBJ)
	${LD} ${LD_FLAGS} $^ -o $@

run: kernel8.img
	@echo "Use Alt + A X to quit."
# Modify this line to specify which UART you would like to use to log. The first serial describes UART0 while the second serial describes UART1 or Mini-UART
	qemu-system-aarch64 -serial stdio -serial null -M raspi3 -kernel kernel8.img

# qemu debug to monitor registers, memory, etc. However, there is no serial output to stdio.
qemu-monitor: kernel8.img
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -monitor stdio

.SECONDEXPANSION:
# Generic rules for wildcards
$(OUTPUT)/%.o: ${SOURCE}/%.c | $$(@D)/.
	${CC} ${CFLAGS} -c $< -o $@

.SECONDEXPANSION:
$(OUTPUT)/%.o: ${SOURCE}/%.S | $$(@D)/.
	${CC} ${CFLAGS} $< -o $@

# remove build folder and img output
clean:
ifeq ($(OS), Windows_NT)
	del kernel8.img
	rmdir /s /q build
else
	rm -rf build kernel8.img
endif