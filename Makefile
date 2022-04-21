################################################################################
#                                                                              #
#                   COMPILER                                                   #
#                                                                              #
################################################################################

CXX				=	g++
CXXFLAGS		=	-std=c++11 -Wall -Wextra# -Wconversion

################################################################################
#                                                                              #
#                   DIRECTORIES                                                #
#                                                                              #
################################################################################

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

################################################################################
#                                                                              #
#                   HEADERS                                                    #
#                                                                              #
################################################################################

CONTAINERS 		= 	$(CONTAINERS_DIR)/ft_vector.hpp

ALGORITHMS 		= 	$(ALGORITHMS_DIR)/ft_lexicographical_compare.hpp

ITERATORS 		= 	$(ITERATORS_DIR)/ft_bidirectional_iterator.hpp \
					$(ITERATORS_DIR)/ft_random_access_iterator.hpp \
					$(ITERATORS_DIR)/ft_iterator_base_types.hpp

################################################################################
#                                                                              #
#                   SOURCES                                                    #
#                                                                              #
################################################################################

#TIMING_SRC		=	constructor_by_default.cpp \
#					constructor_by_copy.cpp \
#					constructor_by_fill.cpp \
#					constructor_by_range.cpp \
#					at.cpp \
#					front.cpp \
#					back.cpp \
#					empty.cpp \
#					reserve.cpp \
#					size.cpp \
#					max_size.cpp \
#					capacity.cpp \
#					clear.cpp \
#					push_back.cpp \
#					pop_back.cpp \
#					resize.cpp \
#					swap.cpp \
#					begin.cpp \
#					end.cpp \
#					op_bracket.cpp \
#					op_assign \
#					get_allocator.cpp \
#					op_equal.cpp \
#					op_non_equal.cpp
# 					clear.cpp # tester independamment du constructor clear
# 					insert_by_element.cpp
# 					insert_by_fill.cpp
# 					insert_by_range.cpp
# 					erase_by_position.cpp
# 					erase_by_range.cpp
# 					assign_by_fill.cpp
# 					assign_by_range.cpp
# 					op_less_than.cpp
# 					op_more_than.cpp
# 					op_less_than_equal.cpp
# 					op_more_than_equal.cpp

TIMING_SRC		=	at.cpp

OUTPUT_SRC		=	all.cpp

TIMING_SOURCES	=	$(addprefix src/timing/, $(TIMING_SRC))
OUTPUT_SOURCES	=	$(addprefix src/output/, $(OUTPUT_SRC))

################################################################################
#                                                                              #
#                   OBJECTS                                                    #
#                                                                              #
################################################################################

TIMING_OBJ		=	$(addsuffix .o, $(basename $(TIMING_SRC)))
OUTPUT_OBJ		=	$(addsuffix .o, $(basename $(OUTPUT_SRC)))

TIMING_OBJ_FT	=	$(addprefix obj/timing/ft/ft_,   $(TIMING_OBJ))
TIMING_OBJ_STD	=	$(addprefix obj/timing/std/std_, $(TIMING_OBJ))

TIMING_OBJECTS	=	$(TIMING_OBJ_FT) $(TIMING_OBJ_STD)
OUTPUT_OBJECTS	=	$(addprefix obj/output/, $(OUTPUT_OBJ))

################################################################################
#                                                                              #
#                   BINARIES                                                   #
#                                                                              #
################################################################################

TIMING_BIN		=	$(addsuffix .out, $(basename $(TIMING_SRC)))
OUTPUT_BIN		=	$(addsuffix .out, $(basename $(OUTPUT_SRC)))

TIMING_BIN_FT	=	$(addprefix bin/timing/ft/ft_,   $(TIMING_BIN))
TIMING_BIN_STD	=	$(addprefix bin/timing/std/std_, $(TIMING_BIN))

TIMING_BINARIES	=	$(TIMING_BIN_FT) $(TIMING_BIN_STD)
OUTPUT_BINARIES	=	$(addprefix bin/output/, $(OUTPUT_BIN))

################################################################################
#                                                                              #
#                   UTILS                                                      #
#                                                                              #
################################################################################

RM				=	rm -rf
NAME			=   a.out

################################################################################
#                                                                              #
#                   TARGETS                                                    #
#                                                                              #
################################################################################

################### TIMING TARGETS  ############################################

$(TIMING_OBJ_FT):	$(TIMING_SOURCES) | obj/timing/ft
					$(CXX) $(CXXFLAGS) $(INCLUDE) -D FT -c $< -o $@

$(TIMING_OBJ_STD):	$(TIMING_SOURCES) | obj/timing/std
					$(CXX) $(CXXFLAGS) -D STD -c $< -o $@

$(TIMING_BIN_FT):	$(TIMING_OBJ_FT) | bin/timing/ft
					$(CXX) $(CXXFLAGS) $(INCLUDE) -D FT $< -o $@

$(TIMING_BIN_STD):	$(TIMING_OBJ_STD) | bin/timing/std
					$(CXX) $(CXXFLAGS) -D STD $< -o $@

################### OUTPUT TARGETS #############################################

$(OUTPUT_OBJECTS):	$(OUTPUT_SOURCES) | obj/output
					$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(OUTPUT_BINARIES):	$(OUTPUT_OBJECTS) | bin/output
					$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@

################### DIRECTORIES TARGETS ########################################

obj/timing/ft:
					mkdir -p obj/timing/ft
obj/timing/std:
					mkdir -p obj/timing/std
bin/timing/ft:
					mkdir -p bin/timing/ft
bin/timing/std:
					mkdir -p bin/timing/std

obj/output:
					mkdir -p obj/output
bin/output:
					mkdir -p bin/output

################### MAIN TARGETS ###############################################

timing:				$(TIMING_BINARIES)

output:				$(OUTPUT_BINARIES)

all: 				timing output # $(NAME)

################### UTILS TARGETS ##############################################

help:
					@echo "Usage: make output|timing|all"

clean:
					$(RM) $(OBJ_DIR)

fclean: 			clean
					$(RM) $(BIN_DIR)

re: 				fclean all

################### PHONY FTW ##################################################

.PHONY: 			obj/* bin/* timing output all help clean fclean re
