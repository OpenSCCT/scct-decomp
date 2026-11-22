// campaign_leaf_0aa900.cpp -- one function at file offset 0xaa900, preferred VA 0x109aa900. A
// constructor: it records its first argument (a grid with its width at offset 0x38, height at 0x3c
// and 8-byte cells at 0x40), the address of the cell at its second and third arguments (column,
// row), those two coordinates, the same coordinates less half the width and height, and its fourth
// argument. The class, method and member names are invented; the offset and the bytes are the
// binary's.

struct UnkCell
{
    int unk_0;
    int unk_4;
};

class UnkGrid
{
public:
    unsigned char unk_0[0x38];
    unsigned int unk_38;
    unsigned int unk_3c;
    UnkCell* unk_40;
};

class UnkType_109aa900
{
public:
    UnkGrid* unk_0;
    UnkCell* unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
    int unk_18;

    UnkType_109aa900(UnkGrid* Grid, int Column, int Row, int Fourth);
};

// UnkType_109aa900::UnkType_109aa900
UnkType_109aa900::UnkType_109aa900(UnkGrid* Grid, int Column, int Row, int Fourth)
    : unk_0(Grid),
      unk_4(&Grid->unk_40[Grid->unk_38 * Row + Column]),
      unk_8(Column),
      unk_c(Row),
      unk_10(Column - ( Grid->unk_38 >> 1 )),
      unk_14(Row - ( Grid->unk_3c >> 1 )),
      unk_18(Fourth)
{
}
