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
#include "sys/types.h"
#include "signal.h"
#include <list>
#include <vector>
#include <netinet/in.h>

class Loop
{

	public:
		Loop(std::vector<Server*> &tmp);
		Loop( Loop const & src );
		~Loop();
		Loop &operator=(Loop &rhs);

		//Construit mes sockets avec les info de la class server
		void createsocket(void); // crée un socket
		void setstruct(void); // remplis ma struct avec les infos de la class Server via la reference de server dans cette class
		void socksetopt(void); // socksetopt mon socket
		void socketbind(void); // bind() mon socket nouvellement crée
		void socketlisten(void); // listen() mon socket nouvellement crée
		void socketaccept(void); // attend un appel du socket client

		//Lis la requête et envoie les info
		void readrequete(void); // lis ce que le socket du client envoie
		void sendrequete(void); // envoie des info au socket du client

		//close le socket
		void closesocket(void); // close le socket et sont fd

		// tous mes accesseurs
		const std::list<int> get_socket(void) const;
		const struct sockaddr_in get_sockaddr(void) const;
		const std::list<int> get_fd_socket(void) const;
		int get_read_octet(void);
		const char *get_read_buffer(void) const;
		int get_write_octet(void);
		const char *get_write_buffer(void) const;
		const std::vector<Server*> &get_ref_server(void) const;

		// loop
		void	loop(void);

	private:
		std::list<int> tab_socket; // pour stocker les multiples sockets
		std::list<int> tab_fd;	  // tab de fd de mes sockets, même indice
		std::list<int>::iterator it_fd;

		std::list<sockaddr_in> sockaddr_vect; // struct pour le socket qui contient plusieur info (ip, port, ...) à supprimer si pas utilisé à la fin
		struct sockaddr_in sockaddr;
		size_t i;

		fd_set setfd;

		int r_octet; // le nombre d'octet read
		char r_buffer[1024]; // le buffer pour le recv (read)
		int w_octet; // le nombre d'octer write
		char w_buffer[1024]; // le buffer pour send

		std::vector<Server*> &serv; // reference de Server pour pouvoir accéder à ces variables et initialisé ma struct
};

#endif