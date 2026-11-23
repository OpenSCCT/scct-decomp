// campaign_leaf_3c1a10.cpp -- one function at file offset 0x3c1a10, preferred VA 0x10cc1a10. When
// the window at 0x4 of the object at 0x1f0 is unset or still a window (IsWindow), the word at
// 0x200 is clear and the words at 0x8c, 0x90 and 0x60 are set, it copies the word at 0x8c to
// 0x18c and returns the method at 0x10a45910 with (First, Second); otherwise it returns 0. The
// class, method, member and parameter names are invented; the import is named by the retail
// import table, and the offsets and the bytes are the binary's.

#include "campaign_import_IsWindow.h"

class UnkType_10cc1a10_Window
{
public:
    int unk_0;
    HWND unk_4;
};

class UnkType_10cc1a10
{
public:
    int Unk_10a45910(int First, int Second);
    int Unk_10cc1a10(int First, int Second);

    unsigned char unk_0[0x60];
    int unk_60;
    unsigned char unk_64[0x28];
    int unk_8c;
    int unk_90;
    unsigned char unk_94[0xf8];
    int unk_18c;
    unsigned char unk_190[0x60];
    UnkType_10cc1a10_Window* unk_1f0;
    unsigned char unk_1f4[0xc];
    int unk_200;
};

// UnkType_10cc1a10::Unk_10cc1a10
int UnkType_10cc1a10::Unk_10cc1a10(int First, int Second)
{
    HWND Window = unk_1f0->unk_4;

    if ( Window != 0 && !IsWindow(Window) )
    {
        return 0;
    }
    if ( unk_200 != 0 || unk_8c == 0 || unk_90 == 0 || unk_60 == 0 )
    {
        return 0;
    }
    unk_18c = unk_8c;
    return Unk_10a45910(First, Second);
}
