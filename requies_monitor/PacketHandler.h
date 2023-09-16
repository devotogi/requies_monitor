#pragma once
class MonitorSession;

class PacketHandler
{
public:
	static void HandlePacket(MonitorSession* session, BYTE* packet, int32 packetSize);

private:
	static void HandlePacket_S2C_LATENCY(MonitorSession* session, BYTE* packet, int32 packetSize);
};

