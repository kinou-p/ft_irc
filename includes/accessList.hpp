/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessList.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:48:00 by apommier          #+#    #+#             */
/*   Updated: 2023/02/12 15:49:11 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_irc.hpp"

template<typename T>
class accessList : public std::list<T>{
	public :
		
		accessList<T>(){}	
		accessList<T>( const accessList<T> &src )
		{
			*this = src;
		}
		~accessList<T>(){}

		accessList<T>	&operator=(const accessList<T> &rhs)
		{
			(void)rhs;
			return *this;
		}
		
		T	&operator[](size_t nbr)
		{
			size_t i = 0;
			std::_List_iterator<T> start = this->begin();
			//int start = this->begin()
			while (i < nbr)
			{
				start++;
				i++;
			}
			return (*start);
		}
};
		template<typename T>
		std::_List_iterator<T> operator +(std::_List_iterator<T> ite, size_t const nbr) 
		{
			size_t i = 0;
			while (i < nbr)
			{
				ite++;
				i++;
			}
			return (ite);
		}

		template<typename T>
		int operator -(std::_List_iterator<T> lhs, std::_List_iterator<T> rhs) 
		{
			//rhs plus petit
			int i = 0;
			while (rhs != lhs)
			{
				rhs++;
				i++;
			}
			return (i);
		}