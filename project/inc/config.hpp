//
// Created by tywael on 12/6/22.
//

#ifndef WEBSERV_CONFIG_HPP
#define WEBSERV_CONFIG_HPP

# define BUFFER_SIZE 1024

class Config
{
public:
    config(void);
    config(const Config &copy);
    virtual ~Config(void);

    void parseConf(stdd::string fileName);

    //get
    const std::vector<Server> getServer() const;


private:
    std::vector<Server> _server;

};

std::string readFile(std::string fileName);
std::string getLine(std::string file, int i);

#endif //WEBSERV_CONFIG_HPP
