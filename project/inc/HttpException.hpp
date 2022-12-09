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
#include <string>
#include <vector>
#include <stdlib.h>

#include "status.h"

class HttpException : public std::exception
{
	public:
		// Constructor
		HttpException(void);
		HttpException(int statusCode);
		HttpException(std::string statusMessage, int statusCode);
		~HttpException(void) throw();
		HttpException(HttpException const &src);

		HttpException &operator=(HttpException const &rhs); // Assignment operator
		HttpException &operator<<(int statusCode); // Set status code

		// Get/Set
		std::string getStatusMessage(int statusCode) const;
		int		    getStatusCode(void) const;

		void        setStatusMessage(std::string statusMessage, int statusCode);
		void        setStatusCode(int statusCode);

		// Methods
		void        manageStatusMessage(std::string statusMessage, int statusCode);

		// throw error
		virtual const char *what() const throw();

	private:
		int                      _statusCode;

		std::vector<std::string> _statusMessages;
		std::vector<int>         _statusCodes;

		void    _init(int code, std::string message);
		void    _initDefault(void);
};

std::ostream &operator<<(std::ostream &o, HttpException const &rhs);

#endif
