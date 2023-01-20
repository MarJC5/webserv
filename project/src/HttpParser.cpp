#include "../inc/HttpParser.hpp"
#include "../inc/check_location.hpp"
#include "../inc/parse.h"

/**
 * Method: HttpParser::consutrctor
 */

HttpParser::HttpParser(void){};

HttpParser::HttpParser(Server &serv) : _serv(serv){};

HttpParser::HttpParser(char *buffer)
{
	parse(buffer);
};

/**
 * Method: HttpParser::destructor
 */

HttpParser::~HttpParser(void)
{
	_headers.clear();
	_method.clear();
	_uri.clear();
	_file.clear();
	_host.clear();
	_port.clear();
	_httpVersion.clear();
	_body.clear();
	_headers.clear();
	_statusCode.clear();
	_statusMessage.clear();
};

/**
 * Method: HttpParser::copy
 */

HttpParser::HttpParser(HttpParser const &src)
{
	if (this != &src)
	{
		*this = src;
	}
	return;
}

/**
 * Method: HttpParser::operator
 */

HttpParser &HttpParser::operator=(HttpParser const &rhs)
{
	if (this != &rhs)
	{
		_method = rhs.getMethod();
		_uri = rhs.getUri();
		_file = rhs.getFile();
		_host = rhs.getHost();
		_port = rhs.getPort();
		_httpVersion = rhs.getHttpVersion();
		_body = rhs.getBody();
		_headers = rhs.getHeaders();
		_statusCode = rhs.getStatusCode();
		_statusMessage = rhs.getStatusMessage();
		_loc = rhs.getLocation();
		_serv = rhs.getServer();
		_status = rhs.getStatus();
	}
	return *this;
}

/**
 * Methods: HttpParser::setters
 */

void HttpParser::setStatus(std::string statusCode, std::string statusMessage)
{
	_statusCode = statusCode;
	_statusMessage = statusMessage;
}

void HttpParser::setStatusCode(std::string statusCode)
{
	_statusCode = statusCode;
}

void HttpParser::setStatusMessage(std::string statusMessage)
{
	_statusMessage = statusMessage;
}

void HttpParser::setMethod(std::string method)
{
	_method = method;
}

void HttpParser::setUri(std::string uri)
{
	_uri = uri;
}

void HttpParser::setHttpVersion(std::string httpVersion)
{
	_httpVersion = httpVersion;
}

void HttpParser::setBody(std::string body)
{
	_body = body;
}

void HttpParser::setHeader(std::string header, std::string value)
{
	_headers[header] = value;
}

void HttpParser::setServ(const Server &serv)
{
	_serv = serv;
}

/**
 * Methods: HttpParser::getters
 */

std::string HttpParser::getMethod(void) const
{
	return (_method);
}

std::string HttpParser::getUri(void) const
{
	return (_uri);
}

std::string HttpParser::getFile(void) const
{
	return (_file);
}

std::string HttpParser::getHost(void) const
{
	return (_host);
}

std::string HttpParser::getPort(void) const
{
	return (_port);
}

const Location &HttpParser::getLocation() const
{
	return (_loc);
}

std::string HttpParser::getHttpVersion(void) const
{
	return (_httpVersion.substr(0, _httpVersion.find_last_not_of(" \r\n\t") + 1));
}

std::string HttpParser::getBody(void) const
{
	return (_body);
}

std::string HttpParser::getStatusCode(void) const
{
	return (_statusCode.substr(0, _statusCode.find_last_not_of(" \r\n\t") + 1));
}

std::string HttpParser::getStatusMessage(void) const
{
	return (_statusMessage);
}

HttpException HttpParser::getStatus(void) const
{
	return _status;
}

const Server &HttpParser::getServer() const
{
	return _serv;
}

bool HttpParser::parsType(void) const
{
	return (_isRequest);
}

std::map<std::string, std::string> HttpParser::getHeaders(void) const
{
	return (_headers);
}

/**
 * Method: HttpParser::parse
 * Description: Parse the HTTP message in the buffer.
 */

