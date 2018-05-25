#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "map.h"
#include "set.h"
#include "list.h"
#include "mtmflix.h"
#include "series.h"
#include "user.h"
#include "mtm_ex3.h"
#define str(x) #x
#define xstr(x) str(x)
#define MAX_STR_LEN 16
#define GENRES_NUM 8

struct mtmFlix_t {
    Map userList;
    Map seriesList;
};
static bool checkName(const char* username);
static Map getAllGenreSeries(Map seriesList, const char* genre, int seriesNum);
//static int stringCompare (const void * a, const void * b );
//static char** sortMapKeys(Map map);
//static void printList(Map list);
//static void printArr(const char** arr, int n);
//static char** makeMap2String(Map map);



MtmFlix mtmFlixCreate() {
    MtmFlix mtmflix = malloc(sizeof(*mtmflix));
    if (!mtmflix) return NULL;
    mtmflix->userList = mapCreate(copyUser, userCopyName, deleteUser,
                        userDeleteName, userCompareNames);
    mtmflix->seriesList = mapCreate(copySeries, seriesCopyName, deleteSeries,
                                    seriesDeleteName, seriesCompareNames);
    return mtmflix;
}
void mtmFlixDestroy(MtmFlix mtmflix) {
    if (mtmflix) {
        if (mtmflix->userList) free(mtmflix->userList);
        if(mtmflix->seriesList) free(mtmflix->seriesList);
        free(mtmflix);
    }
}
MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age) {
    if(!mtmflix || !username) return MTMFLIX_NULL_ARGUMENT;
    if(!checkName(username)) return MTMFLIX_ILLEGAL_USERNAME;
    if(mapContains(mtmflix->userList, (char*)username))
        return MTMFLIX_USERNAME_ALREADY_USED;
    if(age < MTM_MIN_AGE || age > MTM_MAX_AGE) return MTMFLIX_ILLEGAL_AGE;

    User user = createUser((char*)username, age);
    if(!user) return MTMFLIX_OUT_OF_MEMORY;
    mapPut(mtmflix->userList, (char*)username, user);

    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixRemoveUser(MtmFlix mtmflix, const char* username) {
    if (!mtmflix || !username) return MTMFLIX_NULL_ARGUMENT;
    if (!checkName(username)) return MTMFLIX_USER_DOES_NOT_EXIST;
    if (!mtmflix->userList) return MTMFLIX_NO_USERS;
    MapResult result = mapRemove(mtmflix->userList, (char*)username);
    if(result == MAP_ITEM_DOES_NOT_EXIST) return MTMFLIX_USER_DOES_NOT_EXIST;
    else if (result == MAP_NULL_ARGUMENT) return MTMFLIX_NULL_ARGUMENT;
    return MTMFLIX_SUCCESS;
}

MtmFlixResult mtmFlixAddSeries(MtmFlix mtmflix, const char* name,
             int episodesNum, Genre genre, int* ages, int episodesDuration) {
    if(!mtmflix || !name) return MTMFLIX_NULL_ARGUMENT;
    if(!checkName(name)) return MTMFLIX_ILLEGAL_SERIES_NAME;
    if(mapContains(mtmflix->seriesList, (char*)name))
        return MTMFLIX_SERIES_ALREADY_EXISTS;
    if(episodesNum <=0) return MTMFLIX_ILLEGAL_EPISODES_NUM;
    if(episodesDuration <=0) return MTMFLIX_ILLEGAL_EPISODES_DURATION;
    Series series = createSeries(name, episodesNum, genre, ages,
                                 episodesDuration);
    mapPut(mtmflix->seriesList, (char*)name, series);

    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixRemoveSeries(MtmFlix mtmflix, const char* name) {
    if(!mtmflix || !name) return MTMFLIX_NULL_ARGUMENT;
    if(!checkName(name)) return MTMFLIX_SERIES_DOES_NOT_EXIST;
    if(!mapContains(mtmflix->seriesList, (char*)name))
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    MapResult result = mapRemove(mtmflix->seriesList, (char*)name);
    if(result == MAP_ITEM_DOES_NOT_EXIST) return MTMFLIX_USER_DOES_NOT_EXIST;
    else if (result == MAP_NULL_ARGUMENT) return MTMFLIX_NULL_ARGUMENT;
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixSeriesJoin(MtmFlix mtmflix, const char* username,
                                 const char* seriesName){
    if (!mtmflix || !username || !seriesName) return MTMFLIX_NULL_ARGUMENT;

    User ourUser = mapGet(mtmflix->userList, (char*)username);

    if (!ourUser) return MTMFLIX_USER_DOES_NOT_EXIST;

    Series ourSeries = mapGet(mtmflix->seriesList, (char*)seriesName);
    if (!ourSeries){
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    }

    if (userAddFavorite(ourUser, ourSeries) ==
            MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE){

        return MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE;

    }
    mapPut(mtmflix->userList, (char*)username, ourUser);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixSeriesLeave(MtmFlix mtmflix, const char* username,
                                 const char* seriesName) {
    if (!mtmflix || !username || !seriesName) return MTMFLIX_NULL_ARGUMENT;
    if(!mapContains(mtmflix->userList, (char*)username))
        return MTMFLIX_USER_DOES_NOT_EXIST;
    User ourUser = mapGet(mtmflix->userList, (char*)username);

    if(!mapContains(mtmflix->seriesList, (char*)seriesName))
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    Series ourSeries = mapGet(mtmflix->seriesList, (char*)seriesName);

    //the lines that actually make the function:
    userRemoveFavorite(ourUser, ourSeries);

    mapPut(mtmflix->userList, (char*)username, ourUser);

    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixAddFriend(MtmFlix mtmflix, const char* username1,
                               const char* username2) {
    if (!mtmflix || !username1 || !username2)
        return MTMFLIX_NULL_ARGUMENT;
    User ourUser = mapGet(mtmflix->userList, (char*)username1);
    User friend = mapGet(mtmflix->userList, (char*)username2);
    if (!ourUser || !friend) return MTMFLIX_USER_DOES_NOT_EXIST;
    userAddFriend(ourUser, friend);
    mapPut(mtmflix->userList, (char*)username1, ourUser);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixRemoveFriend(MtmFlix mtmflix, const char* username1,
                               const char* username2) {
    if (!mtmflix || !username1 || !username2) return MTMFLIX_NULL_ARGUMENT;
    char* newUsername1 = malloc(strlen(username1));
    strcpy(newUsername1, username1);
    char* newUsername2 = malloc(strlen(username2));
    strcpy(newUsername2, username2);
    User ourUser = mapGet(mtmflix->userList, newUsername1);
    User friend = mapGet(mtmflix->userList, newUsername2);
    if (!ourUser || !friend) return MTMFLIX_USER_DOES_NOT_EXIST;
    userRemoveFriend(ourUser, friend);
    mapPut(mtmflix->userList, newUsername1, ourUser);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixReportSeries(MtmFlix mtmflix, int seriesNum, FILE* outputStream){
    if(!mtmflix || !outputStream) return MTMFLIX_NULL_ARGUMENT;
    if(seriesNum < 0 || mapGetSize(mtmflix->seriesList)<=0)
        return MTMFLIX_NO_SERIES;

    const char* sorted_genres[] = { "COMEDY", "CRIME", "DOCUMENTARY", "DRAMA",
                   "HORROR", "MYSTERY", "ROMANCE", "SCIENCE_FICTION"} ;
    Map series_list = mapCopy(mtmflix->seriesList);
    //printf("\nmtmflix->seriesList:\n");
    //printList(mtmflix->seriesList);
    for(int i=0; i<GENRES_NUM; i++){
        //printf("%s\n",sorted_genres[i]);
        Map genre_list = getAllGenreSeries(series_list, sorted_genres[i], seriesNum);

        //printf("\n%s:\n",sorted_genres[i]);
        //printList(genre_list);
        int list_size = mapGetSize(genre_list);
        if(mapGetSize(genre_list) <= 0) continue;
        //printList(genre_list);
        for(int j=0; (j<seriesNum || seriesNum ==0) && j< list_size; j++){
            char* ptr = mapGetFirst(genre_list);
            char* min_name = malloc(sizeof(char)*(strlen(ptr)+1));
            strcpy(min_name, ptr);
            while(ptr){
                if(strcmp(ptr, min_name) < 0){
                    min_name = realloc(min_name, sizeof(char)*(strlen(ptr)+1));
                    strcpy(min_name, ptr);
                }
                ptr = mapGetNext(genre_list);
            }
            mapRemove(genre_list, min_name);

            Series series = mapGet(mtmflix->seriesList, (MapKeyElement)min_name);
            const char* output = printSeries(series);
            fprintf(outputStream,output);

            free(min_name);
        }
        mapDestroy(genre_list);
    }
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixReportUsers(MtmFlix mtmflix, FILE* outputStream){
    if(!mtmflix || !outputStream) return MTMFLIX_NULL_ARGUMENT;

    Map user_name = mapCopy(mtmflix->userList);
    int user_num = mapGetSize(mtmflix->userList);

    if(user_num<=0) return MTMFLIX_NO_USERS;

    for(int j=0; j<user_num; j++){
        char* ptr = mapGetFirst(user_name);
        if(!ptr) return MTMFLIX_OUT_OF_MEMORY;
        char* min_name = malloc(sizeof(char)*(1+strlen(ptr)));
        strcpy(min_name, ptr);



        while(ptr) {
            if (strcmp(ptr, min_name) < 0) {
                min_name = realloc(min_name, sizeof(char)*(strlen(ptr)+1));
                strcpy(min_name,ptr);
            }
            ptr = mapGetNext(user_name);
        }

        mapRemove(user_name, min_name);

        User user = mapGet(mtmflix->userList, min_name);
        const char* output = printUser(user);

        //printf("output:\n%s\n",output);
        fprintf(outputStream,output);
        free(min_name);
    }
    return MTMFLIX_SUCCESS;
}

Map GetUserList(MtmFlix mtmflix){
    return mtmflix->userList;
}
Map GetSeriesList(MtmFlix mtmflix){
    return mtmflix->seriesList;
}


static Map getAllGenreSeries(Map seriesList, const char* genre, int seriesNum){
    Map new_list = mapCreate(copySeries, seriesCopyName, deleteSeries,
                                       seriesDeleteName, seriesCompareNames);
    char* ptr = mapGetFirst(seriesList);
    while(ptr){
        if(strcmp(genre, seriesGetGenre(mapGet(seriesList, ptr)))==0){
            mapPut(new_list, ptr, mapGet(seriesList, ptr));
        }
        ptr = mapGetNext(seriesList);
    }
   return new_list;
}
/*static int stringCompare (const void * a, const void * b ) {
    char *pa = (char*)a;
    char *pb = (char*)b;
    while(pa && pb){
        if((int)(*pa) > (int)(*pb)){
            return -1;
        }
        else if((int)(*pa) == (int)(*pb)){
            pa++;pb++;
        }
        else return 1;
    }
    if(pa) return -1;
    else if(pb) return 1;

    return strcmp(pa, pb);
}
static void sortStrings(char** a, int n){
    printArr((const char**)a, n);
    int length;
    for(length = n ; length > 1; length--)
    {
        printf("len=%d\n",length);
        int i, i_max = 0;
        for(i = 1; i < n; i++){
            printf("i=%d i_max=%d\n",i, i_max);
            int res = strcmp(a[i], a[i_max]);
            printf("%s %s %d\n",a[i],a[i_max],res);
            if(res > 0){
                i_max = i;
            }
        }

        printf("word=%s\n",a[i]);
        int len = (int)strlen(a[i]);
        printf("len=%d\n",len);
        char* temp = malloc(sizeof(char)*(strlen(a[i])+1));

        memcpy(temp, a[i], strlen(a[i])+1);
        a[i] = realloc(a[i], sizeof(char)*strlen(a[i_max])+1);
        memcpy(a[i], a[i_max], strlen(a[i_max])+1);
        a[i_max] = realloc(a[i_max], sizeof(char)*strlen(a[i])+1);
        memcpy(a[i_max], temp, strlen(temp)+1);
        free(temp);
    }
}
static char** sortMapKeys(Map map){
    char* ptr = mapGetFirst(map);
    char* min_name = ptr;
    int keys_num = mapGetSize(map);
    for(int i=0; i<keys_num; i++){
        while(ptr){
            if(strcmp(ptr, min_name) < 0){
                min_name = ptr;
            }
            ptr = mapGetNext(map);
        }

    }


    return names;
}
static char** makeMap2String(Map map){
    char* ptr = mapGetFirst(map);
    if(!ptr) return NULL;

    int keys_num = mapGetSize(map);
    char** names = malloc(sizeof(char*)*(keys_num+1));
    if(!names) return NULL;

    for(int i = 0; i< keys_num; i++){
        char* string = malloc(sizeof(char)*(strlen(ptr)+1));
        if(!string){
            free(string);
            free(names);
            return NULL;
        }
        strcpy(string, ptr);
        names[i] = string;
        ptr = mapGetNext(map);
    }
    return names;
}*/
static bool checkName(const char* username) {
    if (!username) return false;
    if(strcmp(username,"")==0) return false;
    for (int i = 0; username[i] != '\0'; i++) {
        if (!((username[i] >= 'A' && username[i] <='Z')
              || (username[i] >= 'a' && username[i] <= 'z')
              || (username[i] >= '0' && username[i] <= '9')))
            return false;
    }
    return true;
}
/*
void printU(MtmFlix mtmflix){
    Map usersList = GetUserList(mtmflix);
    char* ptr = mapGetFirst(usersList);
    while(ptr){
        User user = mapGet(usersList, ptr);
        printf("%s\n",printUser(user));
        ptr = mapGetNext(usersList);
    }
    printf("\n");
}
void printS(MtmFlix mtmflix) {
    Map seriesList = GetSeriesList(mtmflix);
    char* ptr = mapGetFirst(seriesList);
    while(ptr){
        Series series = mapGet(seriesList, ptr);
        printf("%s\n",printSeries(series));
        ptr = mapGetNext(seriesList);
    }
    printf("\n");
}*/
/*static void printList(Map list){
    if(!list) return;
    char* ptr = mapGetFirst(list);
    while(ptr){
        printf("%s\n",ptr);
        ptr = mapGetNext(list);
    }
}
static void printArr(const char** arr, int n){
    if(!arr) return;
    if(n>=0) for(int i=0;i<n;i++)printf("%s\n",arr[i]);
    else{
        int i =0;
        while(arr[i]){
            printf("%s\n",arr[i]);
            i++;
        }
    }
    printf("\n");
}*/