#!/bin/bash

RED="\e[31m"
GREEN="\e[32m"
RESET="\e[0m"

time_command="time" # go `man -f time` and enjoy some reading

record_execution_time ()
{
    { time "./$1"; } 2>&1 >/dev/null | grep user | awk -F "m" '{ print $2 }'
}

compare_execution_time ()
{
    for ft_bin in bin/timing/ft/* ; do

        std_bin="bin/timing/std/$(basename $ft_bin | sed 's/ft_/std_/')"

        # delete leading `0` (these would denote octal numbers -- but we wan decimal ones!)
        # cf. https://stackoverflow.com/a/52997535
        local ft_time=$(echo  "$(record_execution_time "$ft_bin"  | sed 's/s//' | sed 's/\.//') + 0" | bc)
        local std_time=$(echo "$(record_execution_time "$std_bin" | sed 's/s//' | sed 's/\.//') + 0" | bc)

        local min=$((std_time < ft_time ? std_time : ft_time))
        local max=$((std_time > ft_time ? std_time : ft_time))

        echo "-- $(basename -s .out $ft_bin | sed 's/ft_//') --"

        echo "ft:  $ft_time"
        echo "std: $std_time"

        echo "min: $min"
        echo "max: $max"

        local ratio=$(echo "scale=4; $max/$min" | bc)

        echo -n "ratio: $ratio -- "

        if (( $(echo "$ratio < 20" | bc -l) )); then
            echo -e "${GREEN}OK${RESET}"
        else
            echo -e "${RED}KO${RESET}"
        fi

    done
}

test_cc_version()
{
    echo "
    //#include "ft_type_traits.hpp"
    //#include "ft_bidirectional_iterator.hpp"
    //#include "ft_iterator_base_types.hpp"
    //#include "ft_random_access_iterator.hpp"
    //#include "ft_vector.hpp"
    //#include "ft_lexicographical_compare.hpp"

    //#include <chrono>

    int main() { return 0; } " > main.cpp

	g++ -std=c++98 -Wall -Wextra -fsyntax-only \
    -I include \
    -I include/containers \
    -I include/algorithms \
    -I include/iterators \
    main.cpp 1>/dev/null 2>log_cc_version.txt

    if [ $? -ne 0 ]; then
        echo -e "${RED}ERROR${RESET} ft_containers doesn't compile with c++98 standard (cf. log.txt)..."
        rm main.cpp
        return 1
    else
        echo -e "${GREEN}SUCESS${RESET} ft_containers compile with c++98 standard !"
        rm log_cc_version.txt
        rm main.cpp
        return 0
    fi
}

#if test_cc_version; then
#    echo "0"
#else
#    echo "1"
#fi

test_cc_version
#compare_execution_time
