#include "socket/socket.hpp"
#include "response/response.hpp"
#include "config/src/Config.hpp"

int		main( int ac, char **av )
{
	std::string		conf_file;

	if (ac == 2)
	{
		conf_file = av[1];

		try
		{
			signal(SIGPIPE, SIG_IGN);
			Config::getInstance().set_config_file(conf_file);
			Config::getInstance().check_config_file();
			Config::getInstance().parse_config();
			_socket socket;
		}
		catch (const std::string & e)
		{
			std::cout << e;
		}
		catch(const char * e)
		{
			std::cerr << e << '\n';
		}
	}
	else
		std::cout << "Usage: ./server [config_file]" << std::endl;
	return (0);
}