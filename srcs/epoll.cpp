/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoll.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:38:30 by apommier          #+#    #+#             */
/*   Updated: 2023/02/22 12:59:31 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void epoll_add(int epollFd, int fd)
{	
	struct epoll_event event;
	memset(&event, 0, sizeof(event));
	event.events = EPOLLIN;
	event.data.fd = fd;

	if (epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &event))
		ft_error("epoll_ctl() error");
}

int epoll_start()
{
	int epollFd;

	epollFd = epoll_create(5);
	if (epollFd == -1)
		ft_error("epoll_create() error");
	return (epollFd);
}