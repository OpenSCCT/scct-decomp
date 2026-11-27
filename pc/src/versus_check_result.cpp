#include "versus_level_trace_vector.h"
#include "versus_level_trace_types.h"

// The Versus startup at 0x2d8640 initializes this pointer to the zero vector.
extern FVector *GZeroVector_10ccacc0;

FCheckResult::FCheckResult(FLOAT InTime, FCheckResult *InNext)
    : Next(InNext), Actor(0), Location(*GZeroVector_10ccacc0),
      Normal(*GZeroVector_10ccacc0), Primitive(0), Time(InTime), Item(-1),
      Material(0), bNonBlocking(0)
{
}
