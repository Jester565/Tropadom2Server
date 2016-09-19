#pragma once
#include <ClientCPP.h>
#include <boost/thread/mutex.hpp>

class TerrainTracker;

class TropClient : public ClientCPP
{
public:
	TropClient(boost::shared_ptr<TCPConnection> tcpConnection, Server* server, IDType cID);

	uint16_t getPing()
	{
		pingMutex.lock();
		uint16_t pingCpy = ping;
		pingMutex.unlock();
		return pingCpy;
	}

	void setPing(uint16_t ping)
	{
		pingMutex.lock();
		this->ping = ping;
		pingMutex.unlock();
	}

	std::string getSummary()
	{
		std::string summary = "ID: ";
		summary += std::to_string(getID());
		summary += " PING: ";
		summary += std::to_string(getPing());
		return summary;
	}

	TerrainTracker* getTerrainTracker()
	{
		return terrainTracker;
	}

	~TropClient();

private:
	TerrainTracker* terrainTracker;
	boost::mutex pingMutex;
	uint16_t ping;
};

