// campaign_leaf_207f70.cpp -- thiscall method at VA 0x10b07f70 taking a context word and a
// callback. It stores them at 0x1584 and 0x1570; when both are set it calls the callback once for
// each entry of the list at 0x15a8 with the context, the entry's first word, the address of its
// buffer at 0x08 and its word at 0x2c. The class, method and member names are invented; the list
// is the compiler's library.

#include <list>

typedef void (*UnkType_10b07f70_Callback)(int Context, int Id, char* Name, int Value);

struct UnkType_10b07f70_Entry
{
    int unk_00;
    char unk_04[4];
    char unk_08[0x24];
    int unk_2c;
};

class UnkType_10b07f70
{
public:
    void Unk_10b07f70(int Context, UnkType_10b07f70_Callback Callback);

private:
    char unk_0000[0x1570];
    UnkType_10b07f70_Callback unk_1570;
    char unk_1574[0x10];
    int unk_1584;
    char unk_1588[0x20];
    std::list<UnkType_10b07f70_Entry> unk_15a8;
};

// UnkType_10b07f70::Unk_10b07f70
void UnkType_10b07f70::Unk_10b07f70(int Context, UnkType_10b07f70_Callback Callback)
{
    std::list<UnkType_10b07f70_Entry>::iterator It;
    std::list<UnkType_10b07f70_Entry>::iterator End;

    unk_1584 = Context;
    unk_1570 = Callback;
    if ( Callback && Context )
    {
        End = unk_15a8.end();
        for ( It = unk_15a8.begin(); It != End; ++It )
        {
            unk_1570(unk_1584, It->unk_00, It->unk_08, It->unk_2c);
        }
    }
}
