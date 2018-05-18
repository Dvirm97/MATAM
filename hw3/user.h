
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
User createUser(const char* username, int age);
MtmFlixResult userAddFavorite(User user, Series series);
MtmFlixResult userRemoveFavorite(User user, Series series);

void printUser(User user); //remove

#endif //HW3_USER_H
