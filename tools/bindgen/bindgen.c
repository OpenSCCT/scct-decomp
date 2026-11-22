/* bindgen.c -- derive a unit's inputs and link_bindings from its compiled object.

   For one unit record of a Campaign-layout target manifest this tool:
     1. collects the unit's inputs: its source file, then every quoted #include it reaches;
     2. compiles the source with the record's build_command and toolchain (--cl), or reads an
        object already built from that source (--object);
     3. finds the record's function in the object and walks its relocations;
     4. gives each external target the VA that the retail image holds at the same relocation
        field. The retail operand is the address, not the symbol name. A call target must be a
        function entry in the function map, and every byte outside a relocation field must equal
        the retail byte, so a unit that is not a byte match gets no bindings.
   It prints the record fragment { "id", "inputs", "link_bindings" }. With --check it compares
   the fragment with the record and lists each difference; the exit status is 1 if there is one.
   The basis text is generated; the record's prose is not compared.

   Build (MSVC 19.44, from a Developer Command Prompt or after vcvars32.bat):
     cl /nologo /std:c11 /W4 /WX /Fe:bindgen.exe tools\bindgen\bindgen.c
   See tools/bindgen/README.md for the run lines and the limits. */

#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include <ctype.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#define MAKE_DIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#include <sys/types.h>
#define MAKE_DIR(path) mkdir(path, 0777)
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

/* Campaign: a file offset becomes a VA by adding this base (VA = 0x10900000 + offset). */
#define IMAGE_BASE ((u32)0x10900000u)
#define PATH_CAP 1024
#define MAX_INCLUDE_DEPTH 32
#define REL_DIR32 0x06u
#define REL_REL32 0x14u
#define SYM_EXTERNAL 2u
#define SYM_STATIC 3u
#define SYM_FUNCTION 0x20u
#define SCN_CODE 0x00000020u
#define SCN_EXECUTE 0x20000000u

/* ---- failures, memory and files ---------------------------------------------------- */

static void fail(const char *format, ...)
{
    va_list args;
    fprintf(stderr, "bindgen: ");
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(1);
}

static void usage(void)
{
    fprintf(stderr,
            "usage: bindgen [--game STEAM_DIR | --image FILE] [--cl CL_EXE | --object FILE] [--check]\n"
            "               MANIFEST UNIT_ID\n");
    exit(2);
}

static void *xmalloc(size_t n)
{
    void *p = malloc(n ? n : 1);
    if (!p)
        fail("out of memory");
    return p;
}

static void *xcalloc(size_t n)
{
    void *p = calloc(1, n ? n : 1);
    if (!p)
        fail("out of memory");
    return p;
}

static char *xstrndup(const char *s, size_t n)
{
    char *p = xmalloc(n + 1);
    memcpy(p, s, n);
    p[n] = 0;
    return p;
}

static char *xstrdup(const char *s)
{
    return xstrndup(s, strlen(s));
}

static void need(size_t size, size_t offset, size_t length, const char *what)
{
    if (offset > size || length > size - offset)
        fail("%s lies outside the file", what);
}

static u32 rd16(const u8 *p)
{
    return (u32)p[0] | ((u32)p[1] << 8);
}

static u32 rd32(const u8 *p)
{
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

/* Reads a whole file, NUL-terminated so that text can be scanned in place. */
static u8 *read_file(const char *path, size_t *size)
{
    FILE *f = fopen(path, "rb");
    long length = 0;
    u8 *buffer;
    if (!f)
        fail("cannot open %s", path);
    if (fseek(f, 0, SEEK_END) != 0 || (length = ftell(f)) < 0 || fseek(f, 0, SEEK_SET) != 0)
        fail("cannot measure %s", path);
    buffer = xmalloc((size_t)length + 1);
    if (fread(buffer, 1, (size_t)length, f) != (size_t)length)
        fail("cannot read %s", path);
    fclose(f);
    buffer[length] = 0;
    *size = (size_t)length;
    return buffer;
}

static int file_exists(const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f)
        return 0;
    fclose(f);
    return 1;
}

static void write_file(const char *path, const u8 *data, size_t size)
{
    FILE *f = fopen(path, "wb");
    if (!f || fwrite(data, 1, size, f) != size)
        fail("cannot write %s", path);
    fclose(f);
}

/* Creates each folder on the way to path; folders that already exist are left alone. */
static void make_dirs(const char *path)
{
    char *copy = xstrdup(path);
    size_t i;
    for (i = 1; copy[i]; i++) {
        if (copy[i] == '/' || copy[i] == '\\') {
            copy[i] = 0;
            MAKE_DIR(copy);
            copy[i] = '/';
        }
    }
    MAKE_DIR(copy);
    free(copy);
}

/* ---- growing strings and lists ------------------------------------------------------ */

typedef struct {
    char *s;
    size_t n;
    size_t cap;
} Buf;

static void buf_putc(Buf *b, char c)
{
    if (b->n + 2 > b->cap) {
        size_t cap = b->cap ? b->cap * 2 : 64;
        b->s = realloc(b->s, cap);
        if (!b->s)
            fail("out of memory");
        b->cap = cap;
    }
    b->s[b->n++] = c;
    b->s[b->n] = 0;
}

static void buf_puts(Buf *b, const char *text)
{
    while (*text)
        buf_putc(b, *text++);
}

typedef struct {
    char **items;
    size_t count;
    size_t cap;
} List;

static int list_has(const List *l, const char *s)
{
    size_t i;
    for (i = 0; i < l->count; i++)
        if (strcmp(l->items[i], s) == 0)
            return 1;
    return 0;
}

static void list_add(List *l, const char *s)
{
    if (l->count == l->cap) {
        size_t cap = l->cap ? l->cap * 2 : 16;
        l->items = realloc(l->items, cap * sizeof *l->items);
        if (!l->items)
            fail("out of memory");
        l->cap = cap;
    }
    l->items[l->count++] = xstrdup(s);
}

/* ---- JSON (the manifests and records are plain JSON) -------------------------------- */

enum { J_NULL, J_BOOL, J_NUMBER, J_STRING, J_ARRAY, J_OBJECT };

typedef struct Json Json;
struct Json {
    int kind;
    int flag;
    double number;
    char *text;
    size_t count;
    size_t cap;
    Json **items;
    char **keys;
};

typedef struct {
    const char *p;
    const char *end;
    const char *name;
} Parser;

static void json_error(Parser *ps, const char *what)
{
    fail("%s: %s", ps->name, what);
}

static Json *json_new(int kind)
{
    Json *j = xcalloc(sizeof *j);
    j->kind = kind;
    return j;
}

static void json_push(Json *j, char *key, Json *item)
{
    if (j->count == j->cap) {
        size_t cap = j->cap ? j->cap * 2 : 8;
        j->items = realloc(j->items, cap * sizeof *j->items);
        if (!j->items)
            fail("out of memory");
        if (j->kind == J_OBJECT) {
            j->keys = realloc(j->keys, cap * sizeof *j->keys);
            if (!j->keys)
                fail("out of memory");
        }
        j->cap = cap;
    }
    if (j->kind == J_OBJECT)
        j->keys[j->count] = key;
    j->items[j->count++] = item;
}

