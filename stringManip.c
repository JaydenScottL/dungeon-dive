#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *str_trim(char *s){
    while(isspace(*s)) s++;

    char *end = strlen(s) + s -1;

    while(s < end && isspace(*end)) end--; 

     *(end +1) = 0;

    return s;
}

char *str_cut(char *s,int start,int end){

    s += start;
    *(s + end) = 0; 

    return s;
}

