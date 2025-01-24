/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:43:14 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/24 20:05:36 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//	constructor
PmergeMe::PmergeMe( void ) : vector_comparisons(0), deque_comparisons(0) {
	generateJacobsthalSequenceNew( JACOBSTAHL_SIZE );
}

PmergeMe::PmergeMe( const PmergeMe& other ) {
	*this = other;
}

PmergeMe &PmergeMe::operator=( const PmergeMe& other ) {
	if (this != &other)
	{
		this->unsortedVector = other.unsortedVector;
		this->sortedVector = other.sortedVector;
		this->unsortedDeque = other.unsortedDeque;
		this->sortedDeque = other.sortedDeque;
	}
	return *this;
}

//	destructor
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
	//if (std::find(container.begin(), container.end(), num) != container.end())
		//pmerge_error(arg_n, arg, "Non-unique number");
	container.push_back(static_cast<unsigned int>(num));
	arg_n++;
}

void PmergeMe::generateJacobsthalSequenceNew( unsigned int n ) {
	if (jacobsthalnew.size())
		jacobsthalnew.clear();
	unsigned long i = 0;
	unsigned long j = 1;
	jacobsthalnew.push_back(i);
	jacobsthalnew.push_back(j);
	for (unsigned int k = 2; k < n; k++) {
		jacobsthalnew.push_back(i * 2 + j);
		i = j;
		j = jacobsthalnew.back();
	}
}

void PmergeMe::printContainers( void ) const {
	std::cout << "Unsorted vector: ";
	printContainer(unsortedVector);
	std::cout << "Unsorted list: ";
	printContainer(unsortedDeque);
	std::cout << "Sorted vector: ";
	printContainer(sortedVector);
	std::cout << "Sorted list: ";
	printContainer(sortedDeque);
	std::cout << "Jacobsthal sequence new: ";
	printContainer(jacobsthalnew);
}

void printStraggler( long int straggler ) {
	if (straggler >= 0 )
		std::cout << "Straggler: " << straggler << std::endl;
}

// returns the number of comparisons made during the insert process
template <typename Container, typename T>
static unsigned int recursiveBinaryInsert(Container &sorted, typename Container::iterator L, typename Container::iterator R, T value) {
	unsigned int comparisons = 1;
	if (L == R)	{	// Comparing iterators does not count towards comparison total
		if (value < *L)
			sorted.insert(L, value);	// This just indicates that the correct node is found
		else
			sorted.insert(L + 1, value);
		return 1;
	}
	typename Container::iterator	M = L + (R - L) / 2;
	if (value < *M)
		comparisons = recursiveBinaryInsert(sorted, L, M, value);
	else
		comparisons = recursiveBinaryInsert(sorted, M + 1, R, value);
	return (comparisons);
}

template <typename Container, typename T>
static unsigned int binaryInsert(Container &sorted, typename Container::iterator L, typename Container::iterator R, T value) {
	std::cout << "Doing binary insert of value " << value << " in container ";
	printContainer(sorted);
	return recursiveBinaryInsert(sorted, L, R, value);
}

template <typename Container>
Container mergeInsertionSort( Container container ) {
	//unsigned int n_pairs = container.size() / 2;
	long straggler = -1;

	binaryInsert(container, container.begin(), container.end() - 1, static_cast<unsigned int>(0));
	if (container.size() % 2)
		straggler = container.back();
	Container a_chain;
	//Container b_chain;
	//for (unsigned int i = 0; i < n_pairs; i++) {
		//a_chain.push_back(container[2 * i]);
		//container.pop_back();
		//b_chain.push_back(container[2 * i + 1]);
		//container.pop_back();
	//}
	//binaryInsert(a_chain, a_chain.begin(), a_chain.end() - 1, static_cast<unsigned int>(16));
	//std::cout << "A chain: ";
	//printContainer(a_chain);
	//std::cout << "B chain: ";
	std::cout << "Container: ";
	printContainer(container);
	//printStraggler(straggler);
	return (a_chain);
}

void PmergeMe::parseInput( int argc, char *argv[] ) {
	if (!argc)
		throw std::invalid_argument("No input");
	for (int i = 0; i < argc; i++) {
		addNumberToContainer( unsortedVector, argv[i] );
		addNumberToContainer( unsortedDeque, argv[i] );
	}
	sortedVector = mergeInsertionSort( unsortedVector );
	sortedDeque = mergeInsertionSort( unsortedDeque );
}
