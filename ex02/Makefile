# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 18:08:59 by jcummins          #+#    #+#              #
#    Updated: 2025/01/31 13:45:40 by jcummins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PmergeMe

CXX = c++
CXXFLAGS = -g -Werror -Wextra -Wall -pedantic -std=c++98

SRCS = main.cpp PmergeMe.cpp
OBJS = $(SRCS:%.cpp=objs/%.o)
DBOBJS = $(SRCS:%.cpp=dbobjs/%.o)
HEADS = PmergeMe.hpp

all: $(NAME)

debug: $(DBOBJS)
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "✅ Linking object files into executable $@"

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "✅ Linking object files into executable $@"

objs/%.o: %.cpp $(HEADS)
	@mkdir -p objs
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "✅ Complied object file $@ from source file $<"

dbobjs/%.o: %.cpp $(HEADS)
	@mkdir -p dbobjs
	@$(CXX) $(CXXFLAGS) -DDB_OUTPUT=2 -c $< -o $@
	@echo "✅ Complied object file $@ from source file $<"

clean:
	@echo "💥 Removing all object files"
	@rm -rf objs dbobjs

fclean: clean
	@echo "💥 Removing executable"
	@rm -f $(NAME) debug
	@rm -f *.out

re:	fclean all

.PHONY: all clean fclean re
