#include "user.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "map.h"
struct user {
    char* username;
    int age;
};

MapDataElement copyUser(MapDataElement src) {
    if (!src) {
        return NULL;
    }
    User dst = malloc(sizeof(*dst));
    if (!dst) {
        return NULL;
    }
    User res = (User)src; //doing this right?
    strcpy(dst->username, res->username); //dunno if need another malloc for this
    dst->age = res->age;
    return dst;
}
MapKeyElement userCopyName(MapKeyElement src) {
    char* dst = malloc(strlen(src)+1);
    strcpy(dst, src);
    return dst;
}
void deleteUser(MapDataElement user) { //Do it better
    if (!user)
        return;
    free(user);
}
void userDeleteName(MapKeyElement name) {
    free(name);
}
int userCompareNames(MapKeyElement name1, MapKeyElement name2) {
    return strcmp((char*)name1, (char*)name2);
}
User createUser(char* newUsername, int newAge) {
    User user = malloc(sizeof(user));
    strcpy(user->username, newUsername);
    user->age = newAge;
    return user;
}
void printUser(User user) { //remove this function
    printf("%s\n%d", user->username, user->age);
}
