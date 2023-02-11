/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:40:33 by apommier          #+#    #+#             */
/*   Updated: 2023/02/11 14:55:28 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void JOIN(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	int chanNbr;
	std::cout << "==========join start========\n";

	if (allFds.channelList.size() == MAX_CHAN)
	{
		std::cout << "creation of channel refused, maximum number reached" << std::endl; // send msg to user?
		return ;
	}

	std::cout << "userNbr= " << userNbr << std::endl;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		/*change error*/cmd_error(allFds, allFds.userData[userNbr].fd, "431 * NICK :No nickname given\n");
		return ;
	}
	
	chanNbr = find_channel(allFds, splitBuff[1]);
	if (chanNbr != -1) //chan already exist
	{
		allFds.userData[userNbr].joinedChan.push_back(&allFds.channelList[chanNbr]); //add chan in user data
		allFds.channelList[chanNbr].userList.push_back(&allFds.userData[userNbr]);//add user in chan data
		allFds.channelList[chanNbr].nbrUser++;
			std::cout << "join2 nickname " << allFds.channelList.back().userList[0]->nickname << std::endl;
			std::cout << "join2 fd " << allFds.channelList.back().userList[0]->nickname << std::endl;
		//allFds.channelList.push_back(new_chan);
		//std::cout << "nbruser in existent chan / persistence = " << allFds.channelList[chanNbr].nbrUser << std::endl;
		//std::cout << "nbruser in existent user / persistence = " << allFds.userData[userNbr].joinedChan[0]->nbrUser << std::endl;
		//message nickname joined the channel?
	}
	else //chan doesn't exist yet
	{
		std::cout << "new chan\n";
		channelData new_chan;
		
		new_chan.name = splitBuff[1];
		new_chan.nbrUser = 1;
		new_chan.userList.push_back(&allFds.userData[userNbr]);
		//new_chan.userList

		allFds.channelList.push_back(new_chan);
		allFds.userData[userNbr].joinedChan.push_back(&allFds.channelList.back());//add chan in user data
		//allFds.channelList.back().userList.push_back(&allFds.userData[userNbr]);//add user in chan data
		

		// allFds.userData[userNbr].joinedChan.push_back(&allFds.channelList[chanNbr]); //add chan in user data
		// allFds.channelList[chanNbr].userList.push_back(&allFds.userData[userNbr]);//add user in chan data
		// allFds.channelList[chanNbr].nbrUser++;

		
			std::cout << "join nickname " << allFds.channelList[0].userList[0]->nickname << std::endl;
			std::cout << "join fd " << allFds.channelList[0].userList[0]->fd << std::endl;
			//ft_putstr_fd(allFds.channelList[fd].userList[i]->fd, fullMsg);
			//std::cout << "loop here\n";

		//message nickname created the channel?
	}
	// std::cout << "============persitence test============\n";
	// std::cout << "odlname = " << allFds.userData[userNbr].joinedChan.back()->name << std::endl;
	// allFds.channelList.back().name = "new name";
	// std::cout << "newname = " << allFds.userData[userNbr].joinedChan.back()->name << std::endl;
	// //allFds.channelList;
}