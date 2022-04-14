#!/bin/bash

containers_dir="../.."
time_command="" # go `man -f time` and enjoy some reading
cc="g++"

# WE NEED A MAKEFILE
# WE NEED A MAKEFILE
# WE NEED A MAKEFILE
# WE NEED A MAKEFILE

compile ()
{

    if [ "$1" == "std" ]; then
        g++ -D STD main.cpp
    elif [ "$1" == "ft" ]; then
        g++ -I $containers_dir/containers -I $containers_dir/iterators -D FT main.cpp
    else
        "Error. file: test.sh, function: compile()"
    fi
}

# new (makefile instead)
#compile ()
#{
#
#    local src="$1"
#    local bin="$2_$1.out"
#    local dir="bin/$1"
#
#    if [ "$2" == "std" ]; then
#        $cc -D STD $src -o $bin
#    elif [ "$2" == "ft" ]; then
#        $cc -D FT \
#            -I $containers_dir/containers \
#            -I $containers_dir/iterators \
#            $src -o $bin
#    else
#        "Error. file: test.sh, function: compile()"
#    fi
#}

record_execution_time () {

    #compile "$1" && { /usr/bin/time ./a.out; }
    compile "$1" && { time ./a.out; } 2>&1 >/dev/null | grep user | awk -F "m" '{ print $2 }'
}

compare_execution_time () {

    # delete leading `0`
    # these would denote octal numbers -- but we wan decimal ones!
    # cf. https://stackoverflow.com/a/52997535
    local std_time=$(echo "$(record_execution_time "std" \
        | sed 's/s//' \
        | sed 's/\.//') \
        + 0" | bc)

    local ft_time=$(echo "$(record_execution_time "ft" \
        | sed 's/s//' \
        | sed 's/\.//') \
        + 0" | bc)

    echo "std: $std_time"
    echo "ft:  $ft_time"

    local min=$((std_time < ft_time ? std_time : ft_time))
    local max=$((std_time > ft_time ? std_time : ft_time))

    echo "min: $min"
    echo "max: $max"

    echo "scale=4; $max/$min" | bc

}

compare_timing () {

    mkdir -p "bin/$1"

   # compile "$1.cpp" "std"
   # compile "$1.cpp" "ft"

}

#compare_timing "constructor" --> makefile
compare_execution_time "constructor"
