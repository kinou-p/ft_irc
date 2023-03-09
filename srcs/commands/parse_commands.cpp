/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:01:25 by apommier          #+#    #+#             */
/*   Updated: 2023/03/09 05:38:19 by apommier         ###   ########.fr       */
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
	std::cout << "\n===========MSG RECEIVE=============" << std::endl;
	std::vector<std::string> splitBuff;
	std::cout << "USERNBR: " << userNbr << " | ";
	std::cout << "BUFFER: " << buffer;
	int a = 0;

	if (buffer.find(13) != std::string::npos) //change that pls
	{
		//std::cout << "pos of bitch= " << buffer.find(13) << std::endl;
		//std::cout << "size= " << buffer.size() << std::endl;
		//if (buffer.find(13) != buffer.size() - 2)
		//	std::cout << "BE CAREFUL CHAR 10 (line feed) not at end\n";
		buffer.erase(buffer.find(13), 1);
	}


	
	allFds.userData[userNbr].cmdBuffer += buffer;
	if (allFds.userData[userNbr].cmdBuffer.find('\n') == std::string::npos)
		return ;
	allFds.userData[userNbr].cmdBuffer.erase(allFds.userData[userNbr].cmdBuffer.size() - 1);
	split(allFds.userData[userNbr].cmdBuffer, ' ', splitBuff);
	//std::cout << "before toupper: " << splitBuff[0] << std::endl;
	for (size_t i = 0; i < splitBuff[0].size(); i++)
		splitBuff[0][i] = toupper(splitBuff[0][i]);
	//std::cout << "after toupper: " << splitBuff[0] << std::endl;
	while (a < allFds.parsingTab.cmdNbr - 1 && splitBuff[0] != allFds.parsingTab.cmdName[a]) 
		a++;
	//std::cout << "after while \n";
	if (a == allFds.parsingTab.cmdNbr - 1)
		std::cout << "Command not found\n";
	else
	{
		allFds.parsingTab.cmdPtr[a](allFds.userData[userNbr].cmdBuffer, allFds, userNbr);
		//allFds.parsingTab.cmdPtr[a]
		//JOIN(allFds.userData[userNbr].cmdBuffer, allFds, userNbr);
	}
	if (splitBuff[0] != "QUIT")
		allFds.userData[userNbr].cmdBuffer.clear();
}