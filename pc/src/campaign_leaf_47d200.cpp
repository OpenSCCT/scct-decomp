// campaign_leaf_47d200.cpp -- variadic function at VA 0x10d7d200. It formats its arguments into a
// local buffer of 0x1000 16-bit characters with the function at 0x10f33887 and, unless the string
// already points at that buffer, frees the string's length-prefixed buffer and copies the
// formatted text into it with 0x10d7ce40. The function, class and parameter names are invented.

int Unk_10f33887(unsigned short* Dest, int Count, const unsigned short* Format, char* Args);
void* Unk_10d8b460();
void Unk_10d8b550(void* Heap, void* Block, int Tag);

struct UnkType_10d7d200_String
{
    unsigned short* unk_0;
};

void Unk_10d7ce40(UnkType_10d7d200_String* String, const unsigned short* Text);

// Unk_10d7d200
void Unk_10d7d200(UnkType_10d7d200_String* String, const unsigned short* Format, ...)
{
    unsigned short Buffer[0x1000];

    Unk_10f33887(Buffer, 0x1000, Format, (char*)( &Format + 1 ));
    if ( String->unk_0 != Buffer )
    {
        if ( String->unk_0 )
        {
            Unk_10d8b550(Unk_10d8b460(), (int*)String->unk_0 - 1, 9);
        }
        Unk_10d7ce40(String, Buffer);
    }
}