std::vector<std::string> HttpParser::split(std::string str, std::string delimiter)
{
	std::vector<std::string> result;
	size_t pos = 0;
	std::string token;

	while ((pos = str.find(delimiter)) != std::string::npos)
	{
		token = str.substr(0, pos);
		result.push_back(token);
		str.erase(0, pos + delimiter.length());
	}

	result.push_back(str);
	return (result);
}

void HttpParser::parse(char *buffer)
{
	std::string str(buffer);
	std::vector<std::string> lines;
	std::string line;

	std::istringstream iss(str);
	while (std::getline(iss, line))
	{
		lines.push_back(line);
		if (line.empty() || line == "\r")
		{
			break;
		}
	}
	// Body
	while (std::getline(iss, line))
	{
		_body += line + "\n";
	}

	for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
	{
		std::vector<std::string> tokens = split(*it, ": ");
		if (it == lines.begin())
		{
			std::vector<std::string> firstLine = split(*it, " ");
			_method = firstLine[0];
			_uri = firstLine[1].substr(0, firstLine[1].rfind('/') + 1);
			_file = firstLine[1].substr(firstLine[1].rfind('/') + 1, std::string::npos);
			_loc = check_location(_serv.getLocations(), _uri, _file);
			_httpVersion = firstLine[2];
			_isRequest = true;
		}
		else if (tokens.size() == 2)
		{
			_headers[tokens[0]] = tokens[1];
		}
	}

	// Host and port from headers
	if (_isRequest)
	{
		_host = _headers["Host"];
		std::vector<std::string> hostTokens = split(_host, ":");
		if (hostTokens.size() == 2)
		{
			_host = hostTokens[0];
			_port = hostTokens[1];
		}
		else
		{
			throw HttpException("403");
		}
	}
}

/**
 * Method: HttpParser::urlEncode
 * Description: Encode a string to be used in an URL.
 * @param str: The string to encode.
 * @return: The encoded string.
 */

std::string HttpParser::urlEncode(std::string const &str)
{
	std::string encoded = "";
	char c;
	int ic;
	std::string::const_iterator i = str.begin();
	std::string::const_iterator end = str.end();
	while (i != end)
	{
		c = (*i);
		ic = c;
		// Keep alphanumeric and other accepted characters intact
		if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
		{
			encoded += c;
		}
		else
		{
			// Any other characters are percent-encoded
			encoded += '%';
			encoded += std::string("0123456789ABCDEF")[(ic >> 4) & 0xF];
			encoded += std::string("0123456789ABCDEF")[ic & 0xF];
		}
		++i;
	}
	return encoded;
}

/**
 * Method: HttpParser::urlDecode
 * Description: Decode a string from an URL.
 * @param str: The string to decode.
 * @return: The decoded string.
 */

std::string HttpParser::urlDecode(std::string const &str)
{
	std::string decoded = "";
	char c;
	int ic;
	std::string::const_iterator i = str.begin();
	std::string::const_iterator end = str.end();
	while (i != end)
	{
		c = (*i);
		if (c == '+')
		{
			decoded += ' ';
		}
		else if (c == '%')
		{
			std::istringstream iss(str.substr(i - str.begin() + 1, 2));
			iss >> std::hex >> ic;
			decoded += static_cast<char>(ic);
			i += 2;
		}
		else
		{
			decoded += c;
		}
		++i;
	}
	return decoded;
}

/**
 * Method: HttpParser::showHeaders
 * Description: Show the headers of the HTTP message.
 */

void HttpParser::showHeaders(void) const
{
	if (_headers.size() > 0)
	{
		std::cout << std::left << std::setw(18) << "\n\033[1;37mHeaders\033[0m" << std::endl;
		for (std::map<std::string, std::string>::const_iterator it = _headers.begin(); it != _headers.end(); ++it)
		{
			std::cout << std::left << std::setw(18) << it->first << ": " << it->second << std::endl;
		}
	}
}

/**
 * Method: HttpParser::buildResponse(const std::vector<Server*> &servers);
 * Description: Build a response from the HTTP message.
 */

