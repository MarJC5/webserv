#include "Loop.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Loop::Loop(Server &tmp)
{
	this->serv = tmp;
	return ;
}

Loop::Loop( const Loop & src )
{
	return ;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Loop::~Loop()
{
	return ;
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Loop &Loop::operator=( Loop const & rhs )
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Loop::createsocket(void)
{
	this->fd_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->fd_socket == -1)
		std::cout << "Error: creation socket" << std::endl; // temporaire
	
	/*
	int len = sizeof(this->sockaddr);
	if (accept(this->fd_socket, (struct sockaddr*)&this->sockaddr, (socklen_t)&len) == -1)
		std::cout << "Error: creation socket" << std::endl; // temporaire
	*/
}

void Loop::setstruct(void)
{
	this->sockaddr.sin_port = htons(this->serv.getPort());
	this->sockaddr.sin_family = AF_INET;
	int temp = atoi(this->serv.getIp().c_str());
	this->sockaddr.sin_addr.s_addr = htonl(temp);
}

void Loop::socketbind(void)
{
	if (bind(this->fd_socket, (struct sockaddr*)&this->sockaddr, sizeof(this->sockaddr)) == -1)
		std::cout << "Error: creation socket" << std::endl; // temporaire
}

void Loop::socketlisten(void)
{
	if (listen(this->fd_socket, 5) == -1)
		std::cout << "Error: creation socket" << std::endl; // temporaire
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */