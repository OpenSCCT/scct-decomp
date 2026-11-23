// campaign_leaf_0fe4b0.cpp -- method at VA 0x109fe4b0 assigning one dynamic array of 0x78-byte
// records (data pointer at 0x00, count at 0x04) to another: unless both are the same object, calls
// the method at VA 0x109fd030 with the other's count, then appends a copy of every record of the
// other made by the copy constructor at VA 0x109eaa00, each time raising the count and calling the
// method at VA 0x10ccb3c0 with the element size; returns the array. The class, member and method
// names are invented; the offsets and the addresses are the binary's.

class UnkType_109fe4b0_Record
{
public:
    UnkType_109fe4b0_Record(const UnkType_109fe4b0_Record& Other);

private:
    unsigned char unk_00[0x78];
};

class UnkType_109fe4b0
{
public:
    UnkType_109fe4b0& Unk_109fe4b0(const UnkType_109fe4b0& Other);
    void Unk_109fd030(int Slack);
    void Unk_10ccb3c0(int ElementSize);

    int Add()
    {
        int Index = unk_04;
        unk_04++;
        Unk_10ccb3c0(sizeof(UnkType_109fe4b0_Record));
        return Index;
    }

    UnkType_109fe4b0_Record* unk_00;
    int unk_04;
};

inline void* operator new(unsigned int, UnkType_109fe4b0& Array)
{
    int Index = Array.Add();
    return &Array.unk_00[Index];
}

// UnkType_109fe4b0::Unk_109fe4b0
UnkType_109fe4b0& UnkType_109fe4b0::Unk_109fe4b0(const UnkType_109fe4b0& Other)
{
    if ( this != &Other )
    {
        Unk_109fd030(Other.unk_04);
        for ( int i = 0; i < Other.unk_04; i++ )
        {
            new(*this) UnkType_109fe4b0_Record(Other.unk_00[i]);
        }
    }
    return *this;
}
