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

void Config::parseConf(std::string fileName)
{
    std::string content;

    content = readFile(fileName);

}

const std::vector<Server> Config::getServer(void) const
{
    return (_server);
}

std::string readFile(std::string fileName)
{
    char buffer[BUFFER_SIZE + 1] = {0};
    int fd;
    int rdRet
    std::string ret;

    fd = open(file.c_str(), O_RDONLY);
    if (fd < 0)
    {
        //TO DO ERROR THROW FILE CORRUPTED...
    }
    while ((rdRet = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        ret += buffer;
        int i = 0;
        while (i < BUFFER_SIZE)
            buffer[i++] = 0;
    }
    close(fd);
    return (ret)
}

std::string getLine(std::string file, int i)
{

}
