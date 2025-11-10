#include <iostream>
#include "Fixed.hpp"
#include "Point.hpp"

int main( void ) {
	// Define a simple triangle
	Point a(0.0f, 0.0f);
	Point b(5.0f, 0.0f);
	Point c(2.5f, 5.0f);
	
	std::cout << "=== BSP (Binary Space Partitioning) Test ===" << std::endl;
	std::cout << "Triangle: A(0,0), B(5,0), C(2.5,5)" << std::endl;
	std::cout << std::endl;
	
	// Test case 1: Point inside triangle
	Point inside(2.5f, 1.0f);
	std::cout << "Point (2.5, 1.0) - Expected: INSIDE" << std::endl;
	std::cout << "Result: " << (bsp(a, b, c, inside) ? "INSIDE" : "OUTSIDE/ON EDGE") << std::endl;
	std::cout << std::endl;
	
	// Test case 2: Point outside triangle
	Point outside(10.0f, 10.0f);
	std::cout << "Point (10.0, 10.0) - Expected: OUTSIDE" << std::endl;
	std::cout << "Result: " << (bsp(a, b, c, outside) ? "INSIDE" : "OUTSIDE/ON EDGE") << std::endl;
	std::cout << std::endl;
	
	// Test case 3: Point on vertex
	std::cout << "Point on vertex A - Expected: ON VERTEX (OUTSIDE)" << std::endl;
	std::cout << "Result: " << (bsp(a, b, c, a) ? "INSIDE" : "OUTSIDE/ON EDGE") << std::endl;
	std::cout << std::endl;
	
	// Test case 4: Point on edge
	Point edge(2.5f, 0.0f);
	std::cout << "Point (2.5, 0.0) on edge - Expected: ON EDGE (OUTSIDE)" << std::endl;
	std::cout << "Result: " << (bsp(a, b, c, edge) ? "INSIDE" : "OUTSIDE/ON EDGE") << std::endl;
	
	return 0;
}