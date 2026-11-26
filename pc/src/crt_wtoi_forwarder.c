typedef unsigned short WideChar;

extern long __cdecl _wtol(const WideChar *text);

int __cdecl _wtoi(const WideChar *text)
{
    return (int)_wtol(text);
}
