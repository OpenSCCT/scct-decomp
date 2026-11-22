// campaign_leaf_158a50.cpp -- copies the vector at the argument index of the array at offset 0x50
// of this to the second argument. File offset 0x158a50, VA 0x10a58a50. The class and method names
// are invented; the offsets are the binary's, and the vector type is a guess.

class UnkVec_10a58a50
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10a58a50
{
public:
    void UnkMethod_10a58a50(int Index, UnkVec_10a58a50 *Out);

private:
    unsigned char unk_00[0x50];     // not read by this function
    UnkVec_10a58a50 *unk_50;        // guess: array of vectors
};

// UnkType_10a58a50::UnkMethod_10a58a50
void UnkType_10a58a50::UnkMethod_10a58a50(int Index, UnkVec_10a58a50 *Out)
{
    *Out = unk_50[Index];
}
