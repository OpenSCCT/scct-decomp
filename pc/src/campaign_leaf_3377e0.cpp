// campaign_leaf_3377e0.cpp -- one function at file offset 0x3377e0, preferred VA 0x10c377e0. It
// creates a DirectPlay8 peer into 0x44 and passes this object, the message handler at 0x10c37540
// and 1 to its virtual slot 3; when both succeed it stores Value at 0x70 and the GUID Id at 0x50,
// sets the byte at 0x4c and returns S_OK, otherwise the failing result. The class, method,
// member, slot and parameter names are invented; the GUIDs are identified by their values, the
// import by the retail import table, and the offsets and the bytes are the binary's.

#include "campaign_global_1115bc90.h"
#include "campaign_global_1115bce0.h"
#include "campaign_import_CoCreateInstance.h"

typedef HRESULT (__stdcall* UnkFn_10c37540)(void* Context, unsigned long Type, void* Message);

class IDirectPlay8Peer
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual HRESULT __stdcall VirtualSlot3(void* Context, UnkFn_10c37540 Handler,
        unsigned long Flags);
};

class UnkType_10c377e0
{
public:
    static HRESULT __stdcall Unk_10c37540(void* Context, unsigned long Type, void* Message);
    HRESULT Unk_10c377e0(const GUID& Id, int Value);

    unsigned char unk_0[0x44];
    IDirectPlay8Peer* unk_44;
    unsigned char unk_48[0x4];
    unsigned char unk_4c;
    GUID unk_50;
    unsigned char unk_60[0x10];
    int unk_70;
};

// UnkType_10c377e0::Unk_10c377e0
HRESULT UnkType_10c377e0::Unk_10c377e0(const GUID& Id, int Value)
{
    HRESULT Result;

    Result = CoCreateInstance(CLSID_DirectPlay8Peer, 0, CLSCTX_INPROC_SERVER,
        IID_IDirectPlay8Peer, (void**)&unk_44);
    if ( FAILED(Result) )
    {
        return Result;
    }
    Result = unk_44->VirtualSlot3(this, Unk_10c37540, 1);
    if ( FAILED(Result) )
    {
        return Result;
    }
    unk_70 = Value;
    unk_50 = Id;
    unk_4c = 1;
    return S_OK;
}
