#ifndef HW3_USER_H
#define HW3_USER_H

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

#endif //HW3_USER_H