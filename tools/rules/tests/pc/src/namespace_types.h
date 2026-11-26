// no-game-data: synthetic
#ifndef NAMESPACE_TYPES_H
#define NAMESPACE_TYPES_H

namespace ExtAlloc {
    template<class T> class Allocator;
    namespace Detail {
        struct Entry { int count; };
        class Handle;
    }
}

namespace Render {
    namespace Detail {
        struct Entry { long width; };
        struct Handle { int slot; };
    }
}

#endif
