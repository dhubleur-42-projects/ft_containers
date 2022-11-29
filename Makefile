# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 16:31:24 by dhubleur          #+#    #+#              #
#    Updated: 2022/11/23 17:03:17 by dhubleur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
INCLUDES = -I./includes

VECTOR_FT_NAME = vector_ft
VECTOR_STD_NAME = vector_std
VECTOR_SRC = srcs/vector_main.cpp

all: vector stack map subject
all_compare: vector_compare stack_compare map_compare

$(VECTOR_FT_NAME): $(VECTOR_SRC)
	$(CXX) $(INCLUDES) $(CXXFLAGS) -D TEST_SRC=ft $(VECTOR_SRC) -o $(VECTOR_FT_NAME)

$(VECTOR_STD_NAME): $(VECTOR_SRC)
	$(CXX) $(INCLUDES) $(CXXFLAGS) -D TEST_SRC=std $(VECTOR_SRC) -o $(VECTOR_STD_NAME)

vector: $(VECTOR_FT_NAME) $(VECTOR_STD_NAME)

vector_compare: $(VECTOR_FT_NAME) $(VECTOR_STD_NAME)
	@./$(VECTOR_FT_NAME) > ft.log
	@./$(VECTOR_STD_NAME) > std.log
	@echo "--------- Vector diff ---------"
	diff ft.log std.log
	@rm ft.log std.log


STACK_FT_NAME = stack_ft
STACK_STD_NAME = stack_std
STACK_SRC = srcs/stack_main.cpp

$(STACK_FT_NAME): $(STACK_SRC)
	$(CXX) $(INCLUDES) $(CXXFLAGS) -D TEST_SRC=ft $(STACK_SRC) -o $(STACK_FT_NAME)

$(STACK_STD_NAME): $(STACK_SRC)
	$(CXX) $(INCLUDES) $(CXXFLAGS) -D TEST_SRC=std $(STACK_SRC) -o $(STACK_STD_NAME)

stack: $(STACK_FT_NAME) $(STACK_STD_NAME)

stack_compare: $(STACK_FT_NAME) $(STACK_STD_NAME)
	@./$(STACK_FT_NAME) > ft.log
	@./$(STACK_STD_NAME) > std.log
	@echo "--------- Stack diff ---------"
	diff ft.log std.log
	@rm ft.log std.log

MAP_FT_NAME = map_ft
MAP_STD_NAME = map_std
MAP_SRC = srcs/map_main.cpp

$(MAP_FT_NAME): $(MAP_SRC)
	$(CXX) $(INCLUDES) $(CXXFLAGS) -D TEST_SRC=ft $(MAP_SRC) -o $(MAP_FT_NAME)

$(MAP_STD_NAME): $(MAP_SRC)
	$(CXX) $(INCLUDES) $(CXXFLAGS) -D TEST_SRC=std $(MAP_SRC) -o $(MAP_STD_NAME)

map: $(MAP_FT_NAME) $(MAP_STD_NAME)

map_compare: $(MAP_FT_NAME) $(MAP_STD_NAME)
	@./$(MAP_FT_NAME) > ft.log
	@./$(MAP_STD_NAME) > std.log
	@echo "--------- Map diff ---------"
	diff ft.log std.log
	@rm ft.log std.log

SUBJECT_NAME = subject_main
SUBJECT_SRC = srcs/subject_main.cpp

$(SUBJECT_NAME): $(SUBJECT_SRC)
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(SUBJECT_SRC) -o $(SUBJECT_NAME)

subject: $(SUBJECT_NAME)


SET_FT_NAME = set_ft
SET_STD_NAME = set_std
SET_SRC = srcs/set_main.cpp

$(SET_FT_NAME): $(SET_SRC)
	$(CXX) $(INCLUDES) $(CXXFLAGS) -D TEST_SRC=ft $(SET_SRC) -o $(SET_FT_NAME)

$(SET_STD_NAME): $(SET_SRC)
	$(CXX) $(INCLUDES) $(CXXFLAGS) -D TEST_SRC=std $(SET_SRC) -o $(SET_STD_NAME)

set: $(SET_FT_NAME) $(SET_STD_NAME)

set_compare: $(SET_FT_NAME) $(SET_STD_NAME)
	@./$(SET_FT_NAME) > ft.log
	@./$(SET_STD_NAME) > std.log
	@echo "--------- Set diff ---------"
	diff ft.log std.log
	@rm ft.log std.log

bonus: all set
bonus_compare: all_compare set_compare

clean:
	rm -f $(VECTOR_FT_NAME) $(VECTOR_STD_NAME) $(STACK_FT_NAME) $(STACK_STD_NAME) $(MAP_FT_NAME) $(MAP_STD_NAME) $(SET_FT_NAME) $(SET_STD_NAME) $(SUBJECT_NAME)

fclean: clean

re: clean
	$(MAKE) all