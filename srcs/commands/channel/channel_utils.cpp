/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:21:57 by apommier          #+#    #+#             */
/*   Updated: 2023/02/09 20:56:31 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_irc.hpp"

int find_channel(fdList &allFds, std::string chanName)
{
	std::vector<channelData>::iterator start = allFds.channelList.begin();
	std::vector<channelData>::iterator pastEnd = allFds.channelList.end();
	while (start != pastEnd)
	{
		std::cout << "result in find chan = " << pastEnd - start << std::endl;
		if (allFds.channelList[pastEnd - start].name == chanName)
			return (pastEnd - start);
		start++;
	}
	return (0);
}