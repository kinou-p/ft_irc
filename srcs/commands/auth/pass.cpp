/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:40:42 by apommier          #+#    #+#             */
/*   Updated: 2023/02/07 19:40:34 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	PASS(std::string buffer, fdList allFds, int user)
{
	std::string password;

	if (buffer.size() < 6)// ---PASS ---
	{
		cmd_error(allFds, user, "461 * PASS :Not enough parameters");
		return ;
	}
	
	// if (splitBuff.size() != 2)
	// {
	// 	cmd_error(allFds, user, "461 * PASS :Not enough parameters");
	// 	//write(allFds.userData[user].fd, "ERR_NEEDMOREPARAMS", 18);
	// 	return ;
	// }
	else if (allFds.userData[user].registered)
	{
		cmd_error(allFds, user, "462 * PASS :You may not reregister");
		return ;
	}
	password = buffer.substr(5, buffer.npos);
	allFds.userData[user].password = buffer;
}