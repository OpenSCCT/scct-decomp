// campaign_angle_maps.cpp -- two std::map instances keyed by a sixteen-bit circular value
//
// The engine keeps two maps from a sixteen-bit circular key to a pointer, ordered by
// UnkType_10dec730. Their find and the lower-bound search it calls are the compiler's own <map>
// code, instantiated once per map: find at VA 0x10dec980 and 0x10dee070, the lower-bound search
// at 0x10dec7b0 and 0x10dedcf0. The search inlines the key comparison; find does not, so the
// comparison's call operator is also emitted on its own, at 0x10dec730. The explicit
// instantiations below ask for find as the game's callers did. None of these functions
// allocates, so the maps' allocator is not visible in their bytes and the default one is
// written. The key, compare, value and map names are invented; the offsets and the bytes are the
// binary's.

#include <cstdlib>
#include <map>

struct UnkType_10dec730_Angle
{
    int UnkDelta(const UnkType_10dec730_Angle& Other) const
    {
        int Mine = unk_0;
        int Theirs = Other.unk_0;
        int Delta = Mine - Theirs;

        if ( abs(Delta) < 0x8000 )
        {
            return Delta;
        }
        return Mine < Theirs ? Delta + 0x10000 : Delta - 0x10000;
    }

    unsigned short unk_0;
};

// UnkType_10dec730: First comes before Second when Second's circular difference from First is
// positive.
class UnkType_10dec730
{
public:
    bool operator()(const UnkType_10dec730_Angle& First, const UnkType_10dec730_Angle& Second) const
    {
        return Second.UnkDelta(First) > 0;
    }
};

struct UnkType_10dec980_Value;
struct UnkType_10dee070_Value;

typedef std::map<UnkType_10dec730_Angle, UnkType_10dec980_Value *, UnkType_10dec730>
    UnkType_10dec980_Map;
typedef std::map<UnkType_10dec730_Angle, UnkType_10dee070_Value *, UnkType_10dec730>
    UnkType_10dee070_Map;

template UnkType_10dec980_Map::iterator
    UnkType_10dec980_Map::_Mybase::find(const UnkType_10dec730_Angle &);
template UnkType_10dee070_Map::iterator
    UnkType_10dee070_Map::_Mybase::find(const UnkType_10dec730_Angle &);
