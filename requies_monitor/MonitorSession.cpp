#include "pch.h"
#include "MonitorSession.h"
#include "PacketHandler.h"
#include "BufferWriter.h"
#include "BufferReader.h"

MonitorSession::MonitorSession(const SOCKET& socket, const SOCKADDR_IN& sock) : Session(socket, sock)
{
}

MonitorSession::~MonitorSession()
{
}

void MonitorSession::OnRecv(Session* session, BYTE* dataPtr, int32 dataLen)
{
	PacketHandler::HandlePacket(static_cast<MonitorSession*>(session), dataPtr, dataLen);
}

void MonitorSession::OnDisconnect()
{
}

void MonitorSession::OnConnect()
{
	SendLatency();
}

void MonitorSession::UpdateLatency(MonitorSession* session, BYTE* packet, int32 packetSize)
{
	BufferReader br(packet);
	int32 lastTick;

	br.Read(lastTick);

	int currentTick = ::GetTickCount64();
	int latency = currentTick - lastTick;
	wprintf(L"Latency %d ms\n", latency);
	Sleep(1000);
	SendLatency();
}

void MonitorSession::SendLatency()
{
	BYTE sendBuffer[20];
	BufferWriter bw(sendBuffer);
	PacketHeader* pktHeader = bw.WriteReserve<PacketHeader>();
	int currentTick = GetTickCount64();
	bw.Write(currentTick);
	pktHeader->_type = PacketProtocol::C2S_LATENCY;
	pktHeader->_pktSize = bw.GetWriterSize();
	Send(sendBuffer, bw.GetWriterSize());
}
