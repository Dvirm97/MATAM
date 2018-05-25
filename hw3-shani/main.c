#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "mtmflix.h"
#include "test_utilities.h"
#include "user.h"
#include "mtm_ex3.h"
#include "series.h"
#include "list.h"
#include <stdlib.h>
#define str(x) #x
#define xstr(x) str(x)


char* readFile(char* path);
bool mtmFlixUnitTest();
bool mtmFlixCreateTest();
bool mtmflixAddUserTest();
bool mtmFlixRemoveUserTest();
bool mtmFlixAddSeriesTest();
bool mtmFlixRemoveSeriesTest();
bool mtmFlixReportUsersTest();
bool mtmFlixReportSeriesTest();
bool mtmFlixSeriesJoinTest();
bool mtmFlixSeriesLeaveTest();
bool mtmFlixAddFriendTest();
bool mtmFlixRemoveFriendTest();
//bool mtmFlixGetRecommendationsTest();
bool mtmFlixRemoveUserTestAdvanced();
bool mtmFlixRemoveSeriesTestAdvanced();

int main() {
    /*char* results[17] ={
            "MTMFLIX_SUCCESS",
            "MTMFLIX_OUT_OF_MEMORY", // You should exit program after this error
            "MTMFLIX_CANNOT_OPEN_FILE", // You should exit program after this error
            "MTMFLIX_NULL_ARGUMENT",
            "MTMFLIX_ILLEGAL_USERNAME",
            "MTMFLIX_USERNAME_ALREADY_USED",
            "MTMFLIX_ILLEGAL_AGE",
            "MTMFLIX_USER_DOES_NOT_EXIST",
            "MTMFLIX_ILLEGAL_SERIES_NAME",
            "MTMFLIX_SERIES_ALREADY_EXISTS",
            "MTMFLIX_ILLEGAL_EPISODES_NUM",
            "MTMFLIX_ILLEGAL_EPISODES_DURATION",
            "MTMFLIX_SERIES_DOES_NOT_EXIST",
            "MTMFLIX_NO_SERIES",
            "MTMFLIX_ILLEGAL_NUMBER",
            "MTMFLIX_NO_USERS",
            "MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE"};

    MtmFlix system = mtmFlixCreate();

    int ages1[2] = {25, 90};
    int ages2[2] = {7, 50};
    mtmFlixAddSeries(system, "House", 30, DRAMA, NULL, 60);
    mtmFlixAddSeries(system, "Homeland", 30, CRIME, ages1, 60);
    mtmFlixAddSeries(system, "Shameless", 50, COMEDY, ages2, 45);

    mtmFlixAddUser(system, "Chandler", 23);
    mtmFlixSeriesJoin(system, "Chandler", "Shameless");
    mtmFlixSeriesJoin(system, "Chandler", "House");

    mtmFlixAddUser(system, "Rachel", 22);
    mtmFlixSeriesJoin(system, "Rachel", "House");

    FILE* fp = fopen("./mtmFlixSeriesJoin_test.out", "w");

    mtmFlixReportUsers(system, fp);

    fclose(fp);

   const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Chandler is 23 years old\n"
            "Series: House\n"
            "Series: Shameless\n"
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Rachel is 22 years old\n"
            "Series: House\n";
    char* output = readFile("./mtmFlixSeriesJoin_test.out");
    printf("output:\n%s\n",output);

    mtmFlixDestroy(system);



    List friends = listCreate(copyUserName, freeUser);
    listInsertFirst(friends,"Monica");
    listInsertFirst(friends,"Joey");
    listInsertFirst(friends,"Ross");

    List favorites = listCreate(copyUserName, freeUser);
    listInsertFirst(favorites, "movie1");
    listInsertFirst(favorites, "movie2");
    listInsertFirst(favorites, "movie3");

    User rachel = createUser("Rachel",22);
    User chandler = createUser("Chandler",22);
    Series house = createSeries("House", 30, DRAMA, NULL, 60);
    Series shameless = createSeries("Shameless", 30, DRAMA, NULL, 60);
    userAddFavorite(chandler, house);
    userAddFavorite(rachel, house);
    userAddFavorite(rachel, shameless);


    MtmFlix system = mtmFlixCreate();

    int ages1[2] = {25, 90};
    int ages2[2] = {7, 50};
    mtmFlixAddSeries(system, "House", 30, DRAMA, NULL, 60);
    mtmFlixAddSeries(system, "Homeland", 30, CRIME, ages1, 60);
    mtmFlixAddSeries(system, "Shameless", 50, COMEDY, ages2, 45);
    mtmFlixAddUser(system, "Chandler", 23);

    ASSERT_TEST(mtmFlixSeriesJoin(system, "Chandler", "Shameless") == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Chandler", "House") == MTMFLIX_SUCCESS);

    mtmFlixAddUser(system, "Rachel", 22);

    mtmFlixSeriesJoin(system, "Rachel", "Shameless");

    printUser(rachel);
    printf("\n");
    printUser(chandler);*/
    mtmFlixUnitTest();
    return 0;
}

