#!/bin/bash

RED="\e[31m"
GREEN="\e[32m"
RESET="\e[0m"

include_dir="include"
logfile="log_iso_standard.txt"

iso_standard()
{
    # creating main
    echo '

    // utility
    #include "ft_pair.hpp"
    #include "rb_tree.hpp"

    // containers
    #include "ft_map.hpp"
    #include "ft_vector.hpp"
    #include "ft_stack.hpp"

    // algorithms
    #include "ft_equal.hpp"
    #include "ft_lexicographical_compare.hpp"

    // iterators
    #include "ft_type_traits.hpp"
    #include "ft_iterator_base_types.hpp"

    // traits
    #include "ft_type_traits.hpp"

    int main() { return 0; }
    ' > main.cpp

    # compiling + eventually create logfile
	c++ -std=c++98 -Wall -Wextra -fsyntax-only \
    -I $include_dir \
    -I $include_dir/containers \
    -I $include_dir/algorithms \
    -I $include_dir/iterators \
    -I $include_dir/utility \
    main.cpp 1>/dev/null 2>$logfile

    # check success/failure
    if [ $? -ne 0 ]; then
        echo -e "${RED}ERROR${RESET} ft_containers doesn't compile with c++98 standard (cf. ${logfile})..."
        rm main.cpp
        return 1
    else
        echo -e "${GREEN}SUCESS${RESET} ft_containers compile with c++98 standard!"
        rm $logfile
        rm main.cpp
        return 0
    fi
}

iso_standard
