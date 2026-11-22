// campaign_leaf_4281c0.cpp -- one function at file offset 0x4281c0, preferred VA 0x10d281c0. It
// sets this object's four signed halfwords from A and B: the smaller of each pair at 0x0 and
// 0x4, the larger at 0x2 and 0x6. The class, method, member and parameter names are invented;
// the offsets and the bytes are the binary's.

class UnkType_10d281c0
{
public:
    void Unk_10d281c0(const UnkType_10d281c0& A, const UnkType_10d281c0& B);

    short unk_0;
    short unk_2;
    short unk_4;
    short unk_6;
};

// UnkType_10d281c0::Unk_10d281c0
void UnkType_10d281c0::Unk_10d281c0(const UnkType_10d281c0& A, const UnkType_10d281c0& B)
{
    unk_0 = A.unk_0 < B.unk_0 ? A.unk_0 : B.unk_0;
    unk_2 = A.unk_2 > B.unk_2 ? A.unk_2 : B.unk_2;
    unk_4 = A.unk_4 < B.unk_4 ? A.unk_4 : B.unk_4;
    unk_6 = A.unk_6 > B.unk_6 ? A.unk_6 : B.unk_6;
}
