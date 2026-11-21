// Work item 0077 (LTCG retry): appSaveStringToFile (Versus RVA 0x12cf0), UnMisc.cpp.
// Retail built this unit with /GL and linked with /LTCG: String arrives in EDI,
// FileManager in ECX, Filename on the stack.

typedef unsigned short TCHAR;
typedef char ANSICHAR;
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short UNICHAR;
#define UNICODE_BOM 0xfeff

class FOutputDevice;
extern FOutputDevice *GNull;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
};

class FFileManager
{
public:
    virtual ~FFileManager();
    virtual void Init(UBOOL Startup);
    virtual FArchive *CreateFileReader(const TCHAR *Filename, DWORD ReadFlags = 0, FOutputDevice *Error = GNull);
    virtual FArchive *CreateFileWriter(const TCHAR *Filename, DWORD WriteFlags = 0, FOutputDevice *Error = GNull, INT MaxFileSize = 0);
};

// Retail keeps these literals in writable data.
extern const TCHAR Text_Empty[];          // L""
extern const TCHAR Text_FArrayCstor[];    // L"Farray::protectedcstor"

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray(INT InNum, INT ElementSize)
        : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (!ArrayMax)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, Text_FArrayCstor);
    }
    INT Num() const { return ArrayNum; }
    void Remove(INT Index, INT Count, INT ElementSize);
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayMax = ArrayNum = 0;
    }
};

template <class T> class TArray : public FArray
{
public:
    TArray(INT InNum) : FArray(InNum, sizeof(T)) {}
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
};


template <class T> __declspec(noinline) TArray<T>::~TArray()
{
    Remove(0, ArrayNum, sizeof(T));
}


class FString : protected TArray<TCHAR>
{
public:
    INT Len() const { return Num() ? Num() - 1 : 0; }
    const TCHAR *operator*() const { return Num() ? &(*this)(0) : Text_Empty; }
};

inline ANSICHAR ToAnsi(TCHAR In) { return (_WORD)In < 0x100 ? In : 0x7f; }
inline TCHAR FromAnsi(ANSICHAR In) { return (BYTE)In; }

// Neutral name: a global flag that forces the byte-order-marked UTF-16 save path.
extern UBOOL GForceUnicodeSave;

UBOOL appSaveStringToFile(const FString &String, const TCHAR *Filename, FFileManager *FileManager)
{
    if (!String.Len())
        return 0;
    FArchive *Ar = FileManager->CreateFileWriter(Filename);
    if (!Ar)
        return 0;
    UBOOL SaveAsUnicode = 0;
    if (GForceUnicodeSave)
    {
        UNICHAR BOM = UNICODE_BOM;
        Ar->Serialize(&BOM, sizeof(BOM));
        SaveAsUnicode = 1;
    }
    else
    {
        for (INT i = 0; i < String.Len(); i++)
        {
            if ((*String)[i] != FromAnsi(ToAnsi((*String)[i])))
            {
                UNICHAR BOM = UNICODE_BOM;
                Ar->Serialize(&BOM, sizeof(BOM));
                SaveAsUnicode = 1;
                break;
            }
        }
    }
    if (!SaveAsUnicode)
    {
        TArray<ANSICHAR> AnsiBuffer(String.Len());
        for (INT i = 0; i < String.Len(); i++)
            AnsiBuffer(i) = ToAnsi((*String)[i]);
        Ar->Serialize(&AnsiBuffer(0), String.Len());
    }
    else
    {
        Ar->Serialize((void *)*String, String.Len() * sizeof(TCHAR));
    }
    delete Ar;
    return 1;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_12cf0(const FString *S, const TCHAR *F, FFileManager *M)
{
    Escape(&GMalloc); Escape(&GForceUnicodeSave); Escape(&GNull);
    Escape((void *)appSaveStringToFile(*S, F, M));
}
