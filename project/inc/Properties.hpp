//
// Created by tywael on 12/6/22.
//

#ifndef WEBSERV_PROPERTIES_HPP
#define WEBSERV_PROPERTIES_HPP

class Properties
{
    public:
        Properties(void);
        Properties(const Properties &copy);
        virtual ~Properties(void);

        Server &operator=(Properties const &right);

        std::string const &getRoot(void) const;
        std::string const &getIndex(void) const;
        std::string const &getCgiBin(void) const;
        std::string const &getUploadDir(void) const;
        int const &getMaxBody(void) const;
        bool const &getDirListing(void) const;
        std::Array<std::string> const &getCgiExtensions(void) const;
        std::Array<std::string> const &getAllowedMet(void) const;


private:
        std::string             _root;
        std::string             _index;
        int                     _max_body_size;
        std::Array<std::string> _allowed_method;
        std::string             _cgi_bin;
        bool                    _directory_listing;
        std::Array<std::string> _cgi_extensions;
        std::string             _upload_dir;
};

#endif //WEBSERV_PROPERTIES_HPP
