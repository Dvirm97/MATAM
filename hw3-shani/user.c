#include "user.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "map.h"
#include "set.h"
#include "series.h"
#include "mtm_ex3.h"


struct user {
    char* username;
    int age;
    Set favorites;
    Set friends;
};

typedef char*(*GetNameFunction)(void*);
//static void printList(List list);
//static void printSetUsers(Set set);
static void printSetSeries(Set set);
static List set2list(Set set, GetNameFunction getName);
MapDataElement copyUser(MapDataElement src){
    if (!src) {
        return NULL;
    }
    User dst = malloc(sizeof(*dst));
    if (!dst) {
        return NULL;
    }
    User res = (User)src; //doing this right?
    dst->username = malloc(strlen(res->username)+1);
    strcpy(dst->username, res->username);
    dst->age = res->age;
    dst->favorites = setCopy(res->favorites);
    dst->friends = setCopy(res->friends);
    return dst;
}
SetElement copyUserSet(SetElement src){
    if (!src) {
        return NULL;
    }
    User dst = malloc(sizeof(*dst));
    if (!dst) {
        return NULL;
    }
    User res = (User)src; //doing this right?
    dst->username = malloc(strlen(res->username)+1);
    strcpy(dst->username, res->username);
    dst->age = res->age;
    dst->favorites = setCopy(res->favorites);
    dst->friends = setCopy(res->friends);
    return dst;
}
MapKeyElement userCopyName(MapKeyElement src) {
    char* dst = malloc(strlen(src)+1);
    strcpy(dst, src);
    return dst;
}
char* userGetName(void* user){
    if(!user) return NULL;
    return ((User)user)->username;
}
void deleteUser(MapDataElement user) { //Do it better
    if (!user)
        return;
    free(user);
}
void deleteUserSet(SetElement user) { //Do it better
    if (!user)
        return;
    userDestroy(user);
}
void userDeleteName(MapKeyElement name) {
    free(name);
}
int userCompareNames(MapKeyElement name1, MapKeyElement name2) {
    return strcmp((char*)name1, (char*)name2);
}
int userSetCompareNames(SetElement name1, SetElement name2) {
    return strcmp((char*)name1, (char*)name2);
}

int userCompareNamesForSet(MapKeyElement user1, MapKeyElement user2) {
    return strcmp(((User)user1)->username, ((User)user2)->username);
}
User createUser(const char* newUsername, int newAge) {
    User user = malloc(sizeof(*user));
    if(!user) return NULL;
    user->username = malloc(sizeof(char)*(strlen(newUsername)+1));
    if(!user->username) return NULL;
    strcpy(user->username, newUsername);
    user->age = newAge;
    user->favorites = setCreate(copySeriesSet, deleteSeriesSet, seriesSetCompareNames);
    user->friends = setCreate(copyUserSet, deleteUserSet, userSetCompareNames);
    return user;
}
//I guess the next function should be USER_STATUS (which we should implement), maybe later
MtmFlixResult userAddFavorite(User user, Series series) {
    if (!user || !series)
        return MTMFLIX_NULL_ARGUMENT;
    //checking if user age is in series age range
    //(should be defined separately in a static function)
    //(should probably make this check in mtmflix.c and not here):
    int* seriesAges = seriesGetAges(series);
    if (seriesAges && (user->age < seriesAges[0] || user->age > seriesAges[1]))
        return MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE;
    if (setAdd(user->favorites, series) == SET_OUT_OF_MEMORY)
        return MTMFLIX_OUT_OF_MEMORY;
    return MTMFLIX_SUCCESS;
}
MtmFlixResult userRemoveFavorite(User user, Series series) {
     char* results[5] = {"SET_SUCCESS",
                        "SET_OUT_OF_MEMORY",
                        "SET_NULL_ARGUMENT",
                        "SET_ITEM_ALREADY_EXISTS",
                        "SET_ITEM_DOES_NOT_EXIST"};
    if (!user || !series)
        return MTMFLIX_NULL_ARGUMENT;
    printf("\nfavorites:\n");
    printSetSeries(user->favorites);
    SetResult res = setRemove(user->favorites, series);
    printf("\nfavorites: %s\n",results[res]);
    printSetSeries(user->favorites);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult userAddFriend(User user, User friend) {
    if (!user || !friend)
        return MTMFLIX_NULL_ARGUMENT;
    setAdd(user->friends, friend);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult userRemoveFriend(User user, User friend) {
    if (!user || !friend)
        return MTMFLIX_NULL_ARGUMENT;
    setRemove(user->friends, friend);
    return MTMFLIX_SUCCESS;
}
static List set2list(Set set, GetNameFunction getName){
    if(!set) return NULL;
    List list = listCreate(copyUserName, freeUser);
    if(!list) return NULL;
    char* ptr = getName(setGetFirst(set));
    if(!ptr) return NULL;

    while(ptr){
        listInsertFirst(list, ptr);;
        ptr = getName(setGetNext(set));
    }

    return list;
}
const char* printUser(User user) {
    if(!user) return NULL;
    List friends = set2list(user->friends, userGetName);

    List favorites = set2list(user->favorites, seriesGetName);

    //printf("\nuser:%s\nfavorites:\n",user->username);
    //printList(favorites);
    //printf("done\n\n");

    const char* output = mtmPrintUser(user->username, user->age, friends, favorites);
    printf("%s",output);
    //const char* output = mtmPrintUser(user->username, user->age, friends, favorites);
    //if(!output) printf("output: null\n");
    //else printf("output:\n%s\ndone\n",output);
    return output;
}
void userDestroy(User user){
    setDestroy(user->favorites);
    setDestroy(user->friends);
    free(user);
}
void freeUser(ListElement user){
    userDestroy(user);
}
/*
int stringCompare(ListElement str1, ListElement str2){
    printf("1\n");
    return strcmp((char*)str1, (char*)str2);
}*/
/*static void printList(List list){
    if(!list) return;
    LIST_FOREACH(char*, ptr, list){
        printf("%s\n",ptr);
    }
}*/
ListElement copyUserName(ListElement str){
    char* new_str = malloc(sizeof(char)*(strlen((char*)str)+1));
    strcpy(new_str, (char*)str);
    return (ListElement)new_str;
}

/*static void printSetUsers(Set set){
    if(!set) return;
    User ptr = setGetFirst(set);
    while(ptr){
        printf("%s\n",userGetName(ptr));
        ptr = setGetNext(set);
    }
}
*/
static void printSetSeries(Set set){
    if(!set) return;
    Series ptr = setGetFirst(set);
    while(ptr){
        printf("%s\n",seriesGetName(ptr));
        ptr = setGetNext(set);
    }
}
