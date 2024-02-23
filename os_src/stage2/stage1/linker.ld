OUTPUT_FORMAT(binary)
ENTRY(__pre__)
INPUT
(
    build/kmc/__main.o
)
OUTPUT(build/OSp2.bin)
SECTIONS{
    . = 0x00100000;
    .setup              : { __setup_start = .;              *(.setup)   }
    .text               : { __text_start = .;               *(.text)    }
    .data               : { __data_start = .;               *(.data)    }
    .rodata             : { __rodata_start = .;             *(.rodata)  }
    .bss                : { __bss_start = .;                *(.bss)     }

    __end = .;
}