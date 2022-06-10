#include "Config.hpp"
#include <cstdlib>
#include <sstream>

						Config::Config( void )
{}

Config				&	Config::operator=( Config const & )
{
	return *this;
}

						Config::~Config( void )
{}

std::string	const	&	Config::getFile( void ) const
{
	return this->_file;
}

Config				&	Config::getInstance( void )
{
	static Config	instance;
	return (instance);
}

void					Config::set_config_file( std::string const & file )
{
	Config::getInstance()._file = file;
}

void					Config::check_config_file( void ) // throw( std::string & )
{
	std::ifstream	ifs;
	int			count_s;
	int			count_e;
	int			count_sc;
	int			line_number = 0;
	std::string	line;
	std::stack<int>	braces;
	int			err = 0;

	if ( Config::getInstance().getFile().size() == 0 )
	{
		throw std::string(RED + std::string("") + "Error: No config file specified.\n" + std::string("") + RESET);
	}

	ifs.open(Config::getInstance().getFile());
	if (!ifs.is_open())
	{
		throw std::string(RED + std::string("") + "Error: Cannot open '" + Config::getInstance().getFile() + "'!\n" + std::string("") + RESET);
	}

	while (getline(ifs, line))
	{
		line = w_trim(line);

		/* IGNORE COMMENTS */
		if (line.size() != 0 && line[0] == '#')
		{
			line_number++;
			continue;
		}
		/* IGNORE COMMENTS */

		// TO REVISE
		std::string::difference_type str_diff = 0;
		count_s = count(line.begin(), line.end(), '{');
		count_e = count(line.begin(), line.end(), '}');
		count_sc = count(line.begin(), line.end(), ';');

		count_s = count_s == str_diff ? -1 : count_s;
		count_e = count_e == str_diff ? -1 : count_e;
		count_sc = count_sc == str_diff ? -1 : count_sc;

		/*	ONE BRACE PER LINE	*/
		if (
			(count_s > 1) ||
			(count_e > 1) ||
			(count_s > 0 && count_e > 0)
			)
		{
			ifs.close();
			Config::line_error("Each brace should be in a seperate line.", line, line_number);
		}
		/*	ONE BRACE PER LINE	*/

		/*	NO LONELY BRACES	*/
		if (count_e > 0 && braces.size() == 0)
		{
			ifs.close();
			Config::line_error("Too many closing braces.", line, line_number);
		}
		/*	NO LONELY BRACES	*/

		/*	NO SEMICOLON + BRACES	*/
		if (count_sc > 0 &&
			(count_sc > 1 || count_s > 0 || count_e > 0))
		{
			ifs.close();
			Config::line_error("Unexpected character.", line, line_number);
		}
		/*	NO SEMICOLON + BRACES	*/

		/*	LINE SHOULD END WITH A BRACE OR A SEMICOLON	*/
		if (line.length() > 0 &&
			(
				line[line.length() - 1] != ';' &&
				line[line.length() - 1] != '{' &&
				line[line.length() - 1] != '}')
			)
		{
			ifs.close();
			Config::line_error("Line should end with a brace or a semicolon.", line, line_number);
		}
		/*	LINE SHOULD END WITH A BRACE OR A SEMICOLON	*/

		if (count_s > 0)
		{
			/*	THREE NESTED BRACES	*/
			if (braces.size() >= 2)
			{
				ifs.close();
				Config::line_error("Too many nested braces.", line, line_number);
			}
			/*	THREE NESTED BRACES	*/

			/*	CHARS BESIDE BRACE	*/
			if ( line.size() > 1 )
			{
				ifs.close();
				Config::line_error("Unexpected character.", line, line_number);
			}
			/*	CHARS BESIDE BRACE	*/

			braces.push(line_number);
		}

		if (count_e > 0)
		{
			/*	CHARS BESIDE BRACE	*/
			if ( line.size() > 1 )
			{
				ifs.close();
				Config::line_error("Unexpected character.", line, line_number);
			}
			/*	CHARS BESIDE BRACE	*/

			braces.pop();
		}
		line_number++;
	}

	/*	NO LONELY BRACES	*/
	if (err == 0 && braces.size() > 0)
	{
		ifs.close();
		std::stringstream ss;
		ss << RED;
		ss << "Error: " << "Too many opening braces." << std::endl;
		ss << "Missing closing brace of line " << braces.top() + 1 << std::endl;
		ss << RESET;
		throw ss.str();
	}
	/*	NO LONELY BRACES	*/

	ifs.close();
}

