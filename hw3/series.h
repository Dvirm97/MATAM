
#ifndef HW3_SERIES_H
#define HW3_SERIES_H
#include "map.h"

typedef struct series* Series;

MapDataElement copySeries(MapDataElement src);
MapKeyElement seriesCopyName(MapKeyElement src);
void deleteSeries(MapDataElement user);
void seriesDeleteName(MapKeyElement name);
int seriesCompareNames(MapKeyElement name1, MapKeyElement name2);

#endif //HW3_SERIES_H
