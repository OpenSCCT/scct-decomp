// versus_d3dx_zlib.h -- canonical Versus D3DX inflate ABI
#ifndef VERSUS_D3DX_ZLIB_H
#define VERSUS_D3DX_ZLIB_H

// Versus' D3DX copy uses the 32-bit zlib 1.1.4 scalar ABI.
typedef unsigned int uInt;
typedef unsigned long uLong;
typedef unsigned char Bytef;
typedef uInt uIntf;
typedef uLong uLongf;
typedef void *voidpf;

namespace D3DX {

typedef unsigned char Byte;
typedef unsigned int uInt;
typedef unsigned long uLong;
typedef Byte Bytef;
typedef uInt uIntf;
typedef uLong uLongf;
typedef void *voidpf;

typedef voidpf (__cdecl *alloc_func)(voidpf opaque, uInt items, uInt size);
typedef void (__cdecl *free_func)(voidpf opaque, voidpf address);
typedef uLong (__cdecl *check_func)(uLong check, const Bytef *buf, uInt len);

struct internal_state;
struct inflate_blocks_state;
struct inflate_codes_state;
struct inflate_huft_s;

typedef inflate_blocks_state inflate_blocks_statef;
typedef inflate_codes_state inflate_codes_statef;
typedef inflate_huft_s inflate_huft;

struct z_stream_s {
    Bytef *next_in;
    uInt avail_in;
    uLong total_in;
    Bytef *next_out;
    uInt avail_out;
    uLong total_out;
    char *msg;
    internal_state *state;
    alloc_func zalloc;
    free_func zfree;
    voidpf opaque;
    int data_type;
    uLong adler;
    uLong reserved;
};

typedef z_stream_s z_stream;
typedef z_stream_s *z_streamp;

// The stream state is 0x18 bytes in Versus. Its mode constants are kept in
// the owning inflate source because the separate zlib state enums reuse names.
struct internal_state {
    int mode;
    union {
        uInt method;
        struct {
            uLong was;
            uLong need;
        } check;
        uInt marker;
    } sub;
    int nowrap;
    uInt wbits;
    inflate_blocks_statef *blocks;
};

// Eight-byte table entry used by the Versus dynamic Huffman builder.
struct inflate_huft_s {
    union {
        struct {
            Byte Exop;
            Byte Bits;
        } what;
        uInt raw;
    } word;
    uInt base;
};

// The mode words are 32-bit enum storage in the retail layouts. Their
// translation-unit enum labels stay with the owning D3DX function bodies.
struct inflate_blocks_state {
    int mode;
    union {
        uInt left;
        struct {
            uInt table;
            uInt index;
            uIntf *blens;
            uInt bb;
            inflate_huft *tb;
        } trees;
        struct {
            inflate_codes_statef *codes;
        } decode;
    } sub;
    uInt last;
    uInt bitk;
    uLong bitb;
    inflate_huft *hufts;
    Bytef *window;
    Bytef *end;
    Bytef *read;
    Bytef *write;
    check_func checkfn;
    uLong check;
};

struct inflate_codes_state {
    int mode;
    uInt len;
    union {
        struct {
            inflate_huft *tree;
            uInt need;
        } code;
        uInt lit;
        struct {
            uInt get;
            uInt dist;
        } copy;
    } sub;
    Byte lbits;
    Byte dbits;
    inflate_huft *ltree;
    inflate_huft *dtree;
};

inflate_blocks_statef *inflate_blocks_new(z_streamp z, check_func check, uInt window_size);
void inflate_blocks_reset(inflate_blocks_statef *blocks, z_streamp z, uLongf *check);
int inflate_blocks_free(inflate_blocks_statef *blocks, z_streamp z);
void inflate_codes_free(inflate_codes_statef *codes, z_streamp z);
inflate_codes_statef *inflate_codes_new(uInt literal_bits, uInt distance_bits,
                                        inflate_huft *literal_tree, inflate_huft *distance_tree,
                                        z_streamp z);
int inflate_trees_bits(uIntf *code_lengths, uIntf *bits, inflate_huft **tree,
                       inflate_huft *work, z_streamp z);
int inflate_trees_dynamic(uInt literal_count, uInt distance_count, uIntf *code_lengths,
                          uIntf *literal_bits, uIntf *distance_bits,
                          inflate_huft **literal_tree, inflate_huft **distance_tree,
                          inflate_huft *work, z_streamp z);
int inflate_flush(inflate_blocks_statef *blocks, z_streamp z, int result);

// These retail data arrays are outside the reserved function ranges. Keep them
// external and bind their relocations to retail; do not add unclaimed definitions.
extern const uInt cplens[31];
extern const uInt cplext[31];
extern const uInt cpdist[30];
extern const uInt cpdext[30];

} // namespace D3DX

#ifndef Z_NULL
#define Z_NULL 0
#endif
#ifndef Z_OK
#define Z_OK 0
#define Z_STREAM_END 1
#define Z_NEED_DICT 2
#define Z_ERRNO (-1)
#define Z_STREAM_ERROR (-2)
#define Z_DATA_ERROR (-3)
#define Z_MEM_ERROR (-4)
#define Z_BUF_ERROR (-5)
#define Z_VERSION_ERROR (-6)
#endif
#ifndef ZLIB_VERSION
#define ZLIB_VERSION "1.1.4"
#endif
#ifndef DEF_WBITS
#define DEF_WBITS 15
#endif
#ifndef MANY
#define MANY 1440
#endif
#ifndef ZALLOC
#define ZALLOC(stream, items, size) ((stream)->zalloc((stream)->opaque, (items), (size)))
#endif
#ifndef ZFREE
#define ZFREE(stream, address) ((stream)->zfree((stream)->opaque, (voidpf)(address)))
#endif

// The x86 COFF names for these C-linkage entry points are _inflateReset,
// _inflateEnd and _inflateInit2_.
extern "C" int __cdecl inflateReset(D3DX::z_streamp z);
extern "C" int __cdecl inflateEnd(D3DX::z_streamp z);
extern "C" int __cdecl inflateInit2_(D3DX::z_streamp z, int window_bits,
                                     const char *version, int stream_size);
extern "C" D3DX::uLong __cdecl adler32(D3DX::uLong adler, const D3DX::Bytef *buffer,
                                        D3DX::uInt length);
extern "C" D3DX::voidpf __cdecl zcalloc(D3DX::voidpf opaque, D3DX::uInt items,
                                        D3DX::uInt size);
extern "C" void __cdecl zcfree(D3DX::voidpf opaque, D3DX::voidpf address);

#endif // VERSUS_D3DX_ZLIB_H
