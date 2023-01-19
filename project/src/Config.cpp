//
// Created by tywael on 12/9/22.
//

#include "../inc/Config.hpp"

std::vector<std::string>::const_iterator getClosingBracket(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end) {
    size_t count = 0;
    std::vector<std::string>::const_iterator it = std::vector<std::string>::const_iterator(begin);

    for (; it != end; it++)
    {
        if (it->find("{") != std::string::npos)
            count++;
        if (it->find("}") != std::string::npos) {
            if(count != 1)
                count--;
            else
                return (it);
        }
    }
    return (it);
}

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

Config::~Config(void) {
    for (std::vector<Server*>::const_iterator it = _server.begin(); it < _server.end(); it++) {
        delete *it;
    }
    _server.clear();
    _server.shrink_to_fit();
}

void Config::parseConf(std::string fileName)
{
    int numServ = -1;

    _file.readFile(fileName);
    for (std::vector<std::string>::const_iterator it = _file.getLines().begin(); it < _file.getLines().end(); it++)
    {
        size_t  pos = 0;
        if ((pos = findKey(*it, "server")) != std::string::npos)
        {
            numServ++;
            _server.push_back(new Server());
            if (it->find("{", pos + std::string("server").size()) != std::string::npos)
            {
                _server[numServ]->parseServer(it, getClosingBracket(it, _file.getLines().end()));
            }
            else
            {
                while (it < _file.getLines().end() && it->find("{") == std::string::npos) {
                    it++;
                }
                    _server[numServ]->parseServer(it, getClosingBracket(it, _file.getLines().end()));
            }
        }
    }
}


const std::vector<Server*> &Config::getServer(void) const
{
    return (_server);
}