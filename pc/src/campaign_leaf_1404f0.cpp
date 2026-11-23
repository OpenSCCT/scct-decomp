// campaign_leaf_1404f0.cpp -- one function at file offset 0x1404f0, preferred VA 0x10a404f0.
// It takes the object at offset 0x6c of its first argument; unless that object is missing, is the
// first entry of its third argument, has bit 0x1 set at offset 0x28 or is already in the pointer
// array its second argument refers to, it recurses on that object and then passes it and the array
// to the function at VA 0x10a40480. It has no this pointer.
// The function and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a404f0_Node
{
public:
    unsigned char unk_0[0x28];
    int unk_28;
    unsigned char unk_2c[0x6c - 0x2c];
    UnkType_10a404f0_Node* unk_6c;
};

struct UnkType_10a404f0_Array
{
    UnkType_10a404f0_Node** Data;
    int ArrayNum;
};

void Unk_10a40480(UnkType_10a404f0_Node* Node, UnkType_10a404f0_Array& Array);

// Unk_10a404f0
void Unk_10a404f0(UnkType_10a404f0_Node* Node, UnkType_10a404f0_Array& Array,
    UnkType_10a404f0_Array& Stop)
{
    UnkType_10a404f0_Node* Next = Node->unk_6c;
    if ( Next && Next != Stop.Data[0] && !( Next->unk_28 & 1 ) )
    {
        for ( int i = 0; i < Array.ArrayNum; i++ )
        {
            if ( Array.Data[i] == Next )
            {
                return;
            }
        }
        Unk_10a404f0(Next, Array, Stop);
        Unk_10a40480(Next, Array);
    }
}
