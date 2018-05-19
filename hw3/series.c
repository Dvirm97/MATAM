#include <stdlib.h>
#include <string.h>
#include "series.h"
#include "mtm_ex3.h"
#define str(x) #x
#define xstr(x) str(x)

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
    strcpy(dst->name, res->name);//dunno if need another malloc for this
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
void deleteSeries(MapDataElement series) { //Do it better
    free(series);
}
void seriesDeleteName(MapKeyElement name) {
    free(name);
}
int seriesCompareNames(MapKeyElement name1, MapKeyElement name2){
    return strcmp((char*)name1, (char*)name2);
}
int seriesCompareNamesForSet(MapKeyElement series1, MapKeyElement series2) {
    return strcmp(((Series)series1)->name, ((Series)series2)->name);
}
int seriesCompareGenres(Genre genre1, Genre genre2){
    return strcmp(xstr(genre1), xstr(genre2));
}
Series createSeries(const char* name, int episodesNum,
                               Genre genre, int* ages, int episodesDuration) {
    Series series = malloc(sizeof(series));
    strcpy(series->name, name);
    series->episodesNum = episodesNum;
    series->genre = genre;
    if (!ages) {
        series->ages = NULL;
    }
    else {
        series->ages = malloc(sizeof(int)*2);
        series->ages[0] = ages[0];
        series->ages[1] = ages[1];
    }
    series->episodeDuration = episodesDuration;
    return series;
}
int* seriesGetAges(Series series) {
    return series->ages;
}

const char* printSeries(const char* series_name, Series series) {
    if(!series) return series_name;
    return mtmPrintSeries(series->name, xstr(series->genre));
}
const char* seriesGetGenre(Series series){
    if(!series) return NULL;
    return xstr(series->genre);
}
