
// PhotoGrabDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PhotoGrab.h"
#include "PhotoGrabDlg.h"
#include "afxdialogex.h"
#include "IKapBoard.h"
#include "socket.h"
#include <atlconv.h>
#include <vector>
//#include <Windows.h>
#pragma comment( lib, "shlwapi.lib" )

DWORD WINAPI ThreadSeek(LPVOID lpParameter);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MSG_SAVEEND WM_USER+999


//HANDLE hDev = INVALID_HANDLE_VALUE;

HANDLE  g_hThreadEvent;   //�¼����
char savePath[MAX_PATH] = { 0 };
char *g_pImageBuffer = NULL;
int	g_nImageOffset = 0;
int g_nSaveCount = 0;
vector<char *> g_vImage;
volatile bool g_bFrameReady = false;
int g_ImgCount = 0;
static int g_nGrabImageTotalCount = 20;
static int g_nFrameTotalCount = 5;
int g_nImageIndex = 0;
CString filepath;
int m_writenum=0;
int m_addnum1 = 0;


void __stdcall OnFrameReady(void* Context);
void __stdcall OnGrabStart(void* pContext);
void __stdcall OnGrabStop(void* pContext);
void __stdcall OnFrameLost(void* pContext);
void __stdcall OnTimeout(void* pContext);

void CPhotoGrabDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	KillTimer(1);
	flag = true;
	CDialogEx::OnTimer(nIDEvent);
}

unsigned CALLBACK threadImg(void *param)
{
	std::vector<char*>::iterator it;
	//CPhotoGrabDlg* pp = (CPhotoGrabDlg*)param;
	int nFrameSize =7920*6004*2;
	int num;
	while (1)
	{
		WaitForSingleObject(g_hThreadEvent, INFINITE);
		if (!g_vImage.empty())
		{
			it = g_vImage.begin();
			memcpy(&num, *it, sizeof(num));
			sprintf_s(savePath, "ImgCount_%d_%d.raw", g_nSaveCount, num);
			CString pathname = filepath + savePath;
			/*errno_t err;
			FILE *fp = NULL;
			err = fopen_s(&fp, pathname, "ab+");
			if (fp != NULL)
			{
				fwrite(*it, nFrameSize, 1, fp);
			}
			fclose(fp);*/
			CFile pfile;
			pfile.Open(pathname, CFile::modeReadWrite | CFile::modeCreate);
			pfile.Write(*it, nFrameSize);
			pfile.Close();
			g_nSaveCount++;
			g_vImage.erase(g_vImage.begin());
		}
		if (g_nSaveCount > g_ImgCount + 1)
		{
			break;
		}
	}
	return 1;
}
void CALLBACK OnFrameReady(void* hDev)
{
	IKAPBUFFERSTATUS status;
	int frameSize;
	char* pBuffer;
	IKapGetBufferStatus(hDev, g_nImageIndex, &status);
	IKapGetBufferAddress(hDev, g_nImageIndex, (void**)&pBuffer);
	IKapGetInfo(hDev, IKP_FRAME_SIZE, &frameSize);

	int size = frameSize - g_nImageOffset;

	g_vImage.push_back(pBuffer);

	memcpy(g_pImageBuffer + g_nImageOffset, pBuffer + g_nImageOffset, size);
	g_nImageOffset += size;
	SetEvent(g_hThreadEvent);
	// ����ͼ������
	static int test = 0;
	test++;
	g_ImgCount++;
	if (g_ImgCount == g_nGrabImageTotalCount)
	{
		g_bFrameReady = true;
	}
	g_nImageOffset = 0;
    g_nImageIndex = (g_nImageIndex + 1) % g_nFrameTotalCount;//���������
}

void CALLBACK OnGrabStart(void* Context) {
	
}

void CALLBACK OnGrabStop(void* Context) {

}

void CALLBACK OnFrameLost(void* Context) {

}

void CALLBACK OnTimeout(void* Context) {

}


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPhotoGrabDlg �Ի���



CPhotoGrabDlg::CPhotoGrabDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPhotoGrabDlg::IDD, pParent)
	, m_eImageNum(0)
	, m_eSpanTime(0)
	, m_eDir(_T(""))
	, m_longtime(0)
	, m_addnum(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_sRootDir = _T("F://Lamost_Data");
}

void CPhotoGrabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUMBER_EDIT, m_eImageNum);
	DDX_Text(pDX, IDC_TIME_EDIT, m_eSpanTime);

	DDX_Text(pDX, IDC_EDIT3, m_eDir);
	DDX_Text(pDX, IDC_LONG_EDIT, m_longtime);
	DDX_Text(pDX, IDC_EDIT4, m_addnum);
}

BEGIN_MESSAGE_MAP(CPhotoGrabDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	//ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GrabOnce_BUTTON, &CPhotoGrabDlg::OnBnClickedGrabContinuousButton)
	ON_BN_CLICKED(IDC_GrabContinus_BUTTON, &CPhotoGrabDlg::OnBnClickedGrabSequenceButton)
	ON_BN_CLICKED(IDC_OK, &CPhotoGrabDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CPhotoGrabDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHUSHIHUA_BUTTON, &CPhotoGrabDlg::OnBnClickedChushihuaButton)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPhotoGrabDlg ��Ϣ�������

BOOL CPhotoGrabDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	m_pListenSocket = new ListenSocket(this);
	m_pListenSocket->Create(nPort); 
	m_pListenSocket->Listen(1);

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	CreateThread(NULL, 0, ThreadSeek, (LPVOID)this, 0, NULL);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
CPhotoGrabDlg::~CPhotoGrabDlg()
{
	delete m_pListenSocket;
}
void CPhotoGrabDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPhotoGrabDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPhotoGrabDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPhotoGrabDlg::OnBnClickedGrabContinuousButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	g_hThreadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	int nFrameSize;
	
	IKapGetInfo(hDev, IKP_FRAME_SIZE, &nFrameSize);
	IKapRegisterCallback(hDev, IKEvent_FrameReady, OnFrameReady, hDev);
	IKapRegisterCallback(hDev, IKEvent_GrabStart, OnGrabStart, NULL);
	IKapRegisterCallback(hDev, IKEvent_GrabStop, OnGrabStop, NULL);
	IKapRegisterCallback(hDev, IKEvent_FrameLost, OnFrameLost, NULL);
	IKapRegisterCallback(hDev, IKEvent_TimeOut, OnTimeout, NULL);
	g_bFrameReady = false;

	g_nImageIndex = 0;
	if (g_pImageBuffer != NULL) delete[] g_pImageBuffer;
	g_pImageBuffer = new char[nFrameSize];

	HANDLE hImage = (HANDLE)_beginthreadex(NULL, 0, threadImg, &m_eDir, 0, NULL);

	int nFrameCount = 5;
	IKapSetInfo(hDev, IKP_FRAME_TRANSFER_MODE, IKP_FRAME_TRANSFER_SYNCHRONOUS_NEXT_EMPTY_WITH_PROTECT);//����ģʽ
	IKapSetInfo(hDev, IKP_FRAME_AUTO_CLEAR, IKP_FRAME_AUTO_CLEAR_VAL_ENABLE);//�����Զ����
	IKapSetInfo(hDev, IKP_FRAME_COUNT, nFrameCount);//���û�����֡��
	IKapStartGrab(hDev, 0);//��������
	Sleep(m_longtime*60*1000);  //���������ɼ�����ʱ��

	IKapClose(hDev);//�ر����
	delete[] g_pImageBuffer;
	delete[] configFilename;
	//�ͷŻص�����
	IKapStopGrab(hDev);
	//WaitForSingleObject(hImage, INFINITE);
	IKapUnRegisterCallback(hDev, IKEvent_FrameReady);
	IKapUnRegisterCallback(hDev, IKEvent_GrabStop);
	IKapUnRegisterCallback(hDev, IKEvent_FrameLost);
	IKapUnRegisterCallback(hDev, IKEvent_TimeOut);
	CloseHandle(g_hThreadEvent);
	CloseHandle(hImage);
	CDialogEx::OnOK();
}
void CPhotoGrabDlg::OnBnClickedGrabSequenceButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nTimeout = 500000;
	int nFrameCount = 1;
	char namein[80];
	int  num;
	int nFrameSize = 0;
	int nIndex = 0;
	CString str1;
	CTime tm;
	tm = CTime::GetCurrentTime();
	str1 = tm.Format("%Y%m%d_%H%M%S");
	IKapSetInfo(hDev, IKP_TIME_OUT, nTimeout);
	IKapSetInfo(hDev, IKP_FRAME_COUNT, nFrameCount);
	IKapSetInfo(hDev, IKP_FRAME_TRANSFER_MODE, IKP_FRAME_TRANSFER_SYNCHRONOUS_NEXT_EMPTY_WITH_PROTECT);
	IKapSetInfo(hDev, IKP_GRAB_MODE, IKP_GRAB_BLOCK);
	IKAPBUFFERSTATUS status;
	IKapGetBufferStatus(hDev, nIndex, &status);
	IKapGetInfo(hDev, IKP_FRAME_SIZE, &nFrameSize);
	IKapStartGrab(hDev, nFrameCount);//����
	if (m_addnum == 1)//ֱ�Ӵ�
	{
		IKapGetBufferAddress(hDev, nIndex, (void**)&pUserBuffer);
		sprintf_s(namein, "_%2d_%2d.raw", m_writenum, m_addnum);
		CString pathname = m_eDir + str1 + namein;
		CFile pfile;
		pfile.Open(pathname, CFile::modeReadWrite | CFile::modeCreate);
		pfile.Write(pUserBuffer, nFrameSize);
		pfile.Close();
		m_writenum++;
	}
	else//���ŵ���
	{
		m_addnum1++;
		IKapGetBufferAddress(hDev, nIndex, (void**)&pUserBuffer);
		unsigned char* pUserBufferx = pUserBufferall;
		for (int i = 0; i < nFrameSize/2; i++)
		{
			int x = 0;
			int y = 0;
			x = x | (*(++pUserBufferx));
			x = x << 8;
			x = x | (*(--pUserBufferx));
			y = y | (*(++pUserBuffer));
			y = y << 8;
			y = y | (*(--pUserBuffer));
			x = x + y;
			BYTE x1, x2;
			x1 = x >> 8;//��λ
			x2 = x & 0xFF;//��λ
			(*pUserBufferx) = x2;
			pUserBufferx++;
			(*pUserBufferx) = x1;
			pUserBufferx++;
			pUserBuffer++;
			pUserBuffer++;
		}
		if (m_addnum1 == m_addnum)//���Ӻ��ͼ
		{
			sprintf_s(namein, "_%2d_%2d.raw", m_writenum, m_addnum);
			CString pathname = m_eDir + str1 + namein;
			CFile pfile;
			pfile.Open(pathname, CFile::modeReadWrite | CFile::modeCreate);
			pfile.Write(pUserBufferall, nFrameSize);
			pfile.Close();
			m_writenum++;
			memset(pUserBufferall, 0, nFrameSize);
			m_addnum1 = 0;
		}
	}
