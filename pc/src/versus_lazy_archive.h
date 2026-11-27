// versus_lazy_archive.h -- archive interface and versioned TLazyArray serialization
#ifndef VERSUS_LAZY_ARCHIVE_H
#define VERSUS_LAZY_ARCHIVE_H

#include "versus_archive.h"

extern UBOOL GLazyLoad;
extern DWORD GUglyHackFlags;

template<class T> class TArray;

class FLazyLoader
{
public:
    virtual void Load() = 0;
    virtual void Unload() = 0;
    FArchive *SavedAr;
    INT SavedPos;
};

template <class T> class TLazyArray : public FLazyLoader, public TArray<T> {};

// operator<< for TLazyArray<T>. Deferred loads remember the archive position.
template <class T> FArchive &operator<<(FArchive &Ar, TLazyArray<T> &This)
{
    if (Ar.IsLoading()) {
        INT SeekPos = 0;
        if (Ar.Ver() <= 61) {
            Ar.AttachLazyLoader(&This);
            INT SkipCount;
            Ar << AR_INDEX(SkipCount);
            // The old archive path reads the current position and returns.
            Ar.Tell();
            return Ar;
        }
        if (Ar.Ver() >= 0xaf) {
            INT Skip;
            Ar << Skip << (TArray<T> &)This;
            return Ar;
        }
        Ar << SeekPos;
        if (GUglyHackFlags & 8)
            Ar << (TArray<T> &)This;
        else
            Ar.AttachLazyLoader(&This);
        if (!GLazyLoad)
            This.Load();
        Ar.Seek(SeekPos);
    } else if (Ar.IsSaving() && Ar.Ver() > 61) {
        if (Ar.Ver() >= 0xaf) {
            INT Skip = 0;
            Ar << Skip << (TArray<T> &)This;
        } else {
            // Backpatch the end position so a reader can skip the data.
            INT CountPos = Ar.Tell();
            Ar << CountPos << (TArray<T> &)This;
            INT EndPos = Ar.Tell();
            Ar.Seek(CountPos);
            Ar << EndPos;
            Ar.Seek(EndPos);
        }
    } else {
        Ar << (TArray<T> &)This;
    }
    return Ar;
}

#endif
