#ifndef VERSUS_MGM_CONTENT_H
#define VERSUS_MGM_CONTENT_H

#include "versus_mgm_keyframes.h"

// A child owns this polymorphic object and invokes its deleting destructor.
struct MgmContent {
    virtual ~MgmContent();
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
