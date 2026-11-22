// campaign_leaf_044670.cpp -- one function at file offset 0x44670, preferred VA 0x10944670. It
// returns the word at offset 0 plus (the word at offset 4, less the argument, less one) times 0x98.
// The class and method names are invented; the offset and the bytes are the binary's.

class UnkType_10944670
{
public:
    int UnkElement(int Index) const;

private:
    int unk_00;                     // base value
    int unk_04;                     // count, less one for the index
};

// UnkType_10944670::UnkElement
int UnkType_10944670::UnkElement(int Index) const
{
    return unk_00 + ( unk_04 - Index - 1 ) * 0x98;
}
