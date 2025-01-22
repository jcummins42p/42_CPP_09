/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:44:19 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/21 16:32:41 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# define JACOBSTAHL_SIZE 20

# include <algorithm>
# include <cstdlib>
# include <iostream>
# include <list>
# include <limits.h>
# include <sstream>
# include <vector>

class	PmergeMe
{
	public:
		PmergeMe	( void );
		PmergeMe	( const PmergeMe &other );
		PmergeMe	&operator=( const PmergeMe &other );
		~PmergeMe	( void );

		void printContainers( void ) const;
		void parseInput( int argc, char *argv[] );
		void generateJacobstahlSequence( unsigned int n );
	private:
		std::vector<unsigned int> unsortedVector;
		std::vector<unsigned int> sortedVector;
		std::list<unsigned int> unsortedList;
		std::list<unsigned int> sortedList;

		//	store generated jacobstahl sequence
		std::vector<unsigned long> jacobstahl;
} ;

#endif

