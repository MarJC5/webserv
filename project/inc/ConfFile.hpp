//
// Created by tywael on 12/28/22.
//

#ifndef WEBSERV_CONFFILE_HPP
#define WEBSERV_CONFFILE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class ConfFile {
    public:
        ConfFile(void);
        ConfFile(std::string fileName);
        ~ConfFile();
        void readFile(std::string fileName);
        const std::vector<std::string> &getLines() const;

    private:
        std::string _fileName;
        std::vector<std::string> _lines;
};


#endif //WEBSERV_CONFFILE_HPP
