/* sound_sample_decode.c -- fills a sample resource from its bank record (sndmanager.cpp) */
#include "sound_manager.h"

/* decode_sample_fields: copies the record and turns its offsets into addresses */
__declspec(noinline) void __cdecl decode_sample_fields(const tdstBlockResourceDisk *disk,
                                                       tdstBlockResourceMem *res,
                                                       unsigned long internal_base,
                                                       unsigned long external_base)
{
    res->Id = disk->Id;
    res->eType = disk->eType;
    res->unk_08 = disk->unk_14;
    res->uRes.stSample.bBalance = disk->bBalance;
    res->uRes.stSample.ulDataSize = disk->ulDataSize;
    res->uRes.stSample.unk_08 = disk->unk_20;
    res->uRes.stSample.unk_0c = disk->unk_24;
    res->uRes.stSample.owned = disk->owned;
    res->uRes.stSample.channels = disk->channels;
    res->uRes.stSample.external = disk->external;
    res->uRes.stSample.use_external = disk->use_external;
    res->uRes.stSample.unk_20 = disk->unk_30;
    if (disk->use_external) {
        res->uRes.stSample.payload_address = disk->external_offset + external_base;
        res->uRes.stSample.external_field = disk->external_field;
    } else {
        res->uRes.stSample.payload_address = disk->internal_offset + internal_base;
    }
}

/* decode_sound_sample: the same inside the tool lock, with the address and size of the data */
int __cdecl decode_sound_sample(const tdstBlockResourceDisk *disk, tdstBlockResourceMem *res,
                                unsigned long internal_base, unsigned long external_base)
{
    EnterCriticalSectionTool_();
    MouchardThreadTool(SNDMANAGER_CPP_FILE, 3357);
    res->uRes.stSample.sample_data = (void *)(disk->data_offset + external_base);
    res->uRes.stSample.buffer_size = disk->ulDataSize;
    decode_sample_fields(disk, res, internal_base, external_base);
    QuitCriticalSectionTool();
    return 1;
}
