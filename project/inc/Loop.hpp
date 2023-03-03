//
//	Class Loop crée le 16.12.2022 par tpaquier
//

#ifndef LOOP_HPP
# define LOOP_HPP

#include "Config.hpp"
#include "Server.hpp"
#include <iostream>
#include <string>
#include "unistd.h"
#include "string.h"
#include "sys/socket.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include "stdlib.h"
#include "stdio.h"
#include <netdb.h>
#include "sys/types.h"
#include "signal.h"
#include <list>
#include <vector>
#include <netinet/in.h>
#include <sys/select.h>
#include "HttpParser.hpp"
#include "Cgi.hpp"

class Loop
{

	public:
		Loop(const std::vector<Server*> &tmp);
		Loop(const Loop &src);
		~Loop();
		Loop &operator=(const Loop &rhs);
		int getlist(int index);

		//Construit mes sockets avec les info de la class server
		void createsocket(void);
		void setstruct(void);
		void socksetopt(void);
		void socketbind(void);
		void socketlisten(void);
		void socketaccept(void);

		//Lis la requête et envoie les info
		void readrequete(void);
		void sendrequete(void);

		//close le socket
		void closesocket(void);

		// tous mes accesseurs
		const std::list<int> get_socket(void) const;
		const struct sockaddr_in get_sockaddr(void) const;
		int get_fd_socket(void) const;
		int get_read_octet(void);
		const char *get_read_buffer(void) const;
		int get_write_octet(void);
		const char *get_write_buffer(void) const;
		const std::vector<Server*> &get_ref_server(void) const;

		// loop
		void	loop();

	private:
		std::list<int> tab_socket; // pour stocker les multiples sockets
		int tab_fd;	  // tab de fd de mes sockets, même indice
		std::list<int>::iterator it_socket;

		std::list<sockaddr_in> sockaddr_vect; // struct pour le socket qui contient plusieur info (ip, port, ...) à supprimer si pas utilisé à la fin
		struct sockaddr_in sockaddr;
		size_t i;

		fd_set setfd;
		int	   fd_accept;
		struct timeval timeout;
		fd_set temp_fd;
		int max_fd;
		int temp;

		int r_octet; // le nombre d'octet read
		char *r_buffer; // le buffer pour le recv (read)
		int w_octet; // le nombre d'octer write
		char *w_buffer; // le buffer pour send

		const std::vector<Server*> &serv; // reference de Server pour pouvoir accéder à ces variables et initialisé ma struct
};

#endif