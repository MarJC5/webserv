//
//	Class Loop crée le 16.12.2022 par tpaquier
//

#ifndef LOOP_HPP
# define LOOP_HPP

#include "Server.hpp"
#include <iostream>
#include <string>
#include "sys/socket.h"
#include <netinet/in.h>
#include "sys/types.h"

class Loop
{

	public:
		Loop(Server &tmp);
		Loop( Loop const & src );
		~Loop();
		Loop &operator=(Loop const & rhs);

		//Construit mes sockets avec les info de la class server
		void createsocket(void); // crée un socket
		void setstruct(void); // remplis ma struct avec les infos de la class Server via la reference de server dans cette class
		void socketbind(void); // bind() mon socket nouvellement crée
		void socketlisten(void); // listen() mon socket nouvellement crée

	private:
		int fd_socket; // le socket crée par socket
		struct sockaddr_in sockaddr; // struct pour le socket qui contient plusieur info (ip, port, ...)
		Server &serv; // reference de Server pour pouvoir accéder à ces variable
};

#endif