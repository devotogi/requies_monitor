#pragma once
#include "ClientService.h"
class MonitorService : public ClientService
{
public:
	MonitorService(int32 maxSession, const char* connetIp, uint16 connetPort, Session* (*clientSessionFactory)(const SOCKET&, const SOCKADDR_IN&));
	virtual ~MonitorService();

	virtual void Start();
};

