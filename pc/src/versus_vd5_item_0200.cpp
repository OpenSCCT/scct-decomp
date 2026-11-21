// FWaveModInfo (UnAudio.cpp, Unreal Engine 2): WAV header parsing and
// 16->8 bit reduction. Retail compiled these four bodies without optimisation
// (#pragma optimize off) in an /O2 /GL unit, so the small helpers they call
// (TArray::operator(), Pad16Bit) got LTCG register conventions. Local names
// were chosen so /Od stack-slot order matches retail.
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef short SWORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" void *appMemcpy(void *Dest, const void *Src, INT Count);

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    __forceinline INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count);
};

#define mmioFOURCC(a, b, c, d) ((DWORD)(BYTE)(a) | ((DWORD)(BYTE)(b) << 8) | ((DWORD)(BYTE)(c) << 16) | ((DWORD)(BYTE)(d) << 24))

struct FRiffWaveHeader
{
    DWORD rID;
    DWORD ChunkLen;
    DWORD wID;
};

struct FRiffChunkOld
{
    DWORD ChunkID;
    DWORD ChunkLen;
};

struct FFormatChunk
{
    _WORD wFormatTag;
    _WORD nChannels;
    DWORD nSamplesPerSec;
    DWORD nAvgBytesPerSec;
    _WORD nBlockAlign;
    _WORD wBitsPerSample;
    _WORD cbSize;
};

struct FSampleChunk
{
    DWORD dwManufacturer;
    DWORD dwProduct;
    DWORD dwSamplePeriod;
    DWORD dwMIDIUnityNote;
    DWORD dwMIDIPitchFraction;
    DWORD dwSMPTEFormat;
    DWORD dwSMPTEOffset;
    DWORD cSampleLoops;
    DWORD cbSamplerData;
};

struct FSampleLoop
{
    DWORD dwIdentifier;
    DWORD dwType;
    DWORD dwStart;
    DWORD dwEnd;
    DWORD dwFraction;
    DWORD dwPlayCount;
};

class FWaveModInfo
{
public:
    _WORD *pFormatTag;
    DWORD *pSamplesPerSec;
    DWORD *pAvgBytesPerSec;
    _WORD *pBlockAlign;
    _WORD *pBitsPerSample;
    _WORD *pChannels;
    DWORD OldBitsPerSample;
    DWORD *pWaveDataSize;
    DWORD *pMasterSize;
    BYTE *SampleDataStart;
    BYTE *SampleDataEnd;
    DWORD SampleDataSize;
    BYTE *WaveDataEnd;
    INT SampleLoopsNum;
    FSampleLoop *pSampleLoop;
    DWORD NewDataSize;
    UBOOL NoiseGate;

    DWORD Pad16Bit(DWORD InDW) { return ((InDW + 1) & ~1); }

    UBOOL ReadWaveInfo(TArray<BYTE> &WavData);
    UBOOL UpdateWave(TArray<BYTE> &WavData);
    void HalveReduce16to8();
    void Reduce16to8();
};

#pragma optimize("", off)

UBOOL FWaveModInfo::ReadWaveInfo(TArray<BYTE> &WavData)
{
    FFormatChunk *FmtChunk;
    FRiffWaveHeader *RiffHdr = (FRiffWaveHeader *)&WavData(0);
    WaveDataEnd = &WavData(0) + WavData.Num();

    if (RiffHdr->wID != mmioFOURCC('W', 'A', 'V', 'E'))
        return 0;

    // Effective file size.
    pMasterSize = &RiffHdr->ChunkLen;

    // Locate the 'fmt ' chunk.
    FRiffChunkOld *RiffChunk = (FRiffChunkOld *)&WavData(3 * 4);
    while (((BYTE *)RiffChunk + 8) < WaveDataEnd && RiffChunk->ChunkID != mmioFOURCC('f', 'm', 't', ' '))
        RiffChunk = (FRiffChunkOld *)((BYTE *)RiffChunk + Pad16Bit(RiffChunk->ChunkLen) + 8);

    if (RiffChunk->ChunkID != mmioFOURCC('f', 'm', 't', ' '))
        return 0;

    FmtChunk = (FFormatChunk *)((BYTE *)RiffChunk + 8);
    pFormatTag = &FmtChunk->wFormatTag;
    pBitsPerSample = &FmtChunk->wBitsPerSample;
    pSamplesPerSec = &FmtChunk->nSamplesPerSec;
    pAvgBytesPerSec = &FmtChunk->nAvgBytesPerSec;
    pBlockAlign = &FmtChunk->nBlockAlign;
    pChannels = &FmtChunk->nChannels;

    // Look for the 'data' chunk.
    RiffChunk = (FRiffChunkOld *)&WavData(3 * 4);
    while (((BYTE *)RiffChunk + 8) < WaveDataEnd && RiffChunk->ChunkID != mmioFOURCC('d', 'a', 't', 'a'))
        RiffChunk = (FRiffChunkOld *)((BYTE *)RiffChunk + Pad16Bit(RiffChunk->ChunkLen) + 8);

    if (RiffChunk->ChunkID != mmioFOURCC('d', 'a', 't', 'a'))
        return 0;

    SampleDataStart = (BYTE *)RiffChunk + 8;
    pWaveDataSize = &RiffChunk->ChunkLen;
    SampleDataSize = RiffChunk->ChunkLen;
    OldBitsPerSample = FmtChunk->wBitsPerSample;
    SampleDataEnd = SampleDataStart + SampleDataSize;
    NewDataSize = SampleDataSize;

    // Look for an optional 'smpl' chunk.
    RiffChunk = (FRiffChunkOld *)&WavData(3 * 4);
    while (((BYTE *)RiffChunk + 8) < WaveDataEnd && RiffChunk->ChunkID != mmioFOURCC('s', 'm', 'p', 'l'))
        RiffChunk = (FRiffChunkOld *)((BYTE *)RiffChunk + Pad16Bit(RiffChunk->ChunkLen) + 8);

    if ((INT)RiffChunk + 4 < (INT)WaveDataEnd && RiffChunk->ChunkID == mmioFOURCC('s', 'm', 'p', 'l'))
    {
        FSampleChunk pSampleChunk;
        appMemcpy(&pSampleChunk, (BYTE *)RiffChunk + 8, sizeof(FSampleChunk));
        SampleLoopsNum = pSampleChunk.cSampleLoops;
        pSampleLoop = (FSampleLoop *)((BYTE *)RiffChunk + 8 + sizeof(FSampleChunk));
    }
    return 1;
}

