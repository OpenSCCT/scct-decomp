/*
 * symindex - turn symbol-bearing sibling builds into a name-evidence index.
 *
 *   symindex elf FILE [--label NAME]     symbols of a 32-bit LE MIPS ELF
 *   symindex mwmap FILE [--label NAME]   closure of a CodeWarrior link map
 *   symindex demangle NAME...            demangle names given as arguments
 *   symindex mkelf FILE                  write the synthetic ELF the tests use
 *   symindex --selftest                  run the built-in demangler checks
 *
 * Rows go to stdout, tab-separated, one per symbol:
 *
 *   elf     label kind address size binding mangled demangled
 *   mwmap   label kind binding library object mangled demangled
 *
 * Two mangling schemes are decoded: Metrowerks CodeWarrior (PS2 builds) and
 * the SN Systems "__0" scheme (PSP build).  A name that does not parse
 * completely is printed unchanged; the demanglers never guess.  README.md
 * lists the exact forms.
 *
 * Build:  cc -std=c99 -O2 -Wall -Wextra -o symindex tools/evidence/symindex.c
 *
 * Standard library only.  The one exception is Windows, where stdout is put
 * in binary mode so that rows end in "\n" on every host.
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

#define TEXT_LIMIT 262144UL       /* longest string a text buffer may hold */
#define DEPTH_LIMIT 64            /* deepest type nesting the parsers follow */
#define ARG_LIMIT 64              /* most arguments kept for back-references */
#define FILE_LIMIT 1073741824UL   /* largest ELF file read into memory */

/* ------------------------------------------------------------------ */
/* Text buffers                                                       */
/* ------------------------------------------------------------------ */

struct pool;

/* A growable string that belongs to a pool and is freed with it. */
struct text {
    char *data;
    size_t len;
    size_t cap;
    struct pool *pool;
    struct text *next;
};

/* Owner of a group of text buffers; records whether any of them overflowed. */
struct pool {
    struct text *head;
    int overflow;
};

/* Report an unrecoverable error and stop. */
static void fatal(const char *message)
{
    fprintf(stderr, "symindex: %s\n", message);
    exit(2);
}

/* Prepare an empty pool. */
static void pool_init(struct pool *pool)
{
    pool->head = NULL;
    pool->overflow = 0;
}

/* Free every text buffer that was taken from the pool. */
static void pool_free(struct pool *pool)
{
    struct text *t = pool->head;

    while (t != NULL) {
        struct text *next = t->next;
        free(t->data);
        free(t);
        t = next;
    }
    pool->head = NULL;
}

/* Take a new empty text buffer from the pool. */
static struct text *text_new(struct pool *pool)
{
    struct text *t = (struct text *)malloc(sizeof(*t));

    if (t == NULL)
        fatal("out of memory");
    t->data = NULL;
    t->len = 0;
    t->cap = 0;
    t->pool = pool;
    t->next = pool->head;
    pool->head = t;
    return t;
}

/* Return the contents as a C string (never NULL). */
static const char *text_str(const struct text *t)
{
    return t->data != NULL ? t->data : "";
}

/* Empty the buffer but keep its storage. */
static void text_clear(struct text *t)
{
    t->len = 0;
    if (t->data != NULL)
        t->data[0] = '\0';
}

/* Append n bytes; past TEXT_LIMIT the data is dropped and the pool is marked. */
static void text_add_n(struct text *t, const char *s, size_t n)
{
    if (n > TEXT_LIMIT || t->len + n + 1 > TEXT_LIMIT) {
        t->pool->overflow = 1;
        return;
    }
    if (t->len + n + 1 > t->cap) {
        size_t cap = t->cap != 0 ? t->cap : 64;
        char *data;

        while (cap < t->len + n + 1)
            cap *= 2;
        data = (char *)realloc(t->data, cap);
        if (data == NULL)
            fatal("out of memory");
        t->data = data;
        t->cap = cap;
    }
    memcpy(t->data + t->len, s, n);
    t->len += n;
    t->data[t->len] = '\0';
}

/* Append a C string. */
static void text_add(struct text *t, const char *s)
{
    text_add_n(t, s, strlen(s));
}

/* Append one character. */
static void text_add_char(struct text *t, char ch)
{
    text_add_n(t, &ch, 1);
}

/* Append the contents of another text buffer. */
static void text_add_text(struct text *t, const struct text *other)
{
    text_add_n(t, text_str(other), other->len);
}

/* ------------------------------------------------------------------ */
/* Pieces shared by both demanglers                                   */
/* ------------------------------------------------------------------ */

/* How a parsed type combines with a pointer or reference wrapped around it. */
enum type_kind {
    KIND_PLAIN,       /* builtin, class, pointer or reference */
    KIND_FUNCTION,    /* function type: a pointer to it needs "(*)" */
    KIND_ARRAY        /* array type: a pointer to it needs " (*)" */
};

/* A read position inside a mangled name. */
struct cursor {
    const char *p;
    const char *end;
};

/* A decoded template argument kept for later back-references (SN scheme). */
struct template_arg {
    struct text *pre;       /* text before the declarator position */
    struct text *post;      /* text after the declarator position */
    int kind;               /* enum type_kind */
    int is_constant;        /* an integer constant, not a type */
    int is_indirect;        /* the type is a pointer or reference */
};

/* State of one demangling attempt. */
struct parser {
    struct pool pool;
    int depth;                              /* current nesting of types */
    int list_count;                         /* SN: template lists on the declarator */
    const char *list_owner;                 /* SN: template the first list belongs to */
    int targ_count;                         /* SN: arguments of that first list */
    struct template_arg targs[ARG_LIMIT];   /* SN: those arguments */
};

/* Prepare a parser for one name. */
static void parser_init(struct parser *ps)
{
    pool_init(&ps->pool);
    ps->depth = 0;
    ps->list_count = 0;
    ps->list_owner = NULL;
    ps->targ_count = 0;
}

/* Number of characters left under the cursor. */
static size_t cur_left(const struct cursor *c)
{
    return (size_t)(c->end - c->p);
}

/* Character under the cursor, or 0 at the end. */
static int cur_peek(const struct cursor *c)
{
    return c->p < c->end ? (unsigned char)*c->p : 0;
}

/* Character n places after the cursor, or 0 past the end. */
static int cur_peek_at(const struct cursor *c, size_t n)
{
    return cur_left(c) > n ? (unsigned char)c->p[n] : 0;
}

/* True for the decimal digits. */
static int is_digit(int ch)
{
    return ch >= '0' && ch <= '9';
}

