/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:40:33 by apommier          #+#    #+#             */
/*   Updated: 2023/03/03 19:37:23 by apommier         ###   ########.fr       */
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
	if (find_client_list(allFds.channelList[chanNbr].banList, &allFds.userData[userNbr]) != -1)
	{
		errorStr = "474 * JOIN " + allFds.channelList[chanNbr].name + " :Cannot join channel (+b)\n";
		cmd_error(allFds, allFds.userData[userNbr].fd, errorStr); //ERR_INVITEONLYCHAN
		return (0);
	}
	else if (allFds.channelList[chanNbr].mode.i && find_client_list(allFds.channelList[chanNbr].invitedList, &allFds.userData[userNbr]) == -1)
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


void join_or_create(std::string buffer, fdList &allFds, int userNbr)
{
	int chanNbr;
	int invitedUser;
	channelData joined_chan;
	std::vector<std::string> splitBuff;
	
	std::cout << "JOINORCREATE\n";
	split(buffer, ' ', splitBuff);
	chanNbr = find_channel(allFds, splitBuff[1]);
	if (chanNbr != -1) //chan already exist
	{
		if (!chan_check(allFds, userNbr, chanNbr, splitBuff))
			return ;
		allFds.userData[userNbr].joinedChan.push_back(&allFds.channelList[chanNbr]); //add chan in user data
		allFds.channelList[chanNbr].userList.push_back(&allFds.userData[userNbr]);//add user in chan data
		allFds.channelList[chanNbr].nbrUser++;
		joined_chan = *(allFds.userData[userNbr].joinedChan.back());
		if ((invitedUser = find_client_list(allFds.channelList[chanNbr].invitedList, &allFds.userData[userNbr])) != -1)
			allFds.channelList[chanNbr].invitedList.erase(allFds.channelList[chanNbr].invitedList.begin() + invitedUser);
	}
	else //chan doesn't exist yet
	{
		std::cout << "new chan\n";
		channelData new_chan;
		if (splitBuff[1][0] != '#' && splitBuff[1][0] != '&')
			cmd_error(allFds, allFds.userData[userNbr].fd, "476 * " + splitBuff[1] + " :Bad Channel Mask\n");
		new_chan.name = splitBuff[1];
		new_chan.nbrUser = 1;
		new_chan.opList.push_back(&allFds.userData[userNbr]);
		new_chan.userList.push_back(&allFds.userData[userNbr]);
		joined_chan = new_chan;
		allFds.channelList.push_back(new_chan);
		allFds.userData[userNbr].joinedChan.push_back(&allFds.channelList.back());//add chan in user data
	}
	// if (chanNbr == -1)
	// {
	// 	chanNbr = 
	// 	find_channel(allFds, splitBuff[1])
	// }

	std::string fullMsg;
	fullMsg = ":" + allFds.userData[userNbr].nickname + "!" + allFds.userData[userNbr].userName + "@" + allFds.userData[userNbr].ip + " JOIN :" + joined_chan.name + "\n";
	for (int i = 0; i < joined_chan.nbrUser; i++)
	{
		send(joined_chan.userList[i]->fd, fullMsg.c_str(), fullMsg.size(), 0);
		std::cout << "loop here\n";
	}

	if (chanNbr == -1)
		chanNbr = find_channel(allFds, splitBuff[1]);
	if (!allFds.channelList[chanNbr].topic.empty())
		cmd_reply(allFds, allFds.userData[userNbr].fd, "332 TOPIC " + allFds.channelList[chanNbr].name + " :" + allFds.channelList[chanNbr].topic + "\n");
	//else
	//	cmd_error(allFds, allFds.userData[userNbr].fd, "NOTICE 331 TOPIC " + allFds.channelList[chanNbr].name + " :No topic is set\n");
	// if (chanNbr == -1)
	// {
			
	// }
}




void join_loop(fdList &allFds, std::vector<std::string> splitBuff, int userNbr)
{
	std::vector<std::string>	splitChan;
	std::vector<std::string>	splitPwd;
	std::string					buffer;
	
	std::cout << "join loop buf= " << splitBuff[1] << std::endl;
	std::cout << "==========join loop========\n";
	split(splitBuff[1], ',', splitChan);
	split(splitBuff[1], ',', splitPwd);
	if (splitBuff[1] == "0")
	{
		leave_all(allFds, userNbr);
		return ;
	}
	std::cout << "==========join loop2========\n";
	std::cout << "size= " << splitChan.size() << std::endl;
	std::cout << "content= " << splitChan[0] << std::endl;
	for (size_t i = 0; i < splitChan.size(); i++)
	{
		if (splitChan[i][0] != '#' && splitChan[i][0] != '&')
		{
			//error bad channel name
			buffer = "476 * JOIN " + splitChan[i] + " ::Bad Channel Mask\n";
			cmd_error(allFds, allFds.userData[userNbr].fd, buffer);
			//:Bad Channel Mask
			std::cout << "bad chan mask\n";
			return ;
		}
		if (i < splitPwd.size())
			buffer = "JOIN " + splitChan[i] + " " + splitPwd[i];
		else
			buffer = "JOIN " + splitChan[i];
		join_or_create(buffer, allFds, userNbr);
		std::cout << "i= " << i << "   ==========join loop3========\n";
	}
	std::cout << "==========join loop3========\n";
}




void JOIN(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	std::string msg;
	std::cout << "==========join start========\n";

	std::cout << "userNbr= " << userNbr << std::endl;
	if (!allFds.userData[userNbr].registered) 
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "451 * JOIN :You have not registered\n");
		return ;
	}
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2) 
	{
		/*change error*/
		std::cout << "JOIN : need more param\n";
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 * JOIN :Not enough parameters\n"); //ERR_NEEDMOREPARAMS
		return ;
	}
	join_loop(allFds, splitBuff, userNbr);
	//if (splitBuff[1].find(' ') != std::string::npos || splitBuff[1].find(7) != std::string::npos) 

	//send 352 and 315 or 353 and 366 (WHO or NAME)
}