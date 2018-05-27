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
    if (!name1) return -1;
    if (!name2) return 1;
    return strcmp((char*)name1, (char*)name2);
}
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
    series->name = malloc(sizeof(char)*(strlen(name)+1));
    if(!series->name){
        free(series);
        return NULL;
    }
    strcpy(series->name, name);
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
    return series;
}
char* seriesGetName(void* series){
    if (!series) return NULL;
    return ((Series)series)->name;
}
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