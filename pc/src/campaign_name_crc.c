/* campaign_name_crc.c -- reflected CRC-32 for Campaign names */
#include "campaign_globals.h"
#include "campaign_name_crc.h"

/* name_crc */
unsigned *__cdecl name_crc(unsigned *destination, const char *name)
{
    unsigned checksum;
    int ch;
    if (table_pending) {
        int i;
        table_pending = 0;
        for (i = 0; i < 256; ++i) {
            unsigned entry = i;
            int bit;
            for (bit = 0; bit < 8; ++bit)
                if (entry & 1)
                    entry = (entry >> 1) ^ 0xedb88320u;
                else
                    entry >>= 1;
            campaign_name_crc_table[i] = entry;
        }
    }
    checksum = ~0u;
    while ((ch = *name++) != 0)
        checksum = campaign_name_crc_table[(checksum ^ ch) & 255] ^ (checksum >> 8);
    *destination = ~checksum;
    return destination;
}
