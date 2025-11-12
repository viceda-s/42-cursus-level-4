//
// Created by viceda-s on 08/11/2025.
//

#include "Animal.hpp"

AAnimal::AAnimal() : type("") {
	std::cout << "Animal default constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal& other) : type(other.type) {
	std::cout << "Animal copy constructor called" << std::endl;
}

AAnimal& AAnimal::operator=(const AAnimal& other) {
	std::cout << "Animal assignment operator called" << std::endl;
	if (this != &other) {
		this->type = other.type;
	}
	return *this;
}

AAnimal::~AAnimal() {
	std::cout << "Animal destructor called" << std::endl;
}

void AAnimal::makeSound() const {
	std::cout << "* Generic animal sound *" << std::endl;
}

std::string AAnimal::getType() const {
	return this->type;
}