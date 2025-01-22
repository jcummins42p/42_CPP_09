/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:43:14 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/20 15:18:52 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
	try {
		RPN rpn = RPN(argc - 1, argv + 1);
	}
	catch ( std::exception &e ) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}
