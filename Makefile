################################################################################
#                                                                              #
#                   COMPILER                                                   #
#                                                                              #
################################################################################

CXX				=	g++
CXXFLAGS		=	-std=c++11 -Wall -Wextra # -Wconversion

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

TIMING_SOURCES	=	$(addprefix $(SRC_DIR)/,$(addprefix timing/,$(TIMING_SRC)))
OUTPUT_SOURCES	=	$(addprefix $(SRC_DIR)/,$(addprefix output/,$(OUTPUT_SRC)))

################################################################################
#                                                                              #
#                   OBJECTS                                                    #
#                                                                              #
################################################################################

TIMING_OBJ		=	$(addsuffix .o, $(basename $(TIMING_SRC)))
OUTPUT_OBJ		=	$(addsuffix .o, $(basename $(OUTPUT_SRC)))

TIMING_OBJECTS	=	$(addprefix $(OBJ_DIR)/,$(addprefix timing/,$(TIMING_OBJ)))
OUTPUT_OBJECTS	=	$(addprefix $(OBJ_DIR)/,$(addprefix output/,$(OUTPUT_OBJ)))

################################################################################
#                                                                              #
#                   BINARIES                                                   #
#                                                                              #
################################################################################

TIMING_BIN		=	$(addsuffix .out, $(basename $(TIMING_SRC)))
OUTPUT_BIN		=	$(addsuffix .out, $(basename $(OUTPUT_SRC)))

TIMING_BINARIES	=	$(addprefix $(BIN_DIR)/,$(addprefix timing/,$(TIMING_BIN)))
OUTPUT_BINARIES	=	$(addprefix $(BIN_DIR)/,$(addprefix output/,$(OUTPUT_BIN)))

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

debug:
#					@echo "TIMING_SRC: " $(TIMING_SRC)
#					@echo "TIMING_OBJ: " $(TIMING_OBJ)
#					@echo "TIMING_BIN: " $(TIMING_BIN)
#					@echo "TIMING_SOURCES: " $(TIMING_SOURCES)
#					@echo "TIMING_OBJECTS: " $(TIMING_OBJECTS)
#					@echo "TIMING_BINARIES: " $(TIMING_BINARIES)
#					@echo $(ITERATORS)
#					@echo $(foreach header, $(ITERATORS), $(addprefix iterators/, $(header)))
#					$( join()) !!!


################### TIMING TESTS ###############################################

#$(OBJ_DIR)/$(TIMING_DIR)/%.o: $(SRC_DIR)/$(TIMING_DIR)/%.cpp
obj/timing/%.o:		src/timing/%.cpp
					$(CXX) $(CXXFLAGS) $(INCLUDE) -D STD -c $< \
					-o $(addprefix $(dir $@)std/, $(addprefix std_, $(notdir $@)))
					$(CXX) $(CXXFLAGS) $(INCLUDE) -D  FT -c $< \
					-o $(addprefix $(dir $@)ft/,  $(addprefix ft_,  $(notdir $@)))

#$(BIN_DIR)/$(TIMING_DIR)/%.o: $(OBJ_DIR)/$(TIMING_DIR)/%.cpp
bin/timing/%.out:	obj/timing/%.o
					$(CXX) $(CXXFLAGS) $(INCLUDE) -D STD \
					$(addprefix $(dir $<)std/, $(addprefix std_, $(notdir $<))) \
					-o $(addprefix $(dir $@)std/, $(addprefix std_, $(notdir $@)))
					$(CXX) $(CXXFLAGS) $(INCLUDE) -D FT \
					-o $(addprefix $(dir $@)ft/,  $(addprefix ft_,  $(notdir $@))) \
					$(addprefix $(dir $<)ft/, $(addprefix ft_, $(notdir $<)))

################### OUTPUT TESTS ###############################################

obj/output/%.o:		src/output/%.cpp
					$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< \
					-o $(addprefix obj/output/, $(notdir $@))

bin/output/%.out:	obj/output/%.o
					$(CXX) $(CXXFLAGS) $(INCLUDE) $< \
					-o $(addprefix bin/output/, $(notdir $@))

################### TARGETS ####################################################

# cf.
# https://www.gnu.org/software/make/manual/html_node/Target_002dspecific.html
output_dirs:
					mkdir -p $(OBJ_DIR)/output/
					mkdir -p $(BIN_DIR)/output/

timing_dirs:
					mkdir -p $(OBJ_DIR)/timing/ft
					mkdir -p $(OBJ_DIR)/timing/std
					mkdir -p $(BIN_DIR)/timing/ft
					mkdir -p $(BIN_DIR)/timing/std

#test "output" : dir "obj" "output"
#test "timing" : dir "obj" "timing"

timing:				timing_dirs | $(TIMING_OBJECTS) $(TIMING_BINARIES)
output:				output_dirs | $(OUTPUT_OBJECTS) $(OUTPUT_BINARIES)

all: 				timing output
#all: 				$(NAME)

help:
					@echo "Usage: make output|timing|all"

clean:
					$(RM) $(OBJ_DIR)

fclean: 			clean
					$(RM) $(BIN_DIR)

re: 				fclean all

.PHONY: 			all clean fclean re help directories
