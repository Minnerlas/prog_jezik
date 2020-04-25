#!/bin/python
from lekser import *
from tokeni import TipTokena
from izrazi import TipIzraza


def dbgprint(*args, **kwargs):
    print(*args, **kwargs)
    pass

def primary_expression(tokeni):
    trenutni = tokeni[0]
    dbgprint("\nprimary_expression: ", tokeni)
    tok = {
            TipTokena.CB,
            TipTokena.RB,
            TipTokena.CHCONST,
            TipTokena.IDENT,
            }
    if trenutni[0] in tok and len(tokeni) == 1:
        return (TipIzraza.primary_expression, trenutni)
    elif tokeni[0][0] == TipTokena.LEVAZAG and tokeni[-1][0] == TipTokena.DESNAZAG:
        t = expression(tokeni[1:-1])
        if t == None:
            return None
        return (TipIzraza.primary_expression, t)
    else:
        return None




def postfix_expression(tokeni):
    dbgprint("\npostfix_expression: ", tokeni)
    if (t:=primary_expression(tokeni)) != None and len(tokeni) == 1:
        return (TipIzraza.postfix_expression, t)
    elif tokeni[-1][0] == TipTokena.DESNAUG:
        dz = 1
        lz = 0
        i = len(tokeni)-1
        while lz != dz and i>=0:
            i-=1
            if tokeni[i][0] == TipTokena.DESNAUG:
                dz+=1
            elif tokeni[i][0] == TipTokena.LEVAUG:
                lz+=1

        if tokeni[i][0] != TipTokena.LEVAUG:
            greska(tokeni[i][1], f"Očekivana '[', dobijen {tokeni[i]}")
            return None
        
        t1 = postfix_expression(tokeni[:i])
        t2 = expression(tokeni[i+1:-1])
        if t1 == None or t2 == None:
            return None
        return (TipIzraza.postfix_expression, t) 

    elif tokeni[-1][0] == TipTokena.DESNAZAG:
        if tokeni[-2][0] == TipTokena.LEVAZAG:
            return (TipIzraza.postfix_expression, postfix_expression(tokeni[:-2]))
        else:
            i = 0
            dz = 1
            lz = 0
            i = len(tokeni)-1
            while lz != dz and i>=0:
                i-=1
                if tokeni[i][0] == TipTokena.DESNAZAG:
                    dz+=1
                elif tokeni[i][0] == TipTokena.LEVAZAG:
                    lz+=1
            if tokeni[i][0] != TipTokena.LEVAZAG:
                greska(tokeni[i][1], f"Očekivana '(', dobijen {tokeni[i]}")
                return None
            t1 = postfix_expression(tokeni[:i])
            t2 = argument_expression_list(tokeni[i+1:-1])

            if t1 == None or t2 == None:
                return None
            
            return (TipIzraza.postfix_expression, t1, t2)
    elif tokeni[-1][0] == TipTokena.IDENT:
        t = tokeni[-2]
        if t[0] == TipTokena.TACKA:
            t = postfix_expression(tokeni[:-2])
            if t == None:
                return None
            return (TipIzraza.postfix_expression, t, TipTokena.TACKA, tokeni[-1])
        elif t[0] == TipTokena.PUTA:
            t = postfix_expression(tokeni[:-2])
            if t == None:
                return None
            return (TipIzraza.postfix_expression, t, TipTokena.PUTA, tokeni[-1])
        else: 
            return None

    elif tokeni[-1][0] == TipTokena.PLUSPLUS:
        t = postfix_expression(tokeni[:-1])
        if t == None:
            return None
        return (TipIzraza.postfix_expression, t, TipTokena.PLUSPLUS)

    elif tokeni[-1][0] == TipTokena.MINUSMINUS:
        t = postfix_expression(tokeni[:-1])
        if t == None:
            return None
        return (TipIzraza.postfix_expression, t, TipTokena.MINUSMINUS)
    else:
        return None


def argument_expression_list(tokeni):
    if (t:=assignment_expression(tokeni)) != None:
        return (TipIzraza.argument_expression_list, t)
    else:
        i = len(tokeni)-1
        while i>=0 and tokeni[i][0] != TipTokena.ZAREZ:
            i-=1
        if tokeni[i] != TipTokena.ZAREZ:
            return None
        t1 = argument_expression_list(tokeni[:i])
        t2 = assignment_expression(tokeni[i+1:])
        if t1 == None or t2 == None:
            return None
        
        return (TipIzraza.argument_expression_list, t1, TipTokena.ZAREZ, t2)