void HttpParser::uploadFile(void) {
	std::string path = _loc.getRoot() + _file;
	std::ofstream file(path.c_str(), std::ios::out | std::ios::trunc);
	if (file)
	{
		file << _body;
		file.close();
	}
}

void HttpParser::buildResponse(void)
{
	std::string fileExtension = _file.substr(_file.rfind('.') + 1, std::string::npos);
	std::vector<std::string> lines;
	std::string accept;

	std::cout << "request path: " << (this->getLocation().getRoot()) << this->getFile() << std::endl;
	lines = readFile(this->getLocation().getRoot() + this->getFile());

	if (!accept.empty())
		accept.clear();
	accept = this->getHeaders().find("Accept")->second;

	_status << "200";
	this->_statusCode = _status.getStatusCode();
	this->_statusMessage = _status.getStatusMessage(_status.getStatusCode());

	// RFC 1123 (HTTP date format)
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *gmtime(&now);
	std::strftime(buf, sizeof(buf), "%a, %d %b %Y %X GMT", &tstruct);
	this->_headers["Date"] = buf;

	// Content-Type
	this->_headers["Content-type"] = accept.substr(0, accept.find(','));

	// Content-Length (file size)
	int contentLength = 0;
	for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
	{
		contentLength += (*it).size();
	}
	std::ostringstream oss;

	std::ostringstream ossb;
	ossb << this->getHttpVersion() << " " << this->_statusCode << " " << this->_statusMessage << "\r\n"
	     << "Content-type: " << this->_headers["Content-type"] << "\r\n"
	     << "Connection: " << this->_headers["Connection"] << "\r\n"
	     << "Date: " << this->_headers["Date"] << "\r\n\n";

	contentLength += ossb.str().size();
	oss << contentLength;
	this->_headers["Content-Length"] = oss.str();

	// Body
	if (!_body.empty())
		this->_body.clear();

	// upload file
	if (this->getMethod() == "POST")
		this->uploadFile();

	for (std::vector<std::string>::const_iterator it = lines.begin(); it < lines.end(); ++it)
		ossb << (*it) << "\r\n";
	this->_body = ossb.str();

	this->_isRequest = false;
	std::cout << *this << std::endl;
}

/**
 * Method: HttpParser::ostream
 */

std::ostream &operator<<(std::ostream &o, HttpParser const &i)
{
	std::string c = "\033[1;37m";
	std::string nc = "\033[0m";

	if (i.parsType())
	{
		o << "Request" << std::endl;
		o << i.getMethod() << " " << i.getFile() << " " << i.getHttpVersion() << std::endl;
		o << "----------------" << std::endl;
	}
	else
	{
		o << "Response" << std::endl;
		o << i.getHttpVersion() << " " << i.getStatusCode() << " " << i.getStatusMessage() << std::endl;
		o << "----------------" << std::endl;
	}

	if (!i.getMethod().empty())
		o << c << std::left << std::setw(18) << "Method" << nc << ": " << i.getMethod() << std::endl;
	if (!i.getUri().empty())
		o << c << std::left << std::setw(18) << "Uri" << nc << ": " << i.getUri() << std::endl;
	if (!i.getHttpVersion().empty())
		o << c << std::left << std::setw(18) << "HttpVersion" << nc << ": " << i.getHttpVersion() << std::endl;
	if (!i.getHost().empty())
		o << c << std::left << std::setw(18) << "Host" << nc << ": " << i.getHost() << std::endl;
	if (!i.getPort().empty())
		o << c << std::left << std::setw(18) << "Port" << nc << ": " << i.getPort() << std::endl;
	if (!i.getStatusCode().empty())
		o << c << std::left << std::setw(18) << "Status" << nc << ": " << i.getStatus() << std::endl;
	i.showHeaders();
	if (!i.getBody().empty())
		o << c << std::left << std::setw(18) << "\nBody" << nc << "\n"
		  << i.getBody() << std::endl;
	return (o);
}
