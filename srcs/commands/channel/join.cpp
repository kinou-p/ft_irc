/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:40:33 by apommier          #+#    #+#             */
/*   Updated: 2023/02/14 14:50:57 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"


// Commande: JOIN
// Paramètres: <canal>{,<canal>} [<clé>{,<clé>}]
//		1459
//    ERR_NEEDMOREPARAMS +             ERR_BANNEDFROMCHAN
//    ERR_INVITEONLYCHAN +             ERR_BADCHANNELKEY 
//    ERR_CHANNELISFULL x              ERR_BADCHANMASK ? +
//    ERR_NOSUCHCHANNEL x              ERR_TOOMANYCHANNELS x
//    RPL_TOPIC

		//		2812
        //    ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
        //    ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
        //    ERR_CHANNELISFULL               ERR_BADCHANMASK
        //    ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
        //    ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
        //    RPL_TOPIC

void leave_all(fdList &allFds, int userNbr)
{
	(void)allFds;
	(void)userNbr;
}

int chan_check(fdList &allFds, int userNbr, int chanNbr, std::vector<std::string> splitBuff)
{
	std::string errorStr;
	if (0/*banned*/)
	{
		errorStr = "474 * JOIN " + allFds.channelList[chanNbr].name + " :Cannot join channel (+b)\n";
		cmd_error(allFds, allFds.userData[userNbr].fd, errorStr); //ERR_INVITEONLYCHAN
		return (0);
	}
	if (allFds.channelList[chanNbr].mode.i)
	{
		errorStr = "461 * JOIN " + allFds.channelList[chanNbr].name + " :Cannot join channel (+i)\n";
		cmd_error(allFds, allFds.userData[userNbr].fd, errorStr); //ERR_INVITEONLYCHAN
		return (0);
	}
	if (allFds.channelList[chanNbr].mode.k)
	{
		if (splitBuff.size() < 3 || allFds.channelList[chanNbr].password != splitBuff[2])
		{
			errorStr = "475 * JOIN " + allFds.channelList[chanNbr].name + " :Cannot join channel (+k)\n";
			cmd_error(allFds, allFds.userData[userNbr].fd, errorStr); //ERR_BADCHANNELKEY
		}
		return (0);
	}
	if (allFds.channelList[chanNbr].mode.l && allFds.channelList[chanNbr].nbrUser == allFds.channelList[chanNbr].maxUser)
	{
		errorStr = "471 * JOIN " + allFds.channelList[chanNbr].name + " :Cannot join channel (+l)\n";
		cmd_error(allFds, allFds.userData[userNbr].fd, errorStr); //ERR_CHANNELISFULL
		return (0);
	}
	return (1);
}






void join_or_create(std::vector<std::string> splitBuff, fdList &allFds, int userNbr)
{
	int chanNbr;
	channelData joined_chan;

	chanNbr = find_channel(allFds, splitBuff[1]);
	if (chanNbr != -1) //chan already exist
	{
		if (!chan_check(allFds, userNbr, chanNbr, splitBuff))
			return ;
		allFds.userData[userNbr].joinedChan.push_back(&allFds.channelList[chanNbr]); //add chan in user data
		allFds.channelList[chanNbr].userList.push_back(&allFds.userData[userNbr]);//add user in chan data
		allFds.channelList[chanNbr].nbrUser++;
		joined_chan = *(allFds.userData[userNbr].joinedChan.back());
	}
	else //chan doesn't exist yet
	{
		std::cout << "new chan\n";
		channelData new_chan;
		
		new_chan.name = splitBuff[1];
		new_chan.nbrUser = 1;
		new_chan.userList.push_back(&allFds.userData[userNbr]);
		//new_chan.userList
		joined_chan = new_chan;
		allFds.channelList.push_back(new_chan);
		allFds.userData[userNbr].joinedChan.push_back(&allFds.channelList.back());//add chan in user data
	}
	for (int i = 0; i < joined_chan.nbrUser; i++)
	{
		std::string fullMsg;
		fullMsg = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@" + allFds.userData[userNbr].ip + " JOIN :" + joined_chan.name + "\n";
		send(joined_chan.userList[i]->fd, fullMsg.c_str(), fullMsg.size(), 0);
		std::cout << "loop here\n";
	}
	// if (chanNbr == -1)
	// {
			
	// }
}









void JOIN(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::string msg;
	std::cout << "==========join start========\n";

	std::cout << "userNbr= " << userNbr << std::endl;
	if (!allFds.userData[userNbr].registered) 
	{
		/*change error*/
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 * JOIN :You have not registered\n"); //ERR_NEEDMOREPARAMS
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2) 
	{
		/*change error*/
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 * JOIN :Not enough parameters\n"); //ERR_NEEDMOREPARAMS
		return ;
	}
	//if (splitBuff[1].find(' ') != std::string::npos || splitBuff[1].find(7) != std::string::npos) 
	if (splitBuff[1][0] != '#' && splitBuff[1][0] != '&')
	{
		//error bad channel name
		msg = "476 * JOIN " + splitBuff[1] + " ::Bad Channel Mask\n";
		cmd_error(allFds, allFds.userData[userNbr].fd, msg);
		//:Bad Channel Mask
		return ;
	}
	if (splitBuff[1] == "0") 
	{
		leave_all(allFds, userNbr);
		return ;
	}
	join_or_create(splitBuff, allFds, userNbr);
	//send 352 and 315 or 353 and 366 (WHO or NAME)
}