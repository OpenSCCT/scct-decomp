// campaign_leaf_08a2e0.cpp -- one function at file offset 0x8a2e0, preferred VA 0x1098a2e0. It
// stores its byte argument in the byte at offset 0 of this object, and returns this object. The
// class and method names are invented; the offset and the bytes are the binary's.

class UnkType_1098a2e0
{
public:
    UnkType_1098a2e0 *UnkSetByte(unsigned char Value);

private:
    unsigned char unk_00;
};

// UnkType_1098a2e0::UnkSetByte
UnkType_1098a2e0 *UnkType_1098a2e0::UnkSetByte(unsigned char Value)
{
    unk_00 = Value;
    return this;
}
