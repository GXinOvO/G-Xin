#!/bin/bash 
read a
if [[ $a -gt 10 ]]; then
    echo "a is greater than 10"
elif [[ $a -le 5 ]]; then
    echo "a is less than or equal 5"
else 
    echo "a is greater than 5 and less than 10 or equal to 10"
fi
