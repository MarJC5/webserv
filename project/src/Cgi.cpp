#include "../inc/Cgi.hpp"

Cgi::Cgi(std::string tmp, std::map<std::string, std::string> tmpp) : file(tmp), head(tmpp)
{
	return ;
}

Cgi::Cgi(Cgi const & src ) : response(src.response)
{
	return ;
}

Cgi::~Cgi()
{
	return ;
}

Cgi &Cgi::operator=(Cgi &rhs)
{
	(void)rhs;
	return (*this);
}

void Cgi::set_maplist(void)
{
	this->cgi_map[".php"] = "application/x-httpd-php";
}

int Cgi::if_maplist_exist(void)
{
	std::string tmp = this->response.getFile();
	int it = tmp.find_last_of(".");
	if (this->cgi_map.find(tmp.substr(it)) != this->cgi_map.end()) // renvoie erreur par rapport au extenstion dans le .conf et du fichier qu'on veux exec
	{
		this->content_type = this->cgi_map[tmp.substr(it)];
		return (0);
	}
	return (1);
}

void  Cgi::launch_binary()
{
	const std::map<std::string, Location*> tmp = serv.getLocations();
	std::cout << "Location : " << tmp.find("")->second->getCgiBin() << std::endl;
	/*pid_t pid;

	pid = fork();
	if (pid == -1)
		throw std::exception(); // temporaire
	else if (pid == 0)
	{
		//execve(, NULL, envp);
	}
	else
		waitpid(pid, NULL, NULL);*/
}
