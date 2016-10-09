#include "TropCore.h"
#include "TropServer.h"
#include "TropClientManager.h"
#include "Pinger.h"
#include "TerrainManager.h"
#include <TCPConnection.h>
#include <Button.h>

TropCore::TropCore()
	:AllegroExt::Core(""), serverOn(false)
{
	setFPSCap(30);
}

bool TropCore::init()
{
	if (Core::init())
	{
		mlst = new AllegroExt::Graphics::MLScreenText();
		newWorldST = new AllegroExt::Graphics::ScreenText();
		seedST = new AllegroExt::Graphics::ScreenText();
		saveFileField = new AllegroExt::Input::TextField();
		saveFileField->set(1000, 60);
		saveFileField->setText("Save Name");
		server = new TropServer(boost::asio::ip::tcp::v4());
		server->createManagers();
		pinger = new Pinger(server);
		terrainManager = new TerrainManager(server);
		return true;
	}
	return false;
}

void TropCore::draw()
{
	if (serverOn)
	{
		pinger->checkTimer();
		if (AllegroExt::Input::InputManager::keyPressed('p'))
		{
			((TropClientManager*)server->getClientManager())->draw();
		}
		if (AllegroExt::Input::InputManager::keyTyped('v'))
		{
			terrainManager->save("save1.trop");
		}
		seedST->drawCenteredText(seedStr, STANDARD_WIDTH / 2, STANDARD_HEIGHT / 2, 30, 0, 0, 0, 255);
	}
	else
	{
		if (AllegroExt::Input::Button::clickButton(STANDARD_WIDTH / 2 - 200, STANDARD_HEIGHT / 2 - 100, 400, 200, 0, 200, 0, 255))
		{
			uint64_t seed = 0;
			srand(time(NULL));
			for (int i = 0; i < 8; i++)
			{
				seed |= ((uint64_t)(rand() % 256)) << (i * 8);
			}
			if (terrainManager->init(seed))
			{
				server->run(SERVER_PORT);
				serverOn = true;
				seedStr = std::to_string(terrainManager->seed);
			}
		}
		newWorldST->drawCenteredText("New World", STANDARD_WIDTH / 2, STANDARD_HEIGHT / 2 - 25, 50, 0, 0, 0, 255);
		saveFileField->draw(500, 900);
		if (saveFileField->isEnterPressed())
		{
			std::string saveFileName = saveFileField->reset();
			if (saveFileName.size() > 0)
			{
				if (terrainManager->init(saveFileName))
				{
					server->run(SERVER_PORT);
					serverOn = true;
					seedStr = std::to_string(terrainManager->seed);
				}
			}
		}
	}
}


TropCore::~TropCore()
{
}
