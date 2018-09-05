#pragma once

#include"Main.h"
#include <stdio.h>
#include<winsock.h>
class  CSoc;


class CSendTask{

public:
	int CL_Send(SOCKET  msoc);
	CSendTask() {};
	~CSendTask() {};
};

