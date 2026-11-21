// Work item 0040: a compressed-buffer reader archive (RVA 0x9be0-0x9dcf).
// Base class is FArchive (ArVer 0xaf = 175, ArNetVer 2000). The derived
// class name is not recovered: FArchiveCompressedReader_9be0 is neutral.
// Retail compiled this unit with /GL and linked with /LTCG: the constructor
// takes the object on the stack and the inner archive in ECX; the destructor
// takes the object on the stack (ret 4).
// It owns an inner archive, reads two sizes from it, reads the compressed
// payload and inflates it with zlib's uncompress (FUN_10b21b94).

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

class FMalloc
{
public:
	virtual void* Malloc( DWORD Count, const TCHAR* Tag );
	virtual void* Realloc( void* Original, DWORD Count, const TCHAR* Tag );
	virtual void Free( void* Original );
};
extern FMalloc* GMalloc;

extern "C" int uncompress( BYTE* Dest, DWORD* DestLen, const BYTE* Source, DWORD SourceLen );

// Allocation tag shared by both buffers (retail 0x10c109d8).
extern const TCHAR FArchiveCompressedReader_Tag[];

class FArchive
{
public:
	virtual ~FArchive() {}
	virtual void Serialize( void* V, INT Length );
	virtual void S08();
	virtual void S0c();
	virtual void S10();
	virtual void S14();
	virtual void S18();
	virtual void S1c();
	virtual void S20();
	virtual void S24();
	virtual void S28();
	virtual void S2c();
	virtual void S30();
	virtual void S34();
	virtual void S38();
	virtual void S3c();
	virtual void S40();
	virtual void S44();
	virtual void S48();
	virtual void S4c();
	virtual UBOOL Close();

	FArchive()
	:	ArVer( 175 )
	,	ArNetVer( 2000 )
	,	ArLicenseeVer( 0 )
	,	ArIsLoading( 0 )
	,	ArIsSaving( 0 )
	,	ArIsTrans( 0 )
	,	ArIsPersistent( 0 )
	,	ArForEdit( 1 )
	,	ArForClient( 1 )
	,	ArForServer( 1 )
	,	ArIsError( 0 )
	,	ArIsCriticalError( 0 )
	,	Unknown34( 3 )
	,	Unknown38( 0 )
	,	Unknown3c( -1 )
	{}

	INT ArVer;
	INT ArNetVer;
	INT ArLicenseeVer;
	UBOOL ArIsLoading;
	UBOOL ArIsSaving;
	UBOOL ArIsTrans;
	UBOOL ArIsPersistent;
	UBOOL ArForEdit;
	UBOOL ArForClient;
	UBOOL ArForServer;
	UBOOL ArIsError;
	UBOOL ArIsCriticalError;
	INT Unknown34;
	INT Unknown38;
	INT Unknown3c;
};

class FArchiveCompressedReader_9be0 : public FArchive
{
public:
	FArchiveCompressedReader_9be0( FArchive* InInner );
	~FArchiveCompressedReader_9be0();
	void CloseInner()
	{
		if( Inner )
		{
			Inner->Close();
			delete Inner;
			Inner = 0;
		}
	}
	UBOOL Close();

	FArchive* Inner;
	INT Pos;
	INT BufferBase;
	INT Size;
	INT Total;
	BYTE* Buffer;
	BYTE* CompressedBuffer;
};

// RVA 0x9be0
FArchiveCompressedReader_9be0::FArchiveCompressedReader_9be0( FArchive* InInner )
:	Inner( InInner )
,	Pos( 0 )
,	BufferBase( 0 )
,	Size( 0 )
{
	ArIsLoading = ArIsPersistent = 1;
	DWORD Sizes[2];
	Inner->Serialize( Sizes, sizeof(Sizes) );
	Buffer = (BYTE*)GMalloc->Malloc( Sizes[0], FArchiveCompressedReader_Tag );
	CompressedBuffer = (BYTE*)GMalloc->Malloc( Sizes[1], FArchiveCompressedReader_Tag );
	Inner->Serialize( CompressedBuffer, Sizes[1] );
	DWORD DestLen = Sizes[0];
	uncompress( Buffer, &DestLen, CompressedBuffer, Sizes[1] );
	Size = Sizes[0];
	Total = Sizes[0];
	BufferBase = 0;
	GMalloc->Free( CompressedBuffer );
}

// RVA 0x9d00
FArchiveCompressedReader_9be0::~FArchiveCompressedReader_9be0()
{
	CloseInner();
	GMalloc->Free( Buffer );
	Pos = BufferBase = Size = 0;
}

// RVA 0x9da0
UBOOL FArchiveCompressedReader_9be0::Close()
{
	CloseInner();
	return !ArIsError;
}

// Scaffolding for the link, not part of the unit.
inline void* operator new( unsigned int, void* Mem ) { return Mem; }
void Escape( void* );
void Driver_9be0( void* Mem, FArchive* Inner )
{
	Escape( &GMalloc );
	new( Mem ) FArchiveCompressedReader_9be0( Inner );
}
void Driver_9d00( FArchiveCompressedReader_9be0* A, FArchiveCompressedReader_9be0* B )
{
	Escape( &GMalloc );
	A->FArchiveCompressedReader_9be0::~FArchiveCompressedReader_9be0();
	B->FArchiveCompressedReader_9be0::~FArchiveCompressedReader_9be0();
}
