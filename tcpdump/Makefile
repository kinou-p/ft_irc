# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apommier <apommier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/12 01:38:24 by apommier          #+#    #+#              #
#    Updated: 2022/12/16 01:47:58 by apommier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	bash launch_tcpdump.sh
# docker-compose -f ./srcs/docker-compose.yml up --build

fclean:
	-docker rm $$(docker ps -qa)
	-docker rmi -f $$(docker images -qa)
	-docker volume rm $$(docker volume ls -q)
	-docker network rm $$(docker network ls -q)
# up:
# 	docker-compose -f ./srcs/docker-compose.yml up

# back:
# 	docker-compose -f ./srcs/docker-compose.yml up --build -d

# down:
# 	docker-compose -f ./srcs/docker-compose.yml down

re: fclean all