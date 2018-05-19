#ifndef HW3_SERIES_H
#define HW3_SERIES_H
#include "map.h"
#include "mtm_ex3.h"

typedef struct series* Series;

MapDataElement copySeries(MapDataElement src);
MapKeyElement seriesCopyName(MapKeyElement src);
void deleteSeries(MapDataElement user);
void seriesDeleteName(MapKeyElement name);
int seriesCompareNames(MapKeyElement name1, MapKeyElement name2);
<<<<<<< HEAD
int seriesCompareGenres(Genre genre1, Genre genre2);
Series createSeries(const char* name, int episodesNum,
                    Genre genre, int* ages, int episodesDuration);
int* seriesGetAges(Series series);
const char* printSeries(const char* series_name, Series series);
const char* seriesGetGenre(Series series);
=======
Series createSeries(const char* name, int episodesNum,
                    Genre genre, int* ages, int episodesDuration);
int* seriesGetAges(Series series);
>>>>>>> ea91432b0dba9ca5736898feb769fe2aa11ee002
/*const char* genres[] = { "SCIENCE_FICTION", "DRAMA", "COMEDY", "CRIME",
                           "MYSTERY", "DOCUMENTARY", "ROMANCE", "HORROR"};
 */
#endif //HW3_SERIES_H
