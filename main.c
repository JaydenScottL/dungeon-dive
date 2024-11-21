#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stringManip.h"
#include "roomManip.h"
#include <time.h>
#include <math.h>
#include <stdbool.h>

/*
Name: Jayden LeCorps
Date: 11/20/2024
*/

typedef struct Player Player;

struct Player{
    ROOM * currentRoom;
};

//returns a pointer to a linked list of rooms
ROOM *createDungeon(ROOM *room,int roomsize,int dungeonsize){
    
    ROOM* head;
    ROOM * currentPosition;
    ROOM * dungeon[dungeonsize][dungeonsize];

    int count = 0;

    srand(time(NULL));
    
    // creates rooms
    for(int i = 0; i < (int)(ceil(sqrt(dungeonsize)));i++){
        for(int j = 0; j < (int)(ceil(sqrt(dungeonsize)));j++){
            
            if(count >= dungeonsize){
                continue;
            }
            
            int temp = rand() % roomsize;
            ROOM * tempRoom = roomCreate(&room[temp]);
            
            

            dungeon[i][j] = tempRoom;

            

            count++;
        }
    }

    // links rooms

    for(int i = 0;i < (int)(ceil(sqrt(dungeonsize)));i++){
        for(int j = 0;j < (int)(ceil(sqrt(dungeonsize)));j++){

            if(dungeon[i][j] == NULL){
                continue;
            }

            
            if(dungeon[i + 1][j] != NULL){
                dungeon[i][j]->East = dungeon[i + 1][j];
                dungeon[i + 1][j]->West = dungeon[i][j];      
            }

            if(i != 0){
                if(dungeon[i - 1][j] != NULL){
                    dungeon[i][j]->West = dungeon[i - 1][j];
                    dungeon[i - 1][j]->East = dungeon[i][j];
                }
            }

            if(dungeon[i][j+1] != NULL){
                dungeon[i][j]->South = dungeon[i][j+1];
                dungeon[i][j + 1]->North = dungeon[i][j];
            }

            if(j != 0){
                if(dungeon[i][j-1] != NULL){
                    
                    dungeon[i][j]->North= dungeon[i][j-1];
                    dungeon[i][j-1]->South = dungeon[i][j];
                }
            }
        }
    }
    

    
    currentPosition = dungeon[0][0];
    
    return currentPosition;
}

//prints linked list of rooms
void printDungeon(ROOM *room){

    ROOM *temp = room;
    
    printf("Visual representation of dungeon: \n");

    while(1){

        //printf("Room %s: %s\n",temp->code,temp->name);
        printf("|%s|",temp->code);

        if(temp->East == NULL){
            bool flag = true;
            while(flag){
                if(temp->West == NULL){

                    if(temp->South != NULL){
                        
                        temp = temp->South;
                        printf("\n");
                        flag = false;
                    }else{
                        printf("\n\n");
                        return;
                    }
                }else{

                    temp = temp->West;
                }
            }
        }else{

        
            temp = temp->East;
        }
    }
}

//deletes linked list of rooms
void deleteDungeon(ROOM *room){

    ROOM *temp = room;
    
    

    while(1){

        if(temp->East == NULL){
            bool flag = true;
            while(flag){
                if(temp->West == NULL){
                    
                    if(temp->South != NULL){
                        ROOM * temp2 = temp;
                        temp = temp->South;
                        free(temp2);
                        flag = false;
                    }else{
                        ROOM * temp2 = temp;
                        free(temp2);

                        printf("Deleted dungeon \n");
                        return;
                    }
                }else{

                    temp = temp->West;
                }
            }
        }else{

        
            temp = temp->East;
        }
    }

    
}


// prints the name and description of a room
void printRoom(ROOM r){
    
    printf("Your current room is: %s\nDescription: %s\n", r.name,r.description);

    if(r.North != NULL){
        printf("North: %s\n",r.North->name);
    }

    if(r.East != NULL){
        printf("East: %s\n",r.East->name);
    }

    if(r.South != NULL){
        printf("South: %s\n",r.South->name);
    }

    if(r.West != NULL){
        printf("West: %s\n",r.West->name);
    }

    printf("\n");
}

int main(){
    
    char fileNameBuffer[1024];
    char dungeonSizeBuffer[10];
    int dungeonSize;

    printf("Enter file name:");
    fgets(fileNameBuffer,1024,stdin);

    str_trim(fileNameBuffer);

    printf("Enter dungeon size:");
    fgets(dungeonSizeBuffer,10,stdin);

    str_trim(dungeonSizeBuffer);

    dungeonSize = atoi(dungeonSizeBuffer);
    

    printf("Using file: %s and dungeon size: %d\n\n",fileNameBuffer,dungeonSize);

    int roomArraySize = 0;
    int *roomArraySizePtr = &roomArraySize;

    ROOM *roomFile = readRoomFile(fileNameBuffer,roomArraySizePtr);

    ROOM *dungeon = createDungeon(roomFile,roomArraySize,dungeonSize);

    printDungeon(dungeon);

    char input[100];

    Player *player = malloc(sizeof(Player));
    player->currentRoom = dungeon;

    printf("\n\n");

    while(1){

        // print current room

        printRoom(*player->currentRoom);

        // get user input
        printf("Enter \"move\" and a direction (n,e,s,w): ");
        fgets(input,100,stdin);

        char *c = malloc(sizeof(char) * 100);
        strcpy(c,input);
        char *s = str_cut(input,0,4);
        
        if(strcmp(input,"move") == 0){
            switch(c[5]){
                case 'w':
                    if(player->currentRoom->West != NULL){
                        player->currentRoom = player->currentRoom->West;
                        printf("Entering %s...",player->currentRoom->name);
                    }else{
                        printf("You can't go in that direction!");
                    }
                break;

                case 'e':
                    if(player->currentRoom->East != NULL){
                        player->currentRoom = player->currentRoom->East;
                        printf("Entering %s...",player->currentRoom->name);
                    }else{
                        printf("You can't go in that direction!");
                    }
                break;

                case 's':
                    if(player->currentRoom->South != NULL){
                        player->currentRoom = player->currentRoom->South;
                        printf("Entering %s...",player->currentRoom->name);
                    }else{
                        printf("You can't go in that direction!");
                    }
                break;

                case 'n':
                    if(player->currentRoom->North != NULL){
                        player->currentRoom = player->currentRoom->North;
                        printf("Entering %s...",player->currentRoom->name);
                    }else{
                        printf("You can't go in that direction!");
                    }
                break;

                default:
                    printf("Please enter a valid direction.");
                break;
            }
        }else{
            printf("Please enter a valid command.");
        }

        printf("\n");
    }

    deleteDungeon(dungeon);

    return 0;
}

