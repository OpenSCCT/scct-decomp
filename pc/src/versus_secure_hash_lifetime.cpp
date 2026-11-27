#include "versus_secure_hash_algorithm_1.h"

extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

clExtalloc_Override_Baseclass::~clExtalloc_Override_Baseclass()
{
}

SecureHashAlgorithm1::~SecureHashAlgorithm1()
{
    memset(&Context, 0, sizeof(Context));
}
