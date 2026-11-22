// campaign_leaf_5929f0.cpp -- one function at file offset 0x5929f0, preferred VA 0x10e929f0.
// When Points holds any entries it sets both corners of Box to the first point and then widens
// them to the per-component minimum and maximum of the x, y and z floats of every point. The
// function, structure, member and parameter names are invented; the offset and the bytes are the
// binary's.

struct UnkType_10e929f0_Point
{
    float X;
    float Y;
    float Z;
    float W;

    UnkType_10e929f0_Point& operator=(const UnkType_10e929f0_Point& Other)
    {
        X = Other.X;
        Y = Other.Y;
        Z = Other.Z;
        W = Other.W;
        return *this;
    }
};

struct UnkType_10e929f0_Array
{
    UnkType_10e929f0_Point* Data;
    int Num;
};

struct UnkType_10e929f0_Box
{
    UnkType_10e929f0_Point Min;
    UnkType_10e929f0_Point Max;
};

template<class T> inline T Min(const T A, const T B)
{
    return ( A < B ) ? A : B;
}

template<class T> inline T Max(const T A, const T B)
{
    return ( A > B ) ? A : B;
}

// Unk_10e929f0
void Unk_10e929f0(const UnkType_10e929f0_Array* Points, UnkType_10e929f0_Box* Box)
{
    int i;

    if ( Points->Num > 0 )
    {
        Box->Min = Points->Data[0];
        Box->Max = Points->Data[0];
        for ( i = 0; i < Points->Num; i++ )
        {
            Box->Min.X = Min(Box->Min.X, Points->Data[i].X);
            Box->Max.X = Max(Box->Max.X, Points->Data[i].X);
            Box->Min.Y = Min(Box->Min.Y, Points->Data[i].Y);
            Box->Max.Y = Max(Box->Max.Y, Points->Data[i].Y);
            Box->Min.Z = Min(Box->Min.Z, Points->Data[i].Z);
            Box->Max.Z = Max(Box->Max.Z, Points->Data[i].Z);
        }
    }
}
