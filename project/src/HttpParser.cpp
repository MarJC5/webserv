#include "../inc/HttpParser.hpp"
#include "../inc/checkLocation.hpp"
#include "../inc/dirListing.hpp"

#include <algorithm>
/**
 * Method: HttpParser::consutrctor
 */

HttpParser::HttpParser(void)
{
	this->methods.push_back("GET");
	this->methods.push_back("POST");
	this->methods.push_back("DELETE");
};

HttpParser::HttpParser(Server &serv) : _serv(serv)
{
	this->methods.push_back("GET");
	this->methods.push_back("POST");
	this->methods.push_back("DELETE");
};

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
		this->methods = rhs.methods;
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

void HttpParser::setContentType(std::string fileExt, std::string accept) {
    std::string contentType = "application/octet-stream"; // default content type

    for (std::string::size_type i = 0; i < fileExt.length(); ++i)
        fileExt[i] = std::tolower(fileExt[i]);

    if (fileExt == "png" || fileExt == "jpg" || fileExt == "jpeg" || fileExt == "gif" || fileExt == "bmp" || fileExt == "tiff" || fileExt == "tif" || fileExt == "svg" || fileExt == "svgz") {
        contentType = "image/" + fileExt;
    } else if (fileExt == "avi" || fileExt == "mpg" || fileExt == "mpeg" || fileExt == "mp4" || fileExt == "mov" || fileExt == "wmv" || fileExt == "mkv" || fileExt == "webm" || fileExt == "ogv" || fileExt == "flv") {
        contentType = "video/" + fileExt;
    } else if (fileExt == "mp3" || fileExt == "wav" || fileExt == "ogg" || fileExt == "flac" || fileExt == "aac" || fileExt == "wma" || fileExt == "m4a" || fileExt == "mid" || fileExt == "midi") {
        contentType = "audio/" + fileExt;
    } else if (accept.size() > 0) {
        contentType = accept.substr(0, accept.find(','));
    }
    if (this->getHeaders().find("Content-Type")->second.size())
        _headers["Content-Type"] = contentType;
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
	_body.clear();
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

void HttpParser::checkMethod(std::vector <std::string> methods, std::string method) {
    if (std::find(this->methods.begin(), this->methods.end(), method) == this->methods.end())
        _status << "501";
    else if (std::find(methods.begin(), methods.end(), method) == methods.end())
        _status << "405";
}

void HttpParser::deleteMethod(void) {
	std::string path = _loc.getRoot() + _file;
	if (std::remove(path.c_str()) != 0) {
		_status << "400";
	} else {
		std::cout << "Removing: " << _file << std::endl;
		_status << "204";
		_body = "";
	}
}

bool HttpParser::postMethod(void) {
	if (_headers["Content-Type"].empty()) {
		_status << "400";
		return false;
	}
	// does it->second contain "multipart/form-data"? == Upload
	if (_headers["Content-Type"].find("multipart/form-data") != std::string::npos) {
		std::string boundary = _headers["Content-Type"].substr(30);
	    boundary.erase(0,boundary.find_first_not_of('-'));
	    _body = _body.substr(_body.find("/r/n") + 2, std::string::npos); // WTF BRO !!!
		std::vector<std::string> parts = spliter(_body, boundary);
		if (parts.size() < 2) {
			_status << "400";
			return false;
		}
	    for (unsigned int i = 1; i < parts.size(); i++) {
			std::string part = parts[i];
			if (part.empty() || !hasSuffix(part, "\r\n")) {
				continue;
			}
			// Find "Content-Disposition: form-data; name="file"; filename="filename.ext""
			std::string::size_type pos = part.find("Content-Disposition: form-data; name=\"file\"; filename=\"");
			if (pos == std::string::npos) {
				_status << "400";
			}
	        int n = std::string("Content-Disposition: form-data; name=\"file\"; filename=\"").size();
			std::string filename = part.substr(pos + n, part.find("\"", pos + n) - pos - n);

	        // Find the file content
			pos = part.find("\r\n\r\n");
			if (pos == std::string::npos) {
	            _status << "400";
			}
			std::string fileContent = part.substr(pos + 4, part.find("\r\n--", pos + 4) - pos - 4);
			// Save the file in the server
			std::ofstream file(getLocation().getRoot() + filename, std::ios::binary);
			if (file.is_open()) {
				file.write(fileContent.c_str(), fileContent.size());
				file.close();
				_status << "201";
			} else {
				_status << "500";
				return false;
			}
        }
	}
	return true;
}

void HttpParser::buildResponse(void) {
    std::string fileExt;
    std::vector <std::string> lines;
    std::ostringstream ossHeader;
    std::ostringstream ossBody;
    int contentLength = 0;
    time_t now = time(0);
    struct tm timeStruct = *gmtime(&now);
    char buf[80];

	std::cout << "Body: \n" << _body << std::endl;
    this->checkMethod(this->getLocation().getAllowedMet(), this->getMethod());
    // lancer CGI
	Cgi cgi(this->_body, _loc.getRoot() + _file, this->_headers, this->_loc, this->_serv.getName(), this->getMethod(), this->getHttpVersion(), this->_serv.getIp(), this->_serv.getPort());
	cgi.set_maplist();
	size_t n = _file.rfind(".");
	if (n == std::string::npos)
		n = 0;
	if (!_file.empty() && _file.substr(n) == ".php")
	{
		if (cgi.if_maplist_exist() == 0)
		{
			_body = cgi.launch_binary();
			_body = _body.substr(_body.find("\r\n\r\n") + 4);
			lines.push_back(_body);
			_status << "200";
		}
	}
	else if (getMethod() == "GET") {
        try {
            if (!this->getFile().empty()) {
                lines = readFile(this->getLocation().getRoot() + this->getFile());
            } else if (this->getLocation().getIndex().size() != 0) {
                lines = readIndex(this->getLocation());
            }
            if (lines.size() == 0 && this->getLocation().getDirListing()) {
                lines = dirListing(concatPath(_uri, _file), this->getLocation().getRoot() + _file);
            }
            if (lines.empty())
                catchErrno();
            _status << "200";
        }
        catch (HttpException::exception &e) {
            _status << e.what();
        }
    }
    else if (this->getMethod() == "POST") {
        postMethod();
    } else if (this->getMethod() == "DELETE") {
        deleteMethod();
    }

	this->_statusCode = _status.getStatusCode();
	this->_statusMessage = _status.getStatusMessage(_status.getStatusCode());

	if (std::atoi(this->_statusCode.c_str()) >= 400) {
		std::string error = this->_statusCode + " " + this->_statusMessage + "\r\n";
		lines.clear();
		lines.push_back(error);
		// Redirect to error page
		this->_file = "./www/error/" + this->_statusCode + ".html";
        try
        {
            lines = readFile(this->getFile());
        } catch (HttpException::exception &e) {
            _status << "500";
            _file = "500.html";
            lines = readFile("./www/error/500.html");
        }
	}

	// Content-type
	if (this->getMethod() != "POST") {
		fileExt = this->getFile().substr(this->getFile().find_last_of(".") + 1);
		setContentType(fileExt, this->getHeaders().find("Accept")->second);
	}

	// Date
	std::strftime(buf, sizeof(buf), "%a, %d %b %Y %X GMT", &timeStruct);
	this->_headers["Date"] = buf;

	// Headers
	for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
		contentLength += (*it).size();

	ossBody << this->getHttpVersion() << " " << this->_statusCode << " " << this->_statusMessage << "\r\n"
	     << "Content-Type: " << this->_headers["Content-Type"] << "\r\n"
	     << "Connection: " << this->_headers["Connection"] << "\r\n"
	     << "Date: " << this->_headers["Date"] << "\r\n";

	ossBody << "\n";

	contentLength += ossBody.str().size();
	ossHeader << contentLength;

	this->_headers["Content-Length"] = ossHeader.str();

	// Body
	this->_body.clear();

	for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
		ossBody << *it;

	this->_body = ossBody.str();

	this->_isRequest = false;
	std::cout << *this;

	if (this->getMethod() == "POST") {
		this->setMethod("GET");
		_headers["Content-Disposition"] = "inline";
		this->buildResponse();
	}
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
		o << "----------------------------------------------------------------" << std::endl;
	}
	else
	{
		o << "Response" << std::endl;
		o << i.getHttpVersion() << " " << i.getStatusCode() << " " << i.getStatusMessage() << std::endl;
		o << "----------------------------------------------------------------" << std::endl;
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
	if (VERBOSE >= 1)
		i.showHeaders();
	if (VERBOSE >= 2) {
		if (!i.getBody().empty())
			o << c << std::left << std::setw(18) << "\nBody" << nc << "\n"
			  << i.getBody() << std::endl;
	}
    o << "----------------------------------------------------------------" << std::endl;
	return (o);
}
