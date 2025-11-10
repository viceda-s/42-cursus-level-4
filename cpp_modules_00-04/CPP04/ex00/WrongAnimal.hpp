//
// Created by viceda-s on 08/11/2025.
//

#ifndef CPP04_WRONGANIMAL_HPP
#define CPP04_WRONGANIMAL_HPP


#include <string>
#include <iostream>

class WrongAnimal {
protected:
	std::string type;

public:
	WrongAnimal();
	WrongAnimal(const WrongAnimal& other);
	WrongAnimal& operator=(const WrongAnimal& other);
	~WrongAnimal();

	void makeSound() const;  // Note: NOT virtual
	std::string getType() const;
};


#endif //CPP04_WRONGANIMAL_HPP