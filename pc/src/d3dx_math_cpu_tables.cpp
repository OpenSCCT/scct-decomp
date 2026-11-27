#include "d3dx_math_cpu_implementations.h"

unsigned get_feature_flags();

enum CpuFeatureFlag {
    CpuMmx = 0x20,
    Cpu3DNow = 0x80,
    CpuExtended3DNow = 0x100,
    CpuExtendedMmx = 0x200
};

void x86_D3DXInitFastTable(D3DXFASTTABLE *table)
{
    table->Vec2Transform = x86_D3DXVec2Transform;
    table->Vec3Transform = x86_D3DXVec3Transform;
    table->Vec4Transform = x86_D3DXVec4Transform;
    table->MatrixMultiply = x86_D3DXMatrixMultiply;
    table->MatrixMultiplyTranspose = x86_D3DXMatrixMultiplyTranspose;
    table->Vec2TransformNormal = x86_D3DXVec2TransformNormal;
    table->Vec3TransformNormal = x86_D3DXVec3TransformNormal;
    table->Vec3Normalize = x86_D3DXVec3Normalize;
}

void x3d_D3DXInitFastTable(D3DXFASTTABLE *table)
{
    const unsigned flags = get_feature_flags();
    if (!(flags & CpuMmx) || !(flags & Cpu3DNow))
        return;

    table->Vec2Transform = x3d_D3DXVec2Transform;
    table->Vec3Transform = x3d_D3DXVec3Transform;
    table->Vec4Transform = x3d_D3DXVec4Transform;
    table->MatrixMultiply = x3d_D3DXMatrixMultiply;
    table->Vec2TransformNormal = x3d_D3DXVec2TransformNormal;
    table->Vec3TransformNormal = x3d_D3DXVec3TransformNormal;
    table->Vec3Normalize = x3d_D3DXVec3Normalize;
    table->Vec4Normalize = x3d_D3DXVec4Normalize;
    table->Vec2TransformCoord = x3d_D3DXVec2TransformCoord;
    table->Vec3TransformCoord = x3d_D3DXVec3TransformCoord;
    table->MatrixfDeterminant = x3d_D3DXMatrixfDeterminant;
    table->PlaneFromPointNormal = x3d_D3DXPlaneFromPointNormal;
    table->PlaneFromPoints = x3d_D3DXPlaneFromPoints;
    table->Vec3Project = x3d_D3DXVec3Project;
    table->Vec3Unproject = x3d_D3DXVec3Unproject;
    table->Vec4Cross = x3d_D3DXVec4Cross;
    table->Vec2Hermite = x3d_D3DXVec2Hermite;
    table->MatrixInverse = x3d_D3DXMatrixInverse;
    table->QuaternionMultiply = x3d_D3DXQuaternionMultiply;
    table->QuaternionNormalize = x3d_D3DXQuaternionNormalize;
    table->PlaneNormalize = x3d_D3DXPlaneNormalize;
    table->PlaneIntersectLine = x3d_D3DXPlaneIntersectLine;
    table->QuaternionToAxisAngle = x3d_D3DXQuaternionToAxisAngle;
    table->QuaternionRotationMatrix = x3d_D3DXQuaternionRotationMatrix;
    table->QuaternionRotationYawPitchRoll = x3d_D3DXQuaternionRotationYawPitchRoll;
    table->MatrixTranslation = x3d_D3DXMatrixTranslation;
    table->MatrixShadow = x3d_D3DXMatrixShadow;
    table->MatrixReflect = x3d_D3DXMatrixReflect;
    table->QuaternionRotationAxis = x3d_D3DXQuaternionRotationAxis;
    table->MatrixRotationX = x3d_D3DXMatrixRotationX;
    table->MatrixRotationY = x3d_D3DXMatrixRotationY;
    table->MatrixRotationZ = x3d_D3DXMatrixRotationZ;
    table->MatrixScaling = x3d_D3DXMatrixScaling;
    table->PlaneTransform = x3d_D3DXPlaneTransform;
    table->QuaternionSlerp = x3d_D3DXQuaternionSlerp;
    table->QuaternionBaryCentric = x3d_D3DXQuaternionBaryCentric;
    table->MatrixTranspose = x3d_D3DXMatrixTranspose;
    table->MatrixRotationQuaternion = x3d_D3DXMatrixRotationQuaternion;
    table->MatrixTransformation = x3d_D3DXMatrixTransformation;
    table->MatrixRotationYawPitchRoll = x3d_D3DXMatrixRotationYawPitchRoll;
    table->MatrixAffineTransformation = x3d_D3DXMatrixAffineTransformation;
    table->MatrixRotationAxis = x3d_D3DXMatrixRotationAxis;
    table->QuaternionSquad = x3d_D3DXQuaternionSquad;
    table->QuaternionInverse = x3d_D3DXQuaternionInverse;
    table->Vec4BaryCentric = x3d_D3DXVec4BaryCentric;
    table->Vec3BaryCentric = x3d_D3DXVec3BaryCentric;
    table->Vec2BaryCentric = x3d_D3DXVec2BaryCentric;
    table->Vec2Normalize = x3d_D3DXVec2Normalize;
    table->Vec4Hermite = x3d_D3DXVec4Hermite;
    table->Vec3Hermite = x3d_D3DXVec3Hermite;
    table->QuaternionLn = x3d_D3DXQuaternionLn;
    table->QuaternionExp = x3d_D3DXQuaternionExp;
    table->Vec4CatmullRom = x3d_D3DXVec4CatmullRom;
    table->Vec2CatmullRom = x3d_D3DXVec2CatmullRom;
    table->Vec3CatmullRom = x3d_D3DXVec3CatmullRom;
    table->MatrixMultiplyTranspose = x3d_D3DXMatrixMultiplyTranspose;
    table->QuaternionSquadSetup = x3d_D3DXQuaternionSquadSetup;

    if ((flags & CpuExtended3DNow) && (flags & CpuExtendedMmx)) {
        table->Vec3Unproject = x3d_D3DXVec3Unproject_K7;
        table->MatrixInverse = x3d_D3DXMatrixInverse_K7;
        table->MatrixRotationQuaternion = x3d_D3DXMatrixRotationQuaternion_K7;
        table->MatrixTransformation = x3d_D3DXMatrixTransformation_K7;
        table->QuaternionRotationMatrix = x3d_D3DXQuaternionRotationMatrix_K7;
    }
}

