// campaign_leaf_74a380.cpp -- free function at VA 0x1104a380: calls the method at VA 0x1104bc90 on
// the object returned by VA 0x1104bca0, then calls VA 0x1104f7c0. All names are invented.

class UnkType_1104bc90
{
public:
    void Unk_1104bc90();
};

UnkType_1104bc90* Unk_1104bca0();
void Unk_1104f7c0();

// Unk_1104a380
void Unk_1104a380()
{
    Unk_1104bca0()->Unk_1104bc90();
    Unk_1104f7c0();
}
