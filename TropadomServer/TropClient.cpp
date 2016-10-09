#include "TropClient.h"
#include "TerrainManager.h"

TropClient::TropClient(boost::shared_ptr<TCPConnection> tcpConnection, Server* server, IDType cID)
	:ClientCPP(tcpConnection, server, cID)
{
	terrainTracker = new TerrainTracker(); 
}


TropClient::~TropClient()
{
	delete terrainTracker;
	terrainTracker = nullptr;
}
