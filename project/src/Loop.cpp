#include "Loop.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Loop::Loop()
{
	return ;
}

Loop::Loop(std::vector<Server> &tmp)
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
		this->tab_socket = rhs.get_socket();
		this->tab_fd = rhs.get_fd_socket();
		this->r_octet = rhs.get_read_octet();
		this->r_buffer = rhs.get_read_buffer();
		this->w_octet = rhs.get_write_octet();
		this->w_buffer = rhs.get_write_buffer();
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Loop::createsocket(void)
{
	this->tab_socket.push_back(socket(AF_INET, SOCK_STREAM, 0));
	if (this->tab_socket.back() == -1)
		throw std::exception(); // temporaire
}

void Loop::setstruct(void)
{
	std::list<sockaddr_in>::iterator it = this->sockaddr_vect.begin();
	this->i = 0;
	if (this->i < this->sockaddr_vect.size())
	{
		this->sockaddr.sin_port = htons(this->serv[i].getPort());
		this->sockaddr.sin_family = AF_INET;
		int temp = atoi(this->serv[i].getIp().c_str());
		this->sockaddr.sin_addr.s_addr = htonl(temp); // INADDR_ANY pour automatiquement set avec l'ip de l'host
		this->sockaddr_vect.push_back(this->sockaddr);
		this->i++;
	}
}

void Loop::socksetopt(void)
{
	int temp = 1;
	if (setsockopt(this->tab_socket.back(), SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(temp) == -1))
		throw std::exception(); // temporaire
}

void Loop::socketbind(void)
{
	if (bind(this->tab_socket.back(), (struct sockaddr*)&this->sockaddr, sizeof(this->sockaddr)) == -1)
		throw std::exception(); // temporaire
}

void Loop::socketlisten(void)
{
	if (listen(this->tab_socket.back(), 5) == -1)
		throw std::exception(); // temporaire
}

void Loop::socketaccept(void)
{
	socklen_t len = sizeof(this->sockaddr);
	this->tab_fd.push_back(accept(this->tab_socket.back(), (struct sockaddr*)&this->sockaddr, &len));
	if (this->tab_fd.back() == -1)
		throw std::exception(); // temporaire
}

void Loop::readrequete(void)
{
	this->r_octet = recv(*this->it_fd, this->r_buffer, sizeof(this->r_buffer), 255);
	if (this->r_octet == -1)
		throw std::exception(); // temporaire
}

void Loop::sendrequete(void)
{
	this->w_octet = send(*this->it_fd, this->w_buffer, sizeof(this->w_buffer), 255);
	if (this->w_octet == -1)
		throw std::exception(); // temporaire
}

void Loop::closesocket(void)
{
	int i = 0;
	std::list<int>::iterator it = this->tab_socket.begin();
	std::list<int>::iterator itt = this->tab_fd.begin();
	while (i < this->tab_socket.size())
	{
		close(*it);
		close(*itt);
		it++;
		itt++;
		i++;
	}
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
		std::cout << "Une connexion a été établie avec \nPort : " << this->sockaddr.sin_port << "\nIP : " << this->sockaddr.sin_addr.s_addr << std::endl;
	}
	catch (std::exception &tmp)
	{
		std::cout << "erreur : loop initialisation\n";
		ret = 1;
	}
	int readsock = socket(AF_INET, SOCK_DGRAM, 0);
	bind(readsock, (struct sockaddr*)&this->sockaddr, sizeof(this->sockaddr));
	// plage fd
	while (ret != 1)
	{
		FD_SET(this->*it_fd, &this->setfd);
		FD_SET(readsock, &this->setfd);
		temp = select(*this->it_fd, &this->setfd, NULL, NULL, NULL);

		// lis message (requete)
		if (FD_ISSET(readsock, &this->setfd))
		{
			readrequete();
		}

		// envoie message (reponse)
		if (FD_ISSET(*this->it_fd, &this->setfd))
		{
			sendrequete(); // accept
		}
	}
	this->closesocket();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::list<int> Loop::get_socket(void)
{
	return (this->tab_socket);
}

struct sockaddr_in Loop::get_sockaddr(void)
{
	return (this->sockaddr);
}

std::list<int> Loop::get_fd_socket(void)
{
	return (this->tab_fd);
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