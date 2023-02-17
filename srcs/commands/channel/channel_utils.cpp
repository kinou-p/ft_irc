/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:21:57 by apommier          #+#    #+#             */
/*   Updated: 2023/02/16 23:26:08 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

int is_chan_op(fdList &allFds, channelData *chanName, int userNbr)
{
	std::vector<clientData*>::iterator start = chanName->opList.begin();
	std::vector<clientData*>::iterator  pastEnd = chanName->opList.end();
	//std::cout << "name1= ---" << chanName << "---\n";
	if (allFds.userData[userNbr].op)
		return (1);
	while (start != pastEnd)
	{
		//std::cout << "result in find chan = " << pastEnd - start << std::endl;
		std::cout << "test = " << chanName->opList[pastEnd - start - 1]->nickname << "---\n";
		if (chanName->opList[pastEnd - start - 1]->nickname == allFds.userData[userNbr].nickname)
			return (1);
		start++;
	}
	std::cout << "chan not found\n";
	return (0);	
}

int is_joined(fdList &allFds, std::string chanName, int userNbr)
{
	std::vector<channelData*>::iterator start = allFds.userData[userNbr].joinedChan.begin();
	std::vector<channelData*>::iterator  pastEnd = allFds.userData[userNbr].joinedChan.end();
	//std::cout << "name1= ---" << chanName << "---\n";
	while (start != pastEnd)
	{
		//std::cout << "result in find chan = " << pastEnd - start << std::endl;
		std::cout << "test = " << allFds.userData[userNbr].joinedChan[pastEnd - start - 1]->name << "---\n";
		if (allFds.userData[userNbr].joinedChan[pastEnd - start - 1]->name == chanName)
			return (pastEnd - start - 1);
		start++;
	}
	std::cout << "chan not found\n";
	return (-1);	
}

int find_channel(fdList &allFds, std::string chanName)//return channel nbr
{
	std::_List_iterator<channelData> start = allFds.channelList.begin();
	std::_List_iterator<channelData> pastEnd = allFds.channelList.end();
	//std::cout << "name1= ---" << chanName << "---\n";
	while (start != pastEnd)
	{
		//std::cout << "result in find chan = " << pastEnd - start << std::endl;
		std::cout << "test = " << allFds.channelList[pastEnd - start - 1].name << "---\n";
		if (allFds.channelList[pastEnd - start - 1].name == chanName)
			return (pastEnd - start - 1);
		start++;
	}
	std::cout << "chan not found\n";
	return (-1);
}

int find_user(fdList &allFds, std::string userName)//return direct user fd
{
	std::_List_iterator<clientData> start = allFds.userData.begin();
	std::_List_iterator<clientData> pastEnd = allFds.userData.end();
	std::cout << "name1= ---" << userName << "---\n";
	while (start != pastEnd)
	{
		std::cout << "result in find user = " << pastEnd - start << std::endl;
		std::cout << "name2= ---" << allFds.userData[pastEnd - start - 1].nickname << "---\n";
		if (allFds.userData[pastEnd - start - 1].nickname == userName)
			return (pastEnd - start - 1);
		start++;
	}
	std::cout << "user not found\n";
	return (-1);
}

