#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <sys/types.h>
# include <sys/stat.h>
# include <cstring>
# include <libgen.h>
# include "../config/src/Config.hpp"
# include "../config/utils.h"
# include "../request/request.hpp"
# include "../CGI/cgi.hpp"

class Request;

class Response
{
	private:
		Request			_req;
		int				_fd_out;
		long long		timestamp;
						Response ( void );
		void			start ( void );
		void			send_file ( void );
		void			output_file ( ServerRoutes const &, ServerConfig const & );

	public:
		int				statusCode;
		int				isAutoindex;
		std::string		responseFile;

						Response ( int &, Request & );
		ServerRoutes	which_route ( ServerConfig, std::string const & );
		void			which_file( ServerConfig const &, ServerRoutes const &, std::string const &, std::string const & );
		std::string		getContentType ( std::string & );
		int				deleteMethod( std::string const & path, std::string const & rootdir );
		int				getLengthFileCgi(std::string outputfile);
};

#endif // !REQUEST_HPP