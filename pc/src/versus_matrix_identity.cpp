// versus_matrix_identity.cpp -- the singular inverse fallback
#include "versus_build.h"
#include "versus_canvas_matrix.h"

FMatrix GIdentityMatrix(
    FPlane(1.f, 0.f, 0.f, 0.f),
    FPlane(0.f, 1.f, 0.f, 0.f),
    FPlane(0.f, 0.f, 1.f, 0.f),
    FPlane(0.f, 0.f, 0.f, 1.f));
