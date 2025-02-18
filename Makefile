# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apommier <apommier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/01 17:27:29 by apommier          #+#    #+#              #
#    Updated: 2023/03/13 02:21:45 by apommier         ###   ########.fr        #
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
		delete_user.cpp\
\
		commands/cmd_utils.cpp\
		commands/parse_commands.cpp\
\
		commands/auth/nick.cpp\
		commands/auth/pass.cpp\
		commands/auth/user.cpp\
		commands/auth/auth_utils.cpp\
		commands/auth/connect_client.cpp\
\
		commands/channel/channel_utils.cpp\
		commands/channel/join.cpp\
		commands/channel/privmsg.cpp\
		commands/channel/notice.cpp\
		commands/channel/part.cpp\
		commands/channel/list.cpp\
\
		commands/other/quit.cpp\
		commands/other/ping_pong.cpp\
		commands/other/who.cpp\
		commands/other/names.cpp\
\
		commands/channel_op/invite.cpp\
		commands/channel_op/kick.cpp\
		commands/channel_op/mode.cpp\
		commands/channel_op/utils_mode.cpp\
		commands/channel_op/topic.cpp\
\
		commands/operator/squit.cpp\
		commands/operator/oper.cpp\
		commands/operator/kill.cpp\
		commands/operator/wallops.cpp\
\
		commands/not_done_cmd.cpp #special (temporary)

CC 			= c++
FLAGS 		= -g  
FLAGS2 		= -Wall -Wextra -Werror -std=c++98
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
	${CC} ${FLAGS} ${FLAGS2} ${DIR_INC} -o $@ -c $< -MMD

${NAME}: ${OBJS}
		${CC} ${FLAGS} ${FLAGS2} ${OBJS} -o ${NAME}

clean:
	${RM} ${DIR_OBJ}

fclean:	clean
		@${RM} ${NAME}

re: 	fclean all

.PHONY: all clean fclean re