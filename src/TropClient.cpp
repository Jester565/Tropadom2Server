#include "TropClient.h"
#include "TerrainManager.h"

TropClient::TropClient(IDType cID, boost::shared_ptr<TCPConnection> tcpConnection, boost::shared_ptr<PacketManager> packetManager, ClientDisconnectHandler handler)
	:ClientCPP(cID, tcpConnection, packetManager, handler)
{
	terrainTracker = new TerrainTracker(); 
}


TropClient::~TropClient()
{
	delete terrainTracker;
	terrainTracker = nullptr;
}
