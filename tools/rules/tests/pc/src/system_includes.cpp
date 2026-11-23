// no-game-data: synthetic
// A unit that compiles against its toolchain's own headers: its record carries system_headers,
// and the checker never reads an angle-bracket include, so the decoy src/vector is not loaded.
#include <vector>
#include <map>

struct Ledger {
	std::vector<int> entries;
	std::map<int, int> totals;
	int Count();
};

// Counts the entries.
int Ledger::Count() {
	return (int)entries.size();
}
