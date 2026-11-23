// campaign_leaf_0e93b0.cpp -- method at VA 0x109e93b0 assigning one dynamic array of 16-byte
// records (data pointer at 0x00, count at 0x04) to another: unless both are the same object, calls
// the method at VA 0x109e9330 with the other's count, then appends a copy of every record of the
// other, each time raising the count and calling the method at VA 0x10ccb3c0 with the element size;
// a record copies its 8-byte array at 0x00 through the copy constructor at VA 0x109dcd40 and the
// two words after it. Returns the array. The class, member and method names are invented; the
// offsets and the addresses are the binary's.

class UnkType_109e93b0_Array
{
public:
    UnkType_109e93b0_Array(const UnkType_109e93b0_Array& Other);

private:
    int* unk_00;
    int unk_04;
};

struct UnkType_109e93b0_Record
{
    UnkType_109e93b0_Array unk_00;
    int unk_08;
    int unk_0c;
};

class UnkType_109e93b0
{
public:
    UnkType_109e93b0& Unk_109e93b0(const UnkType_109e93b0& Other);
    void Unk_109e9330(int Slack);
    void Unk_10ccb3c0(int ElementSize);

    int Add()
    {
        int Index = unk_04;
        unk_04++;
        Unk_10ccb3c0(sizeof(UnkType_109e93b0_Record));
        return Index;
    }

    UnkType_109e93b0_Record* unk_00;
    int unk_04;
};

inline void* operator new(unsigned int, UnkType_109e93b0& Array)
{
    int Index = Array.Add();
    return &Array.unk_00[Index];
}

// UnkType_109e93b0::Unk_109e93b0
UnkType_109e93b0& UnkType_109e93b0::Unk_109e93b0(const UnkType_109e93b0& Other)
{
    if ( this != &Other )
    {
        Unk_109e9330(Other.unk_04);
        for ( int i = 0; i < Other.unk_04; i++ )
        {
            new(*this) UnkType_109e93b0_Record(Other.unk_00[i]);
        }
    }
    return *this;
}
