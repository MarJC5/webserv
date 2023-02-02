//
// Created by tywael on 1/5/23.
//

#ifndef WEBSERV_PARSE_H
#define WEBSERV_PARSE_H

#include <vector>

size_t findKey(std::string line, std::string search);
std::string getVal(std::string line, std::string attrib, size_t pos);
std::vector<std::string> split(std::string line, std::string sep);
std::vector<std::string> readFile(std::string fileName);

bool hasSuffix(const std::string &str, const std::string &suffix);
std::vector<std::string> spliter(const std::string& s, const std::string& delimiter);
std::string concatPath(std::string str1, std::string str2);

#endif //WEBSERV_PARSE_H
