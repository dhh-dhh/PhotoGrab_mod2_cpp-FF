
// PhotoGrab.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPhotoGrabApp: 
// �йش����ʵ�֣������ PhotoGrab.cpp
//

class CPhotoGrabApp : public CWinApp
{
public:
	CPhotoGrabApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPhotoGrabApp theApp;