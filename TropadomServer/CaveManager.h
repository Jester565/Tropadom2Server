#pragma once
#include <vector>

class PerlinManager;

class CaveManager
{
public:
	static const int MAX_CAVE_LENGTH = 399;
	static const int MIN_CAVE_LENGTH = 50;
	static const int CAVE_CREATE_X = 100;
	static const int CAVE_MAX_R = 9;
	CaveManager(int worldSeed, int caveMinY, int caveMaxY);

	bool isAir(int bX, int bY);

	std::vector <std::pair <int, int>> genCavePoints(int bX);

	~CaveManager();

private:
	PerlinManager* caveYNoise;
	PerlinManager* caveRNoise;
	int64_t worldSeed;
	int caveMinY;
	int caveMaxY;
};
