#include "Stdafx.h"
#include "Resource.h"
#include "Socket.h"
#include "PhotoGrabDlg.h"

ServerSocket::ServerSocket(CPhotoGrabDlg* pDlg)
{
	readcount = 0;
	m_bConnected = TRUE;
	this->pDlg = pDlg;
	//	m_Buff=new char(1024*1024);
	memset(m_Buff, 0, sizeof(m_Buff));
}
ServerSocket::~ServerSocket()
{
}

void ServerSocket::SendCmd(UINT cmd)
{
	Send(&cmd, 4);
	Close();
}
void ServerSocket::OnReceive(int nErrorCode)
{
	int n = Receive(m_Buff1, 1024 * 40);
	memcpy(m_Buff + readcount, m_Buff1, n);
	readcount += n;
	struct FARCCD ccd;
	memcpy(&ccd, m_Buff, sizeof(ccd));
	if (readcount<sizeof(ccd)+ccd.fnlen + ccd.filelen)
		return;
	readcount = 0;
	pDlg->CmdProc(ccd.cmd,ccd.fnlen,ccd.filelen,m_Buff+sizeof(ccd),m_Buff+sizeof(ccd)+ccd.fnlen);
}

ListenSocket::ListenSocket(CPhotoGrabDlg* pDlg)
{
	
	this->pDlg = pDlg;
	m_pServerSocket = NULL;
}
ListenSocket::~ListenSocket()
{
	delete m_pServerSocket;
}

void ListenSocket::OnAccept(int nErrorCode)
{
	if (m_pServerSocket != NULL) 
		delete m_pServerSocket;
	m_pServerSocket = new ServerSocket(pDlg);
	int len = sizeof(m_ClientAddr);
	Accept(*m_pServerSocket, (sockaddr*)&m_ClientAddr, &len);
}