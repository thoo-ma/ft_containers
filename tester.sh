#!/bin/bash

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

        echo -n "ratio: " ; echo "scale=4; $max/$min" | bc

    done
}

compare_execution_time
