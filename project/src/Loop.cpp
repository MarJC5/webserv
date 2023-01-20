#include "../inc/Loop.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Loop::Loop(const std::vector<Server*> &tmp) : serv(tmp)
{
	this->timeout.tv_sec = 60;
	this->timeout.tv_usec = 0;
	FD_ZERO(&this->setfd);
	this->i = 0;
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
	bzero(&this->sockaddr, sizeof(this->sockaddr));
	if (this->i < this->serv.size())
	{
		std::string c = "\033[1;34m";
		std::string nc = "\033[0m";

		std::cout <<  std::endl;
		std::cout << c << "Server name: " << nc << this->serv[i]->getName() << std::endl;
		std::cout << c << "----------------------------------------------------------------" << nc << std::endl;
		std::cout << c << std::left << std::setw(18) << "Host" << nc << ": " << this->serv[i]->getIp().c_str() << ":" << this->serv[i]->getPort() << std::endl;
		std::cout << c << std::left << std::setw(18) << "inet_addr" << nc << ": " << inet_addr(this->serv[i]->getIp().c_str())  << std::endl;
		std::cout << c << "----------------------------------------------------------------" << nc << std::endl;
		this->sockaddr.sin_port = htons(this->serv[i]->getPort());
		this->sockaddr.sin_family = AF_INET;
		this->sockaddr.sin_addr.s_addr = inet_addr(this->serv[i]->getIp().c_str()); // INADDR_ANY pour automatiquement set avec l'ip de l'host
		this->sockaddr_vect.push_back(this->sockaddr);
		this->i++;
	}
}

void Loop::socksetopt(void)
{
	int temp = 1;
	if (setsockopt(this->tab_socket.back(), SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(temp)) == -1)
		throw std::exception(); // temporaire
}

void Loop::socketbind(void)
{
	if (bind(this->tab_socket.back(), (struct sockaddr*)&this->sockaddr, sizeof(this->sockaddr)) == -1)
		throw std::exception(); // temporaire
}

void Loop::socketlisten(void)
{
	if (listen(this->tab_socket.back(), 1024) == -1)
		throw std::exception(); // temporaire
}

void Loop::socketaccept(void)
{
	this->tab_fd = accept(this->fd_accept, NULL, NULL);
	if (this->tab_fd == -1)
		throw std::exception(); // temporaire
}

void Loop::readrequete(void)
{
	bzero(this->r_buffer, sizeof(this->r_buffer));
	this->r_octet = recv(this->tab_fd, this->r_buffer, sizeof(this->r_buffer), 0);
	if (this->r_octet == -1)
		throw std::exception(); // temporaire
	this->r_buffer[this->r_octet] = '\0';
}

void Loop::sendrequete(void)
{
	this->r_octet = sizeof(this->w_buffer);
	while (this->r_octet > 0) {
		int sent_data = send(this->tab_fd, this->w_buffer, this->r_octet, 0);
		if (sent_data < 0) {
			throw std::exception(); // handle error
		}
		this->r_octet -= sent_data;
	}
}

void Loop::closesocket(void)
{
	size_t i = 0;
	std::list<int>::iterator it = this->tab_socket.begin();
	while (i < this->tab_socket.size())
	{
		close(*it);
		it++;
		i++;
	}
	FD_ZERO(&this->setfd);
}

int Loop::getlist(int index)
{
	std::list<int>::iterator it = this->tab_socket.begin();
	int i = 0;
	while (i != index)
	{
		*it++;
		i++;
	}
	return (*it);
}

void	Loop::loop(void)
{
	HttpParser request;
	HttpParser response;

	std::string c = "\033[1;32m";
	std::string nc = "\033[0m";

	try
	{
		size_t i = 0;
		while (i < this->serv.size())
		{
			this->createsocket(); // stock ici dans 1 tableau pour la suite aussi et ensuite check avec select cette plage de fd crée
			this->setstruct();
			this->socksetopt();
			this->socketbind();
			this->socketlisten();
			i++;
			std::cout << c << std::endl;
			std::cout << "New connexion" << std::endl;
			std::cout << "----------------------------------------------------------------" << nc << std::endl;
			std::cout << c << std::left << std::setw(18) << "Port" << nc << ": " << ntohs(this->sockaddr.sin_port) << std::endl;
			std::cout << c << std::left << std::setw(18) << "IP" << nc << ": " << ntohl(this->sockaddr.sin_addr.s_addr) << std::endl;
			std::cout << c << "----------------------------------------------------------------" << nc << std::endl;
		}
	}
	catch (std::exception &tmp)
	{
		std::cout << "erreur : loop initialisation\n";
		return ;
	}
	i = 0;
	int it = 0;
	FD_ZERO(&this->setfd);
	while (i < this->tab_socket.size())
	{
		it = getlist(i);
		//std::cout << "fd_socket : " << i << std::endl;
		if (it > this->max_fd)
			this->max_fd = it;
		FD_SET(it, &this->setfd);
		i++;
	}
	int ret = 0;
	while (ret != 1)
	{
		std::memcpy(&this->temp_fd, &this->setfd, sizeof(this->setfd));
		this->temp = select(this->max_fd + 1, &this->temp_fd, NULL, NULL, NULL);
		if (this->temp == -1)
			ret = 1;
		// envoie message (request)
		i = 1;
		while (i < (size_t)this->max_fd)
		{
			this->fd_accept = getlist(i);
			if (FD_ISSET(this->fd_accept, &this->temp_fd))
			{
				socketaccept();
				readrequete();
				// print request
				request.setServ(*serv[fd_accept - this->tab_socket.front()]);
				try {
					request.parse(r_buffer);
					std::cout << request << std::endl;
				} catch (HttpException &e) {
					std::cout << e.what() << std::endl;
				}
				FD_SET(this->tab_fd, &this->temp_fd);
				break ;
			}
			i++;
		}
		// lis message (reponse)
		if (FD_ISSET(this->tab_fd, &this->temp_fd))
		{
			try {
				response = request;
				response.buildResponse();
				std::memset(w_buffer, 0, sizeof(w_buffer));
				std::memcpy(w_buffer, response.getBody().c_str(), response.getBody().size());
			} catch (HttpException &e) {
				std::cout << e.what() << std::endl;
			}
			sendrequete();
			this->fd_accept = 0;
			close(this->fd_accept);
			close(this->tab_fd);
			FD_CLR(this->tab_fd, &this->temp_fd);
			FD_ZERO(&this->temp_fd);
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

int Loop::get_fd_socket(void) const
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