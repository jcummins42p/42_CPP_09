# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 18:08:59 by jcummins          #+#    #+#              #
#    Updated: 2025/01/19 13:56:14 by jcummins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PmergeMe

CXX = c++
CXXFLAGSS = -g -Werror -Wextra -Wall -pedantic -std=c++98

SRCS = main.cpp PmergeMe.cpp
OBJS = $(SRCS:%.cpp=%.o)
HEADS = PmergeMe.hpp

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGSS) $^ -o $@
	@echo "✅ Linking object files into executable $@"

%.o: %.cpp $(HEADS)
	@$(CXX) $(CXXFLAGSS) -c $< -o $@
	@echo "✅ Complied object file $@ from source file $<"

clean:
	@echo "💥 Removing all object files"
	@rm -f $(OBJS)

fclean: clean
	@echo "💥 Removing executable"
	@rm -f $(NAME)
	@rm -f *.out

re:	fclean all

.PHONY: all clean fclean re