/*
	IKapGetInfo(hDev, IKP_FRAME_SIZE, &nFrameSize);
	pUserBufferall = new unsigned char[nFrameSize];
	memset(pUserBufferall, 0, nFrameSize);*/
	/*while (nIndex < m_eImageNum)
	{
		IKapGetBufferAddress(hDev, nIndex, (void**)&pUserBuffer);
		unsigned char* pUserBufferx = pUserBufferall;
		unsigned char* pUserBuffery = pUserBuffer;
		for (int i = 0; i < nFrameSize; i++)
		{
			(*pUserBufferx) = (*pUserBufferx) + (*pUserBuffery);
			pUserBufferx++;
			pUserBuffery++;
		}
		memcpy(&num, pUserBuffer, sizeof(num));
		sprintf_s(namein, "_%d_%d.raw", nIndex, num);
		CString pathname = m_eDir + str1 + namein;
		CFile pfile;
		pfile.Open(pathname, CFile::modeReadWrite | CFile::modeCreate);
		pfile.Write(pUserBuffer, nFrameSize);
		pfile.Close();
		IKapGetBufferStatus(hDev, ++nIndex, &status);
	}
	CString pathname = m_eDir + str1+".raw";
	CFile pfile;
	pfile.Open(pathname, CFile::modeReadWrite | CFile::modeCreate);
	pfile.Write(pUserBufferall, nFrameSize);
	pfile.Close();
*/
	//while (nIndex < m_eImageNum)
	//{
	//	IKapGetInfo(hDev, IKP_FRAME_SIZE, &nFrameSize);
	//	IKapGetBufferAddress(hDev, nIndex, (void**)&pUserBuffer);
	//	memcpy(&num, pUserBuffer, sizeof(num));
	//	sprintf_s(namein, "_%d_%d.raw", nIndex,num);
	//	CString pathname = m_eDir+str1 + namein;
	//	CFile pfile;
	//	pfile.Open(pathname, CFile::modeReadWrite | CFile::modeCreate);
	//	pfile.Write(pUserBuffer, nFrameSize);
	//	pfile.Close();
	//	IKapGetBufferStatus(hDev, ++nIndex, &status);
	//}

}

