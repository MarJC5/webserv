//
//	Class Cgi crée le 26.01.2023 par tpaquier
//

#ifndef CGI_HPP
# define CGI_HPP

#include <map>
#include <iostream>
#include <string>
#include <unistd.h>
#include "HttpParser.hpp"
class HttpParser;

class Cgi
{

	public:
		Cgi(std::string tmp, std::map<std::string, std::string> tmpp);
		Cgi(Cgi const & src);
		~Cgi(void);
		Cgi &operator=(Cgi &rhs);

		void set_maplist(void);
		int if_maplist_exist(void);
		void  launch_binary(void);
		
	private:
		std::string file;
		std::map<std::string, std::string> &head;
		HttpParser &response; // contient toutes les infos pour faire run mon cgi
		std::map<std::string, std::string> cgi_map; // tous les MIME type avec comme keyword l'exécutable

};

#endif