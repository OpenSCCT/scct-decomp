// Archive operators for mesh animation sequences and their legacy and object notifies.
#include "versus_animation_sequence.h"
#include "versus_lazy_archive.h"

// Compact index used for serialized TArray counts, RVA 0x1ea40.
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
    } else {
        INT Original = I.Value;
        DWORD V = Original >= 0 ? Original : -Original;
        BYTE B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
        I.Value = 0;
        Ar << B0;
        if (B0 & 0x40) {
            V >>= 6;
            BYTE B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B1;
            if (B1 & 0x80) {
                V >>= 7;
                BYTE B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B2;
                if (B2 & 0x80) {
                    V >>= 7;
                    BYTE B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                    Ar << B3;
                    if (B3 & 0x80) {
                        V >>= 7;
                        BYTE B4 = V;
                        Ar << B4;
                        I.Value = B4;
                    }
                    I.Value = (I.Value << 7) + (B3 & 0x7f);
                }
                I.Value = (I.Value << 7) + (B2 & 0x7f);
            }
            I.Value = (I.Value << 7) + (B1 & 0x7f);
        }
        I.Value = (I.Value << 6) + (B0 & 0x3f);
        if (B0 & 0x80)
            I.Value = -I.Value;
    }
    return Ar;
}

// The sequences array constructs an empty 30 fps sequence when loading.
FMeshAnimSeq::FMeshAnimSeq() : Name(NAME_None), StartFrame(0), NumFrames(0), Rate(30.f) {}

// Versions before 112 serialized only the notify's time and function name.
inline FArchive &operator<<(FArchive &Ar, FMeshAnimNotify &Notify) {
    if (Ar.Ver() < 112) {
        Notify.NotifyObject = 0;
        Ar << Notify.Time;
        Ar << Notify.Function;
    } else {
        Ar << Notify.Time;
        Ar << Notify.Function;
        Ar << (UObject *&)Notify.NotifyObject;
    }
    return Ar;
}

template<class T> inline void *operator new(unsigned int, TArray<T> &Array) {
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

template<class T> inline void EmptyArray(TArray<T> &Array, INT Slack) {
    for (INT i = 0; i < Array.ArrayNum; ++i)
        Array(i).~T();
    Array.FArray::Empty(sizeof(T), Slack);
}

template<class T> FArchive &operator<<(FArchive &Ar, TArray<T> &Array) {
    Ar.CountBytes(Array.ArrayNum * sizeof(T), Array.ArrayMax * sizeof(T));
    if (Ar.IsLoading()) {
        INT Count;
        Ar << AR_INDEX(Count);
        EmptyArray(Array, Count);
        for (INT i = 0; i < Count; ++i)
            Ar << *new(Array) T;
    } else {
        Ar << AR_INDEX(Array.ArrayNum);
        for (INT i = 0; i < Array.ArrayNum; ++i)
            Ar << Array(i);
    }
    return Ar;
}

FArchive &operator<<(FArchive &Ar, FMeshAnimSeq &Sequence) {
    if (Ar.Ver() >= 115)
        Ar << Sequence.unk_28;
    else
        Sequence.unk_28 = 0;
    Ar << Sequence.Name;
    Ar << Sequence.Groups;
    Ar << Sequence.StartFrame;
    Ar << Sequence.NumFrames;
    Ar << Sequence.Notifys;
    Ar << Sequence.Rate;
    return Ar;
}

template FArchive &operator<<(FArchive &, TArray<FMeshAnimSeq> &);
