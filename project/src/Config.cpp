//
// Created by tywael on 12/9/22.
//

#include "../inc/Config.hpp"

Config::Config(void): _server() {}

Config::Config(const Config &copy)
{
    (*this) = copy;
}

Config &Config::operator=(const Config &right)
{
    if (&right != this)
        _server = right._server;
    return (*this);
}

Config::~Config(void) {}

void Config::parseConf(std::string fileName)
{
    _file.readFile(fileName);
    for (std::vector<std::string>::const_iterator it = _file.getLines().cbegin(); it != _file.getLines().cend(); it++)
    {
        std::cout << *it << std::endl;
    }
}

const std::vector<Server> Config::getServer(void) const
{
    return (_server);
}
