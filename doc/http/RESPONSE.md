# HTTP Response

- [RFC 7231](https://datatracker.ietf.org/doc/html/rfc7231#section-6)
- [Response codes](#Response-codes)
- [Response headers](#Response-headers)
- [Response body](#Response-body)
- [Handling responses in webserv](#Handling-responses-in-webserv)

## Response codes

Response codes are used to indicate the status of the request. The most common ones are listed below.

| Code | Description |
| :--- | :---------- |
| 200 | OK |
| 201 | Created |
| 202 | Accepted |
| 204 | No Content |
| 301 | Moved Permanently |
| 302 | Found |
| 304 | Not Modified |
| 400 | Bad Request |
| 401 | Unauthorized |
| 403 | Forbidden |
| 404 | Not Found |
| 405 | Method Not Allowed |
| 406 | Not Acceptable |
| 408 | Request Timeout |
| 413 | Payload Too Large |
| 414 | URI Too Long |
| 415 | Unsupported Media Type |
| 416 | Range Not Satisfiable |
| 417 | Expectation Failed |
| 418 | I'm a teapot |
| 500 | Internal Server Error |
| 501 | Not Implemented |
| 502 | Bad Gateway |
| 503 | Service Unavailable |
| 504 | Gateway Timeout |
| 505 | HTTP Version Not Supported |

## Response headers

A response header is composed of a name and a value. The name is case-insensitive. The value can be a string or a list of strings.

| Header | Description |
| :----- | :---------- |
| `Allow` | Indicates the set of methods supported by the resource identified by the Request-URI. |
| `Content-Language` | The natural language or languages of the intended audience for the enclosed entity. |
| `Content-Length` | The length of the response body in octets (8-bit bytes). |
| `Content-Location` | An alternate location for the returned data. |
| `Content-Type` | The media type of the entity-body sent to the recipient or, in the case of the HEAD method, the media type that would have been sent had the request been a GET. |
| `Date` | The date and time that the message was sent. |
| `Location` | Used in redirection, or when a new resource has been created. |
| `Retry-After` | If an entity is temporarily unavailable, this instructs the client to try again later. Value could be a specified period of time (in seconds) or a HTTP-date. |
| `Server` | A name for the server. |
| `Transfer-Encoding` | The form of encoding used to safely transfer the entity to the user. Currently defined methods are: chunked, compress, deflate, gzip, identity. |
| `WWW-Authenticate` | Indicates the authentication scheme that should be used to access the requested entity. |

## Response body

A body is optional for all response codes except 1xx, 204 and 304.

## Response examples

| Code | Description |
| :--- | :---------- |
| 200 | The request has succeeded. |
| 201 | The request has been fulfilled and resulted in a new resource being created. |
| 202 | The request has been accepted for processing, but the processing has not been completed. |
| 204 | The server has successfully fulfilled the request and that there is no additional content to send in the response payload body. |
| 301 | The requested resource has been assigned a new permanent URI and any future references to this resource SHOULD use one of the returned URIs. |
| 302 | The requested resource resides temporarily under a different URI. Since the redirection might be altered on occasion, the client SHOULD continue to use the Request-URI for future requests. |
| 304 | Indicates that the resource has not been modified since the version specified by the request headers `If-Modified-Since` or `If-None-Match`. |
| 400 | The server cannot or will not process the request due to an apparent client error. |
| 401 | Similar to 403 Forbidden, but specifically for use when authentication is required and has failed or has not yet been provided. |
| 403 | The request contained valid data and was understood by the server, but the server is refusing action. |
| 404 | The requested resource could not be found but may be available in the future. |
| 405 | A request method is not supported for the requested resource. |
| 406 | The requested resource is capable of generating only content not acceptable according to the Accept headers sent in the request. |
| 408 | The server timed out waiting for the request. |
| 413 | The request is larger than the server is willing or able to process. |
| 414 | The URI provided was too long for the server to process. |
| 415 | The request entity has a media type which the server or resource does not support. |
| 416 | The client has asked for a portion of the file, but the server cannot supply that portion. |
| 417 | The server cannot meet the requirements of the Expect request-header field. |
| 418 | Any attempt to brew coffee with a teapot should result in the error code "418 I'm a teapot". |
| 500 | A generic error message, given when an unexpected condition was encountered and no more specific message is suitable. |
| 501 | The server either does not recognize the request method, or it lacks the ability to fulfill the request. |
| 502 | The server was acting as a gateway or proxy and received an invalid response from the upstream server. |
| 503 | The server is currently unavailable (because it is overloaded or down for maintenance). |
| 504 | The server was acting as a gateway or proxy and did not receive a timely response from the upstream server. |
| 505 | The server does not support the HTTP protocol version used in the request. |

## Handling responses in webserv

// TODO : add response management

[Back to summary](../SUMMARY.md)