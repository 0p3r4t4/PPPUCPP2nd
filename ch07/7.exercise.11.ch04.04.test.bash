#!/bin/bash

# If executing
#   ./7.exercise.11.ch04.04.test.bash | grep -v LIE | cut -f2 | sort -u | wc -l
# returns 100, we know each number from 1 to 100 is reachable on 8 answers

for i in {y,n}{y,n}{y,n}{y,n}{y,n}{y,n}{y,n}{y,n}; do
    result=$(echo $i | ./a.out 2>&1 | tail -n2 | grep -o '[0-9]*\|LIE' | paste - -)
    echo -e "$i\t$result"
done

