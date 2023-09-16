#include "pch.h"
#include "MonitorService.h"
#include "TCPConnector.h"
#include "IOCPCore.h"
#include "Session.h"

MonitorService::MonitorService(int32 maxSession, const char* connetIp, uint16 connetPort, Session* (*clientSessionFactory)(const SOCKET&, const SOCKADDR_IN&)) : ClientService(maxSession, connetIp, connetPort, clientSessionFactory)
{
}

MonitorService::~MonitorService()
{
}

void MonitorService::Start()
{
    wprintf(L"ClientServerStart\n");
    try
    {
        for (int i = 0; i < _maxSession; i++)
        {
            Session* newSession = _tcpConnector->Connect();
            if (newSession != nullptr)
            {
                _iocpCore->RegisterIOCP(newSession);
                newSession->OnConnect();
            }
        }

        while (true) {
            Sleep(10);
        }
    }
    catch (std::wstring error)
    {
        wprintf(L"ClientServerStart Error\n");
    }
}
