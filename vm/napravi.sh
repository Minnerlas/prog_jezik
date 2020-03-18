#!/bin/bash
gcc -c *.c && gcc *.o -O0 -o cvm && rm -f *.o