def unary_expression(tokeni):
    if (t:=postfix_expression(tokeni)) != None:
        return t
    if tokeni[0][0] == TipTokena.PLUSPLUS:
        t = unary_expression(tokeni[1:])
        if t == None:
            return None
        return (TipIzraza.unary_expression, TipTokena.PLUSPLUS, t)
    elif tokeni[0][0] == TipTokena.MINUSMINUS:
        t = unary_expression(tokeni[1:])
        if t == None:
            return None
        return (TipIzraza.unary_expression, TipTokena.MINUSMINUS, t)
    elif tokeni[0][0] == TipTokena.SIZEOF:
        if tokeni[-1][0] == TipTokena.DESNAZAG and tokeni[1][0] == TipTokena.LEVAZAG:
            t = type_name(tokeni[1:-1])
            if t == None:
                return None
            return (TipIzraza.unary_expression, t)
        t = unary_expression(tokeni[1:])
        if t == None:
            return None
        return (TipIzraza.unary_expression, t)
    else:               ## OBAVEZNO 52:	| unary_operator cast_expression
        return None



def assignment_operator(tokeni):
    trenutni = tokeni[0]
    jed = {
            TipTokena.UZV        , 
            TipTokena.UZVJED     , 
            TipTokena.JED        , 
            TipTokena.PLUSJED    , 
            TipTokena.MINUSJED   , 
            TipTokena.PUTAJED    , 
            TipTokena.KROZJED    , 
            TipTokena.MODJED     , 
            TipTokena.IJED       ,
            TipTokena.ILIJED     ,
            TipTokena.KSILIJED   ,
            }
    t = trenutni[0]
    if t in jed and len(tokeni):
        return (TipIzraza.assignment_operator, trenutni)
    else:
        greska(trenutni[1], f"Očekivana je dodela, a dobijen je {trenutni}")
        return None


def unary_operator(tokeni):
    trenutni = tokeni[0]
    tok = {
            TipTokena.I     ,
            TipTokena.PUTA  ,
            TipTokena.PLUS  ,
            TipTokena.MINUS ,
            TipTokena.NEG   ,
            TipTokena.UZV   ,

            } 
    if trenutni[0] in tok and len(tokeni) == 1:
        return (TipIzraza.unary_operator, trenutni)
    else:
        return None

def storage_class_specifier(tokeni):
    trenutni = tokeni[0]
    tok = {
            TipTokena.TYPEDEF   ,
            TipTokena.EXTERN    ,
            TipTokena.STATIC    ,
            TipTokena.AUTO      ,
            TipTokena.REGISTER  ,
            }
    if trenutni[0] in tok:
        return (TipIzraza.storage_class_specifier, trenutni)
    greska(trenutni[1], f"Očekivani specifikator tipa, dobijen {trenutni}")
    return None

def struct_or_union_specifier(tokeni):
    pass

def enum_specifier(tokeni):
    pass


def type_specifier(tokeni):
    trenutni = tokeni[0]
    tok = {
            TipTokena.VOID      ,
            TipTokena.CHAR      ,
            TipTokena.SHORT     ,
            TipTokena.INT       ,
            TipTokena.LONG      ,
            TipTokena.FLOAT     ,
            TipTokena.DOUBLE    ,
            TipTokena.SIGNED    ,
            TipTokena.USIGNED   ,
            TipTokena.IDENT     ,
            }
    if trenutni[0] in tok:
        return (TipIzraza.type_specifier, trenutni)
    elif trenutni[0] == TipTokena.ENUM:
        return (TipIzraza.type_specifier, enum_specifier(tokeni))
    elif trenutni[0] == TipTokena.STRUCT or trenutni[0] == TipTokena.UNION:
        return (TipIzraza.type_specifier, struct_or_union_specifier(tokeni))
    else:
        greska(trenutni[1], f"Očekvan specifikator tipa, dobijen {trenutni}")
        return None

def struct_or_union(tokeni):
    trenutni = tokeni[0]
    if trenutni[0] in {
            TipTokena.STRUCT,
            TipTokena.UNION ,
            }:
        return (TipIzraza.struct_or_union, trenutni)
    else:
        greska(trenutni[1], f"Očekivani struct ili union, dobijen {trenutni}")
        return None


def type_qualifier(tokeni):
    trenutni = tokeni[0]
    if trenutni in {
            TipTokena.CONST   ,
            TipTokena.VOLATILE,
            }:
        return (TipIzraza.type_qualifier, trenutni)
    else:
        greska(trenutni[1], f"Očekivani const ili volatile, dobijen {trenutni}")
        return None

