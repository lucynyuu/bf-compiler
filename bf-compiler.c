#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateCode(FILE* fout , FILE* fin) {
    char c;
    while ((c = fgetc(fin)) != EOF) {
        switch (c) {
            case '+':
                fprintf(fout, "++*ptr;");
                break;
            case '-':
                fprintf(fout, "--*ptr;");
                break;
            case '.':
                fprintf(fout, "putchar(*ptr);");
                break;
            case '>':
                fprintf(fout, "++ptr;");
                break;
            case '<':
                fprintf(fout, "--ptr;");
                break;
            case '[':
                fprintf(fout, "while (*ptr) {");
                break;
            case ']':
                fprintf(fout, "}");
                break;
            default:
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2)
        return -1;
    FILE *fin, *fout;

    char* file = malloc(strlen(argv[1]) - 3 + 1);
    char* pos = strstr(argv[1], ".bf");
    if (pos != NULL) {
        strncpy(file, argv[1], pos - argv[1]);
        strcpy(file + (pos - argv[1]), pos + 3);
    }
    else {
        strcpy(file, argv[1]);
    }

    fin = fopen(argv[1], "r");

    char fname[50];
    sprintf(fname, "%s.c", file);
    fout = fopen(fname, "w");

    fprintf(fout, "#include <stdio.h>\n");
    fprintf(fout, "int main() { char array[30000] = {0}; char *ptr = array;");

    generateCode(fout, fin);

    fprintf(fout, "}");
    fclose(fin);
    fclose(fout);


    char command[50];
    sprintf(command, "gcc %s -o %s", fname, file);
    system(command);
    
    #ifdef linux
    sprintf(command, "rm %s", fname);
    #endif
    #ifdef _WIN32
    sprintf(command, "del %s", fname);
    #endif
    system(command);
}