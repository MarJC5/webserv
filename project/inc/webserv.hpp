#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#ifndef VERBOSE
	// Add verbose flag at compile time
	// 0 = no verbose
	// 1 = verbose
	// 2 = verbose + debug
	#define VERBOSE 0
#endif

inline char **GLOBAL_ENVP;

#include <iostream>
#include "Loop.hpp"
#include "Server.hpp"
#include "ConfFile.hpp"
#include "Config.hpp"

#include "HttpException.hpp"
#include "HttpParser.hpp"

#endif
