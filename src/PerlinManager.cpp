#include "PerlinManager.h"

PerlinManager::PerlinManager(int64_t seed, int32_t freqMax, int32_t freqMin, int32_t freqDiv, int32_t rangeDiv)
	:seed(seed), freqMax(freqMax), freqMin(freqMin), freqDiv(freqDiv), rangeDiv(rangeDiv)
{
}

int PerlinManager::getPerlinVal(int bX, int range, int minY)
{
	int solidBY = getNoise(bX, range) + minY;
	return solidBY;
}

int PerlinManager::getNoise(int bX, int range)
{
	int iRange = range;
	int freq = freqMax;
	int maxRange = 0;
	double noiseBY = 0;
	while (freq >= freqMin && range >= 1)
	{
		noiseBY += genPerlinNoise(bX, freq, range);
		freq /= freqDiv;
		range /= rangeDiv;
		maxRange += range;
	}
	noiseBY *= ((double)iRange / (double)maxRange);
	return (int)noiseBY;
}


PerlinManager::~PerlinManager()
{
}

double PerlinManager::genPerlinNoise(int bX, int freq, int range)
{
	int bXFreqFit = bX - (bX%freq);
	double betweenPercent = (bX%freq) / (double)freq;
	if (bX < 0)
	{
		bXFreqFit -= freq;
		betweenPercent = (freq + (bX%freq)) / (double)freq;
	}
	int bY0 = genPseudoRand(bXFreqFit - freq, range);
	int bY1 = genPseudoRand(bXFreqFit, range);
	int bY2 = genPseudoRand(bXFreqFit + freq, range);
	int bY3 = genPseudoRand(bXFreqFit + freq * 2, range);
	return cubicInterpolate(bY0, bY1, bY2, bY3, betweenPercent);
}
