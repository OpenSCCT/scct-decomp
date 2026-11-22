// campaign_leaf_6282e0.cpp -- stdcall function at VA 0x10f282e0: when the object is not null, passes
// the second argument to the method at VA 0x10f2be80 on it and returns true; otherwise false. All
// names are invented.

class UnkType_10f2be80
{
public:
    void Unk_10f2be80(int Value);
};

// Unk_10f282e0
bool __stdcall Unk_10f282e0(UnkType_10f2be80* Object, int Value)
{
    if ( Object )
    {
        Object->Unk_10f2be80(Value);
        return true;
    }
    return false;
}
