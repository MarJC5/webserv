//
// Created by tywael on 12/6/22.
//

#ifndef WEBSERV_PROPERTIES_HPP
#define WEBSERV_PROPERTIES_HPP

#include <vector>
#include <string>
#include "parse.h"

class Properties
{
    public:
        Properties(void);
        Properties(const Properties &copy);
        virtual ~Properties(void);

        Properties &operator=(Properties const &right);

        std::string const &getRoot(void) const;
        std::vector<std::string> const &getIndex(void) const;
        std::string const &getCgiBin(void) const;
        std::string const &getUploadDir(void) const;
        int getMaxBody(void) const;
        bool const &getDirListing(void) const;
        std::vector<std::string> const &getCgiExtensions(void) const;
        std::vector<std::string> const &getAllowedMet(void) const;

        bool parseProper(std::string line);
        bool parseRoot(std::string line);
        bool parseIndex(std::string line);
        bool parseMaxBodySize(std::string line);
        bool parseAllowedMethod(std::string line);
        bool parseCgiBin(std::string line);
        bool parseDirList(std::string line);
        bool parseCgiExt(std::string line);
        bool parseUpDir(std::string line);

protected:
        std::string             _root;
        std::vector<std::string> _index;
        int                     _max_body_size;
        std::vector<std::string> _allowed_method;
        std::string             _cgi_bin;
        bool                    _directory_listing;
        std::vector<std::string> _cgi_extensions;
        std::string             _upload_dir;
};


#endif //WEBSERV_PROPERTIES_HPP
