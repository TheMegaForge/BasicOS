NASM_FLAGS = -f bin 
CC = $(TARGET)-gcc
LD = $(TARGET)-ld
REAL_MODE_FILE = TRM.bin
CC_FLAGS = -c -ffreestanding -mno-red-zone -m32 -nostdlib
LD_FLAGS_S1 = -T os_src/stage1/linker.ld
FPF = fpf.bin

TOOL_CHAIN = $$HOME/Toolchain
BUILD_BOOT =  build/boot
BUILD_KERNEL = build/kmc
BOOT_SRC = boot
TARGET = $(TOOL_CHAIN)/i686-elf/bin/i386-elf
STAGE_1 = os_src/stage1
STAGE_1_OUT = build/kmc
INTERNEL_OUT = build/kmc/int
all: mkboot mksetup _cat _trunc
mkboot:
	nasm $(ASM_FLAGS) $(BOOT_SRC)/main.asm -I / -o $(BUILD_BOOT)/main.o
	nasm $(ASM_FLAGS) $(BOOT_SRC)/AR.asm -I / -o $(BUILD_BOOT)/AR.o
	nasm $(ASM_FLAGS) $(BOOT_SRC)/procMode.asm -I / -o $(BUILD_BOOT)/procMode.o
	nasm $(ASM_FLAGS) $(BOOT_SRC)/ZEROS.asm -I / -o $(BUILD_BOOT)/ZEROS.o
	nasm -f elf $(BOOT_SRC)/ksetupjmp.asm -I / -o $(BUILD_BOOT)/ksetjmp.o#
	nasm -f elf $(STAGE_1)/i686/io.asm -I / -o $(STAGE_1_OUT)/io.o
	nasm -f elf $(STAGE_1)/i686/math.asm -I / -o $(STAGE_1_OUT)/math.o
	nasm -f elf $(STAGE_1)/i686/IDT.asm -I / -o $(STAGE_1_OUT)/IDT_.o
	nasm -f elf $(STAGE_1)/i686/string.asm -I / -o $(STAGE_1_OUT)/string_.o
	nasm -f elf os_src/internel/PCI.asm -I / -o $(STAGE_1_OUT)/int/PCI.o
	nasm -f elf os_src/internel/binary.asm -I / -o $(STAGE_1_OUT)/int/binary.o
mksetup:
	$(CC) $(CC_FLAGS) os_src/stage1/setup.c -o build/kmc/setup.o
	$(CC) $(CC_FLAGS) os_src/stage1/stdio.c -o build/kmc/stdio.o
	$(CC) $(CC_FLAGS) os_src/stage1/simplealloc.c -o build/kmc/simplealloc.o
	$(CC) $(CC_FLAGS) os_src/stage1/string.c -o build/kmc/string.o
	$(CC) $(CC_FLAGS) os_src/stage1/PCI.c -o build/kmc/PCI.o
	$(CC) $(CC_FLAGS) os_src/stage1/PCIDef.c -o build/kmc/PCIDef.o
	$(CC) $(CC_FLAGS) os_src/stage1/PCIStructs.c -o build/kmc/PCIStructs.o
	$(CC) $(CC_FLAGS) os_src/stage1/IDT.c -o build/kmc/IDT.o
	$(CC) $(CC_FLAGS) os_src/stage1/HAL.c -o build/kmc/HAL.o
	$(LD) $(LD_FLAGS_S1)
_cat:
	cat $(BUILD_BOOT)/main.o $(BUILD_BOOT)/AR.o > build/$(REAL_MODE_FILE)
	cat build/$(REAL_MODE_FILE) $(BUILD_BOOT)/procMode.o > build/$(FPF)
	cat build/$(FPF) build/OSp1.bin > build/ffp.bin
	cat build/ffp.bin $(BUILD_BOOT)/ZEROS.o > build/OS.bin
	cp build/OS.bin build/_OS.img
_trunc:
	truncate -s 1440k build/_OS.img