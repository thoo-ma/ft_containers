#!/bin/bash

cat $1 | column -t -s, | less -F -S -X -K -r