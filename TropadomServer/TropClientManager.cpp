#include "TropClientManager.h"
#include "Packets/Trop.pb.h"
#include "TropClient.h"
#include "TerrainManager.h"
#include <OPacket.h>
#include <Server.h>
#include <boost/thread.hpp>

TropClientManager::TropClientManager(Server* server)
	:ClientManagerCPP(server), PKeyOwner(server->getPacketManager())
{
	
}

Client * TropClientManager::addClient(boost::shared_ptr<TCPConnection> tcpConnection)
{
	Client* client = ClientManager::addClient(tcpConnection);
	if (client != nullptr)
	{
		boost::shared_ptr <OPacket> opB2(new OPacket("B2", 0));
		TropPackets::PackB2 packB2;
		packB2.set_id(client->getID());
		opB2->setData(boost::make_shared <std::string>(packB2.SerializeAsString()));
		send(opB2, client);
	}
	return client;
}

bool TropClientManager::removeClient(IDType id)
{
	bool success = ClientManager::removeClient(id);
	if (success)
	{
		boost::shared_ptr <OPacket> opB1(new OPacket("B1", id));
		TropPackets::PackB1 packB1;
		packB1.set_id(id);
		opB1->setData(boost::make_shared <std::string>(packB1.SerializeAsString()));
		sendToAll(opB1); 
	}
}

std::vector<TropClient*> TropClientManager::getInRange(int64_t bX, int64_t bY, TropClient* exception)
{
	std::vector <TropClient*> clientsInRange;
	boost::shared_lock <boost::shared_mutex> lock(clientMapMutex);
	for (auto it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second != exception)
		{
			TropClient* tropClient = (TropClient*)it->second;
			tropClient->getTerrainTracker()->posMutex.lock();
			int64_t lowBX = tropClient->getTerrainTracker()->bcIterLow->bX - RANGE_OFF;
			int64_t highBX = tropClient->getTerrainTracker()->bcIterHigh->bX + RANGE_OFF;
			if (bX >= lowBX && bX <= highBX)
			{
				int64_t lowBY = tropClient->getTerrainTracker()->rowILow - RANGE_OFF;
				int64_t highBY = tropClient->getTerrainTracker()->rowIHigh + RANGE_OFF;
				if (bY >= lowBY && bY <= highBY)
				{
					clientsInRange.push_back(tropClient);
				}
			}
			tropClient->getTerrainTracker()->posMutex.unlock();
		}
	}
	return clientsInRange;
}

void TropClientManager::draw()
{
	boost::shared_lock <boost::shared_mutex> lock(clientMapMutex);
	std::string total = "Clients\n";
	for (auto it = clients.begin(); it != clients.end(); it++)
	{
		total += ((TropClient*)it->second)->getSummary();
		total += "\n\n";
	}
	clientInfo.drawText(total, 10, 10, 50, 0, 0, 0, 255);
}

void TropClientManager::replaceTerrainSection(std::list <TerrainSection>::iterator searchTS, std::list <TerrainSection>::iterator replaceTS)
{
	boost::shared_lock <boost::shared_mutex> lock(clientMapMutex);
	for (auto it = clients.begin(); it != clients.end(); it++)
	{
		TerrainTracker* terTrack = ((TropClient*)it->second)->getTerrainTracker();
		//write lock terTrack->tsIter
		terTrack->posMutex.lock();
		if (terTrack->tsIter == searchTS)
		{
			terTrack->tsIter = replaceTS;
		}
		terTrack->posMutex.unlock();
	}
}

TropClientManager::~TropClientManager()
{
}
