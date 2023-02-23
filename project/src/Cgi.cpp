#include "../inc/Cgi.hpp"

char *stringdup(const char *str)
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
    int i = 0;
    
	if (!env)
        return ;
    while (env[i])
		i++;
    while (i != 0)
        free(env[i--]);
}

char **vecToArr(std::vector<std::string> vec)
{
    char **arr = NULL;
    int i = 0;

    if (!(arr = (char **)malloc(sizeof(char *) * (vec.size() + 1))))
        return (NULL);
    for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); it++) {
        if (!(arr[i] = stringdup(it->c_str())))
            return (NULL);
        i++;
    }
    arr[i] = NULL;
    return (arr);
}

std::string readFromFd(int fd)
{
    std::string ret;
    char buf[4097];
    int n;

    while ((n = read(fd, buf, 4096))) {
        if (n == -1)
            return ("");
        buf[n] = '\0';
        ret.insert(ret.length(), buf, n);
    }
    return (ret);
}

// ____________________________________________________________________________________________ //

Cgi::Cgi(std::string body, std::string tfile, std::map<std::string, std::string> &thead, Location tloc, std::string tname, std::string tmethod, std::string tversion, std::string tip, int tport) : file(tfile), head(thead), loc(tloc), _body(body)
{
	this->name = tname;
    this->ip = tip;
    this->port = tport;
	this->version = tversion;
	this->method = tmethod;
    this->env = NULL;
	return ;
}

Cgi::Cgi(Cgi const & src ) : file(src.file), head(src.head), loc(src.loc), name(src.name), ip(src.ip), port(src.port)
{
    //this->create_env();
}

Cgi::~Cgi()
{
    if (env) {
        free_env(env);
    }
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
	if (this->cgi_map.find(tmp.substr(it)) != this->cgi_map.end())
	{
		return (0);
	}
	return (1);
}

void Cgi::create_env(void)
{
	// https://helpx.adobe.com/coldfusion/cfml-reference/reserved-words-and-variables/cgi-environment-cgi-scope-variables/cgi-server-variables.html
    std::vector<std::string> temp;
	std::stringstream ss;
	ss << this->port;
	temp.push_back("SERVER_SOFTWARE=webserv/1.1");
	temp.push_back("SERVER_NAME=" + this->ip);
	temp.push_back("GATEWAY_INTERFACE=CGI/1.1");
	temp.push_back("SERVER_PROTOCOL=" + this->version);
	temp.push_back("SERVER_PORT=" + ss.str());
	temp.push_back("REQUEST_METHOD=" + this->method);
	temp.push_back("PATH_INFO=" + this->file);
	temp.push_back("PATH_TRANSLATED=" + this->file);
	temp.push_back("SCRIPT_NAME=" + this->loc.getCgiBin());
    temp.push_back("REQUEST_URI=" + this->file);
	temp.push_back("QUERY_STRING=");
    temp.push_back("REDIRECT_STATUS=0");
	temp.push_back("REMOTE_HOST=");
	temp.push_back("CONTENT_TYPE=" + this->cgi_map["/php"]);
	temp.push_back("CONTENT_LENGTH=NULL");

/*
    temp.push_back("REDIRECT_STATUS=CGI ");
    temp.push_back("SERVER_PROTOCOL=HTTP/1.1");
    temp.push_back("REQUEST_METHOD=GET ");
    temp.push_back("GATEWAY_INTERFACE=CGI/1.1");
    temp.push_back("SCRIPT_FILENAME=" + this->file + " ");
	temp.push_back("CONTENT_TYPE=" + this->cgi_map["/php"] + " ");
    temp.push_back("REDIRECT_STATUS=200");
    temp.push_back("CONTENT_LENGTH=4096 ");
*/
	this->env = vecToArr(temp);
	return ;
}

std::string  Cgi::launch_binary()
{
	this->create_env();
	std::string tmp = this->loc.getCgiBin();

	int pipe_in[2];
    int pipe_out[2];
	pipe(pipe_in);
    pipe(pipe_out);

    pid_t pid = 0;
	pid = fork();
	if (pid == 0)
	{
        char *argv[3];
        argv[0] = strdup(tmp.c_str());
        argv[1] = strdup(file.c_str());
        argv[2] = NULL;
		dup2(pipe_in[0], STDIN_FILENO);
		dup2(pipe_out[1], STDOUT_FILENO);

        close(pipe_in[0]);
        close(pipe_in[1]);
        close(pipe_out[0]);
        close(pipe_out[1]);

		if (execve(argv[0], argv, this->env) == -1)
		{
			perror("DEBUG ");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
        close(pipe_in[0]);
        close(pipe_out[1]);
		if (this->method== "GET")
            write(pipe_in[1], this->_body.c_str(), this->_body.length());
        close(pipe_in[1]);
        pipe_in[1] = -1;

		waitpid(pid, NULL, 0);
        std::string ret = readFromFd(pipe_out[0]);
        close(pipe_out[0]);
		if (this->method == "GET")
			return (ret);
		return (this->_body);
	}
	return ("");
}
