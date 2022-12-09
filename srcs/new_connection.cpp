/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_connection.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:26:27 by apommier          #+#    #+#             */
/*   Updated: 2022/12/09 22:38:40 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

void new_connection(struct epoll_event newClient)
{
	std::cout << "new connection !" << std::endl;	
}