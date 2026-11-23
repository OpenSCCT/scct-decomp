// campaign_leaf_491210.cpp -- thiscall method at VA 0x10d91210, from StationURL.cpp (the wide file
// name and line 408 it passes to the allocator). It frees the length-prefixed 16-bit buffer at
// 0x00; given a text, it measures it with 0x10f32740, allocates a buffer for its characters and
// terminator plus the length word, stores the length, points 0x00 at the characters and copies
// the text there with 0x10f331b9. The class, method and parameter names are invented.

unsigned int Unk_10f32740(const unsigned short* Text);
void Unk_10f331b9(unsigned short* Target, const unsigned short* Source);
void* Unk_10d8b460();
void* Unk_10d8b4e0(void* Heap, int Size, const unsigned short* File, int Line, int Tag);
void Unk_10d8b550(void* Heap, void* Block, int Tag);

class UnkType_10d91210
{
public:
    void Unk_10d91210(const unsigned short* Text);

private:
    unsigned short* unk_0;
};

// UnkType_10d91210::Unk_10d91210
void UnkType_10d91210::Unk_10d91210(const unsigned short* Text)
{
    int Length;
    int* Block;
    unsigned short* Buffer;

    if ( unk_0 )
    {
        Unk_10d8b550(Unk_10d8b460(), (int*)unk_0 - 1, 9);
    }
    if ( Text )
    {
        Length = Unk_10f32740(Text) + 1;
        Block = (int*)Unk_10d8b4e0(Unk_10d8b460(), Length * 2 + 4, L"StationURL.cpp", 0x198, 9);
        Buffer = (unsigned short*)(Block + 1);
        *Block = Length;
        unk_0 = Buffer;
        Unk_10f331b9(Buffer, Text);
    }
}
