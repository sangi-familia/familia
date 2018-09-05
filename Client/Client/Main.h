#pragma once
#include <stdio.h>
#include<winsock.h>
#include"Send.h"
#include "Receive.h"



class CMain {
public:
	CSendTask* m_pSend;
	CReceiveTask* m_pReceive;
};
unsigned __stdcall  CL_ReceiveThread(void*);
unsigned __stdcall  CL_sendThread(void*);
int CL_main(int argc, char *argv[]);
int main(int argc, char *argv[]);
