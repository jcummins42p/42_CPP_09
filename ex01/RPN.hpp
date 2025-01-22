/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:44:19 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/20 15:30:28 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <iostream>
# include <string>
# include <sstream>
# include <cstdlib> // atol

class	RPN
{
	public:
		RPN	( int argc, char *argv[] );
		RPN	( const RPN &other );
		RPN	&operator=( const RPN &other );
		~RPN	( void );

		void displayResult( void );
		void selectOperation( char operation );
		void processArgument( std::string arg );
	private:
		std::stack<int>	numbers;
} ;

#endif

