#!/bin/bash

display_csv()
{
    # TODO
    # bold first line
    # red when KO and green when OK
    # ratio: +10.34% | -22.42% (light green/red)
    if [ -f timing.csv ]; then
        column -t -s, -n timing.csv | less -F -S -X -K -r
    fi
}

display_csv
