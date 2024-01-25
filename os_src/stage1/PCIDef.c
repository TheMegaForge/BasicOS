#include "../include/PCI.h"
struct PCIHeader HD0[] = {
    {.reg = 0,.offset = 0,.attachment = ATTB_2_2_CONNECTED},
    {.reg = 1,.offset = 0x4,.attachment = ATTB_2_2_CONNECTED},{.reg = 2,.offset = 0x8,.attachment = ATTB_ALL_SEPERATED},
    {
        .reg = 3,.offset = 0xC,.attachment = ATTB_ALL_SEPERATED
    },
    {
        .reg = 4,.offset = 0x10,.attachment = ATTB_ALL_CONNECTED   
    },
    {
        .reg = 5,.offset = 0x1C,.attachment = ATTB_ALL_CONNECTED
    },
    {
        .reg = 6,.offset = 0x18,.attachment = ATTB_ALL_CONNECTED
    },
    {
        .reg = 7,.offset = 0x1C,.attachment = ATTB_ALL_CONNECTED
    },
    {
        .reg = 8,.offset = 0x20,.attachment = ATTB_ALL_CONNECTED
    },
    {
        .reg = 9,.offset = 0x24,.attachment = ATTB_ALL_CONNECTED
    },
    {
        .reg = 0xA,.offset = 0x28,.attachment = ATTB_ALL_CONNECTED
    },
    {
        .reg = 0xB,.offset = 0x2C,.attachment = ATTB_2_2_CONNECTED
    },
    {
        .reg = 0xC,.offset = 0x30,.attachment = ATTB_ALL_CONNECTED
    },
    {
        .reg = 0xD,.offset = 0x34,.attachment = ATTB_3_CONNECTED_1_SEPERATED
    },
    {
        .reg = 0xE,.offset = 0x38,.attachment = ATTB_ALL_CONNECTED
    },
    {
        .reg = 0xF,.offset = 0x3C,.attachment = ATTB_ALL_SEPERATED
    }
};
#define HD0_BAR_ENTRIES = (&HD_0[4]-&HD_0[9])sizeof(struct PCIHeader)
#define PCI_PREP(regD,offsetD,attch) {.reg = regD,.offset = offsetD,.attachment = attch}
#define COUNT_SECTION(beg,end,spec)
#define SPEC_COUNT(num,spec) num
struct PCIHeader HD1[0xF] = {
    PCI_PREP(0,0x0,ATTB_2_2_CONNECTED),PCI_PREP(1,0x4,ATTB_2_2_CONNECTED),PCI_PREP(2,0x8,ATTB_ALL_SEPERATED),PCI_PREP(3,0xC,ATTB_ALL_SEPERATED),
    PCI_PREP(4,0x10,ATTB_ALL_CONNECTED),PCI_PREP(5,0x14,ATTB_ALL_CONNECTED),PCI_PREP(6,0x18,ATTB_ALL_SEPERATED),PCI_PREP(7,0x1C,ATTB_3_CONNECTED_1_SEPERATED),
    PCI_PREP(8,0x20,ATTB_2_2_CONNECTED),PCI_PREP(9,0x24,ATTB_2_2_CONNECTED),PCI_PREP(0xA,0x28,ATTB_ALL_CONNECTED),PCI_PREP(0xB,0x2C,ATTB_2_2_CONNECTED),
    PCI_PREP(0xC,0x30,ATTB_2_2_CONNECTED),PCI_PREP(0xD,0x34,ATTB_3_CONNECTED_1_SEPERATED),PCI_PREP(0xE,0x38,ATTB_ALL_CONNECTED),PCI_PREP(0xF,0x3C,ATTB_2_CONNECTED_2_SEPERATED)
};
struct PCIHeader HD2[0x11] = {
    //TODO : IMPLEMENT HEADER IMPLEMENTATION 2 https://wiki.osdev.org/PCI
    PCI_PREP(0,0,ATTB_2_2_CONNECTED),PCI_PREP(1,4,ATTB_2_2_CONNECTED),PCI_PREP(2,8,ATTB_ALL_SEPERATED),PCI_PREP(3,0xC,ATTB_ALL_SEPERATED),
    PCI_PREP(4,0x10,ATTB_ALL_CONNECTED),PCI_PREP(5,0x14,ATTB_2_CONNECTED_2_SEPERATED),PCI_PREP(6,0x18,ATTB_ALL_SEPERATED),PCI_PREP(7,0x1C,ATTB_ALL_CONNECTED),
    PCI_PREP(8,0x20,ATTB_ALL_CONNECTED),PCI_PREP(9,0x24,ATTB_ALL_CONNECTED),PCI_PREP(0xA,0x28,ATTB_ALL_CONNECTED),PCI_PREP(0xB,0x2C,ATTB_ALL_CONNECTED),
    PCI_PREP(0xC,0x30,ATTB_ALL_CONNECTED),PCI_PREP(0xD,0x34,ATTB_ALL_CONNECTED),PCI_PREP(0xE,0x38,ATTB_ALL_CONNECTED),
    PCI_PREP(0xF,0x3C,ATTB_ALL_SEPERATED),PCI_PREP(0x10,0x40,ATTB_2_2_CONNECTED),PCI_PREP(0x11,0x44,ATTB_ALL_CONNECTED)
};
struct PCIHeaderDescriptor headers[] = {
    {//Header Type 0x0
        .count = 0xF,.headers = &HD0[0]
    },
    {//Header Type 0x1 (PCI-to-PCI bridge)
        .count = 0xF,.headers = &HD1[0]
    },
    {//Header Type 0x2 (PCI-to-CardBus bridge)
        .count = 0x11,.headers = &HD2[0]
    }
};