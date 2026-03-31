#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

// Point class representing a 2D point with fixed-point coordinates
class Point
{
private:
	Fixed const x;		// X coordinate (constant)
	Fixed const y;		// Y coordinate (constant)

public:
	// Orthodox Canonical Form
	Point();								// Default constructor
	Point(const float x, const float y);	// Constructor with float parameters
	Point(Point const &copy);				// Copy constructor
	Point &operator=(Point const &copy);	// Copy assignment operator
	~Point();								// Destructor
	
	// Getter functions
	Fixed getX() const;						// Returns x coordinate
	Fixed getY() const;						// Returns y coordinate
};

// BSP function to check if a point is inside a triangle
bool bsp(Point const a, Point const b, Point const c, Point const point);

#endif