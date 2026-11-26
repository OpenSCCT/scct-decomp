#include "campaign_array_allocator.h"

extern "C" {
extern void __stdcall release_73c870(void *pointer);

void __cdecl release_route_0014a0(void *pointer)
{
    reinterpret_cast<ArrayAllocatorVirtual *>(array_allocator)->Release(pointer);
}

void __cdecl release_route_0014e0(void *pointer)
{
    reinterpret_cast<ArrayAllocatorVirtual *>(array_allocator)->Release(pointer);
}

void __cdecl release_route_469670(void *pointer)
{
    release_73c870(pointer);
}

void __cdecl release_route_747ae0(void *pointer) { release_73c870(pointer); }
void __cdecl release_route_75ae00(void *pointer) { release_73c870(pointer); }
void __cdecl release_route_75c0f0(void *pointer) { release_73c870(pointer); }
void __cdecl release_route_75cbc0(void *pointer) { release_73c870(pointer); }
void __cdecl release_route_75d300(void *pointer) { release_73c870(pointer); }
void __cdecl release_route_75eac0(void *pointer) { release_73c870(pointer); }
void __cdecl release_route_75ee20(void *pointer) { release_73c870(pointer); }
void __cdecl release_route_760fe0(void *pointer) { release_73c870(pointer); }
void __cdecl release_route_7653d0(void *pointer) { release_73c870(pointer); }
void __cdecl release_route_765e50(void *pointer) { release_73c870(pointer); }
void __cdecl release_route_767150(void *pointer) { release_73c870(pointer); }
void __cdecl release_route_767a10(void *pointer) { release_73c870(pointer); }
void __cdecl release_route_76f7b0(void *pointer) { release_73c870(pointer); }
void __cdecl release_route_77c720(void *pointer) { release_73c870(pointer); }
}
