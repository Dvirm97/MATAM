#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
<<<<<<< HEAD
#include <math.h>

#include "map.h"
#include "set.h"
#include "list.h"

#include "mtmflix.h"
#include "series.h"
#include "user.h"

=======
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
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
#define GENRES_NUM 8

struct mtmFlix_t {
    Map userList;
    Map seriesList;
};
<<<<<<< HEAD

static float absFloat(float num);
static void updateUser(Map user_list, User updated_user);
static int sortRecommendedList(ListElement series1, ListElement series2);
static bool checkName(const char* username);
static Map getAllGenreSeries(Map series_list, const char* genre);
static int calculatePoints(MtmFlix mtmflix, const char* username,
                           Series series);

MtmFlix mtmFlixCreate() {
    MtmFlix mtmflix = malloc(sizeof(*mtmflix));
    if (!mtmflix) return NULL;
    mtmflix->userList = mapCreate(userCopy, userCopyName, userDestroy,
                        userDestroyName, userCompareNames);
    mtmflix->seriesList = mapCreate(seriesCopy, seriesCopyName, seriesDestroy,
                                    seriesDestroyName, seriesCompareNames);
    return mtmflix;
}
void mtmFlixDestroy(MtmFlix mtmflix) {
    if(!mtmflix) return;
    if(mtmflix->userList) mapDestroy(mtmflix->userList);
    if(mtmflix->seriesList) mapDestroy(mtmflix->seriesList);
    free(mtmflix);
}
MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age) {
    if(!mtmflix || !username) return MTMFLIX_NULL_ARGUMENT;
    if(!checkName(username)) return MTMFLIX_ILLEGAL_USERNAME;
    if(mapContains(mtmflix->userList, (char*)username))
        return MTMFLIX_USERNAME_ALREADY_USED;
    if (age > MTM_MAX_AGE || age < MTM_MIN_AGE) return MTMFLIX_ILLEGAL_AGE;
    User user = userCreate((char*)username, age);
    if (!user) return MTMFLIX_OUT_OF_MEMORY;
    mapPut(mtmflix->userList, (char*)username, user);
    userDestroy(user);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixRemoveUser(MtmFlix mtmflix, const char* username) {
    if (!mtmflix || !username) return MTMFLIX_NULL_ARGUMENT;
    if (!checkName(username)) return MTMFLIX_USER_DOES_NOT_EXIST;
    if (!mtmflix->userList) return MTMFLIX_NO_USERS;
    Map user_list = mapCopy(mtmflix->userList);
    MAP_FOREACH(char*, friend, user_list){
        mtmFlixRemoveFriend(mtmflix, friend, username);
    }
    mapDestroy(user_list);
    MapResult result = mapRemove(mtmflix->userList, (char*)username);
    if(result == MAP_ITEM_DOES_NOT_EXIST) return MTMFLIX_USER_DOES_NOT_EXIST;
    else if (result == MAP_NULL_ARGUMENT) return MTMFLIX_NULL_ARGUMENT;
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixAddSeries(MtmFlix mtmflix, const char* name, int episodesNum,
                               Genre genre, int* ages, int episodesDuration) {
    if(!mtmflix || !name) return MTMFLIX_NULL_ARGUMENT;
    if(!checkName(name)) return MTMFLIX_ILLEGAL_SERIES_NAME;
    if(mapContains(mtmflix->seriesList, (char*)name))
        return MTMFLIX_SERIES_ALREADY_EXISTS;
    if(episodesNum <= 0) return MTMFLIX_ILLEGAL_EPISODES_NUM;
    if(episodesDuration <= 0) return MTMFLIX_ILLEGAL_EPISODES_DURATION;
    if (ages && ages[0] < MTM_MIN_AGE) {
        ages[0] = MTM_MIN_AGE;
    }
    if (ages && ages[1] > MTM_MAX_AGE){
        ages[1] = MTM_MAX_AGE;
    }
    Series series = seriesCreate(name, episodesNum, genre, ages,
                                 episodesDuration);
    mapPut(mtmflix->seriesList, (char*)name, series);
    seriesDestroy((void*)series);
=======
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
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixRemoveSeries(MtmFlix mtmflix, const char* name) {
    if(!mtmflix || !name) return MTMFLIX_NULL_ARGUMENT;
    if(!checkName(name)) return MTMFLIX_SERIES_DOES_NOT_EXIST;
<<<<<<< HEAD
    if (!mtmflix->seriesList) return MTMFLIX_NO_SERIES;
    if(!mapContains(mtmflix->seriesList, (char*)name))
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    Map series_list = mapCopy(mtmflix->userList);
    MAP_FOREACH(char*, user, series_list){
        mtmFlixSeriesLeave(mtmflix, user, name);
    }
    mapDestroy(series_list);
    MapResult result = mapRemove(mtmflix->seriesList, (char*)name);
    if(result == MAP_ITEM_DOES_NOT_EXIST) return MTMFLIX_SERIES_DOES_NOT_EXIST;
    else if (result == MAP_NULL_ARGUMENT) return MTMFLIX_NULL_ARGUMENT;
=======
    if (!mtmflix->seriesList)
        return MTMFLIX_NO_SERIES;
    if(!mapContains(mtmflix->seriesList, (char*)name))
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    Map seriesMapAux = mapCopy(mtmflix->userList);
    MAP_FOREACH(char*, user, seriesMapAux){
        mtmFlixSeriesLeave(mtmflix, user, name);
    }
    mapDestroy(seriesMapAux);
    MapResult result = mapRemove(mtmflix->seriesList, (char*)name);
    if(result == MAP_ITEM_DOES_NOT_EXIST)
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    else if (result == MAP_NULL_ARGUMENT)
        return MTMFLIX_NULL_ARGUMENT;
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixSeriesJoin(MtmFlix mtmflix, const char* username,
                                const char* seriesName) {
<<<<<<< HEAD
    if (!mtmflix || !username || !seriesName) return MTMFLIX_NULL_ARGUMENT;
    User user = mapGet(mtmflix->userList, (char*)username);
    if (!user) return MTMFLIX_USER_DOES_NOT_EXIST;
    Series series = mapGet(mtmflix->seriesList, (char*)seriesName);
    if (!series) return MTMFLIX_SERIES_DOES_NOT_EXIST;
    if (userAddFavorite(user, series) == MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE)
        return MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE;
    updateUser(mtmflix->userList, user);
    mapPut(mtmflix->userList, (char*)username, user);
=======
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
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixSeriesLeave(MtmFlix mtmflix, const char* username,
                                 const char* seriesName) {
<<<<<<< HEAD
    if (!mtmflix || !username || !seriesName) return MTMFLIX_NULL_ARGUMENT;
    if(!mapContains(mtmflix->userList, (char*)username))
        return MTMFLIX_USER_DOES_NOT_EXIST;
    User user = mapGet(mtmflix->userList, (char*)username);
    if(!mapContains(mtmflix->seriesList, (char*)seriesName))
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    Series series = mapGet(mtmflix->seriesList, (char*)seriesName);
    userRemoveFavorite(user, series);
    updateUser(mtmflix->userList, user);
    mapPut(mtmflix->userList, (char*)username, user);
=======
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
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixAddFriend(MtmFlix mtmflix, const char* username1,
                               const char* username2) {
<<<<<<< HEAD
    if (!mtmflix || !username1 || !username2) return MTMFLIX_NULL_ARGUMENT;
    User user = mapGet(mtmflix->userList, (char*)username1);
    User friend = mapGet(mtmflix->userList, (char*)username2);
    if (!user || !friend) return MTMFLIX_USER_DOES_NOT_EXIST;
    userAddFriend(user, friend);
    updateUser(mtmflix->userList, user);
    mapPut(mtmflix->userList, (char*)username1, user);
=======
    if (!mtmflix || !username1 || !username2)
        return MTMFLIX_NULL_ARGUMENT;
    User ourUser = mapGet(mtmflix->userList, (char*)username1);
    User friend = mapGet(mtmflix->userList, (char*)username2);
    if (!ourUser || !friend)
        return MTMFLIX_USER_DOES_NOT_EXIST;
    userAddFriend(ourUser, friend);
    mapPut(mtmflix->userList, (char*)username1, ourUser);
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixRemoveFriend(MtmFlix mtmflix, const char* username1,
                                  const char* username2) {
<<<<<<< HEAD
    if (!mtmflix || !username1 || !username2) return MTMFLIX_NULL_ARGUMENT;
    User user = mapGet(mtmflix->userList, (char*)username1);
    User friend = mapGet(mtmflix->userList, (char*)username2);
    if (!user || !friend)
        return MTMFLIX_USER_DOES_NOT_EXIST;
    userRemoveFriend(user, friend);
    updateUser(mtmflix->userList, user);
    mapPut(mtmflix->userList, (char*)username1, user);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixReportSeries(MtmFlix mtmflix, int seriesNum,
                                  FILE* outputStream){
    if(!mtmflix || !outputStream) return MTMFLIX_NULL_ARGUMENT;
    if(seriesNum < 0 || mapGetSize(mtmflix->seriesList) <= 0)
=======
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
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
        return MTMFLIX_NO_SERIES;

    const char* sorted_genres[] = { "COMEDY", "CRIME", "DOCUMENTARY", "DRAMA",
                                    "HORROR", "MYSTERY", "ROMANCE", "SCIENCE_FICTION"};
<<<<<<< HEAD

    // Make a list of series for each genre
    for(int i=0; i < GENRES_NUM; i++) {
        Map genre_list = getAllGenreSeries(mtmflix->seriesList, sorted_genres[i]);

        // If no series of current genre check next genre
        int list_size = mapGetSize(genre_list);
        if(list_size <= 0){
            mapDestroy(genre_list);
            continue;
        }

        // Sort list of series in current genre
        for(int j=0; (j < seriesNum || seriesNum == 0) && j < list_size; j++){
            char* tmp = mapGetFirst(genre_list);
            char* min_name = malloc(strlen(tmp)+1);
            if(!min_name) {
                mapDestroy(genre_list);
                return MTMFLIX_OUT_OF_MEMORY;
            }
            strcpy(min_name, tmp);
            MAP_FOREACH(char*, ptr, genre_list){
=======
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
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
                if(strcmp(ptr, min_name) < 0){
                    min_name = realloc(min_name, sizeof(char)*(strlen(ptr)+1));
                    strcpy(min_name, ptr);
                }
<<<<<<< HEAD
            }
            mapRemove(genre_list, min_name);

            // Print series in genre
            Series series = mapGet(mtmflix->seriesList,
                                   (MapKeyElement)min_name);
            const char* output = seriesPrint(series);
            fprintf(outputStream,output);
=======
                ptr = mapGetNext(genre_list);
            }
            mapRemove(genre_list, min_name);

            Series series = mapGet(mtmflix->seriesList, (MapKeyElement)min_name);
            const char* output = printSeries(series);
            fprintf(outputStream,output);

>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
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
<<<<<<< HEAD

    for(int j=0; j < user_num; j++) {
        // Get the next name to print
        char* tmp = mapGetFirst(user_name);
        char* min_name = malloc(strlen(tmp)+1);
        if(!min_name) {
            mapDestroy(user_name);
            return MTMFLIX_OUT_OF_MEMORY;
        }
        strcpy(min_name, tmp);
        MAP_FOREACH(char*, ptr, user_name){
=======
    for(int j=0; j < user_num; j++) {
        char* ptr = mapGetFirst(user_name);
        if(!ptr) return MTMFLIX_OUT_OF_MEMORY;
        char* min_name = malloc(sizeof(char)*(1+strlen(ptr)));
        strcpy(min_name, ptr);
        while(ptr) {
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
            if (strcmp(ptr, min_name) < 0) {
                min_name = realloc(min_name, sizeof(char)*(strlen(ptr)+1));
                strcpy(min_name,ptr);
            }
<<<<<<< HEAD
        }
        mapRemove(user_name, min_name);

        // Print name
        User user = mapGet(mtmflix->userList, min_name);
        const char* output = userPrint(user);
=======
            ptr = mapGetNext(user_name);
        }

        mapRemove(user_name, min_name);

        User user = mapGet(mtmflix->userList, min_name);
        const char* output = printUser(user);

        //printf("output:\n%s\n",output);
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
        fprintf(outputStream,output);
        free(min_name);
    }
    return MTMFLIX_SUCCESS;
}
<<<<<<< HEAD
MtmFlixResult mtmFlixGetRecommendations(MtmFlix mtmflix, const char* username,
                                        int count, FILE* outputStream){
    // Check input
    if (!mtmflix || !username || !outputStream) return MTMFLIX_NULL_ARGUMENT;
    if (!mapContains(mtmflix->userList, (MapKeyElement)username))
        return MTMFLIX_USER_DOES_NOT_EXIST;
    if (count < 0) return MTMFLIX_ILLEGAL_NUMBER;

    // Get points for each series
    List recommended_list = listCreate(seriesCopy, seriesDestroy);
    MAP_FOREACH(char*, ptr, mtmflix->seriesList){
        Series series = mapGet(mtmflix->seriesList, ptr);
        int points = calculatePoints(mtmflix, username, series);
        if (points != 0){
            seriesSetPoints(series, points);
            listInsertFirst(recommended_list, series);
        }

    }

    // Print sorted list of recommendations
    listSort(recommended_list, sortRecommendedList);
    int size = mapGetSize(mtmflix->seriesList);
    Series series = listGetFirst(recommended_list);
    int numOfSeries = (count == 0 || count > size) ? size : count;
    for(int i =0; i < numOfSeries; i++){
        fprintf(outputStream, seriesPrint(series));
        series = listGetNext(recommended_list);
    }

    listDestroy(recommended_list);
    return MTMFLIX_SUCCESS;
}

static bool checkName(const char* username) {
    if (!username || *username == '\0') return false;
    for (int i = 0; username[i] != '\0'; i++) {
        if (!((username[i] >= 'A' && username[i] <='Z')
              || (username[i] >= 'a' && username[i] <= 'z')
              || (username[i] >= '0' && username[i] <= '9')))
            return false;
    }
    return true;
}
static int calculatePoints(MtmFlix mtmflix, const char* username, Series series)
{
    User user = mapGet(mtmflix->userList, (MapKeyElement)username);
    if (userIsFavorite(user, series) || !userCheckAges(user, series)) return 0;
    int friends_likes = userCountFriendsLikes(user, series);
    int same_genre = userCountSameGenre(user, series);
    float avg_len = userGetFavoritesAvgLen(user);

    double rank = (same_genre * friends_likes) /
                 (1 + absFloat(seriesGetEpisodeDuration(series) - avg_len));
    return (int)floor(rank);
}
static int sortRecommendedList(ListElement series1, ListElement series2) {
    int points1 = seriesGetPoints((Series)series1);
    int points2 =  seriesGetPoints((Series)series2);
    if (points1 != points2) return points2 - points1;
    return seriesCompareNamesForSet(series1, series2);
}
static float absFloat(float num){
    if(num >= 0) return num;
    return num * (-1);
}
static Map getAllGenreSeries(Map series_list, const char* genre)
{
    Map new_list = mapCreate(seriesCopy, seriesCopyName, seriesDestroy,
                             seriesDestroyName, seriesCompareNames);
    MAP_FOREACH(char*, ptr, series_list){
        Series current_series = mapGet(series_list, ptr);
        const char* current_genre = seriesGetGenre(current_series);
        if(strcmp(genre, current_genre) == 0){
            mapPut(new_list, ptr, current_series);
        }
    }
    return new_list;
}
static void updateUser(Map user_list, User updated_user){
    MAP_FOREACH(char*, ptr, user_list){
        User user = mapGet(user_list, ptr);
        if(userIsFriend(user, updated_user)){
            userRemoveFriend(user, updated_user);
            userAddFriend(user, updated_user);
        }
    }
}
=======
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
    if (!mapContains(mtmflix->userList, username)) return MTMFLIX_USER_DOES_NOT_EXIST;
    if (count < 0) return MTMFLIX_ILLEGAL_NUMBER;
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
        if (recommended->points != 0)
            listInsertLast(recommendedList, recommended);
        series = mapGet(mtmflix->seriesList, mapGetNext(mtmflix->seriesList));
    }
    listSort(recommendedList, sortRecommended);
    Recommended recommended = listGetFirst(recommendedList);
    if (recommended)
        series = recommended->series;
    else
        series = NULL;
    while (series) {
        fprintf(outputStream, printSeries(series)); //...
        series = listGetNext(recommendedList);
    }
    listDestroy(recommendedList);
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
    if (!src) return;
    Recommended res = (Recommended)src;
    if (res->series)
        free (res->series);
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
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
