typedef struct JsonDef {
    struct ValueDef* value;
} JsonDef;

typedef struct ValueDef {
    enum {OBJECT, ARRAY, STRING, NUMBER, BOOLEAN, VNULL} category;
    union {
        struct ObjectDef *object;
        struct ArrayDef *array;
        char *string;
        double number;
        int boolean;
    };
} ValueDef;

typedef struct ObjectDef {
    struct MemberList *members;
} ObjectDef;

typedef struct MemberList {
    struct MemberDef *member;
    struct MemberList *next;
} MemberList;

typedef struct MemberDef {
    char *string;
    struct ValueDef *value;
} MemberDef;

typedef struct ArrayDef {
    struct ValueList *valueList;
} ArrayDef;

typedef struct ValueList {
    struct ValueDef *value;
    struct ValueList *next;
} ValueList;

typedef struct StringDef {
    char *string;
} StringDef;

