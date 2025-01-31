/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:44:19 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/31 13:36:54 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# define JACOBSTAHL_SIZE 10
# define PAIRSORT_INIT 2

# include <algorithm>
# include <cstdlib>
# include <iostream>
# include <limits.h>
# include <sstream>
# include <vector>
# include <deque>
# include <math.h> //	required for pow()

# ifndef DB_OUTPUT
#  define DB_OUTPUT 0
# endif

enum e_debug_level
{
	DB_NONE,
	DB_NUMBERS,
	DB_TEXT
};

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
		void mergeInsertionWrapper( const std::string &select );

		static unsigned int genJacobsthal( int n );

	private:
		std::vector<unsigned int> vector_numbers;
		std::deque<unsigned int> deque_numbers;

		//	store generated jacobsthal sequence
		std::vector<unsigned long> jacobsthal;
} ;

#endif

