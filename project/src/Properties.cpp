//
// Created by tywael on 12/9/22.
//
#include "Properties.hpp"

Properties::Properties(void): _Root(), _Index(), _cgi_bin(), _max_body_size(), _allowed_method(), _directory_listing(), _cgi_extensions, _upload_dir() {}

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

std::string const &getRoot(void) const
{
    return (_root);
}

std::string const &getIndex(void) const
{
    return (_index);
}

std::string const &getCgiBin(void) const
{
    return (_cgi_bin);
}

std::string const &getUploadDir(void) const
{
    return (_upload_dir);
}

int const &getMaxBody(void) const
{
    return (_max_body_size);
}

bool const &getDirListing(void) const
{
    return (_directory_listing);
}

std::Array<std::string> const &getCgiExtensions(void) const
{
    return (_cgi_extensions);
}

std::Array<std::string> const &getAllowedMet(void) const
{
    return (_allowed_method);
}

