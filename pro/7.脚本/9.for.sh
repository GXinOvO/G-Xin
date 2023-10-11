#!/bin/bash
for x in `ls`; do
    echo ${x}
done

for i in a b c d e; do
    echo $i
done

for j in 1 2 3 4 5 6; do
    echo $j
done

for i in `seq 0 2000000`; do
    echo $i
done