void					Config::parse_config( void ) // throw( std::string & )
{
	std::ifstream	ifs;
	int				count_eq;
	int				level = 0;
	int				line_number = 0;
	int				server_number = 0;
	int				routes_number = 0;
	std::string		line;
	ServerConfig	server_config;
	ServerRoutes	server_route;

	if ( Config::getInstance().getFile().size() == 0 )
	{
		throw std::string(RED + std::string("") + "Error: No config file specified.\n" + std::string("") + RESET);
	}

	ifs.open(Config::getInstance().getFile());
	if (!ifs.is_open())
	{
		throw std::string(RED + std::string("") + "Error: Cannot open '" + Config::getInstance().getFile() + "'!\n" + std::string("") + RESET);
	}

	while (getline(ifs, line))
	{
		line = w_trim( line );

		/* IGNORE COMMENTS */
		if (line.size() != 0 && line[0] == '#')
		{
			line_number++;
			continue;
		}
		/* IGNORE COMMENTS */

		/*	BEGIN SERVER OR ROUTE	*/
		if ( line == "{" )
		{
			level++;
			// server bloc
			if ( level == 1 )
			{
				// create Server Config
				server_config = ServerConfig();
				// 
				routes_number = 0;
				server_number++;
			}
			// route bloc
			else if ( level == 2 )
			{
				// create Server Routes
				server_route = ServerRoutes();
				// .
				routes_number++;
			}
		}
		/*	BEGIN SERVER OR ROUTE	*/

		/*	SAVE SERVER OR ROUTE	*/
		else if ( line == "}" )
		{
			// Save server settings
			if ( level == 1 )
			{
				// push server config
				if ( server_config.getPort() == -1 )
				{
					throw(RED + std::string("Invalid configuration. Port is required for each server.\n") + RESET);
				}
				if ( server_config.getHost() == "" )
				{
					throw(RED + std::string("Invalid configuration. Host is required for each server.\n") + RESET);
				}
				// no routes required
				// if ( server_config.getRouteCount() == 0)
				// {
				// 	throw(RED + std::string("Invalid configuration. At least on route is required for each server.\n") + RESET);
				// }

				for ( int i = 0; i < server_config.getRouteCount(); i++ )
				{
					if ( server_config.getRoute(i).getRoute() == "/" )
					{
						break;
					}
					if (i == server_config.getRouteCount() - 1)
					{
						server_config.addRoute(ServerRoutes());
					}
				}

				Config::getInstance().addServer( server_config );
			}
			// Append Routes to server
			if ( level == 2 )
			{
				if ( server_route.getRoot() == "" )
				{
					throw(RED + std::string("Invalid configuration. Root path should be specified for each server.\n") + RESET);
				}
				// push Server Routes
				server_config.addRoute( server_route );
			}
			level--;
		}
		/*	SAVE SERVER OR ROUTE	*/

		/*	HANDLE SETTINGS	*/
		else if ( line.size() > 0 )
		{
			count_eq = 0;
			for (unsigned int i = 0; i < line.size(); i++)
			{
				if (line[i] == '=')
				{
					count_eq++;
				}
			}

			if (count_eq != 1)
			{
				ifs.close();
				Config::line_error("Invalid syntax. Ex [key]=[value];", line, line_number);
			}

			std::string key = line.substr(0, line.find('='));
			std::string value = line.substr(line.find('=') + 1);
			// remove semicolon
			value.resize( value.size() - 1 );

			if (value.size() == 0)
			{
				ifs.close();
				Config::line_error("Invalid syntax. Ex [key]=[value];", line, line_number);
			}

			// server bloc
			if ( level == 1 )
			{
				// get server host
				if (key == "host")
				{
					server_config.setHost(value);
				}
				// get server port
				else if (key == "port")
				{
					// int
					// 1 - 65535
					int port = atoi(value.c_str());
					if ( port <= 0 || port > 65535 )
					{
						ifs.close();
						Config::line_error("Invalid port number. Port number must be between 1 and 65535.", line, line_number);
					}
					server_config.setPort(port);
				}
				// get server name
				else if (key == "server_name")
				{
					server_config.setName(value);
				}
				else if (key == "limit_body_size")
				{
					// int
					if ( !isdigit(value[0]) )
					{
						Config::line_error("Invalid Syntax. Body size limit should be a positive number.", line, line_number);
					}
					server_config.setBodySizeLimit(atoi(value.c_str()));
				}
				else if (key == "error_204")
				{
					if (!file_exists(value) || hasAccess(value) == -1)
					{
						Config::line_error("Invalid Syntax. Error page for code 204 should be a valid file path.", line, line_number);
					}
					server_config.set204Page(value);
				}
				else if (key == "error_400")
				{
					if (!file_exists(value) || hasAccess(value) == -1)
					{
						Config::line_error("Invalid Syntax. Error page for code 400 should be a valid file path.", line, line_number);
					}
					server_config.set400Page(value);
				}
				else if (key == "error_403")
				{
					if (!file_exists(value) || hasAccess(value) == -1)
					{
						Config::line_error("Invalid Syntax. Error page for code 403 should be a valid file path.", line, line_number);
					}
					server_config.set403Page(value);
				}
				else if (key == "error_404")
				{
					if (!file_exists(value) || hasAccess(value) == -1)
					{
						Config::line_error("Invalid Syntax. Error page for code 404 should be a valid file path.", line, line_number);
					}
					server_config.set404Page(value);
				}
				else if (key == "error_405")
				{
					if (!file_exists(value) || hasAccess(value) == -1)
					{
						Config::line_error("Invalid Syntax. Error page for code 405 should be a valid file path.", line, line_number);
					}
					server_config.set405Page(value);
				}
				else if (key == "error_406")
				{
					if (!file_exists(value) || hasAccess(value) == -1)
					{
						Config::line_error("Invalid Syntax. Error page for code 406 should be a valid file path.", line, line_number);
					}
					server_config.set406Page(value);
				}
				else if (key == "error_413")
				{
					if (!file_exists(value) || hasAccess(value) == -1)
					{
						Config::line_error("Invalid Syntax. Error page for code 413 should be a valid file path.", line, line_number);
					}
					server_config.set413Page(value);
				}
				else if (key == "error_500")
				{
					if (!file_exists(value) || hasAccess(value) == -1)
					{
						Config::line_error("Invalid Syntax. Error page for code 500 should be a valid file path.", line, line_number);
					}
					server_config.set500Page(value);
				}
				else if (key == "error_502")
				{
					if (!file_exists(value) || hasAccess(value) == -1)
					{
						Config::line_error("Invalid Syntax. Error page for code 502 should be a valid file path.", line, line_number);
					}
					server_config.set502Page(value);
				}
				else
				{
					// wrong key
					ifs.close();
					Config::line_error("Invalid key: '" + key + "'.", line, line_number);
				}
			}
			else if ( level == 2 )
			{
				if (key == "allow")
				{
					if ( value != "GET" && value != "POST" && value != "DELETE" )
					{
						ifs.close();
						Config::line_error("Invalid method: '" + value + "'.", line, line_number);
					}
					server_route.addMethod(value);
				}
				else if (key == "php_cgi")
				{
					server_route.setPhpCgi(value);
				}
				else if (key == "dir_listing")
				{
					if (value == "on")
						server_route.setDirListing(true);
					else if (value == "off")
						server_route.setDirListing(false);
					else
						throw std::string(RED + std::string("") + "Error: Invalid value for dir_listing.\n" + std::string("") + RESET);
				}
				else if (key == "index")
				{
					if ( value.find('.') == std::string::npos )
					{
						ifs.close();
						Config::line_error("Invalid value for index. Ex: [filename].[ext]", line, line_number);
					}
					server_route.addIndex(value);
				}
				else if (key == "redirection_code")
				{
					if ( !isdigit(value[0]) )
					{
						throw(RED + std::string("") + "Invalid Syntax. Redirection code should be a positive number!\n" + std::string("") + RESET);
					}
					server_route.setRedirectionCode(atoi(value.c_str()));
					if ( server_route.getRedirectionCode() != 301 && server_route.getRedirectionCode() != 302 )
					{
						throw(RED + std::string("") + "Invalid Syntax. Redirection code should be either 301 and 302!\n" + std::string("") + RESET);
					}
				}
				else if (key == "redirection_url")
				{
					server_route.setRedirectionUrl(value);
				}
				else if (key == "upload_dir")
				{
					if (!directory_exists(value) || hasAccess(value) == -1)
					{
						ifs.close();
						Config::line_error("Invalid directory: '" + value + "'.", line, line_number);
					}
					server_route.setUploadDir(value);
				}
				else if (key == "root")
				{
					if (!directory_exists(value) || hasAccess(value) == -1)
					{
						ifs.close();
						Config::line_error("Invalid directory: '" + value + "'.", line, line_number);
					}
					if ( value.size() > 1 && value[-1] == '/' )
						value.substr(0, value.size() - 1);
					server_route.setRoot(value);
				}
				else if (key == "route")
				{
					server_route.setRoute(value);
				}
				else
				{
					// wrong key
					ifs.close();
					Config::line_error("Invalid key: '" + key + "'.", line, line_number);
				}
			}
		}
		/*	HANDLE SETTINGS	*/

		line_number++;
	}
	Config::getInstance().validate_config();
}

