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

// Core.PackageMap: 0x70 bytes, 32 virtual functions
class UPackageMap : public UObject {
public:
    virtual ~UPackageMap();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();

    BYTE unk_28[0x48];
};

// Core.Subsystem: 0x28 bytes, 23 virtual functions
class USubsystem : public UObject {
public:
    virtual ~USubsystem();
    virtual void VirtualSlot22();
};

// Core.Commandlet: 0x1dc bytes, 23 virtual functions
class UCommandlet : public UObject {
public:
    virtual ~UCommandlet();
    virtual void VirtualSlot22();

    BYTE unk_28[0x1b4];
};

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
