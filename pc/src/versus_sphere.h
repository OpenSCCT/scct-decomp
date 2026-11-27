#ifndef VERSUS_SPHERE_H
#define VERSUS_SPHERE_H

#include "versus_canvas_matrix.h"

struct FSphere : public FPlane {
    FSphere(const FVector &Center, FLOAT Radius) : FPlane(Center, Radius) {}
    FSphere(const FSphere &Sphere) : FPlane(Sphere, Sphere.W) {}
};

#endif
