/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:19:30 by apommier          #+#    #+#             */
/*   Updated: 2023/02/15 22:57:31 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

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

void do_chan_opt(fdList &allFds, int userNbr, std::string opt /*, channel (string or direct reference or pointer but no copy)*/)
{
	(void)allFds;
	(void)userNbr;
	char opts[11] = {'o','p','s','i','t','n','m','l','b','v','k'};
	bool sign = true;
	if (opt[0] == '-')
		sign = false;
	for (int i = 0; opt[i]; i++)
	{
		// exec_chan_opt(allFds, opt[i], sign);
		int j = 0;

		for (; opts[j] && opts[j] != opt[i]; j++){}
	
		switch (j)
		{
			case 0: std::cout << "launching option: " << opt[i] << std::endl;
			break ;
			case 1: std::cout << "launching option: " << opt[i] << std::endl;
			break ;
			case 2: std::cout << "launching option: " << opt[i] << std::endl;
			break ;
			case 3: std::cout << "launching option: " << opt[i] << std::endl;
			break ;
			case 4: std::cout << "launching option: " << opt[i] << std::endl;
			break ;
			case 5: std::cout << "launching option: " << opt[i] << std::endl;
			break ;
			case 6: std::cout << "launching option: " << opt[i] << std::endl;
			break ;
			case 7: std::cout << "launching option: " << opt[i] << std::endl;
			break ;
			case 8: std::cout << "launching option: " << opt[i] << std::endl;
			break ;
			case 9: std::cout << "launching option: " << opt[i] << std::endl;
			break ;
			case 10: std::cout << "launching option: " << opt[i] << std::endl;
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

void do_user_option(fdList &allFds, int userNbr, std::string opt)
{
	(void)allFds;
	(void)userNbr;
	for (int i = 0; opt[i]; i++)
	{
		//call option 
		//switch ? if forest? map container ? 2 tab (name and function pointer) ?
		// opt_i(int signe (+ ou -), user);
	}
	return;
}

void	MODE(std::string buffer, fdList &allFds, int userNbr)
{
	(void)userNbr;
	std::vector<std::string> splitBuff;
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
		if (find_channel(allFds, splitBuff[1]) == -1) //if true chan doesn't exist
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
		if ((splitBuff[2].size() < 2) && (splitBuff[2][0] == '-' || splitBuff[2][0] == '+'))
		{
			std::cout << "Bad params" << std::endl;
			return ;
		}
		do_chan_opt(allFds, userNbr, splitBuff[2]);
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
	search_and_erase(splitBuff[2], "iwso");
	//do_option one by one here (do_user_opt)?
	
}