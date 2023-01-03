#include "../inc/webserv.hpp"

int main(int argc, char **argv, char **envp)
{
    Config config;

	(void)envp;
	if (argc > 1)
		std::cout << argv[1] << std::endl;
    config.parseConf(static_cast<std::string>(argv[1]));
	return (0);
}