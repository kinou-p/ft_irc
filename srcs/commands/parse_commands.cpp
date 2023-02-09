/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:01:25 by apommier          #+#    #+#             */
/*   Updated: 2023/02/09 13:20:39 by apommier         ###   ########.fr       */
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
	std::string cmd = buffer;
	std::vector<std::string> splitBuff;
	int a = 0;

	cmd.pop_back();
	
	split(cmd, ' ', splitBuff);
	
	std::cout << "BUFFER In PARSING: ---" << cmd << "---" << std::endl;
	while (splitBuff[0] != allFds.parsingTab.cmdName[a] && a < allFds.parsingTab.cmdNbr)
		a++;
	if (a == allFds.parsingTab.cmdNbr)
		std::cout << "Command not found\n"; 
	else
		allFds.parsingTab.cmdPtr[a](buffer, allFds, userNbr);
}