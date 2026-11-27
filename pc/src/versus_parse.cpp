// versus_parse.cpp -- Core command, token and line parsing
#include "versus_build.h"
#include "unreal_types.h"

extern "C" __declspec(dllimport) unsigned int wcslen(const TCHAR* Text);
extern "C" __declspec(dllimport) int _wcsnicmp(const TCHAR* A, const TCHAR* B, unsigned int Count);

// appIsAlnum
inline UBOOL appIsAlnum(TCHAR Ch) {
    return (Ch >= 'a' && Ch <= 'z') || (Ch >= 'A' && Ch <= 'Z') || (Ch >= '0' && Ch <= '9');
}

// appStrlen
inline INT appStrlen(const TCHAR* Text) {
    return (INT)wcslen(Text);
}

// appStrnicmp
inline INT appStrnicmp(const TCHAR* A, const TCHAR* B, INT Count) {
    return _wcsnicmp(A, B, Count);
}

// ParseCommand
UBOOL ParseCommand(const TCHAR** Stream, const TCHAR* Match) {
    while (**Stream == ' ' || **Stream == '\t')
        ++*Stream;
    if (appStrnicmp(*Stream, Match, appStrlen(Match)) == 0) {
        *Stream += appStrlen(Match);
        if (!appIsAlnum(**Stream)) {
            while (**Stream == ' ' || **Stream == '\t')
                ++*Stream;
            return 1;
        }
        *Stream -= appStrlen(Match);
    }
    return 0;
}

// ParseToken
UBOOL ParseToken(const TCHAR*& Stream, TCHAR* Result, INT MaxLen, UBOOL UseEscape) {
    INT Len = 0;
    while (*Stream == ' ' || *Stream == '\t')
        ++Stream;
    if (*Stream == '"') {
        ++Stream;
        while (*Stream && *Stream != '"' && Len + 1 < MaxLen) {
            TCHAR Ch = *Stream++;
            if (Ch == '\\' && UseEscape) {
                Ch = *Stream++;
                if (!Ch)
                    break;
            }
            Result[Len++] = Ch;
        }
        if (*Stream == '"')
            ++Stream;
    } else {
        for (; *Stream && *Stream != ' ' && *Stream != '\t'; ++Stream)
            if (Len + 1 < MaxLen)
                Result[Len++] = *Stream;
    }
    Result[Len] = 0;
    return Len != 0;
}

// ParseLine
UBOOL ParseLine(const TCHAR** Stream, TCHAR* Result, INT MaxLen, UBOOL Exact) {
    UBOOL GotStream = 0;
    UBOOL IsQuoted = 0;
    UBOOL Ignore = 0;
    *Result = 0;
    while (**Stream && **Stream != '\n' && **Stream != '\r' && --MaxLen > 0) {
        if (!IsQuoted && !Exact && (*Stream)[0] == '/' && (*Stream)[1] == '/')
            Ignore = 1;
        if (!IsQuoted && !Exact && **Stream == '|')
            break;
        IsQuoted ^= **Stream == '"';
        GotStream = 1;
        if (!Ignore)
            *Result++ = *(*Stream)++;
        else
            ++*Stream;
    }
    if (Exact) {
        if (**Stream == '\r')
            ++*Stream;
        if (**Stream == '\n')
            ++*Stream;
    } else {
        while (**Stream == '\n' || **Stream == '\r' || **Stream == '|')
            ++*Stream;
    }
    *Result = 0;
    return **Stream != 0 || GotStream;
}
