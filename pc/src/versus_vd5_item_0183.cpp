// Work item 0183: Versus RVA 0xe07e0, UActorChannel::CleanUp (UE2 UnChan.cpp shape).
// LTCG unit: callees take link-time conventions (0xdfb30 node in EDX,
// ExitProperties Class in EAX / Data in EDI, RemoveItem array in EDI,
// DestroyActor level on the stack). Check with try_ltcg.py.
// Field offsets come from the retail code; UE2 names where the shape agrees.
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum ENetRole { ROLE_None = 0, ROLE_Authority = 4 };

class UClass;
class UProperty
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31();
    virtual void V32(); virtual void V33(); virtual void V34(); virtual void V35();
    virtual void V36();
    virtual void DestroyValue(void *Dest);  // +0x94
    char Pad04[0x38];
    INT Offset;                             // +0x3c
    char Pad40[0x08];
    UProperty *ConstructorLinkNext;         // +0x48
};
class UClass
{
public:
    char Pad00[0x64];
    UProperty *ConstructorLink;             // +0x64
};

class UObject
{
public:
    static void ExitProperties(BYTE *Data, UClass *Class);
};

// RVA 0x179a0 (published in versus_vd2_item_0099.cpp); defined here only so
// the link gives it its retail register convention.
__declspec(noinline) void UObject::ExitProperties(BYTE *Data, UClass *Class)
{
    for (UProperty *P = Class->ConstructorLink; P; P = P->ConstructorLinkNext)
        P->DestroyValue(Data + P->Offset);
}

class FArray
{
public:
    void Remove(INT Index, INT Count, INT ElementSize);
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};
template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
    INT RemoveItem(const T &Item);
};
// RVA 0x10a0bd60 (array in EDI, item by reference on the stack).
template<class T> __declspec(noinline) INT TArray<T>::RemoveItem(const T &Item)
{
    INT OriginalNum = ArrayNum;
    for (INT Index = 0; Index < ArrayNum; Index++)
        if ((*this)(Index) == Item)
            FArray::Remove(Index--, 1, sizeof(T));
    return OriginalNum - ArrayNum;
}

class AActor;
class ULevel;
// RVA 0x21a790: ULevel::DestroyActor; its link-time convention takes the level
// on the stack with the arguments (declared __stdcall since the body is elsewhere).
UBOOL __stdcall ULevel_DestroyActor(ULevel *Level, AActor *Actor, UBOOL bNetForce);

class AActor
{
public:
    char Pad00[0x1a4];
    ULevel *XLevel;                         // +0x1a4
    char Pad1a8[0x2dd - 0x1a8];
    BYTE RemoteRole;                        // +0x2dd
    BYTE Role;                              // +0x2de
    char Pad2df[0x2ec - 0x2df];
    DWORD bNetTemporary : 1;                // +0x2ec bit 0
    DWORD Bits1 : 7;
    DWORD bTearOff : 1;                     // +0x2ec bit 8
};

class UNetConnection;
class UNetDriver
{
public:
    char Pad00[0x38];
    UNetConnection *ServerConnection;       // +0x38
};
class UNetConnection
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08();
    virtual void Refresh();                 // slot 9 (+0x24)
    INT Index;                              // +0x04
    char Pad08[0x14];
    DWORD Flags;                            // +0x1c
    char Pad20[0x48];
    UNetDriver *Driver;                     // +0x68
    char Pad6c[0x2708 - 0x6c];
    TArray<AActor *> SentTemporaries;       // +0x2708
};

// Neutral name: the object at +0x60 whose +8 is the actor class.
struct FUnnamedClassCache_e07e0
{
    INT Pad00[2];
    UClass *Class;                          // +0x08
};

class UActorChannel
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22();
    virtual void SetClosingFlag();          // +0x5c
    INT Index;                              // +0x04
    char Pad08[0x14];
    DWORD Flags;                            // +0x1c
    char Pad20[0x08];
    UNetConnection *Connection;             // +0x28
    char Pad2c[0x54 - 0x2c];
    BYTE Pad54[2];
    BYTE Bits56 : 4;
    BYTE OpenAcked : 1;                     // +0x56 bit 4
    BYTE Pad57;
    INT Pad58;
    AActor *Actor;                          // +0x5c
    FUnnamedClassCache_e07e0 *ClassCache;   // +0x60
    char Pad64[0x8c - 0x64];
    TArray<BYTE> Recent;                    // +0x8c

    void CleanUp();
    void ChannelCleanUp();                  // RVA 0xdfc20, UChannel::CleanUp
};

// RVA 0xdfb30 (channel in EDX); body as recovered for work item 0177.
__declspec(noinline) UBOOL RelinkNode_dfb30(UActorChannel *Node)
{
    UNetConnection *Link = Node->Connection;
    if (Link && (Link->Flags & 2))
    {
        Node->Flags &= ~0x800000;
        if (Link->Index != -1 && !(Link->Flags & 0x800000))
        {
            Link->Flags = (Link->Flags & 0x7f7fffff) | 0x800000;
            Link->Refresh();
            return 1;
        }
        Node->Flags |= 0x800000;
    }
    return 0;
}

// RVA 0xe07e0
void UActorChannel::CleanUp()
{
    if (RelinkNode_dfb30(this))
        return;

    SetClosingFlag();

    // Destroy Recent properties.
    if (Recent.Num())
        UObject::ExitProperties(&Recent(0), ClassCache->Class);

    // If we're the client, destroy this actor.
    if (Connection->Driver->ServerConnection)
    {
        if (Actor)
        {
            if (Actor->bTearOff)
            {
                Actor->Role = ROLE_Authority;
                Actor->RemoteRole = ROLE_None;
            }
            else if (!Actor->bNetTemporary)
                ULevel_DestroyActor(Actor->XLevel, Actor, 1);
        }
    }
    else if (Actor && !OpenAcked)
    {
        // Resend temporary actors if nak'd.
        Connection->SentTemporaries.RemoveItem(Actor);
    }

    ChannelCleanUp();
}

// Scaffolding for the link, not part of the unit.
// Retail CleanUp is reached through the vtable, so its address escapes.
void Escape(void *);
void Driver_e07e0(UActorChannel *C)
{
    void (UActorChannel::*Fn)() = &UActorChannel::CleanUp;
    Escape(*(void **)&Fn);
    C->CleanUp();
}
