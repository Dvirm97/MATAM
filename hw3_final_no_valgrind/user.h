#ifndef HW3_USER_H
#define HW3_USER_H
<<<<<<< HEAD

#include "map.h"
#include "set.h"
#include "mtm_ex3.h"

#include "series.h"
#include "mtmflix.h"

typedef struct user* User;

void* userCopy(void* user);
void userDestroy(void* user);

void* userCopyName(void* str);
void userDestroyName(void* name);
int userCompareNames(void* name1, void* name2);
int userCompareNamesForSet(SetElement user1, SetElement user2);

User userCreate(const char* username, int new_age);
char* userGetName(void* user);
const char* userPrint(User user);

MtmFlixResult userAddFavorite(User user, Series series);
MtmFlixResult userRemoveFavorite(User user, Series series);
bool userIsFavorite(User user, Series series);

MtmFlixResult userRemoveFriend(User user, User friend);
MtmFlixResult userAddFriend(User user, User friend);
bool userIsFriend(User user, User friend);

bool userCheckAges(User user, Series series);
int userCountFriendsLikes(User user, Series series) ;
int userCountSameGenre(User user, Series series);
float userGetFavoritesAvgLen(User user);
=======
#include "map.h"
#include "series.h"
#include "mtm_ex3.h"
#include "set.h"

typedef struct user* User;

MapDataElement copyUser(MapDataElement src);
SetElement copyUserSet(SetElement src);
MapKeyElement userCopyName(MapKeyElement src);
void deleteUser(MapDataElement user);
void deleteUserSet(SetElement user);
void userDeleteName(MapKeyElement name);
int userCompareNames(MapKeyElement name1, MapKeyElement name2);
int userSetCompareNames(SetElement user1, SetElement user2);
int userCompareNamesForSet(MapKeyElement user1, MapKeyElement user2);
User createUser(const char* username, int age);
MtmFlixResult userAddFavorite(User user, Series series);
MtmFlixResult userRemoveFavorite(User user, Series series);
MtmFlixResult userAddFriend(User user, User friend);
MtmFlixResult userRemoveFriend(User user, User friend);
bool userLikeSeries(User user, Series series);
bool userCheckAges(User user, Series series);
int userCountFriendsLikes(User user, Series series);
int userCountSameGenre(User user, Series series);
float userCalcAvgLen(User user, Series series);

const char* printUser(User user);
void userDestroy(User user);
void freeUser(ListElement user);
char* userGetName(void* user);
ListElement copyUserName(ListElement str);
//int stringCompare(ListElement str1, ListElement str2);
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052

#endif //HW3_USER_H