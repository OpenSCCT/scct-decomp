#ifndef VERSUS_CL_EXTALLOC_H
#define VERSUS_CL_EXTALLOC_H

#include "versus_cldata.h"

class clExtalloc_Override_Baseclass : public virtual ExtAlloc::OverrideAllocOperators {
public:
    virtual ~clExtalloc_Override_Baseclass();
};

#endif
