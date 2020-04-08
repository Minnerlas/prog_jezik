from enum import IntEnum, auto

class TipTokena(IntEnum):
    # Tokeni od jednog karaktera
    LEVAVIT     = auto()
    DESNAVIT    = auto()
    LEVAZAG     = auto()
    DESNAZAG    = auto()
    LEVAUG      = auto()
    DESNAUG     = auto()
    TZ          = auto()
    TACKA       = auto() # Može biti i deo realnog broja
    ZAREZ       = auto()
    NEG         = auto()
    UPITNIK     = auto()
    DVOTACKA    = auto()

    # Tokeni od jednog ili dva karakera
    UZV         = auto()
    UZVJED      = auto()
    JED         = auto()
    JEDJED      = auto()
    VECE        = auto()
    VECEVECE    = auto()
    VECEJED     = auto()
    MANJE       = auto()
    MANJEMANJE  = auto()
    MANJEJED    = auto()
    PLUS        = auto()
    PLUSPLUS    = auto()
    PLUSJED     = auto()
    MINUS       = auto()
    MINUSMINUS  = auto()
    MINUSJED    = auto()
    MINUSVECE   = auto()
    PUTA        = auto()
    PUTAJED     = auto()
    KROZ        = auto()
    KROZJED     = auto()
    MOD         = auto()
    MODJED      = auto()
    I           = auto()
    II          = auto()
    IJED        = auto()
    ILI         = auto()
    ILIILI      = auto()
    ILIJED      = auto()
    KSILI       = auto()
    KSILIJED    = auto()

    # Tokeni od tri karaktera: >>= <<=
    MMJED       = auto()
    VVJED       = auto()

    # Literali
    STRING      = auto()
    CB          = auto()
    RB          = auto()
    IDENT       = auto()

    # Ključne reči
    AUTO        = auto()
    BREAK       = auto()
    CASE        = auto()
    CONST       = auto()
    CONTINUE    = auto()
    DEFAULT     = auto()
    DO          = auto()
    ELSE        = auto()
    ENUM        = auto()
    EXTERN      = auto()
    FLOAT       = auto()
    FOR         = auto()
    GOTO        = auto()
    IF          = auto()
    REGISTER    = auto()
    RETURN      = auto()
    SIGNED      = auto()
    SIZEOF      = auto()
    STATIC      = auto()
    STRUCT      = auto()
    SWITCH      = auto()
    TYPEDEF     = auto()
    UNION       = auto()
    USIGNED     = auto()
    VOID        = auto()
    VOLATILE    = auto()
    WHILE       = auto()

    # Tipovi
    CHAR        = auto()
    DOUBLE      = auto()
    INT         = auto()
    LONG        = auto()
    SHORT       = auto()

    EOF         = auto()



if __name__ == "__main__":
    print(repr(TipTokena.EOF))
