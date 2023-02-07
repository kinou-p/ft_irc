/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:27:37 by apommier          #+#    #+#             */
/*   Updated: 2023/02/06 15:10:08 by apommier         ###   ########.fr       */
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
#define CMD_NBR 10

//struct functionTab;
void ft_test();

/* ************************************************************************** */
/* *********************************COMMANDS********************************* */
/* ************************************************************************** */

		std::string	PASS();
		std::string	NICK();
		std::string	USER();
		std::string	SERVER();
		std::string	OPER();
		std::string	QUIT();
		std::string	SQUIT();
		std::string	JOIN();
		std::string	PART();
		std::string	MODE();
		std::string	TOPIC();
		std::string	NAMES();
		std::string	LIST();
		std::string	INVITE();
		std::string	KICK();
		std::string	VERSION();
		std::string	STATS();
		std::string	LINKS();
		std::string	TIME();
		std::string	CONNECT();
		std::string	TRACE();
		std::string	ADMIN();
		std::string	INFO();
		std::string	PRIVMSG();
		std::string	NOTICE();
		std::string	WHO();
		std::string	WHOIS();
		std::string	WHOWAS();
		std::string	KILL();
		std::string	PING();
		std::string	PONG();
		std::string	ERROR();
		std::string	AWAY();
		std::string	REHASH();
		std::string	RESTART();
		std::string	SUMMON();
		std::string	USER();
		std::string	OPERWALL();
		std::string	USERHOST();
		std::string	ISON();


/* ************************************************************************** */
/* *****************************COMMAND STRUCT******************************* */
/* ************************************************************************** */

struct functionTab
{
	static const int cmdNbr = 5;
	std::string cmdName[cmdNbr] =
	{
		//4. Détails des messages

			//4.1 Etablissement de connexion
		"PASS",
		"NICK",
		"USER",
		"SERVER",
		"OPER",
		"QUIT",
		"SQUIT",
		
			//4.2 Opérations sur les canaux
		"JOIN",
		"PART",
		"MODE",
		"TOPIC",
		"NAMES",
		"LIST",
		"INVITE",
		"KICK",

			//4.3 Requêtes et commandes des serveurs
		"VERSION",
		"STATS",
		"LINKS",
		"TIME",
		"CONNECT",
		"TRACE",
		"ADMIN",
		"INFO",
		
			//4.4 Envoi de messages
		"PRIVMSG",
		"NOTICE",

			//4.5 Requêtes basées sur les utilisateurs

		"WHO",
		"WHOIS",
		"WHOWAS",
			//4.6 Messages divers
		
		"KILL",
		"PING",
		"PONG",
		"ERROR",
		
		//5. Messages optionnels
		"AWAY",
		"REHASH",
		"RESTART",
		"SUMMON",
		"USER",
		"OPERWALL",
		"USERHOST",
		"ISON"
	};


	void (*cmdPtr[cmdNbr])(void) = 
	{
		//4. Détails des messages

			//4.1 Etablissement de connexion
		PASS,
		NICK,
		USER,
		SERVER,
		OPER,
		QUIT,
		SQUIT,
	
		//4.2 Opérations sur les canaux
		JOIN,
		PART,
		MODE,
		TOPIC,
		NAMES,
		LIST,
		INVITE,
		KICK,

			//4.3 Requêtes et commandes des serveurs
		VERSION,
		STATS,
		LINKS,
		TIME,
		CONNECT,
		TRACE,
		ADMIN,
		INFO,
		
			//4.4 Envoi de messages
		PRIVMSG,
		NOTICE,

			//4.5 Requêtes basées sur les utilisateurs

		WHO,
		WHOIS,
		WHOWAS,
			//4.6 Messages divers
		
		KILL,
		PING,
		PONG,
		ERROR,
		
			//5. Messages optionnels
		AWAY,
		REHASH,
		RESTART,
		SUMMON,
		USER,
		OPERWALL,
		USERHOST,
		ISON
	};
};

/* ************************************************************************** */
/* *********************************STRUCT*********************************** */
/* ************************************************************************** */

struct fdList //allFds in code
{
		int epollFd;
		int serverFd;
		int userList[MAX_EVENTS];
		int nbrUser;
		functionTab parsingTab;
};

struct userClient
{
		// int epollFd;
		// int serverFd;
		// int userList[MAX_EVENTS];
		// int nbrUser;
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
/* *************************CONNECTION AND REQUEST*************************** */
/* ************************************************************************** */

void new_connection(fdList allFds, struct epoll_event newClient);
bool clientRequest(fdList allFds, int newFd);

/* ************************************************************************** */
/* ***************************COMMANDS PARSING******************************* */
/* ************************************************************************** */

void parse_commands(std::string buffer, fdList allFds);

