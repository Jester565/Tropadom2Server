#include "TropServer.h"
#include "TropClient.h"
#include "TropClientManager.h"
#include <UDPManager.h>
#include <ServicePool.h>
#include <PacketManager.h>

TropServer::TropServer(const boost::asio::ip::tcp& ipVersion)
	:ServerCPP(ipVersion)
{
}

void TropServer::createManagers()
{
	servicePool = boost::make_shared<ServicePool>();
	udpManager = boost::make_shared<UDPManager>(this);
	auto tropCM = boost::make_shared<TropClientManager>(udpManager);
	packetManager = boost::make_shared<PacketManager>(tropCM);
	tropCM->init(packetManager);
	clientManager = tropCM;
}

ClientPtr TropServer::createClient(boost::shared_ptr<TCPConnection> tcpConnection, IDType id)
{
	return boost::make_shared<TropClient>(id, tcpConnection, packetManager);
}

TropServer::~TropServer()
{
}
