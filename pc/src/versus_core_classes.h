// versus_core_classes.h -- classes of the Core package as the Versus executable builds them
#ifndef VERSUS_CORE_CLASSES_H
#define VERSUS_CORE_CLASSES_H

#include "versus_build.h"
#include "unreal_object.h"

// Core.Exporter: 0x40 bytes, 24 virtual functions
class UExporter : public UObject {
public:
    virtual ~UExporter();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();

    BYTE unk_28[0x18];
};

#include "versus_net_channel.h"

// Core.Package: 0x34 bytes, 22 virtual functions
class UPackage : public UObject {
public:
    virtual ~UPackage();

    BYTE unk_28[0xc];
};

// Core.Factory: 0x68 bytes, 25 virtual functions
class UFactory : public UObject {
public:
    virtual ~UFactory();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();

    BYTE unk_28[0x40];
};

// Core.TextBufferFactory: 0x68 bytes, 25 virtual functions
class UTextBufferFactory : public UFactory {
public:
    virtual ~UTextBufferFactory();
};

// Core.ObjectExporterT3D: 0x40 bytes, 24 virtual functions
class UObjectExporterT3D : public UExporter {
public:
    virtual ~UObjectExporterT3D();
};

#endif // VERSUS_CORE_CLASSES_H
