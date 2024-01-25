#pragma once

#define attribute(x) __attribute__((x))
#define __cdecl attribute(cdecl)
#define RawFunction extern
#define section(x) attribute(section(x))