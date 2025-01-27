/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:44:19 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/27 17:52:46 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <iostream>
# include <algorithm>
# include <string>
# include <sstream>
# include <cstdlib> // atol

class	RPN
{
	public:
		RPN	( void );
		RPN	( const RPN &other );
		RPN	&operator=( const RPN &other );
		~RPN	( void );

		void displayResult( void ) const;
		void selectOperation( char operation );
		void processArgument( const std::string &arg );
		void processInput( int argc, std::string argv );
	private:
		std::stack<int>	numbers;
} ;

#endif
