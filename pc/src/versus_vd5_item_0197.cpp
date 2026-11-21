/* Work item 0197: Versus RVA 0xe4750-0xe4b13. */
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef float FLOAT;
typedef double DOUBLE;

/* 0xe4750: returns B when A < B, else A when A < C, else C. Neutral name. */
DOUBLE PickBound_e4750(DOUBLE A, DOUBLE B, DOUBLE C)
{
	if (A < B)
		return B;
	if (A < C)
		return A;
	return C;
}
