/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:43:14 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/31 16:04:52 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//	constructor
PmergeMe::PmergeMe( void ) {
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

static void debugPrint( const std::string &message) {
	if (DB_OUTPUT > DB_NONE)
		std::cout << message << std::endl;
}

template <typename Container>
static bool checkSorted( const Container &container ) {
	unsigned int previous = container.front();
	for (typename Container::const_iterator it = container.begin(); it != container.end(); it++) {
		if (previous > *it) {
			debugPrint("Container is NOT sorted");
			return (false);
		}
		previous = *it;
	}
	debugPrint("Container is sorted");
	return (true);
}

static void printRecursionLevel( unsigned int recursion_level, std::string stage ) {
	if (DB_OUTPUT >= DB_TEXT) {
		std::cout << std::endl << "> After Level " << recursion_level
		<< " (" << stage << " - size " << pow(2, recursion_level) << "):" << std::endl;
	}
}

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
		if (grouping && (i % grouping == 0))
			std::cout << ")  (" << *it++;
		else if (grouping && (i % (grouping / 2) == 0))
			std::cout << " ~ " << *it++;
		else if (grouping)
			std::cout << ", " << *it++;
		else
			std::cout << " " << *it++;
		i++;
	}
	if (grouping && i % grouping == 0)
		std::cout << ")";
	else if (grouping)
		std::cout << "...";
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
	for (unsigned int k = 0; k < n; k++)
		jacobsthal.push_back(genJacobsthal(k));
}

//	we only ever need the sequence from 3, so n=0 generates 3, etc.
unsigned int PmergeMe::genJacobsthal( int n ) {
	if (n < -2)
		return (0);
	return ((pow(2, n + 3) + pow(-1, n + 2)) / 3);
}

template <typename Container>
static void moveToContainerFromRange(
		Container &source,
		Container &dest,
		unsigned int start,
		unsigned int end)
{
	Container temp(source.begin() + start, source.begin() + end);
	dest.insert(dest.end(), temp.begin(), temp.end());
	source.erase(source.begin() + start, source.begin() + end);
}

template <typename Container>
static Container newContainerFromRange(
		Container &source,
		unsigned int start,
		unsigned int end)
{
	Container out;
	moveToContainerFromRange(source, out, start, end);
	std::cout << "> Created temporary container to move element: ";
	printContainer(out, 0);
	return (out);
}

//	creates pend from all b elements starting b2
template <typename Container>
static Container createPend(Container &main, unsigned int e_size)
{
	Container pend;
	for (int i = 2; (i + 1) * e_size <= main.size(); i++) {
		moveToContainerFromRange(main, pend, i * e_size, (i + 1) * e_size);
	}
	std::cout << "Created pend: ";
	printContainer(pend, e_size);
	std::cout << "New main: ";
	printContainer(main, e_size);
	return (pend);
}

//	creates odd from all b elements starting b2
template <typename Container>
static Container createOdds(Container &main, unsigned int e_size)
{
	Container odds;
	int i = 0;	// i counts through e_size chunks
	while (((i + 2) * e_size) < main.size())	// Skips over all the usable b elements
		i += 2;
	if ((i * e_size) + e_size <= main.size()) { // is there a usable odd element after pairs
		moveToContainerFromRange(main, odds, i * e_size, (i + 1) * e_size);
		std::cout << "Created odd element: ";
		printContainer(odds, e_size);
	}
	return (odds);
}

//	just handles the insertion of an element in the existing container
//	call this from the binary function when the destination index is found
template <typename Container>
static void insertElement(
		Container &target,
		Container &source,
		unsigned int target_i,
		unsigned int source_i,
		unsigned int e_size)
{
	for (unsigned int i = 0; i < e_size; i++) {
		target.insert(target.begin() + target_i + i, source[source_i + i]);
	}
}

//	use this to compare elements in the binary insert function
//	takes the element iterators and returns true if they need to be swapped
template <typename Container>
static bool elementIsLessThan(
		const Container &target,
		const Container &source,
		unsigned int dst,
		unsigned int src,
		unsigned int e_size )
{
	if (target.empty() || source.empty())
		return (false);
	return (source[src + e_size - 1] < target[dst + e_size - 1]);
}

//	Write binary insertion sort that works with indices of element starts + element sizes
template <typename Container>
static unsigned int binaryInsert(
		Container &target,
		Container &source,
		unsigned int L,	// defining left and right bounds
		unsigned int R,
		unsigned int e_size,
		unsigned int src_i) // we don't yet have a dest - we are finding it
{
	unsigned int M = 0;

	if (L >= R) {
		if (DB_OUTPUT >= DB_TEXT) {
			std::cout << "Inserting element ending " << source[src_i + e_size - 1]
				<< " before element ending " << target[L + e_size - 1] << std::endl;
		}
		insertElement(target, source, L, src_i, e_size);
		printContainer( target, e_size);
		return (0);
	}
	M = L + (R - L) / 2;
	M -= M % e_size; // take the lower index that aligns with the start of an element
	if (elementIsLessThan(target, source, M, src_i, e_size))
		return 1 + binaryInsert(target, source, L, M, e_size, src_i);
	else
		return 1 + binaryInsert(target, source, M + e_size, R, e_size, src_i);
}

