#ifndef SERVERROUTES_HPP
# define SERVERROUTES_HPP

# include <string>
# include <vector>

class ServerRoutes
{
	private:
		std::string					_phpcgi;
		bool						_dir_list;
		std::vector<std::string>	_indexes;
		std::vector<std::string>	_methods;
		int							_redirection_code;
		std::string					_redirection_url;
		std::string					_root;
		std::string					_route;
		std::string					_upload_dir;

	public:
						ServerRoutes( void );
						ServerRoutes( ServerRoutes const & );
		ServerRoutes &	operator=( ServerRoutes const & );
						~ServerRoutes( void );

		int							getRedirectionCode( void ) const;
		std::string					getRedirectionUrl( void ) const;
		std::string					getRoute( void ) const;
		std::string					getRoot( void ) const;
		bool						getDirListing( void ) const;
		std::vector<std::string>	getIndexes( void ) const;
		std::string					getPhpCgi( void ) const;
		std::vector<std::string>	getAllMethods( void ) const;
		int							getMethodsCount( void ) const;
		bool						isMethodAllowed( std::string const & ) const;
		std::string					getUploadDir( void ) const;

		void						setRedirectionCode( int const & );
		void						setRedirectionUrl( std::string const & );
		void						setRoute( std::string const & );
		void						setRoot( std::string const & );
		void						setDirListing( bool );
		void						addIndex( std::string const & );
		void						setPhpCgi( std::string const & );
		bool						addMethod( std::string const & );
		void						setUploadDir( std::string const & );
};

#endif