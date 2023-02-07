# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apommier <apommier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/01 17:27:29 by apommier          #+#    #+#              #
#    Updated: 2023/02/07 14:47:20 by apommier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
SRCS := main.cpp\
		epoll.cpp\
		start_server.cpp\
		utils.cpp\
		client_request.cpp\
		new_connection.cpp\
		server_loop.cpp\
		commands/parse_commands.cpp\
		commands/auth/nick.cpp\
		commands/auth/pass.cpp\
		commands/auth/user.cpp\
		commands/auth/utils.cpp

CC 			= c++
FLAGS 		= -g 
#-Wall -Wextra -Werror
DIR_OBJ     := obj
DIR_INC		= -I ./includes/
DIR_SRCS    := ./srcs
OBJS        := ${addprefix ${DIR_OBJ}/, ${SRCS:.cpp=.o}}
DEPS        =  ${OBJS:.o=.d}
RM			= rm -rf

all: ${NAME}

-include ${DEPS}

${DIR_OBJ}/%.o:	${DIR_SRCS}/%.cpp
	mkdir -p ${dir $@}
	${CC} ${FLAGS} ${DIR_INC} -o $@ -c $< -MMD

${NAME}: ${OBJS}
		${CC} ${FLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${DIR_OBJ}

fclean:	clean
		@${RM} ${NAME}

re: 	fclean all

.PHONY: all clean fclean re