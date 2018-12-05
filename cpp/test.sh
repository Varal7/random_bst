#!/bin/bash
for i in {1..10000}; do
    echo item: $i
    ./test $i
done
