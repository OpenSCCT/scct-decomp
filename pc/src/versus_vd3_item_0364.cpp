// Work item 0364: Versus RVA 0xa28e0 / 0xa2960.
// Two out-of-line TArray<T> destructors compiled /GL (this on the stack,
// ret 4): element size 8 (RVA 0xa28e0) and element size 200 (RVA 0xa2960).
// Element types are unknown; neutral names are used.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class FMalloc
{
public:
	virtual void* Malloc( DWORD Count, const TCHAR* Tag ) = 0;
	virtual void* Realloc( void* Original, DWORD Count, const TCHAR* Tag ) = 0;
	virtual void Free( void* Original ) = 0;
};
extern FMalloc* GMalloc;

class FArray
{
public:
	void* Data;
	INT ArrayNum;
	INT ArrayMax;
	FArray() : Data( 0 ), ArrayNum( 0 ), ArrayMax( 0 ) {}
	~FArray()
	{
		if( Data )
		{
			GMalloc->Free( Data );
			Data = 0;
		}
		ArrayNum = 0;
	}
	void Remove( INT Index, INT Count, INT ElementSize );
};

template<class T> class TArray : public FArray
{
public:
	TArray() {}
	__declspec(noinline) ~TArray()
	{
		FArray::Remove( 0, ArrayNum, sizeof(T) );
	}
};

// Plain-data elements (no destructor), sizes 8 and 200.
struct UnnamedElement_a28e0 { INT A, B; };
struct UnnamedElement_a2960 { char Bytes[200]; };

template class TArray<UnnamedElement_a28e0>;
template class TArray<UnnamedElement_a2960>;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_a28e0(TArray<UnnamedElement_a28e0> *A) { Escape(&GMalloc); A->~TArray(); }
void Driver_a2960(TArray<UnnamedElement_a2960> *A) { Escape(&GMalloc); A->~TArray(); }
