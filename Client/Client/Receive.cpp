
#include <stdio.h>
#include<winsock.h>
#include <process.h>
#include "Main.h"
#include"Receive.h"
#pragma comment(lib, "wsock32.lib")
#define WIN32_LEAN_AND_MEAN
#define RECVSIZE 65536	
	char recv_buf[RECVSIZE];
	int nBytesRecv;

int CReceiveTask::CL_Receive(SOCKET  msoc) {


	memset(recv_buf, 0, sizeof(recv_buf));
	nBytesRecv = recv(msoc, recv_buf, sizeof(recv_buf), 0);
	if (nBytesRecv > 0) {
		if (nBytesRecv == SOCKET_ERROR) {

			printf("�T�[�o�[����̎�M���s�ł�\n");
			printf("�G���[%d���������܂���\n", WSAGetLastError());
			return -1;
			//break;
		}
		
		recv_buf[nBytesRecv] = '\0';//��M�o�b�t�@�̌���NULL��t������
		printf("SV_%s\n", recv_buf);
		//return 0;
		//}
	}

}