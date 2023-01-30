//
// Created by tywael on 1/26/23.
//

#include <dirent.h>
#include <string>
#include <vector>
#include <iostream>
#include "../inc/HttpException.hpp"
#include "../inc/parse.h"

std::vector<std::string> dirListing(std::string locName, std::string const dirPath)
{
    DIR *dir;
    struct dirent *dirent;
    std::vector<std::string> ret;
	std::vector<std::string> partial;
    std::vector<struct dirent> ents;


    std::cout << locName << std::endl;

    if (locName.back() != '/')
        locName.push_back('/');
    if ((dir = opendir(dirPath.c_str())) == NULL)
        catchErrno();
    while ((dirent = readdir(dir)) != 0) {
        ents.push_back(*dirent);
    }
    closedir(dir);
	// ADD header
	ret.push_back("<!DOCTYPE html><html><head><title>Index of " + locName + "</title><link rel=\"stylesheet\" href=\"/src/stylesheets/main.css\"/></head><body>");
	ret.push_back("<section class=\"wrapper\"><h1>Index of " + locName + "</h1><ul class=\"dirlist\">");
    for (std::vector<struct dirent>::iterator it = ents.begin(); it < ents.end(); it++) {
	    ret.push_back("<li><a class=\"dir-link\" href=\"" + locName + std::string(it->d_name) + "\">");
		if (it->d_type == DT_DIR)
			ret.push_back("&#128193;");
		else if (it->d_type == DT_REG)
			ret.push_back("&#128196;");
		else if (it->d_type == DT_LNK)
			ret.push_back("&#128279;");
		else if (it->d_type == DT_FIFO)
			ret.push_back("&#128290;");
		else if (it->d_type == DT_SOCK)
			ret.push_back("&#128295;");
		else if (it->d_type == DT_CHR)
			ret.push_back("&#128187;");
		else if (it->d_type == DT_BLK)
			ret.push_back("&#128190;");
		else
			ret.push_back("&#10067;");
        ret.push_back("<span>" + std::string(it->d_name) + "</span></a>");
		ret.push_back("</li>");
    }
	ret.push_back("</ul></section><footer><div class=\"container\"><p>&#169;2023 - Webserv -</p><ul class=\"authors\"><li><a href=\"https://github.com/BolleCola\">BolleCola</a></li><li><a href=\"https://github.com/Tywael\">Tywael</a></li><li><a href=\"https://github.com/MarJC5\">MarJC5</a></li></ul></div></footer>");
	ret.push_back("</body></html>");
    return ret;
}