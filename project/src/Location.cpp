//
// Created by tywael on 1/3/23.
//

#include "../inc/Location.hpp"
#include <iostream>

Location::Location(): Properties() {}

Location::~Location() {}

void Location::parseLocation(std::vector<std::string>::const_iterator &it,
                             std::vector<std::string>::const_iterator end) {
    (void)end;
    std::cout << *it << std::endl;
}
