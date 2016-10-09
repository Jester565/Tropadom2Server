#pragma once
#include <stdint.h>

class DepositManager
{
public:
	DepositManager(uint64_t seed, uint32_t minY, int depSize, int depDenom, int bDenom);

	bool isOre(int64_t bX, int64_t bY);

	~DepositManager();

private:
	uint64_t seed;
	uint32_t minY;
	int depDenom;
	int bDenom;
	int depSize;
};

