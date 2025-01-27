/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:43:14 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/27 10:49:01 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

//	static helper functions

static void initTimeStruct( struct tm *input ) {
	input->tm_year = 0;
	input->tm_mon = 0;
	input->tm_mday = 0;
	input->tm_hour = 0;
	input->tm_min = 0;
	input->tm_sec = 0;
	input->tm_isdst = -1;
}

static t_cents stringToCents( std::string amount ) {
	size_t decimalPointIndex = amount.find('.');
	t_cents	dollars = atol(amount.c_str());
	t_cents cents = 0;
	if (decimalPointIndex != std::string::npos) {
		if (amount.substr(decimalPointIndex + 1).size() == 1)
			cents = atol(amount.substr(amount.find('.') + 1).c_str()) * 10;
		else
			cents = atol(amount.substr(amount.find('.') + 1).c_str());
	}
	return ((dollars * CENTS_IN_DOLLAR) + cents);
}

const int longMonths[7] = {0, 2, 4, 6, 7, 9, 11};
const int shortMonths[4] = {3, 5, 8, 10};

static bool yearIsLeap( int year ) {
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

static int daysInMonth( int month, int year ) {
	for (int i = 0; i < 12; i++) {
		if (month == 1) {
			if (yearIsLeap(year))
				return (29);
			else
				return (28);
		}
		else if (longMonths[i] == month)
			return (31);
		else if (shortMonths[i] == month)
			return (30);
	}
	throw std::runtime_error("Invalid month");
}

//	Why is month 0-indexed and day is 1-indexed? Weird.
static void checkDateValidity( int year, int month, int day ) {
	//std::cout << "Checking " << year << "-" << month << "-" << day << std::endl;
	if (year < 0)
		throw std::invalid_argument("Invalid year: ");
	else if (day < 1 || day > daysInMonth(month, year))
		throw std::invalid_argument("Invalid day for month");
}

static time_t dateStringToTimestamp( std::string date ) {
	struct tm out;
	initTimeStruct( &out );
	int year = atol(date.substr(0, 4).c_str()) - 1900;
	int month = atol(date.substr(5, 6).c_str()) - 1;
	int day = atol(date.substr(8, 9).c_str());

	checkDateValidity( year, month, day );
	out.tm_year = year;
	out.tm_mon = month;
	out.tm_mday = day;
	return (mktime(&out));	// mktime creates a time_t timestamp from a tm
}

static void parseDataLine( std::string line, CSVdata &data ) {
	static int line_n = 0;

	line_n++;
	if (!isdigit(line[0]))
		return ;
	try {
		//CSVrecord newdata;
		if (line[10] != ',') {
			std::cout << "Error in line " << line_n << ": ";
			throw std::invalid_argument("Malformed date in CSV file");
		}
		data[dateStringToTimestamp(line.substr(0, 10))] = stringToCents(line.substr(11));
	}
	catch ( std::exception &e ) {
		std::cout << "Error on line " << line_n << ": " << e.what() << std::endl;
	}
}

static std::string printDollars( t_cents amount ) {
	std::stringstream s;
	unsigned int dollars = amount / CENTS_IN_DOLLAR;
	unsigned int cents = amount - (dollars * CENTS_IN_DOLLAR);
	s << dollars << "." << std::fixed << std::setw(2) << std::setfill('0') << cents;
	return (s.str());
}

static std::string printTimestamp( const time_t &time ) {
	char output[50];
	struct tm datetime;
	datetime = *localtime(&time);
	strftime(output, 50, "%Y-%m-%d", &datetime);
	return (std::string(output));
}

//	Debug function to check CSV data stored correctly
//static void printCSVData( const CSVdata &data ) {
	//std::cout << "Printing stored CSV data:" << std::endl;
	//for (CSVdata::const_iterator it = data.begin(); it != data.end(); it++) {
		//std::cout << printTimestamp(it->first) << "," << printDollars(it->second) << std::endl;
	//}
//}

//	Constructor / Destructors

BitcoinExchange::BitcoinExchange( const char *data ) {
	std::ifstream	ifs;
	std::string		line;
	ifs.open(data);
	while (getline(ifs, line))
		parseDataLine(line, this->data);
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange& other ) {
	this->data = other.data;
}

BitcoinExchange &BitcoinExchange::operator=( const BitcoinExchange& other ) {
	if (this != &other)
		this->data = other.data;
	return *this;
}

BitcoinExchange::~BitcoinExchange( void ) {}

//	Member functions

CSVdata::const_iterator BitcoinExchange::getNearestRecord( const time_t &date ) const{
	CSVdata::const_iterator found = data.begin();
	for (CSVdata::const_iterator it = data.begin(); it != data.end(); it++) {
		if (it->first > date)
			break ;
		found = it;
	}
	return (found);
}

void BitcoinExchange::processInput( std::string line ) const {
	if (!isdigit(line[0]))
		return ;
	time_t	date = dateStringToTimestamp(line.substr(0, 10));
	int		value = atof(line.substr(13).c_str());
	if (value < 0)
		throw (std::invalid_argument("Error: not a positive number"));
	if (value > 1000)
		throw (std::invalid_argument("Error: too large a number"));
	std::cout << printTimestamp(date) << " => " << value << " = " << printDollars(getNearestRecord(date)->second * value) << std::endl;
}
