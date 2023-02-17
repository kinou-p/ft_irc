/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:19:52 by apommier          #+#    #+#             */
/*   Updated: 2023/02/17 21:55:29 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	TOPIC(std::string buffer, fdList &allFds, int userNbr)
{
	channelData chan;
	int chanNbr;
	std::vector<std::string> splitBuff;
	
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 * TOPIC :Not enough parameters\n");
		return ;
	}
	if (is_joined(allFds, splitBuff[1], userNbr) == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "422 * " + splitBuff[1] + " :You're not on that channel\n");
		return ;
	}
	if ((chanNbr = find_channel(allFds, splitBuff[1])) != -1)
	{
		chan = allFds.channelList[chanNbr];
		if (!is_chan_op(allFds, &chan, userNbr) && !allFds.userData[userNbr].op)
			cmd_error(allFds, allFds.userData[userNbr].fd, "482 * " + splitBuff[1] + " :You're not channel operator\n");
		return ;
	}
	// else if (!allFds.userData[userNbr].op && !allFds.userData[userNbr].op)
	// {
	// 	cmd_error(allFds, allFds.userData[userNbr].fd, "482 * " + splitBuff[1] + " :You're not channel operator\n");
	// 	return ;
	// }
	if (splitBuff.size() < 3)
		std::cout << "PRINT TOPIC here\n";//RPL_NOTOPIC //RPL_TOPIC
	else
	{
		allFds.channelList[chanNbr].topic = buffer.substr(6 + splitBuff[1].size() + 1, std::string::npos);
		//RPL_TOPIC
	}
	return ;
}