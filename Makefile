################### COMPILER ###################################################

CXX				=	g++

CXXFLAGS		=	-std=c++11 -Wall -Wextra# -Wconversion

################### DIRECTORIES ################################################

SRC_DIR 		= 	src
OBJ_DIR 		= 	obj
BIN_DIR 		= 	bin
INC_DIR			=	include

OUTPUT_DIR		=	output
TIMING_DIR		=	timing

CONTAINERS_DIR 	= 	$(INC_DIR)/containers
ALGORITHMS_DIR 	= 	$(INC_DIR)/algorithms
ITERATORS_DIR 	= 	$(INC_DIR)/iterators

INCLUDE			=	-I include \
					-I $(CONTAINERS_DIR) \
					-I $(ALGORITHMS_DIR) \
					-I $(ITERATORS_DIR)

################### HEADERS ####################################################

CONTAINERS 		= 	$(CONTAINERS_DIR)/ft_vector.hpp \
					$(CONTAINERS_DIR)/ft_stack.hpp

ALGORITHMS 		= 	$(ALGORITHMS_DIR)/ft_lexicographical_compare.hpp

ITERATORS 		= 	$(ITERATORS_DIR)/ft_bidirectional_iterator.hpp \
					$(ITERATORS_DIR)/ft_random_access_iterator.hpp \
					$(ITERATORS_DIR)/ft_iterator_base_types.hpp

HEADERS			=	$(CONTAINERS) $(ALGORITHMS) $(ITERATORS)

################### UTILS  #####################################################

RM				=	rm -rf

NAME			=   a.out

################### TRAITS TARGETS  ############################################

obj/traits/%.o:		src/traits/%.cpp $(HEADERS) | obj/traits
					$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

bin/traits/%.out:	obj/traits/%.o | bin/traits
					$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@

################### TIMING TARGETS  ############################################

obj/timing/%.o:		src/timing/%.cpp $(HEADERS) | obj/timing
					$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

bin/timing/%.out:	obj/timing/%.o | bin/timing
					$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@

################### OUTPUT TARGETS #############################################

obj/output/%.o:		src/output/%.cpp $(HEADERS) | obj/output
					$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

bin/output/%.out:	obj/output/%.o | bin/output
					$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@

################### DIRECTORIES TARGETS ########################################

obj/traits:		;	mkdir -p obj/traits

bin/traits:		;	mkdir -p bin/traits

obj/timing:		;	mkdir -p obj/timing

bin/timing:		;	mkdir -p bin/timing

obj/output:		;	mkdir -p obj/output

bin/output:		;	mkdir -p bin/output

################### MAIN TARGETS ###############################################

output_stack:		bin/output/output_stack.out

output_vector:		bin/output/output_vector.out

output:				output_stack output_vector

timing_stack:		bin/timing/timing_stack.out

timing_vector:		bin/timing/timing_vector.out

timing:				timing_stack timing_vector

traits:				bin/traits/is_integral.out

all: 				timing output traits# $(NAME)

################### UTILS TARGETS ##############################################

clean:			;	$(RM) $(OBJ_DIR)

fclean:	clean	;	$(RM) $(BIN_DIR)

re:		fclean all

help:			;	@echo "Usage: make output|timing|all"

.SECONDARY:			# preserve .o files from automatic deletion

.PHONY: 			obj/* bin/* timing output all clean fclean re help
