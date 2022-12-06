//
// Created by tywael on 12/6/22.
//

#ifndef WEBSERV_PROPERTIES_HPP
#define WEBSERV_PROPERTIES_HPP

class Properties
{
    public:

    private:
        std::string             root;
        std::string             index;
        int                     max_body_size;
        std::Array<std::string> allowed_method;
        std::string             cgi_bin;
        bool                    directory_listing;
        std::Array<std::string> cgi_extensions;
        std::string             upload_dir;
};

#endif //WEBSERV_PROPERTIES_HPP
