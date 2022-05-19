#include "tarb.h"
#define wordSize 50
#define lineSize 10


void touch(TADir actDir, char *nume) {
    TAFile fisier = ConstrFisier(nume);
    TAFile p = actDir->files;
    if (GetDPos(actDir->dirs, nume) != NULL) {
        printf("Directory %s already exists!\n", nume);
        return;
    }
    int ret_val = insertFisier(p, fisier);

    switch (ret_val) {
        case 1:
            return;
        case 0:
            printf("File %s already exists!\n", nume);
            return;
        case -1:
            printf("Eroare\n");
            return;
    }
}


int main() {

    TADir root = InitD();
    

    // parsare

    while (1) {
    char *line = (char *)calloc(lineSize, sizeof(char));
    char **word = (char **)calloc(wordSize, sizeof(char *));
    int wordCount = 0;
    if (!fgets(line, lineSize, stdin)) {
      free(word);
      free(line);
      break;
    }
    if (strrchr(line, '\n')) *strrchr(line, '\n') = '\0';

    word[wordCount] = strtok(line, " ");
    while (word[wordCount]) {
      wordCount++;
      word[wordCount] = strtok(NULL, " ");
    }


    if (strcmp(word[0], "touch") == 0) {

    }

    if (strcmp(word[0], "mkdir") == 0) {
        
    }

    if (strcmp(word[0], "ls") == 0) {
        
    }

    if (strcmp(word[0], "rm") == 0) {
        
    }

    
    if (strcmp(word[0], "rmdir") == 0) {
        
    }

    if (strcmp(word[0], "cd") == 0) {
        
    }

    if (strcmp(word[0], "find") == 0) {
        
    }

    


    free(word);
    free(line);
    }
}