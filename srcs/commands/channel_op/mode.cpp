/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:19:30 by apommier          #+#    #+#             */
/*   Updated: 2023/02/13 00:23:55 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

int search_and_erase(std::string &str, std::string toFind)
{
	// std::vector<string>::iterator i = str.begin;
	int i = 0;
	while (str[i] != 0)
	{
		if (toFind.find(str[i]) == std::string::npos)
			str.erase(str.begin() + i);
		else
			i++;
	}
	return 1;
}

void	verify_option(fdList &allFds, std::string str, int i)
{
	(void)allFds;
	(void)i;
	(void)str;
	std::string find = "opsitnmlbvk";
	std::cout << "1 str = "<< str << std::endl;
	search_and_erase(str, find);
	std::cout << "2 str = "<< str << std::endl;
	use_option(allFds, str, )
}

// int	look_for_channel(fdList &allFds, std::string str)
// {
// 	if (allFds.chanelList[chanNbr.mode.k])
// 	{
// 		if (splitBuff.size() < 3 || allFdschannelList[chanNbr].password != splitBuff[2])
// 		{
// 			errorStr ="475* JOIN" + allFds.channelList[chanNbr].name+" :Cannot join channel(+k)\n";
// 			cmd_error(allFds, allFds.userData[userNbr].fd, errorStr);
// 		}
// 		return 0;
// 	}
// }



void	MODE(std::string buffer, fdList &allFds, int userNbr)
{
	(void)buffer; 
	(void)allFds;
	(void)userNbr;
	int i = 1;
	std::vector<std::string> splitBuff;
	std::cout << "---------------->" << std::endl;
	split(buffer, ' ', splitBuff);
	std::vector<std::string>::iterator ptr = splitBuff.begin();
	std::cout << "-------->" << splitBuff.size() << std::endl;
	if (splitBuff.size() != 6)
	{
		std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
		return ;
	}
	ptr++;
	std::string str = *ptr;
	if (str[0] == '#' || str[0] == '&')
	{
		std::string cmd = str.substr(1, str.npos);
		std::cout << "test = "<< str << std::endl;
		if (find_channel(allFds, cmd) < 0)
			std::cout << "Channel " << cmd <<" Not found" << std::endl;
		while (ptr != splitBuff.end())
		{
			std::string str = *ptr;
			if (str[0] == '#' || str[0] == '&')
			{
				// if (find_channel(allFds, str+1))
				std::cout << "test = "<< str << std::endl;
				
			}
			verify_option(allFds, str, i);
			ptr++;
			i++;
		}
	}
	return ;
}
