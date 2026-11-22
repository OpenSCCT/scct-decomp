// no-game-data: synthetic
typedef int Event;

class Actor {
public:
	void Tick( Event e );
};

// A pointer to member: the typedef is named EventHandler, and Event only appears in its parameter list.
typedef void (Actor::*EventHandler)( Event );
