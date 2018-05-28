#ifndef HW3_SERIES_H
#define HW3_SERIES_H

#include "set.h"
#include "map.h"
#include "mtm_ex3.h"

typedef struct series* Series;

void* seriesCopy(void* series);
void seriesDestroy(void* series);

void* seriesCopyName(void* src);
void seriesDestroyName(void* name);
int seriesCompareNames(void* name1, void* name2);
int seriesCompareNamesForSet(SetElement series1, SetElement series2);
Series seriesCreate(const char* name, int episodes_num,
                    Genre genre, int* ages, int episodes_duration);
char* seriesGetName(void* series);
int* seriesGetAges(Series series);
int seriesGetEpisodeDuration(Series series);
const char* seriesGetGenre(Series series);
int seriesGetPoints(Series series);
void seriesSetPoints(Series series, int points);
const char* seriesPrint(Series series);

#endif //HW3_SERIES_H