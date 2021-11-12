#pragma once
#include <afxsock.h>		
#define CMD_SAVE		1
#define CMD_MAKEDIR		2 
#define CMD_FILEWRITE	3
#define CMD_BEGINSAVE	5
#define CMD_SAVEDONE	6
#define CMD_SUCCESS		11
#define CMD_FAIL		12
#define CMD_DONE		13
class CPhotoGrabDlg;
struct FARCCD
{
	UINT cmd;
	UINT fnlen;
	UINT filelen;
};

class ServerSocket : public CAsyncSocket
{
public:
	ServerSocket(CPhotoGrabDlg* pDlg);
	~ServerSocket();

	void SendCmd(UINT cmd);
public:
	BOOL		m_bConnected;
	char		m_Buff[1024 * 1024];
	char		m_Buff1[1024 * 40];
	UINT			readcount;
	CPhotoGrabDlg *pDlg;

protected:
	virtual void OnReceive(int nErrorCode);
};
class ListenSocket : public CAsyncSocket
{
public:
	ListenSocket(CPhotoGrabDlg* pDlg);
	~ListenSocket();

public:
	sockaddr_in		m_ClientAddr;
	ServerSocket*   m_pServerSocket;
	CPhotoGrabDlg	*pDlg;

protected:
	virtual void OnAccept(int nErrorCode);
};