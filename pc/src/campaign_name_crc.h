/* campaign_name_crc.h -- declarations for the Campaign name CRC */
#ifndef CAMPAIGN_NAME_CRC_H
#define CAMPAIGN_NAME_CRC_H

extern unsigned campaign_name_crc_table[256];
unsigned *__cdecl name_crc(unsigned *destination, const char *name);

#endif
