# Make file created to simplify building process

# declare our source and output folders
OUTPUT = build
SOURCE = src

# declare filenames before wildcarding in order to add source folder prefix
# specifically, all the c source, header, and compiled assembly files.
FOLDERS = * iso/modules/* utils/* drivers/* drivers/hardware/* kernel/* kernel/gdt/* kernel/idt/* kernel/utils/* kernel/mem/* kernel/error/* kernel/mem/paging/* kernel/idt/pic/*
FOLDERS_W_PREFIX = $(addprefix ${SOURCE}/, $(FOLDERS))
C_FILES = $(addsuffix .c, $(FOLDERS_W_PREFIX))
C_HEADERS = $(addsuffix .h, $(FOLDERS_W_PREFIX))
NASM_FILES = $(addsuffix .S, $(FOLDERS_W_PREFIX))
BIN_FILES = $(addsuffix .asm, $(FOLDERS_W_PREFIX))

# wildcard to find all c source and header files and assembly object files required to build
C_SOURCES = $(wildcard ${C_FILES})
HEADERS = $(wildcard ${C_HEADERS})
NASM_SOURCES = $(wildcard ${NASM_FILES})
BIN_SOURCES = $(wildcard ${BIN_FILES})

# generate a list of all the compiled files
OBJ = ${C_SOURCES:${SOURCE}/%.c=${OUTPUT}/%.o}
OBJ += ${NASM_SOURCES:${SOURCE}/%.S=${OUTPUT}/%.o}

MODULES = ${BIN_SOURCES:${SOURCE}/%.asm=${OUTPUT}/%.bin}

# do not delete build output folders if make is stopped abruptly
.PRECIOUS: $(OUTPUT)/. $(OUTPUT)%/.

# find out if the OS is Mac
uname = $(shell uname -s)
is_darwin = $(filter Darwin,$(uname))

# declare our compiler and debugger depending on the OS
CC = $(if $(is_darwin), aarch64-none-elf-gcc, gcc)
GDB = gdb
LD = $(if $(is_darwin), aarch64-none-elf-ld, ld)
OBJCPY = $(if $(is_darwin), aarch64-none-elf-objcopy, objcopy)
ISO_MAKER = $(if $(is_darwin), mkisofs, genisoimage)

# a BUNCH of flags required in order for our compiled files to not have unnecessary extra code
# ALSO treat all warnings as errors
# also build with i386 (x32)
CFLAGS = -nostdlib -nostdinc -ffreestanding -fno-stack-protector \
             -Wall -Wextra -Werror -c
LD_FLAGS = -T link.ld

# default: build the iso file
kernel8.img: $(OUTPUT)/kernel.elf $(MODULES)
	$(OBJCPY) -O binary $(OUTPUT)/kernel.elf $@

# a bunch of extra targets to create the build folders
$(OUTPUT)/.: 
	mkdir -p $@

$(OUTPUT)%/.: 
	mkdir -p $@

# kernel
$(OUTPUT)/kernel.elf: $(OBJ)
	${LD} ${LD_FLAGS} $^ -o $@

# run target
run-bochs: os.iso
	bochs -f bochsrc.txt -q

run: kernel8.img
	@echo "Use Alt + A X to quit."
	qemu-system-aarch64 -nographic -M raspi3 -kernel kernel8.img

# qemu debug to monitor registers, memory, etc. However, there is no serial output to stdio.
qemu-monitor: kernel8.img
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -monitor stdio

.SECONDEXPANSION:
# Generic rules for wildcards
$(OUTPUT)/%.o: ${SOURCE}/%.c ${HEADERS} | $$(@D)/.
	${CC} ${CFLAGS} -c $< -o $@

.SECONDEXPANSION:
$(OUTPUT)/%.o: ${SOURCE}/%.S | $$(@D)/.
	${CC} ${CFLAGS} $< -o $@

.SECONDEXPANSION:
$(OUTPUT)/%.bin: ${SOURCE}/%.asm | $$(@D)/.
	${CC} $< -f bin -o $@

# remove build folder and iso output
clean:
	rm -rf build kernel8.img