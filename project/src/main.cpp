#include "../inc/webserv.hpp"

int main(int argc, char **argv, char **envp)
{

    Config config;
    std::map<std::string, Location*> locations;

	(void)envp;
	if (argc > 1)
		std::cout << argv[1] << std::endl;
    config.parseConf(static_cast<std::string>(argv[1]));
    for (std::vector<Server*>::const_iterator it = config.getServer().begin(); it < config.getServer().end() ; ++it) {
        std::cout << (*it)->getName() << std::endl;
        std::cout << (*it)->getIp() << std::endl;
        std::cout << (*it)->getPort() << std::endl;
        locations = (*it)->getLocations();
        std::cout << (locations["/"]->getIndex()) << std::endl;
        std::cout << (locations["/"]->getRoot()) << std::endl;
        std::cout << (locations["/"]->getCgiBin()) << std::endl;
        std::cout << (locations["/"]->getDirListing()) << std::endl;
        std::cout << (locations["/"]->getMaxBody()) << std::endl;
        std::cout << (locations["/"]->getUploadDir()) << std::endl;

    }
	return (0);
}