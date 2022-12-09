/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:27:37 by apommier          #+#    #+#             */
/*   Updated: 2022/12/09 23:18:30 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h> //socket function
#include <cstdlib> 
#include <cstring> //std::string
#include <cerrno> //errno
#include <iostream> //std::cout | cerr
#include <netinet/in.h> //struct socket
#include <sys/epoll.h> //epoll ensemble
#include <unistd.h> //close()

#define MAX_EVENTS 5
#define READ_SIZE 10

struct fdList
{
		int epollFd;
		int serverFd;
		int userList[MAX_EVENTS];
		int nbrUser;
};

/* ************************************************************************** */
/* *********************************UTILS************************************ */
/* ************************************************************************** */

void ft_error(std::string str);
void close_fd(int fd);

/* ************************************************************************** */
/* ******************************START SERVER******************************** */
/* ************************************************************************** */

void initialize(char **av);									//1st
void start_loop(fdList allFds);								//3rd

/* ************************************************************************** */
/* *****************************EPOLL UTILITY******************************** */
/* ************************************************************************** */

void epoll_add(int epollFd, int fd);
int epoll_start();											//2nd

/* ************************************************************************** */
/* *****************************EPOLL UTILITY******************************** */
/* ************************************************************************** */

void new_connection(struct epoll_event newClient);
bool clientRequest(fdList allFds, int newFd);