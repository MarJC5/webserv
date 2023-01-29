#include "../inc/Cgi.hpp"

Cgi::Cgi(std::string tmp, std::map<std::string, std::string> tmpp, Location tmppp) : file(tmp), head(tmpp), loc(tmppp)
{
	return ;
}

Cgi::Cgi(Cgi const & src ) : file(src.file), head(src.head), loc(src.loc)
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
	std::cout << "IL ARRIVE ICI " << file << std::endl;
	int it = file.find_last_of(".");
	if (this->cgi_map.find(file.substr(it)) != this->cgi_map.end()) // renvoie erreur par rapport au extenstion dans le .conf et du fichier qu'on veux exec
	{
		this->head["Content-Type"] = this->cgi_map[file.substr(it)];
		return (0);
	}
	return (1);
}

void  Cgi::launch_binary()
{
	pid_t pid;
	char *argv[] = { NULL, NULL };

	int dupfile[2];

	pid = fork();
	dup2(dupfile[0], STDOUT_FILENO); // dup stdout et stdin
	dup2(dupfile[1], STDIN_FILENO);
	if (pid == -1)
		throw std::exception(); // temporaire
	else if (pid == 0)
	{
		close(dupfile[0]);
		close(dupfile[1]);
		if (execve(this->loc.getCgiBin().c_str(), argv, GLOBAL_ENVP) == -1)
		{
			throw std::exception(); // temporaire
		}
	}
	else
	{
		waitpid(pid, NULL, 0); // temporaire
	}
}
