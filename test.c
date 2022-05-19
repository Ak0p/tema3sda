#include <stdio.h>
#include <string.h>


void main() {
    char *v = (char*)calloc(15, sizeof(char));
    v = "nume";
    printf("%s\n", v);
}