#include <stdio.h>
#include<winsock.h>
#include <process.h>
#include "Main.h"
#pragma comment(lib, "wsock32.lib")
#define WIN32_LEAN_AND_MEAN
char ServerName[] = "A16009-PC";           // �ڑ���̃z�X�g��
unsigned short Port = 1050;

#define BUFSIZE		256			//�o�b�t�@�T�C�Y
#define RECVSIZE  65536			//��M�o�b�t�@�T�C�Y
void init();
CMain* m_pMain;
// �\�P�b�g����
int soc;
int CL_OK = 0;
int main(int argc, char *argv[])
{

	//m_pMain = new CMain;

	init();
	//while (1) {// ���b�Z�[�W��M�̖������[�v
	// ���b�Z�[�W��M�t���O��ON��������
	// �\������
	//delay
	//	}
	//return 0;
	CL_main(argc, argv);

}

void init()
{

	soc = socket(AF_INET, SOCK_STREAM, 0);
	// ���M�X���b�h����
	HANDLE hThreadHandle;
	// ���M�X���b�h�X�^�[�g
	hThreadHandle = (HANDLE)_beginthreadex(NULL, 0, CL_sendThread, NULL, 0, NULL);
	// ��M�X���b�h
	//HANDLE hReceiveThreadHandle;

	// ��M�X���b�h�X�^�[�g
	hThreadHandle = (HANDLE)_beginthreadex(NULL, 0, CL_ReceiveThread, NULL, 0, NULL);




}

int CL_main(int argc, char *argv[]) {

	//�����`�F�b�N
	//if (argc != 2)return -1;

	//WinSock�̏�����
	WORD wVersionRequseted = MAKEWORD(1, 1);//�g�p����WinSock�̃o�[�W�����v��
	WSADATA wsaData;//WinSock�e�[�^�\��
	int nErrorStatus;

	nErrorStatus = WSAStartup(wVersionRequseted, &wsaData);
	if (atexit((void(*)(void))(WSACleanup))) {//�I������WinSock�̃��\�[�X�����
		printf("atexit(WSACleanup)���s\n");
		return -1;
	}

	if (nErrorStatus != 0) {
		printf("���������s�ł�\n");
		return -1;
	}
	else {
		//�v�������o�[�W�����Ɠ��ꂩ�m�F
		if (LOBYTE(wsaData.wVersion) == 1 && HIBYTE(wsaData.wVersion) == 1)
		{
			printf("WinSock����������\n");
		}
		else {
			printf("WinSock���������s\n");
			return -1;
		}
	}
	//�\�P�b�g�쐬
	//int soc;//�\�P�b�g
	soc = socket(AF_INET, SOCK_STREAM, 0);


	if (soc == INVALID_SET_FILE_POINTER) {
		printf("�\�P�b�g�쐬��\n");
		printf("�G���[%d���������܂���\n", WSAGetLastError());
		return -1;
	}
	//�T�[�o�[��IP�A�h���X�擾


	PHOSTENT phostent;
	unsigned long ulIPAddress;
	ulIPAddress = inet_addr(argv[1]);
	//ulIPAddress = inet_addr(ServerName);        // IP�A�h���X�擾

	//inet_addr()�֐���ServerName���z�X�g���ł������ꍇ���̏����ɓ���
	if (ulIPAddress == -1) {
		if ((phostent = gethostbyname(argv[1])) != NULL) {
			ulIPAddress = *((unsigned long *)(phostent->h_addr));
		}
		else {
			printf("�z�X�g�A�h���X�擾���s�ł�\n");
			printf("�G���[%d���������܂���\n", WSAGetLastError());
			closesocket(soc);		//�\�P�b�g�̔j��
			return -1;
		}
	}
	//�T�[�o�[�֐ڑ�
	SOCKADDR_IN addrServer;										//�T�[�o�[�̃A�h���X
	addrServer.sin_family = AF_INET;						//�A�h���X�t�@�~���̎w��
	addrServer.sin_addr.s_addr = ulIPAddress;					//�T�[�o��IP�A�h���X�̎w��
	addrServer.sin_port = htons((unsigned short)Port);	//�|�[�g�ԍ��̎w��
	if (connect(soc, (LPSOCKADDR)&addrServer, sizeof(addrServer)) == SOCKET_ERROR) {
		printf("�T�[�o�[�ւ̐ڑ����s�ł�\n");
		printf("�G���[%d���������܂���\n", WSAGetLastError());
		
		closesocket(soc);		//�\�P�b�g�̔j��
		return -1;
	}
	else { CL_OK = 1; }

	//�T�[�o�[�Ƀ��b�Z�[�W�𑗐M
	char message[BUFSIZE];
	
	sprintf(message, "Hellow,Server!");

	if (send(soc, message, sizeof(message), 0) == SOCKET_ERROR) {
		printf("�T�[�o�[�ւ̑��M���s�ł�\n");
		printf("�G���[%d���������܂���\n", WSAGetLastError());
		shutdown(soc, 2);			//����M�𖳌��ɂ���	
		closesocket(soc);			//�\�P�b�g�̔j��
		return -1;
	}


	while (1)
	{
	//	m_pMain->m_pReceive->CL_Receive(soc);
		//m_pMain->m_pSend->CL_Send(soc);
	}

	
	
	shutdown(soc, 2);			//����M�𖳌��ɂ���
	closesocket(soc);			//�\�P�b�g�̔j��
	return 0;

}


unsigned __stdcall CL_sendThread(void *pVoid) {

	m_pMain = new CMain;
	while (1) {
		if (CL_OK==1) {
			m_pMain->m_pSend->CL_Send(soc);
		}
	}
	shutdown(soc, 2);			//����M�𖳌��ɂ���
	closesocket(soc);			//�\�P�b�g�̔j��
	_endthread();
	return 0;
}

unsigned __stdcall  CL_ReceiveThread(void *pVoid) {

	m_pMain = new CMain;
	while (1) {
		//if (clientSoc != INVALID_SOCKET) {
			m_pMain->m_pReceive->CL_Receive(soc);
		//}
	}
	shutdown(soc, 2);			//����M�𖳌��ɂ���
	closesocket(soc);			//�\�P�b�g�̔j��
	_endthread();
	return 0;
}