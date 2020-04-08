#!/bin/python
from os import system
from sys import argv

from tokeni import TipTokena

def isnum(c):
    return c in set("0123456789")

def isal(c):
    return  ((c >= 'a' and c <= 'z') or
             (c >= 'A' and c <= 'Z') or
            c == '_')

def isalnum(c):
    return isal(c) or isnum(c)

def c():
    _=system("clear")

def greska(linija, tekst):
    print(f"[Linija {linija}] Greška: {tekst}")

kljucnereci = {
        # Ključne reči
        "auto"      :TipTokena.AUTO,
        "break"     :TipTokena.BREAK,
        "case"      :TipTokena.CASE,
        "const"     :TipTokena.CONST,
        "continue"  :TipTokena.CONTINUE,
        "default"   :TipTokena.DEFAULT,
        "do"        :TipTokena.DO,
        "else"      :TipTokena.ELSE,
        "enum"      :TipTokena.ENUM,
        "extern"    :TipTokena.EXTERN,
        "float"     :TipTokena.FLOAT,
        "for"       :TipTokena.FOR,
        "goto"      :TipTokena.GOTO,
        "if"        :TipTokena.IF,
        "register"  :TipTokena.REGISTER,
        "return"    :TipTokena.RETURN,
        "signed"    :TipTokena.SIGNED,
        "sizeof"    :TipTokena.SIZEOF,
        "static"    :TipTokena.STATIC,
        "struct"    :TipTokena.STRUCT,
        "switch"    :TipTokena.SWITCH,
        "typedef"   :TipTokena.TYPEDEF,
        "union"     :TipTokena.UNION,
        "unsigned"  :TipTokena.USIGNED,
        "void"      :TipTokena.VOID,
        "volatile"  :TipTokena.VOLATILE,
        "while"     :TipTokena.WHILE,
        
        # Tipovi
        "char"      :TipTokena.CHAR,
        "double"    :TipTokena.DOUBLE,
        "int"       :TipTokena.INT,
        "long"      :TipTokena.LONG,
        "short"     :TipTokena.SHORT,
        }

