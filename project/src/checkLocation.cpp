//
// Created by tywael on 1/16/23.
//

#include "../inc/Location.hpp"
#include <map>
#include <iostream>

std::vector<std::string> readIndex(const Location &loc)
{
    std::vector<std::string> ret;
    const std::vector<std::string> &index = loc.getIndex();
    for (std::vector<std::string>::const_iterator it = index.begin(); it < index.end(); it++){
        ret = readFile(loc.getRoot() + *it);
        if (ret[0] == "Error: Could not open file")
            continue;
        return (ret);
    }
    return (ret);
}

Location &check_location(const std::map<std::string, Location*> &locations, std::string uri, std::string &file)
{
    std::string dir = uri;

    while (uri.size() > 1) {
        if (locations.find(uri) != locations.end()) {
            file = dir.substr(uri.size()) + file;
            return (*(locations.find(uri)->second));
        }
        uri = uri.substr(0, uri.rfind("/"));
    }
    if (locations.find("/") != locations.end()) {
        file = dir.substr(uri.size()) + file;
        return (*(locations.find("/")->second));
    }
    return (*locations.begin()->second);
}
