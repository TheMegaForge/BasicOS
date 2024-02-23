#pragma once
//0x00000000	0x000003FF	1 KiB	Real Mode IVT (Interrupt Vector Table)	unusable in real mode	640 KiB RAM ("Low memory") (USED)
//0x00000400	0x000004FF	256 bytes	BDA (BIOS data area) (USED)
//0x00000500	0x00007BFF	29.75 KiB	Conventional memory	usable memory (USED)
//0x00007C00	0x00007DFF	512 bytes	Your OS BootSector (USED)
//0x00007E00	0x0007FFFF	480.5 KiB	Conventional memory (USED!)
#define STACK_POS               0x0000F000 // <-
#define NATIVE_TALK_BEGIN       0x0000F000 // ->
#define MAX_CONV_MEMORY         0x0007FFFF
#define MEMORY_MIN              0x00000500

#define TEXT_DESC_OUTPUT        0x00007E00
#define TEXT_DESC_OUTPUT_END    0x000080FF  //~800 bytes
#define MEM_MAP_BEGIN           TEXT_DESC_OUTPUT_END
#define MEM_MAP_END             0x000082FF  // ~500 bytes
#define PCI_BUSSES_BEGIN        0x000082FF
#define PCI_BUSSES_END          PCI_BUSSES_BEGIN+(565*13)  //565 devices
#define MEMORY_MAX              0x00080000
//0x00080000	0x0009FFFF	128 KiB	EBDA (Extended BIOS Data Area)	partially used by the EBDA (USED)
//0x000A0000	0x000BFFFF	128 KiB	Video display memory	hardware mapped	384 KiB System / Reserved ("Upper Memory") (USED)
//0x000C0000	0x000C7FFF	32 KiB (typically)	Video BIOS	ROM and hardware mapped / Shadow RAM (/)
//0x000C8000	0x000EFFFF	160 KiB (typically)	BIOS Expansions
//0x000F0000	0x000FFFFF	64 KiB	Motherboard BIOS
//0x00100000	0x00EFFFFF	0x00E00000 (14 MiB)	RAM -- free for use (if it exists)	Extended memory 1, 2
//0x00F00000	0x00FFFFFF	0x00100000 (1 MiB)	Possible memory mapped hardware	ISA Memory Hole 15-16MB 3
//0x01000000	 ????????	 ???????? (whatever exists)	RAM -- free for use	More Extended memory 1
//0xC0000000 (sometimes, depends on motherboard and devices)	0xFFFFFFFF	0x40000000 (1 GiB)	various (typically reserved for memory mapped devices)	Memory mapped PCI devices, PnP NVRAM?, IO APIC/s, local APIC/s, BIOS, ...
//0x0000000100000000 (possible memory above 4 GiB)	 ????????????????	 ???????????????? (whatever exists)	RAM -- free for use (PAE/64bit)	More Extended memory 1
// ????????????????

#define DRV_STRUCT_SIZE sizeof(int)*2+sizeof(void*)
/*
    -- Possible memory --
    0x00000500	0x00007BFF(0x00007BE0) (KERNEL)
    0x00100000	0x00EFFFFF
    0x01000000  ?????????? (32 BIT RAM)
*/
/*
    used memory:
    0x7BE0 (32 Bit temporary handler value)
    0x00000500  0x00007BFF (KERNEL)
    0x00008000  0x0000F000 (OS STACK)
    0x0000F000  0x0000F640 (DRIVERS)
*/


#define MEM_MAP_SIZE_LOC (void*)0x7B00
#define STAGE_1_LOCATION (void*)0x00000500 // ->
#define MAX_STAGE_1_POS (void*)0x00007BE0
#define POSSIBLE_STAGE_1_SIZE 0x76E0 //30432

#define STAGE_2_LOCATION (void*)0x00100000
#define STAGE_2_END      (void*)0x00500000
#define STAGE_2_POSSIBLE_SIZE 0x400000
#define STAGE_2_POSSIBLE_SIZE_KB_1024 4096