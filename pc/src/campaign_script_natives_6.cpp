// campaign_script_natives_6.cpp -- Campaign natives: canvas drawing and object lookup
#include "unreal_script.h"
#include "unreal_math.h"
#include "unreal_containers.h"
#include "unreal_class.h"
#include "campaign_engine_classes.h"

// UObject::execFindObject
// The release build compiles out the divide-by-zero script warning.
void UObject::execFindObject(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(ObjectName);
    P_GET_OBJECT(UClass, ObjectClass);
    P_FINISH;
    *(UObject **)Result = StaticFindObject(ObjectClass, 0, *ObjectName);
}

// UCanvas::execSetDrawColor
void UCanvas::execSetDrawColor(FFrame &Stack, RESULT_DECL)
{
    P_GET_BYTE(R);
    P_GET_BYTE(G);
    P_GET_BYTE(B);
    P_GET_BYTE_OPTX(A, 255);
    P_FINISH;
    SetDrawColor(R, G, B, A);
}

// UObject::execDynamicLoadObject
void UObject::execDynamicLoadObject(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Name);
    P_GET_OBJECT(UClass, Class);
    P_GET_UBOOL_OPTX(bMayFail, 0);
    P_FINISH;
    *(UObject **)Result = StaticLoadObject(Class, 0, *Name, 0, LOAD_NoWarn | (bMayFail ? LOAD_Quiet : 0), 0);
}

// UECanvas::execBeginScene
// The PC build reads these console rendering natives' parameters and ignores them.
void UECanvas::execBeginScene(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_GET_INT(C);
    P_GET_INT(D);
    P_GET_INT(E);
    P_GET_INT(F);
    P_GET_INT(G);
    P_FINISH;
}

// UECanvas::execDrawCameraPortal
void UECanvas::execDrawCameraPortal(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(Location);
    P_GET_ROTATOR(Rotation);
    P_GET_FLOAT_OPTX(FOV, 90.0f);
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
}

// UECanvas::execCreateDepthMask
void UECanvas::execCreateDepthMask(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_GET_INT(C);
    P_GET_INT(D);
    P_GET_INT(E);
    P_GET_BYTE(F);
    P_GET_INT(G);
    P_FINISH;
}

// UECanvas::execDrawActorPortal
void UECanvas::execDrawActorPortal(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(AActor, Actor);
    P_GET_VECTOR(Location);
    P_GET_ROTATOR(Rotation);
    P_GET_INT_OPTX(FOV, 90);
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
}

// UCanvas::execDrawText
void UCanvas::execDrawText(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(InText);
    P_GET_UBOOL_OPTX(CR, 1);
    P_FINISH;
    DrawText(*InText, CR);
}

// UCanvas::execTextSize
void UCanvas::execTextSize(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(InText);
    P_GET_FLOAT_REF(XL);
    P_GET_FLOAT_REF(YL);
    P_FINISH;
    TextSize(*InText, XL, YL);
}
