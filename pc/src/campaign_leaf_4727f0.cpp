// campaign_leaf_4727f0.cpp -- thiscall method at VA 0x10d727f0. It walks its list of entries
// (head at 0x138, tail at 0x13c, count at 0x140). Each entry whose object has a zero word at 0x70
// and for which 0x11043bf0 returns zero with the word at 0xd8 is unlinked and released through
// the stdcall function at 0x1103c870, after which its object goes through its method at
// 0x10d723d0 and is released the same way. The class, method and member names are invented.

void __stdcall Unk_1103c870(void* Block);

class UnkType_10d727f0_Object
{
public:
    void Unk_10d723d0();

    unsigned char unk_0[0x70];
    int unk_70;
};

struct UnkType_10d727f0_Entry
{
    UnkType_10d727f0_Entry* unk_0;
    UnkType_10d727f0_Entry* unk_4;
    UnkType_10d727f0_Object* unk_8;
};

struct UnkType_10d727f0_Iterator
{
    UnkType_10d727f0_Object* operator*()
    {
        return unk_0->unk_8;
    }

    UnkType_10d727f0_Iterator operator++(int)
    {
        UnkType_10d727f0_Iterator Old = *this;
        unk_0 = unk_0->unk_0;
        return Old;
    }

    UnkType_10d727f0_Entry* unk_0;
};

int Unk_11043bf0(UnkType_10d727f0_Object* Object, int Value);

class UnkType_10d727f0
{
public:
    void Unk_10d727f0();

private:
    unsigned char unk_0[0xd8];
    int unk_d8;
    unsigned char unk_dc[0x5c];
    UnkType_10d727f0_Entry* unk_138;
    UnkType_10d727f0_Entry* unk_13c;
    int unk_140;
};

// UnkType_10d727f0::Unk_10d727f0
void UnkType_10d727f0::Unk_10d727f0()
{
    UnkType_10d727f0_Iterator Next;

    Next.unk_0 = unk_138;
    while ( Next.unk_0 )
    {
        UnkType_10d727f0_Entry* Entry = Next.unk_0;
        UnkType_10d727f0_Object* Object = *Next++;

        if ( Object->unk_70 == 0 && Unk_11043bf0(Object, unk_d8) == 0 )
        {
            if ( Entry == unk_138 )
            {
                unk_138 = Entry->unk_0;
            }
            else
            {
                Entry->unk_4->unk_0 = Entry->unk_0;
            }
            if ( Entry == unk_13c )
            {
                unk_13c = Entry->unk_4;
            }
            else
            {
                Entry->unk_0->unk_4 = Entry->unk_4;
            }
            Unk_1103c870(Entry);
            unk_140--;
            Object->Unk_10d723d0();
            Unk_1103c870(Object);
        }
    }
}
