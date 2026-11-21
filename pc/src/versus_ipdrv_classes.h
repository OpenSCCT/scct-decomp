// versus_ipdrv_classes.h -- classes of the IpDrv package as the Versus executable builds them
#ifndef VERSUS_IPDRV_CLASSES_H
#define VERSUS_IPDRV_CLASSES_H

#include "versus_build.h"
#include "versus_engine_classes.h"

// IpDrv.InternetLink: 0x314 bytes, 78 virtual functions
class AInternetLink : public AInternetInfo {
public:
    virtual ~AInternetLink();

    BYTE unk_2f8[0x1c];
};

// IpDrv.UdpLink: 0x32c bytes, 78 virtual functions
class AUdpLink : public AInternetLink {
public:
    virtual ~AUdpLink();

    BYTE unk_314[0x18];
};

#endif // VERSUS_IPDRV_CLASSES_H
