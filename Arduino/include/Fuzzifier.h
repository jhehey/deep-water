#ifndef __FUZZIFIER_H__
#define __FUZZIFIER_H__

#include <Arduino.h>
#include "Level.h"

float getTriangularValue(float a, float b, float c, float x)
{
	return max(min((x-a)/(b-a), (c-x)/(c-b)), 0);
}

float getTrapezoidalValue(float a, float b, float c, float d, float x, float sensitivity = 0.1) 
{
  return max(min(min((x-a)/(b-a), 1), (d-x)/(d-c)), 0);
}

Level GetPHLevel(float x) {
	float low = getTrapezoidalValue(0, 0, 6, 6.5, x);
	float normal = getTriangularValue(6, 6.5, 7, x);
	float high = getTrapezoidalValue(6.5, 7, 14, 14, x);

	if(low >= normal && low >= high) return Level::Low;
	if(normal >= low && normal >= high) return Level::Normal;
	return Level::High;
}

Level GetAirTempLevel(float x) {
	float low = getTrapezoidalValue(0, 0, 24, 27, x);
	float normal = getTriangularValue(24, 27, 30, x);
	float high = getTrapezoidalValue(27, 30, 50, 50, x);

	if(low >= normal && low >= high) return Level::Low;
	if(normal >= low && normal >= high) return Level::Normal;
	return Level::High;
}

Level GetWaterTempLevel(float x) {
	float low = getTrapezoidalValue(0, 0, 18, 22, x);
	float normal = getTriangularValue(18, 22, 26, x);
	float high = getTrapezoidalValue(22, 26, 85, 85, x);

	if(low >= normal && low >= high) return Level::Low;
	if(normal >= low && normal >= high) return Level::Normal;
	return Level::High;
}

#endif
