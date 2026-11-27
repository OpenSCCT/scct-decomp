// versus_parse_callers.h -- link-only call sites for the Versus Core parsers
#include "src/versus_build.h"
#include "src/unreal_types.h"

UBOOL ParseCommand(const TCHAR** Stream, const TCHAR* Match);
UBOOL ParseToken(const TCHAR*& Stream, TCHAR* Result, INT MaxLen, UBOOL UseEscape);
UBOOL ParseLine(const TCHAR** Stream, TCHAR* Result, INT MaxLen, UBOOL Exact);

namespace ParserLink {

class FOutputDevice;

// Only the two consumers of parsed text are needed for these link roots.
class Viewport {
public:
    void ExecMacro(const TCHAR* Filename, FOutputDevice& Ar);
    UBOOL Exec(const TCHAR* Cmd, FOutputDevice& Ar);
};

extern const TCHAR ExecCommand[];

// UViewport::Exec's EXEC branch at 0x10ba93, with its 1,024-character filename buffer.
UBOOL ExecMacroCommand(Viewport& V, const TCHAR* Cmd, FOutputDevice& Ar) {
    if (!ParseCommand(&Cmd, ExecCommand))
        return 0;
    TCHAR Filename[1024];
    if (ParseToken(Cmd, Filename, 1024, 0))
        V.ExecMacro(Filename, Ar);
    return 1;
}

// UViewport::ExecMacro's loop at 0x10bb40 reads and executes one macro line at a time.
void ExecMacroLines(Viewport& V, const TCHAR* Data, FOutputDevice& Ar) {
    TCHAR Line[256];
    while (ParseLine(&Data, Line, 256, 0))
        V.Exec(Line, Ar);
}

} // namespace ParserLink
