#!/bin/bash

#bigdiffer by Weston Dransfield
#runs a.out and combines equivilent .tbl files into one and reports results in results.txt

if [ ! -f a.out ]; then
    echo "Please compile as a.out"
    exit
fi

echo processing equivilent functions
rm results.txt *.tbl *.fnl

./a.out 0 50 50 0

touch results.txt

for i in *.tbl; do
    echo .
    for j in *.tbl; do
            if [ "$i" != "$j" ]
                then
                    DIFF=$(diff $i $j)
                    if [ "$DIFF" == "" ]
                        then
                            FIRST=`echo "$i" | cut -d'.' -f1`
                            SECOND=`echo "$j" | cut -d'.' -f1`
                            echo "moving $FIRST and $SECOND"
                            mv $i "$FIRST and $SECOND.fnl"
                            echo "$FIRST <----> $SECOND" >> results.txt
   
                            rm $i $j
                            break
                    fi
            fi
    done
done