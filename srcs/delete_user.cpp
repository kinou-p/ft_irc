/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_user.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:38:50 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:39:49 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void del_user_in_chan(clientData *user, channelData *chan)
{
	int pos;
	
	if ((pos = find_client_list(chan->userList, user)) != -1)
		chan->userList.erase(chan->userList.begin() + pos);

	if ((pos = find_client_list(chan->banList, user)) != -1)
		chan->banList.erase(chan->banList.begin() + pos);

	if ((pos = find_client_list(chan->invitedList, user)) != -1)
		chan->invitedList.erase(chan->invitedList.begin() + pos);

	if ((pos = find_client_list(chan->verboseList, user)) != -1)
		chan->verboseList.erase(chan->verboseList.begin() + pos);
		
	if ((pos = find_client_list(chan->opList, user)) != -1)
		chan->opList.erase(chan->opList.begin() + pos);
}

void del_chan_in_user(clientData *user, channelData *chan)
{
	size_t i;
	for (i = 0; chan != user->joinedChan[i]; i++)
		;
	user->joinedChan.erase(user->joinedChan.begin() + i);
}

void delete_user(fdList &allFds, int userNbr)
{
	std::cout << "Delete user nbr " << userNbr << std::endl;
	
	for (size_t i = 0; i < allFds.channelList.size(); i++)//all joined chan
		del_user_in_chan(&allFds.userData[userNbr], &allFds.channelList[i]);
	close(allFds.userData[userNbr].fd);
	
	allFds.userData.erase(allFds.userData.begin() + userNbr);
	allFds.userFdList.erase(allFds.userFdList.begin() + userNbr);
	
	allFds.nbrUser--;
}