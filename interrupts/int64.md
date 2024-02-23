**int64** also known as **'comMap'**

**table**:\
eax interrupt are access using the register **'eax'**\
each interrupt will return **0xFFF** on failure\

**0**:state2 map (state1->state2)\
**1**:kernel map (state2->kernel)\
**1**:com    map (important functions,if they are not interrupts);