#ifndef KEYSDOWN
#define KEYSDOWN
struct keysdown{
    char rightd;
    char downs;
    char lefta;
    char upw;
    char zj;
    char xk;
    char cl;
};
//to initialize struct:
//struct* keysdown keys = calloc(1,sizeof(struct keysdown));
//Important to calloc to initialize all values to 0
#endif
