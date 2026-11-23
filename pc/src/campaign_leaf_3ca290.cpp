// campaign_leaf_3ca290.cpp -- one function at file offset 0x3ca290, preferred VA 0x10cca290. It
// returns whether the function at 0x10ccb5a0 matches Path against any of the retail folder names
// "..\textures", "..\animations", "..\maps", "..\staticmeshes" and "..\sounds". The function and
// parameter names are invented; the strings and the bytes are the binary's.

int Unk_10ccb5a0(const unsigned short* Path, const unsigned short* Folder);

// Unk_10cca290
bool Unk_10cca290(const unsigned short* Path)
{
    if ( Unk_10ccb5a0(Path, L"..\\textures") || Unk_10ccb5a0(Path, L"..\\animations")
        || Unk_10ccb5a0(Path, L"..\\maps") || Unk_10ccb5a0(Path, L"..\\staticmeshes")
        || Unk_10ccb5a0(Path, L"..\\sounds") )
    {
        return true;
    }
    return false;
}
