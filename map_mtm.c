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

Map mapCreate(copyMapDataElements copyDataElement, copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement, freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements){
    if(!copyDataElement || !copyKeyElement ||!compareKeyElements ||
            !freeDataElement || !freeKeyElement) return NULL;

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
    // Check input
    if(!map) return NULL;

    // Create a new map
    Map new_map = mapCreate(map->copyData, map->copyKey, map->freeData,
                            map->freeKey, map->compareKeys);

    // Add map items to new map
    Node ptr = map->pairs_list;
    while(ptr){
        if(!ptr->pair) {
            mapDestroy(new_map);
            return NULL;
        }
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
    // Check input
    if(!map || !keyElement || !dataElement) return MAP_NULL_ARGUMENT;

    // Go through map elements
    Node ptr = map->pairs_list;
    while(ptr){

        // Check if element is null
        if(!map->compareKeys || !ptr->pair || !ptr->pair->key)
            return MAP_NULL_ARGUMENT;

        // Check if key exists and if it does insert new data
        if(map->compareKeys(ptr->pair->key, keyElement) == 0){
            ptr->pair->data = map->copyData(dataElement);
            if(!ptr->pair->data) return MAP_OUT_OF_MEMORY;
            return MAP_SUCCESS;
        }
        else{
            ptr = ptr->next;
        }
    }

    // if key does'nt already exist create a new element
    Pair new_pair = malloc(sizeof(Pair));
    if(!new_pair) return MAP_OUT_OF_MEMORY;
    new_pair->key = map->copyKey(keyElement);
    new_pair->data = map->copyData(dataElement);

    // Insert new element to map
    Node new_node = malloc(sizeof(Node));
    if(!new_node) return MAP_OUT_OF_MEMORY;
    new_node->pair = new_pair;
    new_node->next = NULL;

    // If map is empty enter new element
    if(!map->pairs_list){
        map->pairs_list = new_node;
    }  else { // Map isn't empty, add new element to existing sorted list
        ptr = map->pairs_list;
        Node prev = NULL;
        if(!ptr->pair) return MAP_NULL_ARGUMENT;

        // Inset element to it's right place by the given compare function
        while (ptr != NULL && (map->compareKeys(ptr->pair->key,
                                                new_node->pair->key) < 0)) {
            prev = ptr;
            ptr = ptr->next;
            if(ptr && !ptr->pair) return MAP_NULL_ARGUMENT;
        }
        new_node->next = ptr;
        if(prev != NULL){
            prev->next = new_node;
        }
        else{
            map->pairs_list = new_node;
        }
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
    // Check input
    if(!map || !keyElement) return MAP_NULL_ARGUMENT;
    if(!map->pairs_list) return MAP_ITEM_DOES_NOT_EXIST;
    Node ptr = map->pairs_list->next, prev = map->pairs_list;
    if(!map->compareKeys || !map->freeData || !map->freeKey || !prev->pair)
        return MAP_NULL_ARGUMENT;

    // check first if first element is the wanted one to free and free it if is
    if(map->compareKeys(prev->pair->key, keyElement) == 0) {
        map->pairs_list = ptr;
        map->freeKey(prev->pair->key);
        map->freeData(prev->pair->data);
        return MAP_SUCCESS;
    }

    // Go through list
    while(ptr){
        if(!ptr->pair) return MAP_NULL_ARGUMENT;

        // if wanted element free it
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
    if(!map || !map->iterator || !map->iterator->pair) return NULL;
    map->iterator = map->iterator->next;
    if(!map->iterator || !map->iterator->pair) return NULL;
    return map->iterator->pair->key;
}
MapResult mapClear(Map map){
    // Check input
    if(!map || !map->freeKey || !map->freeData) return MAP_NULL_ARGUMENT;

    // Go through list
    while(map->pairs_list){
        Node ptr = map->pairs_list;
        map->pairs_list = map->pairs_list->next;

        // If wanted element then free it
        if(ptr->pair){
            map->freeKey(ptr->pair->key);
            map->freeData(ptr->pair->data);
        }
    }

    return MAP_SUCCESS;
}

