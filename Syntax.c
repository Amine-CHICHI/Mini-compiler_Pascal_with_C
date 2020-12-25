/** 
     GRAMMAR for Pascal Language
 
PROGRAM     ::= program ID ; BLOCK .
BLOCK       ::= CONSTS VARS INSTS
CONSTS      ::= const ID = NUM ; { ID = NUM ; } | e
VARS        ::= var ID { , ID } ; | e
INSTS       ::= begin INST { ; INST } end
INST        ::= INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | e
AFFEC       ::= ID := EXPR
SI          ::= if COND then INST
TANTQUE     ::= while COND do INST
ECRIRE      ::= write ( EXPR { , EXPR } )
LIRE        ::= read ( ID { , ID } )
COND        ::= EXPR RELOP EXPR
RELOP       ::= = | <> | < | > | <= | >=
EXPR        ::= TERM { ADDOP TERM }
ADDOP       ::= + | -
TERM        ::= FACT { MULOP FACT }
MULOP       ::= * | /
FACT        ::= ID | NUM | ( EXPR )
ID          ::= lettre {lettre | chiffre}
NUM         ::= chiffre {chiffre}
Chiffre     ::= 0|..|9
Lettre      ::= a|b|..|z|A|..|Z

/**********************************/

#include "Lexer.c"

typedef enum
{
    INORDER,
    ANY
} Method;
const char *fileName = "program.pascal";
/*********** Functions Prototype **********/

void verifyToken();
void Program();
void Block();
void Consts();
void Vars();
void Insts();
void Inst();
void Affec();
void Si();
void Tantque();
void Ecrire();
void Lire();
void Cond();
void Expr();
void AddOp();
void Term();
void MulOp();
void Fact();
// void ID_fct();
// void Num();
// void Chiffre();
// void Lettre();

/*********** Main **********/

int main()
{
    program = fopen(fileName, "r");
    if (program == NULL)
    {
        perror("Error while opening the pascal file");
        exit(1);
    }
    NextChar();
    Program();
    if (currentToken.code == EndOfFile)
    {
        printf("Parse success\n");
    }
    else
    {
        printf("parsing Failed\n");
    }
    return 1;
}

/*********** Functions **********/

void verifyToken(token_code code_to_test, char *erreur)
{

    // printf("compared to : %d\n", code_to_test);
    if (currentToken.code == code_to_test)
    {
        getToken();
    }
    else
    {
        printf("%s\n", erreur);
        exit(0);
    }
}

void SyntaxError(token_code code)
{
    printf("Syntax Error");
    exit(1);
}

void Program()
{
    getToken();
    // printf("current tok : %s\n", currentToken.name);
    verifyToken(PROGRAM, "program missing");
    verifyToken(ID, "ID missing");
    verifyToken(PV, "PV missing");
    Block();
    verifyToken(PT, "PT missing");
}

void Block()
{
    Consts();
    Vars();
    Insts();
}

void Consts()
{
    switch (currentToken.code)
    {
    case CONST:
        getToken();
        verifyToken(ID, "ID missing");
        verifyToken(EG, "EG missing");
        verifyToken(NUM, "NUM missing");
        verifyToken(PV, "PV missing");
        while (currentToken.code == ID)
        {
            getToken();
            verifyToken(EG, "EG missing");
            verifyToken(NUM, "NUM missing");
            verifyToken(PV, "PV missing");
        };
        break;
    case VAR:
        break;
    case BEGIN:
        break;
    default:
        printf("Erreur inside CONSTS\n");
        break;
    }
}

void Vars()
{
    switch (currentToken.code)
    {
    case VAR:
        // printf("current tok : %S\n", currentToken.value);
        getToken();
        printf("|| current tok : %S\n", currentToken.value);
        verifyToken(ID, "ID missing");
        printf("|| current tok : %S\n", currentToken.value);
        // printf("HOLLA\n");
        while (currentToken.code == VIR)
        {
            printf("HOLLA 256\n");
            getToken();
            verifyToken(ID, "ID missing");
            // printf("HOLLA\n");
        }
        printf("HOLLA\n");
        verifyToken(PV, "PV missing");
        break;
    case BEGIN:
        break;
    default:
        printf("Erreur inside Vars\n");
        break;
    }
}

void Insts()
{
    verifyToken(BEGIN, "BEGIN missing");
    Inst();
    prevToken = currentToken;
    while (currentToken.code == PV)
    {
        getToken();
        Inst();
        if (currentToken.code != END && currentToken.code != PV)
        {
            // verifyToken(PV);
            break;
        }
    }
    verifyToken(END, "END missing");
}

void Inst()
{

    switch ((currentToken.code))
    {
    case BEGIN:
        Insts();
        break;
    case ID:
        Affec();
        break;
    case IF:
        Si();
        break;
    case WHILE:
        Tantque();
        break;
    case WRITE:
        Ecrire();
        break;
    case READ:
        Lire();
        break;
    case END:
        break;
    default:
        printf("error in INST\n");
        break;
    }
}

void Affec()
{
    verifyToken(ID, "ID missing");
    verifyToken(AFF, "AFF missing");
    Expr();
}

void Si()
{
    verifyToken(IF, "IF missing");
    Cond();
    verifyToken(THEN, "THEN missing");
    Inst();
}

void Tantque()
{
    verifyToken(WHILE, "WHILE missing");
    Cond();
    verifyToken(DO, "DO missing");
    Inst();
}

void Ecrire()
{
    verifyToken(WRITE, "WRITE missing");
    verifyToken(PO, "PO missing");
    Expr();
    while (currentToken.code == VIR)
    {
        getToken();
        Expr();
    }
    verifyToken(PF, "PF missing");
}

void Lire()
{
    verifyToken(READ, "READ missing");
    verifyToken(PO, "PO missing");
    verifyToken(ID, "ID missing");
    while (currentToken.code == VIR)
    {
        getToken();
        verifyToken(ID, "ID missing");
    }
    verifyToken(PF, "PF missing");
}

void Cond()
{
    Expr();
    switch (currentToken.code)
    {
    case EG:
        break;
    case DIFF:
        break;
    case INF:
        break;
    case SUP:
        break;
    case INFEG:
        break;
    case SUPEG:
        break;
    default:
        printf("error in Cond\n");
        break;
    }
    getToken();
    Expr();
}

void Expr()
{
    Term();
    while (currentToken.code == PLUS || currentToken.code == MOINS)
    {
        getToken();
        Term();
    }
}

// void AddOp()
// {
//     switch (currentToken.code)
//     {
//     case PLUS:
//         break;
//     case MOINS:
//         break;
//     default:
//         printf("error in AddOp\n");
//         break;
//     }
// }

void Term()
{
    Fact();
    while (currentToken.code == MULT || currentToken.code == DIV)
    {
        getToken();
        Fact();
    }
}

// void MulOp()
// {
//     switch ((currentToken = getToken()).code)
//     {
//     case MULT:
//     case DIV:
//         break;
//     default:
//         SyntaxError();
//         break;
//     }
// }

void Fact()
{
    switch (currentToken.code)
    {
    case ID:
        getToken();
        break;
    case NUM:
        getToken();
        break;
    case PO:
        Expr();
        verifyToken(PF, "PF missing");
        break;
    }
}