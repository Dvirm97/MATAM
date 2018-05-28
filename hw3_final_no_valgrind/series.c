<<<<<<< HEAD
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
    if (!series) return NULL;
    Series dst = malloc(sizeof(*dst));
    if (!dst) return NULL;

    Series src = (Series)series;
    dst->name = malloc(sizeof(char)*(strlen(src->name)+1));
    if(!dst->name){
        free(dst);
        return NULL;
    }
    strcpy(dst->name, src->name);
    dst->episodes_num = src->episodes_num;
    dst->genre = src->genre;
    if (!(src->ages)) {
        dst->ages = NULL;
    } else {
        dst->ages = malloc(sizeof(int)*2);
        if(!dst->ages){
            free(dst);
            free(dst->name);
            return NULL;
        }
        dst->ages[0] = src->ages[0];
        dst->ages[1] = src->ages[1];
    }
    dst->episode_duration = src->episode_duration;
    dst->points = src->points;
    return dst;
}
void seriesDestroy(void* series) {
    if (!series) return;
    free(((Series)series)->name);
    free(((Series)series)->ages);
    free(series);
}

void* seriesCopyName(void* src) {
    if(!src) return NULL;
    char* dst = malloc(strlen(src)+1);
    if(!dst) return NULL;
    strcpy(dst, src);
    return dst;
}
void seriesDestroyName(void* name) {
    free(name);
}
int seriesCompareNames(void* name1, void* name2) {
=======
#include <stdlib.h>
#include <string.h>
#include "series.h"
#include "set.h"
#include "mtm_ex3.h"

struct series {
    char* name;
    int episodesNum;
    Genre genre;
    int* ages;
    int episodeDuration;
};

MapDataElement copySeries(MapDataElement src) {
    if (!src) {
        return NULL;
    }
    Series dst = malloc(sizeof(*dst));
    if (!dst) {
        return NULL;
    }
    Series res = (Series) src; //doing this right?
    dst->name = malloc(strlen(res->name)+1);
    strcpy(dst->name, res->name);
    dst->episodesNum = res->episodesNum;
    dst->genre = res->genre;
    if (!(res->ages)) {
        dst->ages = NULL;
    }
    else {
        dst->ages = malloc(sizeof(int)*2);
        dst->ages[0] = res->ages[0];
        dst->ages[1] = res->ages[1];
    }
    dst->episodeDuration = res->episodeDuration;
    return dst;
}
SetElement copySeriesSet(SetElement src) {
    if (!src) {
        return NULL;
    }
    Series dst = malloc(sizeof(*dst));
    if (!dst) {
        return NULL;
    }
    Series res = (Series) src; //doing this right?
    dst->name = malloc(strlen(res->name)+1);
    strcpy(dst->name, res->name);
    dst->episodesNum = res->episodesNum;
    dst->genre = res->genre;
    if (!(res->ages)) {
        dst->ages = NULL;
    }
    else {
        dst->ages = malloc(sizeof(int)*2);
        dst->ages[0] = res->ages[0];
        dst->ages[1] = res->ages[1];
    }
    dst->episodeDuration = res->episodeDuration;
    return dst;
}
MapKeyElement seriesCopyName(MapKeyElement src) {
    char* dst = malloc(strlen(src)+1);
    strcpy(dst, src);
    return dst;
}
void deleteSeries(MapDataElement series) {
    if (!series) return;
    free(((Series)series)->name);
    free(series);
}
void deleteSeriesSet(SetElement series) {
    if(!series) return;
    free(((Series)series)->name);
    free(series);
}
void seriesDeleteName(MapKeyElement name) {
    free(name);
}
int seriesCompareNames(MapKeyElement name1, MapKeyElement name2) {
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
    if (!name1) return -1;
    if (!name2) return 1;
    return strcmp((char*)name1, (char*)name2);
}
<<<<<<< HEAD
int seriesCompareNamesForSet(SetElement series1, SetElement series2){
    return strcmp(((Series)series1)->name, ((Series)series2)->name);
}

Series seriesCreate(const char* name, int episodes_num,
                    Genre genre, int* ages, int episodes_duration) {
    if(!name)return NULL;
    Series series = malloc(sizeof(*series));
    if(!series)return NULL;
=======
int seriesSetCompareNames(SetElement series1, SetElement series2){
    return strcmp(((Series)series1)->name, ((Series)series2)->name);
}
/*int seriesCompareGenres(Genre genre1, Genre genre2){
    return strcmp(xstr(genre1), xstr(genre2));
}*/
Series createSeries(const char* name, int episodesNum,
                    Genre genre, int* ages, int episodesDuration) {
    if(!name)
        return NULL;
    Series series = malloc(sizeof(*series));
    if(!series)
        return NULL;
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
    series->name = malloc(sizeof(char)*(strlen(name)+1));
    if(!series->name){
        free(series);
        return NULL;
    }
    strcpy(series->name, name);
<<<<<<< HEAD
    series->episodes_num = episodes_num;
    series->genre = genre;
    series->points = 0;
    if (!ages) {
        series->ages = NULL;
    } else {
        series->ages = malloc(sizeof(int) * 2);
        if(!series->ages) return NULL;
        series->ages[0] = ages[0];
        series->ages[1] = ages[1];
    }
    series->episode_duration = episodes_duration;
=======
    series->episodesNum = episodesNum;
    series->genre = genre;
    if (!ages) {
        series->ages = NULL;
    }
    else {
        series->ages = malloc(sizeof(int) * 2);
    }
    if(series->ages){
        series->ages[0] = ages[0];
        series->ages[1] = ages[1];
    }
    series->episodeDuration = episodesDuration;
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
    return series;
}
char* seriesGetName(void* series){
    if (!series) return NULL;
    return ((Series)series)->name;
}
<<<<<<< HEAD
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


=======
/*char* seriesGetName2(Series series) {
    if (!series) return NULL;
    return series->name;
}*/
int* seriesGetAges(Series series) {
    return series->ages;
}

const char* printSeries(Series series) {
    const char* genres[] = { "SCIENCE_FICTION", "DRAMA", "COMEDY", "CRIME",
                             "MYSTERY", "DOCUMENTARY", "ROMANCE", "HORROR"};
    if(!series || !series->genre) return NULL;
    return mtmPrintSeries(series->name, genres[series->genre]);
}
const char* seriesGetGenre(Series series){
    const char* genres[] = { "SCIENCE_FICTION", "DRAMA", "COMEDY", "CRIME",
                             "MYSTERY", "DOCUMENTARY", "ROMANCE", "HORROR"};
    if(!series) return NULL;
    return genres[series->genre];
}
int seriesGetEpisodeDuration(Series series) {
    if (!series) return NULL;
    return series->episodeDuration;
}
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
