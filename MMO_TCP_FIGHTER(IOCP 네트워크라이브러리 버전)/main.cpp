//#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "Network.h"
#include "RingBuffer.h"
#include "ProcessContentsPacket.h"
#include "Log.h"
#include "Monitoring.h"

#define SERVERPORT	6000
#define IOCP_WORKER_THREAD_CREATE_CNT	0
#define IOCP_WORKER_THREAD_RUNNING_CNT	0

bool isRunning = true;

int main(void)
{
	int key;
	if (!InitTCPFighterContentThread())
	{
		return 0;
	}

	if (!InitNetworkLib(SERVERPORT, IOCP_WORKER_THREAD_CREATE_CNT, IOCP_WORKER_THREAD_RUNNING_CNT))
	{
		ExitTCPFighterContentThread();
		return 0;
	}

	SetCharacterCntHandle(GetCharacterCnt);
	SetSessionCntHandle(GetCurrentSessionCnt);
	SetSectorCharacterCntHandle(GetSectorCharacterCnt);

	while (isRunning)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == 'Q' || key == 'q')
			{
				isRunning = false;
			}
		}

		Monitoring();
	}

	RequestExitNetworkLibThread();
	ExitTCPFighterContentThread();

	return 0;
}