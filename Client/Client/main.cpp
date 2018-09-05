#include <stdio.h>
#include<winsock.h>
#include <process.h>
#include "Main.h"
#pragma comment(lib, "wsock32.lib")
#define WIN32_LEAN_AND_MEAN
char ServerName[] = "A16009-PC";           // 接続先のホスト名
unsigned short Port = 1050;

#define BUFSIZE		256			//バッファサイズ
#define RECVSIZE  65536			//受信バッファサイズ
void init();
CMain* m_pMain;
// ソケット生成
int soc;
int CL_OK = 0;
int main(int argc, char *argv[])
{

	//m_pMain = new CMain;

	init();
	//while (1) {// メッセージ受信の無限ループ
	// メッセージ受信フラグがONだったら
	// 表示処理
	//delay
	//	}
	//return 0;
	CL_main(argc, argv);

}

void init()
{

	soc = socket(AF_INET, SOCK_STREAM, 0);
	// 送信スレッド生成
	HANDLE hThreadHandle;
	// 送信スレッドスタート
	hThreadHandle = (HANDLE)_beginthreadex(NULL, 0, CL_sendThread, NULL, 0, NULL);
	// 受信スレッド
	//HANDLE hReceiveThreadHandle;

	// 受信スレッドスタート
	hThreadHandle = (HANDLE)_beginthreadex(NULL, 0, CL_ReceiveThread, NULL, 0, NULL);




}

int CL_main(int argc, char *argv[]) {

	//引数チェック
	//if (argc != 2)return -1;

	//WinSockの初期化
	WORD wVersionRequseted = MAKEWORD(1, 1);//使用するWinSockのバージョン要求
	WSADATA wsaData;//WinSockテータ構造
	int nErrorStatus;

	nErrorStatus = WSAStartup(wVersionRequseted, &wsaData);
	if (atexit((void(*)(void))(WSACleanup))) {//終了時にWinSockのリソースを解放
		printf("atexit(WSACleanup)失敗\n");
		return -1;
	}

	if (nErrorStatus != 0) {
		printf("初期化失敗です\n");
		return -1;
	}
	else {
		//要求したバージョンと同一か確認
		if (LOBYTE(wsaData.wVersion) == 1 && HIBYTE(wsaData.wVersion) == 1)
		{
			printf("WinSock初期化成功\n");
		}
		else {
			printf("WinSock初期化失敗\n");
			return -1;
		}
	}
	//ソケット作成
	//int soc;//ソケット
	soc = socket(AF_INET, SOCK_STREAM, 0);


	if (soc == INVALID_SET_FILE_POINTER) {
		printf("ソケット作成失\n");
		printf("エラー%dが発生しました\n", WSAGetLastError());
		return -1;
	}
	//サーバーのIPアドレス取得


	PHOSTENT phostent;
	unsigned long ulIPAddress;
	ulIPAddress = inet_addr(argv[1]);
	//ulIPAddress = inet_addr(ServerName);        // IPアドレス取得

	//inet_addr()関数がServerNameがホスト名であった場合下の処理に入る
	if (ulIPAddress == -1) {
		if ((phostent = gethostbyname(argv[1])) != NULL) {
			ulIPAddress = *((unsigned long *)(phostent->h_addr));
		}
		else {
			printf("ホストアドレス取得失敗です\n");
			printf("エラー%dが発生しました\n", WSAGetLastError());
			closesocket(soc);		//ソケットの破棄
			return -1;
		}
	}
	//サーバーへ接続
	SOCKADDR_IN addrServer;										//サーバーのアドレス
	addrServer.sin_family = AF_INET;						//アドレスファミリの指定
	addrServer.sin_addr.s_addr = ulIPAddress;					//サーバのIPアドレスの指定
	addrServer.sin_port = htons((unsigned short)Port);	//ポート番号の指定
	if (connect(soc, (LPSOCKADDR)&addrServer, sizeof(addrServer)) == SOCKET_ERROR) {
		printf("サーバーへの接続失敗です\n");
		printf("エラー%dが発生しました\n", WSAGetLastError());
		
		closesocket(soc);		//ソケットの破棄
		return -1;
	}
	else { CL_OK = 1; }

	//サーバーにメッセージを送信
	char message[BUFSIZE];
	
	sprintf(message, "Hellow,Server!");

	if (send(soc, message, sizeof(message), 0) == SOCKET_ERROR) {
		printf("サーバーへの送信失敗です\n");
		printf("エラー%dが発生しました\n", WSAGetLastError());
		shutdown(soc, 2);			//送受信を無効にする	
		closesocket(soc);			//ソケットの破棄
		return -1;
	}


	while (1)
	{
	//	m_pMain->m_pReceive->CL_Receive(soc);
		//m_pMain->m_pSend->CL_Send(soc);
	}

	
	
	shutdown(soc, 2);			//送受信を無効にする
	closesocket(soc);			//ソケットの破棄
	return 0;

}


unsigned __stdcall CL_sendThread(void *pVoid) {

	m_pMain = new CMain;
	while (1) {
		if (CL_OK==1) {
			m_pMain->m_pSend->CL_Send(soc);
		}
	}
	shutdown(soc, 2);			//送受信を無効にする
	closesocket(soc);			//ソケットの破棄
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
	shutdown(soc, 2);			//送受信を無効にする
	closesocket(soc);			//ソケットの破棄
	_endthread();
	return 0;
}