// campaign_leaf_3a3830.cpp -- one function at file offset 0x3a3830, preferred VA 0x10ca3830. It
// empties a hash table: for each of the word at 0x10 buckets in the table at 0x14 it releases the
// interface at 0x0 of every chained node (next node at 0x8) through stdcall virtual slot 2 and
// frees the node through the function at 0x109014a0; it then zeroes the bucket table and the word
// at 0x1c. The class, function, structure, member and local names are invented; the offsets, the
// slot and the bytes are the binary's.

extern "C" void* __cdecl memset(void* Dest, int Value, unsigned int Count);

void Unk_109014a0(void* Block);

class UnkType_10ca3830_Interface
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual unsigned long __stdcall VirtualSlot2();
};

struct UnkType_10ca3830_Node
{
    UnkType_10ca3830_Interface* unk_0;
    int unk_4;
    UnkType_10ca3830_Node* unk_8;
};

class UnkType_10ca3830
{
public:
    void Unk_10ca3830();

    unsigned char unk_0[0x10];
    int unk_10;
    UnkType_10ca3830_Node** unk_14;
    unsigned char unk_18[0x4];
    int unk_1c;
};

// UnkType_10ca3830::Unk_10ca3830
void UnkType_10ca3830::Unk_10ca3830()
{
    int Index;

    for ( Index = 0; Index < unk_10; Index++ )
    {
        UnkType_10ca3830_Node* Node = unk_14[Index];

        while ( Node != 0 )
        {
            UnkType_10ca3830_Node* Next = Node->unk_8;

            if ( Node->unk_0 != 0 )
            {
                Node->unk_0->VirtualSlot2();
            }
            Unk_109014a0(Node);
            Node = Next;
        }
    }
    memset(unk_14, 0, unk_10 * 4);
    unk_1c = 0;
}
