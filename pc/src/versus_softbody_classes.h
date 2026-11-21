// versus_softbody_classes.h -- classes of the SoftBody package as the Versus executable builds them
#ifndef VERSUS_SOFTBODY_CLASSES_H
#define VERSUS_SOFTBODY_CLASSES_H

#include "versus_build.h"
#include "versus_engine_classes.h"

// SoftBody.ESBRopeActor: 0x3b8 bytes, 80 virtual functions
class AESBRopeActor : public AESoftBodyActor {
public:
    virtual ~AESBRopeActor();

    BYTE unk_394[0x24];
};

// SoftBody.ESBChainActor: 0x3bc bytes, 80 virtual functions
class AESBChainActor : public AESBRopeActor {
public:
    virtual ~AESBChainActor();

    BYTE unk_3b8[0x4];
};

// SoftBody.ESBPatchActor: 0x3c0 bytes, 80 virtual functions
class AESBPatchActor : public AESoftBodyActor {
public:
    virtual ~AESBPatchActor();

    BYTE unk_394[0x2c];
};

// SoftBody.ESBStripDoorActor: 0x3c0 bytes, 80 virtual functions
class AESBStripDoorActor : public AESBPatchActor {
public:
    virtual ~AESBStripDoorActor();
};

// SoftBody.ESBRope: 0x19c bytes, 58 virtual functions
class UESBRope : public UESoftBody {
public:
    virtual ~UESBRope();

    BYTE unk_15c[0x40];
};

// SoftBody.ESBChain: 0x19c bytes, 58 virtual functions
class UESBChain : public UESBRope {
public:
    virtual ~UESBChain();
};

// SoftBody.ESBPatch: 0x1a4 bytes, 58 virtual functions
class UESBPatch : public UESoftBody {
public:
    virtual ~UESBPatch();

    BYTE unk_15c[0x48];
};

// SoftBody.ESBStripDoor: 0x1a4 bytes, 58 virtual functions
class UESBStripDoor : public UESBPatch {
public:
    virtual ~UESBStripDoor();
};

#endif // VERSUS_SOFTBODY_CLASSES_H
