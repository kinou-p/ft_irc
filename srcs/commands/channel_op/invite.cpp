/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:19:56 by apommier          #+#    #+#             */
/*   Updated: 2023/03/10 22:24:11 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

// Commande: INVITE
// Paramètres: <pseudonyme> <canal>

//            ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
//            ERR_NOTONCHANNEL                ERR_USERONCHANNEL
//            ERR_CHANOPRIVSNEEDED
//            RPL_INVITING                    RPL_AWAY

void	INVITE(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::string msg;
	int invitedNbr;
	channelData chan;
	int chanNbr;
	
	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 " + allFds.userData[userNbr].nickname + " INVITE :You have not registered\r\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 3)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 " + allFds.userData[userNbr].nickname + " INVITE :Not enough parameters\r\n");
		return ;
	}
	if ((invitedNbr = find_user(allFds, splitBuff[1])) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 " + allFds.userData[userNbr].nickname + " " + splitBuff[1] + " :No such nick\r\n");
		return ;
	}
	if (is_joined(allFds, splitBuff[2], userNbr) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "422 " + allFds.userData[userNbr].nickname + " " + splitBuff[2] + " :You're not on that channel\r\n");
		return ;
	}
	if (is_joined(allFds, splitBuff[2], invitedNbr) != -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "443 " + allFds.userData[userNbr].nickname + " " + splitBuff[1] + " " + splitBuff[2] + " :is already on channel\r\n");
		return ;
	}
	// if (is_joined(allFds, splitBuff[2], invitedNbr) != -1)
	// {
	// 	cmd_error(allFds, allFds.userData[userNbr].fd, "443 " + allFds.userData[userNbr].nickname + " " + splitBuff[1] + " " + splitBuff[2] + " :is already on channel\n");
	// 	return ;
	// }
	if ((chanNbr = find_channel(allFds, splitBuff[2])) != -1)
	{
		chan = allFds.channelList[chanNbr];
		if (!is_chan_op(allFds, &chan, userNbr))
			cmd_error(allFds, allFds.userData[userNbr].fd, "482 " + allFds.userData[userNbr].nickname + " " + splitBuff[2] + " :You're not channel operator\r\n");
		return ;
	}
	else if (!allFds.userData[userNbr].op)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "482 " + allFds.userData[userNbr].nickname + " " + splitBuff[2] + " :You're not channel operator\r\n");
		return ;
	}
	std::cout << "invite him !!!!" << splitBuff[1] << " to " <<  splitBuff[2] << std::endl;
	//RPL_INVITING
	//RPL_AWAY
	chan.invitedList.push_back(&allFds.userData[invitedNbr]);//set authorization to join
	msg = "341 " + allFds.userData[userNbr].nickname + " " + chan.name + " " + splitBuff[1] + "\r\n";
	cmd_reply(allFds, allFds.userData[userNbr].fd, msg);
}