// campaign_leaf_4bd420.cpp -- free function at VA 0x10dbd420: calls the method at VA 0x10961930
// of the global object at VA 0x1131b110 with 5 and the result of the free function at
// VA 0x10d98f30. All names are invented.

int Unk_10d98f30();

class UnkType_10961930
{
public:
    void Unk_10961930(int Kind, int Value);
};

extern UnkType_10961930 GUnk_1131b110;

// Unk_10dbd420
void Unk_10dbd420()
{
    GUnk_1131b110.Unk_10961930(5, Unk_10d98f30());
}
