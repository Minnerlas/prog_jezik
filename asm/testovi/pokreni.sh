#!/bin/bash

../asem $1 -o $1.prg > /dev/null && ../../vm/cvm $1.prg && rm $1.prg

