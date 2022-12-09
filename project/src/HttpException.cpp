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

HttpException::HttpException(std::string statusMessage, int statusCode) {
	_initDefault();
	if (!statusMessage.empty() && statusCode >= 0)
		_init(statusCode, statusMessage);
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

HttpException &HttpException::operator<<(int statusCode) {
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
	std::cout << *this;
	return "";
}

/**
* Getter: HttpException::getMessage
 * Description: Returns the error message.
 * Parameters: int errCode
 * Returns: std::string
*/

std::string HttpException::getStatusMessage(int statusCode) const {
	for (size_t i = 0; i < _statusCodes.size(); i++) {
		if (_statusCodes[i] == statusCode) {
			return _statusMessages[i];
		}
	}
	return "Unknown error";
}

/**
 * Getter: HttpException::getErrCode
 * Description: Returns the error code.
 * Parameters: N/A
 * Returns: int
 */

int HttpException::getStatusCode(void) const {
	return _statusCode;
}

/**
 * Method: HttpException::setMessage
 * Description: Sets the error message.
 * Parameters: std::string errMessage, int errCode
 * Returns: void
 */

void HttpException::setStatusMessage(std::string statusMessage, int statusCode) {
	if (!statusMessage.empty() && statusCode >= 0) {
		_init(statusCode, statusMessage);
	}
}

/**
 * Method: HttpException::setStatusCode
 * Description: Sets the error code.
 * Parameters: int statusCode
 * Returns: void
 */

void HttpException::setStatusCode(int statusCode) {
	if (statusCode >= 0) {
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
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			if (line.find("#define HTTP_") != std::string::npos)
			{
				std::string status = line.substr(line.find("HTTP_") + 5);
				std::string code = status.substr(status.find(" ") + 1);
				status = status.substr(0, status.find(" "));
				_init(atoi(code.c_str()), status);
			}
		}
	}
	else
	{
		std::cerr << "Unable to open file" << std::endl;
	}
	file.close();
}

/*
 * Method: HttpException::_init
 * @param code HTTP status code
 * @param message HTTP status message
 */

void HttpException::_init(int code, std::string message)
{
	_statusCode = code;
	_statusMessages.push_back(message);
	_statusCodes.push_back(code);
}

/**
 * Method: HttpException::manageStatusMessage
 * Description: Add a new error message.
 * Parameters: std::string errMessage, int errCode
 * Returns: void
 */

void HttpException::manageStatusMessage(std::string statusMessage, int statusCode) {
	if (!statusMessage.empty() && statusCode >= 0) {
		// if already exists, update the message
		for (size_t i = 0; i < _statusCodes.size(); i++) {
			if (_statusCodes[i] == statusCode) {
				_statusMessages[i] = statusMessage;
				return ;
			}
		}
		_statusMessages.push_back(statusMessage);
		_statusCodes.push_back(statusCode);
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
	int statusCode = rhs.getStatusCode();

	if (rhs.getStatusMessage(statusCode) == "Unknown error")
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
		<< statusCode
		<< " "
		<< "\033[0m"
		<< rhs.getStatusMessage(statusCode) << std::endl;
	return o;
}