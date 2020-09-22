%{
    #include"lex.yy.c"
    void yyerror(const char *s){}
    int result = 1;
%}
%token LP RP LB RB LC RC
%%
String: %empty {}
    ｜ String LP String RP {}
    ｜ String LB String RB {}
    ｜ String LC String RC {}
;
%%

int validParentheses(char *expr){
    yy_scan_string(expr);
    yyparse();
    return result;
}

void yyerror(const char *s){
    result = 0;
    fprintf(stderr, "Syntax error: %s\n", s);
}