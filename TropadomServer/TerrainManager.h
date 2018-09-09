#pragma once
#include <PKeyOwner.h>
#include <vector>
#include <list>
#include <boost/thread.hpp>
#include <unordered_map>

class TropServer;
class CaveManager;
class PerlinManager;
class DepositManager;

const static int COL_HEIGHT = 600;
const static int LOAD_COL_W = 200;
const static int LOAD_COL_H = 100;

static const std::unordered_map <uint16_t, bool> TransparentTypes{ {0, true}, {1, false}, {2, false}, {3, false}, {4, false} };

class WorldGenerator
{
public:
	explicit WorldGenerator(int64_t seed);
	PerlinManager* groundPerlinManager;
	PerlinManager* dirtPerlinManager;
	CaveManager* caveManager;
	DepositManager* ironManager;

	~WorldGenerator();
};

class BlockColumn
{
public:
	BlockColumn(int64_t bX, uint32_t groundY);

	BlockColumn(WorldGenerator* worldGen, int64_t bX);

	std::vector <uint16_t> blocks;

	int64_t bX;

	uint32_t groundY;

	void setBlock(uint32_t bY, uint16_t type, bool* groundHChanged);

	~BlockColumn();

	boost::shared_mutex blocksMutex;
};

class TerrainSection
{
public:
	TerrainSection();

	TerrainSection(WorldGenerator* worldGen, int64_t bX);

	std::list <BlockColumn> blockColumns;

	~TerrainSection();

	boost::shared_mutex blockColumnsMutex;
};

struct TerrainTracker
{
	std::list <TerrainSection>::iterator tsIter;
	std::list <BlockColumn>::iterator bcIterLow;
	std::list <BlockColumn>::iterator bcIterHigh;
	int16_t rowILow;
	int16_t rowIHigh;
	boost::recursive_mutex posMutex;
};

class TerrainManager : public PKeyOwner
{
public:
	TerrainManager(TropServer* server);

	bool init(int64_t seed);

	bool init(const std::string& saveFileName);
	
	void merge(std::list <TerrainSection>::iterator iter1, std::list <TerrainSection>::iterator iter2);

	void shiftLeft(TerrainTracker* terTrack);

	void shiftRight(TerrainTracker* terTrack);

	void teleLoad(int64_t bX, TerrainTracker* terTrack);

	bool save(const std::string& saveFileName);

	bool load(const std::string& saveFileName);

	std::list <TerrainSection> terrainSections;

	int c2RecieveCount;

	int c2HorizontalCount;

	uint64_t seed;

	~TerrainManager();

private:
	bool init();

	void keyC0(boost::shared_ptr<IPacket> iPack);

	void keyC2(boost::shared_ptr<IPacket> iPack);

	void keyD0(boost::shared_ptr<IPacket> iPack);

	void keyG0(boost::shared_ptr<IPacket> iPack);

	boost::shared_mutex terrainSectionsMutex;

	WorldGenerator* worldGenerator;
	TropServer* tropServer;
};
