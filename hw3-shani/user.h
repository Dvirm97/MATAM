
#ifndef HW3_USER_H
#define HW3_USER_H
#include "map.h"
#include "series.h"
#include "mtm_ex3.h"
#include "set.h"

typedef struct user* User;

MapDataElement copyUser(MapDataElement src);
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
SetElement copyUserSet(SetElement src);

const char* printUser(User user);
void userDestroy(User user);
void freeUser(ListElement user);
int stringCompare(ListElement str1, ListElement str2);
char* userGetName(void* user);
ListElement copyUserName(ListElement str);

#endif //HW3_USER_H
