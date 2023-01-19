//
// Created by tywael on 1/5/23.
//

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

std::vector<std::string> readFile(std::string fileName) {
	std::string line;
	std::ifstream file;
	std::vector<std::string> _lines;

	file.open(fileName.c_str());
	while (std::getline(file, line))
		_lines.push_back(line);
	file.close();
	return _lines;
}

size_t findKey(std::string line, std::string search)
{
    size_t ret;

    ret = line.find(search);
    if (ret == 0 || line[ret - 1] == ' ' || line[ret - 1] == '{' || line[ret - 1] == ';')
        return (ret);
    return (std::string::npos);
}

std::string getVal(std::string line, std::string attrib, size_t pos) {
    size_t lenWord;
    size_t lenTemp;
    std::string temp;

    pos += std::string(attrib).size();
    pos = line.find_first_not_of(" ", pos);
    lenWord = line.find(" ", pos) - (pos);
    lenTemp = line.find(";", pos) - (pos);
    if (lenTemp < lenWord)
        lenWord = lenTemp;
    temp = line.substr(pos, lenWord);
    if (temp.back() == ';')
        temp.erase(temp.back());
    return (temp);
}

bool    skip_space(std::string &line)
{
    if (line[0] == ' ') {
        line.erase(0, line.find_first_not_of(' '));
        return (true);
    }
    return (false);
}

std::string cut_word(std::string &line, size_t pos)
{
    std::string temp;

    temp = line.substr(0, pos);
    line.erase(0, temp.size());
//    if (temp.back() == ';')
//        temp.erase(temp.back());
    return (temp);
}

std::vector<std::string> split(std::string line, std::string sep)
{
    std::vector<std::string> ret;
    size_t pos = 0;

    while ((pos = line.find(sep)) != std::string::npos)
    {
        if (skip_space(line))
            continue ;
        ret.push_back(cut_word(line, pos));
    }
    if (!line.empty())
        ret.push_back(cut_word(line, line.back()));
    ret.erase(ret.begin());
    return (ret);
}