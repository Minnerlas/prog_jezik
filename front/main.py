#!/bin/python
from lekser import *

'''
kval            => 'auto' | 'register' | 'static' |'...' | nista 
tip             => 'char' | 'int' | 'float' | 'double'
dekl            => kval* (signed | unsigned)? tip
argument        => dekl ident
funkcija_def    => 'static'*  (dekl|'void')  ident  '(' (argument)* ')' ';'
'''



if __name__ == "__main__":
    c()
    with open("test.c") as f:
        ulaz = f.read()
    
    tokeni = leksiranje(ulaz)
    if tokeni == None:
        exit(1)
    print(tokeni)
