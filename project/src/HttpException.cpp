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
	setStatusMessage(statusMessage, statusCode);
}

HttpException::HttpException(std::string statusCode) {
	_initDefault();
	_statusCode = statusCode;
}

/**
 * Method: HttpException::~HttpException
 * Description: Destructor
 * Parameters: N/A
 * Returns: N/A
 */

HttpException::~HttpException(void) throw() {
_statusCode.clear();
}

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
		_status = rhs.getStatus();
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
	if (std::atoi(_statusCode.c_str()) >= 0 && std::atoi(_statusCode.c_str()) >= 100 && std::atoi(_statusCode.c_str()) < 300)
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

	if (_status.find(statusCode) != _status.end())
		return _status.find(statusCode)->second;
	else
		return "Unknown error";
	return "";
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
 * Getter: HttpException::getStatus
 * Description: Returns the error code.
 * Parameters: N/A
 * Returns: int
 */

std::map<std::string, std::string> HttpException::getStatus(void) const {
	return _status;
}

/**
 * Method: HttpException::setMessage
 * Description: Sets the error message.
 * Parameters: std::string errMessage, int errCode
 * Returns: void
 */

void HttpException::setStatusMessage(std::string statusMessage, std::string statusCode) {
	if (_status.find(statusCode) != _status.end()) {
		_status[statusCode] = statusMessage;
	} else {
		_status.insert(std::pair<std::string, std::string>(statusCode, statusMessage));
	}
}

/**
 * Method: HttpException::setStatusCode
 * Description: Sets the error code.
 * Parameters: int statusCode
 * Returns: void
 */

void HttpException::setStatusCode(std::string statusCode) {
	_statusCode = statusCode;
}

/**
 * Method: HttpException::_initStatusCodes
 * Description: Get all defined error codes in status.h
 * Parameters: N/A
 * Returns: void
 */

void HttpException::_initDefault(void) {
	std::ifstream file("inc/status.h");
	std::string msg;
	std::string code;
	std::string line;

	if (!file.is_open())
	{
		std::cerr << "Unable to open file" << std::endl;
		return;
	} else {
		while (std::getline(file, line))
		{
			if (line.find("#define HTTP_") != std::string::npos)
			{
				size_t end = line.find_first_of(" \t\r\n", line.find("HTTP_") + 5);
				msg = line.substr(line.find("HTTP_") + 5, end - line.find("HTTP_") - 5);
				code = line.substr(end + 1, line.find_first_of(" \t\r\n", end + 1) - end - 1);
				_status[code] = msg;
			}
		}
		file.close();
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
	std::string reset = "\033[0m";
	std::string status = rhs.getStatusCode();

	if (std::atoi(status.c_str()) >= 0 && std::atoi(status.c_str()) >= 100 && std::atoi(status.c_str()) < 300)
		color = "\033[1;32m";
	else if (std::atoi(status.c_str()) >= 300 && std::atoi(status.c_str()) < 400)
		color = "\033[1;33m";
	else if (std::atoi(status.c_str()) >= 400 && std::atoi(status.c_str()) < 500)
		color = "\033[1;31m";
	else if (std::atoi(status.c_str()) >= 500 && std::atoi(status.c_str()) < 600)
		color = "\033[1;35m";

	o << color << status << reset << " " << rhs.getStatusMessage(status) << std::endl;
	return o;
}