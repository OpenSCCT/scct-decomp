#ifndef VERSUS_PERSISTENT_DATA_TYPES_H
#define VERSUS_PERSISTENT_DATA_TYPES_H

// Engine.PersistentData: 0x7c bytes, 22 virtual functions
class UPersistentData : public UObject {
public:
    virtual ~UPersistentData();

    TArray<FString> unk_28;
    FString         unk_34;
    BYTE            unk_40[0xc];
    TArray<FString> unk_4c;
    BYTE            unk_58[0x24];
};

#endif
