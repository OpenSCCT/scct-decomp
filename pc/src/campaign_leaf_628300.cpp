// campaign_leaf_628300.cpp -- stdcall function at VA 0x10f28300: when the object is not null, passes
// the second argument to the method at VA 0x10f2be90 on it and returns true; otherwise false. All
// names are invented.

class UnkType_10f2be90
{
public:
    void Unk_10f2be90(int Value);
};

// Unk_10f28300
bool __stdcall Unk_10f28300(UnkType_10f2be90* Object, int Value)
{
    if ( Object )
    {
        Object->Unk_10f2be90(Value);
        return true;
    }
    return false;
}