template <typename Container>
static unsigned int insertionCycle(Container &main, unsigned int e_size)
{
	unsigned int comparisons = 0;
	unsigned int topinserted = 0;
	Container odds = createOdds(main, e_size);
	Container pend = createPend(main, e_size);

	std::cout << "\nBinary insert in jacobsthal order" << std::endl;
	for (unsigned int i = 0; ; i++)
	{
		unsigned int currJacobsthal = PmergeMe::genJacobsthal(i);
		unsigned int prevJacobsthal = PmergeMe::genJacobsthal(i - 1);
		unsigned int target_area = (pow(2, i + 2) - 1) * e_size;
		std::cout << "Inserting between element 0 and " << target_area / e_size << ": ";
		if (target_area > main.size())
			target_area = main.size();
		if ((currJacobsthal - 1) * e_size > pend.size()) {
			std::cout << "Not enough b elements to use jacobsthal #" << currJacobsthal << std::endl;
			break;
		}
		std::cout << "Inserting from element b " << currJacobsthal << std::endl;
		while (currJacobsthal > prevJacobsthal) {
			comparisons += binaryInsert(main, pend, 0, target_area, e_size, ((currJacobsthal - 1) * e_size)- e_size);
			if ((currJacobsthal - 1) * e_size > topinserted)
				topinserted = (currJacobsthal - 1) * e_size;
			currJacobsthal--;
		}
		std::cout << "Main after insertions: ";
		printContainer( main, e_size );
	}
	if (pend.size())
		std::cout << "Binary insert pend in linear order from element " << topinserted / e_size << std::endl;
	while (pend.size() && (topinserted + e_size <= pend.size())) {
		comparisons += binaryInsert(main, pend, 0, main.size() - e_size - (main.size() % e_size), e_size, topinserted);
		topinserted += e_size;
	}
	if (odds.size()) {
		std::cout << "Binary insert odd in linear order " << std::endl;
		comparisons += binaryInsert(main, odds, 0, main.size() - (main.size() % e_size), e_size, 0);
	}
	return (comparisons);
}

template <typename Container>
static unsigned int insertionStep(Container &container, unsigned int recursion_level)
{
	unsigned int e_size = pow(2, recursion_level);
	unsigned int insert_comparisons = 0;
	if (e_size > container.size())
		return (insert_comparisons);
	std::cout << "\nAt recursion level " << recursion_level << ": ";
	//printRecursionLevel(recursion_level, "insertion");
   	printContainer(container, e_size);
	insert_comparisons += insertionCycle(container, e_size);
	std::cout << "After recursion level " << recursion_level << std::endl;
   	printContainer(container, e_size);
	return (insert_comparisons);
}

template <typename Container>
static void swapElements(
		Container &container,
		const unsigned int &index,
		const unsigned int &comp)
{
	if (index + (comp - index) > container.size())
		throw std::invalid_argument("Swap pair arguments out of range");
	for (int i = 0; i + index < comp; i++)
		std::swap(container[index + i], container[comp + i]);
}

template <typename Container>
static int compareElementsSwap(
		Container &container,
		const unsigned int &index,
		const unsigned int &e_size)
{
	const unsigned int comp = index + e_size;
	//	We need to compare the last element before the next index because that is already sorted
	if (container[index + e_size - 1] > container[comp + e_size - 1])
		swapElements(container, index, comp);
	return (1);
}

template <typename Container>
static unsigned int mergeInsertionSort( Container &container, const unsigned int recursion_level ) {
	unsigned int comparisons = 0;
	const unsigned int e_size = pow(2, recursion_level);

	if (e_size > container.size())
		return (comparisons);
	for (unsigned int i = 0; i + e_size <= container.size(); i += e_size) {
		comparisons += compareElementsSwap(container, i, e_size / 2);	// makes and executes comparisons
	}
	printRecursionLevel( recursion_level, "pair sort" );
   	printContainer(container, e_size);
	comparisons += mergeInsertionSort(container, recursion_level + 1);
	comparisons += insertionStep(container, recursion_level - 1);
	return (comparisons);
}

//	Need to keep track of recursion level to dictate size of sort elements (element_size)
//	element size starts by sorting pairs (1 element size) and doubles with each recursion call
void PmergeMe::mergeInsertionWrapper( const std::string &select )
{
	unsigned int comparisons = 0;

	std::cout << "\nAttempting to sort " << select << std::endl
			<< "Before Sort: " << std::endl;
	printContainerByString( select );
	if (select == "vector") {
		comparisons = mergeInsertionSort(vector_numbers, 1);
		checkSorted(vector_numbers);
	}
	else if (select == "deque") {
		comparisons = mergeInsertionSort(deque_numbers, 1);
		checkSorted(deque_numbers);
	}
	else
		throw std::invalid_argument("Called sort on invalid container type");
	printContainerByString(select);
	std::cout << "Number of comparisons has been " << comparisons << std::endl;
}

void PmergeMe::parseInput( int argc, char *argv[] ) {
	if (!argc)
		throw std::invalid_argument("No input");
	for (int i = 0; i < argc; i++) {
		addNumberToContainer( vector_numbers, argv[i] );
		addNumberToContainer( deque_numbers, argv[i] );
	}
}
