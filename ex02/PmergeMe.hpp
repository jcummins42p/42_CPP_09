/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:44:19 by jcummins          #+#    #+#             */
/*   Updated: 2025/02/01 13:43:37 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# define JACOBSTAHL_SIZE 10
# define PAIRSORT_INIT 2

# include <algorithm>
# include <cstdlib>
# include <ctime>
# include <cmath>
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

		void printOutput( void ) const;

		void printContainerByString( const std::string &select ) const;
		void parseInput( int argc, char *argv[] );
		void generateJacobsthalSequence( unsigned int n );
		void mergeInsertionWrapper( const std::string &select );

		static unsigned int genJacobsthal( int n );

		double getTimeToProcessVector( const std::clock_t &start );
		double getTimeToProcessDeque( const std::clock_t &start );

		unsigned int getContainerSize( const std::string &select ) const;
		unsigned int getNComparisons( const std::string &select ) const;
	private:
		std::vector<unsigned int> vector_numbers;
		std::deque<unsigned int> deque_numbers;

		double time_to_process_vector;
		double time_to_process_deque;

		unsigned int n_comparisons_vector;
		unsigned int n_comparisons_deque;
		//	store generated jacobsthal sequence
		std::vector<unsigned long> jacobsthal;
} ;

#endif

