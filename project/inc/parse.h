//
// Created by tywael on 1/5/23.
//

#ifndef WEBSERV_PARSE_H
#define WEBSERV_PARSE_H

size_t findKey(std::string line, std::string search);
std::string getVal(std::string line, std::string attrib, size_t pos);
std::vector<std::string> split(std::string line, std::string sep);
std::vector<std::string> readFile(std::string fileName);

#endif //WEBSERV_PARSE_H
