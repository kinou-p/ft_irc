/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:01:25 by apommier          #+#    #+#             */
/*   Updated: 2023/02/06 12:39:13 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

void ft_test()
{
	std::cout << "hehe je suis la" << std::endl;
}

void parse_commands(std::string buffer, fdList allFds)
{
	std::string cmd = buffer;
	int a = 0;

	cmd.pop_back();
	std::cout << "BUFFER In PARSING: ---" << cmd << "---" << std::endl;
	while (cmd != allFds.parsingTab.cmdName[a] && a < allFds.parsingTab.cmdNbr)
		a++;
	if (a == allFds.parsingTab.cmdNbr)
		std::cout << "Command not found\n";
	else
		allFds.parsingTab.cmdPtr[a]();
}