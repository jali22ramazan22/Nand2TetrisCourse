#ifndef ASM2HACK_TRANSLATEINTOBINARY_H
#define ASM2HACK_TRANSLATEINTOBINARY_H
#include "common.h"
typedef struct{
    char mnemonic[4];
    char binaryRepr[6];
}CCommandMnemonic;


static const char null[3] = "000";

static const CCommandMnemonic destMap[7] = {
        {"M", "001"},
        {"D", "010"},
        {"MD", "011"},
        {"A", "100"},
        {"AM", "101"},
        {"AD", "110"},
        {"AMD", "111"}
};

static const CCommandMnemonic jmpMap[7] = {
        {"JGT", "001"},
        {"JEQ", "010"},
        {"JGE", "011"},
        {"JLT", "100"},
        {"JNE", "101"},
        {"JLE", "110"},
        {"JMP", "111"}
};


static const CCommandMnemonic A_zero_compMap[18] = {
        {"0", "101010"},
        {"1", "111111"},
        {"-1", "111010"},
        {"D", "001100"},
        {"A", "110000"},
        {"!D", "001101"},
        {"!A", "110001"},
        {"-D", "001111"},
        {"-A", "110011"},
        {"D+1", "011111"},
        {"A+1", "110111"},
        {"D-1", "001110"},
        {"A-1", "110010"},
        {"D+A", "000010"},
        {"D-A", "010011"},
        {"A-D", "000111"},
        {"D&A", "000000"},
        {"D|A", "010101"}
};

static const CCommandMnemonic A_one_compMap[10] = {
        {"M", "110000"},
        {"!M", "110001"},
        {"-M", "110011"},
        {"M+1", "110111"},
        {"M-1", "110010"},
        {"D+M", "000010"},
        {"D-M", "010011"},
        {"M-D", "000111"},
        {"D&M", "000000"},
        {"D|M", "010101"}
};



char* translateDestToBinary(const char* dest);
char* translateCompToBinary(const char* comp);
char* translateJmpToBinary(const char* jmp);



char* translateCommandIntoMachineCode(const char* line);

char* translateIntToBinary(int num);

char* translateCCommandToBinary(const char* line);

#endif //ASM2HACK_TRANSLATEINTOBINARY_H