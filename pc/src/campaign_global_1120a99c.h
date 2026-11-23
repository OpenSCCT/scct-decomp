// campaign_global_1120a99c.h -- the global at VA 0x1120a99c, a stack allocator: the current top
// (aligned up before each allocation) and the end of the current chunk at VA 0x1120a9a0; its
// method at VA 0x10d01de0 starts a new chunk of at least the given size. Name and type invented from
// its uses.
#ifndef CAMPAIGN_GLOBAL_1120A99C_H
#define CAMPAIGN_GLOBAL_1120A99C_H

class UnkType_1120a99c
{
public:
    // UnkType_1120a99c::PushBytes
    unsigned char* PushBytes(int Count, int Align)
    {
        unsigned char* Result =
            (unsigned char*)(((unsigned long)unk_0 + Align - 1) & ~(unsigned long)(Align - 1));
        unk_0 = Result + Count;
        if ( unk_0 > unk_4 )
        {
            Unk_10d01de0(Count + Align);
            Result =
                (unsigned char*)(((unsigned long)unk_0 + Align - 1) & ~(unsigned long)(Align - 1));
            unk_0 = Result + Count;
        }
        return Result;
    }

    void Unk_10d01de0(int MinSize);

    unsigned char* unk_0;
    unsigned char* unk_4;
};

extern UnkType_1120a99c GUnk_1120a99c;

// operator new
inline void* operator new(unsigned int Size, UnkType_1120a99c& Mem)
{
    return Mem.PushBytes(Size, 8);
}

#endif
