// Work item 0046: Versus RVA 0xc820-0xc899.
typedef float FLOAT;

// Unreal Engine 2 Core templates (UnTemplate.h).
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }

// RVA 0xc860: out-of-line instantiation of Max<FLOAT>.
template FLOAT Max<FLOAT>(const FLOAT A, const FLOAT B);
// RVA 0xc880: out-of-line instantiation of Min<FLOAT>.
template FLOAT Min<FLOAT>(const FLOAT A, const FLOAT B);

// RVA 0xc820 receives its iterator in EAX (link-time-generated register
// convention, likely an inlined TObjectIterator<...>::operator++ with an IsA
// check against a StaticClass object at 0x10cc4d30). Not expressible in C.
