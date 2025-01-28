/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:43:14 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/28 19:32:30 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main( int argc, char *argv[] ) {
	try {
		PmergeMe sorter = PmergeMe();
		sorter.printContainerByString( "jacob" );
		sorter.parseInput(argc - 1, argv + 1);
		sorter.mergeInsertionWrapper( "vector" );
	}
	catch ( std::exception &e ) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
