#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stringManip.h"

typedef struct ROOM ROOM;

struct ROOM{
    char name[1024];
    char code[100];
    char description[4096];
    ROOM *North;
    ROOM *South;
    ROOM *East;
    ROOM *West;

};


ROOM *roomCreate(ROOM* room){
    ROOM *r = malloc(sizeof(ROOM));
    *r = *room;

    

    return r;
}

ROOM *readRoomFile(char* filename,int *roomArraySize){
    FILE *fp = fopen(filename,"r");

    // end program if file not found
    if(fp == NULL){
        printf("Could not find file.");
        return 0;
    }

    

    // total lines read
    int count = 0;

    // index of current working struct
    int index = 0;
    
    // empty character array for line read from file
    char line[4096];

    // allocate initial memory for struct
    ROOM *s = (ROOM*)malloc(sizeof(ROOM));
    //ROOM *s = head;

    while(fgets(line,sizeof(line),fp) != NULL){
        
        // op = current operation based on which line we're working with it
        int op = count % 4;

        // removes new line and whitespaces, adds room name to current index
        if(op == 0){
            strcpy(s[index].name, str_cut(str_trim(line),11,50));
        }

        // adds room code to current index
        if(op == 1){
            char sub[3];
            strncpy(sub,line + 11,2);
            sub[2] = '\0'; // important to add a null terminator
            
            strcpy(s[index].code, sub);
        }

        // removes new line and whitespaces, adds room description to current index
        if(op == 2){
            char *start = line + strspn(line, "\t\n\r");
            char *end = start + strcspn(start, "\t\n\r");
            *end = '\0';
            strcpy(line, start);

            char sub[4096];
            strncpy(sub,line + 18,4000);

            strcpy(s[index].description, sub);
        }

        // allocate space for next struct room
        if(op == 3){
            ROOM *temp = realloc(s,(1 + count) * sizeof(ROOM));

            // check if realloc was successful
            if(temp != NULL){
                s = temp;
            }else{
                free(s);
                printf("Space could not be allocated");
                return 0;
            }

            index = (count + 1)/4;
        }

        // increase total lines read
        count++;
    }

    *roomArraySize = index;

    return s;
}