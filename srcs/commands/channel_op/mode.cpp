/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:19:30 by apommier          #+#    #+#             */
/*   Updated: 2023/02/27 23:58:08 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"
#include <sstream>

int search_and_erase(std::string &str, std::string toFind)
{
	// std::vector<string>::iterator i = str.begin;
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

// int ft_stoi(std::string str)
// {
// 	int i = 0;
// 	int result = 0;
	
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		result = result * 10 +str[i] - 48;
// 		i++;
// 	}
// 	return result;
// }

// void	exec_chan_opt(fdList &allFds, char opt, bool sign)
// {
// 	(void)allFds;
// 	char opts[11] = {'o','p','s','i','t','n','m','l','b','v','k'};
// 	int j = 0;

// 	for (; opts[j] && opts[j] != opt; j++){}
	
// 	switch (j)
// 	{
// 		case 0: std::cout << "launching option: " << opt << std::endl;
// 		break ;
// 		case 1: std::cout << "launching option: " << opt << std::endl;
// 		break ;
// 		case 2: std::cout << "launching option: " << opt << std::endl;
// 		break ;
// 		case 3: std::cout << "launching option: " << opt << std::endl;
// 		break ;
// 		case 4: std::cout << "launching option: " << opt << std::endl;
// 		break ;
// 		case 5: std::cout << "launching option: " << opt << std::endl;
// 		break ;
// 		case 6: std::cout << "launching option: " << opt << std::endl;
// 		break ;
// 		case 7: std::cout << "launching option: " << opt << std::endl;
// 		break ;
// 		case 8: std::cout << "launching option: " << opt << std::endl;
// 		break ;
// 		case 9: std::cout << "launching option: " << opt << std::endl;
// 		break ;
// 		case 10: std::cout << "launching option: " << opt << std::endl;
// 		break ;
// 		default : std::cout << "Not launching option" << std::endl;
// 		break ;	
// 	}
// }

void	chan_opt_o(fdList &allFds, int userNbr, std::vector<std::string> opt, int chanNbr, bool sign)
{
	(void)allFds;
	(void)userNbr;
	(void)chanNbr;
	
	if (opt.size() != 4)
	{
		std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
		return ;
	}
	if ((find_user(allFds, opt[3]) == -1))
	{
		std::cout << "User :" << opt[3] << " not found" << std::endl;
		return ;
	}

	//A voir
	if (allFds.userData[userNbr].mode.o == true && sign == true)
		allFds.userData[find_user(allFds, opt[3])].mode.o = (sign = true) ? true : false;
	
	std::cout << "-------> " << opt[3] << std::endl;
}

void	chan_opt_k(fdList &allFds, std::vector<std::string> opt, int chanNbr, bool sign)
{
	if (opt.size() != 4)
	{
		std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
		std::cout << "how to use it :/MODE <channel >+k <password>" << std::endl;
		return ;
	}
	if (sign == true)
		allFds.channelList[chanNbr].password = opt[3];
}

void	chan_opt_v(fdList &allFds, int userNbr, std::vector<std::string> opt, int chanNbr, bool sign)
{
	(void)userNbr;
	(void)chanNbr;
	(void)sign;
	
	if (opt.size() != 4)
	{
		std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
		std::cout << "how to use it :/MODE <channel> +/-v <user>" << std::endl;
		return ;
	}
	
	int target = find_user(allFds, opt[3]);
	if (target == -1)
	{
		std::cout << "no user found " << std::endl;
		return ;
	}
	
	int pos = find_client_list(allFds.channelList[chanNbr].verboseList, &allFds.userData[target]);
	if (sign == true && pos == -1)
		allFds.channelList[chanNbr].verboseList.push_back(&allFds.userData[target]);
	if (sign == false && pos != -1)
		allFds.channelList[chanNbr].verboseList.erase(allFds.channelList[chanNbr].verboseList.begin() + (pos -1));
}

void	chan_opt_b(fdList &allFds, int userNbr, std::vector<std::string> opt, int chanNbr, bool sign)
{
	std::vector<clientData *> ban(allFds.channelList[chanNbr].banList);
	(void)userNbr;
	(void)opt;
	(void)chanNbr;
	(void)sign;
	(void)ban;
	if (opt.size() == 3 && sign == true)
	{
		if (ban.size() < 1)
		{
			std::cout << "Nobody was banned on this channel" << std::endl;
			return ;
		}
		for (long unsigned int i = 0; i < ban.size(); ++i)
		{
			std::cout << ban[i]->userName << std::endl;
		}
	}
	if (opt.size() == 4)
	{
		int target_in_client = find_user(allFds, opt[3]);
		if (target_in_client != -1)
		{
			std::cout << "No user found" << std::endl;
			return ;
		}
		int target_in_ban = find_client_list(allFds.channelList[chanNbr].banList, &allFds.userData[target_in_client]);
		if (sign == true && target_in_ban == -1)
			allFds.channelList[chanNbr].banList.push_back(&allFds.userData[target_in_client]);
		if (sign == false && target_in_ban != -1)
			allFds.channelList[chanNbr].banList.erase(allFds.channelList[chanNbr].banList.begin() + (target_in_ban -1));
	}
}

void do_chan_opt(fdList &allFds, int userNbr, std::vector<std::string> opt, int chanNbr /*, channel (string or direct reference or pointer but no copy)*/)
{
	(void)allFds;
	(void)userNbr;
	char opts[11] = {'o','p','s','i','t','n','m','l','b','v','k'};
	bool sign = true;
	if (opt[2][0] == '-')
		sign = false;
	for (int i = 1; opt[2][i]; i++)
	{
		// exec_chan_opt(allFds, opt[i], sign);
		int j = 0;

		while (opts[j] && opts[j] != opt[2][i])
			j++;
	
		switch (j)
		{
			case 0: chan_opt_o(allFds, userNbr, opt, chanNbr, sign); //std::cout << "launching option: " << opt[2][i] << std::endl;
			break ;
			case 1: allFds.channelList[chanNbr].mode.p = (sign = true) ? true : false;
			break ;
			case 2: allFds.channelList[chanNbr].mode.s = (sign = true) ? true : false;
			break ;
			case 3: allFds.channelList[chanNbr].mode.i = (sign = true) ? true : false;
			break ;
			case 4: allFds.channelList[chanNbr].mode.t = (sign = true) ? true : false;
			break ;
			case 5: allFds.channelList[chanNbr].mode.n = (sign = true) ? true : false;
			break ;
			case 6: allFds.channelList[chanNbr].mode.m = (sign = true) ? true : false;
			break ;
			case 7:
				if (sign == true)
					str_to_int(allFds.channelList[chanNbr].maxUser, opt[3]);
			break ;
			case 8: chan_opt_b(allFds, userNbr, opt, chanNbr, sign);
			break ;
			case 9: chan_opt_v(allFds, userNbr, opt, chanNbr, sign);
			break ;
			case 10: chan_opt_k(allFds, opt, chanNbr, sign);
			break ;
			default : std::cout << "Not launching option" << std::endl;
			break ;	
		}
		//mode_i()
		//call option 
		//switch ? if forest? map container ? 2 tab (name and function pointer) ?
		// opt_i(int signe (+ ou -), channel, user);
	}
	return;
}

