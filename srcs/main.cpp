/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:27:33 by apommier          #+#    #+#             */
/*   Updated: 2023/02/12 22:35:11 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

int main(int ac, char **av)
{
	if (!(ac == 3 || ac == 2))
	{
		//ft_error("wrong number of arguments\nFORMAT: ./ircserv <port> <password>");
		std::cout << "wrong number of arguments\nFORMAT: ./ircserv <port> <password>\n";
		exit(1);
	}
	std::cout << "============Homemade IRC Server start============" << std::endl;
	// try
	// {
	// 	initialize(av);
	// }
	// catch
	// {
		
	// }
	initialize(av);
	return (0);
}