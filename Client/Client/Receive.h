#pragma once
#pragma once

#include"Main.h"
#include <stdio.h>
#include<winsock.h>
class  CSoc;


class CReceiveTask {

public:
	int CL_Receive(SOCKET  msoc);
	CReceiveTask() {};
	~CReceiveTask() {};
};

