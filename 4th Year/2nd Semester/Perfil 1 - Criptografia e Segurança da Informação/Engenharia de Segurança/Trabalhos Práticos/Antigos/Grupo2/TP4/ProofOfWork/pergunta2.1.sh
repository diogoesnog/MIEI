#!/bin/bash


NUM=2
while [ $NUM -lt 6 ]; do
    echo "Mining blocks with difficulty " $NUM
    time node main.pergunta2.1.js $NUM
    let NUM=NUM+1
done
