// Work item 0197: Versus RVA 0xe4750-0xe4b13.
// 0xe4750 is a plain VC7.0 /O2 function; 0xe4780 comes from a /GL /O2 object
// (check with try_ltcg.py, root Driver_e4780); 0xe47e0 and 0xe4a40 are
// UE2 FSoundData::Load and FSoundData::GetPeriod from a /GL /Od /Ob1 object
// (check with try_ltcg.py, root Driver_e47e0).
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef int INT;
typedef unsigned short _WORD;
typedef DWORD UBOOL;
typedef float FLOAT;

/* 0xe4750: three-way double clamp (name unknown, UnnamedClamp_e4750). */
double UnnamedClamp_e4750(double X, double Min, double Max)
{
	if (X < Min)
		return Min;
	if (X < Max)
		return X;
	return Max;
}

/* ---- 0xe4780 ---- */

// Retail 0x12050 (published as CeilLog2_12050), UE2 appCeilLogTwo; defined
// here so the LTCG link gives it its retail register convention (argument in EDX).
extern const BYTE CeilLogTable_12050[256];
__declspec(noinline) BYTE appCeilLogTwo(DWORD Arg)
{
	if (--Arg == (DWORD)-1)
		return 0;
	BYTE Shift = Arg <= 0x10000 ? (Arg <= 0x100 ? 0 : 8) : (Arg <= 0x1000000 ? 16 : 24);
	return Shift + CeilLogTable_12050[Arg >> Shift];
}

/* Neutral names: the interface and owner classes are not identified yet. */
class UnnamedInterface_e4780
{
public:
	virtual void V00() = 0; virtual void V04() = 0; virtual void V08() = 0; virtual void V0c() = 0;
	virtual void V10() = 0; virtual void V14() = 0; virtual void V18() = 0;
	virtual INT GetWidth() = 0;          // +0x1c
	virtual INT GetHeight() = 0;         // +0x20
	virtual void V24() = 0; virtual void V28() = 0;
	virtual UBOOL Flag2c() = 0;          // +0x2c
	virtual UBOOL Flag30() = 0;          // +0x30
	virtual UBOOL Flag34() = 0;          // +0x34
};

class UnnamedClass_e4780
{
public:
	BYTE Pad[0x4c];
	INT Width0;          // 0x4c
	INT Height0;         // 0x50
	INT Width;           // 0x54
	INT Height;          // 0x58
	BYTE Flag5c, Flag5d, Flag5e;
	BYTE WidthLog2;      // 0x5f
	BYTE HeightLog2;     // 0x60
	BYTE Pad61[3];
	UnnamedInterface_e4780 *Interface; // 0x64

	void Init(UnnamedInterface_e4780 *InInterface);
};

__declspec(noinline) void UnnamedClass_e4780::Init(UnnamedInterface_e4780 *InInterface)
{
	Interface = InInterface;
	Flag5c = (BYTE)Interface->Flag2c();
	Flag5d = (BYTE)Interface->Flag30();
	Flag5e = (BYTE)Interface->Flag34();
	Width = Width0 = Interface->GetWidth();
	INT NewHeight = Interface->GetHeight();
	Height0 = NewHeight;
	Height = NewHeight;
	WidthLog2 = appCeilLogTwo(Width);
	HeightLog2 = appCeilLogTwo(NewHeight);
}

// Scaffolding for the link, not part of the unit.
void Driver_e4780(UnnamedClass_e4780 *O, UnnamedClass_e4780 *P, UnnamedInterface_e4780 *I) { O->Init(I); P->Init(I); }

/* ---- FSoundData ---- */

void *appMemcpy(void *Dest, const void *Src, INT Count);

enum EName { NAME_224 = 0x224 }; // name text unknown

class FName
{
public:
	INT Index;
	FName(EName N);
	UBOOL operator==(const FName &Other) const;
	UBOOL operator!=(const FName &Other) const;
};

class FArray
{
public:
	void *Data;
	INT ArrayNum;
	INT ArrayMax;
	__forceinline INT Num() const { return ArrayNum; }
};

template<class T> class TArray : public FArray
{
};

class FArchive;

class FLazyLoader
{
public:
	FArchive *SavedAr;
	INT SavedPos;
	virtual void Load() = 0;
	virtual void Unload() = 0;
};

template<class T> class TLazyArray : public FLazyLoader, public TArray<T>
{
public:
	void Load();
	void Unload();
};

class USound
{
public:
	BYTE Pad[0x44];
	FName FileType;      // 0x44
	BYTE Pad48[0xc];
	INT OriginalSize;    // 0x54
	FLOAT Duration;      // 0x58
};

