//
// Created by tywael on 12/6/22.
//

#ifndef WEBSERV_CONFIG_HPP
#define WEBSERV_CONFIG_HPP

#include "ConfFile.hpp"
#include "Server.hpp"

# define BUFFER_SIZE 1024

class Config
{
public:
    Config(void);
    Config(const Config &copy);
    virtual ~Config(void);

    Config &operator=(const Config &right);

    void parseConf(std::string fileName);

    //get
    const std::vector<Server> getServer() const;


private:
    std::vector<Server> _server;
    ConfFile _file;
};

std::string readFile(std::string fileName);
std::string getLine(std::string file, int i);

#endif //WEBSERV_CONFIG_HPP
