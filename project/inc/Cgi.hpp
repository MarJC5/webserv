//
//	Class Cgi crée le 26.01.2023 par tpaquier
//

#ifndef CGI_HPP
# define CGI_HPP

#include <map>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include "Server.hpp"
#include "HttpParser.hpp"
#include "webserv.hpp"
#include <vector>
#include <sstream>
class HttpParser;
class Server;

class Cgi
{
	public:
		Cgi(std::string body,std::string tfile, std::map<std::string, std::string> &thead, Location tloc, std::string tname, std::string tmethod, std::string tversion, std::string tip, int tport);
		Cgi(Cgi const & src);
		~Cgi(void);
		Cgi &operator=(Cgi &rhs);

		void set_maplist(void);
		int if_maplist_exist(void);
		void create_env(void);	
		std::string launch_binary(void);
	
	private:
		std::string file;
		std::map<std::string, std::string> head;
		std::map<std::string, std::string> cgi_map; // tous les MIME type avec comme keyword l'exécutable
		Location loc;
		std::string _body;

		std::string name;
        std::string ip;
		std::string version;
		std::string method;
        int         port;
		char **env;
};

#endif