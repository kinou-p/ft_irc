/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squit.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:11:03 by apommier          #+#    #+#             */
/*   Updated: 2023/02/12 14:23:39 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

void	SQUIT(std::string buffer, fdList &allFds, int userNbr)
{
	(void)buffer; 
	(void)allFds;
	(void)userNbr;
	
	if (allFds.userData[userNbr].op)
		allFds.alive = 0;
	else
	{
		std::cout << "Not op but okay i'll do it\n";
		allFds.alive = 0;
	}
	return ;
}