%{
    #include"lex.yy.c"
    struct Json* json;
    int is_valid = 1;
    void yyerror(const char*);
%}
%union{
    struct Json* json;
    struct Object* object;
    struct Array* array;
    char string[100];
    double number;
    int boolean;
}

%token LC RC LB RB COLON COMMA
%token <string> STRING
%token <number> NUMBER
%token <boolean> TRUE FALSE 
%token <json> VNULL

%type <json> Json Value
%type <object> Object Members Member
%type <array> Array Values

%%

Json:
      Value { json = $1; }
    ;
Value:
      Object { $$ = createJson(); $$->object = $1; $$->category = OBJECT_; }
    | Array { $$ = createJson(); $$->array = $1; $$->category = ARRAY_; }
    | STRING { $$ = createJson(); $$->string = $1; $$->category = STRING_; }
    | NUMBER { $$ = createJson(); $$->number = $1; $$->category = NUMBER_; }
    | TRUE { $$ = createJson(); $$->boolean = $1; $$->category = BOOLEAN_; }
    | FALSE { $$ = createJson(); $$->boolean = $1; $$->category = BOOLEAN_; }
    | VNULL { $$ = $1; $$->category = VNULL_; }
    ;
Object:
      LC RC { $$ = createObject(); }
    | LC Members RC 
        { 
            $$ = $2;
            Object* object = $2;
            int table[26];
            for (int i = 0; i < 26; ++i) { table[i] = 0; }
            while (object != NULL) {
                int key = (object->string)[1] - 97;
                if (table[key] == 0) {
                    table[key] = 1;
                } else {
                    is_valid = 0;
                    char buf[100];
                    sprintf(buf, "duplicate key: %s\n", object->string);
                    yyerror(buf);
                }
                object = object->members;
            }
        }
    ;
Members:
      Member { $$ = $1; }
    | Member COMMA Members { $$ = $1; $1->members = $3; }
    ;
Member:
      STRING COLON Value 
        {
            $$ = createObject();
            memset($$->string, '\0', sizeof($1));
            strcpy($$->string, $1);
            $$->value = $3;
        }
    ;
Array:
      LB RB { $$ = createArray(); }
    | LB Values RB { $$ = $2; }
    ;
Values:
      Value { $$ = createArray(); $$->value = $1; }
    | Value COMMA Values { $$ = createArray(); $$->value = $1; $$->values = $3; }
    ;
%%

void yyerror(const char *s){
    printf("%s", s);
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
    if(is_valid) {
        printf("%d\n", is_valid);
    }
    return 0;
}