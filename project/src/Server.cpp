//
// Created by tywael on 12/9/22.
//

#include "../inc/Server.hpp"

Server::Server(void): Properties(), _name("localhost"), _ip("127.0.0.1"), _port(80), _locations() {}

Server::Server(const Server &copy): Properties(copy)
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
        _locations = right._locations;
        _root = right._root;
        _index = right._index;
        _max_body_size = right._max_body_size;
        _allowed_method = right._allowed_method;
        _cgi_bin = right._cgi_bin;
        _directory_listing = right._directory_listing;
        _cgi_extensions = right._cgi_extensions;
        _upload_dir = right._upload_dir;
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

int const &Server::getPort(void) const
{
    return (_port);
}

std::map<std::string, Location> const &Server::getLocations() const
{
    return (_locations);
}