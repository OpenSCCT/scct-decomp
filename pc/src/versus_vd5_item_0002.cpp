// Work item w3 0002: Versus RVA 0x8bd0.
// FFileManagerGeneric::Copy (UE2 FFileManagerGeneric.h) with SCCT's .uz2
// compress/decompress modes (zlib compress/uncompress).

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned long uLong;

extern "C" int __cdecl compress(BYTE *dest, uLong *destLen, const BYTE *source, uLong sourceLen);
extern "C" int __cdecl uncompress(BYTE *dest, uLong *destLen, const BYTE *source, uLong sourceLen);

template <class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }

extern const TCHAR Text_Empty[];        // L""
extern const TCHAR COMPRESSED_EXTENSION[]; // L".uz2"

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class FString : public FArray
{
public:
    FString(const TCHAR *In);
    ~FString();
    FString &operator=(const FString &Other);
    FString operator+(const TCHAR *Str) const;
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : Text_Empty; }
};

class FOutputDevice;
extern FOutputDevice *GNull;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void Vtbl08();
    virtual void Vtbl0C();
    virtual void Vtbl10();
    virtual void Vtbl14();
    virtual void Vtbl18();
    virtual void Vtbl1C();
    virtual void Vtbl20();
    virtual void Vtbl24();
    virtual INT Tell();
    virtual INT TotalSize();
    virtual UBOOL AtEnd();
    virtual void Vtbl34();
    virtual void Vtbl38();
    virtual void Vtbl3C();
    virtual void Vtbl40();
    virtual void Vtbl44();
    virtual void Vtbl48();
    virtual void Vtbl4C();
    virtual UBOOL Close();

    UBOOL IsError() { return ArIsError; }

    INT ArPad[10];
    UBOOL ArIsError; // 0x2c
};

class FCopyProgress
{
public:
    virtual UBOOL Poll(FLOAT Fraction) = 0;
};

enum { FILEWRITE_NoReplaceExisting = 2, FILEWRITE_EvenIfReadOnly = 4 };
enum { FILECOPY_Normal = 0, FILECOPY_Compress = 1, FILECOPY_Decompress = 2 };
enum
{
    COPY_OK = 0,
    COPY_MiscFail = 1,
    COPY_ReadFail = 2,
    COPY_WriteFail = 3,
    COPY_CompFail = 4,
    COPY_DecompFail = 5,
    COPY_Canceled = 6,
};

class FFileManagerGeneric
{
public:
    virtual void Vtbl00();
    virtual void Vtbl04();
    virtual FArchive *CreateFileReader(const TCHAR *Filename, DWORD ReadFlags, FOutputDevice *Error, INT Unknown);
    virtual FArchive *CreateFileWriter(const TCHAR *Filename, DWORD WriteFlags, FOutputDevice *Error, INT Unknown);
    virtual INT FileSize(const TCHAR *Filename);
    virtual UBOOL Delete(const TCHAR *Filename, UBOOL RequireExists, UBOOL EvenReadOnly);
    virtual DWORD Copy(const TCHAR *InDestFile, const TCHAR *InSrcFile, UBOOL ReplaceExisting, UBOOL EvenIfReadOnly, UBOOL Attributes, DWORD Compress, FCopyProgress *Progress);
};

