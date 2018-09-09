#include "DepositManager.h"
#include <random>

DepositManager::DepositManager(uint64_t seed, uint32_t minY, int depSize, int depDenom, int bDenom)
	:seed(seed), minY(minY), depSize(depSize), depDenom(depDenom), bDenom(bDenom)
{
}

bool DepositManager::isOre(int64_t bX, int64_t bY)
{
	if (bY > minY)
	{
		srand((int)(bY / depSize));
		int v1 = rand();
		srand((int)(bX / depSize));
		int v2 = rand();
		srand(seed - v1 * v2);
		if (rand() % depDenom < 1)
		{
			srand((int)(bX * depSize + bY));
			if (rand() % bDenom < 1)
			{
				return true;
			}
		}
	}
	return false;
}

DepositManager::~DepositManager()
{
}
