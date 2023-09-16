#pragma once
#include "Session.h"

class MonitorSession : public Session
{
private:
	int _lastTick = 0;

public:
	static Session* MakeGameSession(const SOCKET& socket, const SOCKADDR_IN& sockAddr) { return new MonitorSession(socket, sockAddr); }
	void UpdateLatency(MonitorSession* session, BYTE* packet, int32 packetSize);
	void SendLatency();

public:
	MonitorSession(const SOCKET& socket, const SOCKADDR_IN& sock);
	virtual ~MonitorSession();

	virtual void OnRecv(Session* session, BYTE* dataPtr, int32 dataLen);
	virtual void OnDisconnect();
	virtual void OnConnect();
};