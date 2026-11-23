// campaign_leaf_47d160.cpp -- thiscall method at VA 0x10d7d160, from String.cpp (the wide file
// name and line 191 it passes to the allocator). It frees the current buffer at 0x00, whose
// length word sits just before it, then allocates room for the given number of 16-bit characters
// plus that length word, stores the length, points 0x00 just past it and empties the string. The
// class, method and parameter names are invented.

void* Unk_10d8b460();
void* Unk_10d8b4e0(void* Heap, int Size, const unsigned short* File, int Line, int Tag);
void Unk_10d8b550(void* Heap, void* Block, int Tag);

class UnkType_10d7d160
{
public:
    void Unk_10d7d160(int Length);

private:
    unsigned short* unk_0;
};

// UnkType_10d7d160::Unk_10d7d160
void UnkType_10d7d160::Unk_10d7d160(int Length)
{
    int* Block;
    unsigned short* Text;

    if ( unk_0 )
    {
        Unk_10d8b550(Unk_10d8b460(), (int*)unk_0 - 1, 9);
    }
    Block = (int*)Unk_10d8b4e0(Unk_10d8b460(), Length * 2 + 4, L"String.cpp", 0xbf, 9);
    Text = (unsigned short*)(Block + 1);
    *Block = Length;
    unk_0 = Text;
    *Text = 0;
}
