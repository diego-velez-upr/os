#ifndef INCLUDE_FUNCTIONS_H_
#define INCLUDE_FUNCTIONS_H_

#define MIN_WIND_SPEED 74
#define MAX_SPEED_CAT_1 95
#define MAX_SPEED_CAT_2 110
#define MAX_SPEED_CAT_3 129
#define MAX_SPEED_CAT_4 156
#define MAX_SPEED_CAT_5 256

struct Hurricane {
  int category;
  double latitude;
  double longitude;
  int wind_speeds[100];
};

struct Hurricane CreateHurricane(int category, double latitude,
                                 double longitude);
void FillWindSpeeds(struct Hurricane *hurricane);

#endif  // INCLUDE_FUNCTIONS_H_
