#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stringManip.h"
#include "roomManip.h"
#include <time.h>

ROOM *createDungeon(ROOM *room,int roomsize,int dungeonsize){
    
    ROOM* head;
    ROOM* dungeon;
    srand(time(NULL));
    for(int i = 0;i < dungeonsize;i++){
        
        for(int j = 0;j < dungeonsize;j++){
            
            int temp = rand() % roomsize;
            ROOM* newRoom = roomCreate(&room[temp]);
            if(i == 0 && j ==0){
                head = newRoom;
                dungeon = head;
                continue;
            }
            
            dungeon->East = newRoom;
            dungeon->East->West = dungeon;
            dungeon = dungeon->East;
            
        }
    }

    dungeon->East = NULL;

    return head;
}

void printDungeon(ROOM *room){

    ROOM *temp = room;
    
    while(1){

        printf("Room %s: %s\n",temp->code,temp->name);

        if(temp->East == NULL){
            break;
        }

        
        temp = temp->East;
    }
}

void deleteDungeon(ROOM *room){
    free(room);
}

int main(){
    
    char fileNameBuffer[1024];

    printf("Enter file name:");
    fgets(fileNameBuffer,1024,stdin);

    str_trim(fileNameBuffer);

    printf("Using file: %s",fileNameBuffer);

    int roomArraySize = 0;
    int *roomArraySizePtr = &roomArraySize;

    ROOM *roomFile = readRoomFile(fileNameBuffer,roomArraySizePtr);

    ROOM *dungeon = createDungeon(roomFile,roomArraySize,10);

    printDungeon(dungeon);

    return 0;
}

