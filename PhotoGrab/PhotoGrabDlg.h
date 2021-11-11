
// PhotoGrabDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "LSeekFiber.h"
#include <vector>
#define   nPort   7110
#define MSG_SAVEEND		WM_USER+999
// CPhotoGrabDlg 对话框
class ListenSocket;
class CPhotoGrabDlg : public CDialogEx
{
// 构造
public:
	CPhotoGrabDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PHOTOGRAB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGrabContinuousButton();
	virtual ~CPhotoGrabDlg();
private:
	HANDLE hDev = INVALID_HANDLE_VALUE;
	unsigned int nPCIeDevCount = 0;
	char*    configFilename = new char[MAX_PATH];
	unsigned char* pUserBuffer;
	unsigned char* pUserBufferall;
	bool GetOption(char* lpConfigFileName)
	{
		OPENFILENAME	iniofn;
		wchar_t	gcMsgBuf[MAX_PATH] = _T("\0");
		wchar_t  lpTempFileName[_MAX_PATH] = _T("\0");
		GetModuleFileName(NULL, gcMsgBuf, MAX_PATH);
		PathRemoveFileSpec(gcMsgBuf);

		iniofn.lStructSize = sizeof(OPENFILENAME);
		iniofn.hwndOwner = NULL;
		iniofn.lpstrFilter = _T("Configuration File(*.vlcf)\0*.vlcf\0");
		iniofn.lpstrCustomFilter = NULL;
		iniofn.nFilterIndex = 1;
		iniofn.lpstrFile = lpTempFileName;
		iniofn.nMaxFile = MAX_PATH;
		iniofn.lpstrFileTitle = NULL;
		iniofn.nMaxFileTitle = MAX_PATH;
		iniofn.lpstrInitialDir = gcMsgBuf;
		iniofn.lpstrTitle = _T("The 'Vulcan Configuration File' of the purpose read is chosen.");
		iniofn.Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
		iniofn.lpstrDefExt = _T("vlcf");

		if (GetOpenFileName(&iniofn) == FALSE)
			return false;

		WideCharToMultiByte(CP_OEMCP, 0, lpTempFileName, (int)_tcsclen(lpTempFileName) + 1, lpConfigFileName, _MAX_PATH, NULL, NULL);

		return(true);
	}
	ListenSocket* m_pListenSocket;
public:
	afx_msg void OnBnClickedGrabSequenceButton();
	afx_msg void Grab(int n,CString fn);
    int m_eImageNum;
	int m_eSpanTime;
	CString m_sRootDir;
	UINT	m_nImageNum;
	CString m_sFile;
	LSeekFiber seek;
	int m_nTop;
	int m_nBottom;
	CString m_sFn[1000];
	BOOL m_bClose;
	void CmdProc(UINT cmd, UINT fnlen, UINT filelen, char* suffix, char* end);
	afx_msg void OnBnClickedOk();
	CString m_eDir;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedChushihuaButton();
	double m_longtime;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	UINT m_addnum;
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	bool flag;
};
