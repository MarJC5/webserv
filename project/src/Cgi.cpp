#include "../inc/Cgi.hpp"

Cgi::Cgi(std::string tmp, std::map<std::string, std::string> &tmpp, Location tmppp, Server tmpppp) : file(tmp), head(tmpp), loc(tmppp), serv(tmpppp)
{
	return ;
}

Cgi::Cgi(Cgi const & src ) : file(src.file), head(src.head), loc(src.loc), serv(src.serv)
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
	int it = file.find_last_of(".");
	if (this->cgi_map.find(file.substr(it)) != this->cgi_map.end()) // renvoie erreur par rapport au extenstion dans le .conf et du fichier qu'on veux exec
	{
		this->head["Content-Type"] = this->cgi_map[file.substr(it)];
		return (0);
	}
	this->head["Content-Type"] = this->cgi_map[file.substr(it)];
	return (1);
}

void create_env(void)
{
	
	return ;
}

void  Cgi::launch_binary()
{
	std::cout << "IL ARRIVE ICI " << file << std::endl;
	pid_t pid = 0;
	std::string tmp = this->loc.getCgiBin();
	char *argv[2];
	argv[0] = strdup(tmp.c_str());
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		throw std::exception(); // temporaire
		return ;
	}
	else if (pid == 0)
	{
		std::cout << this->loc.getCgiBin().c_str();
		if (execve(argv[0], argv, NULL) == -1)
		{
			std::cout << "\nIL PLANTE ICI\n";
			throw std::exception(); // temporaire
			return ;
		}
		// read le buffer et send tout après
	}
	else
	{
		waitpid(pid, NULL, 0); // temporaire
	}
}
