// campaign_leaf_47cd80.cpp -- function at VA 0x10d7cd80, from String.cpp (line 47 with the wide
// file name at 0x1113c300). Given no text it stores a null pointer. Otherwise it allocates room
// for the text's characters and terminator as 16-bit characters plus a length word in front,
// stores the length, hands the caller the character buffer and fills it with MultiByteToWideChar
// (code page 0). The function and parameter names are invented.

extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(unsigned int CodePage,
    unsigned long Flags, const char* Text, int TextLength, unsigned short* Wide, int WideLength);

extern "C" unsigned int strlen(const char* Text);

void* Unk_10d8b460();
void* Unk_10d8b4e0(void* Heap, int Size, const unsigned short* File, int Line, int Tag);

// Unk_10d7cd80
void Unk_10d7cd80(unsigned short** Result, const char* Text)
{
    int Length;
    int* Block;
    unsigned short* Buffer;

    if ( Text == 0 )
    {
        *Result = 0;
        return;
    }
    Length = strlen(Text) + 1;
    Block = (int*)Unk_10d8b4e0(Unk_10d8b460(), Length * 2 + 4, L"String.cpp", 0x2f, 9);
    Buffer = (unsigned short*)(Block + 1);
    *Block = Length;
    *Result = Buffer;
    MultiByteToWideChar(0, 0, Text, -1, Buffer, Length);
}