def jump_statement(tokeni):
    tr = tokeni[0]
    sl = tokeni[1]
    if sl[0] == TipTokena.TZ and tr[0] in {
            TipTokena.CONTINUE,
            TipTokena.BREAK,
            }:
        return (TipIzraza.jump_statement, tr) 
    elif tr[0] == TipTokena.RETURN:
        if sl[0] == TipTokena.TZ:
            return (TipIzraza.jump_statement, tr)
        else:
            i = 0
            while i<len(tokeni):
                if tokeni[i][0] == TipTokena.TZ:
                    break
                i+=1

            if tokeni[i][0] == TipTokena.TZ:
                return (TipIzraza.jump_statement, expression(tokeni[1:i]))
    elif tr[0] == TipTokena.GOTO and sl[0] == TipTokena.IDENT and tokeni[2][0] == TipTokena.TZ:
        return (TipIzraza.jump_statement,  tr, sl)
    else:
        greska(tr[1], f"Očekivani return, break, goto ili continue, dobijen {tr}")
        return None





###########################################################################################
def selection_statement(tokeni):
    tr = tokeni[0]
    if tr[0] == TipTokena.SWITCH:
        if tokeni[1][0] == TipTokena.LEVAZAG:
            lz = 1
            dz = 0
            i = 2
            t = []
            while i<len(tokeni) and lz != dz:
                t+=[tokeni[i]]
                if tokeni[i][0] == TipTokena.LEVAZAG:
                    lz+=1
                if tokeni[i][0] == TipTokena.DESNAZAG:
                    dz+=1
                i+=1
            if t.pop()[0] == TipTokena.DESNAZAG:
                izr = expression(t)
                return (TipIzraza.selection_statement, tr, izr, statement(tokeni[i+1:]))
            else:
                greska(tokeni[0][1], f"Ocekivana desna zagrada")
        else:
            greska(tokeni[1][1], f"Očekivana leva zagrada, dobijena {tokeni[1]}")
            return None
    elif tr[0] == TipTokena.IF:
        if tokeni[1][0] != TipTokena.LEVAZAG:
            greska(tokeni[1][1], f"Očekivana leva zagrada, dobijen {tokeni[1]}")
            return None
        i = 2
        lz = 1
        dz = 0
        t = []
        while lz != dz and i<len(tokeni):
            t+=[tokeni[i]]
            if tokeni[i][0] == TipTokena.LEVAZAG:
                lz+=1
            if tokeni[i][0] == TipTokena.DESNAZAG:
                dz+=1

            i+=1

        if t.pop()[0] != TipTokena.DESNAZAG:
            greska(tokeni[1][1], "Ocekivana desna zagrada")
            return None
        izr = expression(t) 

        iff = 1
        els = 0
        t = []
        while iff != els and i<len(tokeni):
            t+=[tokeni[i]]
            if tokeni[i][0] == TipTokena.IF:
                iff+=1
            if tokeni[i][0] == TipTokena.ELSE:
                els+=1
            i+=1            

        if t.pop()[0] != TipTokena.ELSE:
            return (TipIzraza.selection_statement, tr, izr, statement(tokeni[i:]))
        else:
            return (TipIzraza.selection_statement, tr, izr, statement(tokeni[i:]))

    else:
        greska(tr[1], f"Očekivan su switch ili if, dobijeno {tr}")
###########################################################################################

def type_name(tokeni):
    print("type_name: ", tokeni)
    return None

def assignment_expression(tokeni):
    print("assignment_expression: ", tokeni)
    return None

def expression(tokeni):
    print("expression: ", tokeni)
    return None

def statement(tokeni):
    print("statement: ", tokeni)
    return None

######################################################
#def expression(tokeni):
#    trenutni = tokeni[0]
#    if TipTokena.ZAREZ in [a[0] for a in tokeni]:
#        i = 0
#        for t in tokeni:
#            if t[0] == TipTokena.ZAREZ:
#                break
#            i+=1
#        a = (TipIzraza.expression, expression(tokeni[:i]), assignment_expression(tokeni[i+1:]))
#        print(a)
#        return (TipIzraza.expression, expression(tokeni[:i]), assignment_expression(tokeni[i+1:]))
#    else:
#        a = (TipIzraza.expression, assignment_expression(tokeni))
#        print(a)
#        return (TipIzraza.expression, assignment_expression(tokeni))
######################################################


if __name__ == "__main__":
    c()
    with open("test.c") as f:
        ulaz = f.read()

    tokeni = leksiranje(ulaz)
    if tokeni == None:
        exit(1)
    #for i, t in enumerate(tokeni):
    #    print(f'{i}:\t{t}')
    #    pass


    print("jhg: ", postfix_expression(
        [
            (TipTokena.IDENT       ,1),
            (TipTokena.LEVAZAG     ,2),
            (TipTokena.IDENT       ,3),
            (TipTokena.DESNAZAG     ,3),
            ]
        ))
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
