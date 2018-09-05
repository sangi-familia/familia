
#include <stdio.h>
#include<winsock.h>
#include "Main.h"
#include"Send.h"
#pragma comment(lib, "wsock32.lib")
#define WIN32_LEAN_AND_MEAN

char Sendmessage[100];




int CSendTask::CL_Send(SOCKET  msoc) {



	//while (1)
	//	{
	//printf("         CL_");
	scanf("%s", &Sendmessage);

	if (send(msoc, Sendmessage, sizeof(Sendmessage), 0) == SOCKET_ERROR) {
		printf("サーバーへの送信失敗です\n");
		printf("エラー%dが発生しました\n", WSAGetLastError());
		shutdown(msoc, 2);			//送受信を無効にする
		closesocket(msoc);			//ソケットの破棄
		return -1;
		//break;
		//}

	}
	//return 0;

}

