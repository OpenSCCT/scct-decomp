// no-game-data: synthetic
#include "namespace_types.h"

namespace { struct LocalState { long size; }; }

// Uses a namespaced template and two types from a distinct nested namespace.
int ReadWidth( ExtAlloc::Allocator<int> *, ::Render::Detail::Entry *entry, Render::Detail::Handle *handle ) {
    return entry->width + handle->slot + sizeof( LocalState );
}

// A reopened namespace sees its own Entry through unqualified lookup.
namespace ExtAlloc {
    namespace Detail {
        extern "C" {
            // Reads the conflicting type in this namespace.
            int ReadCount( Entry *entry ) {
                return entry->count;
            }
        }
    }
}

// The forward declaration conflicts with the other file's definition in this same namespace.
int HasHandle( ExtAlloc::Detail::Handle *handle ) {
    return handle != 0;
}
