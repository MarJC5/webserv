#include "../inc/webserv.hpp"

int main(int argc, char **argv, char **envp)
{

    Config config;
    std::map<std::string, Location*> locations;

	(void)envp;
	if (argc > 1)
		std::cout << argv[1] << std::endl;
	
	config.parseConf(static_cast<std::string>(argv[1]));
	Loop test(config.getServer());
	test.loop();
	return (0);
}