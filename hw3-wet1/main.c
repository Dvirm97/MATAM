#include <stdio.h>
#include "map_mtm.h"
#include <string.h>
#include <stdlib.h>

int compKeys(MapKeyElement key1, MapKeyElement key2);
MapKeyElement copyKey(MapKeyElement key);
MapDataElement copyName(MapDataElement name);
void freeKey(MapKeyElement key);
void freeName(MapDataElement name);

int main() {
    int keys[3]={1,2,3};
    char* names[3] = {"Dana","Yosi","Ben"};
    Map map = mapCreate(copyName, copyKey, freeName, freeKey, compKeys);
    for(int i=0; i<3; i++){
        mapPut(map, (MapKeyElement)keys[i], (MapDataElement)names[i]);
    }
    int len = mapGetSize(map);
    printf("map:\nlen=%d\n",len);
    for(int i=0; i<len; i++){
        printf("%d:%s\n",i+1,(char*)(mapGet(map, (MapKeyElement)(i+1))));
    }
    if(mapContains(map, (MapKeyElement)2)){
        printf("contain\nYosi is in\n");
    }
    else printf("conatain\nYosi isn't in\n");

    printf("\n");
    mapRemove(map, (MapKeyElement)(2));
    len = mapGetSize(map);
    printf("remove\nlen=%d\n",len);
    for(int i=0; i<3; i++){
        printf("%d:%s\n",i+1,(char*)(mapGet(map, (MapKeyElement)(i+1))));
    }
    if(mapContains(map, (MapKeyElement)2)){
        printf("contain\nYosi is in\n");
    }
    else printf("contain\nYosi isn't in\n");

    printf("new map\n");
    Map new_map = mapCopy(map);
    for(int i=0; i<3; i++){
        printf("%d:%s\n",i+1,(char*)(mapGet(new_map, (MapKeyElement)(i+1))));
    }
    printf("clear\n");
    mapClear(new_map);
    for(int i=0; i<3; i++){
        printf("%d:%s\n",i+1,(char*)(mapGet(new_map, (MapKeyElement)(i+1))));
    }

    mapDestroy(map);
    return 0;
}

int compKeys(MapKeyElement key1, MapKeyElement key2){
    return (int)key1-(int)key2;
}
MapKeyElement copyKey(MapKeyElement key){
   return (int*)key ;
}
MapDataElement copyName(MapDataElement name){
    char* string = (char*)name;
    int len = strlen(string);
    char* new_name = malloc(sizeof(char)*(len+1));
    for(int i=0; i<len; i++){
        new_name[i]=string[i];
    }
    new_name[len]='\0';
    return new_name;
}
void freeKey(MapKeyElement key){
    free(key);
}
void freeName(MapDataElement name){
    free(name);
}



