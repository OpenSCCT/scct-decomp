// Work item 0214: Versus RVA 0xe8ef0-0xe9025.
// 0xe8ef0 and 0xe8f40 are UGameEngine methods (reflected vtable slots 10 and
// 51): Serialize and CancelPending, as in Unreal Engine 2.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

class UObject;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Pad04();
    virtual void Pad08();
    virtual void Pad0C();
    virtual void Pad10();
    virtual void Pad14();
    virtual FArchive& operator<<(UObject*& Res);   // 0x18
};
template<class T> inline FArchive& operator<<(FArchive& Ar, T*& Res)
{
    return Ar << *(UObject**)&Res;
}

class UObject
{
public:
    virtual void Pad00();
    virtual void Pad04();
    virtual void Pad08();
    virtual ~UObject();                            // 0x0c (deleting)
};


class UChannelBase
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0C();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1C();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2C();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3C();
    virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4C();
    virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5C();
    virtual void Close();                          // 0x60
};

class UNetConnection
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0C();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1C();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2C();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3C();
    virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4C();
    virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5C();
    virtual void V60(); virtual void V64(); virtual void V68(); virtual void V6C();
    virtual void FlushNet();                       // 0x70
    char Pad[0xef0 - 4];
    UChannelBase* Channels[1];                     // 0xef0
};

class UNetDriver
{
public:
    char Pad[0x38];
    UNetConnection* ServerConnection;              // 0x38
};

class ULevel;
class UPendingLevel : public UObject
{
public:
    char Pad[0xec - 4];
    UNetDriver* NetDriver;                         // 0xec
};

class UEngine
{
public:
    virtual void Serialize(FArchive& Ar);          // retail 0x96c50
};

class UGameEngine : public UEngine
{
public:
    char Pad[0x130 - 4];
    ULevel* GLevel;                                // 0x130
    ULevel* GEntry;                                // 0x134
    UPendingLevel* GPendingLevel;                  // 0x138
    char Pad13c[0x184 - 0x13c];
    UObject* Obj184;                               // 0x184, role unknown

    virtual void Serialize(FArchive& Ar);
    virtual void CancelPending();
};

void UGameEngine::Serialize(FArchive& Ar)
{
    UEngine::Serialize(Ar);
    Ar << GLevel << GEntry << GPendingLevel << Obj184;
}

void UGameEngine::CancelPending()
{
    if (GPendingLevel)
    {
        if (GPendingLevel->NetDriver
         && GPendingLevel->NetDriver->ServerConnection
         && GPendingLevel->NetDriver->ServerConnection->Channels[0])
        {
            GPendingLevel->NetDriver->ServerConnection->Channels[0]->Close();
            GPendingLevel->NetDriver->ServerConnection->FlushNet();
        }
        delete GPendingLevel;
        GPendingLevel = 0;
    }
}
