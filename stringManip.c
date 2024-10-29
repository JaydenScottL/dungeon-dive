#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//trims string and returns pointer
char *str_trim(char *s){
    while(isspace(*s)) s++;

    char *end = strlen(s) + s -1;

    while(s < end && isspace(*end)) end--; 

     *(end +1) = 0;

    return s;
}

//returns pointer to a substring
char *str_cut(char *s,int start,int end){

    s += start;
    *(s + end) = 0; 

    return s;
}