// 0x8bd0
DWORD FFileManagerGeneric::Copy(const TCHAR *InDestFile, const TCHAR *InSrcFile, UBOOL ReplaceExisting, UBOOL EvenIfReadOnly, UBOOL Attributes, DWORD Compress, FCopyProgress *Progress)
{
    if (Progress && !Progress->Poll(0.0f))
        return COPY_Canceled;
    DWORD Result = COPY_OK;
    FString SrcFile = InSrcFile;
    FString DestFile = InDestFile;
    switch (Compress)
    {
    case FILECOPY_Compress:
        DestFile = DestFile + COMPRESSED_EXTENSION;
        break;
    case FILECOPY_Decompress:
        SrcFile = SrcFile + COMPRESSED_EXTENSION;
        break;
    }
    FArchive *Src = CreateFileReader(*SrcFile, 0, GNull, 0);
    if (!Src)
        Result = COPY_ReadFail;
    else
    {
        INT Size = Src->TotalSize();
        FArchive *Dest = CreateFileWriter(*DestFile, (ReplaceExisting ? 0 : FILEWRITE_NoReplaceExisting) | (EvenIfReadOnly ? FILEWRITE_EvenIfReadOnly : 0), GNull, 0);
        if (!Dest)
            Result = COPY_WriteFail;
        else
        {
            INT Percent = 0, NewPercent = 0;
            BYTE Buffer[0x8000];
            BYTE CompBuffer[0x8148];
            switch (Compress)
            {
            case FILECOPY_Normal:
                for (INT Total = 0; Total < Size; Total += sizeof(Buffer))
                {
                    INT Count = Min(Size - Total, (INT)sizeof(Buffer));
                    Src->Serialize(Buffer, Count);
                    if (Src->IsError())
                    {
                        Result = COPY_ReadFail;
                        break;
                    }
                    Dest->Serialize(Buffer, Count);
                    if (Dest->IsError())
                    {
                        Result = COPY_WriteFail;
                        break;
                    }
                    NewPercent = Total * 100 / Size;
                    if (Progress && Percent != NewPercent && !Progress->Poll(NewPercent * 0.01f))
                    {
                        Result = COPY_Canceled;
                        break;
                    }
                    Percent = NewPercent;
                }
                break;
            case FILECOPY_Compress:
                for (INT Total = 0; Total < Size; Total += sizeof(Buffer))
                {
                    INT Count = Min(Size - Total, (INT)sizeof(Buffer));
                    Src->Serialize(Buffer, Count);
                    if (Src->IsError())
                    {
                        Result = COPY_ReadFail;
                        break;
                    }
                    uLong CompSize = sizeof(CompBuffer);
                    if (compress(CompBuffer, &CompSize, Buffer, Count) != 0)
                    {
                        Result = COPY_CompFail;
                        break;
                    }
                    Dest->Serialize(&CompSize, sizeof(CompSize));
                    Dest->Serialize(&Count, sizeof(Count));
                    Dest->Serialize(CompBuffer, CompSize);
                    if (Dest->IsError())
                    {
                        Result = COPY_WriteFail;
                        break;
                    }
                    NewPercent = Total * 100 / Size;
                    if (Progress && Percent != NewPercent && !Progress->Poll(NewPercent * 0.01f))
                    {
                        Result = COPY_Canceled;
                        break;
                    }
                    Percent = NewPercent;
                }
                break;
            case FILECOPY_Decompress:
                while (!Src->AtEnd())
                {
                    uLong CompSize, UncompSize;
                    Src->Serialize(&CompSize, sizeof(CompSize));
                    Src->Serialize(&UncompSize, sizeof(UncompSize));
                    if (CompSize > sizeof(CompBuffer) || UncompSize > sizeof(Buffer))
                    {
                        Result = COPY_DecompFail;
                        break;
                    }
                    Src->Serialize(CompBuffer, CompSize);
                    if (Src->IsError())
                    {
                        Result = COPY_ReadFail;
                        break;
                    }
                    if (uncompress(Buffer, &UncompSize, CompBuffer, CompSize) != 0)
                    {
                        Result = COPY_DecompFail;
                        break;
                    }
                    Dest->Serialize(Buffer, UncompSize);
                    if (Dest->IsError())
                    {
                        Result = COPY_WriteFail;
                        break;
                    }
                    NewPercent = Src->Tell() * 100 / Size;
                    if (Progress && Percent != NewPercent && !Progress->Poll(NewPercent * 0.01f))
                    {
                        Result = COPY_Canceled;
                        break;
                    }
                    Percent = NewPercent;
                }
                break;
            }
            if (Result == COPY_OK)
                if (!Dest->Close())
                    Result = COPY_WriteFail;
            delete Dest;
            if (Result != COPY_OK)
                Delete(*DestFile, 0, 0);
        }
        if (Result == COPY_OK)
            if (!Src->Close())
                Result = COPY_ReadFail;
        delete Src;
    }
    if (Progress && Result == COPY_OK && !Progress->Poll(1.0f))
        Result = COPY_Canceled;
    return Result;
}
