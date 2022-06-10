# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: murachid <murachid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 17:18:51 by murachid          #+#    #+#              #
#    Updated: 2022/06/09 02:32:48 by murachid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	webserv
CC		=	c++
CFLAGS	=	-std=c++98
EFLAGS	=	-Wall -Wextra -Werror
SRC		=	main.cpp socket/socket.cpp

REQSRCS		=	request/request.cpp \
			CGI/cgi.cpp
REQHSRCS	=	request/request.hpp \
			CGI/cgi.hpp

PARSESRCS	=	config/utils.cpp \
				config/src/Config.cpp \
				config/src/ServerConfig.cpp \
				config/src/ServerRoutes.cpp \
				response/response.cpp
PARSEHSRCS	=	config/utils.h \
				config/src/Config.hpp \
				config/src/ServerConfig.hpp \
				config/src/ServerRoutes.hpp \
				response/response.hpp

all : $(NAME)

$(NAME)		:	$(SRC) $(PARSESRCS) $(PARSEHSRCS) $(REQSRCS) $(REQHSRCS)
	@$(CC) $(CFLAGS) $(EFLAGS) $(PARSESRCS) $(REQSRCS) $(SRC) -o $(NAME)
	
clean		:
	@rm -rf $(NAME)

fclean		:	clean
	@rm -rf $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re