def leksiranje(ulaz):
    trenutni = 0
    prvi = 0
    linija = 1
    tokeni = []
    gr = False
    while(trenutni<len(ulaz)):
        c=ulaz[trenutni]
        if trenutni+1 >= len(ulaz):
            sl='\0'
        else:
            sl=ulaz[trenutni+1]

        if c == ' ' or c == '\t':
            trenutni+=1
        elif c == '\n':
            linija+=1;
            trenutni+=1
        elif c == '{':
            tokeni+=[(TipTokena.LEVAVIT,linija)]
            trenutni+=1
        elif c == '}':
            tokeni+=[(TipTokena.DESNAVIT,linija)]
            trenutni+=1
        elif c == '(':
            tokeni+=[(TipTokena.LEVAZAG,linija)]
            trenutni+=1
        elif c == ')':
            tokeni+=[(TipTokena.DESNAZAG,linija)]
            trenutni+=1
        elif c == '[':
            tokeni+=[(TipTokena.LEVAUG,linija)]
            trenutni+=1
        elif c == ']':
            tokeni+=[(TipTokena.DESNAUG,linija)]
            trenutni+=1
        elif c == ';':
            tokeni+=[(TipTokena.TZ,linija)]
            trenutni+=1
        elif c == '.':
            tekst = ''
            if isnum(sl):
                while isnum(sl):
                    tekst+=sl
                    trenutni+=1
                    c = ulaz[trenutni]
                    sl = ulaz[trenutni+1]
                tokeni+=[(TipTokena.RB,linija, float(tekst))]
                trenutni+=1
            else:
                tokeni+=[(TipTokena.TACKA,linija)]
            trenutni+=1
        elif c == ',':
            tokeni+=[(TipTokena.ZAREZ,linija)]
            trenutni+=1
        elif c == '~':
            tokeni+=[(TipTokena.NEG,linija)]
            trenutni+=1
        elif c == '?':
            tokeni+=[(TipTokena.UPITNIK,linija)]
            trenutni+=1
        elif c == ':':
            tokeni+=[(TipTokena.DVOTACKA,linija)]
            trenutni+=1
        elif c == '!':
            if sl == '=':
                tokeni+=[(TipTokena.UZVJED,linija)]
                trenutni+=2
            else:
                tokeni+=[(TipTokena.UZV,linija)]
                trenutni+=1
        elif c == '=':
            if sl == '=':
                tokeni+=[(TipTokena.JEDJED,linija)]
                trenutni+=2
            else:
                tokeni+=[(TipTokena.JED,linija)]
                trenutni+=1
        elif c == '>':
            if sl == '>' and ulaz[trenutni+2] == '=':
                tokeni+=[(TipTokena.VVJED, linija)]
                trenutni+=3
            elif sl == '>':
                tokeni+=[(TipTokena.VECEVECE,linija)]
                trenutni+=2
            elif sl == '=':
                tokeni+=[(TipTokena.VECEJED,linija)]
                trenutni+=2
            else:
                tokeni+=[(TipTokena.VECE,linija)]
                trenutni+=1
        elif c == '<':
            if sl == '<' and ulaz[trenutni+2] == '=':
                tokeni+=[(TipTokena.MMJED, linija)]
                trenutni+=3
            elif sl == '<':
                tokeni+=[(TipTokena.MANJEMANJE,linija)]
                trenutni+=2
            elif sl == '=':
                tokeni+=[(TipTokena.MANJEJED,linija)]
                trenutni+=2
            else:
                tokeni+=[(TipTokena.MANJE,linija)]
                trenutni+=1
        elif c == '+':
            if sl == '+':
                tokeni+=[(TipTokena.PLUSPLUS,linija)]
                trenutni+=2
            elif sl == '=':
                tokeni+=[(TipTokena.PLUSJED,linija)]
                trenutni+=2
            else:
                tokeni+=[(TipTokena.PLUS,linija)]
                trenutni+=1
        elif c == '-':
            if sl == '-':
                tokeni+=[(TipTokena.MINUSMINUS,linija)]
                trenutni+=2
            elif sl == '=':
                tokeni+=[(TipTokena.MINUSJED,linija)]
                trenutni+=2
            elif sl == '>':
                tokeni+=[(TipTokena.MINUSVECE,linija)]
                trenutni+=2
            else:
                tokeni+=[(TipTokena.MINUS,linija)]
                trenutni+=1
        elif c == '*':
            if sl == '=':
                tokeni+=[(TipTokena.PUTAJED,linija)]
                trenutni+=2
            else:
                tokeni+=[(TipTokena.PUTA,linija)]
                trenutni+=1
        elif c == '/':
            if sl == '/':
                while ulaz[trenutni]!='\n' and ulaz[trenutni]!='\0':
                    trenutni+=1
                linija+=1
            elif sl == '*':
                while ulaz[trenutni:trenutni+2]!='*/' and ulaz[trenutni]!='\0':
                    if trenutni+1 == len(ulaz):
                        greska(linija, "Nezatvoreni komentar")
                        return None
                    if ulaz[trenutni] == '\n':
                        linija+=1
                    trenutni+=1
                trenutni+=2
            elif sl == '=':
                tokeni+=[(TipTokena.KROZJED,linija)]
                trenutni+=2
            else:
                tokeni+=[(TipTokena.KROZ,linija)]
                trenutni+=1
        elif c == '%':
            if sl == '=':
                tokeni+=[(TipTokena.MODJED,linija)]
                trenutni+=2
            else:
                tokeni+=[(TipTokena.MOD,linija)]
                trenutni+=1
        elif c == '&':
            if sl == '&':
                tokeni+=[(TipTokena.II,linija)]
                trenutni+=2
            elif sl == '=':
                tokeni+=[(TipTokena.IJED,linija)]
                trenutni+=2
            else:
                tokeni+=[(TipTokena.I,linija)]
                trenutni+=1
        elif c == '|':
            if sl == '|':
                tokeni+=[(TipTokena.ILIILI,linija)]
                trenutni+=2
            elif sl == '=':
                tokeni+=[(TipTokena.ILIJED,linija)]
                trenutni+=2
            else:
                tokeni+=[(TipTokena.ILI,linija)]
                trenutni+=1
        elif c == '^':
            if sl == '=':
                tokeni+=[(TipTokena.KSILIJED,linija)]
                trenutni+=2
            else:
                tokeni+=[(TipTokena.KSILI,linija)]
                trenutni+=1
        elif c == '\"':
            trenutni += 1
            prvi = trenutni
            sl = ulaz[trenutni+1]
            c = ulaz[trenutni]
            tekst = ""
            while c !='\"':
                if trenutni>=len(ulaz):
                    greska(linija, "Nezatvoren string")
                    return None
                if c == '\\':
                    if sl == 'n':
                        tekst+="\n"
                        trenutni+=1
                    elif sl == 't':
                        tekst+="\t"
                        trenutni+=1
                else:
                    tekst+=ulaz[trenutni]

                trenutni+=1
                c = ulaz[trenutni]
                sl = ulaz[trenutni+1]
            tokeni+=[(TipTokena.STRING, linija, tekst)]
            trenutni+=1
        elif isnum(c):
            tekst = ""
            fl = False
            while isnum(c) :
                tekst+=c
                trenutni += 1
                sl = ulaz[trenutni+1]
                c = ulaz[trenutni]
                # print(c)
            if c == '.':
                fl = True
                tekst +='.'
                trenutni += 1
                c = ulaz[trenutni]
                while isnum(c):
                    tekst +=c
                    trenutni +=1
                    c = ulaz[trenutni]
            if fl:
                tokeni+=[(TipTokena.RB, linija, float(tekst))]
            else:
                tokeni+=[(TipTokena.CB, linija, int(tekst))]

        elif isal(c):
            tekst = ""
            while isalnum(sl):
                tekst += c
                trenutni+=1
                c = ulaz[trenutni]
                sl = ulaz[trenutni+1]

            tekst += c
            trenutni+=1
            c = ulaz[trenutni]
            sl = ulaz[trenutni+1]

            tip = TipTokena.IDENT

            if tekst in kljucnereci:
                tip = kljucnereci[tekst]

            tokeni += [(tip, linija, tekst)]

        else:
            #print("Greška. "+ulaz[trenutni:trenutni+5])
            greska(linija, f"Neočekivani karakter {c}")
            trenutni+=1
            gr = True

    if not gr:
        return tokeni
    else:
        return None

if __name__ == "__main__":
    ul = "test.c"
    ulaz =""

    with open(ul) as f:
        ulaz = f.read()
    c()
    a=leksiranje(ulaz) 
    if a:
        for i in leksiranje(ulaz):
            print(i)

