//
// Created by tywael on 12/28/22.
//


#include "../inc/ConfFile.hpp"

ConfFile::ConfFile() {}

ConfFile::ConfFile(std::string fileName) {
    readFile(fileName);
}

ConfFile::~ConfFile() {}

void ConfFile::readFile(std::string fileName) {
    std::string line;
    std::ifstream file;

    _fileName = fileName;
    file.open(fileName.c_str());
    //if (file)
    //{
        //TO DO ERROR THROW FILE CORRUPTED...
    //}
    while (std::getline(file, line))
        _lines.push_back(line);
    file.close();
}

const std::vector<std::string> &ConfFile::getLines() const {
    return (_lines);
}