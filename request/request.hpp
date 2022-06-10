#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string> 
# include <iostream>
# include <fstream>
# include <sstream>
#include <dirent.h>
#include "../config/utils.h"

class Request
{
    public:
        int 		fd;                 // ok
		std::string PathOfReq; 			// ok
		std::string method; 			// ok
		std::string RequestFile; 		// ok
		std::string QueryString; 		// ok
		std::string host; 				// ok
		std::string port; 				// ok
		std::string Content_type; 		// ok
		std::string Connection; 		// ok
		int			Content_length;		// ok
		bool 		IsPhpFile;    		// ok
		bool 		IsReqBody;    		// ok
		std::string ROOTDIR;
		bool 		AutoindexOn;
		std::string indexfile;
		std::string body_content;
		std::string path_info;


        Request(void);
        Request(std::string req_path, int _fd);
        // ~Request();
        // Request();
        void		start_parsing(void);
        void		parse_firstline(std::string fline);
        void		getHost_Port(std::string line);
        std::string	ParseHeaderReq(std::string lines);
        void		getvalue(std::string line);
        void		PrepareMsgBody(std::string line);
		void		GetStatusCODE(void);

		void printAll(void)
		{
			std::cout << "PathOfReq 	= "  << PathOfReq 		<< std::endl; 		
			std::cout << "method 		= "  << method 			<< std::endl; 		
			std::cout << "RequestFile 	= "  << RequestFile 	<< std::endl; 	
			std::cout << "QueryString 	= "  << QueryString 	<< std::endl; 	
			std::cout << "host 		= "  << host 			<< std::endl; 			
			std::cout << "Content_type 	= "  << Content_type 	<< std::endl; 	
			std::cout << "Content_length  = "  << Content_length << std::endl;	
			std::cout << "IsPhpFile 	= "  << IsPhpFile 		<< std::endl;    	
			std::cout << "IsReqBody 	= "  << IsReqBody 		<< std::endl;    	
			std::cout << "Connection 	= "  << Connection 		<< std::endl;    	
			std::cout << "port 	= "  << port 		<< std::endl;    	
			std::cout << "fd 	= "  << fd 		<< std::endl;    	
			std::cout << "ROOTDIR 	= "  << ROOTDIR 		<< std::endl;    	
		}
};

#endif // !REQUEST_HPP