// variant 2 of 14bcc0: one compound condition
class UnkType_10a4bcc0
{
public:
    int UnkMethod_10a4bcc0(UnkType_10a4bcc0 *Other);

private:
    int unk_00;
    float unk_04;
    float unk_08;
    float unk_0c;
    unsigned char unk_10[0x30];
    float unk_40;
    float unk_44;
};

int UnkType_10a4bcc0::UnkMethod_10a4bcc0(UnkType_10a4bcc0 *Other)
{
    if ( unk_00 == Other->unk_00 && unk_04 == Other->unk_04 && unk_08 == Other->unk_08
         && unk_0c == Other->unk_0c && unk_40 == Other->unk_40 && unk_44 == Other->unk_44 )
    {
        return 1;
    }
    return 0;
}
