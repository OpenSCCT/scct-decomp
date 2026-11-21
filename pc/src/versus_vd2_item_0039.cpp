// Work item 0039: FArchiveFileWriter (UE2 FFileManagerWindows.h) methods.
// Layout: vtable 0x00, FArchive state 0x04..0x3c, Handle 0x40, Error 0x44,
// Pos 0x48, BufferCount 0x4c, Buffer[4096] 0x50. Flush is vtable slot 0x4c.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef void* HANDLE;

void appMemcpy(void* Dest, const void* Src, INT Count);

class FOutputDevice;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, INT Length);
    virtual void SerializeBits(void* V, INT LengthBits);
    virtual void SerializeInt(DWORD& Value, DWORD Max);
    virtual void Preload(void* Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive& operator<<(class FName& N);
    virtual FArchive& operator<<(class UObject*& Res);
    virtual INT MapName(class FName* Name);
    virtual INT MapObject(class UObject* Object);
    virtual INT Tell();
    virtual INT TotalSize();
    virtual UBOOL AtEnd();
    virtual void Seek(INT InPos);
    virtual void AttachLazyLoader(class FLazyLoader* LazyLoader);
    virtual void DetachLazyLoader(class FLazyLoader* LazyLoader);
    virtual void Precache(INT HintCount);
    virtual void Unused1();
    virtual UBOOL Close();
    virtual void Flush();

    INT ArData[15]; // 0x04..0x3c: ArVer, ArNetVer, ArLicenseeVer, flags
};

class FArchiveFileWriter : public FArchive
{
public:
    void Serialize(void* V, INT Length);

    HANDLE         Handle;      // 0x40
    FOutputDevice* Error;       // 0x44
    INT            Pos;         // 0x48
    INT            BufferCount; // 0x4c
    BYTE           Buffer[4096];// 0x50
};

void FArchiveFileWriter::Serialize(void* V, INT Length)
{
    Pos += Length;
    INT Copy;
    while (Length > (Copy = sizeof(Buffer) - BufferCount))
    {
        appMemcpy(Buffer + BufferCount, V, Copy);
        BufferCount += Copy;
        Length -= Copy;
        V = (BYTE*)V + Copy;
        Flush();
    }
    if (Length)
    {
        appMemcpy(Buffer + BufferCount, V, Length);
        BufferCount += Length;
    }
}
