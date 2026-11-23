// campaign_leaf_73d4f0.cpp -- one function at file offset 0x73d4f0, preferred VA 0x1103d4f0. It
// resets a record: it clears the word at 0x50, copies the empty string into the 0x21-character
// buffer at 0x54 through the stdcall function at VA 0x11049240, clears the words from 0x8 to 0x4c
// and sets the words at 0x0, 0x4, 0x28 and 0x2c to -2. The type and function names are invented;
// the offsets and the callee's address are the binary's.

void __stdcall Unk_11049240(char* Buffer, const char* Text, unsigned int Count);

struct UnkType_1103d4f0
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4c;
    int unk_50;
    char unk_54[0x21];
};

// Unk_1103d4f0
void Unk_1103d4f0(UnkType_1103d4f0* Record)
{
    Record->unk_50 = 0;
    Unk_11049240(Record->unk_54, "", 0x21);
    Record->unk_c = 0;
    Record->unk_34 = 0;
    Record->unk_30 = 0;
    Record->unk_8 = 0;
    Record->unk_18 = 0;
    Record->unk_1c = 0;
    Record->unk_40 = 0;
    Record->unk_44 = 0;
    Record->unk_20 = 0;
    Record->unk_24 = 0;
    Record->unk_48 = 0;
    Record->unk_4c = 0;
    Record->unk_10 = 0;
    Record->unk_14 = 0;
    Record->unk_38 = 0;
    Record->unk_3c = 0;
    Record->unk_0 = -2;
    Record->unk_28 = -2;
    Record->unk_4 = -2;
    Record->unk_2c = -2;
}
