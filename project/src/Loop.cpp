#include "../inc/Loop.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Loop::Loop(const std::vector<Server*> &tmp) : serv(tmp)
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
	
	/*
	struct addrinfo temp;
	struct addrinfo *rep;

	temp.ai_family = AF_UNSPEC;
    temp.ai_socktype = SOCK_DGRAM;
    temp.ai_flags = AI_PASSIVE;
    temp.ai_protocol = 0;
    temp.ai_canonname = NULL;
    temp.ai_addr = NULL;
    temp.ai_next = NULL;

	int ret = getaddrinfo(NULL, "8080", &temp, &rep);
	if (ret != 0)
		std::cout << "Erreur de getaddrinfo" << std::endl;
	*/

	if (this->i < this->serv.size())
	{
		std::cout << this->serv[i]->getPort() << " " << this->serv[i]->getIp().c_str() << std::endl;
		this->sockaddr.sin_port = htons(this->serv[i]->getPort());
		this->sockaddr.sin_family = AF_INET;
		//int temp = atoi(this->serv[i]->getIp().c_str());
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
	struct sockaddr_in client;
	socklen_t temp = sizeof(client);
	this->tab_fd.push_back(accept(this->tab_socket.back(), (struct sockaddr*)&client, &temp));
	if (this->tab_fd.back() == -1)
		throw std::exception(); // temporaire
}

void Loop::readrequete(void)
{
	bzero(this->r_buffer, sizeof(this->r_buffer));
	this->r_octet = recv(this->tab_fd.back(), this->r_buffer, sizeof(this->r_buffer), 0);
	if (this->r_octet == -1)
		throw std::exception(); // temporaire
	this->r_buffer[this->r_octet] = '\0';
}

void Loop::sendrequete(void)
{
	this->r_octet = send(this->tab_fd.back(), this->w_buffer, sizeof(this->w_buffer), 0);
	if (this->r_octet == -1)
		throw std::exception(); // temporaire
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
	HttpParser request = HttpParser(*(serv[0]));
	HttpParser response = HttpParser(*(serv[0]));
	
	int ret = 0;
	int temp = 0;
	fd_set r;
	fd_set w;
	try
	{
		std::cout << "--- loop ---\n";
		std::cout << this->tab_socket.back() << std::endl;
		this->createsocket(); // stock ici dans 1 vtableau pour la suite aussi et ensuite check avec select cette plage de fd crée
 		std::cout << this->tab_socket.back() << std::endl;
		this->setstruct();
		this->socksetopt();
		this->socketbind();
		this->socketlisten();
		std::cout << "Une connexion a été établie avec \nPort : " << ntohs(this->sockaddr.sin_port) << "\nIP : " << ntohl(this->sockaddr.sin_addr.s_addr) << std::endl;
	}
	catch (std::exception &tmp)
	{
		std::cout << "erreur : loop initialisation\n";
		ret = 1;
	}
	FD_ZERO(&this->setfd);
	FD_SET(this->tab_socket.back(), &this->setfd);

	while (ret != 1)
	{
		r = this->setfd;
		w = this->setfd;
		temp = select(this->tab_socket.back() + 1, &r, &w, NULL, NULL);
		if (temp == -1)
			ret = 1;

		// envoie message (request)
		if (FD_ISSET(this->tab_socket.back(), &this->setfd))
		{
			socketaccept();
			readrequete();
			// print request
			try {
				request.parse(r_buffer);
				std::cout << request << std::endl;
			} catch (HttpException &e) {
				std::cout << e.what() << std::endl;
			}
			FD_SET(this->tab_fd.back(), &this->setfd);
		}

		// lis message (reponse)
		if (FD_ISSET(this->tab_fd.back(), &this->setfd))
		{
			// print response
			try {
				response = request;
				response.buildResponse(serv, request);
				std::memset(w_buffer, 0, sizeof(w_buffer));
				std::memcpy(w_buffer, response.getBody().c_str(), response.getBody().size());
			} catch (HttpException &e) {
				std::cout << e.what() << std::endl;
			}
			sendrequete();
			close(this->tab_fd.back());
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