/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:44:19 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/27 14:05:59 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# define JACOBSTAHL_SIZE 10

# include <algorithm>
# include <cstdlib>
# include <iostream>
# include <limits.h>
# include <sstream>
# include <vector>
# include <deque>

class	PmergeMe
{
	public:
		PmergeMe	( void );
		PmergeMe	( const PmergeMe &other );
		PmergeMe	&operator=( const PmergeMe &other );
		~PmergeMe	( void );

		void printContainerByString( const std::string &select );
		void printJacobsthal( void ) const;
		void parseInput( int argc, char *argv[] );
		void generateJacobsthalSequenceNew( unsigned int n );

	private:
		std::vector<unsigned int> unsortedVector;
		std::vector<unsigned int> sortedVector;
		std::deque<unsigned int> unsortedDeque;
		std::deque<unsigned int> sortedDeque;

		unsigned int vector_comparisons;
		unsigned int deque_comparisons;
		//	store generated jacobsthal sequence
		std::vector<unsigned long> jacobsthalnew;
} ;

#endif

