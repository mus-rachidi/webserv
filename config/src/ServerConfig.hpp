#ifndef SERVERCONFIG_HPP
# define SERVERCONFIG_HPP

# include <vector>
# include <iostream>

# include "ServerRoutes.hpp"
# include "../utils.h"

class ServerConfig
{
	private:
		long long					_body_size_limit;
		std::string					_host;
		std::string					_name;
		int							_port;
		std::vector< ServerRoutes >	_routes;
		std::string					_error_204;
		std::string					_error_400;
		std::string					_error_403;
		std::string					_error_404;
		std::string					_error_405;
		std::string					_error_406;
		std::string					_error_413;
		std::string					_error_500;
		std::string					_error_502;

	public:
									ServerConfig( void );
									ServerConfig( ServerConfig const & );
		ServerConfig &				operator=( ServerConfig const & );
									~ServerConfig( void );

		std::string					getHost( void ) const;
		int							getPort( void ) const;
		long long					getBodySizeLimit( void ) const;
		std::string					getName( void ) const;
		std::vector< std::string >	getErrorPages( void ) const;
		ServerRoutes				getRootRoute( void ) const; // throw( std::string & )
		ServerRoutes				getRoute( int const & ) const; // throw( std::string & );
		ServerRoutes				getRoute( std::string ) const; // throw( std::string & );
		std::vector< ServerRoutes >		getRoutes( void ) const;
		int							getRouteCount( void ) const;

		void						setHost( std::string const & );
		void						setPort( int const & );
		void						setBodySizeLimit( long long const & );
		void						setName( std::string const & );
		void						addErrorPage( std::string const & );
		void						addRoute( ServerRoutes const & );


		std::string					get204Page( void ) const;
		void						set204Page( std::string const & );
		std::string					get400Page( void ) const;
		void						set400Page( std::string const & );
		std::string					get403Page( void ) const;
		void						set403Page( std::string const & );
		std::string					get404Page( void ) const;
		void						set404Page( std::string const & );
		std::string					get406Page( void ) const;
		void						set406Page( std::string const & );
		std::string					get405Page( void ) const;
		void						set405Page( std::string const & );
		std::string					get413Page( void ) const;
		void						set413Page( std::string const & );
		std::string					get500Page( void ) const;
		void						set500Page( std::string const & );
		std::string					get502Page( void ) const;
		void						set502Page( std::string const & );
};

#endif