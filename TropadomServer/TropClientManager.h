#pragma once
#include <ClientManagerCPP.h>
#include <PKeyOwner.h>
#include <MLScreenText.h>

class TerrainSection;
class TropClient;

class TropClientManager : public ClientManagerCPP, public PKeyOwner
{
public:
	static const int RANGE_OFF = 2;
	TropClientManager(boost::shared_ptr<UDPManager> udpManager);

	virtual void init(boost::shared_ptr<PacketManager> packetManager);

	virtual void TropClientManager::addClient(ClientPtr client) override;

	virtual bool removeClient(IDType id) override;

	std::vector<boost::shared_ptr<TropClient>> TropClientManager::getInRange(int64_t bX, int64_t bY, boost::shared_ptr<TropClient> exception = nullptr);

	void draw();

	void replaceTerrainSection(std::list <TerrainSection>::iterator searchTS, std::list <TerrainSection>::iterator replaceTS);

	~TropClientManager();

protected:
	AllegroExt::Graphics::MLScreenText clientInfo;
};
