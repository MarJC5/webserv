#include "Loop.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Loop::Loop(std::vector<Server*> &tmp) : serv(tmp)
{
	FD_ZERO(&this->setfd);
	return ;
}

Loop::Loop(const Loop & src) : serv(src.serv)
{
	//*this = src;
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
	(void)rhs;
	/*if ( this != &rhs )
	{
		this->tab_socket = rhs.get_socket();
		this->tab_fd = rhs.get_fd_socket();
		this->r_octet = rhs.get_read_octet();
		this->r_buffer = rhs.get_read_buffer();
		this->w_octet = rhs.get_write_octet();
		this->w_buffer = rhs.get_write_buffer();
	}*/
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
	this->i = 0;
	if (this->i < this->sockaddr_vect.size())
	{
		this->sockaddr.sin_port = htons(this->serv[i]->getPort());
		this->sockaddr.sin_family = AF_INET;
		int temp = atoi(this->serv[i]->getIp().c_str());
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
	bzero(this->r_buffer, sizeof(this->r_buffer));
	this->r_octet = recv(*this->it_fd, this->r_buffer, sizeof(this->r_buffer), 255);
	if (this->r_octet == -1)
		throw std::exception(); // temporaire
	this->r_buffer[this->r_octet] = '\0';
}

void Loop::sendrequete(void)
{
	this->w_octet = send(*this->it_fd, this->w_buffer, sizeof(this->w_buffer), 255);
	if (this->w_octet == -1)
		throw std::exception(); // temporaire
	bzero(this->w_buffer, sizeof(this->r_buffer));
}

void Loop::closesocket(void)
{
	size_t i = 0;
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
	fd_set r;
	fd_set w;
	// fork ici
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

	while (ret != 1)
	{
		if (ret != 2)
		{
			FD_SET(this->tab_socket.back(), &this->setfd);

			temp = select(this->tab_socket.back() + 1, &r, &w, NULL, NULL);
			if (temp == -1)
				ret = 1;
		}

		// lis message (requete)
		if (FD_ISSET(this->tab_fd.back(), &this->setfd))
		{
			sendrequete();
			ret = 0;
		}

		// envoie message (reponse)
		if (FD_ISSET(this->tab_socket.back(), &this->setfd))
		{
			socketaccept();
			readrequete();
			FD_SET(this->tab_fd.back(), &this->setfd);
			ret = 2;
		}
	}
	this->closesocket();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const std::list<int> Loop::get_socket(void) const
{
	return (this->tab_socket);
}

const struct sockaddr_in Loop::get_sockaddr(void) const
{
	return (this->sockaddr);
}

const std::list<int> Loop::get_fd_socket(void) const
{
	return (this->tab_fd);
}

int Loop::get_read_octet(void)
{
	return (this->r_octet);

}

const char *Loop::get_read_buffer(void) const
{
	return (this->r_buffer);
}

int Loop::get_write_octet(void)
{
	return (this->w_octet);
}

const char *Loop::get_write_buffer(void) const
{
	return (this->w_buffer);
}

const std::vector<Server*> &Loop::get_ref_server(void) const
{
	return (this->serv);
}

/* *
************************************************************************* */