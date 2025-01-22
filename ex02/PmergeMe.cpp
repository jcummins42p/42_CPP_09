/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:43:14 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/21 20:53:41 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe( void ) {
	generateJacobstahlSequence( JACOBSTAHL_SIZE );
}

PmergeMe::PmergeMe( const PmergeMe& other ) {
	*this = other;
}

PmergeMe &PmergeMe::operator=( const PmergeMe& other ) {
	if (this != &other)
	{
		this->unsortedVector = other.unsortedVector;
		this->sortedVector = other.sortedVector;
		this->unsortedList = other.unsortedList;
		this->sortedList = other.sortedList;
	}
	return *this;
}

PmergeMe::~PmergeMe( void ) {}

template <typename T>
static void printContainer( const T &container ) {
	if (container.size() == 0) {
		std::cout << "Container is empty" << std::endl;
		return;
	}
	typename T::const_iterator it = container.begin();
	std::cout << *it++;
	while (it != container.end())
		std::cout << ", " << *it++;
	std::cout << std::endl;
}

static bool argAllDigits( char *arg ) {
	if (*arg == '-')
		arg++;
	for (int i = 0; arg[i]; i++)
		if (!isdigit(arg[i]))
			return false;
	return true;
}

template <typename T>
static std::string toString( const T &input ) {
	std::stringstream ss;
	ss << input ;
	return (ss.str());
}

static void pmerge_error( unsigned int arg_n, std::string arg, std::string message ) {
	throw std::invalid_argument("Arg #" + toString(arg_n)
		+ " (" + toString(arg) + "): " + message);
}

template <typename T>
static void addNumberToContainer( T &container, char *arg ) {
	static unsigned int arg_n = 1;
	if (!argAllDigits(arg))
		pmerge_error(arg_n, arg, "Non-number argument");
	long num = atol(arg);
	if (num < 0 || num > UINT_MAX)
		pmerge_error(arg_n, arg, "Number out of range");
	if (std::find(container.begin(), container.end(), num) != container.end())
		pmerge_error(arg_n, arg, "Non-unique number");
	container.push_back(static_cast<unsigned int>(num));
	arg_n++;
}

void PmergeMe::generateJacobstahlSequence( unsigned int n ) {
	if (jacobstahl.size())
		jacobstahl.clear();
	unsigned long i = 0;
	unsigned long j = 1;
	for (unsigned int k = 0; k < n; k++) {
		jacobstahl.push_back(i);
		i = j;
		j = jacobstahl.back() * 2 + j;
	}
}

void PmergeMe::printContainers( void ) const {
	std::cout << "Unsorted vector: ";
	printContainer(unsortedVector);
	std::cout << "Unsorted list: ";
	printContainer(unsortedList);
	std::cout << "Sorted vector: ";
	printContainer(sortedVector);
	std::cout << "Sorted list: ";
	printContainer(sortedList);
}

template <typename T>
T mergeInsertionSort( T container ) {
	unsigned int n_pairs = container.size() / 2;
	long straggler = -1;

	if (container.size() % 2)
		straggler = container.front();
	T a_chain;
	T b_chain;
	for (unsigned int i = 0; i < n_pairs; i++) {
		a_chain.push_front(container.at(i));
		container.pop_back();
		b_chain.push_front(container.at(i));
		container.pop_back();
	}
	std::cout << "A chain: ";
	printContainer(a_chain);
	std::cout << "B chain: ";
	printContainer(b_chain);
	if (straggler >= 0)
		std::cout << "Straggler: " << straggler << std::endl;
	return (a_chain);
}

void PmergeMe::parseInput( int argc, char *argv[] ) {
	if (!argc)
		throw std::invalid_argument("No input");
	for (int i = 0; i < argc; i++) {
		addNumberToContainer( unsortedVector, argv[i] );
		addNumberToContainer( unsortedList, argv[i] );
	}
	sortedVector = mergeInsertionSort( unsortedVector );
	sortedList = mergeInsertionSort( unsortedList );
}
