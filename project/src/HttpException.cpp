#include "../inc/HttpException.hpp"

/**
* Method: HttpException::HttpException
 * Description: Constructor
 * Parameters: std::string statusMessage, int statusCode
 * Returns: N/A
*/

HttpException::HttpException(void) {
	_initDefault();
}

HttpException::HttpException(std::string statusMessage, std::string statusCode) {
	_initDefault();
	if (!statusMessage.empty() && atoi(statusCode.c_str()) >= 0)
	{
		manageStatusMessage(statusMessage, statusCode);
		_statusCode = statusCode;
	}
}

HttpException::HttpException(std::string statusCode) {
	_initDefault();
	if (atoi(statusCode.c_str()) >= 0)
	{
		_statusCode = statusCode;
	}
}

/**
 * Method: HttpException::~HttpException
 * Description: Destructor
 * Parameters: N/A
 * Returns: N/A
 */

HttpException::~HttpException(void) throw() {}

/**
* Method: HttpException::HttpException
 * Description: Copy constructor
 * Parameters: HttpException const &src
 * Returns: N/A
*/

HttpException::HttpException(HttpException const &src) {
	if (this != &src) {
		*this = src;
	}
	return ;
}

/**
 * Method: HttpException::operator=
 * Description: Assignment operator
 * Parameters: HttpException const &rhs
 * Returns: HttpException&
 */

HttpException &HttpException::operator=(HttpException const &rhs) {
	if (this != &rhs) {
		_statusCode = rhs.getStatusCode();
	}
	return *this;
}

/**
 * Method: HttpException::operator<<
 * Description: Overload operator<<
 * Parameters: int statusCode
 * Returns: HttpException&
 */

HttpException &HttpException::operator<<(std::string statusCode) {
	setStatusCode(statusCode);
	return *this;
}

/**
* Method: HttpException::what
 * Description: Returns the error message.
 * Parameters: N/A
 * Returns: const char *
*/

const char *HttpException::what() const throw() {
	if (atoi(_statusCode.c_str()) >= 0 && atoi(_statusCode.c_str()) >= 100 && atoi(_statusCode.c_str()) < 300)
		std::cout << *this;
	else
		std::cerr << *this;
	return "";
}

/**
* Getter: HttpException::getMessage
 * Description: Returns the error message.
 * Parameters: int errCode
 * Returns: std::string
*/

std::string HttpException::getStatusMessage(std::string statusCode) const {

	/*for (std::map<std::string, std::string>::const_iterator it = _status.begin(); it != _status.end(); ++it) {
		std::cout << it->first << " : " << it->second << std::endl;
	}*/

	if (_status.find(statusCode) != _status.end()) {
		return _status.find(statusCode)->second;
	}
	return "Unknown error";
}

/**
 * Getter: HttpException::getErrCode
 * Description: Returns the error code.
 * Parameters: N/A
 * Returns: int
 */

std::string HttpException::getStatusCode(void) const {
	return _statusCode;
}

/**
 * Method: HttpException::setMessage
 * Description: Sets the error message.
 * Parameters: std::string errMessage, int errCode
 * Returns: void
 */

void HttpException::setStatusMessage(std::string statusMessage, std::string statusCode) {
	if (!statusMessage.empty() && atoi(statusCode.c_str()) >= 0) {
		_init(statusCode, statusMessage);
	}
}

/**
 * Method: HttpException::setStatusCode
 * Description: Sets the error code.
 * Parameters: int statusCode
 * Returns: void
 */

void HttpException::setStatusCode(std::string statusCode) {
	if (atoi(statusCode.c_str()) >= 0) {
		_statusCode = statusCode;
	}
}

/**
 * Method: HttpException::_initStatusCodes
 * Description: Get all defined error codes in status.h
 * Parameters: N/A
 * Returns: void
 */

void HttpException::_initDefault(void) {
	std::ifstream file("inc/status.h");
	std::string status;
	std::string code;
	std::string line;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			if (line.find("#define HTTP_") != std::string::npos)
			{
				line.erase(0, line.find("HTTP_") + 5);
				status = line.substr(0, line.find(" "));
				line.erase(0, line.find(" ") + 1);
				code = line;
				_init(code, status);
			}
		}
	} else {
		std::cerr << "Unable to open file" << std::endl;
	}
	file.close();
}

/*
 * Init default values
 * @param code HTTP status code
 * @param message HTTP status message
 */

void HttpException::_init(std::string code, std::string message)
{
	_status[code] = message;
}

/**
 * Method: HttpException::manageStatusMessage
 * Description: Add a new error message.
 * Parameters: std::string errMessage, int errCode
 * Returns: void
 */

void HttpException::manageStatusMessage(std::string statusMessage, std::string statusCode) {
	if (!statusMessage.empty() && atoi(statusCode.c_str()) >= 0) {
		_init(statusCode, statusMessage);
	}
}

/**
 * Method: std::ostream &operator<<
 * Description: Overload of the << operator
 * Parameters: std::ostream &o, HttpException const &rhs
 * Returns: std::ostream&
 */

std::ostream &operator<<(std::ostream &o, HttpException const &rhs) {
	std::string color = "\033[1;37m";
	int statusCode = atoi(rhs.getStatusCode().c_str());

	if (rhs.getStatusMessage(rhs.getStatusCode()) == "Unknown error")
		color = "\033[1;37m";
	else if (statusCode >= 100 && statusCode < 200)
		color = "\033[1;34m";
	else if (statusCode >= 200 && statusCode < 300)
		color = "\033[1;32m";
	else if (statusCode >= 300 && statusCode < 400)
		color = "\033[1;35m";
	else if (statusCode >= 400 && statusCode < 500)
		color = "\033[1;33m";
	else if (statusCode >= 500 && statusCode < 600)
		color = "\033[1;31m";

	o << color
		<< rhs.getStatusCode()
		<< " "
		<< "\033[0m"
		<< rhs.getStatusMessage(rhs.getStatusCode());
	return o;
}