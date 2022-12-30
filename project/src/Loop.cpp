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
	this->closesocket();
	return ;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Loop &Loop::operator=(Loop &rhs)
{
	if ( this != &rhs )
	{
		this->_socket = rhs.get_socket();
		this->sockaddr = rhs.get_sockaddr();
		this->fd_socket = rhs.get_fd_socket();
		this->r_octet = rhs.get_read_octet();
		this->r_buffer = rhs.get_read_buffer();
		this->w_octet = rhs.get_write_octet();
		this->w_buffer = rhs.get_write_buffer();
		this->serv = rhs.get_ref_server();
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Loop::createsocket(void)
{
	this->_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socket == -1)
		throw std::exception(); // temporaire
}

void Loop::setstruct(void)
{
	this->sockaddr.sin_port = htons(this->serv.getPort());
	this->sockaddr.sin_family = AF_INET;
	int temp = atoi(this->serv.getIp().c_str());
	this->sockaddr.sin_addr.s_addr = htonl(temp);
}

void Loop::socksetopt(void)
{
	int temp = 1;
	if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(temp) == -1))
		throw std::exception(); // temporaire
}

void Loop::socketbind(void)
{
	if (bind(this->_socket, (struct sockaddr*)&this->sockaddr, sizeof(this->sockaddr)) == -1)
		throw std::exception(); // temporaire
}

void Loop::socketlisten(void)
{
	if (listen(this->_socket, 5) == -1)
		throw std::exception(); // temporaire
}

void Loop::socketaccept(void)
{
	this->it = this->tab_socket.end();
	socklen_t len = sizeof(this->sockaddr);
	*this->it = accept(this->_socket, (struct sockaddr*)&this->sockaddr, &len);
	if (*this->it == -1)
		throw std::exception(); // temporaire
}

void Loop::readrequete(void)
{
	this->r_octet = recv(*this->it, this->r_buffer, sizeof(this->r_buffer), 255);
	if (this->r_octet == -1)
		throw std::exception(); // temporaire
}

void Loop::sendrequete(void)
{
	this->w_octet = send(*this->it, this->w_buffer, sizeof(this->w_buffer), 255);
	if (this->w_octet == -1)
		throw std::exception(); // temporaire
}

void Loop::closesocket(void)
{
	close(this->fd_socket);
	close(this->_socket);
}

void	Loop::loop(void)
{
	int ret = 0;
	int temp = 0;
	try
	{
		this->createsocket(); // stock ici dans 1 vtableau pour la suite aussi et ensuite check avec select cette plage de fd crée
 		this->setstruct();
		this->socksetopt();
		this->socketbind();
		this->socketlisten();
	}
	catch (std::exception &tmp)
	{
		std::cout << "erreur : loop initialisation\n";
		ret = 1;
	}
	int readsock = socket(AF_INET, SOCK_DGRAM, 0);
	bind(readsock, (struct sockaddr*)&this->sockaddr, sizeof(this->sockaddr));
	while (ret != 1)
	{
		FD_SET(this->_socket, &this->setfd);
		FD_SET(readsock, &this->setfd);
		temp = select(this->_socket, &this->setfd, NULL, NULL, NULL);

		// lis message (requete)
		if (FD_ISSET(readsock, &this->setfd))
		{

		}

		// envoie message (reponse)
		if (FD_ISSET(this->_socket, &this->setfd))
		{

		}
	}
	this->closesocket();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int Loop::get_socket(void)
{
	return (this->_socket);
}

struct sockaddr_in Loop::get_sockaddr(void)
{
	return (this->sockaddr);
}

int Loop::get_fd_socket(void)
{
	return (this->fd_socket);
}

int Loop::get_read_octet(void)
{
	return (this->r_octet);

}

char *Loop::get_read_buffer(void)
{
	return (this->r_buffer);
}

int Loop::get_write_octet(void)
{
	return (this->w_octet);
}

char *Loop::get_write_buffer(void)
{
	return (this->w_buffer);
}

Server &Loop::get_ref_server(void)
{
	return (this->serv);
}

/* *
************************************************************************* */