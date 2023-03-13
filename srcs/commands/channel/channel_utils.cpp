/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:21:57 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:29:41 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

int is_chan_op(fdList &allFds, channelData *chanName, int userNbr)
{
	std::vector<clientData*>::iterator start = chanName->opList.begin();
	std::vector<clientData*>::iterator  pastEnd = chanName->opList.end();

	if (allFds.userData[userNbr].op)
		return (1);
	while (start != pastEnd)
	{
		if (chanName->opList[pastEnd - start - 1]->nickname == allFds.userData[userNbr].nickname)
			return (1);
		start++;
	}
	return (0);	
}

int is_joined(fdList &allFds, std::string chanName, int userNbr)
{
	std::vector<channelData*>::iterator start = allFds.userData[userNbr].joinedChan.begin();
	std::vector<channelData*>::iterator  pastEnd = allFds.userData[userNbr].joinedChan.end();
	
	while (start != pastEnd)
	{
		if (allFds.userData[userNbr].joinedChan[pastEnd - start - 1]->name == chanName)
			return (pastEnd - start - 1);
		start++;
	}
	return (-1);	
}

int find_channel(fdList &allFds, std::string chanName)//return channel nbr
{
	int size = allFds.channelList.size();
	for (int i = 0; i < size; i++)
	{
		if (allFds.channelList[i].name == chanName)
			return (i);
	}
	return (-1);
}

int find_user(fdList &allFds, std::string userName)//return direct user fd
{
	int size = allFds.userData.size();
	for (int i = 0; i < size; i++)
	{
		if (allFds.userData[i].nickname == userName)
			return (i);
	}
	return (-1);
}

int is_in_same(fdList &allFds, int userNbr, int userNbr2)
{
	size_t size;
	
	if (userNbr < 0 || userNbr2 < 0)
		return (0);
	if (allFds.userData[userNbr].joinedChan.size() <= allFds.userData[userNbr2].joinedChan.size())
		size = allFds.userData[userNbr].joinedChan.size();
	else
		size = allFds.userData[userNbr2].joinedChan.size();
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (allFds.userData[userNbr].joinedChan[i] == allFds.userData[userNbr2].joinedChan[j])
				return (1);
		}
	}
	return (0);
}