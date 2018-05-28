#ifndef HW3_SERIES_H
#define HW3_SERIES_H
<<<<<<< HEAD

=======
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
#include "set.h"
#include "map.h"
#include "mtm_ex3.h"

typedef struct series* Series;

<<<<<<< HEAD
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

=======
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
>>>>>>> f73708eab1fcafc29b2f972be0ae51ec6485d052
#endif //HW3_SERIES_H