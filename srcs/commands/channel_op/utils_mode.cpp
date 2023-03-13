/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 00:13:32 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:36:06 by apommier         ###   ########.fr       */
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
	//:irc.local 368 kinou3 #test :End of channel ban list 
	endReply = ":irc.local 368 " + user.nickname + " " + chan.name + " :End of channel ban list\r\n";
	send(user.fd, endReply.c_str(), endReply.size(), 0);
}

void chan_reply(channelData &chan, clientData &user)
{
	//:irc.server.com 324 ClientName #channel +tnkLs 10 operator1 operator2
	(void) chan;
	//int mode;
	//std::string reply = " +";
	//:irc.local 324 kinou3 #test :+nt
	std::string reply = ":irc.local 324 " + user.nickname + " " + chan.name + " :+";
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

void chan_mode_reply(fdList &allFds, channelData &chan, int userNbr, std::string mode, int sign)
{
	std::string reply;
	std::string base_reply = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName
		+ "@" + allFds.userData[userNbr].ip + " MODE " + chan.name;// + " :+" + mode + "\r\n";

	if (sign && contain_any(mode, "olbvk"))
	{
		reply += " +";
		if (mode == "o")
			reply += mode + " :" + chan.opList.back()->nickname;
		else if (mode == "l")
			reply += mode + " :" + int_to_str(chan.maxUser);
		else if (mode == "b")
			reply += mode + " :" + chan.banList.back()->nickname;
		else if (mode == "v")
			reply += mode + " :" + chan.verboseList.back()->nickname;
		else if (mode == "k")
			reply += mode + " :" + chan.password;
	}
	else if (contain_any(mode, "obv"))
	{
		if (mode == "o")
			reply += " -" + mode + " :" + chan.verboseList.back()->nickname;
		else if (mode == "b")
			reply += " -" + mode + " :" + chan.verboseList.back()->nickname;
		else if (mode == "v")
			reply += " -" + mode + " :" + chan.verboseList.back()->nickname;
	}
	else if (sign)
			reply += " :+" + mode;
	else
		reply += " :-" + mode;
	reply = base_reply + reply;
	reply += "\r\n";
	std::cout << "reply=" << reply << std::endl;
	for (size_t i = 0; i < chan.userList.size(); i++)
	{
		std::cout << "i=" << i << std::endl;
		send(chan.userList[i]->fd, reply.c_str(), reply.size(), 0);
	}
}

void user_mode_reply(fdList &allFds, clientData &user, int userNbr, std::string mode)
{
	std::string reply = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName
		+ "@" + allFds.userData[userNbr].ip + " MODE " + user.nickname + " :+" + mode + "\r\n";
	send(allFds.userData[userNbr].fd, reply.c_str(), reply.size(), 0);
}

void user_reply(clientData &user)
{
	std::string reply = ":irc.local 221 " + user.nickname + " +";
	if (user.mode.i)
		reply += 'i';
	if (user.mode.s)
		reply += 's';
	if (user.mode.w)
		reply += 'w';
	if (user.mode.o)
		reply += 'o';
	reply += "\r\n";
	std::cout << reply;
	send(user.fd, reply.c_str(), reply.size(), 0);	
}

int search_and_erase(std::string &str, std::string toFind)
{
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