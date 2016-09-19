#include "TropServer.h"
#include "TropClient.h"
#include "TropClientManager.h"
#include <ServicePool.h>
#include <PacketManager.h>

TropServer::TropServer(const boost::asio::ip::tcp& ipVersion)
	:ServerCPP(ipVersion)
{
}

void TropServer::createManagers()
{
	servicePool = new ServicePool();
	pm = new PacketManager(this);
	cm = new TropClientManager(this);
}

Client * TropServer::createClient(boost::shared_ptr<TCPConnection> tcpConnection, IDType id)
{
	return new TropClient(tcpConnection, this, id);
}

TropServer::~TropServer()
{
}