UBOOL FWaveModInfo::UpdateWave(TArray<BYTE> &WavData)
{
    if (NewDataSize < SampleDataSize)
    {
        INT SizeDiff = Pad16Bit(SampleDataSize) - Pad16Bit(NewDataSize);
        *pWaveDataSize = NewDataSize;
        *pMasterSize -= SizeDiff;
        *pBlockAlign = *pChannels * (*pBitsPerSample >> 3);
        *pAvgBytesPerSec = *pBlockAlign * *pSamplesPerSec;
        if (SampleLoopsNum)
        {
            FSampleLoop *pTempSampleLoop = pSampleLoop;
            DWORD SampleDivisor = (SampleDataSize * *pBitsPerSample) / NewDataSize;
            for (INT SL = 0; SL < SampleLoopsNum; SL++)
            {
                pTempSampleLoop->dwStart = pTempSampleLoop->dwStart * OldBitsPerSample / SampleDivisor;
                pTempSampleLoop->dwEnd = pTempSampleLoop->dwEnd * OldBitsPerSample / SampleDivisor;
                pTempSampleLoop++;
            }
        }
        BYTE *NewTail = SampleDataEnd - SizeDiff;
        for (INT i = 0; i < WaveDataEnd - SampleDataEnd; i++)
            NewTail[i] = SampleDataEnd[i];
        // Remove the excess. NewSize is unused; retail keeps its stack slot.
        {
            INT OldSize = WavData.Num();
            INT NewSize;
            WavData.Remove(OldSize - SizeDiff, SizeDiff);
        }
    }
    return 1;
}

void FWaveModInfo::HalveReduce16to8()
{
    DWORD SampleWords = SampleDataSize >> 1;
    INT OrigValue, NewValue;
    INT ErrorDiff = 0;
    DWORD SampleBytes = SampleWords >> 1;
    INT NextSample0 = (INT)((SWORD *)SampleDataStart)[0];
    INT NextSample1, NextSample2;
    BYTE *SampleData = SampleDataStart;
    for (DWORD T = 0; T < SampleBytes; T++)
    {
        NextSample1 = (INT)((SWORD *)SampleData)[T * 2];
        NextSample2 = (INT)((SWORD *)SampleData)[T * 2 + 1];
        INT Combined = NextSample0 + 2 * 65536 + NextSample1 + NextSample1 + NextSample2;
        NextSample0 = NextSample2;
        OrigValue = ErrorDiff + Combined;
        NewValue = (OrigValue + 512) & 0xfffffc00;
        if (NewValue > 0x3fc00)
            NewValue = 0x3fc00;
        INT NewByte = NewValue >> 10;
        SampleData[T] = (BYTE)NewByte;
        ErrorDiff = OrigValue - NewValue;
    }
    NewDataSize = SampleBytes;
    *pBitsPerSample = 8;
    *pSamplesPerSec = *pSamplesPerSec >> 1;
    NoiseGate = 1;
}

void FWaveModInfo::Reduce16to8()
{
    DWORD NumSamples = SampleDataSize >> 1;
    INT OrigValue, NewValue;
    INT ErrorDiff = 0;
    SWORD *SampleData = (SWORD *)SampleDataStart;
    for (DWORD T = 0; T < NumSamples; T++)
    {
        OrigValue = ErrorDiff + SampleData[T] + 32768;
        NewValue = (OrigValue + 127) & 0xffffff00;
        if (NewValue > 0xff00)
            NewValue = 0xff00;
        INT NewByte = NewValue >> 8;
        ((BYTE *)SampleData)[T] = (BYTE)NewByte;
        ErrorDiff = OrigValue - NewValue;
    }
    NewDataSize = NumSamples;
    *pBitsPerSample = 8;
    NoiseGate = 1;
}

#pragma optimize("", on)

// Scaffolding for the link, not part of the unit.
void Driver_e5230(FWaveModInfo *W, TArray<BYTE> *A)
{
    W->ReadWaveInfo(*A);
    W->UpdateWave(*A);
    W->HalveReduce16to8();
    W->Reduce16to8();
}
