// campaign_leaf_1a3fc0.cpp -- returns 1 when the 16-bit character argument is an ASCII letter or
// digit, otherwise 0. File offset 0x1a3fc0, VA 0x10aa3fc0. The class and method names are invented;
// the offsets are the binary's. The character type is a guess.

class UnkType_10aa3fc0
{
public:
    static int UnkMethod_10aa3fc0(unsigned short c);
};

// UnkType_10aa3fc0::UnkMethod_10aa3fc0
int UnkType_10aa3fc0::UnkMethod_10aa3fc0(unsigned short c)
{
    if (c >= 'a' && c <= 'z')
        return 1;
    if (c >= 'A' && c <= 'Z')
        return 1;
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}
