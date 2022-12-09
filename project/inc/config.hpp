//
// Created by tywael on 12/6/22.
//

#ifndef WEBSERV_CONFIG_HPP
#define WEBSERV_CONFIG_HPP

class Config
{
public:
    config(void);
    config(const Config &copy);
    virtual ~Config(void);

    //get
    const std::vector<Server> getServer() const;


private:
    std::vector<Server> _server;

};

#endif //WEBSERV_CONFIG_HPP
