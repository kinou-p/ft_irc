/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:04:47 by apommier          #+#    #+#             */
/*   Updated: 2023/02/11 20:04:53 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	OPER(std::string buffer, fdList &allFds, int userNbr)
{
	std::vector<std::string> splitBuff;
	split(buffer, ' ', splitBuff);
	if (splitBuff.size() < 2)
	{
		/*change error*/cmd_error(allFds, allFds.userData[userNbr].fd, "431 * OPER :No nickname given\n");
		return ;
	}
}