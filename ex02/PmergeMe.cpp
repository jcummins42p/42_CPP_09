/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:43:14 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/27 21:05:04 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//	constructor
PmergeMe::PmergeMe( void ) :
	vector_comparisons(0),
	deque_comparisons(0) {
	generateJacobsthalSequence( JACOBSTAHL_SIZE );
}

PmergeMe::PmergeMe( const PmergeMe& other ) {
	*this = other;
}

PmergeMe &PmergeMe::operator=( const PmergeMe& other ) {
	if (this != &other)
	{
		this->vector_numbers = other.vector_numbers;
		this->deque_numbers = other.deque_numbers;
	}
	return *this;
}

//	destructor
PmergeMe::~PmergeMe( void ) {}

template <typename T>
static void printContainer( const T &container, unsigned int grouping) {
	if (grouping % 2)
		grouping = 0;
	if (container.size() == 0) {
		std::cout << "Container is empty" << std::endl;
		return;
	}
	typename T::const_iterator it = container.begin();
	if (grouping)
		std::cout << "(";
	std::cout << *it++;
	int i = 1;
	while (it != container.end()) {
		if (grouping && (i++ % grouping == 0))
			std::cout << ")(" << *it++;
		else
			std::cout << ", " << *it++;
	}
	std::cout << std::endl;
}

void PmergeMe::printContainerByString( const std::string &select ) const {
	//std::cout << "Printing " << select << ": " << std::endl;
	if (select == "vector")
		printContainer( vector_numbers, 0 );
	else if (select == "deque")
		printContainer( deque_numbers, 0 );
	else if (select == "jacob")
		printContainer( jacobsthal, 0 );
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
	container.push_back(static_cast<unsigned int>(num));
	arg_n++;
}

//	we only need the numbers starting from '3' in the sequence
void PmergeMe::generateJacobsthalSequence( unsigned int n ) {
	if (jacobsthal.size())
		jacobsthal.clear();
	unsigned long i = 1;
	unsigned long j = 1;
	for (unsigned int k = 2; k < n; k++) {
		jacobsthal.push_back(i * 2 + j);
		i = j;
		j = jacobsthal.back();
	}
}

// returns the number of comparisons made during the insert process
// max comparisons for binary insertion grow by 1 on each next power of 2
template <typename Container, typename T>
static unsigned int recursiveBinaryInsert(
		Container &sorted,
		typename Container::iterator L,
		typename Container::iterator R,
		const T &value)
{
	typename Container::iterator	M = L + (R - L) / 2;

	if (L == R)	{	// Comparing iterators does not count towards comparison total
		if (value < *L)
			sorted.insert(L, value);	// This just indicates that the correct node is found
		else
			sorted.insert(L + 1, value);
		return 1;
	}
	if (value < *M)
		return 1 + recursiveBinaryInsert(sorted, L, M, value);
	else
		return 1 + recursiveBinaryInsert(sorted, M + 1, R, value);
}

template <typename Container, typename T>
static unsigned int binaryInsert(
		Container &sorted,
		typename Container::iterator L,
		typename Container::iterator R,
		const T &value)
{	//	Just a wrapper function for the recursive, to print debug message once
	std::cout << "Doing binary insert of value " << value << " in container ";
	printContainer(sorted, 0);
	return recursiveBinaryInsert(sorted, L, R, value);
}

template <typename Container>
static void swapPairs(
		Container &container,
		const unsigned int &index,
		const unsigned int &comp)
{
	if (index + (comp - index) > container.size())
		throw std::invalid_argument("Swap pair arguments out of range");
	for (int i = 0; i + index < comp; i++)
		std::swap(container[index + i], container[comp + i]);
}

//	Pass the first index of first element, we can deduce the one to compare.
//	Put tests here so that the function can be called without checks. Will always
//	make one comparison, so always returns 1 to increment comparisons.
template <typename Container>
static int comparePairs(
		Container &container,
		const unsigned int &index,
		const unsigned int &pair_size)
{
	const unsigned int comp = index + pair_size;
	//	We need to compare the last element before the next index because that is already sorted
	if (container[index + pair_size - 1] > container[comp + pair_size - 1])
		swapPairs(container, index, comp);
	return (1);
}

template <typename Container>
static unsigned int pairSort( Container &container, const unsigned int pair_size ) {
	unsigned int comparisons = 0;

	if (pair_size > container.size() / 2)
		return (comparisons);
	for (unsigned int i = 0; i + (2 * pair_size) <= container.size(); i += 2 * pair_size) {
		comparisons += comparePairs(container, i, pair_size);	// makes and executes comparisons
	}
	std::cout << "After pair sort (size " << pair_size << "):" << std::endl;
   	printContainer(container, pair_size * 2);
	comparisons += pairSort(container, pair_size * 2);
	return (comparisons);
}

//	Need to keep track of recursion level to dictate size of sort elements (element_size)
//	element size starts by sorting pairs (1 element size) and doubles with each recursion call
void PmergeMe::mergeInsertionSort( const std::string &select )
{
	std::cout << "Attempting to sort " << select << std::endl
			<< "Before Sort: " << std::endl;
	printContainerByString( select );
	if (select == "vector")
		vector_comparisons = pairSort(vector_numbers, PAIRSORT_INIT);
	else if (select == "deque")
		deque_comparisons = pairSort(deque_numbers, PAIRSORT_INIT);
	else {
		std::cout << "\tInvalid container name" << std::endl;
		return;
	}
}

void PmergeMe::parseInput( int argc, char *argv[] ) {
	if (!argc)
		throw std::invalid_argument("No input");
	for (int i = 0; i < argc; i++) {
		addNumberToContainer( vector_numbers, argv[i] );
		addNumberToContainer( deque_numbers, argv[i] );
	}
}
