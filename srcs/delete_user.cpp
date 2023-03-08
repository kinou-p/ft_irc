/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_user.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:38:50 by apommier          #+#    #+#             */
/*   Updated: 2023/03/08 01:08:10 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void del_user_in_chan(clientData *user, channelData *chan)
{
	// size_t i;
	int pos;
	// for (i = 0; user != chan->userList[i]; i++)
	// 	;
	// chan->userList.erase(chan->userList.begin() + i);

	if ((pos = find_client_list(chan->userList, user)) != -1)
		chan->userList.erase(chan->userList.begin() + pos);

	if ((pos = find_client_list(chan->banList, user)) != -1)
		chan->userList.erase(chan->banList.begin() + pos);

	if ((pos = find_client_list(chan->invitedList, user)) != -1)
		chan->userList.erase(chan->invitedList.begin() + pos);

	if ((pos = find_client_list(chan->verboseList, user)) != -1)
		chan->userList.erase(chan->verboseList.begin() + pos);
		
	if ((pos = find_client_list(chan->opList, user)) != -1)
		chan->userList.erase(chan->opList.begin() + pos);

	chan->nbrUser--;
}

void del_chan_in_user(clientData *user, channelData *chan)
{
	size_t i;
	for (i = 0; chan != user->joinedChan[i]; i++)
		;
	user->joinedChan.erase(user->joinedChan.begin() + i);
	//user->nbrUser--;
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
	allFds.userFdList.erase(allFds.userFdList.begin() + userNbr);
	
	allFds.nbrUser--;
}