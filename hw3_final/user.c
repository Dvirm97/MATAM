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
//static void printSetSeries(Set set);
static List set2list(Set set, GetNameFunction getName);
MapDataElement copyUser(MapDataElement src) {
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
void deleteUser(MapDataElement user) { //Do it better
    if (!user)
        return;
    free(user);
}
void deleteUserSet(SetElement user) { //Do it better
    if (!user) return;
    userDestroy((User)user);
}
void userDeleteName(MapKeyElement name) {
    free(name);
}
int userCompareNames(MapKeyElement name1, MapKeyElement name2) {
    return strcmp((char*)name1, (char*)name2);
}
int userSetCompareNames(SetElement user1, SetElement user2) {
    return strcmp(((User)user1)->username, ((User)user2)->username);
}
char* userGetName(void* user){
    if(!user) return NULL;
    return ((User)user)->username;
}
User createUser(const char* newUsername, int newAge) {
    User user = malloc(sizeof(*user));
    if(!user)
        return NULL;
    user->username = malloc(sizeof(char)*(strlen(newUsername)+1));
    if(!user->username)
        return NULL;
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
    if (!userCheckAges(user, series))
        return MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE;
    if (setAdd(user->favorites, series) == SET_OUT_OF_MEMORY)
        return MTMFLIX_OUT_OF_MEMORY;
    return MTMFLIX_SUCCESS;
}
MtmFlixResult userRemoveFavorite(User user, Series series) {
    if (!user || !series)
        return MTMFLIX_NULL_ARGUMENT;
    setRemove(user->favorites, series);
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
    //printf("%s",output);
    //const char* output = mtmPrintUser(user->username, user->age, friends, favorites);
    //if(!output) printf("output: null\n");
    //else printf("output:\n%s\ndone\n",output);
    return output;
}
void userDestroy(User user){
    if(!user) return;
    setDestroy(user->favorites);
    setDestroy(user->friends);
    free(user);
}
void freeUser(ListElement user){
    userDestroy(user);
}
ListElement copyUserName(ListElement str){
    char* new_str = malloc(sizeof(char)*(strlen((char*)str)+1));
    strcpy(new_str, (char*)str);
    return (ListElement)new_str;
}
bool userLikeSeries(User user, Series series) {
    return setIsIn(user->favorites, series);
}
Set userGetFriends(User user) {
    return user->friends;
}
bool userCheckAges(User user, Series series) {
    if(!user || !series) return false;
    int* ages = seriesGetAges(series);
    if (!ages) return true;
    if (user->age < *ages || user->age > *(ages + 1))
        return false;
    return true;
}

int userCountFriendsLikes(User user, Series series) {
    int likeCounter = 0;
    User aFriend = setGetFirst(user->friends);
    while (aFriend) {
        if (setIsIn(aFriend->favorites, series))
            likeCounter++;
        aFriend = setGetNext(user->friends);
    }
    return likeCounter;
}
int userCountSameGenre(User user, Series series) {
    int sameGenreCounter = 0;
    const char* genre = seriesGetGenre(series);
    Series aFavorite = setGetFirst(user->favorites);
    while (aFavorite) {
        if (seriesGetGenre(aFavorite) == genre)
            sameGenreCounter++;
        aFavorite = setGetNext(user->favorites);
    }
    return sameGenreCounter;
}
float userCalcAvgLen(User user, Series series) {
    int lenSum = 0;
    Series aFavorite = setGetFirst(user->favorites);
    while (aFavorite) {
        lenSum += seriesGetEpisodeDuration(aFavorite);
        aFavorite = setGetNext(user->favorites);
    }
    int numOfSeries = setGetSize(user->favorites);
    return lenSum/numOfSeries;
}