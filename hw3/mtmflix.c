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
static char** getAllGenreSeries(Map seriesList, char* genre);
static char** getAllGenres(Map seriesList);
static int stringCompare (const void * a, const void * b );
static char** sortMapKeys(Map map);
static int calculatePoints(MtmFlix mtmflix,
                           char* username, Series series);

MtmFlix mtmFlixCreate() {
    MtmFlix mtmflix = malloc(sizeof(mtmflix));
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
        //free(mtmflix);
    }
}
MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age) {

    char* newUsername = malloc(strlen(username));
    strcpy(newUsername, username);
    User user = createUser(newUsername, age);
    mapPut(mtmflix->userList, newUsername, user);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixRemoveUser(MtmFlix mtmflix, const char* username) {
    if (!mtmflix || !username)
        return MTMFLIX_NULL_ARGUMENT;
    if (!mtmflix->userList)
        return MTMFLIX_NO_USERS;
    char* searchName = malloc(strlen(username));
    if (!searchName)
        return MTMFLIX_OUT_OF_MEMORY;
    strcpy(searchName, username);
    if (!checkName(searchName))
        return MTMFLIX_ILLEGAL_USERNAME;
    if(!(mapRemove(mtmflix->userList, searchName) == MAP_SUCCESS))
        return MTMFLIX_USER_DOES_NOT_EXIST; //bad, should depend more precisely on MAP_STATUS
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
    Series series = createSeries(name, episodesNum, genre, ages, episodesDuration);
    char* newName = malloc(strlen(name));
    strcpy(newName, name);
    mapPut(mtmflix->seriesList, newName, series);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixRemoveSeries(MtmFlix mtmflix, const char* name) {
    char* removedName = malloc(strlen(name));
    strcpy(removedName, name);
    mapRemove(mtmflix->seriesList, removedName);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixSeriesJoin(MtmFlix mtmflix, const char* username,
                                const char* seriesName) {
    if (!mtmflix || !username || !seriesName)
        return MTMFLIX_NULL_ARGUMENT;
    //making a non-const username and making sure it exists:
    char* searchUsername = malloc(strlen(username));
    strcpy(searchUsername, username);
    User ourUser = mapGet(mtmflix->userList, searchUsername);
    if (!searchUsername)
        return MTMFLIX_USER_DOES_NOT_EXIST;
    //making a non-const seriesName and making sure it exists:
    char* searchSeriesName = malloc(strlen(seriesName));
    strcpy(searchSeriesName, seriesName);
    Series ourSeries = mapGet(mtmflix->seriesList, searchSeriesName);
    if (!searchSeriesName)
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    //the lines that actually make the function:
    if (userAddFavorite(ourUser, ourSeries) == MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE)
        return MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE;
    //mapPut(mtmflix->userList, searchUsername, ourUser);
    //STILL NEED TO FREE SHIT! (USER, SERIES, NAMES)
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixSeriesLeave(MtmFlix mtmflix, const char* username,
                                 const char* seriesName) {
    if (!mtmflix || !username || !seriesName)
        return MTMFLIX_NULL_ARGUMENT;
    //making a non-const username and making sure it exists:
    char* searchUsername = malloc(strlen(username));
    strcpy(searchUsername, username);
    User ourUser = mapGet(mtmflix->userList, searchUsername);
    if (!ourUser)
        return MTMFLIX_USER_DOES_NOT_EXIST;
    //making a non-const seriesName and making sure it exists:
    char* searchSeriesName = malloc(strlen(seriesName));
    strcpy(searchSeriesName, seriesName);
    Series ourSeries = mapGet(mtmflix->seriesList, searchSeriesName);
    if (!ourSeries)
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    //the lines that actually make the function:
    userRemoveFavorite(ourUser, ourSeries);
    //mapPut(mtmflix->userList, searchUsername, ourUser); //apparently not needed
    //STILL NEED TO FREE SHIT! (USER, SERIES, NAMES)
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixAddFriend(MtmFlix mtmflix, const char* username1,
                               const char* username2) {
    if (!mtmflix || !username1 || username2)
        return MTMFLIX_NULL_ARGUMENT;
    char* newUsername1 = malloc(strlen(username1));
    strcpy(newUsername1, username1);
    char* newUsername2 = malloc(strlen(username2));
    strcpy(newUsername2, username2);
    User ourUser = mapGet(mtmflix->userList, newUsername1);
    User friend = mapGet(mtmflix->userList, newUsername2);
    if (!ourUser || !friend)
        return MTMFLIX_USER_DOES_NOT_EXIST;
    userAddFriend(ourUser, friend);
    mapPut(mtmflix->userList, newUsername1, ourUser);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixRemoveFriend(MtmFlix mtmflix, const char* username1,
                               const char* username2) {
    if (!mtmflix || !username1 || username2)
        return MTMFLIX_NULL_ARGUMENT;
    char* newUsername1 = malloc(strlen(username1));
    strcpy(newUsername1, username1);
    char* newUsername2 = malloc(strlen(username2));
    strcpy(newUsername2, username2);
    User ourUser = mapGet(mtmflix->userList, newUsername1);
    User friend = mapGet(mtmflix->userList, newUsername2);
    if (!ourUser || !friend)
        return MTMFLIX_USER_DOES_NOT_EXIST;
    userRemoveFriend(ourUser, friend);
    mapPut(mtmflix->userList, newUsername1, ourUser);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixReportSeries(MtmFlix mtmflix, int seriesNum, FILE* outputStream){
    if(!mtmflix || !outputStream) return MTMFLIX_NULL_ARGUMENT;
    if(seriesNum < 0) return MTMFLIX_ILLEGAL_NUMBER;
    char** genres = getAllGenres(mtmflix->seriesList);
    if(!genres) return MTMFLIX_NO_SERIES;
    int i = 0;
    while(genres[i]){
        char** genre_list = getAllGenreSeries(mtmflix->seriesList, genres[i]);
        int j = 0;
        while(genre_list[j]){
            if(!fputs(printSeries(genre_list[j], mapGet(mtmflix->seriesList,
                                                        genre_list[j])), outputStream)) {
                return MTMFLIX_NULL_ARGUMENT;
            }
            j++;
        }
    }
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixReportUsers(MtmFlix mtmflix, FILE* outputStream){
    if(!mtmflix || !outputStream) return MTMFLIX_NULL_ARGUMENT;

    char** user_name = sortMapKeys(mtmflix->userList);
    if(!user_name) return MTMFLIX_NO_USERS;
    int i = 0;
    while(user_name[i]){
        User user = mapGet(mtmflix->userList, user_name[i]);
        if(!fputs(printUser(user_name[i], user), outputStream)) {
            return MTMFLIX_NULL_ARGUMENT;
        }
        i++;
    }
    return MTMFLIX_SUCCESS;
}
static char** getAllGenreSeries(Map seriesList, char* genre){
    Map new_list = mapCreate(copySeries, seriesCopyName, deleteSeries,
                             seriesDeleteName, seriesCompareNames);
    Map ptr = mapGetFirst(seriesList);
    while(ptr){
        if(strcmp(genre, seriesGetGenre(mapGet(seriesList, ptr)))==0){
            mapPut(new_list, ptr, mapGet(seriesList, ptr));
        }
        ptr = mapGetNext(seriesList);
    }
    char** sorted_list = sortMapKeys(new_list);
    return sorted_list;
}
static char** getAllGenres(Map seriesList){
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
}
static int stringCompare (const void * a, const void * b ) {
    const char *pa = (const char*)a;
    const char *pb = (const char*)b;
    return strcmp(pa,pb);
}
static char** sortMapKeys(Map map){
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
}
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
    Series series = mapGetFirst(mtmflix->seriesList);
    for (int i=0; i < numOfSeries; i++) {
        Recommended recommended = malloc(sizeof(Recommended));

        recommended->series = series;
        recommended->points = calculatePoints(mtmflix, username, series);
        if (!recommended->points)
            listInsertLast(recommendedList, recommended);
        series = mapGetNext(mtmflix->seriesList);
    }
    listSort(recommendedList, sortRecommended);
    series = listGetFirst(recommendedList);
    while (series) {
        printSeries(seriesGetName(series), series); //...
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
    return seriesCompareNamesForSet(series1, series2);

}
