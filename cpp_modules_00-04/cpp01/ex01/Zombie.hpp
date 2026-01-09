#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <string>

#define RED		"\033[1;31m"
#define GREEN	"\033[1;32m"
#define YELLOW	"\033[1;33m"
#define RESET	"\033[0m"

class Zombie {
private:
	std::string name;

public:
	Zombie();
	~Zombie();

	void setName(std::string name);
	void announce( void );
};

Zombie* zombieHorde( int N, std::string name );

#endif
