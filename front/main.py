#!/bin/python
from lekser import *
from izrazi import *
from tokeni import TipTokena

tab = 2*" "

tipovi = {
        TipTokena.INT,
        }

const = {
        TipTokena.CB,
        }

unarni = {
        TipTokena.NEG,
        TipTokena.UZV,
        TipTokena.MINUS,
        }


def dbgprint(*args, **kwargs):
    #print(*args, **kwargs)
    #print("\n")
    pass


def parse_program(tokeni):
    dbgprint("prg: ", tokeni)
    t = parse_function(tokeni)
    if t == None:
        return None
    else:
        return (TipAst.prog, t)

def parse_function(tokeni):
    dbgprint("fun: ", tokeni)
    global tipovi
    tr = tokeni[0]
    if len(tokeni)<7:
        return None
    if tr[0] not in tipovi:
        return None
    if tokeni[1][0] != TipTokena.IDENT:
        return None

    if tokeni[2][0] != TipTokena.LEVAZAG or tokeni[3][0] != TipTokena.DESNAZAG:
        return None

    if tokeni[4][0] != TipTokena.LEVAVIT or tokeni[-1][0] != TipTokena.DESNAVIT:
        return None

    t = parse_statement(tokeni[4+1:-1])
    if t == None:
        return None

    return (TipAst.fun_decl, tokeni[1], t)

def parse_statement(tokeni):
    dbgprint("sta: ", tokeni)
    global tipovi
    if len(tokeni)<3:
        return None
    if tokeni[0][0] != TipTokena.RETURN:
        return None
    if tokeni[-1][0] != TipTokena.TZ:
        return None
    
    t = parse_exp(tokeni[1:-1])
    if t == None:
        return None

    return (TipAst.statement, Return(t))

def parse_exp(tokeni):
    dbgprint("exp: ", tokeni)
    global const
    global unarni
    if tokeni[0][0] in const:
        return (TipAst.exp, Const(tokeni[0]))
    else:
        return None

def parse_unary_op(tokeni):
    global unarni
    if tokeni[0][0] in unarni:
        return (TipAst.unary_op, tokeni[0])
    else:
        return None

def stamp_ast(ast, uv=0):
    global tab
    if ast == None:
        return "(none)"
    elif ast.tip == "RETURN_KEYWORD":
        return uv*tab + "RETURN " + ast(ast.e, 0)
    elif ast[0] == TipAst.exp:
        return "I: " + "RETURN" +  " "+ repr(ast[1])

    elif ast[0] == TipAst.statement:
        return (uv*tab+"S:\n"
                + (uv+1)*tab + stamp_ast(ast[1], uv+1))

    elif ast[0] == TipAst.fun_decl:
        return (uv*tab+"FUN: " + "TIP"  + " "+ ast[1][2] + ":\n" 
                + (uv+1)*tab + "params: (" + ")\n" 
                + (uv+1)*tab + "telo:\n"
                + stamp_ast(ast[2], uv+2))

    elif ast[0] == TipAst.prog:
        return "PROGRAM: \n" + stamp_ast(ast[1], uv+1)
               
    else:
        return None


if __name__ == "__main__":
    c()
    with open("test2.c") as f:
        ulaz = f.read()

    tokeni = leksiranje(ulaz)
    if tokeni == None:
        exit(1)

    ast = parse_program(tokeni)

    #ast = (TipAst.fun_decl, (TipTokena.IDENT, 2, "nijokk"), ( TipAst.statement, (TipAst.exp, (TipTokena.CB, 2, 1)) ))
    #ast = (TipAst.exp, (TipTokena.CB, 2, 1))
    

    print(stamp_ast(ast))

    #for i, t in enumerate(tokeni):
    #    print(f'{i}:\t{t}')
    #    pass


#    print("jhg: ", print(
#        [
#            (TipTokena.IDENT       ,1),
#            (TipTokena.LEVAZAG     ,2),
#            (TipTokena.IDENT       ,3),
#            (TipTokena.DESNAZAG     ,3),
#            ]
#        ))
#            (TipTokena.LEVAZAG      ,2),
#            (TipTokena.LEVAZAG      ,2),
#            (TipTokena.LEVAZAG      ,2),
#            (TipTokena.TZ           ,3), 
#            (TipTokena.DESNAZAG           ,5), 
#            (TipTokena.ELSE           ,4), 
#            (TipTokena.TZ           ,6), 
#            (TipTokena.DESNAZAG     ,7),
#            (TipTokena.TZ           ,8), 
#            (TipTokena.TZ           ,9), 
#            (TipTokena.TZ           ,0), 
#            (TipTokena.DESNAZAG     ,2)
#            ]
#        ))
