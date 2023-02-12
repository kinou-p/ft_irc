/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:01:25 by apommier          #+#    #+#             */
/*   Updated: 2023/02/11 22:51:59 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

std::string ft_test()
{
	std::cout << "hehe je suis la" << std::endl;
	return ("prout");
}

void parse_commands(std::string buffer, fdList &allFds, int userNbr)
{
	//std::string cmd = buffer;
	std::cout << "===========parse command=============" << std::endl;
	std::vector<std::string> splitBuff;
	int a = 0;
	
	allFds.userData[userNbr].cmdBuffer += buffer;
	if (allFds.userData[userNbr].cmdBuffer.find('\n') == std::string::npos)
		return ;
	allFds.userData[userNbr].cmdBuffer.erase(allFds.userData[userNbr].cmdBuffer.size() - 1);
	split(allFds.userData[userNbr].cmdBuffer, ' ', splitBuff);
	
	//std::cout << "BUFFER In PARSING: ---" << allFds.userData[userNbr].cmdBuffer << "---" << std::endl;
	while (a < allFds.parsingTab.cmdNbr - 1 && splitBuff[0] != allFds.parsingTab.cmdName[a]) 
		a++;
	//std::cout << "after while \n";
	if (a == allFds.parsingTab.cmdNbr - 1)
		std::cout << "Command not found\n";
	else
	{
		//std::cout << "Command name = " << allFds.parsingTab.cmdName[a] << std::endl;
		//std::cout << "Command nbr = " << a << std::endl;
		allFds.parsingTab.cmdPtr[a](allFds.userData[userNbr].cmdBuffer, allFds, userNbr);
		//allFds.parsingTab.cmdPtr[a]
		//JOIN(allFds.userData[userNbr].cmdBuffer, allFds, userNbr);
	}
	allFds.userData[userNbr].cmdBuffer.clear();
}