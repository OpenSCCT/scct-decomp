// campaign_leaf_3cb9d0.cpp -- a variadic free function at VA 0x10ccb9d0 that passes the global
// buffer at VA 0x112d5158, its size 0x1000 and the address of its argument list to the free
// function at VA 0x10ccada0. guess: formats a message into a global buffer. The function, parameter
// and global names are invented; the addresses are the binary's.

#include "campaign_global_112d5158.h"

void Unk_10ccada0(unsigned short* Dest, int Count, const unsigned short** Args);

// Unk_10ccb9d0
void Unk_10ccb9d0(const unsigned short* Format, ...)
{
    Unk_10ccada0(GUnk_112d5158, 0x1000, &Format);
}