static void json_free(Json *j)
{
    size_t i;
    if (!j)
        return;
    for (i = 0; i < j->count; i++) {
        json_free(j->items[i]);
        if (j->kind == J_OBJECT)
            free(j->keys[i]);
    }
    free(j->items);
    free(j->keys);
    free(j->text);
    free(j);
}

static void skip_space(Parser *ps)
{
    while (ps->p < ps->end && (*ps->p == ' ' || *ps->p == '\t' || *ps->p == '\r' || *ps->p == '\n'))
        ps->p++;
}

static int hex_digit(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}

static char *parse_string(Parser *ps)
{
    Buf b;
    memset(&b, 0, sizeof b);
    if (ps->p >= ps->end || *ps->p != '"')
        json_error(ps, "expected a string");
    ps->p++;
    for (;;) {
        char c;
        if (ps->p >= ps->end)
            json_error(ps, "unterminated string");
        c = *ps->p++;
        if (c == '"')
            break;
        if (c != '\\') {
            buf_putc(&b, c);
            continue;
        }
        if (ps->p >= ps->end)
            json_error(ps, "unterminated escape");
        c = *ps->p++;
        switch (c) {
        case '"': case '\\': case '/': buf_putc(&b, c); break;
        case 'b': buf_putc(&b, '\b'); break;
        case 'f': buf_putc(&b, '\f'); break;
        case 'n': buf_putc(&b, '\n'); break;
        case 'r': buf_putc(&b, '\r'); break;
        case 't': buf_putc(&b, '\t'); break;
        case 'u': {
            u32 code = 0;
            int k;
            if (ps->end - ps->p < 4)
                json_error(ps, "short \\u escape");
            for (k = 0; k < 4; k++) {
                int d = hex_digit(ps->p[k]);
                if (d < 0)
                    json_error(ps, "bad \\u escape");
                code = code * 16 + (u32)d;
            }
            ps->p += 4;
            if (code < 0x80) {
                buf_putc(&b, (char)code);
            } else if (code < 0x800) {
                buf_putc(&b, (char)(0xC0 | (code >> 6)));
                buf_putc(&b, (char)(0x80 | (code & 0x3F)));
            } else {
                buf_putc(&b, (char)(0xE0 | (code >> 12)));
                buf_putc(&b, (char)(0x80 | ((code >> 6) & 0x3F)));
                buf_putc(&b, (char)(0x80 | (code & 0x3F)));
            }
            break;
        }
        default:
            json_error(ps, "bad escape");
        }
    }
    return b.s ? b.s : xstrdup("");
}

static Json *parse_value(Parser *ps);

static Json *parse_object(Parser *ps)
{
    Json *obj = json_new(J_OBJECT);
    ps->p++;
    skip_space(ps);
    if (ps->p < ps->end && *ps->p == '}') {
        ps->p++;
        return obj;
    }
    for (;;) {
        char *key;
        Json *value;
        skip_space(ps);
        key = parse_string(ps);
        skip_space(ps);
        if (ps->p >= ps->end || *ps->p != ':')
            json_error(ps, "expected ':'");
        ps->p++;
        value = parse_value(ps);
        json_push(obj, key, value);
        skip_space(ps);
        if (ps->p < ps->end && *ps->p == ',') {
            ps->p++;
            continue;
        }
        if (ps->p < ps->end && *ps->p == '}') {
            ps->p++;
            return obj;
        }
        json_error(ps, "expected ',' or '}'");
    }
}

static Json *parse_array(Parser *ps)
{
    Json *arr = json_new(J_ARRAY);
    ps->p++;
    skip_space(ps);
    if (ps->p < ps->end && *ps->p == ']') {
        ps->p++;
        return arr;
    }
    for (;;) {
        json_push(arr, NULL, parse_value(ps));
        skip_space(ps);
        if (ps->p < ps->end && *ps->p == ',') {
            ps->p++;
            continue;
        }
        if (ps->p < ps->end && *ps->p == ']') {
            ps->p++;
            return arr;
        }
        json_error(ps, "expected ',' or ']'");
    }
}

static Json *parse_value(Parser *ps)
{
    Json *j;
    skip_space(ps);
    if (ps->p >= ps->end)
        json_error(ps, "unexpected end of file");
    if (*ps->p == '{')
        return parse_object(ps);
    if (*ps->p == '[')
        return parse_array(ps);
    if (*ps->p == '"') {
        j = json_new(J_STRING);
        j->text = parse_string(ps);
        return j;
    }
    if (ps->end - ps->p >= 4 && memcmp(ps->p, "true", 4) == 0) {
        ps->p += 4;
        j = json_new(J_BOOL);
        j->flag = 1;
        return j;
    }
    if (ps->end - ps->p >= 5 && memcmp(ps->p, "false", 5) == 0) {
        ps->p += 5;
        return json_new(J_BOOL);
    }
    if (ps->end - ps->p >= 4 && memcmp(ps->p, "null", 4) == 0) {
        ps->p += 4;
        return json_new(J_NULL);
    }
    if (*ps->p == '-' || (*ps->p >= '0' && *ps->p <= '9')) {
        char *endp;
        j = json_new(J_NUMBER);
        j->number = strtod(ps->p, &endp);
        if (endp == ps->p || endp > ps->end)
            json_error(ps, "bad number");
        ps->p = endp;
        return j;
    }
    json_error(ps, "unexpected character");
    return NULL;
}

static Json *json_load(const char *path)
{
    size_t size;
    char *text = (char *)read_file(path, &size);
    Parser ps;
    Json *root;
    ps.p = text;
    ps.end = text + size;
    ps.name = path;
    root = parse_value(&ps);
    skip_space(&ps);
    if (ps.p != ps.end)
        json_error(&ps, "text after the JSON value");
    free(text);
    return root;
}

static const Json *jget(const Json *obj, const char *key)
{
    size_t i;
    if (!obj || obj->kind != J_OBJECT)
        return NULL;
    for (i = 0; i < obj->count; i++)
        if (strcmp(obj->keys[i], key) == 0)
            return obj->items[i];
    return NULL;
}

static const Json *jreq(const Json *obj, const char *key)
{
    const Json *v = jget(obj, key);
    if (!v)
        fail("missing \"%s\" in the manifest or a unit record", key);
    return v;
}

static const char *jstr(const Json *v, const char *what)
{
    if (!v || v->kind != J_STRING)
        fail("%s is not a string", what);
    return v->text;
}

static u32 ju32(const Json *v, const char *what)
{
    if (!v || v->kind != J_NUMBER || v->number < 0.0 || v->number > 4294967295.0
        || (double)(u32)v->number != v->number)
        fail("%s is not a 32-bit unsigned integer", what);
    return (u32)v->number;
}

/* ---- paths -------------------------------------------------------------------------- */

/* Writes the folder part of path (everything before the last separator, or "." if none). */
static void parent_of(const char *path, char *out)
{
    const char *cut = NULL;
    const char *p;
    for (p = path; *p; p++)
        if (*p == '/' || *p == '\\')
            cut = p;
    if (!cut) {
        strcpy(out, ".");
        return;
    }
    if (cut - path >= PATH_CAP)
        fail("path too long: %s", path);
    memcpy(out, path, (size_t)(cut - path));
    out[cut - path] = 0;
}

