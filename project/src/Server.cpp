//
// Created by tywael on 12/9/22.
//
Server::Server(void): _routes() {}

Server::Server(const Server &copy)
{
    (*this) = copy;
}

Server::~Server(void) {}

Server &Server::operator=(Server const &right)
{
    if (&right != this)
    {
        _name = right._name;
        _ip = right._ip;
        _port = right._port;
        _routes = right._routes;
    }
    return (*this);
}

std::string const &Server::getName(void) const
{
    return (_name);
}

std::string const &Server::getIp(void) const
{
    return (_ip);
}

int const &getPort(void) const
{
    return (_port);
}

std::map<std::string, Route> const &getRoutes() const
{
    return (_routes);
}