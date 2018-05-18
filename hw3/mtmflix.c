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


struct mtmFlix_t {
    Map userList;
    Map seriesList;
};
static bool checkName(char* username);

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
        free(mtmflix);
    }
}
MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age) {

    char* newUsername = malloc(strlen(username));
    strcpy(newUsername, username);
    User user = createUser(username, age);
    mapPut(mtmflix->userList, newUsername, user);

    user = mapGet(mtmflix->userList, newUsername); //remove
    printUser(user); //remove
    return MTMFLIX_SUCCESS;
}
MtmFlixResult mtmFlixRemoveUser(MtmFlix mtmflix, const char* username) {
    if (!mtmflix)
        return MTMFLIX_NULL_ARGUMENT;
    if (!username)
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
static bool checkName(char* username) {
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
    mapPut(mtmflix->userList, searchUsername, ourUser);
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
    if (!searchUsername)
        return MTMFLIX_USER_DOES_NOT_EXIST;
    //making a non-const seriesName and making sure it exists:
    char* searchSeriesName = malloc(strlen(seriesName));
    strcpy(searchSeriesName, seriesName);
    Series ourSeries = mapGet(mtmflix->seriesList, searchSeriesName);
    if (!searchSeriesName)
        return MTMFLIX_SERIES_DOES_NOT_EXIST;
    //the lines that actually make the function:
    userRemoveFavorite(ourUser, ourSeries);
    mapPut(mtmflix->userList, searchUsername, ourUser);
    //STILL NEED TO FREE SHIT! (USER, SERIES, NAMES)
    return MTMFLIX_SUCCESS;
}
