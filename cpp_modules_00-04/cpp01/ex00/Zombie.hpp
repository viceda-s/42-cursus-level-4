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
	Zombie(std::string name);
	~Zombie();

	void announce( void );
};

Zombie* newZombie( std::string name );
void randomChump ( std::string name );

#endif
