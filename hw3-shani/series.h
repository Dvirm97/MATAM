#ifndef HW3_SERIES_H
#define HW3_SERIES_H
#include "map.h"
#include "mtm_ex3.h"
#include "set.h"

typedef struct series* Series;

MapDataElement copySeries(MapDataElement src);
MapKeyElement seriesCopyName(MapKeyElement src);
void deleteSeries(MapDataElement user);
void deleteSeriesSet(SetElement series);
void seriesDeleteName(MapKeyElement name);
int seriesCompareNames(MapKeyElement name1, MapKeyElement name2);
int seriesSetCompareNames(SetElement name1, SetElement name2);
int seriesCompareNamesForSet(MapKeyElement series1, MapKeyElement series2);
int seriesCompareGenres(Genre genre1, Genre genre2);
Series createSeries(const char* name, int episodesNum,
                    Genre genre, int* ages, int episodesDuration);
int* seriesGetAges(Series series);
const char* seriesGetGenre(Series series);
char* seriesGetName(void* series);
const char* printSeries(Series series);
SetElement copySeriesSet(SetElement src);


#endif //HW3_SERIES_H
