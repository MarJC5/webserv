#ifndef ZOMBIE_H
# define ZOMBIE_H

#include <iostream>

class   Zombie
{
	public :
		Zombie(std::string temp);
		Zombie(void);
		~Zombie(void);
		void    announce(void);
		void    setname(std::string tname);

	private :
		std::string name;

};

#endif