void sse_D3DXInitFastTable(D3DXFASTTABLE *table)
{
    table->MatrixReflect = sse_D3DXMatrixReflect;
    table->Vec2Transform = sse_D3DXVec2Transform;
    table->PlaneFromPoints = sse_D3DXPlaneFromPoints;
    table->MatrixShadow = reinterpret_cast<MatrixShadowFunction>(sse_D3DXMatrixShadow);
    table->MatrixfDeterminant = sse_D3DXMatrixDeterminant;
    table->Vec2BaryCentric = sse_D3DXVec2BaryCentric;
    table->Vec2CatmullRom = sse_D3DXVec2CatmullRom;
    table->Vec2Hermite = sse_D3DXVec2Hermite;
    table->Vec4BaryCentric = sse_D3DXVec4BaryCentric;
    table->Vec4CatmullRom = sse_D3DXVec4CatmullRom;
    table->Vec4Hermite = sse_D3DXVec4Hermite;
    table->Vec3BaryCentric = sse_D3DXVec3BaryCentric;
    table->Vec3CatmullRom = sse_D3DXVec3CatmullRom;
    table->Vec3Hermite = sse_D3DXVec3Hermite;
    table->MatrixInverse = sse_D3DXMatrixInverse;
    table->PlaneIntersectLine = sse_D3DXPlaneIntersectLine;
    table->QuaternionRotationYawPitchRoll = sse_D3DXQuaternionRotationYawPitchRoll;
    table->QuaternionRotationMatrix = sse_D3DXQuaternionRotationMatrix;
    table->MatrixRotationY = sse_D3DXMatrixRotationY;
    table->MatrixRotationX = sse_D3DXMatrixRotationX;
    table->QuaternionMultiply = sse_D3DXQuaternionMultiply;
    table->QuaternionInverse = sse_D3DXQuaternionInverse;
    table->QuaternionNormalize = sse_D3DXQuaternionNormalize;
    table->Vec4Cross = sse_D3DXVec4Cross;
    table->PlaneNormalize = sse_D3DXPlaneNormalize;
    table->Vec4Normalize = sse_D3DXVec4Normalize;
    table->Vec3Normalize = sse_D3DXVec3Normalize;
    table->Vec3TransformCoord = sse_D3DXVec3TransformCoord;
    table->Vec2TransformCoord = sse_D3DXVec2TransformCoord;
    table->Vec3TransformNormal = sse_D3DXVec3TransformNormal;
    table->Vec2TransformNormal = sse_D3DXVec2TransformNormal;
    table->MatrixMultiplyTranspose = sse_D3DXMatrixMultiplyTranspose;
    table->MatrixMultiply = sse_D3DXMatrixMultiply;
    table->Vec4Transform = sse_D3DXVec4Transform;
    table->Vec3Transform = sse_D3DXVec3Transform;
}

