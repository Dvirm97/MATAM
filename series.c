#include "series.h"

#include <stdlib.h>
#include <string.h>

struct series {
    char* name;
    int episodes_num;
    Genre genre;
    int* ages;
    int episode_duration;
    int points;
};

void* seriesCopy(void* series) {
    // Check input
    if (!series) return NULL;
    Series original_series = (Series)series;

    // Create new series
    Series copied_series = malloc(sizeof(*copied_series));
    if (!copied_series) return NULL;

    // Copy series name
    copied_series->name = malloc(sizeof(char)*(strlen(original_series->name)+1));
    if(!copied_series->name){
        free(copied_series);
        return NULL;
    }
    strcpy(copied_series->name, original_series->name);

    // Copy series episodes numbers, genre, episode duration and points
    copied_series->episodes_num = original_series->episodes_num;
    copied_series->genre = original_series->genre;
    copied_series->episode_duration = original_series->episode_duration;
    copied_series->points = original_series->points;

    // Copy series ages limit if there is one
    if (!(original_series->ages)) {
        copied_series->ages = NULL;
    } else {
        copied_series->ages = malloc(sizeof(int)*2);
        if(!copied_series->ages){
            free(copied_series);
            free(copied_series->name);
            return NULL;
        }
        copied_series->ages[0] = original_series->ages[0];
        copied_series->ages[1] = original_series->ages[1];
    }

    return copied_series;
}
void seriesDestroy(void* series) {
    if (!series) return;
    free(((Series)series)->name);
    free(((Series)series)->ages);
    free(series);
}

void* seriesCopyName(void* name) {
    if(!name) return NULL;
    char* copied_name = malloc(strlen(name)+1);
    if(!copied_name) return NULL;
    strcpy(copied_name, name);
    return copied_name;
}
void seriesDestroyName(void* name) {
    free(name);
}
int seriesCompareNames(void* name1, void* name2) {
    if (!name1) return -1;
    if (!name2) return 1;
    return strcmp((char*)name1, (char*)name2);
}
int seriesCompareNamesForSet(SetElement series1, SetElement series2){
    return strcmp(((Series)series1)->name, ((Series)series2)->name);
}

Series seriesCreate(const char* name, int episodes_num,
                    Genre genre, int* ages, int episodes_duration) {
    // Check input
    if(!name)return NULL;

    // Allocate memory
    Series series = malloc(sizeof(*series));
    if(!series)return NULL;

    // Insert name
    series->name = malloc(sizeof(char)*(strlen(name)+1));
    if(!series->name){
        free(series);
        return NULL;
    }
    strcpy(series->name, name);

    // Insert episodes_num, genre, episodes_duration
    series->episodes_num = episodes_num;
    series->genre = genre;
    series->episode_duration = episodes_duration;

    series->points = 0; // Initialize points

    // Insert ages limit if there is one
    if (!ages) {
        series->ages = NULL;
    } else {
        series->ages = malloc(sizeof(int) * 2);
        if(!series->ages) return NULL;
        series->ages[0] = ages[0];
        series->ages[1] = ages[1];
    }

    return series;
}
char* seriesGetName(void* series){
    if (!series) return NULL;
    return ((Series)series)->name;
}
int* seriesGetAges(Series series) {
    return series->ages;
}
int seriesGetEpisodeDuration(Series series) {
    if (!series) return 0;
    return series->episode_duration;
}
const char* seriesGetGenre(Series series){
    const char* genres[] = { "SCIENCE_FICTION", "DRAMA", "COMEDY", "CRIME",
                             "MYSTERY", "DOCUMENTARY", "ROMANCE", "HORROR"};
    if(!series) return NULL;
    return genres[series->genre];
}
int seriesGetPoints(Series series){
    if(!series) return 0;
    return series->points;
}
void seriesSetPoints(Series series, int points){
    if(!series) return;
    series->points = points;
}
const char* seriesPrint(Series series) {
    const char* genres[] = { "SCIENCE_FICTION", "DRAMA", "COMEDY", "CRIME",
                             "MYSTERY", "DOCUMENTARY", "ROMANCE", "HORROR"};
    if(!series) return NULL;
    return mtmPrintSeries(series->name, genres[series->genre]);
}


