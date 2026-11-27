#ifndef VERSUS_MGM_TIMED_KEY_H
#define VERSUS_MGM_TIMED_KEY_H
#include "versus_mgm.h"
#include "versus_mgm_content.h"
struct MgmTimelineAction {
    virtual void ActionSlot0();
    virtual void ActionSlot1();
    virtual void Execute();
};
struct MgmTimedKey {
    BYTE unk_00[4];
    std::vector<MgmTimelineAction *> Actions;
    INT Frame;
    MgmKeyframe *Value;
    EMgmInterpolationMode Interpolation;
    INT GetFrame() const { return Frame; }
};
#endif
