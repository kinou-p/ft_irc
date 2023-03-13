/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_request.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:34:36 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:39:34 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

bool clientRequest(fdList &allFds, int userNbr) 
{
	char buf[1024] = {0};
	std::string buffer;
	size_t len = 1024;
	int ret = 0;
	
	if ((ret = recv(allFds.userData[userNbr].fd, buf, len, 0)) == -1)
		ft_error("recv() error");
	buffer = buf;
	buffer[ret] = 0;
	if (buffer.empty())
	{
		delete_user(allFds, userNbr);
		return (1);
	}
	std::vector<std::string> splitBuff;
	split_but_keep(buffer, '\n', splitBuff);
	for (size_t i = 0; i < splitBuff.size(); i++)
	{
		parse_commands(splitBuff[i], allFds, userNbr);
	}

	return (1);
}