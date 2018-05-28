#include "user.h"

#include <stdlib.h>
#include <string.h>

struct user {
    char* username;
    int age;
    Set favorites;
    Set friends;
};

typedef char*(*GetNameFunction)(void*);

static List convertSetToList(Set set, GetNameFunction getName);

void* userCopy(void* user) {
    if (!user) return NULL;
    User src = (User)user;
    User dst = malloc(sizeof(*dst));
    if (!dst) return NULL;

    dst->username = malloc(sizeof(char)*(strlen(src->username)+1));
    if(!dst->username){
        free(dst);
        return NULL;
    }
    strcpy(dst->username, src->username);
    dst->age = src->age;
    dst->favorites = setCopy(src->favorites);
    dst->friends = setCopy(src->friends);
    return dst;
}
void userDestroy(void* user){
    if(!user) return;
    setDestroy(((User)user)->favorites);
    setDestroy(((User)user)->friends);
    free(((User)user)->username);
    free(user);
}

void* userCopyName(void* str){
    char* new_str = malloc(sizeof(char)*(strlen((char*)str)+1));
    if(!new_str) return NULL;
    strcpy(new_str, (char*)str);
    return (void*)new_str;
}
void userDestroyName(void* name) {
    free(name);
}
int userCompareNames(void* name1, void* name2) {
    return strcmp((char*)name1, (char*)name2);
}
int userCompareNamesForSet(SetElement user1, SetElement user2) {
    return strcmp(((User)user1)->username, ((User)user2)->username);
}

User userCreate(const char* username, int new_age) {
    User user = malloc(sizeof(*user));
    if(!user) return NULL;

    user->username = malloc(sizeof(char) * (strlen(username) + 1));
    if(!user->username){
        free(user);
        return NULL;
    }

    strcpy(user->username, username);
    user->age = new_age;
    user->favorites = setCreate(seriesCopy, seriesDestroy,
                                seriesCompareNamesForSet);
    user->friends = setCreate(userCopy, userDestroy, userCompareNamesForSet);
    return user;
}
char* userGetName(void* user){
    if(!user) return NULL;
    return ((User)user)->username;
}
const char* userPrint(User user) {
    if(!user) return NULL;
    return mtmPrintUser(user->username, user->age,
                        convertSetToList(user->friends, userGetName),
                        convertSetToList(user->favorites, seriesGetName));
}

MtmFlixResult userAddFavorite(User user, Series series) {
    // Check input
    if (!user || !series) return MTMFLIX_NULL_ARGUMENT;

    // Check if user is in the right age for the series
    if (!userCheckAges(user, series)) return MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE;

    // Add series to user's favorites
    if (setAdd(user->favorites, series) == SET_OUT_OF_MEMORY)
        return MTMFLIX_OUT_OF_MEMORY;
    return MTMFLIX_SUCCESS;
}
MtmFlixResult userRemoveFavorite(User user, Series series) {
    if (!user || !series) return MTMFLIX_NULL_ARGUMENT;
    setRemove(user->favorites, series);
    return MTMFLIX_SUCCESS;
}
// Check if series is in user's favorites
bool userIsFavorite(User user, Series series) {
    return setIsIn(user->favorites, series);
}

MtmFlixResult userRemoveFriend(User user, User friend) {
    if (!user || !friend)return MTMFLIX_NULL_ARGUMENT;
    setRemove(user->friends, friend);
    return MTMFLIX_SUCCESS;
}
MtmFlixResult userAddFriend(User user, User friend) {
    if (!user || !friend) return MTMFLIX_NULL_ARGUMENT;
    setAdd(user->friends, friend);
    return MTMFLIX_SUCCESS;
}
// Check if the second user is in the friends list of the first user
bool userIsFriend(User user, User friend){
    return setIsIn(user->friends, friend);
}

// Check if the user is in the right age for the series
bool userCheckAges(User user, Series series) {
    if(!user || !series) return false;
    int* ages = seriesGetAges(series);
    if (!ages) return true;
    return !(user->age < *ages || user->age > *(ages + 1));
}
// Count how many friends of the user like the series
int userCountFriendsLikes(User user, Series series) {
    int likeCounter = 0;
    SET_FOREACH(User, friend, user->friends){
        if (setIsIn(friend->favorites, series))
            likeCounter++;
    }
    return likeCounter;
}
/* Count the amount of series in user's favoirtes  list are of the same genre
 * as the input series
 */
int userCountSameGenre(User user, Series series) {
    int sameGenreCounter = 0;
    const char* genre = seriesGetGenre(series);
    SET_FOREACH(Series, favorite, user->favorites){
        if (seriesGetGenre(favorite) == genre)
            sameGenreCounter++;
    }
    return sameGenreCounter;
}

// Get the average length of episode duration of all user's favorite series
float userGetFavoritesAvgLen(User user) {
    // Count favorites duration sum
    int lenSum = 0;
    SET_FOREACH(Series, favorite, user->favorites){
        lenSum += seriesGetEpisodeDuration(favorite);
    }

    // Get amount of favorite series
    int numOfSeries = setGetSize(user->favorites);

    // Calculate and return average
    return (float)lenSum/(float)numOfSeries;
}

static List convertSetToList(Set set, GetNameFunction getName){
    // Check input
    if(!set || !getName) return NULL;

    // Make a list
    List list = listCreate(userCopyName, userDestroy);
    if(!list) return NULL;

    // Copy set's items to list
    char* ptr = getName(setGetFirst(set));
    if(!ptr) {
        listDestroy(list);
        return NULL;
    }
    while(ptr){
        listInsertFirst(list, ptr);;
        ptr = getName(setGetNext(set));
    }

    return list;
}