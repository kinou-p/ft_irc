/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:19:32 by apommier          #+#    #+#             */
/*   Updated: 2023/02/17 21:54:06 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

//Paramètres: <canal> <utilisateur> [<commentaire>]

void	KICK(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string>	splitBuff;
	std::string					msg;
	int							chanPos;
	int							userPos;
	channelData					chan;

	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 3)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "431 * KICK :Not enought argument\n");
		return ;
	}

	if ((chanPos = find_channel(allFds, splitBuff[1])) == -1)
	{	
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 * KICK " + splitBuff[1] + " :No such nick/channel\n");
		return ;
	}
	if (!allFds.userData[userNbr].op && is_joined(allFds, splitBuff[1], userNbr) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "422 * " + splitBuff[1] + " :You're not on that channel\n");
		return ;
	}
	if (chanPos != -1)
	{
		chan = allFds.channelList[chanPos];
		if (!is_chan_op(allFds, &chan, userNbr) && !allFds.userData[userNbr].op)
			cmd_error(allFds, allFds.userData[userNbr].fd, "482 * " + splitBuff[1] + " :You're not channel operator\n");
		return ;
	}
	msg = ":" + allFds.userData[userNbr].nickname + " KICK " + chan.name + " " + splitBuff[2];
	if (splitBuff.size() > 3)
		msg += ": " + buffer.substr(splitBuff[0].size() + splitBuff[1].size() + splitBuff[2].size() + 1, std::string::npos);
	if ((userPos = find_user(allFds, splitBuff[2])) == -1)
		return ;
	del_user_in_chan(&allFds.userData[userPos], &allFds.channelList[chanPos]);
	del_chan_in_user(&allFds.userData[userPos], &allFds.channelList[chanPos]);
	send(allFds.userData[userPos].fd, msg.c_str(), msg.size(), 0);
	
	// else if (!allFds.userData[userNbr].op)
	// {
	// 	cmd_error(allFds, allFds.userData[userNbr].fd, "482 * " + splitBuff[1] + " :You're not channel operator\n");
	// 	return ;
	// }







	return ;
}