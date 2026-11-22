struct Bank;
/* FAKEMATCH: the original passes a bank as a stack argument; this one-member struct only steers
   that stack slot. */
struct BankValue { struct Bank *ptr; };
/* FAKEMATCH: the original passes a bank reference as a stack argument; this one-member struct
   only steers that stack slot. */
struct BankRef { struct Bank **ptr; };
struct Banks { struct Bank **data; int count; };
struct Records { void *data; int count; };
/* FAKEMATCH: the original members in this range are not recovered; these padding members are not
   named by offset and only push later members into place. */
struct Mesh {
    unsigned char reserved[0x78];
    struct Banks banks;
    struct Records records;
};
extern void __fastcall grow_banks(struct Banks *, float);
extern int __fastcall add_zeroed(struct Records *, float);
/* FAKEMATCH: bit pattern passed as a float argument; the union integer word fills the stack slot
   that the original fills with an integer. */
union StackInt { int value; float argument; };

__declspec(noinline) int __fastcall add_unique_bank(struct Banks *list, struct BankRef bank)
{
    static const union StackInt width = {4};
    int i;
    for (i = 0; i < list->count; ++i) {
        if (list->data[i] == *bank.ptr)
            return i;
    }
    i = list->count++;
    grow_banks(list, width.argument);
    list->data[i] = *bank.ptr;
    return i;
}

int __fastcall register_bank(struct Mesh *mesh, struct BankValue bank)
{
    static const union StackInt one = {1};
    if (bank.ptr) {
        struct BankRef reference;
        reference.ptr = &bank.ptr;
        add_unique_bank(&mesh->banks, reference);
        if (mesh->banks.count > mesh->records.count)
            add_zeroed(&mesh->records, one.argument);
    }
    return 1;
}
