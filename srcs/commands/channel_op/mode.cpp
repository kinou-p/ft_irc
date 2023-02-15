/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:19:30 by apommier          #+#    #+#             */
/*   Updated: 2023/02/14 23:28:49 by apommier         ###   ########.fr       */
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



void do_chan_option(fdList &allFds, int userNbr, std::string opt /*, channel (string or direct reference or pointer but no copy)*/)
{
	(void)allFds;
	(void)userNbr;
	for (int i = 0; opt[i]; i++)
	{
		//call option 
		//switch ? if forest? map container ? 2 tab (name and function pointer) ?
		// opt_i(int signe (= ou -), channel, user);
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
		// opt_i(int signe (= ou -), user);
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
			std::cout << "chan doesn't exist" << std::endl;
			// 403 ERR_NOSUCHCHANNEL
			// "<nom de canal> :No such channel"
			return ;
		}//else
		//verify_option(allFds, str, i); //needed?

		std::cout << "splitbuff[2] = " << splitBuff[2] << std::endl;
		
		search_and_erase(splitBuff[2], "opsitnmlbvk");
		std::cout << "splitbuff[2] after = " << splitBuff[2] << std::endl;
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

// void	verify_option(fdList &allFds, std::string str, int i)
// {
// 	(void)allFds;
// 	(void)i;
// 	(void)str;
// 	std::string find = "opsitnmlbvk";
// 	std::cout << "1 str = "<< str << std::endl;
// 	search_and_erase(str, find);
// 	std::cout << "2 str = "<< str << std::endl;
// 	//use_option(allFds, str, )
// }

// void	MODE(std::string buffer, fdList &allFds, int userNbr)
// {
// 	(void)buffer; 
// 	(void)allFds;
// 	(void)userNbr;
// 	int i = 1;
// 	std::vector<std::string> splitBuff;
// 	std::cout << "---------------->" << std::endl;
// 	split(buffer, ' ', splitBuff);
// 	std::vector<std::string>::iterator ptr = splitBuff.begin();
// 	std::cout << "-------->" << splitBuff.size() << std::endl;
// 	if (splitBuff.size() != 6)
// 	{
// 		std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
// 		return ;
// 	}
// 	ptr++;
// 	std::string str = *ptr; /*std::string str = splitBuff[1]; ⚠️  */ /*STR sert a rien |*ptr = str|*/
// 	if (str[0] == '#' || str[0] == '&')
// 	{
// 		std::string cmd = str.substr(1, str.npos); //std::string cmd = (*ptr).substr(1, str.npos);	//Not needed? need full channel's name  with # or &
// 		std::cout << "test = "<< str << std::endl; //std::cout << "test = "<< *ptr << std::endl;
// 		if (find_channel(allFds, cmd) < 0)															//find_channel(allFds, cmd)				
// 			std::cout << "Channel " << cmd <<" Not found" << std::endl;
// 		while (ptr != splitBuff.end())
// 		{
// 			std::string str = *ptr;
// 			if (str[0] == '#' || str[0] == '&')
// 			{
// 				// if (find_channel(allFds, str+1))
// 				std::cout << "test = "<< str << std::endl;
				
// 			}
// 			verify_option(allFds, str, i);
// 			ptr++;
// 			i++;
// 		}
// 	}
// 	return ;
// }