/* Writes dir/name into out (a different buffer). */
static void join_path(const char *dir, const char *name, char *out)
{
    if (strlen(dir) + strlen(name) + 2 > PATH_CAP)
        fail("path too long: %s/%s", dir, name);
    if (dir[0])
        sprintf(out, "%s/%s", dir, name);
    else
        strcpy(out, name);
}

/* Writes a normalized forward-slash form of a project-relative path. Returns 0 for an absolute
   path, one that leaves the project, or one that is too long. */
static int normalize_relative(const char *in, char *out)
{
    char work[PATH_CAP];
    char *parts[128];
    size_t n = 0, i, used = 0;
    char *tok;
    if (strlen(in) >= sizeof work || in[0] == '/' || in[0] == '\\' || strchr(in, ':'))
        return 0;
    for (i = 0; in[i]; i++)
        work[i] = in[i] == '\\' ? '/' : in[i];
    work[i] = 0;
    for (tok = strtok(work, "/"); tok; tok = strtok(NULL, "/")) {
        if (strcmp(tok, ".") == 0 || tok[0] == 0)
            continue;
        if (strcmp(tok, "..") == 0) {
            if (n == 0)
                return 0;
            n--;
            continue;
        }
        if (n == sizeof parts / sizeof parts[0])
            return 0;
        parts[n++] = tok;
    }
    out[0] = 0;
    for (i = 0; i < n; i++) {
        size_t len = strlen(parts[i]);
        if (used + len + 2 > PATH_CAP)
            return 0;
        if (i)
            out[used++] = '/';
        memcpy(out + used, parts[i], len);
        used += len;
        out[used] = 0;
    }
    return 1;
}

static int ends_with_ci(const char *s, const char *suffix)
{
    size_t n = strlen(s), m = strlen(suffix), i;
    if (n < m)
        return 0;
    for (i = 0; i < m; i++)
        if (tolower((unsigned char)s[n - m + i]) != tolower((unsigned char)suffix[i]))
            return 0;
    return 1;
}

/* ---- SHA-256: the image must be the locked build before anything is read from it ----- */

