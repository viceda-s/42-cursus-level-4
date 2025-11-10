//
// Created by viceda-s on 08/11/2025.
//

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
	std::cout << "=== Testing Animal, Dog, and Cat ===" << std::endl;
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << "\nType of j: " << j->getType() << std::endl;
	std::cout << "Type of i: " << i->getType() << std::endl;

	std::cout << "\nMaking sounds:" << std::endl;
	j->makeSound(); // Will output the dog sound!
	i->makeSound(); // Will output the cat sound!
	meta->makeSound(); // Will output the animal sound!

	std::cout << "\nDeleting animals:" << std::endl;
	delete j;
	delete i;
	delete meta;

	std::cout << "\n=== Testing WrongAnimal and WrongCat ===" << std::endl;
	const WrongAnimal* wrongMeta = new WrongAnimal();
	const WrongAnimal* wrongCat = new WrongCat();

	std::cout << "\nType of wrongCat: " << wrongCat->getType() << std::endl;

	std::cout << "\nMaking wrong sounds:" << std::endl;
	wrongCat->makeSound(); // Will output WrongAnimal sound (not polymorphic)!
	wrongMeta->makeSound();

	std::cout << "\nDeleting wrong animals:" << std::endl;
	delete wrongCat;
	delete wrongMeta;

	return 0;
}