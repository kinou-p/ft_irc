/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:19:56 by apommier          #+#    #+#             */
/*   Updated: 2023/02/19 22:27:00 by apommier         ###   ########.fr       */
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
	int invitedNbr;
	channelData chan;
	int chanNbr;
	
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 3)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 * INVITE :Not enough parameters\n");
		return ;
	}
	if ((invitedNbr = find_user(allFds, splitBuff[1])) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 * " + splitBuff[1] + " :No such nick/channel\n");
		return ;
	}
	if (is_joined(allFds, splitBuff[2], userNbr) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "422 * " + splitBuff[2] + " :You're not on that channel\n");
		return ;
	}
	if (is_joined(allFds, splitBuff[2], invitedNbr) != -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "443 * " + splitBuff[1] + " " + splitBuff[2] + " :is already on channel\n");
		return ;
	}
	// if (is_joined(allFds, splitBuff[2], invitedNbr) != -1)
	// {
	// 	cmd_error(allFds, allFds.userData[userNbr].fd, "443 * " + splitBuff[1] + " " + splitBuff[2] + " :is already on channel\n");
	// 	return ;
	// }
	if ((chanNbr = find_channel(allFds, splitBuff[2])) != -1)
	{
		chan = allFds.channelList[chanNbr];
		if (!is_chan_op(allFds, &chan, userNbr))
			cmd_error(allFds, allFds.userData[userNbr].fd, "482 * " + splitBuff[2] + " :You're not channel operator\n");
		return ;
	}
	else if (!allFds.userData[userNbr].op)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "482 * " + splitBuff[2] + " :You're not channel operator\n");
		return ;
	}
	std::cout << "invite him !!!!" << splitBuff[1] << " to " <<  splitBuff[2] << std::endl;
	//RPL_INVITING
	//RPL_AWAY
	//set authorization to join
	return ;
}