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
#include "series.h"
#include "mtm_ex3.h"
#define str(x) #x
#define xstr(x) str(x)
#define MAX_STR_LEN 16
#define GENRES_NUM 8

struct mtmFlix_t {
    Map userList;
    Map seriesList;
};
struct recommended {
    Series series;
    int points;
};
typedef struct recommended* Recommended;

ListElement copyRecommended(ListElement src);
void freeRecommended(ListElement src);
int sortRecommended(ListElement recommended1, ListElement recommended2);
static bool checkName(const char* username);
static Map getAllGenreSeries(Map seriesList, const char* genre, int seriesNum);
//static char** getAllGenres(Map seriesList);
//static int stringCompare (const void * a, const void * b );
//static char** sortMapKeys(Map map);
//static void printList(Map list);
//static void printArr(const char** arr, int n);
//static char** makeMap2String(Map map);

static int calculatePoints(MtmFlix mtmflix,
                           char* username, Series series);

MtmFlix mtmFlixCreate() {
    MtmFlix mtmflix = malloc(sizeof(*mtmflix)); //ha'omnam "*" ?
    if (!mtmflix)
        return NULL;
    mtmflix->userList = mapCreate(copyUser, userCopyName, deleteUser,
                        userDeleteName, userCompareNames);
    mtmflix->seriesList = mapCreate(copySeries, seriesCopyName, deleteSeries,
                                    seriesDeleteName, seriesCompareNames);
    return mtmflix;
}
void mtmFlixDestroy(MtmFlix mtmflix) {
    if (mtmflix) {
        if (mtmflix->userList)
            free(mtmflix->userList);
        if(mtmflix->seriesList)
            free(mtmflix->seriesList);
        free(mtmflix);
    }
}
MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age) {
    if(!mtmflix || !username)
        return MTMFLIX_NULL_ARGUMENT;
    if(!checkName(username))
        return MTMFLIX_ILLEGAL_USERNAME;
    if(mapContains(mtmflix->userList, (char*)username))
        return MTMFLIX_USERNAME_ALREADY_USED;
    if (age > MTM_MAX_AGE || age < MTM_MIN_AGE)
        return MTMFLIX_ILLEGAL_AGE;
    User user = createUser((char*)username, age);
    if (!user)
        return MTMFLIX_OUT_OF_MEMORY;
    mapPut(mtmflix->userList, (char*)username, user);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixRemoveUser(MtmFlix mtmflix, const char* username) {
    if (!mtmflix || !username)
        return MTMFLIX_NULL_ARGUMENT;
    if (!checkName(username))
        return MTMFLIX_USER_DOES_NOT_EXIST;
    if (!mtmflix->userList)
        return MTMFLIX_NO_USERS;
    Map userMapAux = mapCopy(mtmflix->userList);
    MAP_FOREACH(char*, friend, userMapAux){ //toRemove?
        mtmFlixRemoveFriend(mtmflix, friend, username);
    }
    mapDestroy(userMapAux); //instead of free
    MapResult result = mapRemove(mtmflix->userList, (char*)username);
    if(result == MAP_ITEM_DOES_NOT_EXIST)
        return MTMFLIX_USER_DOES_NOT_EXIST;
    else if (result == MAP_NULL_ARGUMENT)
        return MTMFLIX_NULL_ARGUMENT;
    return MTMFLIX_SUCCESS;
}
static bool checkName(const char* username) {
    if (!username)
        return false;
    if (*username == '\0')
        return false;
    for (int i = 0; username[i] != '\0'; i++) {
        if (!((username[i] >= 'A' && username[i] <='Z')
               || (username[i] >= 'a' && username[i] <= 'z')
               || (username[i] >= '0' && username[i] <= '9')))
            return false;
    }
    return true;
}
MtmFlixResult mtmFlixAddSeries(MtmFlix mtmflix, const char* name, int episodesNum,
                               Genre genre, int* ages, int episodesDuration) {
    if(!mtmflix || !name)
        return MTMFLIX_NULL_ARGUMENT;
    if(!checkName(name))
        return MTMFLIX_ILLEGAL_SERIES_NAME;
    if(mapContains(mtmflix->seriesList, (char*)name))
        return MTMFLIX_SERIES_ALREADY_EXISTS;
    if(episodesNum <= 0)
        return MTMFLIX_ILLEGAL_EPISODES_NUM;
    if(episodesDuration <= 0)
        return MTMFLIX_ILLEGAL_EPISODES_DURATION;
    if (ages) {
        if (ages[0] < MTM_MIN_AGE)
            ages[0] = MTM_MIN_AGE;
        if (ages[1] > MTM_MAX_AGE)
            ages[1] = MTM_MAX_AGE;
    }
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
    Map seriesMapAux = mapCopy(mtmflix->seriesList);
    MAP_FOREACH(char*, user, seriesMapAux){
        mtmFlixSeriesLeave(mtmflix, user, name);
    }
    mapDestroy(seriesMapAux);
    MapResult result = mapRemove(mtmflix->seriesList, (char*)name);
    if(result == MAP_ITEM_DOES_NOT_EXIST)
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    else if (result == MAP_NULL_ARGUMENT)
        return MTMFLIX_NULL_ARGUMENT;
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixSeriesJoin(MtmFlix mtmflix, const char* username,
                                const char* seriesName) {
    if (!mtmflix || !username || !seriesName)
        return MTMFLIX_NULL_ARGUMENT;
    User ourUser = mapGet(mtmflix->userList, (char*)username);
    if (!ourUser)
        return MTMFLIX_USER_DOES_NOT_EXIST;
    Series ourSeries = mapGet(mtmflix->seriesList, (char*)seriesName);
    if (!ourSeries)
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    if (userAddFavorite(ourUser, ourSeries) == MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE)
        return MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE;
    mapPut(mtmflix->userList, (char*)username, ourUser); //needed? also might need to free
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixSeriesLeave(MtmFlix mtmflix, const char* username,
                                 const char* seriesName) {
    if (!mtmflix || !username || !seriesName)
        return MTMFLIX_NULL_ARGUMENT;
    if(!mapContains(mtmflix->userList, (char*)username))
        return MTMFLIX_USER_DOES_NOT_EXIST;
    User ourUser = mapGet(mtmflix->userList, (char*)username);
    if(!mapContains(mtmflix->seriesList, (char*)seriesName))
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    Series ourSeries = mapGet(mtmflix->seriesList, (char*)seriesName);
    userRemoveFavorite(ourUser, ourSeries);
    mapPut(mtmflix->userList, (char*)username, ourUser); //needed? also might need to free
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixAddFriend(MtmFlix mtmflix, const char* username1,
                               const char* username2) {
    if (!mtmflix || !username1 || !username2)
        return MTMFLIX_NULL_ARGUMENT;
    User ourUser = mapGet(mtmflix->userList, (char*)username1);
    User friend = mapGet(mtmflix->userList, (char*)username2);
    if (!ourUser || !friend)
        return MTMFLIX_USER_DOES_NOT_EXIST;
    userAddFriend(ourUser, friend);
    mapPut(mtmflix->userList, (char*)username1, ourUser);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixRemoveFriend(MtmFlix mtmflix, const char* username1,
                                  const char* username2) {
    if (!mtmflix || !username1 || !username2)
        return MTMFLIX_NULL_ARGUMENT;
    User ourUser = mapGet(mtmflix->userList, (char*)username1);
    User friend = mapGet(mtmflix->userList, (char*)username2);
    if (!ourUser || !friend)
        return MTMFLIX_USER_DOES_NOT_EXIST;
    userRemoveFriend(ourUser, friend);
    mapPut(mtmflix->userList, (char*)username1, ourUser);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixReportSeries(MtmFlix mtmflix, int seriesNum, FILE* outputStream){
    if(!mtmflix || !outputStream) return MTMFLIX_NULL_ARGUMENT;
    if(seriesNum < 0 || mapGetSize(mtmflix->seriesList)<=0)
        return MTMFLIX_NO_SERIES;

    const char* sorted_genres[] = { "COMEDY", "CRIME", "DOCUMENTARY", "DRAMA",
                                    "HORROR", "MYSTERY", "ROMANCE", "SCIENCE_FICTION"};
    //printf("\nmtmflix->seriesList:\n");
    //printList(mtmflix->seriesList);
    for(int i=0; i < GENRES_NUM; i++) {
        Map genre_list = getAllGenreSeries(mtmflix->seriesList, sorted_genres[i], seriesNum);
        //printf("\n%s:\n",sorted_genres[i]);
        //printList(genre_list);
        int list_size = mapGetSize(genre_list);
        if(mapGetSize(genre_list) <= 0) continue; //?
        //printList(genre_list);
        //Here probably one of the conditions is redundant:
        for(int j=0; (j < seriesNum || seriesNum == 0) && j < list_size; j++){
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
    if(user_num <= 0) return MTMFLIX_NO_USERS;
    for(int j=0; j < user_num; j++) {
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
/*static char** getAllGenres(Map seriesList){
    char* ptr = mapGetFirst(seriesList);
    if(!ptr) return NULL;
    char** genres = malloc(sizeof(char)*(MAX_STR_LEN));
    if(!genres) return NULL;
    strcpy(genres[0], seriesGetGenre(mapGet(seriesList, ptr)));
    int genres_num = 0;
    while(ptr) {
        const char* genre = seriesGetGenre(mapGet(seriesList, ptr));
        int i = 0;
        for (; i < genres_num; i++) {
            if (strcmp(genre, genres[i]) == 0)
            {
                break;
            }
        }
        if(i == genres_num){
            genres = (char**)realloc(genres, sizeof(char)*genres_num*
                                             (MAX_STR_LEN));
            if(!genres){
                free(genres);
                return NULL;
            }
            strcpy(genres[0], genre);
        }
        ptr = mapGetNext(seriesList);
    }
    qsort(genres, (size_t)genres_num, sizeof(char*),stringCompare);
    genres = (char**)realloc(genres, sizeof(char)*(genres_num+1)*
                                     (MAX_STR_LEN));
    if(!genres) {
        free(genres);
        return NULL;
    }
    genres[genres_num] = NULL;
    return genres;
}*/
/*static int stringCompare (const void * a, const void * b ) {
    const char *pa = (const char*)a;
    const char *pb = (const char*)b;
    return strcmp(pa,pb);
}*/
/*static char** sortMapKeys(Map map){
    char* ptr = mapGetFirst(map);
    if(!ptr) return NULL;
    char** names = malloc(sizeof(char*));
    names[0] = malloc(sizeof(char)*(strlen(ptr)+1));
    if(!names[0]) return NULL;
    strcpy(names[0], ptr);
    int names_num = 0;
    while(ptr) {
        names = realloc(names, sizeof(char*)*(names_num+1));
        names[names_num] = malloc(sizeof(char*)*(strlen(ptr)+1));
        if(!names[names_num]) return NULL;
        strcpy(names[names_num], ptr);
        names_num++;
        ptr = mapGetNext(map);
    }
    qsort(names, (size_t)names_num, sizeof(char*),stringCompare);
    names = (char**)realloc(names, sizeof(char)*(names_num+1)*
                                   (MAX_STR_LEN));
    if(!names) {
        free(names);
        return NULL;
    }
    names[names_num] = NULL;
    return names;
}*/
MtmFlixResult mtmFlixGetRecommendations(MtmFlix mtmflix, char* username,
                                        int count, FILE* outputStream) {
    if (!mtmflix || !username || !outputStream) return MTMFLIX_NULL_ARGUMENT;
    if (count < 0) return MTMFLIX_ILLEGAL_NUMBER;
    if (!mapContains(mtmflix->userList, username)) return MTMFLIX_USER_DOES_NOT_EXIST;
    List recommendedList = listCreate(copyRecommended, freeRecommended);
    int numOfSeries = count;
    int size = mapGetSize(mtmflix->seriesList);
    if (count == 0 || count > size) {
        numOfSeries = size;
    }
    Series series = mapGet(mtmflix->seriesList, mapGetFirst(mtmflix->seriesList));
    for (int i=0; i < numOfSeries; i++) {
        Recommended recommended = malloc(sizeof(Recommended));

        recommended->series = series;
        recommended->points = calculatePoints(mtmflix, username, series);
        if (!recommended->points)
            listInsertLast(recommendedList, recommended);
        series = mapGet(mtmflix->seriesList, mapGetNext(mtmflix->seriesList));
    }
    listSort(recommendedList, sortRecommended);
    Recommended recommended = listGetFirst(recommendedList);
    series = recommended->series;
    while (series) {
        fprintf(outputStream, printSeries(series)); //...
        series = listGetNext(recommendedList);
    }
    return MTMFLIX_SUCCESS;
}

static int calculatePoints(MtmFlix mtmflix,
                           char* username, Series series) {
    User user = mapGet(mtmflix->userList, username);
    if (userLikeSeries(user, series) || !userCheckAges(user, series))
        return 0;
    int friendLikes = userCountFriendsLikes(user, series);
    int sameGenre = userCountSameGenre(user, series);
    float avgLen = userCalcAvgLen(user, series);

    //CALCULATION probably NOT GOOD! Because of float/int thing
    float rank = (sameGenre * friendLikes) /
                 (1 + abs((int)(seriesGetEpisodeDuration(series) - avgLen)));
    return (int)rank;
}

ListElement copyRecommended(ListElement src) {
    Recommended dst = malloc(sizeof(Recommended));
    Recommended res = (Recommended)src;
    dst->series = copySeries(res->series);
    dst->points = res->points;
    return dst;
}

void freeRecommended(ListElement src) {
    Recommended res = (Recommended)src;
    free(res->series);
    free(res);
}

int sortRecommended(ListElement recommended1, ListElement recommended2) {
    int points1 = ((Recommended)recommended1)->points;
    int points2 = ((Recommended)recommended2)->points;
    if (points1 != points2)
        return points1 - points2; //might need to switch that
    Series series1 = ((Recommended)recommended1)->series;
    Series series2 = ((Recommended)recommended2)->series;
    return seriesSetCompareNames(series1, series2);

}
