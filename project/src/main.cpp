#include "../inc/webserv.hpp"

int main(int argc, char **argv, char **envp)
{

	(void)envp;
	if (argc > 1)
		std::cout << argv[1] << std::endl;
    ConfFile file(static_cast<std::string>(argv[1]));
    const std::vector<std::string> lines = file.getLines();
    for (std::vector<std::string>::const_iterator it = lines.cbegin(); it != lines.cend(); it++) {
        std::cout << *it << std::endl;
    }
	return (0);
}