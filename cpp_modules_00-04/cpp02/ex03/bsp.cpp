#include "Point.hpp"

// Helper function to calculate the cross product of two vectors
// Returns the z-component of the cross product (since we're in 2D)
static Fixed crossProduct(Point const &p1, Point const &p2, Point const &p3) {
	// Vector from p1 to p2: (p2.x - p1.x, p2.y - p1.y)
	// Vector from p1 to p3: (p3.x - p1.x, p3.y - p1.y)
	// Cross product z-component: (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x)
	return (p2.getX() - p1.getX()) * (p3.getY() - p1.getY()) - (p2.getY() - p1.getY()) * (p3.getX() - p1.getX());
}

// Helper function to check if a value is zero (for edge detection)
static bool isZero(Fixed const &value) {
	return value == Fixed(0);
}

// BSP function - Binary Space Partitioning
// Returns true if point is strictly inside the triangle (not on edges or vertices)
bool bsp(Point const a, Point const b, Point const c, Point const point) {
	// Calculate cross products for each edge of the triangle
	Fixed cross1 = crossProduct(a, b, point);
	Fixed cross2 = crossProduct(b, c, point);
	Fixed cross3 = crossProduct(c, a, point);
	
	// If any cross product is zero, the point is on an edge or vertex
	if (isZero(cross1) || isZero(cross2) || isZero(cross3)) {
		return false;
	}
	
	// Check if all cross products have the same sign
	// If they do, the point is inside the triangle
	bool sameSign = (cross1 > Fixed(0) && cross2 > Fixed(0) && cross3 > Fixed(0)) ||
					(cross1 < Fixed(0) && cross2 < Fixed(0) && cross3 < Fixed(0));
	
	return sameSign;
}