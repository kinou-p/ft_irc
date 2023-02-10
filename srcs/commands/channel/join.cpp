/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:40:33 by apommier          #+#    #+#             */
/*   Updated: 2023/02/09 21:55:57 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void JOIN(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	int chanNbr;
	std::cout << "join start\n";
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		/*change error*/cmd_error(allFds, allFds.userData[userNbr].fd, "431 * NICK :No nickname given\n");
		return ;
	}
	
	chanNbr = find_channel(allFds, splitBuff[1]);
	if (chanNbr)
	{
		//allFds.userData[userNbr].joinedChan.push_back(splitBuff[1]);
		//message nickname joined the channel?
	}
	else
	{
		std::cout << "new chan\n";
		channelData new_chan;
		
		new_chan.name = splitBuff[1];
		//new_chan.userList
		
		allFds.channelList.push_back(new_chan);
		allFds.userData[userNbr].joinedChan.push_back(&allFds.channelList.back());
		//message nickname created the channel?
	}
	std::cout << "============persitence test============\n";
	allFds.channelList.back().name = "new name";
	std::cout << "newname = " << allFds.userData[userNbr].joinedChan.back()->name << std::endl;
	//allFds.channelList;
}