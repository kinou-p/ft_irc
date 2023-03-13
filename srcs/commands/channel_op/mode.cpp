/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:19:30 by sadjigui          #+#    #+#             */
/*   Updated: 2023/03/13 16:35:17 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"
#include <sstream>

//:kinou3!kinou@172.17.0.1 MODE #test +o :kinou1 
//:kinou3!kinou@172.17.0.1 MODE #test :+p 
//kinou3 = baseop
//kinou1 = newOP

void	chan_opt_o(fdList &allFds, int userNbr, std::vector<std::string> opt, int chanNbr, bool sign)
{
	(void)chanNbr;
	int pos;
	
	if (opt.size() < 4)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 " + allFds.userData[userNbr].nickname + " MODE " + opt[0] + " :Not enough parameters\r\n");
		return ;
	}
	if ((find_user(allFds, opt[3]) == -1))
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 " + allFds.userData[userNbr].nickname + " MODE " + opt[1] + " :No such nick\r\n");
		return ;
	}
	pos = find_client_list(allFds.channelList[chanNbr].opList, &allFds.userData[userNbr]) != -1;
	if (pos == -1 && !allFds.userData[userNbr].op)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "482 " + allFds.userData[userNbr].nickname + " MODE " + opt[1] + " :You're not channel operator\r\n");
		return ;
	}
	if (sign == false)
		allFds.channelList[chanNbr].opList.erase(allFds.channelList[chanNbr].opList.begin() + pos);
	else
		allFds.channelList[chanNbr].opList.push_back(&allFds.userData[userNbr]);
	chan_mode_reply(allFds, allFds.channelList[chanNbr], userNbr, "o", sign);
}

void	chan_opt_k(fdList &allFds, int userNbr, std::vector<std::string> opt, int chanNbr, bool sign)
{
	if (find_client_list(allFds.channelList[chanNbr].opList, &allFds.userData[userNbr]) == -1 && !allFds.userData[userNbr].op)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "482 " + allFds.userData[userNbr].nickname + " MODE " + opt[1] + " :You're not channel operator\n");
		return ;
	}
	if (opt.size() < 3)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 " + allFds.userData[userNbr].nickname + " MODE " + opt[0] + " :Not enough parameters\n");
		return ;
	}
	if (sign == true)
	{
		allFds.channelList[chanNbr].mode.k = 1;
		allFds.channelList[chanNbr].password = opt[3];
	}
	else
		allFds.channelList[chanNbr].mode.k = 0;
	chan_mode_reply(allFds, allFds.channelList[chanNbr], userNbr, "k", sign);
}

void	chan_opt_v(fdList &allFds, int userNbr, std::vector<std::string> opt, int chanNbr, bool sign)
{
	if (find_client_list(allFds.channelList[chanNbr].opList, &allFds.userData[userNbr]) < 0)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "482 " + allFds.userData[userNbr].nickname + " MODE " + opt[1] + " :You're not channel operator\n");
		return ;
	}
	if (opt.size() < 4)
	{
		std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
		std::cout << "how to use it :/MODE <channel> +/-v <user>" << std::endl;
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 " + allFds.userData[userNbr].nickname + " MODE " + opt[0] + " :Not enough parameters\n");
		return ;
	}
	
	int target = find_user(allFds, opt[3]);
	if (target == -1)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 " + allFds.userData[userNbr].nickname + " MODE " + opt[3] + " :No such nick\n");
		return ;
	}
	
	int pos = find_client_list(allFds.channelList[chanNbr].verboseList, &allFds.userData[target]);
	if (sign == true && pos == -1)
		allFds.channelList[chanNbr].verboseList.push_back(&allFds.userData[target]);
	if (sign == false && pos != -1)
		allFds.channelList[chanNbr].verboseList.erase(allFds.channelList[chanNbr].verboseList.begin() + pos);
	chan_mode_reply(allFds, allFds.channelList[chanNbr], userNbr, "v", sign);
}

void	chan_opt_b(fdList &allFds, int userNbr, std::vector<std::string> opt, int chanNbr, bool sign)
{
	std::vector<clientData *> ban(allFds.channelList[chanNbr].banList);
	std::vector<std::string> name;
	int pos;
	int target_in_client;
	int target_in_ban;
	
	if (opt.size() == 3 && sign == true)
		ban_reply(allFds.channelList[chanNbr], allFds.userData[userNbr]);
	if (opt.size() >= 4)
	{
		if (find_client_list(allFds.channelList[chanNbr].opList, &allFds.userData[userNbr]) < 0)
		{
			cmd_error(allFds, allFds.userData[userNbr].fd, "482 " + allFds.userData[userNbr].nickname + " MODE " + opt[1] + " :You're not channel operator\n");
			return ;
		}
		split(opt[3], ',', name);
		
		for (size_t i = 0; i < name.size(); i++)
		{
			target_in_client = find_user(allFds, name[i]);
			if (target_in_client == -1)
			{
				std::cout << "No user found" << std::endl;
				cmd_error(allFds, allFds.userData[userNbr].fd, "401 " + allFds.userData[userNbr].nickname + " MODE " + name[i] + " :No such nick\n");
			}
			
			target_in_ban = find_client_list(allFds.channelList[chanNbr].banList, &allFds.userData[target_in_client]);
			if (sign == true && target_in_ban == -1)
			{
				if (find_client_list(allFds.channelList[chanNbr].opList, &allFds.userData[target_in_client]))
				{
					allFds.channelList[chanNbr].banList.push_back(&allFds.userData[target_in_client]);
					std::cout << "call kick\n";
					KICK("/KICK " + allFds.channelList[chanNbr].name + " " + allFds.userData[target_in_client].nickname + " You have been banned from this channel", allFds, userNbr);
					if ((pos = find_client_list(allFds.channelList[chanNbr].userList, &allFds.userData[target_in_client])) != -1)
						allFds.channelList[chanNbr].userList.erase(allFds.channelList[chanNbr].userList.begin() + pos);
					if ((pos = find_client_list(allFds.channelList[chanNbr].opList, &allFds.userData[target_in_client])) != -1)
						allFds.channelList[chanNbr].opList.erase(allFds.channelList[chanNbr].opList.begin() + pos);
				}
				else
					cmd_error(allFds, allFds.userData[userNbr].fd, "482 " + allFds.userData[userNbr].nickname + " MODE " + opt[0] + " :You're not channel operator\n");
			}
			if (sign == false && target_in_ban != -1)
			{
				std::cout <<"target in bam == "<< allFds.channelList[chanNbr].banList[target_in_ban]->nickname << std::endl;
				allFds.channelList[chanNbr].banList.erase(allFds.channelList[chanNbr].banList.begin() + (target_in_ban));
			}
			std::cout << "counter" << std::endl;
		}
	}
	chan_mode_reply(allFds, allFds.channelList[chanNbr], userNbr, "b", sign);
	return ;
}

void do_chan_opt(fdList &allFds, int userNbr, std::vector<std::string> opt, int chanNbr /*, channel (string or direct reference or pointer but no copy)*/)
{
	bool sign = true;

	if (opt[2][0] == '-')
		sign = false;
	for (int i = 1; opt[2][i]; i++)
	{
		switch (opt[2][i])
		{
			case 'o': chan_opt_o(allFds, userNbr, opt, chanNbr, sign);
				break ;
			case 'p': allFds.channelList[chanNbr].mode.p = (sign == true) ? true : false;
				chan_mode_reply(allFds, allFds.channelList[chanNbr], userNbr, "p", sign);
				break ;
			case 's': allFds.channelList[chanNbr].mode.s = (sign == true) ? true : false;
				chan_mode_reply(allFds, allFds.channelList[chanNbr], userNbr, "s", sign);
				break ;
			case 'i': allFds.channelList[chanNbr].mode.i = (sign == true) ? true : false;
				chan_mode_reply(allFds, allFds.channelList[chanNbr], userNbr, "i", sign);
				break ;
			case 't': allFds.channelList[chanNbr].mode.t = (sign == true) ? true : false;
				chan_mode_reply(allFds, allFds.channelList[chanNbr], userNbr, "t", sign);
				break ;
			case 'n': allFds.channelList[chanNbr].mode.n = (sign == true) ? true : false;
				chan_mode_reply(allFds, allFds.channelList[chanNbr], userNbr, "n", sign);
				break ;
			case 'm': allFds.channelList[chanNbr].mode.m = (sign == true) ? true : false;
				chan_mode_reply(allFds, allFds.channelList[chanNbr], userNbr, "m", sign);
				break ;
			case 'l':
				if (sign == true)
					str_to_int(allFds.channelList[chanNbr].maxUser, opt[3]);
				chan_mode_reply(allFds, allFds.channelList[chanNbr], userNbr, "l", sign);
				break ;
			case 'b': chan_opt_b(allFds, userNbr, opt, chanNbr, sign);
				break ;
			case 'v': chan_opt_v(allFds, userNbr, opt, chanNbr, sign);
				break ;
			case 'k': chan_opt_k(allFds, userNbr, opt, chanNbr, sign);
				break ;
			default : std::cout << "Not launching option" << std::endl;
				break ;	
		}
	}
	return;
}

