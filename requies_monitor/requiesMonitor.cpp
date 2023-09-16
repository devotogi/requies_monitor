#include "pch.h"
#include "MonitorService.h"
#include "IOCPCore.h"
#include "MonitorSession.h"
#include "ThreadManager.h"
unsigned int _stdcall Dispatch(void* Args)
{
	MonitorService* service = reinterpret_cast<MonitorService*>(Args);
	while (true)
		service->GetIOCPCore()->Dispatch();
}

int main()
{
	const char* ip = "58.236.86.23";
	MonitorService service(1, ip, 30002, MonitorSession::MakeGameSession);

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	int32 threadCount = sysInfo.dwNumberOfProcessors * 2;

	for (int i = 0; i < threadCount; i++)
	{
		ThreadManager::GetInstance()->Launch(Dispatch, &service);
	}

	service.Start();
	return 0;
}