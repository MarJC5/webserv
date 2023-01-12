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

bool Properties::parseProper(std::string line) {
    if (parseRoot(line))
        return (true);
    if (parseIndex(line))
        return (true);
    if (parseMaxBodySize(line))
        return (true);
    if (parseAllowedMethod(line))
        return (true);
    if (parseCgiBin(line))
        return (true);
    if (parseCgiExt(line))
        return (true);
    if (parseDirList(line))
        return (true);
    if (parseUpDir(line))
        return (true);
    return (false);
}

bool Properties::parseRoot(std::string line) {
    size_t pos;

    if ((pos = findKey(line, "root")) != std::string::npos) {
        _root = getVal(line, "root", pos);
        return (true);
    }
    return (false);
}

bool Properties::parseIndex(std::string line) {
    size_t pos;

    if ((pos = findKey(line, "index ")) != std::string::npos) {
        _index = getVal(line, "index", pos);
        return (true);
    }
    return (false);
}

bool Properties::parseMaxBodySize(std::string line) {
    size_t pos;

    if ((pos = findKey(line, "client_max_body_size ")) != std::string::npos) {
        _max_body_size = stoi(getVal(line, "client_max_body_size", pos));
        return (true);
    }
    return (false);
}

bool Properties::parseAllowedMethod(std::string line) {
    size_t pos;

    if ((pos = findKey(line, "method ")) != std::string::npos) {
        _cgi_extensions = split(line, " ");
        return (true);
    }
    return (false);
}

bool Properties::parseCgiBin(std::string line) {
    size_t pos;

    if ((pos = findKey(line, "cgi_path ")) != std::string::npos) {
        _cgi_bin = getVal(line, "cgi_path", pos);
        return (true);
    }
    return (false);
}

bool Properties::parseDirList(std::string line) {
    size_t pos;

    if ((pos = findKey(line, "autoindex ")) != std::string::npos) {
        if (getVal(line, "autoindex", pos) == "true")
            _directory_listing = true;
        else
            _directory_listing = false;
        return (true);
    }
    return (false);
}

bool Properties::parseCgiExt(std::string line) {
    size_t pos;

    if ((pos = findKey(line, "cgi_extension ")) != std::string::npos) {
        _cgi_extensions = split(line, " ");
        return (true);
    }
    return (false);
}

bool Properties::parseUpDir(std::string line) {
    size_t pos;

    if ((pos = findKey(line, "upload_folder ")) != std::string::npos) {
        _upload_dir = getVal(line, "upload_folder", pos);
        return (true);
    }
    return (false);
}
