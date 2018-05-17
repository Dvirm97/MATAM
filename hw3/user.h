
#ifndef HW3_USER_H
#define HW3_USER_H
#include "map.h"

typedef struct user* User;

MapDataElement copyUser(MapDataElement src);
MapKeyElement userCopyName(MapKeyElement src);
void deleteUser(MapDataElement user);
void userDeleteName(MapKeyElement name);
int userCompareNames(MapKeyElement name1, MapKeyElement name2);
User createUser(char* username, int age);

void printUser(User user); //remove

#endif //HW3_USER_H
