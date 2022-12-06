//
// Created by tywael on 12/3/22.
//

#ifndef WEBSERV_SERVER_HPP
# define WEBSERV_SERVER_HPP

#include "Route.hpp"

class Server:    public Properties
{
    public:
        Server(void);
        virtual ~Server(void);

        Server &operator=(Server const &right);

        //get
        std::string const &getName(void) const;
        std::string const &ip(void) const;
        int const &getPort(void) const;

    private:
        std::string _name;
        std::string _ip;
        int         _port;
        std::map<std::string, Route> _routes;
};

#endif //WEBSERV_SERVER_HPP
