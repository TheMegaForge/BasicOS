OUTPUT_FORMAT(binary)
ENTRY(__setup)
INPUT
(
    build/kmc/setup.o
    build/kmc/string.o
    build/kmc/stdio.o
    build/kmc/simplealloc.o
    build/kmc/PCI.o
    build/kmc/PCIDef.o
    build/kmc/PCIStructs.o
    build/kmc/IRQ.o
    build/kmc/math.o
    build/kmc/IDT.o
    build/kmc/HAL.o
    build/kmc/isrs.o
    build/kmc/PIC.o
    build/kmc/ISR.o
    build/kmc/IDE.o
    build/kmc/ATA.o
    build/kmc/ATAdrv.o
    build/kmc/ATAI.o
    
    build/kmc/i686/IDT.o
    build/kmc/i686/io.o
    build/kmc/i686/ISR.o
    build/kmc/i686/math.o
    build/kmc/i686/string.o

    build/kmc/int/PCI.o
    build/kmc/int/binary.o
    build/kmc/int/stdio.o
    build/kmc/int/x86.o
    build/kmc/int/Driver.o
    build/kmc/int/SysCommon.o
)
OUTPUT(build/OSp1.bin)
STARTUP(build/boot/ksetjmp.o)
SECTIONS{
    . = 0x00000500;
    .setup              : { __setup_start = .;              *(.setup)   }
    .text               : { __text_start = .;               *(.text)    }
    .data               : { __data_start = .;               *(.data)    }
    .rodata             : { __rodata_start = .;             *(.rodata)  }
    .bss                : { __bss_start = .;                *(.bss)     }
    DRIVERS 0x0000F000 (NOLOAD):{
        *(drivers)
    } = 0x0
    __end = .;
}