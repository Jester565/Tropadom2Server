#include "CaveManager.h"
#include "PerlinManager.h"


CaveManager::CaveManager(int worldSeed, int caveMinY, int caveMaxY)
	:worldSeed(worldSeed), caveMinY(caveMinY), caveMaxY(caveMaxY)
{
	caveYNoise = new PerlinManager(0);
	caveRNoise = new PerlinManager(0, 20, 2, 2, 1.3);
}

bool CaveManager::isAir(int bX, int bY)
{
	for (int i = 0; i < MAX_CAVE_LENGTH / CAVE_CREATE_X; i++)
	{
		int caveBX = bX - bX % CAVE_CREATE_X - CAVE_CREATE_X * i;
		if (bX < 0)
		{
			caveBX = bX - (CAVE_CREATE_X + bX % CAVE_CREATE_X) - CAVE_CREATE_X * i;
		}
		int64_t caveSeed = (int)((worldSeed * 2.0) / (caveBX + .75));
		srand(caveSeed * 3);
		int caveLength = rand() % (MAX_CAVE_LENGTH - MIN_CAVE_LENGTH) + MIN_CAVE_LENGTH;
		if (bX - caveBX > caveLength + CAVE_MAX_R)
		{
			continue;
		}
		caveYNoise->setSeed(caveSeed);
		caveRNoise->setSeed(caveSeed * 1.78);
		for (int j = bX - caveBX - CAVE_MAX_R; j <= bX - caveBX + CAVE_MAX_R; j++)
		{
			if (j > caveLength)
			{
				break;
			}
			if (j < 0)
			{
				continue;
			}
			int cPerlinY1 = caveYNoise->getPerlinVal(j, caveMaxY - caveMinY, caveMinY);
			int cPerlinY2 = caveYNoise->getPerlinVal(j - 1, caveMaxY - caveMinY, caveMinY);
			int cPerlinR1 = caveRNoise->getPerlinVal(j + cPerlinY1, CAVE_MAX_R, 0);
			int cPerlinR2 = caveRNoise->getPerlinVal(j - 1 + cPerlinY2, CAVE_MAX_R, 0);
			if (cPerlinY1 < cPerlinY2)
			{
				if (bY >= cPerlinY1 - cPerlinR1 && bY <= cPerlinY2 + cPerlinR2)
				{
					if (j == bX - caveBX)
					{
						return true;
					}
					else
					{
						for (int k = cPerlinY1; k <= cPerlinY2; k++)
						{
							int rad = caveRNoise->getPerlinVal(j + k, CAVE_MAX_R, 0);
							float dis = sqrt(pow(j - (bX - caveBX), 2) + pow(k - bY, 2));
							if (dis < rad)
							{
								return true;
							}
						}
					}
				}
			}
			else
			{
				if (bY >= cPerlinY2 - cPerlinR2 && bY <= cPerlinY1 + cPerlinR1)
				{
					if (j == 0)
					{
						return true;
					}
					else
					{
						for (int k = cPerlinY2; k <= cPerlinY1; k++)
						{
							int rad = caveRNoise->getPerlinVal(j + k, CAVE_MAX_R, 0);
							float dis = sqrt(pow(j - (bX - caveBX), 2) + pow(k - bY, 2));
							if (dis < rad)
							{
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

std::vector<std::pair<int, int>> CaveManager::genCavePoints(int bX)
{
	std::vector<std::pair<int, int>> cavePoints;
	for (int i = 0; i < MAX_CAVE_LENGTH / CAVE_CREATE_X; i++)
	{
		int caveBX = bX - bX % CAVE_CREATE_X - CAVE_CREATE_X * i;
		if (bX < 0)
		{
			caveBX = bX - (CAVE_CREATE_X + bX % CAVE_CREATE_X) - CAVE_CREATE_X * i;
		}
		int64_t caveSeed = (int)((worldSeed * 2.0) / (caveBX + .75));
		srand(caveSeed);
		int caveLength = rand() % (MAX_CAVE_LENGTH - MIN_CAVE_LENGTH) + MIN_CAVE_LENGTH;
		if (bX - caveBX > caveLength + CAVE_MAX_R)
		{
			continue;
		}
		caveYNoise->setSeed(caveSeed);
		caveRNoise->setSeed(caveSeed * 1.78);
		/*
		int cPerlinY1 = caveYNoise->getPerlinVal(bX, caveMaxY - caveMinY, caveMinY);
		int cPerlinY2 = caveYNoise->getPerlinVal(bX - 1, caveMaxY - caveMinY, caveMinY);
		int cPerlinR1 = caveRNoise->getPerlinVal(bX + cPerlinY1, CAVE_MAX_R, 0);
		int cPerlinR2 = caveRNoise->getPerlinVal(bX - 1 + cPerlinY2, CAVE_MAX_R, 0);
		if (cPerlinY1 < cPerlinY2)
		{
			cavePoints.emplace_back(cPerlinY1 - cPerlinR1, cPerlinY2 + cPerlinR2);
		}
		else
		{
			cavePoints.emplace_back(cPerlinY2 - cPerlinR2, cPerlinY1 + cPerlinR1);
		}
		*/
		for (int j = -CAVE_MAX_R; j <= CAVE_MAX_R; j++)
		{
			int cPerlinY1 = caveYNoise->getPerlinVal(bX + j, caveMaxY - caveMinY, caveMinY);
			int cPerlinY2 = caveYNoise->getPerlinVal(bX + j - 1, caveMaxY - caveMinY, caveMinY);
			int cPerlinR1 = caveRNoise->getPerlinVal(bX + j + cPerlinY1, CAVE_MAX_R, 0);
			int colR = cPerlinR1 - abs(j);
			if (colR > 0)
			{
				if (cPerlinY1 < cPerlinY2)
				{
					cavePoints.emplace_back(cPerlinY1 - colR, cPerlinY2 + colR);
				}
				else
				{
					cavePoints.emplace_back(cPerlinY2 - colR, cPerlinY1 + colR);
				}
			}
		}
		/*
		for (int j = bX - caveBX - CAVE_MAX_R; j <= bX - caveBX + CAVE_MAX_R; j++)
		{
			if (j > caveLength)
			{
				break;
			}
			if (j < 0)
			{
				continue;
			}
			int cPerlinY1 = caveYNoise->getPerlinVal(j, caveMaxY - caveMinY, caveMinY);
			int cPerlinY2 = caveYNoise->getPerlinVal(j - 1, caveMaxY - caveMinY, caveMinY);
			int cPerlinR1 = caveRNoise->getPerlinVal(j + cPerlinY1, CAVE_MAX_R, 0);
			int cPerlinR2 = caveRNoise->getPerlinVal(j - 1 + cPerlinY2, CAVE_MAX_R, 0);
			if (cPerlinY1 < cPerlinY2)
			{
				if (bY >= cPerlinY1 - cPerlinR1 && bY <= cPerlinY2 + cPerlinR2)
				{
					if (j == bX - caveBX)
					{
						return true;
					}
					else
					{
						for (int k = cPerlinY1; k <= cPerlinY2; k++)
						{
							int rad = caveRNoise->getPerlinVal(j + k, CAVE_MAX_R, 0);
							float dis = sqrt(pow(j - (bX - caveBX), 2) + pow(k - bY, 2));
							if (dis < rad)
							{
								return true;
							}
						}
					}
				}
			}
			else
			{
				if (bY >= cPerlinY2 - cPerlinR2 && bY <= cPerlinY1 + cPerlinR1)
				{
					if (j == 0)
					{
						return true;
					}
					else
					{
						for (int k = cPerlinY2; k <= cPerlinY1; k++)
						{
							int rad = caveRNoise->getPerlinVal(j + k, CAVE_MAX_R, 0);
							float dis = sqrt(pow(j - (bX - caveBX), 2) + pow(k - bY, 2));
							if (dis < rad)
							{
								return true;
							}
						}
					}
				}
			}
		}
		*/
	}
	return cavePoints;
}

CaveManager::~CaveManager()
{
}