void do_user_option(fdList &allFds, int userNbr, std::string opt, int new_target)
{
	(void)allFds;
	(void)userNbr;
	for (int i = 1; opt[i]; i++)
	{
		
	}
	return;
}

void	MODE(std::string buffer, fdList &allFds, int userNbr)
{
	(void)userNbr;
	std::vector<std::string> splitBuff;
	int pos;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 3) 
	{
		std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
		return ;
	}
	//check if user is op? else error
	//check if (splitBuff[2][0] == +/-)  //splitbuff[2] always equal to {[+|-]|o|p|s|i|t|n|b|v}
		//else ??? erreur j'imagine mais j'ai pas trouvé
	if (splitBuff[1][0] == '#' || splitBuff[1][0] == '&') //splitbuff[1] always equal to <channel> or <nickname>
	{
		if ((pos = find_channel(allFds, splitBuff[1])) == -1) //if true chan doesn't exist
		{
			std::cout << splitBuff[1] << ": No such channel" << std::endl;
			// 403 ERR_NOSUCHCHANNEL
			// "<nom de canal> :No such channel"
			return ;
		}//else
		//verify_option(allFds, str, i); //needed?

		std::cout << "splitbuff[2] = " << splitBuff[2] << std::endl;
		
		search_and_erase(splitBuff[2], "opsitnmlbvk");
		std::cout << "splitbuff[2] after = " << splitBuff[2] << std::endl;
		if ((splitBuff[2].size() < 2) && (splitBuff[2][0] != '-' || splitBuff[2][0] != '+'))
		{
			std::cout << "Bad params" << std::endl;
			return ;
		}
		do_chan_opt(allFds, userNbr, splitBuff, pos);
		//do_option one by one here (do_chan_opt)?
		return ;
	}
	else if ((find_user(allFds, splitBuff[1]) == -1))
	{
		std::cout << "user doesn't exist" << std::endl;
		// 401 ERR_NOSUCHNICK
		// "<pseudonyme> :No such nick/channel"
		return ;
	}
	else if ((find_user(allFds, splitBuff[1]) != -1))
	{
		pos = find_user(allFds, splitBuff[1]);
		search_and_erase(splitBuff[2], "iswo");
		if ((splitBuff[2].size() < 2) && (splitBuff[2][0] != '-' || splitBuff[2][0] != '+'))
		{
			std::cout << "Bad params" << std::endl;
			return ;
		}
		do_user_opt(allFds, userNbr, splitBuff, pos);
	}
	//do_option one by one here (do_user_opt)?
	
}