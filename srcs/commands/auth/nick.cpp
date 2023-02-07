/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:28:38 by apommier          #+#    #+#             */
/*   Updated: 2023/02/07 15:13:27 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

//           ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
//           ERR_NICKNAMEINUSE               ERR_NICKCOLLISION

void	NICK(std::string buffer, fdList allFds, int user)
{
	std::vector<std::string> splitBuff;
	
	split(buffer, ' ', splitBuff);
	//if nickname ok then (another user has it? )
	allFds.userData[user].nickname = splitBuff[1];
	return ;
}