bool mtmFlixUnitTest() {
    printf("\n");
    RUN_TEST(mtmFlixCreateTest);
    RUN_TEST(mtmflixAddUserTest);
    RUN_TEST(mtmFlixRemoveUserTest);
    RUN_TEST(mtmFlixAddSeriesTest);
    RUN_TEST(mtmFlixRemoveSeriesTest);
    RUN_TEST(mtmFlixReportSeriesTest);
    RUN_TEST(mtmFlixReportUsersTest);
    RUN_TEST(mtmFlixSeriesJoinTest);
    RUN_TEST(mtmFlixSeriesLeaveTest);
    RUN_TEST(mtmFlixAddFriendTest);
    RUN_TEST(mtmFlixRemoveFriendTest);
//    RUN_TEST(mtmFlixGetRecommendationsTest);
    RUN_TEST(mtmFlixRemoveUserTestAdvanced);
    RUN_TEST(mtmFlixRemoveSeriesTestAdvanced);

  // MessageBox(NULL, "I don't know about the code, but are you sure your style is good?\n\n"
    //        "https://xkcd.com/1695/" , "Real Windows dialogue", 4);
    return true;
}

bool mtmFlixCreateTest() {
    MtmFlix system = mtmFlixCreate();
    mtmFlixDestroy(system);
    return true;
}

