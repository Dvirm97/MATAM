
#ifndef HW3_USER_H
#define HW3_USER_H
#include "map.h"
#include "series.h"
#include "mtm_ex3.h"

typedef struct user* User;

MapDataElement copyUser(MapDataElement src);
MapKeyElement userCopyName(MapKeyElement src);
void deleteUser(MapDataElement user);
void userDeleteName(MapKeyElement name);
int userCompareNames(MapKeyElement name1, MapKeyElement name2);
int userCompareNamesForSet(MapKeyElement user1, MapKeyElement user2);
User createUser(const char* username, int age);
MtmFlixResult userAddFavorite(User user, Series series);
MtmFlixResult userRemoveFavorite(User user, Series series);
MtmFlixResult userAddFriend(User user, User friend);
MtmFlixResult userRemoveFriend(User user, User friend);

const char* printUser(char* user_name, User user);

#endif //HW3_USER_H
