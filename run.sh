#!/bin/bash
make
if [[ $? == 0 ]] 
then
    cd build
    date >> out.log 
    if [[ -z $1 ]] 
    then
       ./hdr.out 2>> out.log
    else 
       ./hdr.out -w $1 -h $2 -f $3 2>> out.log
    fi
    cd ..

    #print todos
    for f in `find . -name "*.cpp"`; do
        out=`cat $f | grep "TODO*"`
        if [[ $? == 0 ]]
        then
            echo "todo in $f :"
            echo "$out"
        fi
    done
fi
