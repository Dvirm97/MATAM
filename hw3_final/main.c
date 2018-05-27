#include <stdio.h>
#include "mtmflix.h"
#include "user.h"

int main() {
    printf("Hello, World!\n");
    MtmFlix mtmflix = mtmFlixCreate();
    mtmFlixAddUser(mtmflix, "Dvir", 21);
    mtmFlixAddUser(mtmflix, "Mishu", 16);
    int ages[2] = {12, 120};
    mtmFlixAddSeries(mtmflix, "Westworld", 10, COMEDY, ages, 45);
    mtmFlixAddSeries(mtmflix, "How I Met Your Mother", 9, COMEDY, NULL, 45);
    mtmFlixSeriesJoin(mtmflix, "Dvir", "Westworld");
    mtmFlixAddFriend(mtmflix, "Dvir", "Mishu");
    mtmFlixSeriesJoin(mtmflix, "Mishu", "How I Met Your Mother");
    //mtmFlixRemoveFriend(mtmflix, "Dvir", "Mishu");
    //mtmFlixRemoveUser(mtmflix, "Mishu");
    //mtmFlixRemoveSeries(mtmflix, "Westworld");
    List friends = listCreate(userCopyName, userDeleteName);
    listInsertFirst(friends, "Mishu");
    listInsertFirst(friends, "Dvir");
    List series = listCreate(userCopyName, userDeleteName);
    listInsertFirst(series, "Westworld");
    FILE* outputStream = outputStream = fopen("recommendCheck", "w");
    mtmFlixGetRecommendations(mtmflix, "Dvir", 0, outputStream);
    fclose(outputStream);
    //const char* a = mtmPrintUser("Dvir", 13, friends, series);
    //printf("%s", a);
    mtmFlixDestroy(mtmflix);
    return 0;
}