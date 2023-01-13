/**
 * Parses HTTP request and response messages.
 *
 * How to use:
 * 1. Create an instance of HttpParser.
 * 2. Call parse() with a buffer containing the HTTP message.
 *
 */

#ifndef HTTPPARSER_HPP
#define HTTPPARSER_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <cstring>
#include <stdlib.h>

#include "HttpException.hpp"

class HttpParser
{
	public:
		HttpParser(void);
		HttpParser(char *buffer);
		virtual ~HttpParser(void);
		HttpParser(HttpParser const &src);
		HttpParser &operator=(HttpParser const &rhs);

		// Parse the HTTP message in the buffer.
		void parse(char *buffer);

		// Request
		std::string getMethod(void) const;
		std::string getUri(void) const;
		std::string getHost(void) const;
		std::string getPort(void) const;
		std::string getHttpVersion(void) const;
		std::string getHeader(std::string header);
		std::string getBody(void) const;
		bool        parsType(void) const;

		// Get the status code and status message
		std::string     getStatusCode(void) const;
		std::string     getStatusMessage(void) const;
		HttpException   getStatus(void) const;

		// URL encoding and decoding
		static std::string urlEncode(std::string const &str);
		static std::string urlDecode(std::string const &str);

		// Response
		void setStatus(std::string statusCode, std::string statusMessage);
		void setStatusMessage(std::string statusMessage);
		void setStatusCode(std::string statusCode);

		void setMethod(std::string method);
		void setUri(std::string uri);
		void setHttpVersion(std::string httpVersion);
		void setHeader(std::string header, std::string value);
		void setBody(std::string body);

		// Build the HTTP response message with HttpParser instance variables.
		void buildResponse(void);

		// Methods
		void showHeaders(void) const;
		std::vector<std::string> split(std::string str, std::string delimiter);

	protected:
		std::string   _method;
		std::string   _uri;
		std::string   _httpVersion;
		std::string   _host;
		std::string   _port;
		std::string   _body;
		std::string   _statusCode;
		std::string   _statusMessage;
		bool		  _isRequest;
		std::map<std::string, std::string> _headers;
};

std::ostream &operator<<(std::ostream &o, HttpParser const &rhs);

#endif