void Config::validate_config( void ) // throw( std::string & )
{
	std::vector< ServerConfig > server_configs = Config::getInstance().getServers();
	// check for duplicate server
	for (unsigned long i = 0; i < server_configs.size(); i++)
	{
		for (unsigned long j = i + 1; j < server_configs.size(); j++)
		{
			if ( server_configs[i].getHost() == server_configs[j].getHost() &&
				server_configs[i].getPort() == server_configs[j].getPort() &&
				server_configs[i].getName() == server_configs[j].getName() )
			{
				throw std::string(RED + std::string("") + "Error: Duplicate server configuration.\n" + std::string("") + RESET);
			}
		}
	}
	if ( server_configs.size() == 0 )
	{
		throw std::string(RED + std::string("") + "Error: No server configuration found.\n" + std::string("") + RESET);
	}
}

std::vector< ServerConfig > const &	Config::getServers( void ) const
{
	return (this->_servers);
}

ServerConfig const &	Config::getServer( int i ) const // throw( std::string & )
{
	if ( i >= 0 && i < Config::getInstance().getServerCount() )
	{
		return (Config::getInstance().getServers()[i]);
	}
	throw std::string(RED + std::string("") + "Error: Server index out of range.\n" + std::string("") + RESET);
}

ServerConfig const &	Config::getServer( std::string const & host, int const & port ) const
{
	ServerConfig	srvr;
	for ( int i = 0; i < Config::getInstance().getServerCount(); i++ )
	{
		srvr = Config::getInstance().getServer(i);
		if (
			srvr.getHost() == host &&
			srvr.getPort() == port
		)
		{
			return (Config::getInstance().getServer(i));
		}
	}
	return this->getServerName( host, port );
}

ServerConfig const &	Config::getServerName( std::string const & host, int const & port ) const
{
	ServerConfig	srvr;
	for ( int i = 0; i < Config::getInstance().getServerCount(); i++ )
	{
		srvr = Config::getInstance().getServer(i);
		if (
			srvr.getName() == host &&
			srvr.getPort() == port
		)
		{
			return (Config::getInstance().getServer(i));
		}
	}
	return this->getServer( 0 );
}

int						Config::getServerCount( void ) const
{
	return (Config::getInstance().getServers().size());
}

void					Config::addServer( ServerConfig const server_config )
{
	this->_servers.push_back( server_config );
}

void					Config::line_error(std::string const & msg, std::string const & line, int const line_number) const // throw( std::string & );
{
	std::stringstream ss;
	ss << RED;
	ss << "Error: " << msg << std::endl;
	ss << "line " << line_number + 1 << ": " << line << std::endl;
	ss << RESET;
	throw ss.str();
}