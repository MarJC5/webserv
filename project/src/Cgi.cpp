#include "../inc/Cgi.hpp"

Cgi::Cgi(std::string tfile, std::map<std::string, std::string> &thead, Location tloc, std::string tname, std::string tip, int tport) : file(tfile), head(thead), loc(tloc)
{
	this->name = tname;
    this->ip = tip;
    this->port = tport;
	return ;
}

Cgi::Cgi(Cgi const & src ) : file(src.file), head(src.head), loc(src.loc), name(src.name), ip(src.ip), port(src.port)
{
}

Cgi::~Cgi()
{
}

Cgi &Cgi::operator=(Cgi &rhs)
{
	(void)rhs;
	return (*this);
}

void Cgi::set_maplist(void)
{
	this->cgi_map[".php"] = "application/x-httpd-php\n\n";
	//this->cgi_map["php"] = "application/x-httpd-php\n\n";
}

int Cgi::if_maplist_exist(void)
{
	std::cout << "FILE : " << file << std::endl;
	int it = this->file.find_last_of(".");
	if (this->cgi_map.find(this->file.substr(it)) != this->cgi_map.end()) // renvoie erreur par rapport au extenstion dans le .conf et du fichier qu'on veux exec
	{
		this->head["Content-Type"] = this->cgi_map[this->file.substr(it)];
		return (0);
	}
	this->head["Content-Type"] = this->cgi_map[this->file.substr(it)]; // pas là normalement
	return (1);

	// ---------------------------------------- //

	/*std::cout << "LOC : " << this->loc.getCgiBin() << std::endl;
	std::string tmp = this->loc.getCgiBin();
	int it = tmp.find_last_of("/");
	if (this->cgi_map.find(tmp.substr(it)) != this->cgi_map.end()) // renvoie erreur par rapport au extenstion dans le .conf et du fichier qu'on veux exec
	{
		this->head["Content-Type"] = this->cgi_map[tmp.substr(it)];
		return (0);
	}
	this->head["Content-Type"] = this->cgi_map[tmp.substr(it)];
	return (1);*/
}

void Cgi::create_env(void)
{
	// https://helpx.adobe.com/coldfusion/cfml-reference/reserved-words-and-variables/cgi-environment-cgi-scope-variables/cgi-server-variables.html
	// CONTENT_LENGTH = -1
	// CONTENT_TYPE = this->head["Content-Type"]
	// GATEWAY_INTERFACE = CGI/1.1
	// PATH_INFO = path to cgi script
	// PATH_TRANSLATED = X
	// QUERRY_STRING = tous ce qui suit le ?
	// REMOTE_ADDR = ip du client	
	// REQUEST_METHODE = GET / POST
	// SCRIPT_NAME = chemin du script
	// SERVER_NAME = IP du serveur
	// SERVER_PORT = Port du serveur
	// SERVER_PROTOCOL = HTTP/1.1
	// SERVER_SOFTWARE = ?
	this->cgi_envp = "SERVER_SOFTWARE=name/version"; // ?
	this->cgi_envp += "SERVER_NAME=";
	this->cgi_envp += this->ip;
	this->cgi_envp += "GATEWAY_INTERFACE=CGI/1.1";
	this->cgi_envp += "SERVER_PROTOCOL=HTTP/1.1";
	this->cgi_envp += "SERVER_PORT=";
	this->cgi_envp += this->port;
	this->cgi_envp += "REQUEST_METHOD="; // method
	this->cgi_envp += "PATH_INFO="; // ??
	this->cgi_envp += this->loc.getCgiBin();
	this->cgi_envp += "PATH_TRANSLATED="; // ???
	this->cgi_envp += "SCRIPT_NAME=php";
	this->cgi_envp += "QUERY_STRING=";
	this->cgi_envp += "REMOTE_ADDR=";
	this->cgi_envp += "CONTENT_TYPE=";
	this->cgi_envp += "CONTENT_LENGTH=";

	return ;
}

void  Cgi::launch_binary()
{
	std::string tmp = this->loc.getCgiBin();
	char *argv[2];
	argv[0] = strdup(tmp.c_str());
	argv[1] = NULL;

	/*int s[2];
	int s_out = 0;
	pipe(s);*/

	pid_t pid = 0;
	pid = fork();
	if (pid == 0)
	{
		/*close(s[1]);
		dup2(s[0], STDIN_FILENO);
		dup2(s_out, STDOUT_FILENO);*/

		std::cout << "IL ARRIVE ICI " << this->loc.getCgiBin() << " : " << this->head["Content-Type"];
		if (execve(argv[0], argv, NULL) == -1)
		{
			std::cout << "\nIL PLANTE ICI\n";
			exit(EXIT_FAILURE);
			return ;
		}
		exit(EXIT_SUCCESS);
		// read le buffer et send tout après
	}
	else
	{
		waitpid(pid, NULL, 0);
		std::cout << "IL ARRIVE ICI !!!!!!!!!!!!!\n";
		//close(s[0]);
	}
}
