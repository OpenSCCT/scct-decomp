// The skeletal mesh archive stores one motion chunk per sequence.
#include "versus_build.h"
#include "versus_mesh_animation.h"
#include "versus_lazy_archive.h"

// The key arrays initialize themselves. Flags is filled by the archive.
AnalogTrack::AnalogTrack() {}

inline FArchive &operator<<(FArchive &Ar, FVector &V)
{
    return Ar << V.X << V.Y << V.Z;
}

inline FArchive &operator<<(FArchive &Ar, DWORD &V)
{
    Ar.Serialize(&V, sizeof(V));
    return Ar;
}

FArchive &operator<<(FArchive &Ar, AnalogTrack &Track);
FArchive &operator<<(FArchive &Ar, TArray<DWORD> &Array);
FArchive &operator<<(FArchive &Ar, MotionChunk &Move);

#include "versus_compact_index.inl"

template<class T> inline void *operator new(unsigned int, TArray<T> &Array) {
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

template<class T> void TArray<T>::Empty(INT Slack) {
    for (INT i = 0; i < ArrayNum; ++i)
        (*this)(i).~T();
    FArray::Empty(sizeof(T), Slack);
}

template<class T> FArchive &operator<<(FArchive &Ar, TArray<T> &Array) {
    Ar.CountBytes(Array.ArrayNum * sizeof(T), Array.ArrayMax * sizeof(T));
    if (Ar.IsLoading()) {
        INT Count;
        Ar << AR_INDEX(Count);
        Array.Empty(Count);
        for (INT i = 0; i < Count; ++i)
            Ar << *new(Array) T;
    } else {
        Ar << AR_INDEX(Array.ArrayNum);
        for (INT i = 0; i < Array.ArrayNum; ++i)
            Ar << Array(i);
    }
    return Ar;
}

FArchive &operator<<(FArchive &Ar, MotionChunk &Move)
{
    return Ar << Move.RootSpeed3D << Move.TrackTime << Move.StartBone << Move.Flags
              << Move.BoneIndices << Move.AnimTracks << Move.RootTrack;
}

// Allocation label used by the bulk bone-index serializer.
extern const TCHAR ArrayArchiveTag[];

FArchive &operator<<(FArchive &Ar, TArray<DWORD> &Array)
{
    Ar.CountBytes(Array.ArrayNum * sizeof(DWORD), Array.ArrayMax * sizeof(DWORD));
    Ar << AR_INDEX(Array.ArrayNum);
    if (Ar.IsLoading()) {
        Array.ArrayMax = Array.ArrayNum;
        if (!Array.Data) {
            if (!Array.ArrayNum)
                return Ar;
            Array.Data = GMalloc->Malloc(Array.ArrayNum * sizeof(DWORD), ArrayArchiveTag);
        } else if (Array.ArrayNum) {
            Array.Realloc(sizeof(DWORD));
        } else {
            Array.ArrayNum = Array.ArrayMax = 0;
            GMalloc->Free(Array.Data);
            Array.Data = 0;
            return Ar;
        }
    }
    Ar.Serialize(Array.Data, Array.ArrayNum * sizeof(DWORD));
    return Ar;
}

template FArchive &operator<<(FArchive &, TArray<MotionChunk> &);
