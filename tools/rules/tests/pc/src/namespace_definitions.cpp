// no-game-data: synthetic
struct Allocator { int blocks; };
namespace { struct LocalState { short flags; }; }

namespace ExtAlloc {
    namespace Detail {
        struct Entry;
        struct Handle { int id; };
    }
}

struct ExtAlloc::Detail::Entry { long size; };

// This global type's tag has the same spelling as the unrelated namespaced template.
int ReadBlocks( Allocator *allocator ) {
    return allocator->blocks + sizeof( LocalState );
}
