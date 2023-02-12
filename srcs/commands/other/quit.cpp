/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:10:26 by apommier          #+#    #+#             */
/*   Updated: 2023/02/12 14:09:33 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	QUIT(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() == 2)
	{
		//print message?
	}
	delete_user(allFds, userNbr);
	return ;
}