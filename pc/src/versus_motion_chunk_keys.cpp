// versus_motion_chunk_keys.cpp -- decompress individual skeletal animation keys.
#include "versus_build.h"
#include "versus_mesh_animation.h"

// GetTrackOrientation returns the requested quaternion, using the final key for negative indices.
void MotionChunk::GetTrackOrientation(INT TrackIndex, INT KeyIndex, FQuat &Orientation)
{
    const AnalogTrack &Track = AnimTracks(TrackIndex);
    if (KeyIndex < 0)
        KeyIndex = Track.KeyQuat.Num() - 1;

    const FCompressedQuatKey &Key = Track.KeyQuat(KeyIndex);
    const FLOAT InvScale = 1.f / 32767.f;
    FLOAT X = Key.X * InvScale;
    FLOAT Y = Key.Y * InvScale;
    FLOAT Z = Key.Z * InvScale;
    FLOAT W = Key.W * InvScale;
    FQuat Result = { X, Y, Z, W };
    Orientation = Result;
}

// GetTrackPosition returns the requested translation, using the final key for negative indices.
void MotionChunk::GetTrackPosition(INT TrackIndex, INT KeyIndex, FVector &Position)
{
    const AnalogTrack &Track = AnimTracks(TrackIndex);
    if (KeyIndex < 0)
        KeyIndex = Track.KeyPos.Num() - 1;

    const FCompressedVectorKey &Key = Track.KeyPos(KeyIndex);
    const FLOAT InvScale = 1.f / 32.f;
    Position = FVector(Key.X * InvScale, Key.Y * InvScale, Key.Z * InvScale);
}
