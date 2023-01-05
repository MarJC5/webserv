//
// Created by tywael on 12/9/22.
//

#include "../inc/Server.hpp"
#include <iostream>
#include <cctype>

size_t nspace(std::string str) {
    size_t ret = 0;

    for (ret = 0; ret < str.size() || std::isspace(str[ret]); ++ret) {}
    return (ret);
}

Server::Server(void): Properties(), _name("localhost"), _ip("127.0.0.1"), _port(80), _locations() {}

Server::Server(const Server &copy): Properties(copy)
{
    (*this) = copy;

}

Server::~Server(void) {
    for (std::map<std::string, Location*>::const_iterator it = _locations.begin(); it != _locations.end() ; it++) {
        delete it->second;
    }
    _locations.clear();
}

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

std::map<std::string, Location*> const &Server::getLocations() const
{
    return (_locations);
}

void Server::parseServer(std::vector<std::string>::const_iterator &it, std::vector<std::string>::const_iterator end) {

    for (; it < end; ++it) {
        if (parseName(*it))
            continue;
        if (parseIp(*it))
            continue;
        if (parsePort(*it))
            continue;
        if (parseLocations(it, end))
            continue;
    }
}

bool Server::parseLocations(std::vector<std::string>::const_iterator &it, std::vector<std::string>::const_iterator end) {
    size_t pos;
    int numLoc = -1;
    std::string key;

    if ((pos = it->find("location")) != std::string::npos) {
        for (; it != end; it++) {
            numLoc++;
            _locations[key = getVal(*it, "location", pos)] = new Location();
            pos += std::string("location").size();
            if (it->find("{", pos) != std::string::npos) {
                _locations[key]->parseLocation(it, getClosingBracket(it, end));
            } else {
                while (it != end && it->find("{") == std::string::npos)
                    it++;
                _locations[key]->parseLocation(it, getClosingBracket(it, end));
                it--;
            }
            return (true);
        }
    }
    return (false);
}

bool Server::parseName(std::string line) {
    size_t pos;

    if ((pos = line.find("name ")) != std::string::npos) {
        _name = getVal(line, "name", pos);
        return (true);
    }
    return (false);
}

bool Server::parseIp(std::string line) {
    size_t pos;

    if ((pos = line.find("ip ")) != std::string::npos) {
        _ip = getVal(line, "ip", pos);
        return (true);
    }
    return (false);
}

bool Server::parsePort(std::string line) {
    size_t pos;

    if ((pos = line.find("port ")) != std::string::npos) {
        _port = stoi(getVal(line, "port", pos));
        return (true);
    }
    return (false);
}
