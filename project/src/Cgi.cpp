#include "../inc/Cgi.hpp"

char *strdup(const char *str)
{
    int        size_src;
    int        c;
    char    *ret;

    size_src = strlen(str);
    ret = (char *)malloc(sizeof(char) * (size_src + 1));
    if (ret == NULL)
        return (NULL);
    c = 0;
    while (str[c])
    {
        ret[c] = str[c];
        c++;
    }
    ret[c] = '\0';
    return (ret);
}

void    free_env(char **env)
{
    int i;
    
	if (!ptr)
        return ;
    while (env[i])
		i++;
    while (i != 0)
        free(env[i--]);
    free(env);
}

char **vecToArr(std::vector<std::string> vec)
{
    char **arr = NULL;
    int i = 0;

    if (!(arr = (char **)malloc(sizeof(char *) * (vec.size() + 1))))
        return (NULL);
    for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); it++) {
        if (!(arr[i] = strdup(it->c_str())))
            return (NULL);
        i++;
    }
    arr[i] = NULL;
    return (arr);
}

// ____________________________________________________________________________________________ //

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
	free_env(env);
}

Cgi &Cgi::operator=(Cgi &rhs)
{
	(void)rhs;
	return (*this);
}

void Cgi::set_maplist(void)
{
	this->cgi_map["/php"] = "application/x-httpd-php\r\n";
}

int Cgi::if_maplist_exist(void)
{
	if (this->loc.getCgiBin().size() == 0)
		return (1);
	std::string tmp = this->loc.getCgiBin();
	int it = tmp.find_last_of("/");
		std::cout << "LOC : " << this->loc.getCgiBin() << " " << tmp.substr(it) << std::endl;
	if (this->cgi_map.find(tmp.substr(it)) != this->cgi_map.end()) // renvoie erreur par rapport au extenstion dans le .conf et du fichier qu'on veux exec
	{
		this->head["Content-Type"] = this->cgi_map[tmp.substr(it)];
		return (0);
	}
	return (1);	
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
	std::vector<std::string> temp;
	std::stringstream ss;
	ss << this->port;
	temp.push_back("SERVER_SOFTWARE=webserv/1.1");
	temp.push_back("SERVER_NAME=" + this->ip);
	temp.push_back("GATEWAY_INTERFACE=CGI/1.1");
	temp.push_back("SERVER_PROTOCOL=HTTP/1.1");
	temp.push_back("SERVER_PORT=" + ss.str());
	temp.push_back("REQUEST_METHOD=GET");
	temp.push_back("PATH_INFO=" + this->loc.getCgiBin());
	temp.push_back("PATH_TRANSLATED=" + this->loc.getCgiBin());
	temp.push_back("SCRIPT_NAME=php");
	temp.push_back("QUERY_STRING=");
	temp.push_back("REMOTE_HOST=");
	temp.push_back("CONTENT_TYPE=" + this->cgi_map["/php"]);
	temp.push_back("CONTENT_LENGTH=");

	this->env = vecToArr(temp);

	int i = 0;
	while(i < 13)
	{
		std::cout << this->env[i] << std::endl;
		i++;
	}
	return ;
}

void  Cgi::launch_binary()
{
	this->create_env();
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

		std::cout << this->head["Content-Type"];
		if (execve(argv[0], argv, this->env) == -1)
		{
			perror("DEBUG ");
			exit(EXIT_FAILURE);
			return ;
		}
		exit(EXIT_SUCCESS);
		// read le buffer et send tout après
	}
	else
	{
		waitpid(pid, NULL, 0);
		//close(s[0]);
	}
}
