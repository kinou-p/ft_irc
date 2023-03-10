/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 00:13:32 by apommier          #+#    #+#             */
/*   Updated: 2023/03/10 22:03:03 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void ban_reply(channelData &chan, clientData &user)
{
	std::string endReply;
	std::string fullReply;
	std::string reply = ":irc.local 367 " + user.nickname + " " + chan.name + " ";
	for (size_t i = 0; i < chan.banList.size(); i++)
	{
		fullReply = reply + chan.banList[i]->nickname + "!" + chan.banList[i]->userName + "@" + chan.banList[i]->hostName + "\r\n";
		send(user.fd, fullReply.c_str(), fullReply.size(), 0);
	}
	endReply = ":irc.local 367 " + user.nickname + " " + chan.name + " :End of channel ban list\r\n";
	send(user.fd, endReply.c_str(), endReply.size(), 0);
}

void chan_reply(channelData &chan, clientData &user)
{
	//:irc.server.com 324 ClientName #channel +tnkLs 10 operator1 operator2
	(void) chan;
	//int mode;
	//std::string reply = " +";
	std::string reply = ":irc.local 324 " + user.nickname + " " + chan.name + " +";
	if (chan.mode.p)
		reply += 'p';
	if (chan.mode.s)
		reply += 's';
	if (chan.mode.i)
		reply += 'i';
	if (chan.mode.t)
		reply += 't';
	if (chan.mode.n)
		reply += 'n';
	if (chan.mode.m)
		reply += 'm';
	if (chan.mode.l)
		reply += 'l';
	if (chan.mode.k)
		reply += 'k';
	if (chan.mode.l)
		reply += chan.maxUser;
	for (size_t i = 0; i < chan.opList.size(); i++)
		reply += " " + chan.opList[i]->nickname;
	reply += "\r\n";
	send(user.fd, reply.c_str(), reply.size(), 0);
	//if (reply.size() > 2)
	//	reply_begin += reply;
	//return (reply);
}

void user_reply(clientData &user)
{
	//:irc.server.com 221 ClientName +ix

	//std::string reply;
	std::string reply = " +";
	std::string reply_begin = ":irc.local 221 " + user.nickname + " +";
	if (user.mode.i)
		reply += 'i';
	if (user.mode.s)
		reply += 's';
	if (user.mode.w)
		reply += 'w';
	if (user.mode.o)
		reply += 'o';
	reply += "\r\n";
	send(user.fd, reply.c_str(), reply.size(), 0);	
}

int search_and_erase(std::string &str, std::string toFind)
{
	// std::vector<string>::iterator i = str.begin;
	int i = 1; //1 instead of 0 to skip +/-
	while (str[i] != 0)
	{
		if (toFind.find(str[i]) == std::string::npos)
			str.erase(str.begin() + i);
		else
			i++;
	}
	std::cout << "splitbuff[2]after? = " << str << std::endl;
	return 1;
}

bool	str_to_int(int &i, const std::string s)
{
	std::stringstream ss(s);
	ss >> i;
	if (ss.fail())
		return false;
	return true;
}