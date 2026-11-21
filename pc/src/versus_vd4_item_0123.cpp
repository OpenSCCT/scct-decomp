// Work item 0123: Versus RVA 0x1fcf0, a Core UnObj.cpp helper.
// It forwards to the FName overload of UObject::StaticFindObject at 0x17720
// (see item 0099) with the class at 0x10cc9ed8 (UObject::PrivateStaticClass,
// as labelled in item 0106). Whole-program optimisation passes ExactClass in
// EAX. Name of the helper is neutral: no symbol survives for it.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class UClass;

struct FName
{
	INT Index;
};

class UObject
{
public:
	static UClass PrivateStaticClass;	// 0x10cc9ed8
	static UClass* StaticClass() { return &PrivateStaticClass; }

	// RVA 0x17720: FName overload with two leading group names.
	static UObject* StaticFindObject( UClass* ObjectClass, UObject* InObjectPackage, FName Group1, FName Group2, FName ObjectName, UBOOL ExactClass );

	static UObject* Unnamed_1fcf0( UObject* InOuter, FName Group1, FName Group2, FName Name, UBOOL ExactClass );
};

// RVA 0x1fcf0
__declspec(noinline) UObject* UObject::Unnamed_1fcf0( UObject* InOuter, FName Group1, FName Group2, FName Name, UBOOL ExactClass )
{
	return StaticFindObject( StaticClass(), InOuter, Group1, Group2, Name, ExactClass );
}

// Scaffolding for the link, not part of the unit.
UObject* Driver_1fcf0( UObject* O, FName A, FName B, FName N, UBOOL E )
{
	return UObject::Unnamed_1fcf0( O, A, B, N, E );
}
