#ifndef HW3_SERIES_H
#define HW3_SERIES_H
#include "set.h"
#include "map.h"
#include "mtm_ex3.h"

typedef struct series* Series;

MapDataElement copySeries(MapDataElement src);
SetElement copySeriesSet(SetElement src);
MapKeyElement seriesCopyName(MapKeyElement src);
void deleteSeries(MapDataElement user);
void deleteSeriesSet(SetElement series);
void seriesDeleteName(MapKeyElement name);
int seriesCompareNames(MapKeyElement name1, MapKeyElement name2);
int seriesSetCompareNames(SetElement series1, SetElement series2);
int seriesCompareGenres(Genre genre1, Genre genre2);
Series createSeries(const char* name, int episodesNum,
                    Genre genre, int* ages, int episodesDuration);
char* seriesGetName(void* series);
int* seriesGetAges(Series series);
const char* printSeries(Series series);
const char* seriesGetGenre(Series series);
int seriesGetEpisodeDuration(Series series);
/*const char* genres[] = { "SCIENCE_FICTION", "DRAMA", "COMEDY", "CRIME",
                           "MYSTERY", "DOCUMENTARY", "ROMANCE", "HORROR"};
 */
#endif //HW3_SERIES_H