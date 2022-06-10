/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murachid <murachid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:56:09 by murachid          #+#    #+#             */
/*   Updated: 2022/06/09 03:53:49 by murachid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <unistd.h>
#include <algorithm>
#include <cstring>
#include <string>
#include <arpa/inet.h>
#include "../config/src/ServerConfig.hpp"
#include "../config/src/ServerRoutes.hpp"
#include "../config/src/Config.hpp"
#include <fcntl.h>
#include "../response/response.hpp"
#include "../request/request.hpp"
# include <sys/time.h>

#define TRUE   1

class ServerRoutes;
class ServerConfig;

class _socket
{
    private: 
	
        int fd;
        int port;
        std::string host;
	socklen_t addrLen;
        int max_fd;
	int opt;
        struct sockaddr_in serverAddr;
	socklen_t clientAddr;
        fd_set struct_fd;
	fd_set struct_read_fd;
	fd_set struct_write_fd;
	std::vector<int> all_fd;
        struct timeval tv;
    public:
        void creat_socket();
        void bind_socket();
        void listen_socket();
        void start_socket();
        void ft_wait();
        void store_fd();
        void ft_accept(int fd_sock);
        void add_conection(int fd_sock);
        void ft_clear(int fd_sock);
        void ft_restart();
        void search(int socket);
        int max(int x, int y);
        int	        GetLengthFileCgiDone(std::string outputfile, int n);
        int             isfiledone(std::string outputfile);
        void	        ft_req_res(std::string file_name, int fd_sock);
        _socket();
        ~_socket();
        
};

#endif