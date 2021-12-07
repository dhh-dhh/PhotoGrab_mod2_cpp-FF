// SeekFiber.h : main header file for the SEEKFIBER application
//

#include <Eigen/Dense>
//using Eigen::MatrixXd;
using namespace Eigen;
using namespace Eigen::internal;
using namespace Eigen::Architecture;

#if !defined(AFX_LSEEKFIBER_H__8A300018_A752_4758_9892_FE28DE21F58C__INCLUDED_)
#define AFX_LSEEKFIBER_H__8A300018_A752_4758_9892_FE28DE21F58C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define  CFG_DIR "F:\\Paohe\\bin"
#define  LAM_DIR "F:\\Lamost_Data"

#include "resource.h"		// main symbols
#include <afx.h>
#include <vector>
//#include <string>
#include <Python.h>
#include <string>
//#include <iostream>
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CSeekFiberp:
// See SeekFiber.cpp for the implementation of this class
//

class LSeekFiber
{
public:
	LSeekFiber();
	virtual ~LSeekFiber();

	BOOL Init();
	void Close();
	void TxtReadQ(CString fn);//txt��Ѱ��Q���� Ϊ���������׼��
	BOOL SeekPoints(CString strFileName);
	BOOL SeekPointsTxt(CString strFileName);
	void LSeekFiber::NiheParam(CString strFileName);
	int		m_nTop;
	int		m_nBottom;

protected:
	BOOL MemAlloc();
	void MemRelease();

	BOOL GetConfig();		//��ȡconfig.ini

	BOOL GetFFLilun(); //�xȡFF��Փ

	BOOL ReadZBdata(CString strFileName);
	BOOL ReadRawData(CString strFileName);

	void SortPoints2();
	void SortPoints();
	void CaliPoints();
	BOOL WriteTxtData(CString strFileName);

	unsigned short * lpRawBuffer;		//��raw�ļ���������
	double	dblCaliFactor[2][15];		//�궨ϵ��
	double*	dblX;						//����������,intLightNum��
	double* dblY;						//����������,intLightNum��
	double* dblX1;						//��������������,intLightNum����intUnitNum��
	double* dblY1;						//��������������,intLightNum����intUnitNum��
	double*	dblCoorX;					//������,intLightNum��
	double* dblCoorY;					//������,intLightNum��
	double* dblCoorX1;					//����������,intLightNum����intUnitNum��
	double* dblCoorY1;					//����������,intLightNum����intUnitNum��
	double* dblDist;					//�������
	double* dblDist1;					//�������
	int*	dblDistM;					//�������
	int*	dblDistN;					//�������
	BOOL*	bFlag1;						//���
	BOOL*	bFlag2;						//���
	int*	intMM;						//������ֵ,intLightNum��
	int*	intMM1;						//������ֵ,intLightNum��
	int*	intNum;						//���������,intLightNum��
	int*	intNum1;						//���������,intLightNum��

	//double* dblPCoorX;				//���������������꣬intPNum����Ԥ��
	//double* dblPCoorY;				//���������������꣬intPNum����Ԥ��
	//double* dblPCenA;					//�������˵�Ƕ����꣬intPNum����Ԥ��
	//double* dblPEccA;					//�������˵�Ƕ����꣬intPNum����Ԥ��

	/// <summary>
	/// dsp add
	/// </summary>
	double* pixelPCoorX;					//�������˵�Ƕ����꣬intPNum����Ԥ��
	double* pixelPCoorY;					//�������˵�Ƕ����꣬intPNum����Ԥ��
	double* micronPCoorX;					//�������˵�΢�����꣬intPNum����Ԥ��
	double* micronPCoorY;					//�������˵�΢�����꣬intPNum����Ԥ��
	double* micronQCoorX;					//�ο����˵�΢�����꣬intQNum����Ԥ��
	double* micronQCoorY;					//�ο����˵�΢�����꣬intQNum����Ԥ��
	double* dblQCoorX;				//�ο������������꣬intQNum����Ԥ��
	double* dblQCoorY;				//�ο������������꣬intQNum����Ԥ��
	double* dblQCenA;					//�ο����˵�Ƕ����꣬intQNum����Ԥ��
	double* dblQEccA;					//�ο����˵�Ƕ����꣬intQNum����Ԥ��
	double* pixelQCoorX;			//�ο������������꣬intQNum����Ԥ��
	double* pixelQCoorY;			//�ο������������꣬intQNum����Ԥ��
	vector<string> sCellNameQ;				//CellName��intUnitNum����Ԥ��
	vector<string> sCellNameP;				//CellName��intUnitNum����Ԥ��
	double* temp;

	double * dblZBCoorX;				//�������꣬intUnitNum����Ԥ��
	double * dblZBCoorY;				//�������꣬intUnitNum����Ԥ��
	double * dblZBCenA;					//��Ƕ����꣬intUnitNum����Ԥ��
	double * dblZBEccA;					//��Ƕ����꣬intUnitNum����Ԥ��
	vector<string> sCellName;				//CellName��intUnitNum����Ԥ��


	int		intAllUnit;
	int		intNeedFile;
	int		intUnitNum;					//ʵ�ʵ�Ԫ������Ч�����
	int		intSolidNum;				//ʵ��Q��Ԫ������Ч�����
	int		intQNum0;
	int		intQNum;				//�ο���Ԫ��
	int		intPNum;				//������Ԫ��
	int		intLightNum;				//ʵ���ҵ��ĵ���
	int		intMemAlloc;				//�������ļ�����������������ڷ����ڴ�
	int		intUnitTotal;					//��Ԫ��������Ч�����
	int		intRepeatTimes;				//�����ظ�����

	double	dblCenterX[5], dblCenterY[5],dblXiangX[5],dblXiangY[5],dblXiangA[5],dblBiliX[5],dblBiliY[5];	//����ƫ��
	int		intCCDNo;						//CCD���
	int		intImageWidth,intImageHeight;	//ͼ���С
	int		intWndSize;						//���㴰��С
	int		intBKThreshold;					//����ֵ
	int		intLightThreshold;				//����ż�ֵ

	
	int		m_nDui[3][2000];


	double* FFCircleX;//txt�ļ���ȡ�������
	double* FFCircleY;
	double FFCMax = 85;//FFԲ���̽��뾶
	double FFCMin = 74;//FFԲ��С̽��뾶
	double pixcelDisThreshold = 10.0; //Qֵ�ж���ȷ���ƥ�����
	double* FFSingeX;
	double* FFSingeY;
	double* centerX;//FFԲ����������
	double* centerY;
	double* radius;//�뾶
	double* centerUmX; //FFԲ��΢������
	double* centerUmY;

	void CircleFitting(double* FFSingeX, double* FFSingeY, double* centerX, double* centerY, double* radius);//�ο�����Բ�����
	void FindQ();
	int biaoding = 20;//�궨����
	double* paramX;
	double* paramY;

	double* FFLilunX;
	double* FFLilunY;
	void LSeekFiber::NiheParamCpp(int biaoding);
	void LSeekFiber::PixelToMicron(int biaoding);

	void LSeekFiber::WriteMicronTxtData(CString path);

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSEEKFIBER_H__8A300018_A752_4758_9892_FE28DE21F58C__INCLUDED_)
