/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:27:33 by apommier          #+#    #+#             */
/*   Updated: 2022/12/06 21:50:25 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

int main(int ac, char **av)
{
	if (!(ac == 3 || ac == 2))
		ft_error("wrong number of arguments\nFORMAT: ./ircserv <port> <password>");
	initialize(av);
	return (0);
}