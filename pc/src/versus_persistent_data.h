#ifndef VERSUS_PERSISTENT_DATA_H
#define VERSUS_PERSISTENT_DATA_H

#include "versus_persistent_data_types.h"

class USPlayerProfile;

class USPersistentData : public UPersistentData {
public:
    USPlayerProfile *PlayerProfile;
};

USPersistentData *GetMgmPersistentData();

#endif
