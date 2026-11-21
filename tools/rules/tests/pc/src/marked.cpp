// no-game-data: synthetic
// A class template is named after the class, not after its parameter.
template<class T> class Box {
public:
	T *Data;
	int Num() const;
};

struct T {
	int unrelated;
};

class Reflected {
public:
	unsigned char *PropertyAddress( int runtimeOffset );
	int first;
};

// A run-time offset added to `this` is the reflection system's arithmetic, not a finding.
unsigned char *Reflected::PropertyAddress( int runtimeOffset ) {
	return (unsigned char *)this + runtimeOffset;
}

// FAKEMATCH: the original calls a helper that this stand-in only imitates.
int marked_stand_in( Box<int> *box ) {
	return box->Num();
}
