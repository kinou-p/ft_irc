/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_tab.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:55:52 by apommier          #+#    #+#             */
/*   Updated: 2023/02/10 09:59:21 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./ft_irc.hpp"

struct fdList;

/* ************************************************************************** */
/* *********************************COMMANDS********************************* */
/* ************************************************************************** */

		void	PASS(std::string buffer, fdList &allFds, int userNbr);
		void	NICK(std::string buffer, fdList &allFds, int userNbr);
		void	USER(std::string buffer, fdList &allFds, int userNbr);
		void	SERVER(std::string buffer, fdList &allFds, int userNbr);
		void	OPER(std::string buffer, fdList &allFds, int userNbr);
		void	QUIT(std::string buffer, fdList &allFds, int userNbr);
		void	SQUIT(std::string buffer, fdList &allFds, int userNbr);
		void	JOIN(std::string buffer, fdList &allFds, int userNbr);
		void	PART(std::string buffer, fdList &allFds, int userNbr);
		void	MODE(std::string buffer, fdList &allFds, int userNbr);
		void	TOPIC(std::string buffer, fdList &allFds, int userNbr);
		void	NAMES(std::string buffer, fdList &allFds, int userNbr);
		void	LIST(std::string buffer, fdList &allFds, int userNbr);
		void	INVITE(std::string buffer, fdList &allFds, int userNbr);
		void	KICK(std::string buffer, fdList &allFds, int userNbr);
		void	VERSION(std::string buffer, fdList &allFds, int userNbr);
		void	STATS(std::string buffer, fdList &allFds, int userNbr);
		void	LINKS(std::string buffer, fdList &allFds, int userNbr);
		void	TIME(std::string buffer, fdList &allFds, int userNbr);
		void	CONNECT(std::string buffer, fdList &allFds, int userNbr);
		void	TRACE(std::string buffer, fdList &allFds, int userNbr);
		void	ADMIN(std::string buffer, fdList &allFds, int userNbr);
		void	INFO(std::string buffer, fdList &allFds, int userNbr);
		void	PRIVMSG(std::string buffer, fdList &allFds, int userNbr);
		void	NOTICE(std::string buffer, fdList &allFds, int userNbr);
		void	WHO(std::string buffer, fdList &allFds, int userNbr);
		void	WHOIS(std::string buffer, fdList &allFds, int userNbr);
		void	WHOWAS(std::string buffer, fdList &allFds, int userNbr);
		void	KILL(std::string buffer, fdList &allFds, int userNbr);
		void	PING(std::string buffer, fdList &allFds, int userNbr);
		void	PONG(std::string buffer, fdList &allFds, int userNbr);
		void	ERROR(std::string buffer, fdList &allFds, int userNbr);
		void	AWAY(std::string buffer, fdList &allFds, int userNbr);
		void	REHASH(std::string buffer, fdList &allFds, int userNbr);
		void	RESTART(std::string buffer, fdList &allFds, int userNbr);
		void	SUMMON(std::string buffer, fdList &allFds, int userNbr);
		void	USER(std::string buffer, fdList &allFds, int userNbr);
		void	OPERWALL(std::string buffer, fdList &allFds, int userNbr);
		void	USERHOST(std::string buffer, fdList &allFds, int userNbr);
		void	ISON(std::string buffer, fdList &allFds, int userNbr);


struct functionTab
{
	static const int cmdNbr = 40;

	std::vector<std::string>cmdName;
	//std::vector<(void *)(std::string buffer, fdList &allFds, int userNbr);
	std::vector<void (*)(std::string buffer, fdList &allFds, int userNbr)>cmdPtr;
	functionTab()
	{

//4.1 Etablissement de connexion
	cmdName.push_back("PASS");
	cmdName.push_back("NICK");
	cmdName.push_back("USER");
	cmdName.push_back("SERVER");
	cmdName.push_back("OPER");
	cmdName.push_back("QUIT");
	cmdName.push_back("SQUIT");

//4.2 Opérations sur les canaux
	cmdName.push_back("JOIN");
	cmdName.push_back("PART");
	cmdName.push_back("MODE");
	cmdName.push_back("TOPIC");
	cmdName.push_back("NAMES");
	cmdName.push_back("LIST");
	cmdName.push_back("INVITE");
	cmdName.push_back("KICK");

//4.3 Requêtes et commandes des serveurs
	cmdName.push_back("VERSION");
	cmdName.push_back("STATS");
	cmdName.push_back("LINKS");
	cmdName.push_back("TIME");
	cmdName.push_back("CONNECT");
	cmdName.push_back("TRACE");
	cmdName.push_back("ADMIN");
	cmdName.push_back("INFO");

//4.4 Envoi de messages
	cmdName.push_back("PRIVMSG");
	cmdName.push_back("NOTICE");

//4.5 Requêtes basées sur les utilisateurs

	cmdName.push_back("WHO");
	cmdName.push_back("WHOIS");
	cmdName.push_back("WHOWAS");
//4.6 Messages divers

	cmdName.push_back("KILL");
	cmdName.push_back("PING");
	cmdName.push_back("PONG");
	cmdName.push_back("ERROR");

	//5. Messages optionnels
	cmdName.push_back("AWAY");
	cmdName.push_back("REHASH");
	cmdName.push_back("RESTART");
	cmdName.push_back("SUMMON");
	cmdName.push_back("OPERWALL");
	cmdName.push_back("USERHOST");
	cmdName.push_back("ISON");
		
		//4. Détails des messages

	// 	//4.1 Etablissement de connexion
	cmdPtr.push_back(PASS);
	cmdPtr.push_back(NICK);
	cmdPtr.push_back(USER);
	cmdPtr.push_back(SERVER);
	cmdPtr.push_back(OPER);
	cmdPtr.push_back(QUIT);
	cmdPtr.push_back(SQUIT);

	//4.2 Opérations sur les canaux
	cmdPtr.push_back(JOIN);
	cmdPtr.push_back(PART);
	cmdPtr.push_back(MODE);
	cmdPtr.push_back(TOPIC);
	cmdPtr.push_back(NAMES);
	cmdPtr.push_back(LIST);
	cmdPtr.push_back(INVITE);
	cmdPtr.push_back(KICK);
	
	//4.3 Requêtes et commandes des serveurs
	cmdPtr.push_back(VERSION);
	cmdPtr.push_back(STATS);
	cmdPtr.push_back(LINKS);
	cmdPtr.push_back(TIME);
	cmdPtr.push_back(CONNECT);
	cmdPtr.push_back(TRACE);
	cmdPtr.push_back(ADMIN);
	cmdPtr.push_back(INFO);
	
	//4.4 Envoi de messages
	cmdPtr.push_back(PRIVMSG);
	cmdPtr.push_back(NOTICE);
	
	//4.5 Requêtes basées sur les utilisateurs
	cmdPtr.push_back(WHO);
	cmdPtr.push_back(WHOIS);
	cmdPtr.push_back(WHOWAS);
	
	//4.6 Messages divers
	cmdPtr.push_back(KILL);
	cmdPtr.push_back(PING);
	cmdPtr.push_back(PONG);
	cmdPtr.push_back(ERROR);
	
	//5. Messages optionnels
	cmdPtr.push_back(AWAY);
	cmdPtr.push_back(REHASH);
	cmdPtr.push_back(RESTART);
	cmdPtr.push_back(SUMMON);
	cmdPtr.push_back(OPERWALL);
	cmdPtr.push_back(USERHOST);
	cmdPtr.push_back(ISON);
}
	
};
