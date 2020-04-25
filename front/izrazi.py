from enum import IntEnum, auto
from tokeni import TipTokena

class TipAst (IntEnum):
    exp         = auto() # Const(int)
    statement   = auto() # Return(exp)
    fun_decl    = auto() # Fun(string, statement)
    prog        = auto() # Prog(fun_decl)
    unary_op    = auto() # Prog(fun_decl)

class Const:
    t = None 
    l = None
    v = None
    def __init__(self, a):
        self.t = a[0]
        self.l = a[1]
        self.v = a[2]
        #print(a)

    def __str__(self):
        if self.t == TipTokena.CB:
            return f"Int<{self.v}>"
        else:
            return "asd"

    def __repr__(self):
        if self.t == TipTokena.CB:
            return f"Int<{self.v}>"
        else:
            return "asd"

class Return:
    e = None
    tip = "RETURN_KEYWORD"
    def __init__(self, a):
        self.e = a
        #print(a)

if __name__ == "__main__":
    print(repr(TipAst.fun_decl))
