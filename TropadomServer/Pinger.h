#pragma once
#include <PKeyOwner.h>
#include <boost/shared_ptr.hpp>

class IPacket;
class Server;
class ClientManager;

class Pinger : public PKeyOwner
{
public:
	static const int MAX_PING = 1000000;

	static const int PING_UPDATE_TIME = 10000;

	Pinger(Server* server);

	void checkTimer();

	~Pinger();

private:
	void updatePing();

	void keyA0(boost::shared_ptr<IPacket> iPack);

	int64_t lastUpdateTime;

	boost::shared_ptr<ClientManager> cm;
};