void CPhotoGrabDlg::Grab(int n, CString fn)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nTimeout = 50000;
	int nFrameCount = n;
	char namein[80];
	int nFrameSize = 0;
	int nIndex = 0;
	IKapSetInfo(hDev, IKP_TIME_OUT, nTimeout);
	IKapSetInfo(hDev, IKP_FRAME_COUNT, nFrameCount);
	IKapSetInfo(hDev, IKP_FRAME_TRANSFER_MODE, IKP_FRAME_TRANSFER_ASYNCHRONOUS);
	IKapSetInfo(hDev, IKP_GRAB_MODE, IKP_GRAB_BLOCK);
	IKAPBUFFERSTATUS status;
	IKapGetInfo(hDev, IKP_FRAME_COUNT, &nFrameCount);
	IKapGetBufferStatus(hDev, nIndex, &status);
	IKapStartGrab(hDev, nFrameCount);
	while (nIndex < nFrameCount)
	{
		IKapGetInfo(hDev, IKP_FRAME_SIZE, &nFrameSize);
		IKapGetBufferAddress(hDev, nIndex, (void**)&pUserBuffer);
		sprintf_s(namein, "_%02d.raw", nIndex);
		CString pathname=fn+namein;
		CFile pfile;
		pfile.Open(pathname, CFile::modeReadWrite | CFile::modeCreate);
		pfile.Write(pUserBuffer, nFrameSize);
		pfile.Close();
		IKapGetBufferStatus(hDev, ++nIndex, &status);
	}

}




void CPhotoGrabDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_eImageNum <= 0)
	{
		MessageBox(_T("ͼƬ�����������0"));
		return;
	}
	if (m_addnum > 16)
	{
		MessageBox(_T("���16��ͼƬ���Ӵ�һ��rawͼ"));
		return;
	}
	if (m_addnum < 0)
		m_addnum = 1;
	if (m_eSpanTime < 0)
		m_eSpanTime = 0;
	if (m_eDir.IsEmpty())
	{
		AfxMessageBox(_T("����·������Ϊ��"));
		return;
	}
	if (m_eImageNum%m_addnum != 0)
	{
		AfxMessageBox(_T("����ͼ����������Ϊ��������������"));
		return;
	}
	int nFrameSize = 0;
	if (m_addnum>1)
	{
		IKapGetInfo(hDev, IKP_FRAME_SIZE, &nFrameSize);
		pUserBufferall = new unsigned char[nFrameSize];
		memset(pUserBufferall, 0, nFrameSize);
	}
	double photonumber = m_longtime * 60 / m_eSpanTime;
	for (int i = 0; i <= photonumber; i++)
	{ 
		SetTimer(1, m_eSpanTime * 1000, NULL);
		flag = false;
		for (int j = 0; j < m_eImageNum; j++)
		{
			OnBnClickedGrabSequenceButton();
		}
		m_writenum = 0;
		MSG msg;
		while (GetMessage(&msg, 0, 0, 0))
		{
			DispatchMessage(&msg);
			if (flag)
				break;
		}
	}
	IKapClose(hDev);
	delete[] configFilename;
	CDialogEx::OnOK();
	
}


void CPhotoGrabDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	::CoInitialize(NULL);
	USES_CONVERSION;

	LPITEMIDLIST     pidlPath;
	TCHAR  pszDplName[MAX_PATH];
	BROWSEINFO     biFile;
	IMalloc     *pDllMlc;
	biFile.hwndOwner = this->GetSafeHwnd();
	biFile.pidlRoot = NULL;
	biFile.pszDisplayName = NULL;
	biFile.lpszTitle =L"ѡ���ļ��� ";
	biFile.ulFlags = BIF_RETURNFSANCESTORS;
	biFile.lpfn = NULL;
	biFile.lParam = NULL;
	biFile.iImage = 0;
	if (SUCCEEDED(SHGetMalloc(&pDllMlc)))
	{
		if ((pidlPath = SHBrowseForFolder(&biFile)) != NULL)
			SHGetPathFromIDList(pidlPath, pszDplName);
		else
			return;
	}

	CString m_eDir = pszDplName;
	m_eDir += "\\";
	filepath = m_eDir;
	SetDlgItemTextW(IDC_EDIT3, m_eDir);
	
	
}


void CPhotoGrabDlg::OnBnClickedChushihuaButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (GetOption(configFilename) == false)
	{
		AfxMessageBox(_T("Read Vulcan configuration file failed(*.vlcf)."));
		return;
	}
	//PIKAPERRORINFO pInfo = (PIKAPERRORINFO)malloc(sizeof(PIKAPERRORINFO));

	IKapGetBoardCount(IKBoardPCIE, &nPCIeDevCount);
	hDev = IKapOpen(IKBoardPCIE, 0);
	
	IKapLoadConfigurationFromFile(hDev, configFilename);

}

void CPhotoGrabDlg::CmdProc(UINT cmd, UINT fnlen, UINT filelen, char* suffix, char* end)
{
	UINT return_msg = CMD_SUCCESS;
	char buf[200];
	strncpy_s(buf, suffix, fnlen);
	buf[fnlen] = 0;
	CString DirName = m_sRootDir + _T("//raw//");
	if (cmd == CMD_SAVE)//�����ļ���
	{
		m_nImageNum = filelen;
		DirName += buf;
		Grab(m_nImageNum, DirName);
		PostMessage(MSG_SAVEEND, CMD_DONE, 0);
	}
	else if (cmd == CMD_MAKEDIR)//�����ļ���
	{
		DirName += buf;
		if (!CreateDirectory(DirName, NULL))
			return_msg = CMD_FAIL;
		PostMessage(MSG_SAVEEND, return_msg, 0);
	}
	else
	{
		DirName += buf;
		USES_CONVERSION;
		LPCSTR FN = (LPCSTR)T2A(DirName);//ת��CString��const char*
		FILE *pFile;
		errno_t err;
		err = fopen_s(&pFile, FN, "w+");
		fwrite(end, 1, filelen, pFile);
		fclose(pFile);
		return_msg = CMD_DONE;

	    m_sFn[m_nBottom].Format(_T("%s"),DirName);
		m_nBottom++;
	    if(m_nBottom>=1000)m_nBottom=0;
		PostMessage(MSG_SAVEEND, return_msg, 0);

	}

	return;
}

DWORD WINAPI ThreadSeek(LPVOID lpParameter)
{
	CPhotoGrabDlg* pp = (CPhotoGrabDlg*)lpParameter;

	pp->seek.Init();
	pp->m_nTop = 0;
	pp->m_nBottom = 0;
	pp->m_bClose = FALSE;

	CString fn;

	while (1)
	{
		if (pp->m_bClose)break;

		if (pp->m_nTop == pp->m_nBottom)
			Sleep(1000);
		else
		{
			pp->seek.SeekPoints(pp->m_sFn[pp->m_nTop]);
			pp->m_nTop++;
			if (pp->m_nTop >= 1000)pp->m_nTop = 0;
		}
	}
	return 0;
}
LRESULT CPhotoGrabDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (message == MSG_SAVEEND)
		m_pListenSocket->m_pServerSocket->SendCmd(wParam);

	return CDialogEx::WindowProc(message, wParam, lParam);
}



