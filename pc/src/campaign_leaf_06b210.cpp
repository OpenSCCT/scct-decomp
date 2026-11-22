// campaign_leaf_06b210.cpp -- one function at file offset 0x6b210, preferred VA 0x1096b210. It sets
// the four bytes that its pointer argument points to to zero. The class and method names are
// invented; the offset and the bytes are the binary's.

class UnkType_1096b210
{
public:
    void ClearFourBytes(unsigned char *Out);
};

// UnkType_1096b210::ClearFourBytes
void UnkType_1096b210::ClearFourBytes(unsigned char *Out)
{
    Out[0] = 0;
    Out[1] = 0;
    Out[2] = 0;
    Out[3] = 0;
}
