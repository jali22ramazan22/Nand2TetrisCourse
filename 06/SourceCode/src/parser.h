#ifndef ASM2HACK_PARSER_H
#define ASM2HACK_PARSER_H
#define IN 1
#define OUT 0

#include "common.h"

#define SCREEN "SCREEN"
#define KBD "KBD"


#define SP "SP"
#define LCL "LCL"
#define ARG "ARG"
#define THIS "THIS"
#define THAT "THAT"


#define R0 "R0"
#define R1  "R1"
#define R2  "R2"
#define R3  "R3"
#define R4  "R4"
#define R5  "R5"
#define R6  "R6"
#define R7  "R7"
#define R8  "R8"
#define R9  "R9"
#define R10 "R10"
#define R11 "R11"
#define R12 "R12"
#define R13 "R13"
#define R14 "R14"
#define R15 "R15"


typedef struct{
    char name[BUFFER];
    int address;
}label;

typedef struct{
    char name[BUFFER];
    int queue;
}var;
typedef enum {
    not_commentary,
    has_commentary,
    is_commentary
}commentary;
commentary isCommentary(char* line);
char** divide_into_lines(char* file_content);

void eraseElement(int index, char** array);
char* getLines(FILE* fp);
int lines_count(const char* file_content);

label** LabelTable(char** lines_array);
var** VarTable(char** lines_array);
void translateVar(var** VarTable, char* line);
void translateLabel(label** LabelTable, char* line);

int IsItKEYWORD(char* Var_name);


#endif //ASM2HACK_PARSER_H
