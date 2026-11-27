#ifndef VERSUS_SHADER_DECLARATION_H
#define VERSUS_SHADER_DECLARATION_H

#include "versus_build.h"
#include "unreal_types.h"

class FVertexStream;

struct FVertexComponent {
    DWORD Type;
    DWORD Function;
    FVertexComponent() {}
};

struct FStreamDeclaration {
    FVertexComponent Components[8];
    INT NumComponents;

    FStreamDeclaration() : NumComponents(0) {}
    FStreamDeclaration(FVertexStream *Stream);
};

struct FShaderDeclaration {
    FStreamDeclaration Streams[16];
    INT NumStreams;

    __declspec(noinline) FShaderDeclaration() : NumStreams(0) {}
    ~FShaderDeclaration() {}
};

#endif
