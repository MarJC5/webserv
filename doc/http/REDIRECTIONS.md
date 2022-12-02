# HTTP Redirection

- [RFC 7231](https://datatracker.ietf.org/doc/html/rfc7231#section-6.4)
- [Handling redirections](#Handling-redirections)
  - [301 Moved Permanently](#301-Moved-Permanently)
  - [302 Found](#302-Found)
  - [303 See Other](#303-See-Other)
  - [307 Temporary Redirect](#307-Temporary-Redirect)
  - [308 Permanent Redirect](#308-Permanent-Redirect)
- [Handling redirections in webserv](#Handling-redirections-in-webserv)

# Handling redirections

In the case of a redirection, the server must send a response with a status code indicating the redirection type and a `Location` header containing the URL to which the client should be redirected.

The redirection status codes listed below are the most common ones

| Code | Description |
| :--- | :---------- |
| 301 | Moved Permanently |
| 302 | Found |
| 303 | See Other |
| 307 | Temporary Redirect |
| 308 | Permanent Redirect |

# 301 Moved Permanently

The 301 status code indicates that the resource has been permanently moved to a new location. The new location is provided in the `Location` header of the response.

# 302 Found

The 302 status code indicates that the resource has been temporarily moved to a new location. The new location is provided in the `Location` header of the response.

# 303 See Other

The 303 status code indicates that the server is redirecting the client to a different resource, as indicated by a URI in the `Location` header. The method used to make the original request will not be changed when the redirected request is made. For example, a POST request will be repeated using POST.

# 307 Temporary Redirect

The 307 status code indicates that the resource has been temporarily moved to a new location. The new location is provided in the `Location` header of the response. The method used to make the original request will not be changed when the redirected request is made. For example, a POST request will be repeated using POST.

# 308 Permanent Redirect

The 308 status code indicates that the resource has been permanently moved to a new location. The new location is provided in the `Location` header of the response. The method used to make the original request will not be changed when the redirected request is made. For example, a POST request will be repeated using POST.

# Handling redirections in webserv

// TODO : add redirection management

[Back to summary](../SUMMARY.md)