#pragma once
#include <ServerCPP.h>

class TropServer : public ServerCPP
{
public:
	TropServer(const boost::asio::ip::tcp& ipVersion);

	void createManagers() override;

	ClientPtr createClient(boost::shared_ptr<TCPConnection> tcpConnection, IDType id);

	~TropServer();
};

