// campaign_script_natives_5.cpp -- Campaign natives: vector and rotator division, struct comparison, string conversion
#include "unreal_script.h"
#include "unreal_math.h"
#include "unreal_containers.h"
#include "unreal_field.h"

// UObject::execDivide_VectorFloat
// The release build compiles out the divide-by-zero script warning.
void UObject::execDivide_VectorFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_FLOAT(B);
    P_FINISH;
    if (B == 0.0f) {
        *(FVector *)Result = FVector(0.0f, 0.0f, 0.0f);
        return;
    }
    *(FVector *)Result = A / B;
}

// UObject::execDivide_RotatorFloat
void UObject::execDivide_RotatorFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_ROTATOR(A);
    P_GET_FLOAT(B);
    P_FINISH;
    if (B == 0.0f) {
        *(FRotator *)Result = FRotator(0, 0, 0);
        return;
    }
    *(FRotator *)Result = A / B;
}

// UObject::execDivideEqual_VectorFloat
void UObject::execDivideEqual_VectorFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR_REF(A);
    P_GET_FLOAT(B);
    P_FINISH;
    if (B == 0.0f) {
        *(FVector *)Result = FVector(0.0f, 0.0f, 0.0f);
        return;
    }
    *(FVector *)Result = (*A /= B);
}

// UObject::execDivideEqual_RotatorFloat
void UObject::execDivideEqual_RotatorFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_ROTATOR_REF(A);
    P_GET_FLOAT(B);
    P_FINISH;
    if (B == 0.0f) {
        *(FRotator *)Result = FRotator(0, 0, 0);
        return;
    }
    *(FRotator *)Result = (*A /= B);
}

// UObject::execMirrorVectorByNormal
void UObject::execMirrorVectorByNormal(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    B = B.SafeNormal();
    *(FVector *)Result = A - 2.0f * B * (B | A);
}

// UObject::execStructCmpEq
void UObject::execStructCmpEq(FFrame &Stack, RESULT_DECL)
{
    UStruct *Struct = (UStruct *)Stack.ReadObject();
    BYTE *Buffer1 = (BYTE *)appAlloca(Struct->PropertiesSize);
    BYTE *Buffer2 = (BYTE *)appAlloca(Struct->PropertiesSize);
    appMemzero(Buffer1, Struct->PropertiesSize);
    appMemzero(Buffer2, Struct->PropertiesSize);
    Stack.Step(this, Buffer1);
    Stack.Step(this, Buffer2);
    *(DWORD *)Result = Struct->StructCompare(Buffer1, Buffer2);
}

// UObject::execStructCmpNe
void UObject::execStructCmpNe(FFrame &Stack, RESULT_DECL)
{
    UStruct *Struct = (UStruct *)Stack.ReadObject();
    BYTE *Buffer1 = (BYTE *)appAlloca(Struct->PropertiesSize);
    BYTE *Buffer2 = (BYTE *)appAlloca(Struct->PropertiesSize);
    appMemzero(Buffer1, Struct->PropertiesSize);
    appMemzero(Buffer2, Struct->PropertiesSize);
    Stack.Step(this, Buffer1);
    Stack.Step(this, Buffer2);
    *(DWORD *)Result = !Struct->StructCompare(Buffer1, Buffer2);
}

// UObject::execFloatToString
void UObject::execFloatToString(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(F);
    *(FString *)Result = FString::Printf((const TCHAR *)L"%0.2f", F);
}

// UObject::execVectorToString
void UObject::execVectorToString(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(V);
    *(FString *)Result = FString::Printf((const TCHAR *)L"%0.2f,%0.2f,%0.2f", V.X, V.Y, V.Z);
}

// UObject::execRotatorToString
void UObject::execRotatorToString(FFrame &Stack, RESULT_DECL)
{
    P_GET_ROTATOR(R);
    *(FString *)Result = FString::Printf((const TCHAR *)L"%i,%i,%i", R.Pitch & 65535, R.Yaw & 65535, R.Roll & 65535);
}

// UObject::execStringToVector
void UObject::execStringToVector(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    const TCHAR *Stream = *Str;
    FVector Value(0.0f, 0.0f, 0.0f);
    Value.X = appAtof(Stream);
    Stream = appStrstr(Stream, (const TCHAR *)L",");
    if (Stream) {
        Value.Y = appAtof(++Stream);
        Stream = appStrstr(Stream, (const TCHAR *)L",");
        if (Stream)
            Value.Z = appAtof(++Stream);
    }
    *(FVector *)Result = Value;
}

// UObject::execStringToRotator
void UObject::execStringToRotator(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    const TCHAR *Stream = *Str;
    FRotator Rotator(0, 0, 0);
    Rotator.Pitch = appAtoi(Stream);
    Stream = appStrstr(Stream, (const TCHAR *)L",");
    if (Stream) {
        Rotator.Yaw = appAtoi(++Stream);
        Stream = appStrstr(Stream, (const TCHAR *)L",");
        if (Stream)
            Rotator.Roll = appAtoi(++Stream);
    }
    *(FRotator *)Result = Rotator;
}
