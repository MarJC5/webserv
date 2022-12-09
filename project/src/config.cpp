//
// Created by tywael on 12/9/22.
//

#include "Config.hpp"

Config::Config(void): _Server() {}

Config::Config(const config &copy)
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


const std::vector<Server> getServer(void) const
{
    return (_server);
}
