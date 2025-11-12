//
// Created by viceda=s on 08/11/2025.
//

#ifndef CPP04_CAT_HPP
#define CPP04_CAT_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"

class Cat : public AAnimal {
private:
	Brain* brain;
public:
	Cat();
	Cat(const Cat& other);
	Cat& operator=(const Cat& other);
	~Cat();

	void makeSound() const;
	Brain *getBrain() const;
};

#endif //CPP04_CAT_HPP