bool mtmflixAddUserTest() {
    MtmFlix system = mtmFlixCreate();
    // Null values
    ASSERT_TEST(mtmFlixAddUser(NULL, "Chandler", 23) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddUser(system, NULL, 23) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddUser(NULL, "@lon", 23) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddUser(system, NULL, -3) == MTMFLIX_NULL_ARGUMENT);
    // Name tests
    ASSERT_TEST(mtmFlixAddUser(system, "Chandler", 23) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddUser(system, "Chandler123", 23) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddUser(system, "321Chandler09", 23) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddUser(system, "Chandler!", 23) == MTMFLIX_ILLEGAL_USERNAME);
    ASSERT_TEST(mtmFlixAddUser(system, "Al~n", 23) == MTMFLIX_ILLEGAL_USERNAME);
    ASSERT_TEST(mtmFlixAddUser(system, "", 23) == MTMFLIX_ILLEGAL_USERNAME);
    ASSERT_TEST(mtmFlixAddUser(system, "Chandler!", -8) == MTMFLIX_ILLEGAL_USERNAME);
    // User already exists
    mtmFlixAddUser(system, "Monica", 30);
    ASSERT_TEST(mtmFlixAddUser(system, "Monica", 31) == MTMFLIX_USERNAME_ALREADY_USED);
    ASSERT_TEST(mtmFlixAddUser(system, "Monica", -6) == MTMFLIX_USERNAME_ALREADY_USED);
    // Age tests
    ASSERT_TEST(mtmFlixAddUser(system, "Rachel", 22) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddUser(system, "Rachel2", MTM_MAX_AGE) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddUser(system, "Rachel3", MTM_MIN_AGE) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddUser(system, "Rachel4", MTM_MAX_AGE + 1) == MTMFLIX_ILLEGAL_AGE);
    ASSERT_TEST(mtmFlixAddUser(system, "Rachel5", MTM_MIN_AGE - 1) == MTMFLIX_ILLEGAL_AGE);
    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixRemoveUserTest() {
    MtmFlix system = mtmFlixCreate();
    // Null values
    ASSERT_TEST(mtmFlixRemoveUser(NULL, "Chandler") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixRemoveUser(system, NULL) == MTMFLIX_NULL_ARGUMENT);
    // User tests
    ASSERT_TEST(mtmFlixRemoveUser(system, "Joey") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixRemoveUser(system, "") == MTMFLIX_USER_DOES_NOT_EXIST);
    mtmFlixAddUser(system, "Chandler", 23);
    ASSERT_TEST(mtmFlixRemoveUser(system, "Chandler") == MTMFLIX_SUCCESS);
    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixAddSeriesTest() {
    MtmFlix system = mtmFlixCreate();
    // Null values
    ASSERT_TEST(mtmFlixAddSeries(NULL, "Friends", 9000, COMEDY, NULL, 25) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddSeries(system, NULL, 9000, COMEDY, NULL, 25) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddSeries(NULL, "#Blessed", 10,DRAMA, NULL, 25) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddSeries(NULL, "Firefly", -1, SCIENCE_FICTION, NULL, 25) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddSeries(system, NULL, 10, COMEDY, NULL, -1) == MTMFLIX_NULL_ARGUMENT);
    // Name tests
    ASSERT_TEST(mtmFlixAddSeries(system, "Friends", 9000, COMEDY, NULL, 25) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddSeries(system, "21JumpStreet", 20, COMEDY, NULL, 25) == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixAddSeries(system, "2 And 1/2 Men", 20, COMEDY, NULL, 25) == MTMFLIX_ILLEGAL_SERIES_NAME);
    ASSERT_TEST(mtmFlixAddSeries(system, "", 20, COMEDY, NULL, 25) == MTMFLIX_ILLEGAL_SERIES_NAME);
    ASSERT_TEST(mtmFlixAddSeries(system, "", -1, COMEDY, NULL, 25) == MTMFLIX_ILLEGAL_SERIES_NAME);
    ASSERT_TEST(mtmFlixAddSeries(system, "", 20, COMEDY, NULL, -1) == MTMFLIX_ILLEGAL_SERIES_NAME);
    // Series already exists
    mtmFlixAddSeries(system, "Scrubs", 160, COMEDY, NULL, 25);
    ASSERT_TEST(mtmFlixAddSeries(system, "Scrubs", 160, COMEDY, NULL, 25) == MTMFLIX_SERIES_ALREADY_EXISTS);
    ASSERT_TEST(mtmFlixAddSeries(system, "Scrubs", -1, COMEDY, NULL, 25) == MTMFLIX_SERIES_ALREADY_EXISTS);
    ASSERT_TEST(mtmFlixAddSeries(system, "Scrubs", 160, COMEDY, NULL, -1) == MTMFLIX_SERIES_ALREADY_EXISTS);
    // Age tests
    int ages1[2] = {MTM_MIN_AGE, MTM_MAX_AGE};
    ASSERT_TEST(mtmFlixAddSeries(system, "Community", 60, COMEDY, ages1, 25) == MTMFLIX_SUCCESS);
    int ages2[2] = {MTM_MIN_AGE - 1, MTM_MAX_AGE};
    ASSERT_TEST(mtmFlixAddSeries(system, "BreakingBad", 50, DRAMA, ages2, 60) == MTMFLIX_SUCCESS);
    int ages3[2] = {MTM_MIN_AGE, MTM_MAX_AGE + 1};
    ASSERT_TEST(mtmFlixAddSeries(system, "Westworld", 20, DRAMA, ages3, 60) == MTMFLIX_SUCCESS);
    // EpisodesNum tests
    ASSERT_TEST(mtmFlixAddSeries(system, "Firefly", 0, SCIENCE_FICTION, NULL, 45) == MTMFLIX_ILLEGAL_EPISODES_NUM);
    ASSERT_TEST(mtmFlixAddSeries(system, "Halo", -1, SCIENCE_FICTION, NULL, 45) == MTMFLIX_ILLEGAL_EPISODES_NUM);
    ASSERT_TEST(mtmFlixAddSeries(system, "Halo", -1, SCIENCE_FICTION, NULL, -1) == MTMFLIX_ILLEGAL_EPISODES_NUM);
    // EpisodeDuration tests
    ASSERT_TEST(mtmFlixAddSeries(system, "DoctorWho", 500, SCIENCE_FICTION, NULL, 0) == MTMFLIX_ILLEGAL_EPISODES_DURATION);
    ASSERT_TEST(mtmFlixAddSeries(system, "Suits", 500, DRAMA, NULL, -1) == MTMFLIX_ILLEGAL_EPISODES_DURATION);
    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixRemoveSeriesTest() {
    MtmFlix system = mtmFlixCreate();
    ASSERT_TEST(mtmFlixAddSeries(system, "Homeland", 30, CRIME, NULL, 60) == MTMFLIX_SUCCESS);
    // Null values
    ASSERT_TEST(mtmFlixRemoveSeries(NULL, "Friends") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixRemoveSeries(system, NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixRemoveSeries(NULL, "Skins") == MTMFLIX_NULL_ARGUMENT);
    // Series tests
    ASSERT_TEST(mtmFlixRemoveSeries(system, "13ReasonsWhy") == MTMFLIX_SERIES_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixRemoveSeries(system, "") == MTMFLIX_SERIES_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixRemoveSeries(system, "Homeland") == MTMFLIX_SUCCESS);
    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixReportSeriesTest() {


      /*char* results[15] ={
        "MTMFLIX_SUCCESS",
        "MTMFLIX_OUT_OF_MEMORY",
        "MTMFLIX_NULL_ARGUMENT",
        "MTMFLIX_SERIES_ALREADY_EXISTS",
        "MTMFLIX_SERIES_DOES_NOT_EXIST",
        "MTMFLIX_NO_SERIES",
        "MTMFLIX_USER_ALREADY_EXISTS",
        "MTMFLIX_USER_DOES_NOT_EXIST",
        "MTMFLIX_NO_USERS",
        "MTMFLIX_USER_ALREADY_FRIEND",
        "MTMFLIX_USER_NOT_FRIEND",
        "MTMFLIX_ILLEGAL_VALUE",
        "MTMFLIX_ILLEGAL_EPISODES_NUM",
        "MTMFLIX_ILLEGAL_EPISODES_DURATION",
        "MTMFLIX_ILLEGAL_SERIES_NAME"
    };*/
    MtmFlix system = mtmFlixCreate();
    FILE* fp = fopen("./mtmFlixReportSeries_test.out", "w");
    ASSERT_TEST(mtmFlixReportSeries(NULL, 0, fp) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixReportSeries(system, 0, NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixReportSeries(system, 0, fp) == MTMFLIX_NO_SERIES);
    ASSERT_TEST(mtmFlixReportSeries(system, 5, fp) == MTMFLIX_NO_SERIES);
    // Report with no amount limitations
    int ages[2] = {18, 25};
    mtmFlixAddSeries(system, "Friends", 9000, COMEDY, NULL, 25);
    mtmFlixAddSeries(system, "Westworld", 20, DOCUMENTARY, NULL, 60);
    mtmFlixAddSeries(system, "GameOfThrones", 70, DOCUMENTARY, ages, 60);

    //printf("syste:\n");
    //printS(system);

    MtmFlixResult result = mtmFlixReportSeries(system, 0, fp);
    fclose(fp);
    char* output = readFile("./mtmFlixReportSeries_test.out");
    //printf("\noutput:\n%s\n%s",output,results[(int)result]);
    const char* test1_valid = "Series 'Friends', Genre: COMEDY.\n"
            "Series 'GameOfThrones', Genre: DOCUMENTARY.\n"
            "Series 'Westworld', Genre: DOCUMENTARY.\n";
    ASSERT_TEST(result == MTMFLIX_SUCCESS && strcmp(output, test1_valid) == 0);

    // Report with amount limitation
    fp = fopen("./mtmFlixReportSeries_test.out", "w");
    result = mtmFlixReportSeries(system, 1, fp);
    fclose(fp);
    output = readFile("./mtmFlixReportSeries_test.out");
    const char* test2_valid = "Series 'Friends', Genre: COMEDY.\n"
            "Series 'GameOfThrones', Genre: DOCUMENTARY.\n";
    ASSERT_TEST(result == MTMFLIX_SUCCESS && strcmp(output, test2_valid) == 0);

    // Report with series below, at, and above amount limitation
    mtmFlixAddSeries(system, "24", 24, ROMANCE, ages, 24);
    mtmFlixAddSeries(system, "Scrubs", 300, COMEDY, ages, 25);
    mtmFlixAddSeries(system, "PlanetEarth", 10, DOCUMENTARY, NULL, 45);
    mtmFlixAddSeries(system, "TheCrown", 10, DOCUMENTARY, ages, 50);

    fp = fopen("./mtmFlixReportSeries_test.out", "w");
    result = mtmFlixReportSeries(system, 2, fp);
    fclose(fp);
    output = readFile("./mtmFlixReportSeries_test.out");
    const char* test3_valid = "Series 'Friends', Genre: COMEDY.\n"
            "Series 'Scrubs', Genre: COMEDY.\n"
            "Series 'GameOfThrones', Genre: DOCUMENTARY.\n"
            "Series 'PlanetEarth', Genre: DOCUMENTARY.\n"
            "Series '24', Genre: ROMANCE.\n";
    ASSERT_TEST(result == MTMFLIX_SUCCESS && strcmp(output, test3_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixReportUsersTest() {
    MtmFlix system = mtmFlixCreate();

    FILE* fp = fopen("./mtmFlixReportUsers_test.out", "w");
    ASSERT_TEST(mtmFlixReportUsers(NULL, fp) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixReportUsers(system, NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixReportUsers(system, fp) == MTMFLIX_NO_USERS);

    // Report with people
    mtmFlixAddUser(system, "Rachel", 18);
    mtmFlixAddUser(system, "Chandler", 23);
    mtmFlixAddUser(system, "Monica", 30);
    MtmFlixResult result = mtmFlixReportUsers(system, fp);
    fclose(fp);
    const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Chandler is 23 years old\n"
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Monica is 30 years old\n"
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Rachel is 18 years old\n";
    char* output = readFile("./mtmFlixReportUsers_test.out");
    ASSERT_TEST(result == MTMFLIX_SUCCESS && strcmp(output, test1_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixSeriesJoinTest() {


    MtmFlix system = mtmFlixCreate();
    // Null values
    ASSERT_TEST(mtmFlixSeriesJoin(NULL, "Chandler", "House") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixSeriesJoin(system, NULL, "House") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Chandler", NULL) == MTMFLIX_NULL_ARGUMENT);

    int ages1[2] = {25, 90};
    int ages2[2] = {7, 50};
    mtmFlixAddSeries(system, "House", 30, DRAMA, NULL, 60);
    mtmFlixAddSeries(system, "Homeland", 30, CRIME, ages1, 60);
    mtmFlixAddSeries(system, "Shameless", 50, COMEDY, ages2, 45);
    mtmFlixAddUser(system, "Chandler", 23);

    // Nonexistent elements
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Rachel", "House") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesJoin(system, "", "House") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Rachel", "FullHouse") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Chandler", "FullHouse") == MTMFLIX_SERIES_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Chandler", "") == MTMFLIX_SERIES_DOES_NOT_EXIST);

    // Invalid age
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Chandler", "Homeland") == MTMFLIX_USER_NOT_IN_THE_RIGHT_AGE);

    // Valid input
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Chandler", "Shameless") == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixSeriesJoin(system, "Chandler", "House") == MTMFLIX_SUCCESS);

    mtmFlixAddUser(system, "Rachel", 22);

    mtmFlixSeriesJoin(system, "Rachel", "House");
    //mtmFlixSeriesJoin(system, "Rachel", "Shameless");

    FILE* fp = fopen("./mtmFlixSeriesJoin_test.out", "w");

    mtmFlixReportUsers(system, fp);

    fclose(fp);

    const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Chandler is 23 years old\n"
            "Series: House\n"
            "Series: Shameless\n"
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Rachel is 22 years old\n"
            "Series: House\n";
    char* output = readFile("./mtmFlixSeriesJoin_test.out");

    ASSERT_TEST(strcmp(output, test1_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixSeriesLeaveTest() {
    MtmFlix system = mtmFlixCreate();
    ASSERT_TEST(mtmFlixSeriesLeave(NULL, "Chandler", "Argo") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixSeriesLeave(system, NULL, "Argo") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixSeriesLeave(system, "Chandler", NULL) == MTMFLIX_NULL_ARGUMENT);

    mtmFlixAddSeries(system, "Argo", 30, DRAMA, NULL, 60);
    mtmFlixAddUser(system, "Chandler", 23);
    mtmFlixSeriesJoin(system, "Chandler", "Argo");

    // Nonexistent elements
    ASSERT_TEST(mtmFlixSeriesLeave(system, "Rachel", "Argo") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesLeave(system, "", "Argo") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesLeave(system, "Rachel", "TheBrink") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesLeave(system, "Chandler", "TheBrink") == MTMFLIX_SERIES_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixSeriesLeave(system, "Chandler", "") == MTMFLIX_SERIES_DOES_NOT_EXIST);

   // Valid input
    ASSERT_TEST(mtmFlixSeriesLeave(system, "Chandler", "Argo") == MTMFLIX_SUCCESS);
    FILE* fp = fopen("./mtmFlixSeriesLeave_test.out", "w");
    mtmFlixReportUsers(system, fp);
    fclose(fp);
    const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Chandler is 23 years old\n";
    char* output = readFile("./mtmFlixSeriesLeave_test.out");
    ASSERT_TEST(strcmp(output, test1_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixAddFriendTest() {
    MtmFlix system = mtmFlixCreate();
    mtmFlixAddUser(system, "Chandler", 23);
    mtmFlixAddUser(system, "Rachel", 22);

    // Null values
    ASSERT_TEST(mtmFlixAddFriend(system, NULL, "Rachel") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddFriend(system, "Rachel", NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddFriend(system, "Joey", NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixAddFriend(system, NULL, "Joey") == MTMFLIX_NULL_ARGUMENT);

    // Nonexistent elements
    ASSERT_TEST(mtmFlixAddFriend(system, "Rachel", "Joey") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixAddFriend(system, "Joey", "Rachel") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixAddFriend(system, "Monica", "Joey") == MTMFLIX_USER_DOES_NOT_EXIST);

    // One-sided friendship
    ASSERT_TEST(mtmFlixAddFriend(system, "Chandler", "Rachel") == MTMFLIX_SUCCESS);
    FILE* fp = fopen("./mtmFlixAddFriend_test.out", "w");
    mtmFlixReportUsers(system, fp);
    fclose(fp);
    const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Chandler is 23 years old\n"
            "Friend: Rachel\n"
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Rachel is 22 years old\n";
    char* output = readFile("./mtmFlixAddFriend_test.out");
    ASSERT_TEST(strcmp(output, test1_valid) == 0);

    // Two-sided friendship
    mtmFlixAddFriend(system, "Rachel", "Chandler");
    fp = fopen("./mtmFlixAddFriend_test.out", "w");
    mtmFlixReportUsers(system, fp);
    fclose(fp);
    const char* test2_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Chandler is 23 years old\n"
            "Friend: Rachel\n"
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Rachel is 22 years old\n"
            "Friend: Chandler\n";
    output = readFile("./mtmFlixAddFriend_test.out");
    ASSERT_TEST(strcmp(output, test2_valid) == 0);

    mtmFlixDestroy(system);

    return true;
}

bool mtmFlixRemoveFriendTest() {
    MtmFlix system = mtmFlixCreate();
    mtmFlixAddUser(system, "Chandler", 23);
    mtmFlixAddUser(system, "Rachel", 22);
    mtmFlixAddUser(system, "Phoebe", 24);

    // Null values
    ASSERT_TEST(mtmFlixRemoveFriend(system, NULL, "Rachel") == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixRemoveFriend(system, "Rachel", NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixRemoveFriend(system, "Ross", NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixRemoveFriend(system, NULL, "Ross") == MTMFLIX_NULL_ARGUMENT);

    // Nonexistent elements
    ASSERT_TEST(mtmFlixRemoveFriend(system, "Ross", "Chandler") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixRemoveFriend(system, "Chandler", "Ross") == MTMFLIX_USER_DOES_NOT_EXIST);
    ASSERT_TEST(mtmFlixRemoveFriend(system, "Ross", "Tamar") == MTMFLIX_USER_DOES_NOT_EXIST);

    mtmFlixAddFriend(system, "Rachel", "Chandler");
    mtmFlixAddFriend(system, "Rachel", "Phoebe");
    mtmFlixAddFriend(system, "Phoebe", "Rachel");
    mtmFlixAddFriend(system, "Phoebe", "Chandler");

    // Valid input
    ASSERT_TEST(mtmFlixRemoveFriend(system, "Rachel", "Chandler") == MTMFLIX_SUCCESS);
    ASSERT_TEST(mtmFlixRemoveFriend(system, "Rachel", "Chandler") == MTMFLIX_SUCCESS);

    FILE* fp = fopen("./mtmFlixRemoveFriend_test.out", "w");
    mtmFlixReportUsers(system, fp);
    fclose(fp);
    const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Chandler is 23 years old\n"
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Phoebe is 24 years old\n"
            "Friend: Chandler\n"
            "Friend: Rachel\n"
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Rachel is 22 years old\n"
            "Friend: Phoebe\n";
    char* output = readFile("./mtmFlixRemoveFriend_test.out");
    ASSERT_TEST(strcmp(output, test1_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}
/*
bool mtmFlixGetRecommendationsTest() {
    MtmFlix system = mtmFlixCreate();
    FILE* fp = fopen("./mtmFlixGetRecommendations_test.out", "w");

    // Illegal arguments
    ASSERT_TEST(mtmFlixGetRecommendations(NULL, "Chandler", 0, fp) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixGetRecommendations(system, NULL, 0, fp) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixGetRecommendations(system, "Chandler", 0, NULL) == MTMFLIX_NULL_ARGUMENT);
    ASSERT_TEST(mtmFlixGetRecommendations(system, "Chandler", -1, fp) == MTMFLIX_USER_DOES_NOT_EXIST);
    mtmFlixAddUser(system, "Chandler", 23);
    ASSERT_TEST(mtmFlixGetRecommendations(system, "Chandler", -1, fp) == MTMFLIX_ILLEGAL_NUMBER);

    // Users
    mtmFlixAddUser(system, "Rachel", 22);
    mtmFlixAddUser(system, "Phoebe", 24);
    mtmFlixAddUser(system, "Monica", 30);
    mtmFlixAddUser(system, "Ross", 26);

    // Shows
    int ages[2] = {25, 120};
    mtmFlixAddSeries(system, "Friends", 1, COMEDY, NULL, 30);
    mtmFlixAddSeries(system, "21JumpStreet", 1, COMEDY, NULL, 30);
    mtmFlixAddSeries(system, "Community", 1, COMEDY, NULL, 25);
    mtmFlixAddSeries(system, "TheOffice", 1, COMEDY, NULL, 30);
    mtmFlixAddSeries(system, "Brooklyn99", 1, COMEDY, NULL, 30);
    mtmFlixAddSeries(system, "30Rock", 1, COMEDY, ages, 33);
    mtmFlixAddSeries(system, "DoctorWho", 1, SCIENCE_FICTION, NULL, 33);
    mtmFlixAddSeries(system, "Firefly", 1, SCIENCE_FICTION, NULL, 45);

    // Chandler
    mtmFlixSeriesJoin(system, "Chandler", "Friends");
    mtmFlixSeriesJoin(system, "Chandler", "21JumpStreet");
    mtmFlixSeriesJoin(system, "Chandler", "Community");
    mtmFlixSeriesJoin(system, "Chandler", "Firefly");
    mtmFlixAddFriend(system, "Chandler", "Rachel");
    mtmFlixAddFriend(system, "Chandler", "Phoebe");
    mtmFlixAddFriend(system, "Chandler", "Monica");

    // Rachel
    mtmFlixSeriesJoin(system, "Rachel", "TheOffice");

    // Phoebe
    mtmFlixSeriesJoin(system, "Phoebe", "TheOffice");

    // Ross
    mtmFlixSeriesJoin(system, "Ross", "30Rock");

    // Monica
    mtmFlixSeriesJoin(system, "Monica", "30Rock");

    // 1 series recommended, others not in liked genre or have no friend likes.
    fp = fopen("./mtmFlixGetRecommendations_test.out", "w");
    mtmFlixGetRecommendations(system, "Chandler", 0, fp);
    fclose(fp);
    const char* test1_valid = "Series 'TheOffice', Genre: COMEDY.\n";
    char* output = readFile("./mtmFlixGetRecommendations_test.out");
    ASSERT_TEST(strcmp(output, test1_valid) == 0);

    // 1 series recommended, 1 should be but not age appropriate
    mtmFlixAddFriend(system, "Chandler", "Ross");
    fp = fopen("./mtmFlixGetRecommendations_test.out", "w");
    mtmFlixGetRecommendations(system, "Chandler", 0, fp);
    fclose(fp);
    const char* test2_valid = "Series 'TheOffice', Genre: COMEDY.\n";
    output = readFile("./mtmFlixGetRecommendations_test.out");
    ASSERT_TEST(strcmp(output, test2_valid) == 0);

    // 2 series recommended, same ranks
    mtmFlixSeriesJoin(system, "Rachel", "DoctorWho");
    mtmFlixSeriesJoin(system, "Phoebe", "DoctorWho");
    fp = fopen("./mtmFlixGetRecommendations_test.out", "w");
    mtmFlixGetRecommendations(system, "Chandler", 0, fp);
    fclose(fp);
    const char* test3_valid = "Series 'DoctorWho', Genre: SCIENCE_FICTION.\n"
            "Series 'TheOffice', Genre: COMEDY.\n";
    output = readFile("./mtmFlixGetRecommendations_test.out");
    ASSERT_TEST(strcmp(output, test3_valid) == 0);

    // 2 series recommended, different ranks
    mtmFlixSeriesJoin(system, "Chandler", "Brooklyn99");
    fp = fopen("./mtmFlixGetRecommendations_test.out", "w");
    mtmFlixGetRecommendations(system, "Chandler", 0, fp);
    fclose(fp);
    const char* test4_valid = "Series 'TheOffice', Genre: COMEDY.\n"
            "Series 'DoctorWho', Genre: SCIENCE_FICTION.\n";
    output = readFile("./mtmFlixGetRecommendations_test.out");
    ASSERT_TEST(strcmp(output, test4_valid) == 0);

    // 2 series recommended, but limit is 1
    fp = fopen("./mtmFlixGetRecommendations_test.out", "w");
    mtmFlixGetRecommendations(system, "Chandler", 1, fp);
    fclose(fp);
    const char* test5_valid = "Series 'TheOffice', Genre: COMEDY.\n";
    output = readFile("./mtmFlixGetRecommendations_test.out");
    ASSERT_TEST(strcmp(output, test5_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}
*/
bool mtmFlixRemoveUserTestAdvanced() {
    MtmFlix system = mtmFlixCreate();
    mtmFlixAddUser(system, "Chandler", 23);
    mtmFlixAddUser(system, "Rachel", 22);
    mtmFlixAddUser(system, "Phoebe", 24);
    mtmFlixAddUser(system, "Shalev", 16);

    mtmFlixAddFriend(system, "Chandler", "Rachel");
    mtmFlixAddFriend(system, "Chandler", "Phoebe");
    mtmFlixAddFriend(system, "Rachel", "Chandler");
    mtmFlixAddFriend(system, "Rachel", "Phoebe");
    mtmFlixAddFriend(system, "Shalev", "Rachel");

    mtmFlixRemoveUser(system, "Rachel");

    FILE* fp = fopen("./mtmflixRemoveUser_testAdvanced.out", "w");
    mtmFlixReportUsers(system, fp);
    fclose(fp);

    const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Chandler is 23 years old\n"
            "Friend: Phoebe\n"
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Phoebe is 24 years old\n"
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Shalev is 16 years old\n";
    char* output = readFile("./mtmflixRemoveUser_testAdvanced.out");
    ASSERT_TEST(strcmp(output, test1_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

bool mtmFlixRemoveSeriesTestAdvanced() {
    MtmFlix system = mtmFlixCreate();
    mtmFlixAddUser(system, "Chandler", 23);
    mtmFlixAddUser(system, "Rachel", 22);

    mtmFlixAddSeries(system, "Friends", 1, COMEDY, NULL, 30);
    mtmFlixAddSeries(system, "21JumpStreet", 1, COMEDY, NULL, 30);
    mtmFlixAddSeries(system, "Community", 1, COMEDY, NULL, 25);
    mtmFlixAddSeries(system, "TheOffice", 1, COMEDY, NULL, 30);

    mtmFlixSeriesJoin(system, "Chandler", "Community");
    mtmFlixSeriesJoin(system, "Chandler", "TheOffice");
    mtmFlixSeriesJoin(system, "Rachel", "TheOffice");

    mtmFlixRemoveSeries(system, "TheOffice");

    FILE* fp = fopen("./mtmflixRemoveSeries_testAdvanced.out", "w");
    mtmFlixReportUsers(system, fp);
    fclose(fp);

    const char* test1_valid = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Chandler is 23 years old\n"
            "Series: Community\n"
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "The user Rachel is 22 years old\n";
    char* output = readFile("./mtmflixRemoveSeries_testAdvanced.out");
    ASSERT_TEST(strcmp(output, test1_valid) == 0);

    mtmFlixDestroy(system);
    return true;
}

char* readFile(char* path) {
    FILE* fp = fopen(path, "r");
    char* output = malloc(0);
    int ch = getc(fp), i = 1;
    while (ch != EOF) {
        output = realloc(output, i);
        *(output + i - 1) = ch;
        ch = getc(fp);
        i++;
    }
    output = realloc(output, i);
    *(output + i - 1) = '\0';
    fclose(fp);
    return output;
}

