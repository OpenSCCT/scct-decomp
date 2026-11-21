// Work item 0041 (LTCG retry): Versus RVA 0x9ee0 and 0x9f50.
// A buffered, compressing archive writer derived from FArchive (ArVer 0xaf
// = 175, ArNetVer 2000): data is gathered into a 15 MB buffer, compressed in
// blocks and handed to an inner archive. The derived class name is not
// recovered: FArchiveCompressedWriter_9ee0 is neutral.
// Retail compiled this unit with /GL and linked with /LTCG: the constructor
// takes the object in EAX and the inner archive in ESI; the destructor takes
// the object on the stack (ret 4).

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

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
	virtual void Flush();
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

enum { BUFFER_SIZE = 0xf00000 };

class FArchiveCompressedWriter_9ee0 : public FArchive
{
public:
	FArchiveCompressedWriter_9ee0( FArchive* InInner );
	~FArchiveCompressedWriter_9ee0();
	void Serialize( void* V, INT Length );
	void Flush();
	UBOOL Close()
	{
		if( Inner )
		{
			Flush();
			ArIsError = Inner->Close() == 0;
			delete Inner;
			Inner = 0;
		}
		return !ArIsError;
	}

	FArchive* Inner;                    // 0x40
	INT TotalWritten;                   // 0x44
	INT Count;                          // 0x48
	INT Extra;                          // 0x4c
	BYTE Buffer[BUFFER_SIZE];           // 0x50
	INT BlockHeader[2];                 // 0xf00050
	BYTE Compressed[0xf00ff8];          // 0xf00058
	INT TotalUncompressed;              // 0x1e01050
	INT TotalCompressed;                // 0x1e01054
};

// RVA 0x9ee0
FArchiveCompressedWriter_9ee0::FArchiveCompressedWriter_9ee0( FArchive* InInner )
:	Inner( InInner )
,	TotalWritten( 0 )
,	Count( 0 )
,	Extra( 0 )
,	TotalUncompressed( 0 )
,	TotalCompressed( 0 )
{
	ArIsSaving = ArIsPersistent = 1;
}

// RVA 0x9f50
FArchiveCompressedWriter_9ee0::~FArchiveCompressedWriter_9ee0()
{
	Close();
}

// Scaffolding for the link, not part of the unit.
inline void* operator new( unsigned int, void* Mem ) { return Mem; }
void Driver_9ee0( void* Mem, FArchive* Inner )
{
	new( Mem ) FArchiveCompressedWriter_9ee0( Inner );
}
void Driver_9f50( FArchiveCompressedWriter_9ee0* A, FArchiveCompressedWriter_9ee0* B )
{
	A->FArchiveCompressedWriter_9ee0::~FArchiveCompressedWriter_9ee0();
	B->FArchiveCompressedWriter_9ee0::~FArchiveCompressedWriter_9ee0();
}
