#ifndef VERSUS_OBJECT_FACTORY_H
#define VERSUS_OBJECT_FACTORY_H

inline UObject *ConstructObject(UClass *Type, UObject *Outer, FName InName = NAME_None,
    DWORD Flags = 0, UObject *Template = 0, FOutputDevice *Error = GError, UObject *SubobjectRoot = 0) {
    UObject *Object = UObject::StaticAllocateObject(Type, Outer, InName, Flags, Template, Error, 0, SubobjectRoot);
    if (Object)
        Type->ClassConstructor(Object);
    return Object;
}

#endif