/* True for the ASCII letters. */
static int is_letter(int ch)
{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

/* True if the n bytes at s form a C identifier. */
static int is_identifier(const char *s, size_t n)
{
    size_t i;

    if (n == 0 || is_digit((unsigned char)s[0]))
        return 0;
    for (i = 0; i < n; i++) {
        int ch = (unsigned char)s[i];
        if (!is_letter(ch) && !is_digit(ch) && ch != '_')
            return 0;
    }
    return 1;
}

/* Name of a builtin type code shared by both schemes, or NULL. */
static const char *builtin_name(int ch)
{
    switch (ch) {
    case 'v': return "void";
    case 'c': return "char";
    case 's': return "short";
    case 'i': return "int";
    case 'l': return "long";
    case 'x': return "long long";
    case 'f': return "float";
    case 'd': return "double";
    case 'b': return "bool";
    case 'w': return "wchar_t";
    case 'e': return "...";
    default:  return NULL;
    }
}

/* One operator code of the cfront family and the text it stands for. */
struct operator_code {
    const char *code;
    const char *text;
};

/* Operator codes; three-letter codes come first so they are tried first. */
static const struct operator_code operator_codes[] = {
    { "apl", "operator+=" },  { "ami", "operator-=" },  { "amu", "operator*=" },
    { "adv", "operator/=" },  { "amd", "operator%=" },  { "aad", "operator&=" },
    { "aor", "operator|=" },  { "aer", "operator^=" },  { "als", "operator<<=" },
    { "ars", "operator>>=" }, { "nwa", "operator new[]" },
    { "dla", "operator delete[]" },
    { "as", "operator=" },    { "eq", "operator==" },   { "ne", "operator!=" },
    { "pl", "operator+" },    { "mi", "operator-" },    { "ml", "operator*" },
    { "dv", "operator/" },    { "md", "operator%" },    { "vc", "operator[]" },
    { "cl", "operator()" },   { "nw", "operator new" }, { "dl", "operator delete" },
    { "ls", "operator<<" },   { "rs", "operator>>" },   { "lt", "operator<" },
    { "gt", "operator>" },    { "le", "operator<=" },   { "ge", "operator>=" },
    { "aa", "operator&&" },   { "oo", "operator||" },   { "nt", "operator!" },
    { "co", "operator~" },    { "pp", "operator++" },   { "mm", "operator--" },
    { "rf", "operator->" },   { "ad", "operator&" },    { "or", "operator|" },
    { "er", "operator^" },    { "cm", "operator," },    { "rm", "operator->*" }
};

#define OPERATOR_COUNT (sizeof(operator_codes) / sizeof(operator_codes[0]))

/* Text of the operator whose code is exactly the n bytes at s, or NULL. */
static const char *operator_text(const char *s, size_t n)
{
    size_t i;

    for (i = 0; i < OPERATOR_COUNT; i++) {
        const char *code = operator_codes[i].code;
        if (strlen(code) == n && memcmp(code, s, n) == 0)
            return operator_codes[i].text;
    }
    return NULL;
}

/* Append " const" and " volatile" as requested. */
static void add_cv_suffix(struct text *t, int is_const, int is_volatile)
{
    if (is_const)
        text_add(t, " const");
    if (is_volatile)
        text_add(t, " volatile");
}

/* Append "const " and "volatile " as requested. */
static void add_cv_prefix(struct text *t, int is_const, int is_volatile)
{
    if (is_const)
        text_add(t, "const ");
    if (is_volatile)
        text_add(t, "volatile ");
}

/*
 * Wrap a pointer ("*"), reference ("&") or member pointer ("Class::*") around
 * the inner type already written to pre, whose own suffix is inner_post.
 */
static void wrap_indirection(struct text *pre, struct text *post,
                             const struct text *inner_post, int inner_kind,
                             const char *mark, int is_const, int is_volatile)
{
    if (inner_kind == KIND_FUNCTION) {
        text_add(pre, "(");
    } else if (inner_kind == KIND_ARRAY) {
        text_add(pre, " (");
    } else if (strlen(mark) > 1) {
        text_add(pre, " ");
    }
    text_add(pre, mark);
    add_cv_suffix(pre, is_const, is_volatile);
    if (inner_kind != KIND_PLAIN)
        text_add(post, ")");
    text_add_text(post, inner_post);
}

/*
 * Finish a function type: ret_pre/ret_post hold the return type and args the
 * decoded argument list.  The result is split around the place where a
 * declarator such as "(*)" goes.
 */
static void build_function_type(struct text *pre, struct text *post,
                                const struct text *ret_pre,
                                const struct text *ret_post,
                                const struct text *args, int is_const)
{
    text_add_text(pre, ret_pre);
    if (ret_post->len == 0)
        text_add(pre, " ");
    text_add(post, "(");
    text_add_text(post, args);
    text_add(post, ")");
    if (is_const)
        text_add(post, " const");
    text_add_text(post, ret_post);
}

/* Append one more entry (pre, then post unless NULL) to a comma-separated list. */
static void list_add(struct text *list, const struct text *pre,
                     const struct text *post)
{
    if (list->len != 0)
        text_add(list, ", ");
    text_add_text(list, pre);
    if (post != NULL)
        text_add_text(list, post);
}

/* Write "[ret ]scope::name(args)[ const][ volatile]" for a function. */
static void compose_function(struct text *out, const struct text *ret,
                             const struct text *scope, const struct text *name,
                             const struct text *args, int is_const,
                             int is_volatile)
{
    if (ret != NULL && ret->len != 0) {
        text_add_text(out, ret);
        text_add(out, " ");
    }
    if (scope != NULL && scope->len != 0) {
        text_add_text(out, scope);
        text_add(out, "::");
    }
    text_add_text(out, name);
    text_add(out, "(");
    text_add_text(out, args);
    text_add(out, ")");
    add_cv_suffix(out, is_const, is_volatile);
}

/* ------------------------------------------------------------------ */
/* Scheme A: Metrowerks CodeWarrior                                   */
/* ------------------------------------------------------------------ */

static int cw_type(struct parser *ps, struct cursor *c, struct text *pre,
                   struct text *post, int *kind);

/* Read a decimal number of at most six digits. */
static int cw_number(struct cursor *c, unsigned long *value)
{
    unsigned long v = 0;
    int digits = 0;

    while (is_digit(cur_peek(c))) {
        if (++digits > 6)
            return 0;
        v = v * 10 + (unsigned long)(cur_peek(c) - '0');
        c->p++;
    }
    *value = v;
    return digits > 0;
}

/* Decode the comma-separated template arguments between p and end. */
static int cw_template_args(struct parser *ps, const char *p, const char *end,
                            struct text *out)
{
    struct cursor c;
    struct text *list = text_new(&ps->pool);

    c.p = p;
    c.end = end;
    for (;;) {
        struct text *pre = text_new(&ps->pool);
        struct text *post = text_new(&ps->pool);
        const char *q = c.p;
        int kind;

        /* An integer constant is a run of digits that ends the argument. */
        if (q < c.end && *q == '-')
            q++;
        while (q < c.end && is_digit((unsigned char)*q))
            q++;
        if (q > c.p && is_digit((unsigned char)q[-1])
            && (q == c.end || *q == ',')) {
            text_add_n(pre, c.p, (size_t)(q - c.p));
            c.p = q;
        } else if (!cw_type(ps, &c, pre, post, &kind)) {
            return 0;
        }
        list_add(list, pre, post);
        if (c.p == c.end)
            break;
        if (*c.p != ',')
            return 0;
        c.p++;
    }
    text_add(out, "<");
    text_add_text(out, list);
    text_add(out, ">");
    return 1;
}

/*
 * Decode a length-counted name such as "7UObject" or "11Box<3Bar,0>".
 * base receives the name without template arguments (may be NULL).
 */
static int cw_simple_name(struct parser *ps, struct cursor *c, struct text *out,
                          struct text *base)
{
    unsigned long len;
    const char *name;
    const char *name_end;
    const char *angle;

    if (!cw_number(c, &len) || len == 0 || len > cur_left(c))
        return 0;
    name = c->p;
    name_end = name + len;
    c->p = name_end;
    angle = (const char *)memchr(name, '<', len);
    if (angle == NULL)
        angle = name_end;
    if (angle == name)
        return 0;
    text_add_n(out, name, (size_t)(angle - name));
    if (base != NULL) {
        text_clear(base);
        text_add_n(base, name, (size_t)(angle - name));
    }
    if (angle == name_end)
        return 1;
    if (name_end[-1] != '>' || name_end - angle < 3)
        return 0;
    return cw_template_args(ps, angle + 1, name_end - 1, out);
}

/* Decode a class name, plain or qualified ("Q23std7__nInit"). */
static int cw_class(struct parser *ps, struct cursor *c, struct text *out,
                    struct text *base)
{
    int count;
    int i;

    if (cur_peek(c) != 'Q')
        return cw_simple_name(ps, c, out, base);
    count = cur_peek_at(c, 1) - '0';
    if (count < 1 || count > 9)
        return 0;
    c->p += 2;
    for (i = 0; i < count; i++) {
        if (i != 0)
            text_add(out, "::");
        if (!cw_simple_name(ps, c, out, base))
            return 0;
    }
    return 1;
}

/* Decode argument types up to the end of the cursor or a '_'. */
static int cw_args(struct parser *ps, struct cursor *c, struct text *out)
{
    int count = 0;
    int saw_void = 0;
    int saw_ellipsis = 0;

    while (c->p < c->end && *c->p != '_') {
        struct text *pre = text_new(&ps->pool);
        struct text *post = text_new(&ps->pool);
        int kind;

        if (saw_ellipsis)
            return 0;
        saw_ellipsis = *c->p == 'e';
        if (*c->p == 'v')
            saw_void = 1;
        if (!cw_type(ps, c, pre, post, &kind))
            return 0;
        list_add(out, pre, post);
        count++;
    }
    /* "void" only stands alone, and nothing follows "...". */
    return count > 0 && (!saw_void || count == 1);
}

/* Decode one type; the work behind cw_type, which tracks the nesting depth. */
static int cw_type_inner(struct parser *ps, struct cursor *c, struct text *pre,
                         struct text *post, int *kind)
{
    int is_const = 0, is_volatile = 0, is_unsigned = 0, is_signed = 0;
    int ch;

    *kind = KIND_PLAIN;
    for (;;) {
        ch = cur_peek(c);
        if (ch == 'C' && !is_const)
            is_const = 1;
        else if (ch == 'V' && !is_volatile)
            is_volatile = 1;
        else if (ch == 'U' && !is_unsigned && !is_signed)
            is_unsigned = 1;
        else if (ch == 'S' && !is_unsigned && !is_signed)
            is_signed = 1;
        else
            break;
        c->p++;
    }

    if (ch == 'P' || ch == 'R') {
        struct text *inner_post = text_new(&ps->pool);
        int inner_kind;

        if (is_unsigned || is_signed)
            return 0;
        c->p++;
        if (!cw_type(ps, c, pre, inner_post, &inner_kind))
            return 0;
        wrap_indirection(pre, post, inner_post, inner_kind,
                         ch == 'P' ? "*" : "&", is_const, is_volatile);
        return 1;
    }

    if (ch == 'M') {
        struct text *owner = text_new(&ps->pool);
        struct text *inner_post = text_new(&ps->pool);
        int inner_kind;

        if (is_unsigned || is_signed)
            return 0;
        c->p++;
        if (!cw_class(ps, c, owner, NULL))
            return 0;
        if (!cw_type(ps, c, pre, inner_post, &inner_kind))
            return 0;
        text_add(owner, "::*");
        wrap_indirection(pre, post, inner_post, inner_kind, text_str(owner),
                         is_const, is_volatile);
        return 1;
    }

    if (ch == 'F') {
        struct text *args = text_new(&ps->pool);
        struct text *ret_pre = text_new(&ps->pool);
        struct text *ret_post = text_new(&ps->pool);
        int ret_kind;

        if (is_unsigned || is_signed || is_volatile)
            return 0;
        c->p++;
        if (!cw_args(ps, c, args) || cur_peek(c) != '_')
            return 0;
        c->p++;
        if (!cw_type(ps, c, ret_pre, ret_post, &ret_kind))
            return 0;
        build_function_type(pre, post, ret_pre, ret_post, args, is_const);
        *kind = KIND_FUNCTION;
        return 1;
    }

    if (ch == 'A') {
        unsigned long count;
        char dimension[32];
        struct text *elem_post = text_new(&ps->pool);
        int elem_kind;

        if (is_unsigned || is_signed || is_const || is_volatile)
            return 0;
        c->p++;
        if (!cw_number(c, &count) || cur_peek(c) != '_')
            return 0;
        c->p++;
        if (!cw_type(ps, c, pre, elem_post, &elem_kind))
            return 0;
        if (elem_kind == KIND_FUNCTION)
            return 0;
        sprintf(dimension, "[%lu]", count);
        text_add(post, dimension);
        text_add_text(post, elem_post);
        *kind = KIND_ARRAY;
        return 1;
    }

    add_cv_prefix(pre, is_const, is_volatile);
    if (is_digit(ch) || ch == 'Q') {
        if (is_unsigned || is_signed)
            return 0;
        return cw_class(ps, c, pre, NULL);
    }
    if (builtin_name(ch) == NULL)
        return 0;
    if ((is_unsigned || is_signed) && strchr("csilx", ch) == NULL)
        return 0;
    if (is_unsigned)
        text_add(pre, "unsigned ");
    if (is_signed)
        text_add(pre, "signed ");
    text_add(pre, builtin_name(ch));
    c->p++;
    return 1;
}

/* Decode one type into the text before and after its declarator position. */
static int cw_type(struct parser *ps, struct cursor *c, struct text *pre,
                   struct text *post, int *kind)
{
    int ok;

    if (ps->depth >= DEPTH_LIMIT)
        return 0;
    ps->depth++;
    ok = cw_type_inner(ps, c, pre, post, kind);
    ps->depth--;
    return ok;
}

/* What the part of a CodeWarrior name before the "__" separator stands for. */
enum cw_name_kind {
    CW_PLAIN,         /* an ordinary identifier or an operator */
    CW_CONSTRUCTOR,   /* __ct */
    CW_DESTRUCTOR,    /* __dt */
    CW_VTABLE         /* __vt */
};

/* Decode a conversion operator name, "__op" followed by the target type. */
static int cw_conversion_name(struct parser *ps, const char *name, size_t len,
                              struct text *out)
{
    struct cursor c;
    struct text *pre = text_new(&ps->pool);
    struct text *post = text_new(&ps->pool);
    int kind;

    if (len <= 4 || memcmp(name, "__op", 4) != 0)
        return 0;
    c.p = name + 4;
    c.end = name + len;
    if (!cw_type(ps, &c, pre, post, &kind) || c.p != c.end)
        return 0;
    text_add(out, "operator ");
    text_add_text(out, pre);
    text_add_text(out, post);
    return 1;
}

/* Decode the name part (before the separator) into out and name_kind. */
static int cw_entity_name(struct parser *ps, const char *name, size_t len,
                          struct text *out, int *name_kind)
{
    const char *angle = (const char *)memchr(name, '<', len);
    size_t base_len = angle != NULL ? (size_t)(angle - name) : len;
    const char *op;

    *name_kind = CW_PLAIN;
    if (cw_conversion_name(ps, name, len, out))
        return 1;
    if (angle != NULL && (name[len - 1] != '>' || len - base_len < 3))
        return 0;
    if (base_len == 4 && angle == NULL) {
        if (memcmp(name, "__ct", 4) == 0) {
            *name_kind = CW_CONSTRUCTOR;
            return 1;
        }
        if (memcmp(name, "__dt", 4) == 0) {
            *name_kind = CW_DESTRUCTOR;
            return 1;
        }
        if (memcmp(name, "__vt", 4) == 0) {
            *name_kind = CW_VTABLE;
            return 1;
        }
    }
    op = base_len > 2 && name[0] == '_' && name[1] == '_'
        ? operator_text(name + 2, base_len - 2) : NULL;
    if (op != NULL) {
        text_add(out, op);
    } else if (is_identifier(name, base_len)) {
        text_add_n(out, name, base_len);
    } else {
        return 0;
    }
    if (angle != NULL)
        return cw_template_args(ps, angle + 1, name + len - 1, out);
    return 1;
}

/*
 * Try to demangle the len bytes at name with the "__" separator at offset
 * split.  The part after the separator must be consumed completely for the
 * attempt to count.
 */
static int cw_demangle_at(struct parser *ps, const char *name, size_t len,
                          size_t split, struct text *out)
{
    struct cursor c;
    struct text *fname = text_new(&ps->pool);
    struct text *scope = text_new(&ps->pool);
    struct text *base = text_new(&ps->pool);
    struct text *args = text_new(&ps->pool);
    struct text *ret = text_new(&ps->pool);
    int name_kind;
    int has_class = 0, is_const = 0, is_volatile = 0;

    c.p = name + split + 2;
    c.end = name + len;
    if (!is_digit(cur_peek(&c)) && cur_peek(&c) != 'Q' && cur_peek(&c) != 'F')
        return 0;
    if (!cw_entity_name(ps, name, split, fname, &name_kind))
        return 0;

    if (cur_peek(&c) != 'F') {
        if (!cw_class(ps, &c, scope, base))
            return 0;
        has_class = 1;
    }

    if (c.p == c.end) {
        /* A class with nothing after it: static data, vtable and the like. */
        if (name_kind == CW_CONSTRUCTOR || name_kind == CW_DESTRUCTOR)
            return 0;
        if (name_kind == CW_PLAIN && !is_identifier(text_str(fname), fname->len))
            return 0;
        text_add_text(out, scope);
        text_add(out, "::");
        if (name_kind == CW_VTABLE)
            text_add(out, "__vtable");
        else
            text_add_text(out, fname);
        return 1;
    }

    if (name_kind == CW_VTABLE)
        return 0;
    if (name_kind != CW_PLAIN && !has_class)
        return 0;
    if (has_class && cur_peek(&c) == 'C') {
        is_const = 1;
        c.p++;
    }
    if (has_class && cur_peek(&c) == 'V') {
        is_volatile = 1;
        c.p++;
    }
    if (cur_peek(&c) != 'F')
        return 0;
    c.p++;
    if (!cw_args(ps, &c, args))
        return 0;
    if (cur_peek(&c) == '_') {
        /* Template functions carry their return type after the arguments. */
        struct text *ret_post = text_new(&ps->pool);
        int ret_kind;

        c.p++;
        if (!cw_type(ps, &c, ret, ret_post, &ret_kind) || ret_post->len != 0)
            return 0;
    }
    if (c.p != c.end)
        return 0;

    if (name_kind == CW_CONSTRUCTOR) {
        text_add_text(fname, base);
    } else if (name_kind == CW_DESTRUCTOR) {
        text_add(fname, "~");
        text_add_text(fname, base);
    }
    compose_function(out, ret, scope, fname, args, is_const, is_volatile);
    return 1;
}

/* Demangle the len bytes at name as a CodeWarrior name without a wrapper. */
static int cw_demangle_plain(const char *name, size_t len, struct text *out)
{
    size_t i;
    int depth = 0;

    /* Try every "__" outside template brackets, leftmost first. */
    for (i = 1; i + 2 < len; i++) {
        struct parser ps;
        struct text *result;
        int ok;

        if (name[i] == '<')
            depth++;
        else if (name[i] == '>' && depth > 0)
            depth--;
        if (depth != 0 || name[i] != '_' || name[i + 1] != '_')
            continue;
        parser_init(&ps);
        result = text_new(&ps.pool);
        ok = cw_demangle_at(&ps, name, len, i, result) && !ps.pool.overflow;
        if (ok)
            text_add_text(out, result);
        pool_free(&ps.pool);
        if (ok)
            return 1;
    }
    return 0;
}

/*
 * Length of the wrapper tags at the start of a name: "@ET@", "@STRING@" and
 * the like, or the "@<n>@" / "@<n>@<m>@" of a this-adjusting thunk.
 */
static size_t cw_wrapper_length(const char *name)
{
    size_t i = 1;
    size_t end;

    if (name[0] != '@')
        return 0;
    if (is_digit((unsigned char)name[i])) {
        while (is_digit((unsigned char)name[i]))
            i++;
    } else {
        while (name[i] >= 'A' && name[i] <= 'Z')
            i++;
    }
    if (i == 1 || name[i] != '@')
        return 0;
    end = ++i;
    while (is_digit((unsigned char)name[i]))
        i++;
    if (i > end && name[i] == '@')
        end = i + 1;
    return end;
}

/*
 * Demangle a CodeWarrior name; returns 0 if it is not one.  The compiler
 * names companions of a function (exception tables, thunks, string
 * constants, static locals) by wrapping the function's mangled name as
 * "@<tag>@<name>" or "@<tag>@<name>@<suffix>".  The wrapper is copied as it
 * is and only the name inside is demangled.
 */
static int cw_demangle(const char *name, struct text *out)
{
    size_t wrapper = cw_wrapper_length(name);
    const char *inner = name + wrapper;
    size_t len = strlen(inner);
    size_t i;

    text_add_n(out, name, wrapper);
    if (cw_demangle_plain(inner, len, out))
        return 1;
    for (i = 1; wrapper != 0 && i < len; i++) {
        if (inner[i] == '@' && cw_demangle_plain(inner, i, out)) {
            text_add(out, inner + i);
            return 1;
        }
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/* Scheme B: SN Systems "__0" names                                   */
/* ------------------------------------------------------------------ */

static int sn_type(struct parser *ps, struct cursor *c, struct text *pre,
                   struct text *post, int *kind);

/* Value of a count letter: 'A'..'Z' are 0..25, 'a'..'z' are 26..51. */
static int sn_letter(int ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return ch - 'A';
    if (ch >= 'a' && ch <= 'z')
        return ch - 'a' + 26;
    return -1;
}

/*
 * Decode an identifier: a length and that many characters.  The length is
 * one count letter, or "0" and a count letter for lengths from 52 up.
 */
static int sn_ident(struct cursor *c, struct text *out)
{
    size_t skip = 1;
    int len = sn_letter(cur_peek(c));

    if (cur_peek(c) == '0' && sn_letter(cur_peek_at(c, 1)) >= 0) {
        skip = 2;
        len = 52 + sn_letter(cur_peek_at(c, 1));
    }
    if (len < 1 || cur_left(c) < skip + (size_t)len)
        return 0;
    if (!is_identifier(c->p + skip, (size_t)len))
        return 0;
    text_add_n(out, c->p + skip, (size_t)len);
    c->p += skip + (size_t)len;
    return 1;
}

/*
 * Name of a builtin type code of this scheme, or NULL.  The 64-bit integer
 * is "L"; "x" and "w" do not occur in the build this was worked out from.
 */
static const char *sn_builtin_name(int ch)
{
    if (ch == 'L')
        return "long long";
    if (ch == 'x' || ch == 'w')
        return NULL;
    return builtin_name(ch);
}

/*
 * True if the type starting at p is a builtin with nothing but const and
 * sign prefixes, which is how a template's own value parameter is written.
 */
static int sn_is_bare_builtin(const char *p, const char *end)
{
    while (p < end && (*p == 'C' || *p == 'U' || *p == 'S'))
        p++;
    return p < end && sn_builtin_name((unsigned char)*p) != NULL;
}

/*
 * Decode template arguments "7<arg>..._" (the cursor is on the '7') of the
 * template called owner (NULL for an operator).  With record set, the list
 * belongs to the declarator itself and its arguments are remembered.
 *
 * Inside the signature, the declarator's own template can be named again
 * with its parameters instead of its arguments: type parameters as "9"
 * references and value parameters as their bare type.  The latter are
 * replaced by the constant the declarator has in that position.
 */
static int sn_template_args(struct parser *ps, struct cursor *c,
                            struct text *out, int record, const char *owner)
{
    struct text *list = text_new(&ps->pool);
    int self = !record && owner != NULL && ps->list_count == 1
        && ps->list_owner != NULL && strcmp(owner, ps->list_owner) == 0;
    int count = 0;

    c->p++;
    if (record && ++ps->list_count == 1)
        ps->list_owner = owner;
    while (cur_peek(c) != '_') {
        struct text *pre = text_new(&ps->pool);
        struct text *post = text_new(&ps->pool);
        int kind = KIND_PLAIN;
        int is_constant = 0;
        int first = cur_peek(c) == 'C' ? cur_peek_at(c, 1) : cur_peek(c);
        int own_constant = self && count < ps->targ_count
            && ps->targs[count].is_constant;

        if (cur_peek(c) == '4') {
            /* Integer constant; only "4A" (zero) is known. */
            if (cur_peek_at(c, 1) != 'A')
                return 0;
            text_add(pre, "0");
            c->p += 2;
            is_constant = 1;
        } else if (own_constant) {
            struct text *unused = text_new(&ps->pool);

            if (!sn_is_bare_builtin(c->p, c->end)
                || !sn_type(ps, c, unused, post, &kind))
                return 0;
            text_add_text(pre, ps->targs[count].pre);
        } else if (!sn_type(ps, c, pre, post, &kind)) {
            return 0;
        }
        list_add(list, pre, post);
        if (record && ps->list_count == 1) {
            struct template_arg *arg;

            if (count >= ARG_LIMIT)
                return 0;
            arg = &ps->targs[count];
            arg->pre = pre;
            arg->post = post;
            arg->kind = kind;
            arg->is_constant = is_constant;
            arg->is_indirect = first == 'P' || first == 'R';
            ps->targ_count = count + 1;
        }
        count++;
    }
    if (count == 0)
        return 0;
    c->p++;
    text_add(out, "<");
    text_add_text(out, list);
    text_add(out, ">");
    return 1;
}

/*
 * Decode a template parameter reference "9<n>A": argument n of the only
 * template list on the declarator.  Other forms are not understood.
 */
static int sn_template_param(struct parser *ps, struct cursor *c,
                             struct text *pre, struct text *post, int *kind,
                             int is_const)
{
    int index = sn_letter(cur_peek_at(c, 1));
    const struct template_arg *arg;
    const char *text;

    if (cur_peek_at(c, 2) != 'A' || ps->list_count != 1)
        return 0;
    if (index < 1 || index > ps->targ_count || ps->targs[index - 1].is_constant)
        return 0;
    arg = &ps->targs[index - 1];
    text = text_str(arg->pre);
    if (is_const && strncmp(text, "const ", 6) == 0)
        is_const = 0;
    /* const goes after a pointer or reference and before anything else. */
    if (is_const && !arg->is_indirect)
        text_add(pre, "const ");
    text_add(pre, text);
    if (is_const && arg->is_indirect)
        text_add(pre, " const");
    text_add_text(post, arg->post);
    *kind = arg->kind;
    c->p += 3;
    return 1;
}

/* Decode an identifier with optional template arguments. */
static int sn_name(struct parser *ps, struct cursor *c, struct text *out,
                   struct text *base, int record)
{
    struct text *ident = text_new(&ps->pool);

    if (!sn_ident(c, ident))
        return 0;
    text_add_text(out, ident);
    if (base != NULL) {
        text_clear(base);
        text_add_text(base, ident);
    }
    if (cur_peek(c) == '7')
        return sn_template_args(ps, c, out, record, text_str(ident));
    return 1;
}

/* Decode a class name; "5<outer><name>" is a name nested in another scope. */
static int sn_class(struct parser *ps, struct cursor *c, struct text *out,
                    struct text *base, int record)
{
    int ok;

    if (cur_peek(c) != '5')
        return sn_name(ps, c, out, base, record);
    if (ps->depth >= DEPTH_LIMIT)
        return 0;
    ps->depth++;
    c->p++;
    ok = sn_class(ps, c, out, base, record);
    ps->depth--;
    if (!ok)
        return 0;
    text_add(out, "::");
    return sn_name(ps, c, out, base, record);
}

/*
 * Decode argument types up to something that cannot start one.  "T<n>"
 * repeats argument n and "N<count><n>" repeats it count times.
 */
static int sn_args(struct parser *ps, struct cursor *c, struct text *out)
{
    struct text *seen[ARG_LIMIT];
    int count = 0;
    int saw_void = 0;
    int saw_ellipsis = 0;

    for (;;) {
        int ch = cur_peek(c);
        int repeat = 0;
        int index = 0;
        struct text *arg;

        if (ch == 'T' && is_letter(cur_peek_at(c, 1))) {
            repeat = 1;
            index = sn_letter(cur_peek_at(c, 1));
            c->p += 2;
        } else if (ch == 'N') {
            repeat = sn_letter(cur_peek_at(c, 1));
            index = sn_letter(cur_peek_at(c, 2));
            if (repeat < 1)
                return 0;
            c->p += 3;
        } else if (ch == 0 || ch == '_' || ch == 'K' || ch == 'T') {
            break;
        }
        if (saw_ellipsis)
            return 0;
        if (repeat != 0) {
            if (index < 1 || index > count)
                return 0;
            arg = seen[index - 1];
        } else {
            struct text *post = text_new(&ps->pool);
            int kind;

            saw_ellipsis = ch == 'e';
            if (ch == 'v')
                saw_void = 1;
            arg = text_new(&ps->pool);
            if (!sn_type(ps, c, arg, post, &kind))
                return 0;
            text_add_text(arg, post);
            repeat = 1;
        }
        while (repeat-- > 0) {
            if (count >= ARG_LIMIT)
                return 0;
            seen[count++] = arg;
            list_add(out, arg, NULL);
        }
    }
    /* "void" only stands alone, and nothing follows "...". */
    return count > 0 && (!saw_void || count == 1);
}

/* Decode one type; the work behind sn_type, which tracks the nesting depth. */
static int sn_type_inner(struct parser *ps, struct cursor *c, struct text *pre,
                         struct text *post, int *kind)
{
    int is_const = 0, is_unsigned = 0, is_signed = 0;
    int ch;

    *kind = KIND_PLAIN;
    for (;;) {
        ch = cur_peek(c);
        if (ch == 'C' && !is_const)
            is_const = 1;
        else if (ch == 'U' && !is_unsigned && !is_signed)
            is_unsigned = 1;
        else if (ch == 'S' && !is_unsigned && !is_signed)
            is_signed = 1;
        else
            break;
        c->p++;
    }

    if (ch == 'P' && cur_peek_at(c, 1) == 'M') {
        /* Pointer to member function: "PM", the class, a function type. */
        struct text *owner = text_new(&ps->pool);
        struct text *inner_post = text_new(&ps->pool);
        int inner_kind;

        if (is_unsigned || is_signed)
            return 0;
        c->p += 2;
        if (!sn_class(ps, c, owner, NULL, 0))
            return 0;
        if (!sn_type(ps, c, pre, inner_post, &inner_kind)
            || inner_kind != KIND_FUNCTION)
            return 0;
        text_add(owner, "::*");
        wrap_indirection(pre, post, inner_post, inner_kind, text_str(owner),
                         is_const, 0);
        return 1;
    }

    if (ch == 'P' || ch == 'R') {
        struct text *inner_post = text_new(&ps->pool);
        int inner_kind;

        if (is_unsigned || is_signed)
            return 0;
        c->p++;
        if (!sn_type(ps, c, pre, inner_post, &inner_kind))
            return 0;
        wrap_indirection(pre, post, inner_post, inner_kind,
                         ch == 'P' ? "*" : "&", is_const, 0);
        return 1;
    }

    if (ch == 'F') {
        struct text *args = text_new(&ps->pool);
        struct text *ret_pre = text_new(&ps->pool);
        struct text *ret_post = text_new(&ps->pool);
        int ret_kind;

        if (is_unsigned || is_signed || is_const)
            return 0;
        c->p++;
        if (!sn_args(ps, c, args) || cur_peek(c) != '_')
            return 0;
        c->p++;
        if (!sn_type(ps, c, ret_pre, ret_post, &ret_kind))
            return 0;
        build_function_type(pre, post, ret_pre, ret_post, args, 0);
        *kind = KIND_FUNCTION;
        return 1;
    }

    if (is_unsigned || is_signed) {
        if (ch == 0 || strchr("csilL", ch) == NULL)
            return 0;
    }
    if (ch == '9')
        return sn_template_param(ps, c, pre, post, kind, is_const);

    add_cv_prefix(pre, is_const, 0);
    if (ch == '6') {
        c->p++;
        return sn_class(ps, c, pre, NULL, 0);
    }
    if (sn_builtin_name(ch) == NULL)
        return 0;
    if (is_unsigned)
        text_add(pre, "unsigned ");
    if (is_signed)
        text_add(pre, "signed ");
    text_add(pre, sn_builtin_name(ch));
    c->p++;
    return 1;
}

/* Decode one type into the text before and after its declarator position. */
static int sn_type(struct parser *ps, struct cursor *c, struct text *pre,
                   struct text *post, int *kind)
{
    int ok;

    if (ps->depth >= DEPTH_LIMIT)
        return 0;
    ps->depth++;
    ok = sn_type_inner(ps, c, pre, post, kind);
    ps->depth--;
    return ok;
}

/*
 * Decode what follows a function or operator name: the arguments, then
 * "_<type>" for the return type that template functions and members of
 * templates carry, then "K" for a const member or "T" for a static member.
 */
static int sn_signature(struct parser *ps, struct cursor *c, struct text *args,
                        struct text *ret, int *is_const, int *is_static)
{
    if (!sn_args(ps, c, args))
        return 0;
    if (cur_peek(c) == '_') {
        struct text *ret_post = text_new(&ps->pool);
        int ret_kind;

        c->p++;
        if (!sn_type(ps, c, ret, ret_post, &ret_kind) || ret_post->len != 0)
            return 0;
    }
    if (cur_peek(c) == 'K') {
        *is_const = 1;
        c->p++;
    } else if (cur_peek(c) == 'T') {
        *is_static = 1;
        c->p++;
    }
    return c->p == c->end;
}

/* The special names that share the operator position in an SN name. */
enum sn_operator_kind {
    SN_OPERATOR,        /* an entry of operator_codes */
    SN_CONSTRUCTOR,     /* ct */
    SN_DESTRUCTOR,      /* dt */
    SN_CONVERSION       /* op<type> */
};

/*
 * Try to read the text under c as the operator with the given code followed
 * by its signature.  Nothing is written unless the whole name is consumed.
 */
static int sn_operator_try(struct parser *ps, struct cursor c, const char *code,
                           const char *text, int op_kind,
                           const struct text *scope, const struct text *base,
                           struct text *out)
{
    struct text *name = text_new(&ps->pool);
    struct text *args = text_new(&ps->pool);
    struct text *ret = text_new(&ps->pool);
    size_t code_len = strlen(code);
    int saved_lists = ps->list_count;
    int saved_targs = ps->targ_count;
    int is_const = 0, is_static = 0;
    int ok = 1;

    if (cur_left(&c) < code_len || memcmp(c.p, code, code_len) != 0)
        return 0;
    c.p += code_len;
    if (op_kind == SN_OPERATOR) {
        text_add(name, text);
        if (cur_peek(&c) == '7')
            ok = sn_template_args(ps, &c, name, 1, NULL);
    } else if (op_kind == SN_CONSTRUCTOR) {
        text_add_text(name, base);
    } else if (op_kind == SN_DESTRUCTOR) {
        text_add(name, "~");
        text_add_text(name, base);
    } else {
        struct text *post = text_new(&ps->pool);
        int kind;

        text_add(name, "operator ");
        ok = sn_type(ps, &c, name, post, &kind) && post->len == 0;
    }
    ok = ok && sn_signature(ps, &c, args, ret, &is_const, &is_static);
    if (!ok) {
        ps->list_count = saved_lists;
        ps->targ_count = saved_targs;
        return 0;
    }
    if (is_static)
        text_add(out, "static ");
    compose_function(out, ret, scope, name, args, is_const, 0);
    return 1;
}

/*
 * Decode an operator, constructor or destructor.  The codes are not
 * delimited, so each known code is tried as a prefix; only one of them can
 * leave a signature that parses to the end.  scope is empty for "__0O".
 */
static int sn_operator(struct parser *ps, const struct cursor *start,
                       const struct text *scope, const struct text *base,
                       struct text *out)
{
    size_t i;

    if (scope->len != 0) {
        if (sn_operator_try(ps, *start, "ct", NULL, SN_CONSTRUCTOR, scope, base, out)
            || sn_operator_try(ps, *start, "dt", NULL, SN_DESTRUCTOR, scope, base, out)
            || sn_operator_try(ps, *start, "op", NULL, SN_CONVERSION, scope, base, out))
            return 1;
    }
    for (i = 0; i < OPERATOR_COUNT; i++) {
        if (sn_operator_try(ps, *start, operator_codes[i].code,
                            operator_codes[i].text, SN_OPERATOR, scope, base, out))
            return 1;
    }
    return 0;
}

/* Demangle the body of an SN name; kind is the letter after "__0". */
static int sn_demangle_body(struct parser *ps, int kind, struct cursor *c,
                            struct text *out)
{
    struct text *scope = text_new(&ps->pool);
    struct text *base = text_new(&ps->pool);
    struct text *name = text_new(&ps->pool);
    struct text *args = text_new(&ps->pool);
    struct text *ret = text_new(&ps->pool);
    int is_const = 0, is_static = 0;

    if (kind == 'f' || kind == 'o' || kind == 'd') {
        if (!sn_class(ps, c, scope, base, 1))
            return 0;
    }
    if (kind == 'o' || kind == 'O')
        return sn_operator(ps, c, scope, base, out);
    if (kind == 'd') {
        /* Static data member; cfront's "__vtbl" is the class's vtable. */
        if (!sn_ident(c, name) || c->p != c->end)
            return 0;
        text_add_text(out, scope);
        text_add(out, "::");
        if (strcmp(text_str(name), "__vtbl") == 0)
            text_add(out, "__vtable");
        else
            text_add_text(out, name);
        return 1;
    }
    /* A free function may sit in a namespace; a member's class is in scope. */
    if (kind == 'F' ? !sn_class(ps, c, name, NULL, 1)
                    : !sn_name(ps, c, name, NULL, 1))
        return 0;
    if (!sn_signature(ps, c, args, ret, &is_const, &is_static))
        return 0;
    if (kind == 'F' && (is_const || is_static))
        return 0;
    if (is_static)
        text_add(out, "static ");
    compose_function(out, ret, scope, name, args, is_const, 0);
    return 1;
}

/* Demangle an SN name; the caller has checked that it starts "__0<kind>". */
static int sn_demangle(const char *name, struct text *out)
{
    struct parser ps;
    struct cursor c;
    struct text *result;
    int ok;

    parser_init(&ps);
    result = text_new(&ps.pool);
    c.p = name + 4;
    c.end = name + strlen(name);
    ok = sn_demangle_body(&ps, name[3], &c, result) && !ps.pool.overflow;
    if (ok)
        text_add_text(out, result);
    pool_free(&ps.pool);
    return ok;
}

/* ------------------------------------------------------------------ */
/* Choosing a scheme                                                  */
/* ------------------------------------------------------------------ */

/*
 * Write the demangled form of name to out; returns 0 if there is none.  The
 * scheme is picked by shape: "__0" and a kind letter is an SN name and is
 * never tried as a CodeWarrior name.
 */
static int demangle(const char *name, struct text *out)
{
    int is_sn = strncmp(name, "__0", 3) == 0 && name[3] != '\0'
        && strchr("FfOod", name[3]) != NULL;
    int ok;

    text_clear(out);
    ok = is_sn ? sn_demangle(name, out) : cw_demangle(name, out);
    if (out->pool->overflow) {
        /* Too long to hold: treat it like any other name we cannot decode. */
        out->pool->overflow = 0;
        ok = 0;
    }
    if (!ok)
        text_clear(out);
    return ok;
}

/* The demangled form of name, or name itself when it has none. */
static const char *demangled_or_same(const char *name, struct text *scratch)
{
    return demangle(name, scratch) ? text_str(scratch) : name;
}

/* ------------------------------------------------------------------ */
/* Output helpers                                                     */
/* ------------------------------------------------------------------ */

/* Print a field, replacing control characters that would break the table. */
static void put_field(const char *s)
{
    for (; *s != '\0'; s++) {
        int ch = (unsigned char)*s;
        putchar(ch < 0x20 || ch == 0x7f ? '?' : ch);
    }
}

/* Print the mangled name and its demangled form as the last two fields. */
static void put_names(const char *mangled, struct text *scratch)
{
    put_field(mangled);
    putchar('\t');
    put_field(demangled_or_same(mangled, scratch));
    putchar('\n');
}

/* File name without its directory part, used as the default label. */
static const char *base_name(const char *path)
{
    const char *base = path;
    const char *p;

    for (p = path; *p != '\0'; p++) {
        if (*p == '/' || *p == '\\')
            base = p + 1;
    }
    return base;
}

/* ------------------------------------------------------------------ */
/* ELF symbol tables                                                  */
/* ------------------------------------------------------------------ */

enum {
    ELF_HEADER_SIZE = 52,
    ELF_SECTION_SIZE = 40,
    ELF_SYMBOL_SIZE = 16,
    ELF_CLASS_32 = 1,
    ELF_DATA_LSB = 1,
    ELF_MACHINE_MIPS = 8,
    ELF_SHT_SYMTAB = 2,
    ELF_SHT_STRTAB = 3,
    ELF_STT_OBJECT = 1,
    ELF_STT_FUNC = 2
};

/* Read a little-endian 16-bit value. */
static unsigned long get_le16(const unsigned char *p)
{
    return (unsigned long)p[0] | ((unsigned long)p[1] << 8);
}

/* Read a little-endian 32-bit value. */
static unsigned long get_le32(const unsigned char *p)
{
    return (unsigned long)p[0] | ((unsigned long)p[1] << 8)
        | ((unsigned long)p[2] << 16) | ((unsigned long)p[3] << 24);
}

/* Read a whole file into memory; returns NULL after printing the reason. */
static unsigned char *read_file(const char *path, size_t *size)
{
    FILE *f = fopen(path, "rb");
    unsigned char *data;
    long length;

    if (f == NULL) {
        fprintf(stderr, "symindex: cannot open %s\n", path);
        return NULL;
    }
    if (fseek(f, 0, SEEK_END) != 0 || (length = ftell(f)) < 0
        || fseek(f, 0, SEEK_SET) != 0) {
        fprintf(stderr, "symindex: cannot measure %s\n", path);
        fclose(f);
        return NULL;
    }
    if ((unsigned long)length > FILE_LIMIT) {
        fprintf(stderr, "symindex: %s is too large\n", path);
        fclose(f);
        return NULL;
    }
    data = (unsigned char *)malloc((size_t)length + 1);
    if (data == NULL)
        fatal("out of memory");
    if (fread(data, 1, (size_t)length, f) != (size_t)length) {
        fprintf(stderr, "symindex: cannot read %s\n", path);
        free(data);
        fclose(f);
        return NULL;
    }
    fclose(f);
    *size = (size_t)length;
    return data;
}

/* True if the byte range [offset, offset + length) lies inside the file. */
static int range_ok(size_t file_size, unsigned long offset, unsigned long length)
{
    return offset <= file_size && length <= file_size - offset;
}

/* Name of a symbol binding value. */
static const char *binding_name(unsigned long binding, char *scratch)
{
    switch (binding) {
    case 0: return "local";
    case 1: return "global";
    case 2: return "weak";
    default:
        sprintf(scratch, "bind%lu", binding);
        return scratch;
    }
}

/* Say why an ELF file cannot be indexed, release it, return the error status. */
static int refuse_elf(const char *path, const char *reason, unsigned char *data)
{
    fprintf(stderr, "symindex: %s %s\n", path, reason);
    free(data);
    return 1;
}

/* Print one row per function and object symbol of an ELF file. */
static int index_elf(const char *path, const char *label)
{
    size_t size = 0;
    unsigned char *data = read_file(path, &size);
    const unsigned char *sections;
    const unsigned char *symtab = NULL;
    const unsigned char *strtab;
    const unsigned char *symbols;
    const char *strings;
    unsigned long shoff, shentsize, shnum, link, i;
    unsigned long sym_offset, sym_size, sym_entsize, str_offset, str_size;
    struct pool pool;
    struct text *scratch;

    if (data == NULL)
        return 1;
    if (size < ELF_HEADER_SIZE || memcmp(data, "\177ELF", 4) != 0
        || data[4] != ELF_CLASS_32 || data[5] != ELF_DATA_LSB
        || get_le16(data + 18) != ELF_MACHINE_MIPS)
        return refuse_elf(path, "is not a little-endian 32-bit MIPS ELF", data);
    shoff = get_le32(data + 32);
    shentsize = get_le16(data + 46);
    shnum = get_le16(data + 48);
    if (shentsize < ELF_SECTION_SIZE || shnum == 0
        || !range_ok(size, shoff, shentsize * shnum))
        return refuse_elf(path, "has no usable section headers", data);
    sections = data + shoff;
    for (i = 0; i < shnum && symtab == NULL; i++) {
        if (get_le32(sections + i * shentsize + 4) == ELF_SHT_SYMTAB)
            symtab = sections + i * shentsize;
    }
    if (symtab == NULL)
        return refuse_elf(path, "has no .symtab", data);
    sym_offset = get_le32(symtab + 16);
    sym_size = get_le32(symtab + 20);
    link = get_le32(symtab + 24);
    sym_entsize = get_le32(symtab + 36);
    if (sym_entsize == 0)
        sym_entsize = ELF_SYMBOL_SIZE;
    if (sym_size < sym_entsize)
        return refuse_elf(path, "has an empty .symtab (stripped)", data);
    if (sym_entsize < ELF_SYMBOL_SIZE || link >= shnum
        || !range_ok(size, sym_offset, sym_size))
        return refuse_elf(path, "has a damaged .symtab", data);
    strtab = sections + link * shentsize;
    str_offset = get_le32(strtab + 16);
    str_size = get_le32(strtab + 20);
    if (get_le32(strtab + 4) != ELF_SHT_STRTAB || str_size == 0
        || !range_ok(size, str_offset, str_size)
        || data[str_offset + str_size - 1] != '\0')
        return refuse_elf(path, "has a damaged string table", data);
    symbols = data + sym_offset;
    strings = (const char *)data + str_offset;

    pool_init(&pool);
    scratch = text_new(&pool);
    for (i = 0; i < sym_size / sym_entsize; i++) {
        const unsigned char *sym = symbols + i * sym_entsize;
        unsigned long name_offset = get_le32(sym);
        unsigned long type = sym[12] & 0x0f;
        char binding[32];

        if (type != ELF_STT_FUNC && type != ELF_STT_OBJECT)
            continue;
        if (name_offset >= str_size || strings[name_offset] == '\0')
            continue;
        put_field(label);
        printf("\t%s\t%08lx\t%lu\t%s\t", type == ELF_STT_FUNC ? "func" : "object",
               get_le32(sym + 4), get_le32(sym + 8),
               binding_name((unsigned long)sym[12] >> 4, binding));
        put_names(strings + name_offset, scratch);
    }
    pool_free(&pool);
    free(data);
    return 0;
}

/* ------------------------------------------------------------------ */
/* Synthetic ELF for the tests                                        */
/* ------------------------------------------------------------------ */

/* One symbol of the synthetic test ELF. */
struct test_symbol {
    const char *name;
    unsigned long value;
    unsigned long size;
    unsigned info;      /* (binding << 4) | type */
    unsigned shndx;
};

/* Symbols of the synthetic ELF: every type and binding the indexer meets. */
static const struct test_symbol test_symbols[] = {
    { "", 0, 0, 0x00, 0 },
    { "", 0x00100000UL, 0, 0x03, 1 },
    { "selftest.c", 0, 0, 0x04, 0xfff1 },
    { "init_ps2_system__Fv", 0x00100000UL, 64, 0x02, 1 },
    { "execDot_VectorVector__7UObjectFR6FFramePv", 0x00100040UL, 128, 0x12, 1 },
    { "__0FJDiskReadyv", 0x001000c0UL, 8, 0x22, 1 },
    { "StartFadeOut__13CThemeChannelFv", 0x001000c8UL, 24, 0xd2, 1 },
    { "__vt__12hkBaseObject", 0x00200000UL, 16, 0x11, 2 },
    { "s_instance__8hkMemory", 0x00200010UL, 4, 0x01, 2 },
    { "selftest_label", 0x001000e0UL, 0, 0x10, 1 },
    { "SND_fn_tduGetLowestResourceSwitch", 0x001000e0UL, 32, 0x12, 1 },
    { "__0fNUGUIComponentNexecActualTopR6GFFramePv", 0x00100100UL, 12, 0x12, 1 },
    { "", 0x00100200UL, 4, 0x02, 1 }
};

#define TEST_SYMBOL_COUNT (sizeof(test_symbols) / sizeof(test_symbols[0]))

/* A file image under construction. */
struct image {
    unsigned char data[4096];
    size_t len;
};

/* Append bytes to the image. */
static void image_add(struct image *img, const void *bytes, size_t n)
{
    if (n > sizeof(img->data) - img->len)
        fatal("synthetic ELF does not fit its buffer");
    memcpy(img->data + img->len, bytes, n);
    img->len += n;
}

/* Append a little-endian 16-bit value to the image. */
static void image_add16(struct image *img, unsigned long value)
{
    unsigned char b[2];

    b[0] = (unsigned char)(value & 0xff);
    b[1] = (unsigned char)((value >> 8) & 0xff);
    image_add(img, b, 2);
}

/* Append a little-endian 32-bit value to the image. */
static void image_add32(struct image *img, unsigned long value)
{
    image_add16(img, value & 0xffff);
    image_add16(img, (value >> 16) & 0xffff);
}

/* Append one section header to the image. */
static void image_add_section(struct image *img, unsigned long name,
                              unsigned long type, unsigned long addr,
                              unsigned long offset, unsigned long size,
                              unsigned long link, unsigned long entsize)
{
    image_add32(img, name);
    image_add32(img, type);
    image_add32(img, 0);        /* flags */
    image_add32(img, addr);
    image_add32(img, offset);
    image_add32(img, size);
    image_add32(img, link);
    image_add32(img, 0);        /* info */
    image_add32(img, 4);        /* alignment */
    image_add32(img, entsize);
}

/* Write a small MIPS ELF whose .symtab holds test_symbols. */
static int write_test_elf(const char *path)
{
    /* Section names: .text at 1, .data at 7, .symtab at 13, .strtab at 21. */
    static const char section_names[] = "\0.text\0.data\0.symtab\0.strtab\0.shstrtab";
    static const unsigned char magic[16] = {
        0x7f, 'E', 'L', 'F', ELF_CLASS_32, ELF_DATA_LSB, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    static struct image img;
    static struct image strtab;
    unsigned long name_offsets[TEST_SYMBOL_COUNT];
    unsigned long symtab_offset, strtab_offset, names_offset, sections_offset;
    size_t i;
    FILE *f;

    img.len = 0;
    strtab.len = 0;
    image_add(&strtab, "", 1);
    for (i = 0; i < TEST_SYMBOL_COUNT; i++) {
        name_offsets[i] = 0;
        if (test_symbols[i].name[0] != '\0') {
            name_offsets[i] = (unsigned long)strtab.len;
            image_add(&strtab, test_symbols[i].name,
                      strlen(test_symbols[i].name) + 1);
        }
    }

    for (i = 0; i < ELF_HEADER_SIZE; i++)
        image_add(&img, "", 1);
    symtab_offset = (unsigned long)img.len;
    for (i = 0; i < TEST_SYMBOL_COUNT; i++) {
        unsigned char info[2];

        info[0] = (unsigned char)test_symbols[i].info;
        info[1] = 0;
        image_add32(&img, name_offsets[i]);
        image_add32(&img, test_symbols[i].value);
        image_add32(&img, test_symbols[i].size);
        image_add(&img, info, 2);
        image_add16(&img, test_symbols[i].shndx);
    }
    strtab_offset = (unsigned long)img.len;
    image_add(&img, strtab.data, strtab.len);
    names_offset = (unsigned long)img.len;
    image_add(&img, section_names, sizeof(section_names));
    while (img.len % 4 != 0)
        image_add(&img, "", 1);
    sections_offset = (unsigned long)img.len;
    image_add_section(&img, 0, 0, 0, 0, 0, 0, 0);
    image_add_section(&img, 1, 8, 0x00100000UL, 0, 0x1000, 0, 0);
    image_add_section(&img, 7, 8, 0x00200000UL, 0, 0x1000, 0, 0);
    image_add_section(&img, 13, ELF_SHT_SYMTAB, 0, symtab_offset,
                      (unsigned long)(TEST_SYMBOL_COUNT * ELF_SYMBOL_SIZE), 4,
                      ELF_SYMBOL_SIZE);
    image_add_section(&img, 21, ELF_SHT_STRTAB, 0, strtab_offset,
                      (unsigned long)strtab.len, 0, 0);
    image_add_section(&img, 29, ELF_SHT_STRTAB, 0, names_offset,
                      (unsigned long)sizeof(section_names), 0, 0);

    /* Fill in the file header now that the layout is known. */
    {
        struct image header;

        header.len = 0;
        image_add(&header, magic, sizeof(magic));
        image_add16(&header, 2);                    /* executable */
        image_add16(&header, ELF_MACHINE_MIPS);
        image_add32(&header, 1);                    /* version */
        image_add32(&header, 0x00100000UL);         /* entry point */
        image_add32(&header, 0);                    /* no program headers */
        image_add32(&header, sections_offset);
        image_add32(&header, 0);                    /* flags */
        image_add16(&header, ELF_HEADER_SIZE);
        image_add16(&header, 0);
        image_add16(&header, 0);
        image_add16(&header, ELF_SECTION_SIZE);
        image_add16(&header, 6);                    /* section count */
        image_add16(&header, 5);                    /* .shstrtab index */
        memcpy(img.data, header.data, ELF_HEADER_SIZE);
    }

    f = fopen(path, "wb");
    if (f == NULL) {
        fprintf(stderr, "symindex: cannot create %s\n", path);
        return 1;
    }
    if (fwrite(img.data, 1, img.len, f) != img.len || fclose(f) != 0) {
        fprintf(stderr, "symindex: cannot write %s\n", path);
        return 1;
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/* CodeWarrior link maps                                              */
/* ------------------------------------------------------------------ */

/* A set of strings that remembers what it has seen. */
struct string_set {
    char **slots;
    size_t slot_count;      /* a power of two, or 0 before first use */
    size_t used;
};

/* Hash a string (FNV-1a). */
static unsigned long hash_string(const char *s)
{
    unsigned long h = 2166136261UL;

    for (; *s != '\0'; s++) {
        h ^= (unsigned char)*s;
        h = (h * 16777619UL) & 0xffffffffUL;
    }
    return h;
}

/* Put an already-allocated string into a free slot of the table. */
static void set_place(char **slots, size_t slot_count, char *s)
{
    size_t i = (size_t)hash_string(s) & (slot_count - 1);

    while (slots[i] != NULL)
        i = (i + 1) & (slot_count - 1);
    slots[i] = s;
}

/* Double the table once it is half full. */
static void set_grow(struct string_set *set)
{
    size_t new_count = set->slot_count != 0 ? set->slot_count * 2 : 1024;
    char **slots = (char **)calloc(new_count, sizeof(*slots));
    size_t i;

    if (slots == NULL)
        fatal("out of memory");
    for (i = 0; i < set->slot_count; i++) {
        if (set->slots[i] != NULL)
            set_place(slots, new_count, set->slots[i]);
    }
    free(set->slots);
    set->slots = slots;
    set->slot_count = new_count;
}

/* Add a string; returns 1 if it was new and 0 if it was already present. */
static int set_add(struct string_set *set, const char *s)
{
    size_t i;
    char *copy;

    if (set->used * 2 >= set->slot_count)
        set_grow(set);
    i = (size_t)hash_string(s) & (set->slot_count - 1);
    while (set->slots[i] != NULL) {
        if (strcmp(set->slots[i], s) == 0)
            return 0;
        i = (i + 1) & (set->slot_count - 1);
    }
    copy = (char *)malloc(strlen(s) + 1);
    if (copy == NULL)
        fatal("out of memory");
    strcpy(copy, s);
    set->slots[i] = copy;
    set->used++;
    return 1;
}

/* Free the table and the strings it holds. */
static void set_free(struct string_set *set)
{
    size_t i;

    for (i = 0; i < set->slot_count; i++)
        free(set->slots[i]);
    free(set->slots);
    set->slots = NULL;
    set->slot_count = 0;
    set->used = 0;
}

/* Read one line of any length without its terminator; returns 0 at the end. */
static int read_line(FILE *f, struct text *line)
{
    int ch;
    int got = 0;

    text_clear(line);
    while ((ch = getc(f)) != EOF) {
        got = 1;
        if (ch == '\n')
            break;
        text_add_char(line, ch == '\0' ? ' ' : (char)ch);
    }
    return got;
}

/* Cut trailing spaces, tabs and carriage returns off a string of length n. */
static void trim_end(char *s, size_t n)
{
    while (n > 0 && (s[n - 1] == ' ' || s[n - 1] == '\t' || s[n - 1] == '\r'))
        n--;
    s[n] = '\0';
}

/* True if s is a non-empty run of lower-case letters. */
static int is_lower_word(const char *s)
{
    if (*s == '\0')
        return 0;
    for (; *s != '\0'; s++) {
        if (*s < 'a' || *s > 'z')
            return 0;
    }
    return 1;
}

/* The fields of one closure line; they point into the line buffer. */
struct closure_entry {
    char *symbol;
    char *kind;
    char *binding;
    const char *library;
    char *object;
};

/*
 * Split "<indent><depth>] <symbol> (<kind>,<binding>) found in <lib> <obj>"
 * in place.  Returns 0 for every other line, including section lines.
 */
static int parse_closure_line(char *line, struct closure_entry *entry)
{
    static const char marker[] = " found in ";
    char *p = line;
    char *body;
    char *found = NULL;
    char *next;
    char *paren;
    char *comma;
    char *where;
    size_t n;

    while (*p == ' ')
        p++;
    if (!is_digit((unsigned char)*p))
        return 0;
    while (is_digit((unsigned char)*p))
        p++;
    if (p[0] != ']' || p[1] != ' ')
        return 0;
    body = p + 2;

    /* The symbol may itself contain the marker text; the last one counts. */
    for (next = strstr(body, marker); next != NULL;
         next = strstr(next + 1, marker))
        found = next;
    if (found == NULL)
        return 0;
    *found = '\0';
    where = found + (sizeof(marker) - 1);

    /* The "(kind,binding)" group is the last thing before the marker. */
    n = strlen(body);
    if (n < 2 || body[n - 1] != ')')
        return 0;
    body[n - 1] = '\0';
    paren = strrchr(body, '(');
    if (paren == NULL || paren == body || paren[-1] != ' ')
        return 0;
    comma = strchr(paren, ',');
    if (comma == NULL)
        return 0;
    *comma = '\0';
    entry->kind = paren + 1;
    entry->binding = comma + 1;
    if (!is_lower_word(entry->kind) || !is_lower_word(entry->binding))
        return 0;
    if (strcmp(entry->kind, "section") == 0)
        return 0;
    trim_end(body, (size_t)(paren - body));
    if (body[0] == '\0')
        return 0;
    entry->symbol = body;

    /* "<library> <object>", or a lone object linked without a library. */
    while (*where == ' ')
        where++;
    trim_end(where, strlen(where));
    if (where[0] == '\0')
        return 0;
    p = strchr(where, ' ');
    if (p == NULL) {
        entry->library = "-";
        entry->object = where;
    } else {
        *p++ = '\0';
        while (*p == ' ')
            p++;
        entry->library = where;
        entry->object = p;
    }
    return 1;
}

/* Print one row per distinct symbol of a CodeWarrior link map's closure. */
static int index_map(const char *path, const char *label)
{
    FILE *f = fopen(path, "rb");
    struct pool pool;
    struct text *line;
    struct text *key;
    struct text *scratch;
    struct string_set seen;
    int status = 0;

    if (f == NULL) {
        fprintf(stderr, "symindex: cannot open %s\n", path);
        return 1;
    }
    pool_init(&pool);
    line = text_new(&pool);
    key = text_new(&pool);
    scratch = text_new(&pool);
    seen.slots = NULL;
    seen.slot_count = 0;
    seen.used = 0;

    if (!read_line(f, line) || strncmp(text_str(line), "# Link map of ", 14) != 0) {
        fprintf(stderr, "symindex: %s is not a CodeWarrior link map\n", path);
        status = 1;
    }
    while (status == 0 && read_line(f, line)) {
        struct closure_entry entry;

        if (pool.overflow) {
            fprintf(stderr, "symindex: %s has a line longer than %lu bytes\n",
                    path, TEXT_LIMIT);
            status = 1;
            break;
        }
        /* The closure ends where the next "#" section of the map starts. */
        if (text_str(line)[0] == '#')
            break;
        if (line->len == 0 || !parse_closure_line(line->data, &entry))
            continue;
        text_clear(key);
        text_add(key, entry.library);
        text_add_char(key, '\t');
        text_add(key, entry.object);
        text_add_char(key, '\t');
        text_add(key, entry.symbol);
        if (!set_add(&seen, text_str(key)))
            continue;
        put_field(label);
        putchar('\t');
        put_field(entry.kind);
        putchar('\t');
        put_field(entry.binding);
        putchar('\t');
        put_field(entry.library);
        putchar('\t');
        put_field(entry.object);
        putchar('\t');
        put_names(entry.symbol, scratch);
    }
    if (ferror(f)) {
        fprintf(stderr, "symindex: cannot read %s\n", path);
        status = 1;
    }
    fclose(f);
    set_free(&seen);
    pool_free(&pool);
    return status;
}

/* ------------------------------------------------------------------ */
/* Built-in checks                                                    */
/* ------------------------------------------------------------------ */

/* A mangled name and the demangled text it must produce. */
struct demangle_case {
    const char *mangled;
    const char *expected;
};

/* Demangler checks; a case whose two strings match must pass through. */
static const struct demangle_case demangle_cases[] = {
    /* CodeWarrior */
    { "execDot_VectorVector__7UObjectFR6FFramePv",
      "UObject::execDot_VectorVector(FFrame&, void*)" },
    { "appBitsCpy__FPUciPUcii",
      "appBitsCpy(unsigned char*, int, unsigned char*, int, int)" },
    { "init_ps2_system__Fv", "init_ps2_system(void)" },
    { "__vt__12hkBaseObject", "hkBaseObject::__vtable" },
    { "s_instance__8hkMemory", "hkMemory::s_instance" },
    { "__ct__Q23std7__nInitFv", "std::__nInit::__nInit(void)" },
    { "StartFadeOut__13CThemeChannelFv", "CThemeChannel::StartFadeOut(void)" },
    { "isIPAddress__FPc", "isIPAddress(char*)" },
    { "hkDummySingletoncreate__Fv", "hkDummySingletoncreate(void)" },
    { "__ct__Q23std39basic_filebuf<c,Q23std14char_traits<c>>FP7__sFILE",
      "std::basic_filebuf<char, std::char_traits<char>>::basic_filebuf(__sFILE*)" },
    { "Foo__3BarCFv", "Bar::Foo(void) const" },
    { "__dt__3BarFv", "Bar::~Bar(void)" },
    { "__as__3BarFRC3Bar", "Bar::operator=(const Bar&)" },
    { "__vc__3BarCFi", "Bar::operator[](int) const" },
    { "__nwa__FUi", "operator new[](unsigned int)" },
    { "__ls__FR3OutRC3Bar", "operator<<(Out&, const Bar&)" },
    { "__opPCc__3BarCFv", "Bar::operator const char*(void) const" },
    { "__opQ211Box<3Bar,0>4Item__3BarFv", "Bar::operator Box<Bar, 0>::Item(void)" },
    { "__open__3BarFv", "Bar::__open(void)" },
    { "__ct__11Box<3Bar,4>Fv", "Box<Bar, 4>::Box(void)" },
    { "Make<3Bar>__FP3Bar_P3Bar", "Bar* Make<Bar>(Bar*)" },
    { "Set__3BarFPFi_vA4_fM3BarFPCvPv_ve",
      "Bar::Set(void (*)(int), float[4], void (Bar::*)(const void*, void*), ...)" },
    { "Walk__3BarFPA3_CiCPCcRx",
      "Bar::Walk(const int (*)[3], const char* const, long long&)" },
    { "a__b__3BarFv", "Bar::a__b(void)" },
    { "__RTTI__Q23Out3Bar", "Out::Bar::__RTTI" },
    { "@EX@Foo__3BarFv", "@EX@Bar::Foo(void)" },
    { "@12@Foo__3BarFv", "@12@Bar::Foo(void)" },
    { "@8@72@__dt__3BarFv", "@8@72@Bar::~Bar(void)" },
    { "@LOCAL@Foo__3BarFv@count", "@LOCAL@Bar::Foo(void)@count" },
    { "@STRING@Foo__3BarFv@4", "@STRING@Bar::Foo(void)@4" },
    { "@GUARD@count__11Box<3Bar,0>", "@GUARD@Box<Bar, 0>::count" },
    { "SND_fn_tduGetLowestResourceSwitch", "SND_fn_tduGetLowestResourceSwitch" },
    { "__sinit_Core.cpp", "__sinit_Core.cpp" },
    { ".p__sinit_UnController.cpp", ".p__sinit_UnController.cpp" },
    { "@GUARD@fin$1688", "@GUARD@fin$1688" },
    { "@Foo__3BarFv", "@Foo__3BarFv" },
    { "my__name", "my__name" },
    { "Foo__3Ba", "Foo__3Ba" },
    { "Foo__3BarFq", "Foo__3BarFq" },
    { "Foo__3BarFvv", "Foo__3BarFvv" },
    { "Foo__3BarFP1", "Foo__3BarFP1" },
    /* SN Systems */
    { "__0FJDiskReadyv", "DiskReady(void)" },
    { "__0FSGetPSPFullFileNamePCcPc", "GetPSPFullFileName(const char*, char*)" },
    { "__0FIMainLoopP6HUEngine", "MainLoop(UEngine*)" },
    { "__0FKInitEngineR6SFFileManagerLinearPc",
      "InitEngine(FFileManagerLinear&, char*)" },
    { "__0FO_GetDeviceTypev", "_GetDeviceType(void)" },
    { "__0fNUGUIComponentNexecActualTopR6GFFramePv",
      "UGUIComponent::execActualTop(FFrame&, void*)" },
    { "__0fDBarDFooiK", "Bar::Foo(int) const" },
    { "__0fDBarDFoovT", "static Bar::Foo(void)" },
    { "__0fDBarDFooPCvTBNCB",
      "Bar::Foo(const void*, const void*, const void*, const void*)" },
    { "__0oDBarctv", "Bar::Bar(void)" },
    { "__0oDBardtv", "Bar::~Bar(void)" },
    { "__0oDBarasRC6DBar", "Bar::operator=(const Bar&)" },
    { "__0oDBaraplRC6DBar", "Bar::operator+=(const Bar&)" },
    { "__0oDBarop6DQuxv", "Bar::operator Qux(void)" },
    { "__0OlsR6DOutR6DBar", "operator<<(Out&, Bar&)" },
    { "__0dDBarFcount", "Bar::count" },
    { "__0dDBarG__vtbl", "Bar::__vtable" },
    { "__0FEMake76DBar_P6DBar_P9BA", "Bar* Make<Bar>(Bar*)" },
    { "__0fDBox76DBar4A_DGeti_R9BA", "Bar& Box<Bar, 0>::Get(int)" },
    { "__0f5DOutDBarDFooPFPv_v", "Out::Bar::Foo(void (*)(void*))" },
    { "__0F5DOutDFooi", "Out::Foo(int)" },
    { "__0FDFooULPLSc", "Foo(unsigned long long, long long*, signed char)" },
    { "__0FDFooPMDBarFR6DBari_v", "Foo(void (Bar::*)(Bar&, int))" },
    { "__0fDBar0AThisIdentifierIsExactlyFiftyTwoCharactersLongForTestv",
      "Bar::ThisIdentifierIsExactlyFiftyTwoCharactersLongForTest(void)" },
    { "__0fDBox76DBar_DGetv_R9BAK", "Bar& Box<Bar>::Get(void) const" },
    { "__0fDBox76DBar_EMakei_P9BAT", "static Bar* Box<Bar>::Make(int)" },
    { "__0fDBox7P6DBar_EFindRC9BA_iK", "int Box<Bar*>::Find(Bar* const&) const" },
    { "__0oDBox76DBar4A_asRC6DBox79BACi__R6DBox79BACi_",
      "Box<Bar, 0>& Box<Bar, 0>::operator=(const Box<Bar, 0>&)" },
    { "__0FEFind7P6DBarPFR6DBar_b_9BATB9CA_9BA",
      "Bar* Find<Bar*, bool (*)(Bar&)>(Bar*, Bar*, bool (*)(Bar&))" },
    { "__0Onw76DBar_UiR6DBox79BA4A__Pv",
      "void* operator new<Bar>(unsigned int, Box<Bar, 0>&)" },
    { "__0fDBox76DBar_DGet7i_9BC_v", "__0fDBox76DBar_DGet7i_9BC_v" },
    { "__0fDBarDFooiKT", "__0fDBarDFooiKT" },
    { "__0FJDiskReady", "__0FJDiskReady" },
    { "__0FJDiskReadyq", "__0FJDiskReadyq" },
    { "__0fDBox76DBar_DGeti_R9CA", "__0fDBox76DBar_DGeti_R9CA" },
    { "__0fDBox76DBar_DGeti_R9BB", "__0fDBox76DBar_DGeti_R9BB" },
    { "__0fDBox76DBar44_DGeti", "__0fDBox76DBar44_DGeti" }
};

#define DEMANGLE_CASE_COUNT (sizeof(demangle_cases) / sizeof(demangle_cases[0]))

/* Run the demangler checks; returns the process exit status. */
static int run_selftest(void)
{
    struct pool pool;
    struct text *out;
    size_t i;
    int failures = 0;

    pool_init(&pool);
    out = text_new(&pool);
    for (i = 0; i < DEMANGLE_CASE_COUNT; i++) {
        const char *got = demangled_or_same(demangle_cases[i].mangled, out);

        if (strcmp(got, demangle_cases[i].expected) != 0) {
            printf("FAIL %s\n  expected %s\n  got      %s\n",
                   demangle_cases[i].mangled, demangle_cases[i].expected,
                   got);
            failures++;
        }
    }
    pool_free(&pool);
    printf("selftest: %lu cases, %d failures\n",
           (unsigned long)DEMANGLE_CASE_COUNT, failures);
    return failures == 0 ? 0 : 1;
}

/* ------------------------------------------------------------------ */
/* Command line                                                       */
/* ------------------------------------------------------------------ */

/* Print the usage text and return the usage-error exit status. */
static int usage(void)
{
    fputs("usage: symindex elf FILE [--label NAME]\n"
          "       symindex mwmap FILE [--label NAME]\n"
          "       symindex demangle NAME...\n"
          "       symindex mkelf FILE\n"
          "       symindex --selftest\n", stderr);
    return 2;
}

/* Run the elf or mwmap command with its "FILE [--label NAME]" arguments. */
static int run_index(const char *command, int argc, char **argv)
{
    const char *path = NULL;
    const char *label = NULL;
    int i;

    for (i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--label") == 0) {
            if (i + 1 >= argc || label != NULL)
                return usage();
            label = argv[++i];
        } else if (path == NULL) {
            path = argv[i];
        } else {
            return usage();
        }
    }
    if (path == NULL)
        return usage();
    if (label == NULL)
        label = base_name(path);
    if (strcmp(command, "elf") == 0)
        return index_elf(path, label);
    return index_map(path, label);
}

/* Entry point: dispatch on the subcommand. */
int main(int argc, char **argv)
{
    int status;

#ifdef _WIN32
    /* Keep line ends as "\n" so the tables are the same on every host. */
    _setmode(_fileno(stdout), _O_BINARY);
#endif
    if (argc < 2)
        return usage();
    if (strcmp(argv[1], "--selftest") == 0 && argc == 2) {
        status = run_selftest();
    } else if (strcmp(argv[1], "mkelf") == 0 && argc == 3) {
        status = write_test_elf(argv[2]);
    } else if (strcmp(argv[1], "demangle") == 0 && argc >= 3) {
        struct pool pool;
        struct text *out;
        int i;

        pool_init(&pool);
        out = text_new(&pool);
        for (i = 2; i < argc; i++) {
            put_field(demangled_or_same(argv[i], out));
            putchar('\n');
        }
        pool_free(&pool);
        status = 0;
    } else if ((strcmp(argv[1], "elf") == 0 || strcmp(argv[1], "mwmap") == 0)
               && argc >= 3) {
        status = run_index(argv[1], argc - 2, argv + 2);
    } else {
        return usage();
    }
    if (fflush(stdout) != 0 || ferror(stdout)) {
        fprintf(stderr, "symindex: cannot write output\n");
        return 1;
    }
    return status;
}
