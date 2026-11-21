// no-game-data: synthetic
class Shape {
public:
	virtual ~Shape();
	virtual void pad1();
	virtual float Area();
	int sides;
};

// Destroys the shape.
Shape::~Shape() {
	sides = 0;
}
