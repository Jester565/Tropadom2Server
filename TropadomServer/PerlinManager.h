#pragma once
#include <stdint.h>
#include <math.h>
#include <random>

class PerlinManager
{
public:
	static const int FREQ_MAX_DEFAULT = 200;
	static const int FREQ_MIN_DEFAULT = 4;
	static const int FREQ_DIV_DEFAULT = 2;
	static const int RANGE_DIV_DEFAULT = 2;
	PerlinManager(int64_t seed, int32_t freqMax = FREQ_MAX_DEFAULT, int32_t freqMin = FREQ_MIN_DEFAULT, int32_t freqDiv = FREQ_DIV_DEFAULT, int32_t rangeDiv = RANGE_DIV_DEFAULT);

	int getPerlinVal(int bX, int range, int minY);

	int getNoise(int bX, int range);

	void setSeed(int64_t seed)
	{
		this->seed = seed;
	}

	~PerlinManager();

private:
	double genPerlinNoise(int bX, int freq, int range);

	int genPseudoRand(int bX, int range)
	{
		srand(seed + bX);
		return (rand() % range);
	}
	double cubicInterpolate(int bY0, int bY1, int bY2, int bY3, double betweenPercent)
	{
		double a0 = bY3 - bY2 - bY0 + bY1;
		double a1 = bY0 - bY1 - a0;
		double a2 = bY2 - bY0;
		double a3 = bY1;
		return (a0 * pow(betweenPercent, 3) + a1 * pow(betweenPercent, 2) + a2 * betweenPercent + a3);
	}
	int32_t freqMax;
	int32_t freqMin;
	int32_t freqDiv;
	int32_t rangeDiv;
	int64_t seed;
};
