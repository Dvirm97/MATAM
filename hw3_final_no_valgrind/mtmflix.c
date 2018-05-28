#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "map.h"
#include "set.h"
#include "list.h"

#include "mtmflix.h"
#include "series.h"
#include "user.h"

#define GENRES_NUM 8

struct mtmFlix_t {
    Map userList;
    Map seriesList;
};

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
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixRemoveSeries(MtmFlix mtmflix, const char* name) {
    if(!mtmflix || !name) return MTMFLIX_NULL_ARGUMENT;
    if(!checkName(name)) return MTMFLIX_SERIES_DOES_NOT_EXIST;
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
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixSeriesJoin(MtmFlix mtmflix, const char* username,
                                const char* seriesName) {
    if (!mtmflix || !username || !seriesName) return MTMFLIX_NULL_ARGUMENT;
    User user = mapGet(mtmflix->userList, (char*)username);
    if (!user) return MTMFLIX_USER_DOES_NOT_EXIST;
    Series series = mapGet(mtmflix->seriesList, (char*)seriesName);
    if (!series) return MTMFLIX_SERIES_DOES_NOT_EXIST;
    if (userAddFavorite(user, series) == MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE)
        return MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE;
    updateUser(mtmflix->userList, user);
    mapPut(mtmflix->userList, (char*)username, user);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixSeriesLeave(MtmFlix mtmflix, const char* username,
                                 const char* seriesName) {
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
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixAddFriend(MtmFlix mtmflix, const char* username1,
                               const char* username2) {
    if (!mtmflix || !username1 || !username2) return MTMFLIX_NULL_ARGUMENT;
    User user = mapGet(mtmflix->userList, (char*)username1);
    User friend = mapGet(mtmflix->userList, (char*)username2);
    if (!user || !friend) return MTMFLIX_USER_DOES_NOT_EXIST;
    userAddFriend(user, friend);
    updateUser(mtmflix->userList, user);
    mapPut(mtmflix->userList, (char*)username1, user);

    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixRemoveFriend(MtmFlix mtmflix, const char* username1,
                                  const char* username2) {
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
        return MTMFLIX_NO_SERIES;

    const char* sorted_genres[] = { "COMEDY", "CRIME", "DOCUMENTARY", "DRAMA",
                                    "HORROR", "MYSTERY", "ROMANCE", "SCIENCE_FICTION"};

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
                if(strcmp(ptr, min_name) < 0){
                    min_name = realloc(min_name, sizeof(char)*(strlen(ptr)+1));
                    strcpy(min_name, ptr);
                }
            }
            mapRemove(genre_list, min_name);

            // Print series in genre
            Series series = mapGet(mtmflix->seriesList,
                                   (MapKeyElement)min_name);
            const char* output = seriesPrint(series);
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
        // Get the next name to print
        char* tmp = mapGetFirst(user_name);
        char* min_name = malloc(strlen(tmp)+1);
        if(!min_name) {
            mapDestroy(user_name);
            return MTMFLIX_OUT_OF_MEMORY;
        }
        strcpy(min_name, tmp);
        MAP_FOREACH(char*, ptr, user_name){
            if (strcmp(ptr, min_name) < 0) {
                min_name = realloc(min_name, sizeof(char)*(strlen(ptr)+1));
                strcpy(min_name,ptr);
            }
        }
        mapRemove(user_name, min_name);

        // Print name
        User user = mapGet(mtmflix->userList, min_name);
        const char* output = userPrint(user);
        fprintf(outputStream,output);
        free(min_name);
    }
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixGetRecommendations(MtmFlix mtmflix, const char* username,
                                        int count, FILE* outputStream){
    // Check input
    if (!mtmflix || !username || !outputStream) return MTMFLIX_NULL_ARGUMENT;
    if (!mapContains(mtmflix->userList, (MapKeyElement)username))
        return MTMFLIX_USER_DOES_NOT_EXIST;
    if (count < 0) return MTMFLIX_ILLEGAL_NUMBER;

    // Get points for each series
    List recommended_list = listCreate(seriesCopy, seriesDestroy);
    char* ptr = mapGetFirst(mtmflix->seriesList);
    while(ptr){
        Series series = mapGet(mtmflix->seriesList, ptr);
        int points = calculatePoints(mtmflix, username, series);
        if (points != 0){
            seriesSetPoints(series, points);
            listInsertFirst(recommended_list, series);
        }
        ptr = mapGetNext(mtmflix->seriesList);

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