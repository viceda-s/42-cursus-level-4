//
// Created by viceda=s on 08/11/2025.
//

#ifndef CPP04_DOG_HPP
#define CPP04_DOG_HPP

#include "AAnimal.hpp"

class Dog : public AAnimal {
public:
	Dog();
	Dog(const Dog& other);
	Dog& operator=(const Dog& other);
	~Dog();

	void makeSound() const;
};


#endif //CPP04_DOG_HPP