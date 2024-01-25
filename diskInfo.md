**GetFileSystemInformation**:\
    **does not save registers do to working with the stack**\
**Stack Structure after calling**:\
|-----------------------|                                               \
| **dx**:                                                               \
| &nbsp;*upper*: maximum heads                                          \
| &nbsp;*lower*: number of drives                                       \
|-----------------------|                                               \
| **cx**:                                                               \
| &nbsp;*upper*: low 8 bits of maximum cylinder number                  \
| &nbsp;*lower*: maximum sector number **(bits 5-0)**,maximum cylinder number **(bits 7-6)**\
|-----------------------|           \
| **bx**                            \
| &nbsp;*lower*:drive type          \
| &nbsp;*upper*:**unused**          \
|                                                              
|-----------------------|
