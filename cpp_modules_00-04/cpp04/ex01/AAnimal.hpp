	//
// Created by viceda-s on 08/11/2025.
//

#ifndef CPP04_ANIMAL_HPP
#define CPP04_ANIMAL_HPP


#include <string>
#include <iostream>

class AAnimal {
protected:
	std::string type;

public:
	AAnimal();
	AAnimal(const AAnimal& other);
	AAnimal& operator=(const AAnimal& other);
	virtual ~AAnimal();

	virtual void makeSound() const;
	std::string getType() const;
};


#endif //CPP04_ANIMAL_HPP