/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:44:19 by jcummins          #+#    #+#             */
/*   Updated: 2025/01/24 16:28:04 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <map>
# include <algorithm>
# include <ctime>
# include <cstring>
# include <string>
# include <cstdlib>
# include <bits/stdc++.h>

#define CENTS_IN_DOLLAR 100

typedef unsigned int t_cents;
//typedef std::pair<time_t, t_cents> CSVrecord;
typedef std::map<time_t, t_cents> CSVdata;

class	BitcoinExchange
{
	public:
		BitcoinExchange	( const char *data );
		BitcoinExchange	( const BitcoinExchange &other );
		BitcoinExchange	&operator=( const BitcoinExchange &other );
		~BitcoinExchange ( void );

		void	processInput( std::string line ) const;
		CSVdata::const_iterator getNearestRecord( const time_t &date ) const;
	private:
		CSVdata	data;
} ;

#endif
