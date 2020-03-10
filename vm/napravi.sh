#!/bin/bash
gcc -c *.c && gcc *.o -O0 -o izlaz && rm -f *.o
