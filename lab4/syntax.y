%{
    #include"lex.yy.c"
    void yyerror(const char*);
%}

%token LC RC LB RB COLON COMMA
%token STRING NUMBER
%token TRUE FALSE VNULL
%%

Json:
      Value
    ;
Value:
      Object
    | Array
    | STRING
    | NUMBER
    | TRUE
    | FALSE
    | VNULL
    ;
Object:
      LC RC
    | LC Members RC
    | LC Members COMMA error { puts("Comma instead if closing brace, recovered"); }
    | LC Members RC STRING error { puts("misplaced quoted value"); }
    ;
Members:
      Member
    | Member COMMA Members
    | Member COMMA error { puts("Extra comma, Members, recovered"); }
    ;
Member:
      STRING COLON Value
    | STRING Value error { puts("Missing colon, recovered"); }
    | STRING COMMA Value error { puts("Missing colon, recovered"); }
    | STRING COMMA COMMA Value error { puts("Double colon, recovered"); }
    ;
Array:
      LB RB
    | LB Values RB
    | LB Values RC error { puts("unmatched right bracket, recovered"); }
    | LB Values RB COMMA error { puts("Comma after the close, recovered"); }
    | LB Values error { puts("Unclosed array, recovered"); }
    | LB Values RB RB error { puts("Extra close, recovered"); }
    ;
Values:
      Value
    | Value COMMA Values
    | Value COMMA error { puts("Extra comma, Values, recovered"); }
    | Value COMMA COMMA error { puts("double, recovered"); }
    | Value COLON Values error { puts("Colon instead of comma, recovered"); }
    | COMMA Value error { puts("missing value, recovered"); }
    ;
%%

void yyerror(const char *s){
    printf("syntax error: ");
}

int main(int argc, char **argv){
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(-1);
    }
    else if(!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
        exit(-1);
    }
    yyparse();
    return 0;
}
