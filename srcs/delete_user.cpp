/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_user.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:38:50 by apommier          #+#    #+#             */
/*   Updated: 2023/02/13 20:25:45 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void del_user_in_chan(clientData *user, channelData *chan)
{
	size_t i;
	for (i = 0; user != chan->userList[i]; i++)
		;
	chan->userList.erase(chan->userList.begin() + i);
	chan->nbrUser--;
}

void delete_user(fdList &allFds, int userNbr)
{
	std::cout << "Delete user nbr " << userNbr << std::endl;
	
	for (size_t i = 0; i < allFds.userData[userNbr].joinedChan.size(); i++)//all joined chan
	{
		del_user_in_chan(&allFds.userData[userNbr], allFds.userData[userNbr].joinedChan[i]);
		//allFds.userData[userNbr].joinedChan[i].erase(find_user_in_chan(allFds.userData[userNbr].joinedChan[i])/*find user in chan*/)
	}
	close(allFds.userData[userNbr].fd);
	
	allFds.userData.erase(allFds.userData.begin() + userNbr);
	allFds.userList.erase(allFds.userList.begin() + userNbr);
	
	allFds.nbrUser--;
}