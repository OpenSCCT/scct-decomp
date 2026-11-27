// versus_global_math.cpp -- global coordinates and scale initialized during Core startup
#include "versus_global_math.h"

FGlobalMath GMath;

// FGlobalMath::FGlobalMath
FGlobalMath::FGlobalMath()
    : UnitCoords(FVector(0.f, 0.f, 0.f), FVector(1.f, 0.f, 0.f),
                 FVector(0.f, 1.f, 0.f), FVector(0.f, 0.f, 1.f)),
      UnitScale(FVector(1.f, 1.f, 1.f), 0.f, SHEER_ZX),
      ViewCoords(FVector(0.f, 0.f, 0.f), FVector(0.f, 1.f, 0.f),
                 FVector(0.f, 0.f, -1.f), FVector(1.f, 0.f, 0.f))
{
}
