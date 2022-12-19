#include "Loop.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Loop::Loop()
{
	return ;
}

Loop::Loop(Server &tmp)
{
	this->serv = tmp;
	return ;
}

Loop::Loop(const Loop & src)
{
	*this = src;
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
	this->_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socket == -1)
		std::cout << "Error: creation _socket" << std::endl; // temporaire
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
	if (bind(this->_socket, (struct sockaddr*)&this->sockaddr, sizeof(this->sockaddr)) == -1)
		std::cout << "Error: bind" << std::endl; // temporaire
}

void Loop::socketlisten(void)
{
	if (listen(this->_socket, 5) == -1)
		std::cout << "Error: listen" << std::endl; // temporaire
}

void Loop::socketaccept(void)
{
	socklen_t len = sizeof(this->sockaddr);
	this->fd_socket = accept(this->_socket, (struct sockaddr*)&this->sockaddr, &len);
	if (this->fd_socket == -1)
		std::cout << "Error: accept" << std::endl; // temporaire
}

void Loop::readrequete(void)
{
	this->r_octet = recv(this->fd_socket, this->r_buffer, sizeof(this->r_buffer), 0);
	if (this->r_octet == -1)
		std::cout << "Error: recv" << std::endl; // temporaire
}

void Loop::sendrequete(void)
{
	this->w_octet = send(this->fd_socket, this->w_buffer, sizeof(this->w_buffer), 0);
	if (this->w_octet == -1)
		std::cout << "Error: send" << std::endl; // temporaire
}

void Loop::closesocket(void)
{
	close(this->fd_socket);
	close(this->_socket);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */