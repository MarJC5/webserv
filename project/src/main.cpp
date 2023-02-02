#include "../inc/webserv.hpp"

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main(int argc, char **argv, char **envp)
{
    Config config;
    std::map<std::string, Location*> locations;

	if (argc > 1)
		std::cout << argv[1] << std::endl;

	config.parseConf(static_cast<std::string>(argv[1]));
	Loop looper(config.getServer());
	looper.loop();
	return (0);
}