#!/bin/python
from lekser import *



if __name__ == "__main__":
    c()
    with open("test.c") as f:
        ulaz = f.read()
    
    tokeni = leksiranje(ulaz)
    if tokeni == None:
        exit(1)
    print(tokeni)
