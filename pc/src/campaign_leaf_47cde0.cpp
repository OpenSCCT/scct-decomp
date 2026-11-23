// campaign_leaf_47cde0.cpp -- function at VA 0x10d7cde0, from String.cpp (line 57 with the wide
// file name at 0x1113c300). Given no text it stores a null pointer. Otherwise it measures the
// 16-bit text with the function at 0x10f32740, allocates room for its characters and terminator
// as bytes plus a length word in front, stores the length, hands the caller the byte buffer and
// fills it with WideCharToMultiByte (code page 0). The function and parameter names are invented.

extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(unsigned int CodePage,
    unsigned long Flags, const unsigned short* Wide, int WideLength, char* Text, int TextLength,
    const char* DefaultChar, int* UsedDefaultChar);

unsigned int Unk_10f32740(const unsigned short* Text);
void* Unk_10d8b460();
void* Unk_10d8b4e0(void* Heap, int Size, const unsigned short* File, int Line, int Tag);

// Unk_10d7cde0
void Unk_10d7cde0(char** Result, const unsigned short* Text)
{
    int Length;
    int* Block;
    char* Buffer;

    if ( Text == 0 )
    {
        *Result = 0;
        return;
    }
    Length = Unk_10f32740(Text) + 1;
    Block = (int*)Unk_10d8b4e0(Unk_10d8b460(), Length + 4, L"String.cpp", 0x39, 9);
    Buffer = (char*)(Block + 1);
    *Block = Length;
    *Result = Buffer;
    WideCharToMultiByte(0, 0, Text, -1, Buffer, Length, 0, 0);
}
