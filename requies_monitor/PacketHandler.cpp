#include "pch.h"
#include "PacketHandler.h"
#include "MonitorSession.h"

void PacketHandler::HandlePacket(MonitorSession* session, BYTE* packet, int32 packetSize)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(packet);
	BYTE* dataPtr = packet + sizeof(PacketHeader);
	int32 dataSize = packetSize - sizeof(PacketHeader);

	switch (header->_type)
	{
	case PacketProtocol::S2C_LATENCY:
		HandlePacket_S2C_LATENCY(session, dataPtr, dataSize);
		break;
	}
}

void PacketHandler::HandlePacket_S2C_LATENCY(MonitorSession* session, BYTE* packet, int32 packetSize)
{
	session->UpdateLatency(session, packet, packetSize);
}
