#include "parser.h"

commentary isCommentary(char* line){
    for(int i = 0; line[i] != '\0'; ++i){
        if(line[i] == '/' && line[i+1] == '/') {
            if(i == 0){
                return is_commentary;
            }
            else{
                line[i] = '\0';
                return has_commentary;
            }
        }

    }
    return 0;
}

void eraseElement(int index, char** array) {
    free(array[index]);

    int last;
    for (last = index; array[last] != NULL; ++last)
        ;

    for (int i = index; array[i] != NULL; ++i) {
        array[i] = array[i + 1];
    }

    free(array[last - 1]);
    array[last - 1] = NULL;
}


char* getLines(FILE* fp){
    int c;
    int i = 0;
    char* file_content = NULL;
    while ((c = fgetc(fp)) != EOF) {
        file_content = realloc(file_content, (i+1) * sizeof(char));
        file_content[i++] = (char)c;
    }
    file_content[i++] = '\n';
    file_content[i] = '\0';
    fclose(fp);
    return file_content;
}

int lines_count(const char* file_content) {
    int lines_count = 0;
    int state = OUT;
    for (int i = 0; file_content[i] != '\0'; ++i) {
        if (file_content[i] == '\n') {
            state = OUT;
        } else if (state == OUT) {
            state = IN;
            ++lines_count;
        }
    }
    return lines_count;
}


char** divide_into_lines(char* file_content) {
    char* line_ptr = NULL;
    char** lines_array = NULL;

    int lines = lines_count(file_content);
    lines_array = malloc(sizeof(char*) * (lines + 1));
    lines_array[lines] = NULL;

    int state = OUT;
    int j = 0;
    int k = 0;
    char buffer[BUFFER];

    for (int i = 0; file_content[i] != '\0'; ++i) {
        if (file_content[i] == '\n') {
            state = OUT;

            buffer[j] = '\0';

            if (isCommentary(buffer) == 2) {
                j = 0;
                continue;
            }

            
            if (j > 0 || buffer[j-1] == '\n') {
                line_ptr = malloc(sizeof(char) * (j + 1));
                lines_array[k++] = line_ptr;
                strcpy(line_ptr, buffer);
            }
            j = 0;
        } else if (state == OUT) {
            if(file_content[i] != ' ' && file_content[i] != '\t')
                buffer[j++] = file_content[i];
            state = IN;
        } else {
            if(file_content[i] != ' ' && file_content[i] != '\t')
                buffer[j++] = file_content[i];

        }
    }
    lines_array[k] = NULL;
    return lines_array;
}

label** LabelTable(char** lines_array) {
    label** LabelArr = NULL;
    label* labelObj = NULL;

    int arr_cnt = 0;

    for (int i = 0; lines_array[i] != NULL; ++i) {
        if (lines_array[i][0] == '(')
            ++arr_cnt;
    }
    if (arr_cnt == 0) {
        return NULL;
    }

    LabelArr = malloc(sizeof(label*) * (arr_cnt + 1));
    int it = 0;
    for (int i = 0; lines_array[i] != NULL; ++i) {
        if (lines_array[i][0] == '(') {
            int k = 0;

            labelObj = malloc(sizeof(label));
            for (int j = 1; lines_array[i][j] != ')' && lines_array[i][j] != '\n'; ++j) {
                labelObj->name[k++] = lines_array[i][j];
            }
            labelObj->name[k] = '\0';
            labelObj->address = i;
            LabelArr[it] = labelObj;
            eraseElement(i, lines_array);
            --i;
            ++it;
        }
    }

    LabelArr[arr_cnt] = NULL;

    return LabelArr;
}

