#include <stdio.h>
#include <stdlib.h>

#include "../include/functions.h"

int main(void) {
  int category;
  double latitude, longitude;
  scanf("%d %lf %lf", &category, &latitude, &longitude);

  int category_is_valid = category >= 1 && category <= 5;
  if (!category_is_valid) {
    return 1;
  }

  struct Hurricane h = CreateHurricane(category, latitude, longitude);
  FillWindSpeeds(&h);

  printf("Category: %d\n", h.category);
  printf("Coordinates: %.1lf, %.1lf\n", h.latitude, h.longitude);

  printf("Wind Speeds (mph):");
  for (int i = 0; i < 100; i++) {
    printf(" %d", h.wind_speeds[i]);
  }
  printf("\n");

  return 0;
}
