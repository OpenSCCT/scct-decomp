// campaign_leaf_11c170.cpp -- multiplies the six floats of this by the float argument, copies this
// to the object at the first argument and returns that object. File offset 0x11c170, VA 0x10a1c170.
// The class and method names are invented; the offsets are the binary's.

class UnkType_10a1c170
{
public:
    UnkType_10a1c170 *UnkMethod_10a1c170(UnkType_10a1c170 *Out, float Scale);

private:
    float unk_00;
    float unk_04;
    float unk_08;
    float unk_0c;
    float unk_10;
    float unk_14;
};

UnkType_10a1c170 *UnkType_10a1c170::UnkMethod_10a1c170(UnkType_10a1c170 *Out, float Scale)
{
    unk_00 = unk_00 * Scale;
    unk_04 = unk_04 * Scale;
    unk_08 = unk_08 * Scale;
    unk_0c = unk_0c * Scale;
    unk_10 = unk_10 * Scale;
    unk_14 = unk_14 * Scale;
    *Out = *this;
    return Out;
}
