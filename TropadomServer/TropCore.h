#pragma once
#include <Core.h>
#include <MLScreenText.h>
#include <TextField.h>

class TropServer;
class Pinger;
class TerrainManager;

static const int SERVER_PORT = 4065;

class TropCore : public AllegroExt::Core
{
public:
	TropCore();

	bool init() override;

	void draw() override;

	~TropCore();

private:
	TropServer* server;
	Pinger* pinger;
	TerrainManager* terrainManager;
	
	AllegroExt::Graphics::MLScreenText* mlst;
	AllegroExt::Graphics::ScreenText* newWorldST;
	AllegroExt::Graphics::ScreenText* seedST;
	AllegroExt::Input::TextField* saveFileField;
	std::string seedStr;
	bool serverOn;
};

