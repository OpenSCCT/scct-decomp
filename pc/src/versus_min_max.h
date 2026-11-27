#ifndef VERSUS_MIN_MAX_H
#define VERSUS_MIN_MAX_H

template<class T> inline T Min(T A, T B) { return A <= B ? A : B; }
template<class T> inline T Max(T A, T B) { return A >= B ? A : B; }

#endif
