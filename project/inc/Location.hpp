//
// Created by tywael on 12/3/22.
//

#ifndef WEBSERV_ROUTE_HPP
#define WEBSERV_ROUTE_HPP

#include "Properties.hpp"
#include "parse.h"

class Location:    public Properties
{
public:
    Location();
    ~Location();

    void parseLocation(std::vector<std::string>::const_iterator it, std::vector<std::string>::const_iterator end);
};


#endif //WEBSERV_ROUTE_HPP
