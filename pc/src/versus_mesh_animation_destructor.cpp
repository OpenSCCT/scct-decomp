#include "versus_build.h"
#include "versus_mesh_animation.h"

UMeshAnimation::~UMeshAnimation()
{
    ConditionalDestroy();
}
