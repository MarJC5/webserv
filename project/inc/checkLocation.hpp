//
// Created by tywael on 1/16/23.
//

#ifndef WEBSERV_CHECK_LOCATION_HPP
#define WEBSERV_CHECK_LOCATION_HPP

Location &check_location(const std::map<std::string, Location*> &locations, std::string uri, std::string &file);
std::vector<std::string> readIndex(const Location &loc);

#endif //WEBSERV_CHECK_LOCATION_HPP
