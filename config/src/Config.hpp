#ifndef CONFIG_HPP
# define CONFIG_HPP

// string
# include <string>
// cout
# include <iostream>
// exception
# include <exception>
// ifstream
# include <fstream>

# include "ServerConfig.hpp"
# include "../utils.h"

class Config
{
	private:
		std::string					_file;
		std::vector< ServerConfig >	_servers;
		/**
		 * @brief Construct a new Config object
		 * 
		 * Use Config::getInstance() instead.
		 */
		Config( void );

	public:

		/**
		 * @brief 
		 * 
		 * @param src Config const & - The Config object to copy
		 * @return Config & 
		 */
		Config &				operator=( Config const & ); //

		/**
		 * @brief Destroy the Config object
		 * 
		 */
		~Config( void );

		/**
		 * @brief Get the File object
		 * 
		 * @return std::string const & 
		 */
		std::string const &		getFile( void ) const;

		/**
		 * @brief Get the Instance object
		 * 
		 * @return Config & 
		 */
		Config static &			getInstance( void );

		/**
		 * @brief Set the config file object
		 * 
		 * @param file std::string const & - path to the config file
		 */
		void					set_config_file( std::string const & file );

		/**
		 * @brief 
		 * 
		 */
		void					check_config_file( void ); // throw( std::string & );

		/**
		 * @brief Parse the config file object
		 * 
		 */
		void					parse_config( void ); // throw( std::string & );

		/**
		 * @brief 
		 * 
		 */
		void					validate_config( void ); // throw( std::string & );

		/**
		 * @brief Get the Servers object
		 * 
		 * @return vector< ServerConfig > const & 
		 */
		std::vector< ServerConfig > const &	getServers( void ) const;

		/**
		 * @brief Get the Server object
		 * 
		 * @param index int - index of the server
		 * @return ServerConfig const & 
		 */
		ServerConfig const &	getServer( int index ) const; // throw( std::string & );
		ServerConfig const &	getServer( std::string const &, int const & ) const;
		ServerConfig const &	getServerName( std::string const &, int const & ) const;

		int						getServerCount( void ) const;

		/**
		 * @brief Add a server to the config file
		 * 
		 * @param server 
		 */
		void					addServer( ServerConfig const );

		void					line_error(std::string const &, std::string const &, int const) const; // throw( std::string & );

};

#endif