var** VarTable(char** lines_array) {
    var** VarTable = NULL;
    var* Var = NULL;

    int arr_cnt = 0;

    for (int i = 0; lines_array[i] != NULL; ++i) {
        if (lines_array[i][0] == '@') {
            char second = tolower(lines_array[i][1]);
            if (!(second >= 48 && second <= 57))
                ++arr_cnt;
        }
    }

    if (arr_cnt == 0) {
        return NULL;
    }

    VarTable = malloc(sizeof(var*) * (arr_cnt + 1));

    int it = 0;
    int varCounter = 0;
    for (int i = 0; lines_array[i] != NULL; ++i) {
        if (lines_array[i][0] == '@') {
            char second = tolower(lines_array[i][1]);
            if (!(second >= 48 && second <= 57)) {
                char temp[BUFFER];
                strcpy(temp, lines_array[i]);
                int k = 0;
                int duplicate = 0;

                for (int j = 0; j < it; ++j) {
                    if (strcmp(lines_array[i] + 1, VarTable[j]->name) == 0) {
                        duplicate = 1;
                        break;
                    }
                }
                if (!duplicate) {
                    Var = malloc(sizeof(var));
                    for (int j = 1; lines_array[i][j] != '\n' && lines_array[i][j] != '\0'; ++j) {
                        Var->name[k++] = lines_array[i][j];
                    }
                    Var->name[k] = '\0';
                    int keyword = IsItKEYWORD(Var->name);
                    if(keyword != -1){
                        Var->queue = keyword;
                    }
                    else{
                        Var->queue = varCounter + 16;
                        ++varCounter;
                    }

                    VarTable[it++] = Var;
                }
            }
        }
    }

    VarTable[it] = NULL;
    return VarTable;
}

int IsItKEYWORD(char* Var_name){
    if(0 == strcmp(Var_name, R0)) {
        return 0;
    }
    else if(strcmp(Var_name, R1) == 0) {
        return 1;
    }
    else if(strcmp(Var_name, R2) == 0) {
        return 2;
    }
    else if(strcmp(Var_name, R3) == 0) {
        return 3;
    }
    else if(strcmp(Var_name, R4) == 0) {
        return 4;
    }
    else if(strcmp(Var_name, R5) == 0) {
        return 5;
    }
    else if(strcmp(Var_name, R6) == 0) {
        return 6;
    }
    else if(strcmp(Var_name, R7) == 0) {
        return 7;
    }
    else if(strcmp(Var_name, R8) == 0) {
        return 8;
    }
    else if(strcmp(Var_name, R9) == 0) {
        return 9;
    }
    else if(strcmp(Var_name, R10) == 0) {
        return 10;
    }
    else if(strcmp(Var_name, R11) == 0) {
        return 11;
    }
    else if(strcmp(Var_name, R12) == 0) {
        return 12;
    }
    else if(strcmp(Var_name, R13) == 0) {
        return 13;
    }
    else if(strcmp(Var_name, R14) == 0) {
        return 14;
    }
    else if(strcmp(Var_name, R15) == 0) {
        return 15;
    }
    else if(strcmp(Var_name, SCREEN) == 0) {
        return 16384;
    }
    else if(strcmp(Var_name, KBD) == 0) {
        return 24576;
    }
    else if(strcmp(Var_name, SP) == 0) {
        return 0;
    }
    else if(strcmp(Var_name, LCL) == 0) {
        return 1;
    }
    else if(strcmp(Var_name, ARG) == 0) {
        return 2;
    }
    else if(strcmp(Var_name, THIS) == 0) {
        return 3;
    }
    else if(strcmp(Var_name, THAT) == 0) {
        return 4;
    }
    return -1;
}
void changeElement(char* array, const char* needed) {
    int i = 0;
    for (; needed[i] != '\0'; ++i) {
        array[i] = needed[i];
    }
    array[i] = '\0';
}

void translateLabel(label** LabelTable, char* line){

        if(LabelTable == NULL || line == NULL)
            return;
        if (line[0] == '@') {
            char temp[BUFFER];
            int j;
            for (j = 1; line[j] != '\n' && line[j] != '\0'; ++j) {
                temp[j - 1] =line[j];
            }
            temp[j - 1] = '\0';

            for (int k = 0; LabelTable[k] != NULL; ++k) {
                if (LabelTable[k]->name != NULL && 0 == strcmp(temp, LabelTable[k]->name)) {
                    char address[BUFFER];
                    snprintf(address, BUFFER, "@%d", LabelTable[k]->address);
                    changeElement(line, address);
                }
            }
        }


}

void translateVar(var** VarTable, char* line) {
    if (line[0] == '@') {
        char temp[BUFFER];
        int j;
        for (j = 0; line[j + 1] != '\n' && line[j + 1] != '\0'; ++j) {
            temp[j] = line[j + 1];
        }
        temp[j] = '\0';
        if (VarTable != NULL){
        for (int k = 0; VarTable[k] != NULL; ++k) {

             if(VarTable[k] != NULL && strcmp(temp, VarTable[k]->name) == 0) {
                char queue[BUFFER];
                snprintf(queue, BUFFER, "@%d", VarTable[k]->queue);
                changeElement(line, queue);
            }
        }
    }
    }
}

