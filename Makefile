################### COMPILER ###################################################

CXX				=	c++

CXXFLAGS		=	-std=c++11 -Wall -Wextra -Werror -Wconversion

################### DIRECTORIES ################################################

TEST_DIR 		= 	test
OBJ_DIR 		= 	obj
BIN_DIR 		= 	bin
INC_DIR			=	include

OUTPUT_DIR		=	output
TIMING_DIR		=	timing

CONTAINERS_DIR 	= 	$(INC_DIR)/containers
ALGORITHMS_DIR 	= 	$(INC_DIR)/algorithms
ITERATORS_DIR 	= 	$(INC_DIR)/iterators
UTILITY_DIR		=	$(INC_DIR)/utility

INCLUDE			=	-I include \
					-I $(CONTAINERS_DIR) \
					-I $(ALGORITHMS_DIR) \
					-I $(ITERATORS_DIR) \
					-I $(UTILITY_DIR) \
					-I $(TEST_DIR)

################### HEADERS ####################################################

CONTAINERS 		= 	$(CONTAINERS_DIR)/ft_vector.hpp \
					$(CONTAINERS_DIR)/ft_stack.hpp \
					$(CONTAINERS_DIR)/ft_map.hpp

ALGORITHMS 		= 	$(ALGORITHMS_DIR)/ft_lexicographical_compare.hpp

ITERATORS 		= 	$(ITERATORS_DIR)/ft_iterator_base_types.hpp \
					$(ITERATORS_DIR)/ft_reverse_iterator.hpp

UTILITY			=	$(UTILITY_DIR)/ft_pair.hpp \
					$(UTILITY_DIR)/rb_tree.hpp

HEADERS			=	$(CONTAINERS) $(ALGORITHMS) $(ITERATORS) $(UTILITY)

################### UTILS  #####################################################

RM				=	rm -rf

NAME			=   a.out

################### TRAITS TARGETS  ############################################

obj/traits/%.o:		test/traits/%.cpp $(HEADERS) | obj/traits
					$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

bin/traits/%.out:	obj/traits/%.o | bin/traits
					$(CXX) $(CXXFLAGS) $< -o $@

################### TIMING TARGETS  ############################################

obj/timing/%.o:		test/timing/%.cpp $(HEADERS) | obj/timing
					$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

bin/timing/%.out:	obj/timing/%.o | bin/timing
					$(CXX) $(CXXFLAGS) $< -o $@

################### OUTPUT TARGETS #############################################

obj/output/%.o:		test/output/%.cpp $(HEADERS) | obj/output
					$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

bin/output/%.out:	obj/output/%.o | bin/output
					$(CXX) $(CXXFLAGS) $< -o $@

################### DIRECTORIES TARGETS ########################################

obj/traits:		;	mkdir -p obj/traits

bin/traits:		;	mkdir -p bin/traits

obj/timing:		;	mkdir -p obj/timing

bin/timing:		;	mkdir -p bin/timing

obj/output:		;	mkdir -p obj/output

bin/output:		;	mkdir -p bin/output

################### MAIN TARGETS ###############################################

output_tree:		bin/output/output_rb_tree.out

output_pair:		bin/output/output_pair.out

output_map:			bin/output/output_map.out

output_stack:		bin/output/output_stack.out

output_vector:		bin/output/output_vector.out

output:				output_stack output_vector output_map# output_pair

timing_map:			bin/timing/timing_map.out

timing_stack:		bin/timing/timing_stack.out

timing_vector:		bin/timing/timing_vector.out

timing:				timing_stack timing_vector timing_map

traits:				bin/traits/is_integral.out

all: 				timing output traits# $(NAME)

################### UTILS TARGETS ##############################################

clean:			;	$(RM) $(OBJ_DIR)

fclean:	clean	;	$(RM) $(BIN_DIR) *.csv

re:		fclean all

help:			;	@echo "Usage: make output|timing|all"

.SECONDARY:			# preserve .o files from automatic deletion

.PHONY: 			obj/* bin/* timing output all clean fclean re help
