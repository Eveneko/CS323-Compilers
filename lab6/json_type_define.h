typedef struct Json {
    struct Value value;
    char *name;
    enum {Object, Array, STRING, NUMBER, TRUE, FALSE, VNULL} category;
} Json;

typedef struct Value {
    union value {
        struct Object *object;
        struct Array *array;
        char *string;
        int intNum;
        double doubleNum;
        enum {True, False} boolean;
        enum {NULL} null;
    };
} Value;

typedef struct Object {
    struct Member **member;
    int size;
} Object;

typedef struct Array {
    struct Value *base;
    int size;
} Array;

typedef struct Member {
    char *key;
    struct Value *value;
} Member;

