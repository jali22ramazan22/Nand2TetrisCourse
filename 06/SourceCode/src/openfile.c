#include "openfile.h"


FILE* openFile(char* filepath){
    FILE* fp;
    fp = fopen(filepath, "r");
    return fp;
}