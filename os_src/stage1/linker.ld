OUTPUT_FORMAT(binary)
ENTRY(__setup)
INPUT
(
    build/kmc/setup.o
    build/kmc/string.o
    build/kmc/string_.o
    build/kmc/stdio.o
    build/kmc/simplealloc.o
    build/kmc/io.o
    build/kmc/math.o
    build/kmc/PCI.o
    build/kmc/PCIDef.o
    build/kmc/PCIStructs.o
    build/kmc/IDT_.o
    build/kmc/IDT.o
    build/kmc/HAL.o
    build/kmc/int/PCI.o
    build/kmc/int/binary.o
)
OUTPUT(build/OSp1.bin)
STARTUP(build/boot/ksetjmp.o)
SECTIONS{
    . = 0x00000500;
    .setup              : { __setup_start = .;      *(.setup)   }
    .text               : { __text_start = .;       *(.text)    }
    .data               : { __data_start = .;       *(.data)    }
    .rodata             : { __rodata_start = .;     *(.rodata)  }
    .bss                : { __bss_start = .;        *(.bss)     }
    
    __end = .;
}