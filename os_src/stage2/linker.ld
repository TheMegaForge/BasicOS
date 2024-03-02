OUTPUT_FORMAT(binary)
ENTRY(_pstart)
INPUT
(
    build/kmc/__86.o
    build/kmc/kbd.o
    build/kmc/__kbd.o
    build/kmc/ps2.o
    build/kmc/bits.o
)
OUTPUT(build/OSp2.bin)
STARTUP(build/kmc/__main.o)
SECTIONS{
    . = 0x00100000;
    .text               : { __text_start = .;               *(.text)    }
    .data               : { __data_start = .;               *(.data)    }
    .rodata             : { __rodata_start = .;             *(.rodata)  }
    .bss                : { __bss_start = .;                *(.bss)     }

    __end = .;
}