#include "../include/functions.h"

#include <stdint.h>
#include <stdlib.h>

struct Hurricane CreateHurricane(int category, double latitude,
                                 double longitude) {
  struct Hurricane h = {.category = category,
                        .latitude = latitude,
                        .longitude = longitude,
                        .wind_speeds = {0}};
  return h;
}

void FillWindSpeeds(struct Hurricane *hurricane) {
  for (int i = 0; i < 100; i++) {
    int wind_speed;
    switch (hurricane->category) {
      case 1:
        wind_speed =
            rand() % (MAX_SPEED_CAT_1 - MIN_WIND_SPEED + 1) + MIN_WIND_SPEED;
        break;
      case 2:
        wind_speed =
            rand() % (MAX_SPEED_CAT_2 - MIN_WIND_SPEED + 1) + MIN_WIND_SPEED;
        break;
      case 3:
        wind_speed =
            rand() % (MAX_SPEED_CAT_3 - MIN_WIND_SPEED + 1) + MIN_WIND_SPEED;
        break;
      case 4:
        wind_speed =
            rand() % (MAX_SPEED_CAT_4 - MIN_WIND_SPEED + 1) + MIN_WIND_SPEED;
        break;
      case 5:
        wind_speed =
            rand() % (MAX_SPEED_CAT_5 - MIN_WIND_SPEED + 1) + MIN_WIND_SPEED;
        break;
    }
    hurricane->wind_speeds[i] = wind_speed;
  }
}
