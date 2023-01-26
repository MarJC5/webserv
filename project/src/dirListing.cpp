//
// Created by tywael on 1/26/23.
//

#include <dirent.h>
#include <string>
#include <vector>
#include <iostream>
#include "../inc/HttpException.hpp"

std::vector<std::string> dirListing(std::string locName, std::string const dirPath)
{
    DIR *dir;
    struct dirent *dirent;
    std::vector<std::string> ret;
    std::vector<struct dirent> ents;

    if (locName.back() != '/')
        locName.push_back('/');
    if ((dir = opendir(dirPath.c_str())) == NULL)
        catchErrno();
    while ((dirent = readdir(dir)) != 0) {
        ents.push_back(*dirent);
    }
    closedir(dir);
    for (std::vector<struct dirent>::iterator it = ents.begin(); it < ents.end(); it++) {
        ret.push_back("<a href=\"" + locName + std::string(it->d_name) +"\">" + std::string(it->d_name) + "</a>");
    }
    return ret;
}