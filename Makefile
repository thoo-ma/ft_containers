# Compiler

CXX				=	g++

CXXFLAGS		=	-std=c++11 -Wall -Wextra # -Wconversion

# Directories

CONTAINERS_DIR 	= 	containers

ALGORITHMS_DIR 	= 	algorithms

ITERATORS_DIR 	= 	iterators

# Headers

CONTAINERS 		= 	$(CONTAINERS_DIR)/ft_vector.hpp

ALGORITHMS 		= 	$(ALGORITHMS_DIR)/ft_lexicographical_compare.hpp

ITERATORS 		= 	$(ITERATORS_DIR)/ft_bidirectional_iterator.hpp \
					$(ITERATORS_DIR)/ft_random_access_iterator.hpp \
					$(ITERATORS_DIR)/ft_iterator_base_types.hpp

# Sources

SRC 			= 	main.cpp

# Executable

NAME			=   a.out

# Targets

all: 				$(NAME)

$(NAME): 			$(SRC) $(CONTAINERS) $(ALGORITHMS) $(ITERATORS)
					$(CXX) $(CXXFLAGS) $(SRC) \
					-I $(CONTAINERS_DIR) \
					-I $(ALGORITHMS_DIR) \
					-I $(ITERATORS_DIR) \
					-o $(NAME)

clean:

fclean: 			clean
					$(RM) $(NAME)

re: 				fclean all

.PHONY : 			all clean fclean re
