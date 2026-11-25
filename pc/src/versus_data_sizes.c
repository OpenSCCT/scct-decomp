struct ByteRangeData {
    unsigned char unknown[12];
    const char *first;
    /* Preserve the separate end-pointer load observed in the retail body. */
    const char *volatile last;
};

unsigned __fastcall versus_range_data_size(const struct ByteRangeData *value) {
    return (unsigned)(value->last - value->first);
}
