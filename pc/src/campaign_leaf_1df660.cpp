// campaign_leaf_1df660.cpp -- thiscall method at VA 0x10adf660 of a tree node gathering statistics
// into the object at 0x00. A leaf (array at 0x1c set) counts itself at 0x60, adds its count (the
// array's word at 0x04) to 0x58 and its square to 0x5c, and folds it into the maximum at 0x70 and
// the minimum at 0x74. An inner node counts its kind (word at 0x2c: 0, 1 or 2) at 0x64, 0x68 or
// 0x6c and recurses into the children at 0x20 and 0x24. It returns 1. The class, method and member
// names are invented.

// Max
template<class T> inline T Max(const T A, const T B)
{
    return (A >= B) ? A : B;
}

// Min
template<class T> inline T Min(const T A, const T B)
{
    return (A <= B) ? A : B;
}

struct UnkType_10adf660_Stats
{
    char unk_00[0x58];
    int unk_58;
    int unk_5c;
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6c;
    int unk_70;
    int unk_74;
};

struct UnkType_10adf660_Array
{
    int unk_0;
    int unk_4;
};

class UnkType_10adf660
{
public:
    int Unk_10adf660();

private:
    UnkType_10adf660_Stats* unk_00;
    char unk_04[0x1c - 0x04];
    UnkType_10adf660_Array* unk_1c;
    UnkType_10adf660* unk_20;
    UnkType_10adf660* unk_24;
    int unk_28;
    int unk_2c;
};

// UnkType_10adf660::Unk_10adf660
int UnkType_10adf660::Unk_10adf660()
{
    if ( unk_1c )
    {
        unk_00->unk_60++;
        int Count = unk_1c->unk_4;
        unk_00->unk_58 += Count;
        unk_00->unk_5c += Count * Count;
        unk_00->unk_70 = Max(unk_00->unk_70, Count);
        unk_00->unk_74 = Min(unk_00->unk_74, Count);
        return 1;
    }
    switch ( unk_2c )
    {
    case 0:
        unk_00->unk_64++;
        break;
    case 1:
        unk_00->unk_68++;
        break;
    case 2:
        unk_00->unk_6c++;
        break;
    }
    if ( unk_20 )
    {
        unk_20->Unk_10adf660();
    }
    if ( unk_24 )
    {
        unk_24->Unk_10adf660();
    }
    return 1;
}
