#!/bin/bash
read start end
for i in `seq ${start} ${end}`;do
    if [[ $[${i} % 2] -eq 0 ]];then
        echo $i
    fi
done
