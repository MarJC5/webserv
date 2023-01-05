//
// Created by tywael on 1/5/23.
//

#include <string>
#include <vector>

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

std::vector<std::string> split(std::string line, std::string sep)
{
    std::vector<std::string> ret;
    std::string temp;
    size_t pos = 0;

    while ((pos = line.find(sep,pos)) != std::string::npos)
    {
        temp = line.substr(0, pos);
        if (temp.back() == ';')
            temp.erase(temp.back());
        ret.push_back(temp);
        line.erase(0, pos + sep.size());
    }
    ret.erase(ret.begin());
    return (ret);
}