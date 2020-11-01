%{
    #include"lex.yy.c"
    void yyerror(const char*);
    ValueDef* valuedefcreation();
%}
%union {
    struct JsonDef* jsondef;
    struct ValueDef* valuedef;
    struct ObjectDef* objectdef;
    struct MemberList* memberlist;
    struct MemberDef* memberdef;
    struct ArrayDef* arraydef;
    struct ValueList* valuelist;
    struct StringDef* stringdef;
}

%token  LC RC LB RB COLON COMMA
%token  STRING NUMBER
%token  TRUE FALSE VNULL

%type   <jsondef>       Json
%type   <valuedef>      Value
%type   <objectdef>     Object
%type   <arraydef>      Array
%type   <stringdef>     NUMBER STRING
%type   <memberlist> Members
%type   <memberdef>     Member
%type   <valuelist>  Values

%%

Json:
      Value { $$ = (struct JsonDef*)malloc(sizeof(struct JsonDef)); $$->value = $1;}
    ;
Value:
      Object { $$ = valuedefcreation(); $$->category = OBJECT; $$->object = $1;}
    | Array  { $$ = valuedefcreation(); $$->category = ARRAY; $$->array = $1;}
    | STRING { $$ = valuedefcreation(); $$->category = STRING; $$->string = $1->string;}
    | NUMBER { $$ = valuedefcreation(); $$->category = NUMBER; $$->number = atof($1->string);}
    | TRUE { $$ = valuedefcreation(); $$->category = BOOLEAN; $$->boolean = 1;}
    | FALSE { $$ = valuedefcreation(); $$->category = BOOLEAN; $$->boolean = 0;}
    | VNULL { $$ = valuedefcreation(); $$->category = VNULL;}
    ;
Object:
      LC RC { $$ = (struct ObjectDef*)malloc(sizeof(struct ObjectDef)); $$->members = NULL;}
    | LC Members RC { $$ = (struct ObjectDef*)malloc(sizeof(struct ObjectDef)); $$->members = $2;}
    ;
Members:
      Member { $$ = (struct MemberList*)malloc(sizeof(struct MemberList)); $$->member = $1; $$->next = NULL;}
    | Member COMMA Members { $$ = (struct MemberList*)malloc(sizeof(struct MemberList)); $$->member = $1; $$->next = $3;}
    ;
Member:
      STRING COLON Value { $$ = (struct MemberDef*)malloc(sizeof(struct MemberDef)); $$->string = $1->string; $$->value = $3;}
    ;
Array:
      LB RB { $$ = (struct ArrayDef*)malloc(sizeof(struct ArrayDef)); $$->valueList = NULL;}
    | LB Values RB { $$ = (struct ArrayDef*)malloc(sizeof(struct ArrayDef)); $$->valueList = $2;}
    ;
Values:
      Value  { $$ = (struct ValueList*)malloc(sizeof(struct ValueList)); $$->value = $1; $$->next = NULL;}
    | Value COMMA Values { $$ = (struct ValueList*)malloc(sizeof(struct ValueList)); $$->value = $1; $$->next = $3;}
    ;
%%

void yyerror(const char *s){
    printf("syntax error: ");
}

ValueDef* valuedefcreation(){
    ValueDef* value = (struct ValueDef*)malloc(sizeof(struct ValueDef));
    value->object = NULL;
    value->array = NULL;
    value->string = NULL;
    value->number = 0;
    value->boolean = 0;
    return value;
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