static void sha256(const u8 *message, size_t length, u8 digest[32])
{
    static const u32 k[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    u32 h[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    size_t padded = ((length + 9 + 63) / 64) * 64, block, i;
    u8 *buf = xcalloc(padded);
    uint64_t bits = (uint64_t)length * 8;
    memcpy(buf, message, length);
    buf[length] = 0x80;
    for (i = 0; i < 8; i++)
        buf[padded - 1 - i] = (u8)(bits >> (8 * i));
    for (block = 0; block < padded; block += 64) {
        u32 w[64], a, b, c, d, e, f, g, hh;
        for (i = 0; i < 16; i++) {
            const u8 *p = buf + block + 4 * i;
            w[i] = ((u32)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | (u32)p[3];
        }
        for (i = 16; i < 64; i++) {
            u32 x = w[i - 15], y = w[i - 2];
            u32 s0 = ((x >> 7) | (x << 25)) ^ ((x >> 18) | (x << 14)) ^ (x >> 3);
            u32 s1 = ((y >> 17) | (y << 15)) ^ ((y >> 19) | (y << 13)) ^ (y >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }
        a = h[0]; b = h[1]; c = h[2]; d = h[3]; e = h[4]; f = h[5]; g = h[6]; hh = h[7];
        for (i = 0; i < 64; i++) {
            u32 s1 = ((e >> 6) | (e << 26)) ^ ((e >> 11) | (e << 21)) ^ ((e >> 25) | (e << 7));
            u32 ch = (e & f) ^ (~e & g);
            u32 t1 = hh + s1 + ch + k[i] + w[i];
            u32 s0 = ((a >> 2) | (a << 30)) ^ ((a >> 13) | (a << 19)) ^ ((a >> 22) | (a << 10));
            u32 maj = (a & b) ^ (a & c) ^ (b & c);
            u32 t2 = s0 + maj;
            hh = g; g = f; f = e; e = d + t1; d = c; c = b; b = a; a = t1 + t2;
        }
        h[0] += a; h[1] += b; h[2] += c; h[3] += d; h[4] += e; h[5] += f; h[6] += g; h[7] += hh;
    }
    for (i = 0; i < 8; i++) {
        digest[4 * i] = (u8)(h[i] >> 24);
        digest[4 * i + 1] = (u8)(h[i] >> 16);
        digest[4 * i + 2] = (u8)(h[i] >> 8);
        digest[4 * i + 3] = (u8)h[i];
    }
    free(buf);
}

static void hex_digest(const u8 *digest, char out[65])
{
    static const char *hex = "0123456789abcdef";
    size_t i;
    for (i = 0; i < 32; i++) {
        out[2 * i] = hex[digest[i] >> 4];
        out[2 * i + 1] = hex[digest[i] & 15];
    }
    out[64] = 0;
}

/* ---- function map ------------------------------------------------------------------- */

typedef struct {
    u32 start;
    u32 end;
} Range;

typedef struct {
    u32 *entries;
    size_t count;
    Range *bodies;
    size_t nbodies;
} FunctionMap;

static int compare_u32(const void *a, const void *b)
{
    u32 x = *(const u32 *)a, y = *(const u32 *)b;
    return (x > y) - (x < y);
}

static u32 parse_hex32(const char **cursor, const char *what)
{
    const char *p = *cursor;
    u32 value = 0;
    int digits = 0, d;
    while ((d = hex_digit(*p)) >= 0) {
        if (value > 0x0fffffffu)
            fail("%s is too large", what);
        value = value * 16 + (u32)d;
        digits++;
        p++;
    }
    if (!digits)
        fail("%s is not hexadecimal", what);
    *cursor = p;
    return value;
}

/* Reads the entry offsets of a function map. A header that names another image is an error. */
static void load_function_map(const char *path, const char *sha_hex, FunctionMap *map)
{
    size_t size, cap = 0, bcap = 0;
    char *text = (char *)read_file(path, &size);
    char *cursor = text;
    map->entries = NULL;
    map->count = 0;
    map->bodies = NULL;
    map->nbodies = 0;
    while (*cursor) {
        char *line = cursor;
        size_t len = strcspn(cursor, "\r\n");
        const char *p;
        cursor = line + len;
        if (*cursor)
            cursor++;
        line[len] = 0;
        p = line;
        while (*p == ' ' || *p == '\t')
            p++;
        if (!*p)
            continue;
        if (*p == '#') {
            if (strncmp(p, "# Image SHA-256 ", 16) == 0 && strncmp(p + 16, sha_hex, 64) != 0)
                fail("%s belongs to another image", path);
            continue;
        }
        if (map->count == cap) {
            cap = cap ? cap * 2 : 1024;
            map->entries = realloc(map->entries, cap * sizeof *map->entries);
            if (!map->entries)
                fail("out of memory");
        }
        map->entries[map->count++] = parse_hex32(&p, "function map entry");
        while (*p == ' ' || *p == '\t')
            p++;
        while (*p) {
            u32 start = parse_hex32(&p, "function map interval"), end;
            if (*p != '-')
                fail("%s: expected start-end on a function map line", path);
            p++;
            end = parse_hex32(&p, "function map interval");
            if (start >= end)
                fail("%s: empty interval on a function map line", path);
            if (map->nbodies == bcap) {
                bcap = bcap ? bcap * 2 : 1024;
                map->bodies = realloc(map->bodies, bcap * sizeof *map->bodies);
                if (!map->bodies)
                    fail("out of memory");
            }
            map->bodies[map->nbodies].start = start;
            map->bodies[map->nbodies].end = end;
            map->nbodies++;
            while (*p == ' ' || *p == '\t')
                p++;
        }
    }
    free(text);
    qsort(map->entries, map->count, sizeof *map->entries, compare_u32);
}

static int map_has_entry(const FunctionMap *map, u32 file)
{
    return map->count && bsearch(&file, map->entries, map->count, sizeof *map->entries, compare_u32) != NULL;
}

static int in_body(const FunctionMap *map, u32 file)
{
    size_t i;
    for (i = 0; i < map->nbodies; i++)
        if (file >= map->bodies[i].start && file < map->bodies[i].end)
            return 1;
    return 0;
}

/* The retail image must carry the Campaign base. A PE image is read through its header. */
static void check_image_base(const u8 *image, size_t len)
{
    u32 header, optional, base;
    if (len < 0x40 || image[0] != 'M' || image[1] != 'Z')
        return;
    need(len, 0x3c, 4, "the DOS header");
    header = rd32(image + 0x3c);
    need(len, header, 24, "the PE header");
    if (memcmp(image + header, "PE\0\0", 4) != 0)
        fail("the image has no PE signature");
    optional = header + 24;
    need(len, optional, 32, "the optional header");
    base = rd32(image + optional + 28);
    if (base != IMAGE_BASE)
        fail("the image base is 0x%08" PRIx32 ", not the Campaign base 0x%08" PRIx32, base, IMAGE_BASE);
}

/* True when a VA lies in a section's virtual range (or, for an image that is not PE, in the
   file). The caller has checked that va is at least the base. */
static int in_image(const u8 *image, size_t len, u32 va)
{
    u32 header, count, optional, k;
    if (len < 0x40 || image[0] != 'M' || image[1] != 'Z')
        return va - IMAGE_BASE < len;
    header = rd32(image + 0x3c);
    need(len, header, 24, "the PE header");
    count = rd16(image + header + 6);
    optional = rd16(image + header + 20);
    need(len, header + 24 + (size_t)optional, (size_t)count * 40, "the PE section table");
    for (k = 0; k < count; k++) {
        const u8 *s = image + header + 24 + optional + (size_t)k * 40;
        u32 vsize = rd32(s + 8), rva = rd32(s + 12), raw = rd32(s + 16);
        u32 span = vsize > raw ? vsize : raw;
        u32 start = IMAGE_BASE + rva;
        if (va >= start && va - start < span)
            return 1;
    }
    return 0;
}

/* ---- inputs: the source and the quoted headers it reaches -------------------------- */

static int word_at(const char *p, const char *word)
{
    size_t n = strlen(word);
    return strncmp(p, word, n) == 0 && !(isalnum((unsigned char)p[n]) || p[n] == '_');
}

/* Adds each quoted #include that names a file of the project, depth first. Includes that are not
   in the project (system headers, the compiler's own) are left to the compiler, as they are
   when verify_build.py copies the inputs. */
static void collect_inputs(const char *pc_root, const char *rel, List *inputs, int depth)
{
    char path[PATH_CAP], dir[PATH_CAP], candidate[PATH_CAP], normal[PATH_CAP], name[PATH_CAP];
    size_t size;
    char *text, *cursor;
    if (depth > MAX_INCLUDE_DEPTH)
        fail("include nesting too deep at %s", rel);
    join_path(pc_root, rel, path);
    text = (char *)read_file(path, &size);
    parent_of(rel, dir);
    if (strcmp(dir, ".") == 0)
        dir[0] = 0;
    cursor = text;
    while (*cursor) {
        char *line = cursor, *p, *close;
        size_t len = strcspn(cursor, "\r\n");
        cursor = line + len;
        if (*cursor)
            cursor++;
        line[len] = 0;
        p = line;
        while (*p == ' ' || *p == '\t')
            p++;
        if (*p != '#')
            continue;
        p++;
        while (*p == ' ' || *p == '\t')
            p++;
        if (!word_at(p, "include"))
            continue;
        p += 7;
        while (*p == ' ' || *p == '\t')
            p++;
        if (*p != '"')
            continue;
        p++;
        close = strchr(p, '"');
        if (!close || close == p || (size_t)(close - p) >= sizeof name)
            continue;
        memcpy(name, p, (size_t)(close - p));
        name[close - p] = 0;
        join_path(dir, name, candidate);
        if (!normalize_relative(candidate, normal))
            continue;
        join_path(pc_root, normal, path);
        if (!file_exists(path))
            continue;
        if (!list_has(inputs, normal)) {
            list_add(inputs, normal);
            collect_inputs(pc_root, normal, inputs, depth + 1);
        }
    }
    free(text);
}

/* ---- COFF object -------------------------------------------------------------------- */

typedef struct {
    char *name;      /* NULL for an auxiliary record */
    u32 value;
    int section;     /* 0 undefined, -1 absolute, otherwise the 1-based section number */
    u32 type;
    u32 storage;
} Symbol;

typedef struct {
    u8 *data;
    size_t size;
    u32 nsections;
    size_t section_table;
    u32 nsymbols;
    Symbol *symbols;
} Coff;

typedef struct {
    u32 raw_size;
    u32 raw_offset;
    u32 reloc_offset;
    u32 reloc_count;
    u32 characteristics;
} Section;

static Coff coff_open(u8 *data, size_t size)
{
    Coff c;
    u32 optional, table, strtab, strsize, i;
    need(size, 0, 20, "the COFF header");
    if (rd16(data) != 0x14c)
        fail("the object is not x86 COFF");
    c.data = data;
    c.size = size;
    c.nsections = rd16(data + 2);
    table = rd32(data + 8);
    c.nsymbols = rd32(data + 12);
    optional = rd16(data + 16);
    c.section_table = 20 + (size_t)optional;
    need(size, c.section_table, (size_t)c.nsections * 40, "the COFF section table");
    if (!c.nsymbols)
        fail("the object has no symbol table");
    need(size, table, (size_t)c.nsymbols * 18, "the COFF symbol table");
    strtab = table + c.nsymbols * 18;
    need(size, strtab, 4, "the COFF string table");
    strsize = rd32(data + strtab);
    need(size, strtab, strsize, "the COFF string table");
    c.symbols = xcalloc((size_t)c.nsymbols * sizeof *c.symbols);
    for (i = 0; i < c.nsymbols;) {
        const u8 *e = data + table + (size_t)i * 18;
        u32 aux = e[17], j;
        Symbol *s = &c.symbols[i];
        if (rd32(e) == 0) {
            u32 off = rd32(e + 4);
            size_t at;
            if (off < 4 || off >= strsize)
                fail("invalid COFF symbol name offset");
            at = (size_t)strtab + off;
            if (!memchr(data + at, 0, size - at))
                fail("unterminated COFF symbol name");
            s->name = xstrdup((const char *)data + at);
        } else {
            size_t n = 0;
            while (n < 8 && e[n])
                n++;
            s->name = xstrndup((const char *)e, n);
        }
        s->value = rd32(e + 8);
        s->section = (int)(int16_t)(u16)rd16(e + 12);
        s->type = rd16(e + 14);
        s->storage = e[16];
        for (j = 1; j <= aux && i + j < c.nsymbols; j++)
            c.symbols[i + j].name = NULL;
        i += 1 + aux;
    }
    return c;
}

static void coff_section(const Coff *c, u32 number, Section *s)
{
    const u8 *h;
    if (number == 0 || number > c->nsections)
        fail("a symbol names a section outside the object");
    need(c->size, c->section_table + (size_t)(number - 1) * 40, 40, "a COFF section header");
    h = c->data + c->section_table + (size_t)(number - 1) * 40;
    s->raw_size = rd32(h + 16);
    s->raw_offset = rd32(h + 20);
    s->reloc_offset = rd32(h + 24);
    s->reloc_count = rd16(h + 32);
    s->characteristics = rd32(h + 36);
}

/* The section of the one function definition with this name. */
static u32 find_function(const Coff *c, const char *name)
{
    u32 k, found = 0;
    for (k = 0; k < c->nsymbols; k++) {
        const Symbol *s = &c->symbols[k];
        if (!s->name || strcmp(s->name, name) != 0 || s->type != SYM_FUNCTION)
            continue;
        if (s->value != 0 || s->section <= 0 || (s->storage != SYM_EXTERNAL && s->storage != SYM_STATIC))
            fail("%s is not a complete function at the start of its section", name);
        if (found)
            fail("%s is defined twice in the object", name);
        found = (u32)s->section;
    }
    if (!found)
        fail("the object does not define %s", name);
    return found;
}

/* ---- bindings ----------------------------------------------------------------------- */

typedef struct {
    char *name;
    u32 va;
    char *basis;
} Binding;

typedef struct {
    Binding *items;
    size_t count;
    size_t cap;
} Bindings;

static int find_binding(const Bindings *b, const char *name)
{
    size_t i;
    for (i = 0; i < b->count; i++)
        if (strcmp(b->items[i].name, name) == 0)
            return (int)i;
    return -1;
}

static void add_binding(Bindings *b, const char *name, u32 va, const char *basis)
{
    if (b->count == b->cap) {
        size_t cap = b->cap ? b->cap * 2 : 16;
        b->items = realloc(b->items, cap * sizeof *b->items);
        if (!b->items)
            fail("out of memory");
        b->cap = cap;
    }
    b->items[b->count].name = xstrdup(name);
    b->items[b->count].va = va;
    b->items[b->count].basis = xstrdup(basis);
    b->count++;
}

/* A switch label is the $L<digits> label the compiler places inside the function itself. */
static int is_switch_label(const char *name)
{
    size_t i;
    if (name[0] != '$' || name[1] != 'L' || !name[2])
        return 0;
    for (i = 2; name[i]; i++)
        if (name[i] < '0' || name[i] > '9')
            return 0;
    return 1;
}

/* The address a name carries: the last "_" followed by six to eight hex digits that end the name
   or precede an "@". It is a label for a reader and never the source of a VA; --check reports
   where it disagrees with the retail operand. */
static int name_address(const char *name, u32 *out)
{
    const char *p;
    int found = 0;
    for (p = name; *p; p++) {
        const char *q = p + 1;
        size_t n = 0;
        if (*p != '_')
            continue;
        while (hex_digit(q[n]) >= 0)
            n++;
        if (n >= 6 && n <= 8 && (q[n] == 0 || q[n] == '@')) {
            *out = (u32)strtoul(q, NULL, 16);
            found = 1;
        }
    }
    return found;
}

/* ---- compiling the record's build_command ------------------------------------------ */

static void split_words(const char *text, char ***words, size_t *count)
{
    size_t n = 0, cap = 16;
    const char *p = text;
    *words = xmalloc(cap * sizeof **words);
    for (;;) {
        const char *start;
        while (*p == ' ' || *p == '\t')
            p++;
        if (!*p)
            break;
        start = p;
        while (*p && *p != ' ' && *p != '\t')
            p++;
        if (memchr(start, '"', (size_t)(p - start)))
            fail("the build_command has a quoted argument; bindgen reads plain words only");
        if (n == cap) {
            cap *= 2;
            *words = realloc(*words, cap * sizeof **words);
            if (!*words)
                fail("out of memory");
        }
        (*words)[n++] = xstrndup(start, (size_t)(p - start));
    }
    *count = n;
}

static void backslashes(char *s)
{
    for (; *s; s++)
        if (*s == '/')
            *s = '\\';
}

/* Compiles the unit as its record says, in a fresh folder under local/ (git ignores it). The
   inputs are copied in first, as verify_build.py does, so the compiler sees only what the record
   names plus what it reaches. */
static u8 *compile_unit(const char *pc_root, const char *id, const char *cl, const char *command,
                        const char *toolchain, const List *inputs, size_t *size)
{
    char **words;
    size_t count, i;
    char local[PATH_CAP], folder[PATH_CAP], build[PATH_CAP], build_win[PATH_CAP], cl_dir[PATH_CAP];
    char output[PATH_CAP], object_path[PATH_CAP], log_path[PATH_CAP], to_dir[PATH_CAP];
    const char *target = NULL;
    int compile_only = 0, has_source = 0, status;
    Buf cmd;
    u8 *log, *object;
    size_t log_size;

    if (strncmp(toolchain, "Microsoft C/C++ ", 16) != 0)
        fail("the unit uses %s; bindgen compiles only Microsoft C/C++ units (use --object)", toolchain);
    split_words(command, &words, &count);
    if (count < 2 || !(strcmp(words[0], "cl") == 0 || strcmp(words[0], "cl.exe") == 0))
        fail("the build_command is not a Microsoft cl command");
    for (i = 1; i < count; i++) {
        if (strcmp(words[i], "/c") == 0)
            compile_only = 1;
        if (strncmp(words[i], "/Fo", 3) == 0) {
            if (words[i][3])
                target = words[i] + 3;
            else if (i + 1 < count)
                target = words[++i];
        }
    }
    if (!compile_only || !target)
        fail("the build_command must compile only (/c) and name its object (/Fo)");
    if (strncmp(target, "local/", 6) != 0 || !ends_with_ci(target, ".obj"))
        fail("the object must be local/*.obj");
    if (strlen(target) >= sizeof output)
        fail("the object path is too long");
    strcpy(output, target);

    /* Each unit builds in its own folder under local/, which git ignores. */
    join_path(pc_root, "../local", local);
    join_path(local, "bindgen-build", folder);
    join_path(folder, id, build);
    make_dirs(build);
    for (i = 0; i < inputs->count; i++) {
        char from[PATH_CAP], to[PATH_CAP];
        size_t n;
        u8 *data;
        join_path(pc_root, inputs->items[i], from);
        join_path(build, inputs->items[i], to);
        parent_of(to, to_dir);
        make_dirs(to_dir);
        data = read_file(from, &n);
        write_file(to, data, n);
        free(data);
        if (ends_with_ci(inputs->items[i], ".c") || ends_with_ci(inputs->items[i], ".cpp"))
            has_source = 1;
    }
    if (!has_source)
        fail("the inputs name no C or C++ source");
    join_path(build, output, object_path);
    parent_of(object_path, log_path);
    make_dirs(log_path);
    remove(object_path);
    join_path(build, "cl.log", log_path);

    strcpy(build_win, build);
    backslashes(build_win);
    parent_of(cl, cl_dir);
    backslashes(cl_dir);

    cmd.s = NULL;
    cmd.n = 0;
    cmd.cap = 0;
    buf_puts(&cmd, "cd /d \"");
    buf_puts(&cmd, build_win);
    buf_puts(&cmd, "\" && set \"VSLANG=1033\" && set \"CL=\" && set \"_CL_=\" && set \"PATH=");
    buf_puts(&cmd, cl_dir);
    buf_puts(&cmd, ";%PATH%\" && \"");
    buf_puts(&cmd, cl);
    buf_puts(&cmd, "\"");
    for (i = 1; i < count; i++) {
        buf_putc(&cmd, ' ');
        buf_puts(&cmd, words[i]);
    }
    buf_puts(&cmd, " > cl.log 2>&1");
    status = system(cmd.s);
    if (status != 0) {
        log = read_file(log_path, &log_size);
        fprintf(stderr, "%s", (const char *)log);
        fail("the compiler failed for %s (status %d)", id, status);
    }
    object = read_file(object_path, size);
    return object;
}

/* ---- deriving the bindings ---------------------------------------------------------- */

typedef struct {
    const char *symbol;
    u32 function_va;
    u32 unit_size;
    const u8 *object_bytes;
    const u8 *retail;     /* the retail bytes of the function */
    const u8 *image;      /* the whole retail image */
    size_t image_size;
    const FunctionMap *map;
    const Range *code;    /* VA ranges of the manifest's code sections */
    size_t ncode;
} Unit;

static void derive_bindings(const Unit *unit, const Coff *c, const Section *section, u32 section_number,
                            Bindings *out)
{
    u32 nsyms = c->nsymbols, k;
    const u8 *rel;
    u8 *covered;
    size_t j;

    if (section->raw_size != unit->unit_size)
        fail("%s is %u bytes in the object; the record says %u", unit->symbol, section->raw_size, unit->unit_size);
    if (!(section->characteristics & SCN_CODE) || !(section->characteristics & SCN_EXECUTE))
        fail("%s is not in an executable section", unit->symbol);
    for (k = 0; k < nsyms; k++) {
        const Symbol *s = &c->symbols[k];
        /* C++ catch blocks ($L labels) and frame handlers belong to their function. */
        if (s->name && s->section == (int)section_number && s->type == SYM_FUNCTION
            && strcmp(s->name, unit->symbol) != 0 && !is_switch_label(s->name)
            && strncmp(s->name, "__ehhandler$", 12) != 0)
            fail("the section of %s also holds the function %s", unit->symbol, s->name);
    }
    if (section->reloc_count == 0xffff)
        fail("extended relocation counts are not supported");
    need(c->size, section->reloc_offset, (size_t)section->reloc_count * 10, "the relocation table");
    rel = c->data + section->reloc_offset;

    covered = xcalloc(unit->unit_size);
    for (k = 0; k < section->reloc_count; k++) {
        u32 site = rd32(rel + (size_t)k * 10);
        if (site > unit->unit_size || unit->unit_size - site < 4)
            fail("%s has a relocation outside its function", unit->symbol);
        for (j = 0; j < 4; j++) {
            if (covered[site + j])
                fail("%s has overlapping relocations", unit->symbol);
            covered[site + j] = 1;
        }
    }

    /* Everything outside a relocation field must already be the retail byte. */
    for (j = 0; j < unit->unit_size; j++)
        if (!covered[j] && unit->object_bytes[j] != unit->retail[j])
            fail("%s differs from retail at +0x%x outside its relocations: not a byte match",
                 unit->symbol, (unsigned)j);

    for (k = 0; k < section->reloc_count; k++) {
        const u8 *r = rel + (size_t)k * 10;
        u32 site = rd32(r), index = rd32(r + 4), type = rd16(r + 8);
        u32 addend, retail_value, target;
        const Symbol *sym;
        int listed = 0, tib;
        char basis[640];
        if (type != REL_DIR32 && type != REL_REL32)
            fail("%s uses relocation type 0x%x, which bindgen does not decode", unit->symbol, (unsigned)type);
        if (index >= nsyms || !c->symbols[index].name)
            fail("%s has a relocation to an invalid symbol", unit->symbol);
        sym = &c->symbols[index];
        addend = rd32(unit->object_bytes + site);
        retail_value = rd32(unit->retail + site);
        /* The linker stores the target plus the addend (DIR32), or the target plus the addend
           less the field's own end (REL32). The retail field holds the same sum, so the target
           is recovered from it. */
        if (type == REL_REL32)
            target = retail_value - addend + (unit->function_va + site + 4);
        else
            target = retail_value - addend;
        /* The C runtime's __except_list is the absolute thread-information-block offset 0 that the
           code reads through FS; it is not a VA in the image. */
        tib = type == REL_DIR32 && sym->section == 0 && strcmp(sym->name, "__except_list") == 0;

        if (sym->section == (int)section_number && sym->storage == SYM_STATIC && sym->type == 0
            && is_switch_label(sym->name)) {
            if (type != REL_DIR32 || addend != 0 || sym->value >= unit->unit_size
                || target != unit->function_va + sym->value)
                fail("switch label %s does not match the retail bytes", sym->name);
            continue;
        }
        if (sym->section == -1)
            fail("%s is an absolute symbol, which bindgen does not decode", sym->name);
        if (sym->section == 0) {
            if (sym->value != 0 || sym->storage != SYM_EXTERNAL)
                fail("external %s is a common or unusual symbol", sym->name);
        } else {
            if (sym->storage == SYM_STATIC && sym->type != SYM_FUNCTION)
                fail("%s refers to static data, which the verifier cannot link", sym->name);
            if (sym->storage != SYM_STATIC && sym->storage != SYM_EXTERNAL)
                fail("%s has an unsupported storage class", sym->name);
            if (sym->storage == SYM_EXTERNAL && sym->value != 0)
                fail("%s is not at the start of its section", sym->name);
            if (sym->storage == SYM_STATIC && addend != 0)
                fail("%s is a private function referenced with an addend", sym->name);
        }
        if (type == REL_REL32) {
            u32 file = target - IMAGE_BASE;
            int in_code = 0;
            size_t range;
            if (target < IMAGE_BASE)
                fail("%s is called at VA 0x%08" PRIx32 ", below the image base", sym->name, target);
            for (range = 0; range < unit->ncode; range++)
                if (target >= unit->code[range].start && target < unit->code[range].end)
                    in_code = 1;
            if (!in_code)
                fail("%s is called at VA 0x%08" PRIx32 ", outside the code sections", sym->name, target);
            listed = map_has_entry(unit->map, file);
            if (!listed) {
                /* The map is Ghidra's and can miss a function; the retail call still proves the
                   target is code. A target inside another function's body is a real error. */
                if (in_body(unit->map, file))
                    fail("%s is called at VA 0x%08" PRIx32 ", inside another function", sym->name, target);
                fprintf(stderr, "bindgen: note: %s is called at VA 0x%08" PRIx32
                                ", which the function map does not list\n", sym->name, target);
            }
        } else if (tib) {
            if (target != 0)
                fail("%s is referenced at VA 0x%08" PRIx32 ", not the thread information block offset 0",
                     sym->name, target);
        } else if (target < IMAGE_BASE || !in_image(unit->image, unit->image_size, target)) {
            fail("%s is referenced at VA 0x%08" PRIx32 ", outside the image", sym->name, target);
        }
        {
            int existing = find_binding(out, sym->name);
            if (existing >= 0) {
                if (out->items[existing].va != target)
                    fail("%s refers to two addresses in one unit", sym->name);
                continue;
            }
        }
        if (type == REL_REL32)
            snprintf(basis, sizeof basis,
                     "Call or jump at +0x%x of %s; the retail operand gives VA 0x%08" PRIx32
                     " (file offset 0x%" PRIx32 "), %s.",
                     (unsigned)site, unit->symbol, target, target - IMAGE_BASE,
                     listed ? "a function entry in the function map"
                            : "a code-section call target that the function map does not list");
        else if (tib)
            snprintf(basis, sizeof basis,
                     "Absolute thread-information-block offset at +0x%x of %s, read through FS "
                     "(the C runtime's __except_list).", (unsigned)site, unit->symbol);
        else
            snprintf(basis, sizeof basis,
                     "Absolute operand at +0x%x of %s; the retail operand gives VA 0x%08" PRIx32 ".",
                     (unsigned)site, unit->symbol, target);
        add_binding(out, sym->name, target, basis);
    }
    free(covered);
}

/* ---- output ------------------------------------------------------------------------- */

static void json_string(FILE *out, const char *s)
{
    fputc('"', out);
    for (; *s; s++) {
        unsigned char c = (unsigned char)*s;
        if (c == '"' || c == '\\')
            fprintf(out, "\\%c", c);
        else if (c < 0x20)
            fprintf(out, "\\u%04x", (unsigned)c);
        else
            fputc(c, out);
    }
    fputc('"', out);
}

static void print_fragment(const char *id, const List *inputs, const Bindings *bindings)
{
    size_t i;
    printf("{\n  \"id\": ");
    json_string(stdout, id);
    printf(",\n  \"inputs\": [\n");
    for (i = 0; i < inputs->count; i++) {
        printf("    ");
        json_string(stdout, inputs->items[i]);
        printf("%s\n", i + 1 < inputs->count ? "," : "");
    }
    printf("  ]");
    if (bindings->count) {
        printf(",\n  \"link_bindings\": {\n");
        for (i = 0; i < bindings->count; i++) {
            const Binding *b = &bindings->items[i];
            printf("    ");
            json_string(stdout, b->name);
            printf(": {\n      \"va\": %" PRIu32 ",\n      \"basis\": ", b->va);
            json_string(stdout, b->basis);
            printf("\n    }%s\n", i + 1 < bindings->count ? "," : "");
        }
        printf("  }");
    }
    printf("\n}\n");
}

/* Compares the derived inputs and bindings with the record and prints each difference. Returns
   the number of differences; notes (order, name labels) are not differences. */
static int check_fragment(const char *id, const Json *record, const List *inputs, const Bindings *bindings)
{
    const Json *ri = jget(record, "inputs");
    const Json *rb = jget(record, "link_bindings");
    int input_diffs = 0, binding_diffs = 0;
    size_t i, j;

    if (!ri || ri->kind != J_ARRAY)
        fail("%s: the record has no inputs array", id);
    for (i = 0; i < inputs->count; i++) {
        int found = 0;
        for (j = 0; j < ri->count; j++)
            if (strcmp(ri->items[j]->text, inputs->items[i]) == 0)
                found = 1;
        if (!found) {
            printf("inputs: derived only: %s\n", inputs->items[i]);
            input_diffs++;
        }
    }
    for (j = 0; j < ri->count; j++) {
        if (ri->items[j]->kind != J_STRING)
            fail("%s: an input in the record is not a string", id);
        if (!list_has(inputs, ri->items[j]->text)) {
            printf("inputs: record only: %s\n", ri->items[j]->text);
            input_diffs++;
        }
    }
    if (!input_diffs) {
        int same_order = ri->count == inputs->count;
        for (j = 0; same_order && j < ri->count; j++)
            same_order = strcmp(ri->items[j]->text, inputs->items[j]) == 0;
        printf("inputs: same (%zu)\n", inputs->count);
        if (!same_order)
            printf("note: the inputs are listed in a different order\n");
    }

    for (i = 0; i < bindings->count; i++) {
        const Binding *b = &bindings->items[i];
        const Json *recorded = rb ? jget(rb, b->name) : NULL;
        if (!recorded) {
            printf("link_bindings: derived only: %s (VA 0x%08" PRIx32 ")\n", b->name, b->va);
            binding_diffs++;
        } else {
            u32 recorded_va = ju32(jget(recorded, "va"), "the record's va");
            if (recorded_va != b->va) {
                printf("link_bindings: va differs: %s derived 0x%08" PRIx32 " record 0x%08" PRIx32 "\n",
                       b->name, b->va, recorded_va);
                binding_diffs++;
            }
        }
    }
    if (rb && rb->kind == J_OBJECT)
        for (j = 0; j < rb->count; j++)
            if (find_binding(bindings, rb->keys[j]) < 0) {
                printf("link_bindings: record only: %s\n", rb->keys[j]);
                binding_diffs++;
            }
    if (!binding_diffs)
        printf("link_bindings: %s (%zu)\n", bindings->count ? "same" : "none", bindings->count);

    for (i = 0; i < bindings->count; i++) {
        u32 suffix;
        if (name_address(bindings->items[i].name, &suffix)
            && suffix != bindings->items[i].va - IMAGE_BASE)
            printf("note: %s carries 0x%" PRIx32 " in its name; its retail target is file offset 0x%" PRIx32
                   " (a label, not the address)\n",
                   bindings->items[i].name, suffix, bindings->items[i].va - IMAGE_BASE);
    }
    return input_diffs + binding_diffs;
}

/* ---- main --------------------------------------------------------------------------- */

static const Json *find_record(const Json *manifest, const char *pc_root, const char *unit_id, Json **owner)
{
    const Json *units = jget(manifest, "units");
    const Json *files = jget(manifest, "unit_files");
    const Json *found = NULL;
    size_t i, k;
    *owner = NULL;
    if (units && units->kind == J_ARRAY)
        for (i = 0; i < units->count; i++) {
            const Json *id = jget(units->items[i], "id");
            if (id && strcmp(jstr(id, "a unit id"), unit_id) == 0) {
                if (found)
                    fail("unit %s appears twice", unit_id);
                found = units->items[i];
            }
        }
    if (files && files->kind == J_ARRAY)
        for (i = 0; i < files->count; i++) {
            char path[PATH_CAP], normal[PATH_CAP];
            Json *rows;
            if (!normalize_relative(jstr(files->items[i], "a unit file"), normal))
                fail("invalid unit file name in the manifest");
            join_path(pc_root, normal, path);
            rows = json_load(path);
            if (rows->kind != J_ARRAY)
                fail("%s is not a list of units", path);
            for (k = 0; k < rows->count; k++) {
                const Json *id = jget(rows->items[k], "id");
                if (id && strcmp(jstr(id, "a unit id"), unit_id) == 0) {
                    if (found)
                        fail("unit %s appears twice", unit_id);
                    found = rows->items[k];
                    *owner = rows;
                }
            }
            if (!*owner || *owner != rows)
                json_free(rows);
        }
    return found;
}

int main(int argc, char **argv)
{
    const char *game = NULL, *image_path = NULL, *cl = NULL, *object_path = NULL;
    const char *manifest_path = NULL, *unit_id = NULL;
    int check = 0, positional = 0, i;
    Json *manifest, *owner = NULL;
    const Json *record, *image, *sections, *unit_json;
    const char *target_id, *sha_text, *file_text, *command, *toolchain, *symbol, *source = NULL;
    char pc_root[PATH_CAP], config_dir[PATH_CAP], map_path[PATH_CAP], image_file[PATH_CAP];
    char computed[65], source_path[PATH_CAP];
    u8 digest[32];
    size_t image_len = 0, object_len = 0, word_count = 0, w;
    u32 image_size, offset, size, section_number;
    u8 *image_bytes, *object;
    FunctionMap map;
    List inputs;
    Bindings bindings;
    char **words;
    Coff coff;
    Section section;
    Unit unit;
    Range *code;
    size_t ncode = 0;
    int differences;

    for (i = 1; i < argc; i++) {
        const char *arg = argv[i];
        if (strcmp(arg, "--check") == 0)
            check = 1;
        else if (strcmp(arg, "--game") == 0 && i + 1 < argc)
            game = argv[++i];
        else if (strcmp(arg, "--image") == 0 && i + 1 < argc)
            image_path = argv[++i];
        else if (strcmp(arg, "--cl") == 0 && i + 1 < argc)
            cl = argv[++i];
        else if (strcmp(arg, "--object") == 0 && i + 1 < argc)
            object_path = argv[++i];
        else if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0 || arg[0] == '-')
            usage();
        else if (positional == 0) {
            manifest_path = arg;
            positional++;
        } else if (positional == 1) {
            unit_id = arg;
            positional++;
        } else
            usage();
    }
    if (positional != 2)
        usage();
    if ((image_path == NULL) == (game == NULL))
        fail("pass exactly one of --game or --image");
    if ((cl == NULL) == (object_path == NULL))
        fail("pass exactly one of --cl or --object");

    /* The manifest lives in <pc>/config/, so the project root is two folders up. */
    parent_of(manifest_path, config_dir);
    parent_of(config_dir, pc_root);
    manifest = json_load(manifest_path);
    target_id = jstr(jreq(manifest, "id"), "the manifest id");
    image = jreq(manifest, "image");
    sha_text = jstr(jreq(image, "sha256"), "the image sha256");
    if (strlen(sha_text) != 64)
        fail("the manifest's image sha256 is malformed");
    image_size = ju32(jreq(image, "size"), "the image size");
    file_text = jstr(jreq(manifest, "file"), "the manifest file");
    sections = jreq(image, "executable_sections");
    for (w = 0; w < sections->count; w++) {
        const Json *s = sections->items[w];
        u32 address = ju32(jreq(s, "address"), "a section address");
        u32 section_offset = ju32(jreq(s, "offset"), "a section offset");
        const Json *flag_json = jreq(s, "code");
        if (flag_json->kind == J_BOOL && flag_json->flag && address - section_offset != IMAGE_BASE)
            fail("a code section of %s is not at VA 0x%08" PRIx32 " + file offset: bindgen supports the Campaign layout only",
                 target_id, IMAGE_BASE);
    }

    record = find_record(manifest, pc_root, unit_id, &owner);
    if (!record)
        fail("no unit %s in %s", unit_id, manifest_path);
    unit_json = record;
    offset = ju32(jreq(unit_json, "offset"), "the record's offset");
    size = ju32(jreq(unit_json, "size"), "the record's size");
    symbol = jstr(jreq(unit_json, "rebuilt_symbol"), "the record's rebuilt_symbol");
    command = jstr(jreq(unit_json, "build_command"), "the record's build_command");
    toolchain = jstr(jreq(unit_json, "toolchain"), "the record's toolchain");

    if (image_path)
        strcpy(image_file, image_path);
    else
        join_path(game, file_text, image_file);
    image_bytes = read_file(image_file, &image_len);
    if (image_len != image_size)
        fail("%s is %zu bytes; the manifest's image is %u", image_file, image_len, (unsigned)image_size);
    sha256(image_bytes, image_len, digest);
    hex_digest(digest, computed);
    if (strcmp(computed, sha_text) != 0)
        fail("the reference binary differs from the locked build");
    check_image_base(image_bytes, image_len);
    if (offset > image_len || size > image_len - offset)
        fail("the unit lies outside the image");
    code = xcalloc(sections->count * sizeof *code);
    for (w = 0; w < sections->count; w++) {
        const Json *s = sections->items[w];
        const Json *is_code = jreq(s, "code");
        if (is_code->kind == J_BOOL && is_code->flag) {
            code[ncode].start = ju32(jreq(s, "address"), "a section address");
            code[ncode].end = code[ncode].start + ju32(jreq(s, "size"), "a section size");
            ncode++;
        }
    }

    join_path(pc_root, "function_maps", config_dir);
    join_path(config_dir, target_id, map_path);
    strcat(map_path, ".txt");
    load_function_map(map_path, sha_text, &map);

    split_words(command, &words, &word_count);
    for (w = 0; w < word_count; w++)
        if (ends_with_ci(words[w], ".c") || ends_with_ci(words[w], ".cpp"))
            source = words[w];
    if (!source || !normalize_relative(source, source_path))
        fail("the build_command names no project C or C++ source");
    inputs.items = NULL;
    inputs.count = 0;
    inputs.cap = 0;
    list_add(&inputs, source_path);
    collect_inputs(pc_root, source_path, &inputs, 0);

    if (object_path)
        object = read_file(object_path, &object_len);
    else
        object = compile_unit(pc_root, unit_id, cl, command, toolchain, &inputs, &object_len);
    coff = coff_open(object, object_len);
    section_number = find_function(&coff, symbol);
    coff_section(&coff, section_number, &section);
    need(coff.size, section.raw_offset, size, "the function's bytes");

    unit.symbol = symbol;
    unit.function_va = IMAGE_BASE + offset;
    unit.unit_size = size;
    unit.object_bytes = coff.data + section.raw_offset;
    unit.retail = image_bytes + offset;
    unit.image = image_bytes;
    unit.image_size = image_len;
    unit.map = &map;
    unit.code = code;
    unit.ncode = ncode;
    bindings.items = NULL;
    bindings.count = 0;
    bindings.cap = 0;
    derive_bindings(&unit, &coff, &section, section_number, &bindings);

    if (check) {
        differences = check_fragment(unit_id, record, &inputs, &bindings);
        printf("%s %s\n", differences ? "DIFF" : "OK", unit_id);
        return differences ? 1 : 0;
    }
    print_fragment(unit_id, &inputs, &bindings);
    return 0;
}