class UAudioSubsystem
{
public:
	virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c();
	virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1c();
	virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2c();
	virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3c();
	virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4c();
	virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5c();
	virtual void V60(); virtual void V64();
	virtual void RegisterSound(USound *Sound);   // 0x68
	virtual void V6c();
	virtual void V70(); virtual void V74(); virtual void V78(); virtual void V7c();
	virtual void V80(); virtual void V84(); virtual void V88(); virtual void V8c();
	virtual void V90(); virtual void V94(); virtual void V98(); virtual void V9c();
	virtual void Va0(); virtual void Va4(); virtual void Va8(); virtual void Vac();
	virtual void Vb0(); virtual void Vb4(); virtual void Vb8();
	virtual UBOOL LowQualitySound();             // 0xbc
};
extern UAudioSubsystem *GAudio;

class FWaveModInfo
{
public:
	DWORD *pFormatTag;       // 0x00 (name guessed)
	DWORD *pSamplesPerSec;   // 0x04
	DWORD *pAvgBytesPerSec;  // 0x08
	_WORD *pBlockAlign;      // 0x0c
	_WORD *pBitsPerSample;   // 0x10
	_WORD *pChannels;        // 0x14
	DWORD OldBitsPerSample;  // 0x18
	DWORD *pWaveDataSize;    // 0x1c
	DWORD *pMasterSize;      // 0x20
	BYTE *SampleDataStart;   // 0x24
	BYTE *SampleDataEnd;     // 0x28
	DWORD SampleDataSize;    // 0x2c
	BYTE *WaveDataEnd;       // 0x30
	INT SampleLoopsNum;      // 0x34
	void *pSampleLoop;       // 0x38
	DWORD NewDataSize;       // 0x3c
	UBOOL NoiseGate;         // 0x40
	DWORD Unknown44;         // 0x44

	FWaveModInfo();
	UBOOL ReadWaveInfo(TArray<BYTE> &WavData);
	UBOOL UpdateWaveData(TArray<BYTE> &WavData);
	void Reduce16to8();
	void HalveData();
	void HalveReduce16to8();
};

class FSoundData : public TLazyArray<BYTE>
{
public:
	USound *Owner;   // 0x18
	void Load();
	FLOAT GetPeriod();
};

// The engine headers' inline members were optimised; this unit was not.
#pragma optimize("gt", on)
inline UBOOL FName::operator!=(const FName &Other) const { return Index != Other.Index; }
inline FWaveModInfo::FWaveModInfo() { NoiseGate = 0; SampleLoopsNum = 0; }
#pragma optimize("", on)

// RVA 0xe47e0: UE2 FSoundData::Load.
void FSoundData::Load()
{
	UBOOL Loaded = SavedPos > 0;
	TLazyArray<BYTE>::Load();
	if (Loaded && Owner->FileType != FName(NAME_224))
	{
		Owner->Duration = GetPeriod();
		INT Force8Bit = 0;
		INT ForceHalve = 0;
		if (GAudio && GAudio->LowQualitySound())
		{
			Force8Bit = 1;
			ForceHalve = 1;
		}
		DWORD MinRate = 22050;
		if (Force8Bit || ForceHalve)
		{
			FWaveModInfo WavData;
			if (WavData.ReadWaveInfo(*this) && WavData.SampleDataSize > 4)
			{
				UBOOL Convert8 = Force8Bit && *WavData.pBitsPerSample == 16;
				UBOOL Halve = ForceHalve && *WavData.pSamplesPerSec >= MinRate;
				if (Convert8 && Halve)
					WavData.HalveReduce16to8();
				else if (Convert8 && !Halve)
					WavData.Reduce16to8();
				else if (Halve)
					WavData.HalveData();
				WavData.UpdateWaveData(*this);
			}
		}
		Owner->OriginalSize = Num();
		if (GAudio)
			GAudio->RegisterSound(Owner);
	}
	else if (Loaded && Owner->FileType == FName(NAME_224))
	{
		Owner->Duration = GetPeriod();
		Owner->OriginalSize = Num();
		if (GAudio)
			GAudio->RegisterSound(Owner);
	}
}

// RVA 0xe4a40: UE2 FSoundData::GetPeriod.
FLOAT FSoundData::GetPeriod()
{
	FLOAT Period = 0.f;
	if (Owner->FileType != FName(NAME_224))
	{
		TLazyArray<BYTE>::Load();
		FWaveModInfo WavData;
		if (WavData.ReadWaveInfo(*this))
		{
			INT DurationDiv = *WavData.pChannels * *WavData.pBitsPerSample * *WavData.pSamplesPerSec;
			if (DurationDiv)
				Period = *WavData.pWaveDataSize * 8.f / DurationDiv;
		}
	}
	else
	{
		TLazyArray<BYTE>::Load();
		appMemcpy(&Period, (BYTE *)Data + 4, 4);
	}
	return Period;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_e47e0(FSoundData *S) { Escape(&GAudio); S->FSoundData::Load(); S->GetPeriod(); }
