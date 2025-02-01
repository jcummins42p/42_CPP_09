/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:43:14 by jcummins          #+#    #+#             */
/*   Updated: 2025/02/01 11:55:24 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

int main( int argc, char *argv[] ) {
	BitcoinExchange exchange = BitcoinExchange("data.csv");

	if ( argc != 2 ) {
		std::cout << "Please provide a single input file argument" << std::endl;
		return (1);
	}
	std::ifstream	ifs;
	std::string		line;
	ifs.open(argv[1]);
	while (getline(ifs, line)) {
		try {
			exchange.processInput(line);
		}
		catch ( std::exception &e ) {
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
	return (0);
}
