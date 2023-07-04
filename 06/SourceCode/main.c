#include "src/common.h"
#include "src/openfile.h"
#include "src/parser.h"
#include "src/TranslateIntoBinary.h"
static char* MAIN_PATH = NULL;

void DestructTwoDimensionalArray(char** CharArr, var** VarArr, label** LabelArr){
    if(CharArr != NULL){
        for(int i = 0; CharArr[i] != NULL; ++i){
            free(CharArr[i]);
        }
        free(CharArr);
    }
    if(VarArr != NULL){
        for(int i = 0; VarArr[i] != NULL; ++i){
            free(VarArr[i]);
        }
        free(VarArr);
    }
    if(LabelArr != NULL){
        for(int i = 0; LabelArr[i] != NULL; ++i){
            free(LabelArr[i]);
        }
        free(LabelArr);
    }
}
char* getNameOfFile(const char* filepath) {
    char temp[BUFFER];
    char postFix[] = ".hack";
    int i = 0;

    for (; !(filepath[i] == '.' && i > 2) && filepath[i] != '\0'; ++i) {
        temp[i] = filepath[i];
    }
    temp[i] = '\0';

    if (filepath[i] == '\0') {

        return NULL;
    }

    size_t fileNameLength = strlen(temp) + strlen(postFix) + 1;
    char* fileName = malloc(sizeof(char) * fileNameLength);
    strcpy(fileName, temp);
    strcat(fileName, postFix);
    return fileName;
}
int main(int argc, char** argv){
    if(argv[1] == NULL){
        printf("Error");
        return -1;
    }
    char* Filename = getNameOfFile(argv[1]);
    FILE* fp = openFile(argv[1]);
    if (fp == NULL) {
        printf("Error: Failed to open file '%s'.\n", argv[1]);
        return -1;
    }
    char* file_content = getLines(fp);
    char** lines = divide_into_lines(file_content);
    fclose(fp);


    label** labelTable = LabelTable(lines);
    if(labelTable != NULL) {
        for (int i = 0; lines[i] != NULL; ++i) {
            translateLabel(labelTable, lines[i]);
        }
    }
    var** Var = VarTable(lines);
    if(Var != NULL) {
        for (int i = 0; lines[i] != NULL; ++i) {
            translateVar(Var, lines[i]);
        }
    }

    FILE* hackCon = fopen(Filename, "w+");
    for(int i = 0; lines[i] != NULL; ++i){
        char* BIN = translateCommandIntoMachineCode(lines[i]);
        fprintf(hackCon, "%s\n", BIN);
        free(BIN);
    }
    fclose(hackCon);
    DestructTwoDimensionalArray(lines, Var, labelTable);
}
