/**
 * HttpException class
 * Holds the exception information for the HttpParser class and its methods.
 *
 * How to use:
 * 1. Create an instance of HttpException.
 * 2. Call the constructor with the error message.
 * 3. Call what() to get the error message.
 *
 */

#ifndef HTTPEXCEPTION_HPP
#define HTTPEXCEPTION_HPP

#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include <string>
#include <cstdlib>
#include <map>
#include <errno.h>

#include "status.h"

class HttpException : public std::exception
{
	public:
	// Constructor
	HttpException(void);
	HttpException(std::string statusCode);
	HttpException(std::string statusMessage, std::string statusCode);
	virtual ~HttpException(void) throw();
	HttpException(HttpException const &src);

	HttpException &operator=(HttpException const &rhs); // Assignment operator
	HttpException &operator<<(std::string statusCode); // Set status code

	// Get/Set
	std::string getStatusMessage(std::string statusCode) const;
	std::string getStatusCode(void) const;

	std::map<std::string, std::string> getStatus(void) const;

	void        setStatusMessage(std::string statusMessage, std::string statusCode);
	void        setStatusCode(std::string statusCode);

	// throw error
	virtual const char *what() const throw();

	private:
	std::string              _statusCode;

	std::map<std::string, std::string> _status;

	void    _initDefault(void);
};

std::ostream &operator<<(std::ostream &o, HttpException const &rhs);

void catchErrno(void);
#endif
