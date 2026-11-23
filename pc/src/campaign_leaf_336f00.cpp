// campaign_leaf_336f00.cpp -- one function at file offset 0x336f00, preferred VA 0x10c36f00. When
// no DirectPlay8 address is held at 0x48 it creates one and passes the GUID at 0x60 to its
// virtual slot 13; then it passes First, a cleared local and the word at 0x70 to the method at
// 0x10c36c30 and, on success, the local and two zeros to the method at 0x10c36cb0, returning the
// first failing result or the last one. The class, method, member, slot, local and parameter
// names are invented; the GUIDs are identified by their values, the import by the retail import
// table, and the offsets and the bytes are the binary's.

#include "campaign_global_1115bd20.h"
#include "campaign_global_1115bd30.h"
#include "campaign_import_CoCreateInstance.h"

class IDirectPlay8Address
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual HRESULT __stdcall VirtualSlot13(const GUID* Id);
};

class UnkType_10c36f00
{
public:
    HRESULT Unk_10c36c30(int First, int* Out, int Value);
    HRESULT Unk_10c36cb0(int Value, int Second, int Third);
    HRESULT Unk_10c36f00(int First, int Second, int Third);

    unsigned char unk_0[0x48];
    IDirectPlay8Address* unk_48;
    unsigned char unk_4c[0x14];
    GUID unk_60;
    int unk_70;
};

// UnkType_10c36f00::Unk_10c36f00
HRESULT UnkType_10c36f00::Unk_10c36f00(int First, int Second, int Third)
{
    HRESULT Result;
    int Value;

    if ( unk_48 == 0 )
    {
        Result = CoCreateInstance(CLSID_DirectPlay8Address, 0, CLSCTX_INPROC_SERVER,
            IID_IDirectPlay8Address, (void**)&unk_48);
        if ( FAILED(Result) )
        {
            return Result;
        }
        Result = unk_48->VirtualSlot13(&unk_60);
        if ( FAILED(Result) )
        {
            return Result;
        }
    }
    Value = 0;
    Result = Unk_10c36c30(First, &Value, unk_70);
    if ( FAILED(Result) )
    {
        return Result;
    }
    return Unk_10c36cb0(Value, 0, 0);
}
