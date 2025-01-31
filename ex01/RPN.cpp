/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:43:14 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/31 16:16:56 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static const char validOperators[4] = {'+', '-', '/', '*'};

static bool isValidOperator( char c ) {
	for (int i = 0; i < 4; i++) {
		if (c == validOperators[i])
			return (true);
	}
	return (false);
}

void RPN::selectOperation( char operation ) {
	if (numbers.size() < 2)
		throw std::runtime_error("Insufficient numbers to perform operation");
	int lastval = numbers.top();
	numbers.pop();
	if (operation == '+')
		numbers.top() = numbers.top() + lastval;
	else if (operation == '-')
		numbers.top() = numbers.top() - lastval;
	else if (operation == '*')
		numbers.top() = numbers.top() * lastval;
	else if (operation == '/') {
		if (lastval == 0)
			throw std::runtime_error("Divide by zero error");
		numbers.top() = numbers.top() / lastval;
	}
	else
		throw std::runtime_error("Invalid operator in selectOperation function");
}

void RPN::processArgument( const std::string &arg ) {
	if (arg.empty())
		return;
	int toadd = atol(arg.c_str());
	if (toadd > 9 || toadd < -9)
		throw std::invalid_argument("Single digit numbers only");
	else if (isdigit(arg[0])) {
		//std::cout << "Adding " << arg << " to numbers stack" << std::endl;
		numbers.push(atol(arg.c_str()));
	}
	else if (isValidOperator(arg[0]))
		selectOperation(arg[0]);
	else
		throw std::invalid_argument(arg + ": Invalid character detected");
}

void RPN::displayResult( void ) const {
	if (numbers.size() > 1)
		throw std::runtime_error("Insufficient operators for operands");
	std::cout << numbers.top() << std::endl;
}

RPN::RPN( void ) {}

void RPN::processInput( int argc, std::string arg ) {
	if (argc < 1)
		throw std::invalid_argument("No arguments supplied");
	if (argc == 1) {
		std::stringstream	argstream(arg);
		while (getline(argstream, arg, ' '))
			processArgument(arg);
	}
	else {
		throw std::invalid_argument("Use enclosing \"quotations\", not separate args");
	}
	displayResult();
	numbers.pop();	//	remove the last element so the object can be used again
}

RPN::RPN( const RPN& other )
{
	(void) other;
}

RPN &RPN::operator=( const RPN& other ) {
	if (this != &other)
	{
		(void) other;
	}
	return *this;
}

RPN::~RPN( void ) {}
