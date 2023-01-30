//
//	Class Cgi crée le 26.01.2023 par tpaquier
//

#ifndef CGI_HPP
# define CGI_HPP

#include <map>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Server.hpp"
#include "HttpParser.hpp"
#include "webserv.hpp"
class HttpParser;
class Server;

class Cgi
{
	public:
		Cgi(std::string tmp, std::map<std::string, std::string> &tmpp, Location tmppp, Server tmpppp);
		Cgi(Cgi const & src);
		~Cgi(void);
		Cgi &operator=(Cgi &rhs);

		void set_maplist(void);
		int if_maplist_exist(void);
		void launch_binary(void);
		void create_env(void);
		
	private:
		std::string file;
		std::map<std::string, std::string> head;
		std::map<std::string, std::string> cgi_map; // tous les MIME type avec comme keyword l'exécutable
		Location loc;
		Server serv;
};

#endif