#include "TranslateIntoBinary.h"

char* translateIntToBinary(int num) {
    char* ACommand = (char*)malloc(sizeof(char) * 17);
    if (ACommand == NULL) {
        return NULL;
    }

    for (int i = 0; i < 16; ++i) {
        int bit = (num >> (15 - i)) & 1;
        ACommand[i] = (char)(bit + '0');
    }
    ACommand[16] = '\0';

    return ACommand;
}

char* translateDestToBinary(const char* dest) {
    char* BinaryDest = malloc(sizeof(char) * 4);
    if (dest == NULL) {
        strncpy(BinaryDest, null, 3);
        BinaryDest[3] = '\0';
        return BinaryDest;
    }
    for (int i = 0; i < 7; ++i) {
        if (strcmp(dest, destMap[i].mnemonic) == 0) {
            strncpy(BinaryDest, destMap[i].binaryRepr, 3);
            BinaryDest[3] = '\0';
            return BinaryDest;
        }
    }
    free(BinaryDest);
    return NULL;
}

char* translateJmpToBinary(const char* jmp) {
    char* BinaryJmp = malloc(sizeof(char) * 4);
    if (jmp == NULL) {
        strncpy(BinaryJmp, null, 3);
        BinaryJmp[3] = '\0';
        return BinaryJmp;
    }
    for (int i = 0; i < 7; ++i) {
        if (strcmp(jmp, jmpMap[i].mnemonic) == 0) {
            strncpy(BinaryJmp, jmpMap[i].binaryRepr, 3);
            BinaryJmp[3] = '\0';
            return BinaryJmp;
        }
    }
    free(BinaryJmp);
    return NULL;
}

char* translateCompToBinary(const char* comp) {
    char* BinaryComp = malloc(sizeof(char) * 8);
    for (int i = 0; i < 10; ++i) {
        if (strcmp(comp, A_one_compMap[i].mnemonic) == 0) {
            BinaryComp[0] = '1';
            for (int j = 1; j < 7; ++j) {
                BinaryComp[j] = A_one_compMap[i].binaryRepr[j - 1];
            }
            BinaryComp[7] = '\0';
            return BinaryComp;
        }
    }
    for (int i = 0; i < 18; ++i) {
        if (strcmp(comp, A_zero_compMap[i].mnemonic) == 0) {
            BinaryComp[0] = '0';
            for (int j = 1; j < 7; ++j) {
                BinaryComp[j] = A_zero_compMap[i].binaryRepr[j - 1];
            }
            BinaryComp[7] = '\0';
            return BinaryComp;
        }
    }
    free(BinaryComp);
    return NULL;
}


void copyPartOfCommand(char** part_ptr, char command_symbol, int* partLen) {
    *part_ptr = realloc(*part_ptr, (*partLen + 2) * sizeof(char));
    (*part_ptr)[*partLen] = command_symbol;
    ++(*partLen);
    (*part_ptr)[*partLen] = '\0';
}

char* translateCCommandToBinary(const char* line) {
    if(line == NULL) {
        printf("The line does not exist\n");
        return NULL;
    }
    char* dest = NULL;
    char* comp = NULL;
    char* jmp = NULL;

    int destLen = 0;
    int compLen = 0;
    int jmpLen = 0;

    bool isDest = false;
    bool isComp = true;
    bool isJmp = false;

    int iter = 0;
    while(line[iter] != '\n' && line[iter] != '\0'){
        if(line[iter] == '='){
            isDest = true;
            isComp = false;
        }
        ++iter;
    }

    for (int i = 0; line[i] != '\0' && line[i] != '\n'; ++i) {

        if (isDest && line[i] != '=')
            copyPartOfCommand(&dest, line[i], &destLen);

        if (isComp && line[i] != ';')
            copyPartOfCommand(&comp, line[i], &compLen);

        if (isJmp)
            copyPartOfCommand(&jmp, line[i], &jmpLen);

        if (line[i] == '=') {
            isDest = false;
            isComp = true;
        } else if (line[i] == ';') {
            isComp = false;
            isJmp = true;
        }

    }
    if(jmpLen > 0)
        jmp[jmpLen] = '\0';

    if(destLen > 0)
        dest[destLen] = '\0';
    if(compLen > 0)
        comp[compLen] = '\0';


    char* BinaryDest = translateDestToBinary(dest);
    char* BinaryComp = translateCompToBinary(comp);
    char* BinaryJmp = translateJmpToBinary(jmp);

    char* CCommand = malloc(sizeof(char)*17);

    for(int i = 0; i < 3; ++i){
        CCommand[i] = '1';
    }
    for(int i = 3; i < 10; ++i){
        CCommand[i] = BinaryComp[i-3];
    }
    for(int i = 10; i < 13; ++i){
        CCommand[i] = BinaryDest[i-10];
    }
    for(int i = 13; i < 16; ++i){
        CCommand[i] = BinaryJmp[i-13];
    }

    CCommand[16] = '\0';


    if(BinaryDest != NULL){
        free(BinaryDest);
    }
    if(BinaryComp != NULL){
        free(BinaryComp);
    }
    if(BinaryJmp != NULL){
        free(BinaryJmp);
    }

    if (dest != NULL) {
        free(dest);
    }
    if (comp != NULL) {
        free(comp);
    }
    if (jmp != NULL) {
        free(jmp);
    }

    return CCommand;
}




char* translateCommandIntoMachineCode(const char* line){
    if(line == NULL){
        return NULL;
    }

    if (line[0] == '@') {
        char temp[BUFFER];
        int i = 1;
        for (; line[i] != '\n' && line[i] != '\0'; ++i) {
            temp[i-1] = line[i];
        }
        temp[i-1] = '\0';
        int num = strtol(temp, NULL, 10);
        return translateIntToBinary(num);
    }
    else{
        return translateCCommandToBinary(line);
    }

}