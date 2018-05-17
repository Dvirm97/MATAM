//
// Created by shani on 16/05/2018.
//
#define INITIAL_SIZE 1
#define INVALID -1
#include "map_mtm.h"
#include <stdlib.h>

typedef struct pair{
    MapKeyElement key;
    MapDataElement data;
}*Pair;

typedef struct node {
    Pair pair;
    struct node* next;
}*Node;

struct Map_t{
    Node pairs_list;
    Node iterator;
    MapDataElement (*copyData)(MapDataElement);
    MapKeyElement  (*copyKey)(MapKeyElement);
    void (*freeData)(MapDataElement);
    void (*freeKey)(MapKeyElement);
    int (*compareKeys)(MapKeyElement, MapKeyElement);
};

static int find(Map map, MapKeyElement key);

Map mapCreate(copyMapDataElements copyDataElement, copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement, freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements){
    Map map = malloc(sizeof(*map));
    if(!map) return NULL;

    map->iterator = NULL;
    map->pairs_list = NULL;
    map->copyData = copyDataElement;
    map->copyKey = copyKeyElement;
    map->freeData = freeDataElement;
    map->freeKey = freeKeyElement;
    map->compareKeys = compareKeyElements;

    return map;
}
void mapDestroy(Map map){
    if(!map) return;
    while(map->pairs_list){
        Node toDelete = map->pairs_list;
        map->pairs_list = map->pairs_list->next;
        map->freeKey(toDelete->pair->key);
        map->freeData(toDelete->pair->data);
    }
    free(map);
}
Map mapCopy(Map map){
    Map new_map = mapCreate(map->copyData, map->copyKey, map->freeData,
                            map->freeKey, map->compareKeys);
    Node ptr = map->pairs_list;
    while(ptr){
        mapPut(new_map, ptr->pair->key, ptr->pair->data);
        ptr = ptr->next;
    }
    return new_map;
}
int mapGetSize(Map map){
    if(!map) return -1;
    int counter = 0;
    Node ptr = map->pairs_list;
    while(ptr){
        counter++;
        ptr = ptr->next;
    }
    return counter;
}
bool mapContains(Map map, MapKeyElement element){
    if(!map || !element) return false;
    Node ptr = map->pairs_list;
    while(ptr){
        if(!map->compareKeys || !ptr->pair || !ptr->pair->key) return false;
        if(map->compareKeys(ptr->pair->key, element) == 0){
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}
MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement){
    if(!map || !keyElement) return MAP_NULL_ARGUMENT;
    Node ptr = map->pairs_list;
    while(ptr){
        if(!map->compareKeys || !ptr->pair || !ptr->pair->key)
            return MAP_NULL_ARGUMENT;
        if(map->compareKeys(ptr->pair->key, keyElement) == 0){
            ptr->pair->data = map->copyData(dataElement);
            if(!ptr->pair->data) return MAP_OUT_OF_MEMORY;
            return MAP_SUCCESS;
        }
        else{
            ptr = ptr->next;
        }
    }


    Pair new_pair = malloc(sizeof(Pair));
    if(!new_pair) return MAP_OUT_OF_MEMORY;
    new_pair->key = map->copyKey(keyElement);
    new_pair->data = map->copyData(dataElement);

    Node new_node = malloc(sizeof(Node));
    if(!new_node) return MAP_OUT_OF_MEMORY;
    new_node->pair = new_pair;
    new_node->next = NULL;

    if(!map->pairs_list){
        map->pairs_list = new_node;
    }
    else {
        ptr = map->pairs_list;
        while (ptr->next) {
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }
    return MAP_SUCCESS;
}
MapDataElement mapGet(Map map, MapKeyElement keyElement){
    if(!map || !keyElement) return NULL;
    Node ptr = map->pairs_list;
    while(ptr){
        if(!map->compareKeys || !ptr->pair || !ptr->pair->key) return NULL;
        if(map->compareKeys(ptr->pair->key, keyElement) == 0){
            return ptr->pair->data;
        }
        ptr = ptr->next;
    }
    return NULL;
}
MapResult mapRemove(Map map, MapKeyElement keyElement){
    if(!map || !keyElement) return MAP_NULL_ARGUMENT;
    if(!map->pairs_list) return MAP_ITEM_DOES_NOT_EXIST;

    Node ptr = map->pairs_list->next, prev = map->pairs_list;

    if(!map->compareKeys || !ptr->pair || !ptr->pair->key)
        return MAP_NULL_ARGUMENT;

    if(map->compareKeys(prev->pair->key, keyElement) == 0) {
        map->pairs_list = ptr;
        map->freeKey(prev->pair->key);
        map->freeData(prev->pair->data);
        free(prev);
        return MAP_SUCCESS;
    }

    while(ptr){
        if(!map->compareKeys || !ptr->pair || !ptr->pair->key)
            return MAP_NULL_ARGUMENT;

        if(map->compareKeys(ptr->pair->key, keyElement) == 0){
            prev->next = ptr->next;
            map->freeKey(ptr->pair->key);
            map->freeData(ptr->pair->data);
            return MAP_SUCCESS;
        }
        else{
            ptr = ptr->next;
            prev = prev->next;
        }
    }
    return MAP_ITEM_DOES_NOT_EXIST;
}
MapKeyElement mapGetFirst(Map map) {
    if(!map) return NULL;
    map->iterator = map->pairs_list;
    if(!map->iterator || !map->iterator->pair) return NULL;
    return map->iterator->pair->key;
}
MapKeyElement mapGetNext(Map map){
    if(!map || !map->iterator) return NULL;
    map->iterator = map->iterator->next;
    return map->iterator->pair->key;
}
MapResult mapClear(Map map){
    if(!map || !map->freeKey || !map->freeData) return MAP_NULL_ARGUMENT;

    while(map->pairs_list){
        Node ptr = map->pairs_list;
        map->pairs_list = map->pairs_list->next;
        if(ptr->pair){
            map->freeKey(ptr->pair->key);
            map->freeData(ptr->pair->data);
        }
    }

    return MAP_SUCCESS;
}

