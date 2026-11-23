// campaign_leaf_10b370.cpp -- one function at file offset 0x10b370, preferred VA 0x10a0b370.
// It passes the object at offset 0x24 with each of the names "MusicVolume", "AmbientVolume",
// "SFXVolume", "UseVoiceChat" and "UseOriginalVoices" and 1 to the function at VA 0x10cddbd0.
// The class, function and member names are invented; the offset and the bytes are the binary's.

void Unk_10cddbd0(void* Object, const unsigned short* Name, int Flag);

class UnkType_10a0b370
{
public:
    unsigned char unk_0[0x24];
    void* unk_24;

    void Unk_10a0b370();
};

// UnkType_10a0b370::Unk_10a0b370
void UnkType_10a0b370::Unk_10a0b370()
{
    Unk_10cddbd0(unk_24, L"MusicVolume", 1);
    Unk_10cddbd0(unk_24, L"AmbientVolume", 1);
    Unk_10cddbd0(unk_24, L"SFXVolume", 1);
    Unk_10cddbd0(unk_24, L"UseVoiceChat", 1);
    Unk_10cddbd0(unk_24, L"UseOriginalVoices", 1);
}