void	do_user_opt(fdList &allFds, int userNbr, std::vector<std::string> opt, int new_target)
{	
	bool sign = true;
	
	if (allFds.userData[userNbr].nickname != opt[1])
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "502 " + allFds.userData[userNbr].nickname + " MODE " + opt[1] + " :Cant change mode for other users\r\n");
		return ;
	}
	if (opt[2][0] == '-')
	{
		std::cout << "sign = false\n";
		sign = false;
	}
	for (int i = 1; opt[2][i]; i++)
	{
		switch(opt[2][i])
		{
			case 'i': allFds.userData[new_target].mode.i = (sign == true) ? true : false;
				user_mode_reply(allFds, allFds.userData[new_target]/*clientData &user*/, userNbr, "i");
				break ;
			case 's': allFds.userData[new_target].mode.s = (sign == true) ? true : false;
				break ;
			case 'w': allFds.userData[new_target].mode.w = (sign == true) ? true : false;
				break ;
			case 'o':
				if (sign == true)
					return ;
				allFds.userData[new_target].mode.o = (sign == true) ? true : false;
				break ;
			default:
				break ;
		}
	}
	return;
}

void	MODE(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	int pos;

	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		cmd_error(allFds, allFds.userData[userNbr].fd, "461 " + allFds.userData[userNbr].nickname + " MODE " + splitBuff[0] + " :Not enough parameters\n");
		return ;
	}
	if (splitBuff[1][0] == '#' || splitBuff[1][0] == '&')
	{
		if ((pos = find_channel(allFds, splitBuff[1])) == -1)
		{
			std::cout << splitBuff[1] << ": No such channel" << std::endl;
			cmd_error(allFds, allFds.userData[userNbr].fd, "403 " + allFds.userData[userNbr].nickname + " MODE " + splitBuff[1] + " :No such channel\n");
			return ;
		}
		if (splitBuff.size() > 2)
		{
			search_and_erase(splitBuff[2], "opsitnmlbvk");
			if ((splitBuff[2].size() < 2) || (splitBuff[2][0] != '-' && splitBuff[2][0] != '+'))
			{
				if (splitBuff[2].size() > 2)
				{
					if (splitBuff[2] == "b")
						ban_reply(allFds.channelList[pos], allFds.userData[userNbr]);
				}		
				std::cout << "Bad params" << std::endl;
				return ;
			}
			do_chan_opt(allFds, userNbr, splitBuff, pos);
		}
		else
			chan_reply(allFds.channelList[pos], allFds.userData[userNbr]);
		return ;
	}
	else if ((pos = find_user(allFds, splitBuff[1]))  == -1)
	{
		std::cout << "user doesn't exist" << std::endl;
		cmd_error(allFds, allFds.userData[userNbr].fd, "401 " + allFds.userData[userNbr].nickname + " MODE " + splitBuff[1] + " :No such nick\n");
		return ;
	}
	else
	{
		if (splitBuff.size() > 2)
		{
			search_and_erase(splitBuff[2], "iswo");
			if ((splitBuff[2].size() < 2) && (splitBuff[2][0] != '-' || splitBuff[2][0] != '+'))
			{
				cmd_error(allFds, allFds.userData[userNbr].fd, "461 " + allFds.userData[userNbr].nickname + " MODE " + splitBuff[0] + " :Not enough parameters\n");
				return ;
			}
			do_user_opt(allFds, userNbr, splitBuff, pos);
		}
		else 
			user_reply(allFds.userData[userNbr]);
	}
}