/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:44:19 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/27 19:47:43 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# define JACOBSTAHL_SIZE 10
# define PAIRSORT_INIT 1

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

		void printContainerByString( const std::string &select ) const;
		void parseInput( int argc, char *argv[] );
		void generateJacobsthalSequence( unsigned int n );
		void mergeInsertionSort( const std::string &select );

	private:
		std::vector<unsigned int> vector_numbers;
		std::deque<unsigned int> deque_numbers;

		unsigned int vector_comparisons;
		unsigned int deque_comparisons;
		//	store generated jacobsthal sequence
		std::vector<unsigned long> jacobsthal;
} ;

#endif

