// campaign_leaf_11c1e0.cpp -- method at VA 0x10a1c1e0: converts an angle in radians to 65536ths of
// a turn and returns the entry of the 16384-float table at 0x8c for it (a table sine). The class,
// member, method and parameter names are invented; the offset and the constants are the binary's.

#define UNK_PI_10a1c1e0 3.1415926535897932

class UnkType_10a1c1e0
{
public:
    float Unk_10a1c1e0(float Angle);

private:
    char unk_0[0x8c];
    float unk_8c[0x4000];
};

// UnkType_10a1c1e0::Unk_10a1c1e0
float UnkType_10a1c1e0::Unk_10a1c1e0(float Angle)
{
    return unk_8c[( (int)( Angle * 65536.0f / ( 2.0 * UNK_PI_10a1c1e0 ) ) >> 2 ) & 0x3fff];
}
