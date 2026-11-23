// campaign_leaf_1ce190.cpp -- function at VA 0x10ace190 with no this pointer. Given four floats it
// divides them by their length (the square root from the function at VA 0x10ccabc0, taken as 1
// when it is zero) and negates the first three: the inverse of a rotation quaternion. The type and
// function names are invented.

double Unk_10ccabc0(double Value);

struct UnkType_10ace190
{
    float X;
    float Y;
    float Z;
    float W;
};

// Unk_10ace190
void Unk_10ace190(UnkType_10ace190& Quat)
{
    float Length = Unk_10ccabc0(Quat.X * Quat.X + Quat.Y * Quat.Y + Quat.Z * Quat.Z
                                + Quat.W * Quat.W);
    if ( Length == 0.0f )
    {
        Length = 1.0f;
    }
    float Scale = 1.0f / Length;
    Quat.W = Quat.W * Scale;
    Quat.X = -(Quat.X * Scale);
    Quat.Y = -(Quat.Y * Scale);
    Quat.Z = -(Quat.Z * Scale);
}
