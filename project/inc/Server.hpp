//
// Created by tywael on 12/3/22.
//

#ifndef WEBSERV_SERVER_HPP
# define WEBSERV_SERVER_HPP

#include "Location.hpp"
#include "Properties.hpp"
#include "parse.h"
#include <map>

std::vector<std::string>::const_iterator getClosingBracket(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end);

class Server:    public Properties
{
    public:
        Server(void);
        Server(const Server &copy);
        virtual ~Server(void);

        Server &operator=(Server const &right);

        //get
        std::string const &getName(void) const;
        std::string const &getIp(void) const;
        int const &getPort(void) const;
        std::map<std::string, Location*> const &getLocations() const;

        void parseServer(std::vector<std::string>::const_iterator &it, std::vector<std::string>::const_iterator end);
        bool parseName(std::string line);
        bool parseIp(std::string line);
        bool parsePort(std::string line);
        bool parseLocations(std::vector<std::string>::const_iterator &it, std::vector<std::string>::const_iterator end);

        private:
        std::string _name;
        std::string _ip;
        int         _port;
        std::map<std::string, Location*> _locations;

};

#endif //WEBSERV_SERVER_HPP
