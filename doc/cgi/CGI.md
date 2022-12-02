# CGI

- [What is CGI?](#what-is-cgi)
- [How does it work?](#how-does-it-work)
- [CGI Environment Variables](#cgi-environment-variables)
  - [Mandatory](#mandatory)
- [CGI in Webserv](#cgi-in-webserv)

## What is CGI?

CGI is a protocol that allows a web server to execute programs on the server side and return the result to the client.

## How does it work?

CGI is a protocol that allows a web server to execute programs on the server side and return the result to the client.

## CGI Environment Variables

CGI Environment Variables are variables that are passed to the program when it is executed.

### Mandatory

- `AUTH_TYPE` - The authentication type
- `CONTENT_LENGTH` - The length of the request body
- `CONTENT_TYPE` - The type of the request body
- `GATEWAY_INTERFACE` - The CGI version
- `PATH_INFO` - The path to the resource
- `PATH_TRANSLATED` - The path to the resource
- `QUERY_STRING` - The query string
- `REMOTE_ADDR` - The IP address of the client
- `REMOTE_HOST` - The hostname of the client
- `REMOTE_IDENT` - The identity of the client
- `REMOTE_USER` - The user name of the client
- `REQUEST_METHOD` - The method of the request
- `SCRIPT_NAME` - The name of the script
- `SERVER_NAME` - The name of the server
- `SERVER_PORT` - The port of the server
- `SERVER_PROTOCOL` - The protocol of the request
- `SERVER_SOFTWARE` - The name and version of the server

## CGI in webserv

// TODO: add CGI management

[Back to summary](../SUMMARY.md)