//
// Created by tywael on 12/9/22.
//
#include "../inc/Properties.hpp"

Properties::Properties(void): _root(""), _index(""), _max_body_size(1048576), _cgi_bin(""), _directory_listing(false), _upload_dir("") {}

Properties::Properties(const Properties &copy)
{
    (*this) = copy;
}

Properties::~Properties(void) {}

Properties &Properties::operator=(Properties const &right)
{
    if (&right != this)
    {
        _root = right.getRoot();
        _index = right.getIndex();
        _max_body_size = right.getMaxBody();
        _allowed_method = right.getAllowedMet();
        _cgi_bin = right.getCgiBin();
        _directory_listing = right.getDirListing();
        _cgi_extensions = right.getCgiExtensions();
        _upload_dir = right.getUploadDir();
    }
    return (*this);
}

std::string const &Properties::getRoot(void) const
{
    return (_root);
}

std::string const &Properties::getIndex(void) const
{
    return (_index);
}

std::string const &Properties::getCgiBin(void) const
{
    return (_cgi_bin);
}

std::string const &Properties::getUploadDir(void) const
{
    return (_upload_dir);
}

int const &Properties::getMaxBody(void) const
{
    return (_max_body_size);
}

bool const &Properties::getDirListing(void) const
{
    return (_directory_listing);
}

std::vector<std::string> const &Properties::getCgiExtensions(void) const
{
    return (_cgi_extensions);
}

std::vector<std::string> const &Properties::getAllowedMet(void) const
{
    return (_allowed_method);
}

