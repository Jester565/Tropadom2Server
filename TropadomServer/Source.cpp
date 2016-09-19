#include "TropCore.h"
#include <iostream>

int main()
{
	/*
	TropServer* tropServer = new TropServer();
	tropServer->createManagers();
	Pinger* pinger = new Pinger(tropServer);
	tropServer->run(5652);
	*/
	TropCore* tropCore = new TropCore();
	tropCore->run();
}
 