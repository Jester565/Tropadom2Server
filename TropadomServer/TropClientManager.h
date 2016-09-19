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
	TropClientManager(Server* server);

	virtual Client* addClient(boost::shared_ptr <TCPConnection> tcpConnection);

	virtual bool removeClient(IDType id) override;

	std::vector <TropClient*> getInRange(int64_t bX, int64_t bY, TropClient* exception = nullptr);

	void draw();

	void replaceTerrainSection(std::list <TerrainSection>::iterator searchTS, std::list <TerrainSection>::iterator replaceTS);

	~TropClientManager();

protected:
	AllegroExt::Graphics::MLScreenText clientInfo;
};
