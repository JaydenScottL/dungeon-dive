#ifndef ROOM_MANIP
#define ROOM_MANIP

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

ROOM *roomCreate(ROOM* room);

ROOM *readRoomFile(char* filename,int *roomArraySize);

#endif