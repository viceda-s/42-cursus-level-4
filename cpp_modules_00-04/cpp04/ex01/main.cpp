//
// Created by viceda-s on 08/11/2025.
//

#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
	std::cout << "=== Creating array of Animals ===s" << std::endl;
	const int arraySize = 4;
	AAnimal* animals[arraySize];

	for (int i = 0; i < arraySize / 2; i++) {
		animals[i] = new Dog();
	}

	for (int i = arraySize / 2; i < arraySize; i++) {
		animals[i] = new Cat();
	}

	{
		std::cout << "\n=== Testing deep copy ===" << std::endl;
		Dog originalDog;
		originalDog.getBrain()->ideas[0] = "I want to chase cats";
		originalDog.getBrain()->ideas[1] = "I want to eat";

		std::cout << "\n--- Creating copy of Dog ---" << std::endl;
		Dog copyDog(originalDog);

		std::cout << "\n--- Modifying copy's brain ---" << std::endl;
		copyDog.getBrain()->ideas[0] = "I want to sleep";
		copyDog.getBrain()->ideas[1] = "I want to play";

		std::cout << "\n--- Verifying deep copy ---" << std::endl;
		std::cout << "Original Dog idea 0: " << originalDog.getBrain()->ideas[0] << std::endl;
		std::cout << "Original Dog idea 1: " << originalDog.getBrain()->ideas[1] << std::endl;
		std::cout << "Copy Dog idea 0: " << copyDog.getBrain()->ideas[0] << std::endl;
		std::cout << "Copy Dog idea 1: " << copyDog.getBrain()->ideas[1] << std::endl;

		std::cout << "\n--- Testing assignment operator ---" << std::endl;
		Cat originalCat;
		originalCat.getBrain()->ideas[0] = "I want to hunt mice";

		Cat assignedCat;
		assignedCat = originalCat;
		assignedCat.getBrain()->ideas[0] = "I want to nap";

		std::cout << "Original Cat idea: " << originalCat.getBrain()->ideas[0] << std::endl;
		std::cout << "Assigned Cat idea: " << assignedCat.getBrain()->ideas[0] << std::endl;
	}

	std::cout << "\n=== Deleting all animals ===" << std::endl;
	for (int i = 0; i < arraySize; i++) {
		delete animals[i];
	}

	std::cout << "\n=== End of program ===" << std::endl;
	return 0;
}
