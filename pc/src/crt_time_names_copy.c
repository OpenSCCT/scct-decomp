#include "crt_locale_time_types.h"

typedef unsigned LocaleNamesSize;
void *malloc(LocaleNamesSize);
LocaleNamesSize strlen(const char *);
char *strcpy(char *, const char *);
void *memcpy(void *, const void *, LocaleNamesSize);

#define COPY_NAME(field) \
    result->field = cursor; \
    cursor += strlen(strcpy(cursor, names->field)) + 1

struct LocaleTimeNames *__cdecl steam_Gettnames(void)
{
    struct LocaleTimeNames *names = __lc_time_curr;
    struct LocaleTimeNames *result;
    char *cursor;
    LocaleNamesSize i, length = 0;
    for (i = 0; i < 7; ++i)
        length += strlen(names->short_day[i]) + strlen(names->long_day[i]) + 2;
    for (i = 0; i < 12; ++i)
        length += strlen(names->short_month[i]) + strlen(names->long_month[i]) + 2;
    length += strlen(names->am_pm[1]) + strlen(names->am_pm[0]) + 2;
    length += strlen(names->short_date) + 1;
    length += strlen(names->long_date) + 1;
    length += strlen(names->time) + 1;
    result = malloc(sizeof(*result) + length);
    if (result) {
        cursor = (char *)(result + 1);
        memcpy(result, __lc_time_curr, sizeof(*result));
        for (i = 0; i < 7; ++i) {
            COPY_NAME(short_day[i]);
            COPY_NAME(long_day[i]);
        }
        for (i = 0; i < 12; ++i) {
            COPY_NAME(short_month[i]);
            COPY_NAME(long_month[i]);
        }
        COPY_NAME(am_pm[0]);
        COPY_NAME(am_pm[1]);
        COPY_NAME(short_date);
        COPY_NAME(long_date);
        result->time = cursor;
        strcpy(cursor, names->time);
    }
    return result;
}