void sse2_D3DXInitFastTable(D3DXFASTTABLE *table)
{
    table->QuaternionSlerp = sse2_QuaternionSlerp;
    table->Vec2Transform = sse_D3DXVec2Transform;
    table->MatrixReflect = sse2_D3DXMatrixReflect;
    table->PlaneFromPoints = sse2_D3DXPlaneFromPoints;
    table->MatrixShadow = reinterpret_cast<MatrixShadowFunction>(sse2_D3DXMatrixShadow);
    table->MatrixfDeterminant = sse2_D3DXMatrixDeterminant;
    table->Vec2BaryCentric = sse_D3DXVec2BaryCentric;
    table->Vec2CatmullRom = sse_D3DXVec2CatmullRom;
    table->Vec2Hermite = sse_D3DXVec2Hermite;
    table->Vec4BaryCentric = sse_D3DXVec4BaryCentric;
    table->Vec4CatmullRom = sse_D3DXVec4CatmullRom;
    table->Vec4Hermite = sse_D3DXVec4Hermite;
    table->Vec3BaryCentric = sse_D3DXVec3BaryCentric;
    table->Vec3CatmullRom = sse_D3DXVec3CatmullRom;
    table->Vec3Hermite = sse_D3DXVec3Hermite;
    table->MatrixInverse = sse2_D3DXMatrixInverse;
    table->PlaneIntersectLine = sse_D3DXPlaneIntersectLine;
    table->QuaternionRotationYawPitchRoll = sse2_D3DXQuaternionRotationYawPitchRoll;
    table->QuaternionRotationMatrix = sse2_D3DXQuaternionRotationMatrix;
    table->MatrixRotationY = sse2_D3DXMatrixRotationY;
    table->MatrixRotationX = sse2_D3DXMatrixRotationX;
    table->QuaternionMultiply = sse_D3DXQuaternionMultiply;
    table->QuaternionInverse = sse2_D3DXQuaternionInverse;
    table->QuaternionNormalize = sse_D3DXQuaternionNormalize;
    table->Vec4Cross = sse2_D3DXVec4Cross;
    table->PlaneNormalize = sse2_D3DXPlaneNormalize;
    table->Vec4Normalize = sse_D3DXVec4Normalize;
    table->Vec3Normalize = sse2_D3DXVec3Normalize;
    table->Vec3TransformCoord = sse2_D3DXVec3TransformCoord;
    table->Vec2TransformCoord = sse_D3DXVec2TransformCoord;
    table->Vec3TransformNormal = sse2_D3DXVec3TransformNormal;
    table->Vec2TransformNormal = sse_D3DXVec2TransformNormal;
    table->MatrixMultiplyTranspose = sse2_D3DXMatrixMultiplyTranspose;
    table->MatrixMultiply = sse2_D3DXMatrixMultiply;
    table->Vec4Transform = sse2_D3DXVec4Transform;
    table->Vec3Transform = sse2_D3DXVec3Transform;
}
