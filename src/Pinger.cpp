#include "Pinger.h"
#include "TropClient.h"
#include "Trop.pb.h"
#include <IPacket.h>
#include <OPacket.h>
#include <Server.h>
#include <PacketManager.h>
#include <ClientManager.h>
#include <chrono>

Pinger::Pinger(Server* server)
	:PKeyOwner(), cm(server->getClientManager())
{
	PKeyOwner::attach(server->getPacketManager());
	addKey(boost::make_shared<PKey>("A0", this, &Pinger::keyA0));
	lastUpdateTime = std::chrono::duration_cast <std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Pinger::checkTimer()
{
	if ((std::chrono::duration_cast <std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())).count() - lastUpdateTime > PING_UPDATE_TIME)
	{
		updatePing();
		lastUpdateTime = (std::chrono::duration_cast <std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())).count();
	}
}

Pinger::~Pinger()
{
}


void Pinger::updatePing()
{
	TropPackets::PackA0 packA0;
	packA0.set_timestamp(std::chrono::duration_cast <std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	boost::shared_ptr<OPacket> opA0(new OPacket("A0", 0));
	opA0->setData(boost::make_shared<std::string>(packA0.SerializeAsString()));
	cm->sendToAll(opA0);
}

void Pinger::keyA0(boost::shared_ptr<IPacket> iPack)
{
	TropPackets::PackA0 packA0;
	packA0.ParseFromString(*iPack->getData());
	int64_t timeStamp = packA0.timestamp();
	int64_t timeDif = std::chrono::duration_cast <std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - timeStamp;
	auto sender = boost::static_pointer_cast<TropClient>(iPack->getSender());
	if (sender->getPing() > MAX_PING && timeDif > MAX_PING)
	{
		cm->removeClient(sender->getID());
	}
	else
	{
		sender->setPing(timeDif);
	}
}
