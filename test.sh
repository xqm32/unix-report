#!/bin/bash

rm -f a3.txt
rm -f sort.txt

echo -n "[[" >> a3.txt
echo -n "[[" >> sort.txt

start=100
end=1000000

for ((i=start; i<=end; i*=10))
do
    for ((j=i; j<i*10; j+=i))
    do
        echo -n ${j}", " >> a3.txt
        echo -n ${j}", " >> sort.txt
        if [ ${j} -eq ${end} ]; then
            break
        fi
    done
done

echo -n "], [" >> a3.txt
echo -n "], [" >> sort.txt

for ((i=start; i<=end; i*=10))
do
    for ((j=i; j<i*10; j+=i))
    do
        echo "madbc.py: m="${j}
        python madbc.py ${j}

        a3=$(./a3)
        sort=$(./sort)
        
        root_a3=$(echo ${a3}|awk '{print $1}')
        time_a3=$(echo ${a3}|awk '{print $2}')
        root_sort=$(echo ${sort}|awk '{print $1}')
        time_sort=$(echo ${sort}|awk '{print $2}')

        # echo -e "a3="${root_a3}"\nsort="${root_sort}
        # echo -e "diff="$(echo ${root_a3} ${root_sort}|awk '{printf("%lf", $1-$2)}')""

        echo -n "${time_a3}, " >> a3.txt
        echo -n "${time_sort}, " >> sort.txt
        if [ ${j} -eq ${end} ]; then
            break
        fi
    done
done

echo "]]" >> a3.txt
echo "]]" >> sort.txt