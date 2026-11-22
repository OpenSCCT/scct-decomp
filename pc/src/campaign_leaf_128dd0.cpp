// campaign_leaf_128dd0.cpp -- free function at VA 0x10a28dd0: returns the floor of its float
// argument, computed by the C runtime floor (VA 0x10f32390). The function name is invented; floor
// is named from its jump into the runtime's _floor_default.

extern "C" double __cdecl floor(double Value);

// Unk_10a28dd0
float Unk_10a28dd0(float Value)
{
    return (float)floor(Value);
}
