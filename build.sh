#!/bin/sh


# Use value algorithm for now
gcc -DCHEESE_ALGO_VALUE -Wall $(find . -name "*.c") -Iinclude -Llib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Ofast -o cheese
