#ifndef VERSUS_MGM_CONTENT_H
#define VERSUS_MGM_CONTENT_H

#include "versus_mgm_keyframes.h"

// A child owns this polymorphic object and invokes its deleting destructor.
struct MgmContent {
    virtual ~MgmContent();
    virtual void ContentSlot1();
    virtual void ContentSlot2();
    virtual void ContentSlot3();
    virtual void GetBounds(MgmImageRegion &Region) const;
    virtual void SetPlaying(BYTE Value);
    virtual void Tick(FLOAT Seconds, FLOAT DeltaSeconds);
    virtual void SetTime(FLOAT Seconds);
};

struct MgmImageContent : MgmContent {
    MgmImage *Image;
};

struct MgmTextContent : MgmContent {
    BYTE Unknown04[8];
    TCHAR *Text;
    BYTE Unknown10[5];
    BYTE Flags;

    enum { PreserveTextOnReset = 2 };
    void SetExternalText(TCHAR *Buffer)
    {
        Text = Buffer;
        Flags &= ~PreserveTextOnReset;
    }
};

#endif
