/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:27:33 by apommier          #+#    #+#             */
/*   Updated: 2023/03/13 16:39:59 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

int main(int ac, char **av)
{
	if (!(ac == 3))
	{
		std::cout << "wrong number of arguments\nFORMAT: ./ircserv <port> <password>\n";
		exit(1);
	}
	std::cout << "============Homemade IRC Server start============" << std::endl;
	try
	{
		initialize(av);
	}
	catch(std::exception &e)
	{
		if (errno)
			std::cerr << "Fatal error: " << strerror(errno) << std::endl;
	}
	return (0);
}