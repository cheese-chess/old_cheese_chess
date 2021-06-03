#!/bin/sh

gcc -DCHEESE_ALGO_AA2006 -Wall $(find . -name "*.c") -Iinclude -Llib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Ofast -o cheese
