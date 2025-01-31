/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:43:14 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/31 17:17:55 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void PmergeMe::printOutput( void ) const {
	std::cout << "Time to process a range of "
		<< vector_numbers.size() << " elements with std::vector: "
		<< time_to_process_vector << "us, "
		<< n_comparisons_vector << " comparisons" <<	std::endl;
	std::cout << "Time to process a range of "
		<< deque_numbers.size() << " elements with std::deque: "
		<< time_to_process_deque << "us, "
		<< n_comparisons_deque << " comparisons" <<	std::endl;
}

int	main( int argc, char *argv[] ) {
	try {
		PmergeMe sorter = PmergeMe();
		sorter.parseInput(argc - 1, argv + 1);
		std::cout << "Before: ";
		sorter.printContainerByString( "vector" );
		sorter.mergeInsertionWrapper( "vector" );
		sorter.mergeInsertionWrapper( "deque" );
		std::cout << "After: ";
		sorter.printContainerByString( "vector" );
		sorter.printOutput();
	}
	catch ( std::exception &e ) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
