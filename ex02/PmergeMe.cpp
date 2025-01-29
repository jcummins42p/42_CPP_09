/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:43:14 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/29 20:26:58 by jcummins         ###   ########.fr       */
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

template <typename Container>
static bool checkSorted( const Container &container ) {
	unsigned int previous = container.front();
	for (typename Container::const_iterator it = container.begin(); it != container.end(); it++) {
		if (previous > *it) {
			std::cout << "Container is NOT sorted" << std::endl;
			return (false);
		}
		previous = *it;
	}
	std::cout << "Container is sorted" << std::endl;
	return (true);
}

static void printRecursionLevel( unsigned int recursion_level, std::string stage ) {
	std::cout << std::endl << "> After Level " << recursion_level
		<< " (" << stage << " - size " << pow(2, recursion_level) << "):" << std::endl;
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
		else
			std::cout << ", " << *it++;
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
	while (start < end) {
		dest.push_back(source[start]);
		source.erase(source.begin() + start);
		end--;
	}
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
static Container createPend(Container &main, unsigned int elementSize)
{
	Container pend;
	for (int i = 2; (i + 1) * elementSize < main.size(); i++) {
		moveToContainerFromRange(main, pend, i * elementSize, (i + 1) * elementSize);
	}
	std::cout << "Created pend: ";
	printContainer(pend, elementSize);
	std::cout << "New main: ";
	printContainer(main, elementSize);
	return (pend);
}

//	just handles the insertion of an element in the existing container
//	call this from the binary function when the destination index is found
template <typename Container>
static void insertElement(
		Container &target,
		Container &source,
		unsigned int target_i,
		unsigned int source_i,
		unsigned int elementSize)
{
	for (unsigned int i = 0; i < elementSize; i++) {
		target.insert(target.begin() + target_i + i, source[source_i + i]);
	}
}

//	use this to compare elements in the binary insert function
//	takes the element iterators and returns true if they need to be swapped
template <typename Container>
static bool compareElements(
		const Container &main,
		const Container &pend,
		unsigned int src,
		unsigned int dst,
		unsigned int elementSize )
{
	return ((pend[src + elementSize - 1])
			< (main[dst + elementSize - 1]) ? true : false);
}

//	Write binary insertion sort that works with indices of element starts + element sizes
template <typename Container>
static unsigned int binaryElementInsert(
		Container &target,
		Container &source,
		unsigned int L,	// defining left and right bounds
		unsigned int R,
		unsigned int elementSize,
		unsigned int src_i) // we don't yet have a dest - we are finding it
{
	unsigned int M = L + (R - L) / 2;

	if (L == R || (M % elementSize)) {
		std::cout << "Inserting element ending " << source[src + elementSize - 1]
			<< " before element ending " << target[L + elementSize - 1] << std::endl;
		insertElement(target, source, L, src_i, elementSize);
		printContainer( container, elementSize);
		return (0);
	}
	else if (compareElements(container, src_i, M, elementSize))
		return 1 + binaryElementInsert(container, L, M, elementSize, src_i);
	else
		return 1 + binaryElementInsert(container, M + elementSize, R, elementSize, src_i);
}

template <typename Container>
static unsigned int compareElementsInsert(Container &container, unsigned int elementSize)
{
	unsigned int comparisons = 0;
	unsigned int totalChunks = container.size() / elementSize;
	unsigned int currJacobsthal = PmergeMe::genJacobsthal(0);
	unsigned int prevJacobsthal = PmergeMe::genJacobsthal(-1);
	Container pend = createPend(container, elementSize);

	//	ordered insertion following jacobstahl sequence
	for (unsigned int i = 0; currJacobsthal < totalChunks; i++) {
		while (currJacobsthal > prevJacobsthal) {
			if (currJacobsthal * elementSize < pend.size()) {
				comparisons += binaryElementInsert(container, 0, src, elementSize, src);
//need to fix this								 								
			}
			currJacobsthal--;
		}
		prevJacobsthal = currJacobsthal;
		currJacobsthal = PmergeMe::genJacobsthal(i + 1);
	}
	//	ordered insertion without jacobsthal sequence
	while (!pend.empty()) {
		binaryElementInsert(container, 0, src, elementsSize, src);
	}
	return (comparisons);
}

template <typename Container>
static unsigned int insertionStep(Container &container, unsigned int recursion_level)
{
	unsigned int elementSize = pow(2, recursion_level);
	unsigned int insert_comparisons = 0;
	if (elementSize > container.size())
		return (insert_comparisons);
	printRecursionLevel(recursion_level, "insertion");
   	printContainer(container, elementSize);
	insert_comparisons += compareElementsInsert(container, elementSize);
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
		const unsigned int &elementSize)
{
	const unsigned int comp = index + elementSize;
	//	We need to compare the last element before the next index because that is already sorted
	if (container[index + elementSize - 1] > container[comp + elementSize - 1])
		swapElements(container, index, comp);
	return (1);
}

template <typename Container>
static unsigned int mergeInsertionSort( Container &container, const unsigned int recursion_level ) {
	unsigned int comparisons = 0;
	const unsigned int elementSize = pow(2, recursion_level);

	if (elementSize > container.size())
		return (comparisons);
	for (unsigned int i = 0; i + elementSize <= container.size(); i += elementSize) {
		comparisons += compareElementsSwap(container, i, elementSize / 2);	// makes and executes comparisons
	}
	printRecursionLevel( recursion_level, "pair sort" );
   	printContainer(container, elementSize);
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
		//vector_numbers.insert(vector_numbers.end(), 1); // to prove checker works
		checkSorted(vector_numbers);
	}
	else if (select == "deque") {
		comparisons = mergeInsertionSort(deque_numbers, 1);
		//deque_numbers.insert(deque_numbers.end(), 1);	// to prove checker works
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
