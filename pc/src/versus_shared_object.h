// versus_shared_object.h -- prefix shared by reference-counting and storage helpers
#ifndef VERSUS_SHARED_OBJECT_H
#define VERSUS_SHARED_OBJECT_H

struct SharedObject;
typedef void (__fastcall *SharedObjectDestroy)(struct SharedObject *, float);

struct SharedObject {
    SharedObjectDestroy *methods;
    unsigned references;
};

#endif
