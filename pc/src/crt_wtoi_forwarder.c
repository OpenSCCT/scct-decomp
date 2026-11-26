/* crt_wtoi_forwarder.c -- Microsoft CRT _wtoi forwarding to _wtol. */
typedef unsigned short WideChar;

extern long __cdecl _wtol(const WideChar *text);

/* _wtoi */
int __cdecl _wtoi(const WideChar *text)
{
    return (int)_wtol(text);
}
