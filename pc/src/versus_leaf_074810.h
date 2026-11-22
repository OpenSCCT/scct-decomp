// versus_leaf_074810.h -- types and the class object for the function at VA 0x10974810.
// The class object at VA 0x10cbd8c8 is named by its address only. Its own unit is not identified.

#ifndef VERSUS_LEAF_074810_H
#define VERSUS_LEAF_074810_H

struct UnkType_74810_Class
{
    unsigned char unk_00[0x28];
    UnkType_74810_Class *unk_28;
};

struct UnkType_74810_Object
{
    unsigned char unk_00[0x24];
    UnkType_74810_Class *unk_24;
};

extern UnkType_74810_Class Unk_10cbd8c8;

#endif
