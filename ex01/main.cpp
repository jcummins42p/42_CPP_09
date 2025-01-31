/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:43:14 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/31 16:14:21 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
	RPN rpn = RPN();
	try {
		rpn.processInput(argc - 1, std::string(argv[1]));
	}
	catch ( std::exception &e ) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}
