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
	void TxtReadQ(CString fn);//txt中寻找Q坐标 为参数拟合做准备
	BOOL SeekPoints(CString strFileName);
	BOOL SeekPointsTxt(CString strFileName);
	void LSeekFiber::NiheParam(CString strFileName);
	int		m_nTop;
	int		m_nBottom;

protected:
	BOOL MemAlloc();
	void MemRelease();

	BOOL GetConfig();		//读取config.ini

	BOOL GetFFLilun(); //讀取FF理論

	BOOL ReadZBdata(CString strFileName);
	BOOL ReadRawData(CString strFileName);

	void SortPoints2();
	void SortPoints();
	void CaliPoints();
	BOOL WriteTxtData(CString strFileName);

	unsigned short * lpRawBuffer;		//从raw文件读的数据
	double	dblCaliFactor[2][15];		//标定系数
	double*	dblX;						//点像素坐标,intLightNum个
	double* dblY;						//点像素坐标,intLightNum个
	double* dblX1;						//排序后点像素坐标,intLightNum个或intUnitNum个
	double* dblY1;						//排序后点像素坐标,intLightNum个或intUnitNum个
	double*	dblCoorX;					//点坐标,intLightNum个
	double* dblCoorY;					//点坐标,intLightNum个
	double* dblCoorX1;					//排序后点坐标,intLightNum个或intUnitNum个
	double* dblCoorY1;					//排序后点坐标,intLightNum个或intUnitNum个
	double* dblDist;					//距离矩阵
	double* dblDist1;					//距离矩阵
	int*	dblDistM;					//距离矩阵
	int*	dblDistN;					//距离矩阵
	BOOL*	bFlag1;						//标记
	BOOL*	bFlag2;						//标记
	int*	intMM;						//光点最大值,intLightNum个
	int*	intMM1;						//光点最大值,intLightNum个
	int*	intNum;						//光点像素数,intLightNum个
	int*	intNum1;						//光点像素数,intLightNum个

	//double* dblPCoorX;				//工作光纤理论坐标，intPNum个，预存
	//double* dblPCoorY;				//工作光纤理论坐标，intPNum个，预存
	//double* dblPCenA;					//工作光纤点角度坐标，intPNum个，预存
	//double* dblPEccA;					//工作光纤点角度坐标，intPNum个，预存

	/// <summary>
	/// dsp add
	/// </summary>
	double* pixelPCoorX;					//工作光纤点角度坐标，intPNum个，预存
	double* pixelPCoorY;					//工作光纤点角度坐标，intPNum个，预存
	double* micronPCoorX;					//工作光纤点微米坐标，intPNum个，预存
	double* micronPCoorY;					//工作光纤点微米坐标，intPNum个，预存
	double* micronQCoorX;					//参考光纤点微米坐标，intQNum个，预存
	double* micronQCoorY;					//参考光纤点微米坐标，intQNum个，预存
	double* dblQCoorX;				//参考光纤理论坐标，intQNum个，预存
	double* dblQCoorY;				//参考光纤理论坐标，intQNum个，预存
	double* dblQCenA;					//参考光纤点角度坐标，intQNum个，预存
	double* dblQEccA;					//参考光纤点角度坐标，intQNum个，预存
	double* pixelQCoorX;			//参考光纤像素坐标，intQNum个，预存
	double* pixelQCoorY;			//参考光纤像素坐标，intQNum个，预存
	vector<string> sCellNameQ;				//CellName，intUnitNum个，预存
	vector<string> sCellNameP;				//CellName，intUnitNum个，预存
	double* temp;

	double * dblZBCoorX;				//理论坐标，intUnitNum个，预存
	double * dblZBCoorY;				//理论坐标，intUnitNum个，预存
	double * dblZBCenA;					//点角度坐标，intUnitNum个，预存
	double * dblZBEccA;					//点角度坐标，intUnitNum个，预存
	vector<string> sCellName;				//CellName，intUnitNum个，预存


	int		intAllUnit;
	int		intNeedFile;
	int		intUnitNum;					//实际单元数，有效光点数
	int		intSolidNum;				//实际Q单元数，有效光点数
	int		intQNum0;
	int		intQNum;				//参考单元数
	int		intPNum;				//工作单元数
	int		intLightNum;				//实际找到的点数
	int		intMemAlloc;				//从配置文件读的最大光点数，用于分配内存
	int		intUnitTotal;					//单元总数，有效光点数
	int		intRepeatTimes;				//拍摄重复次数

	double	dblCenterX[5], dblCenterY[5],dblXiangX[5],dblXiangY[5],dblXiangA[5],dblBiliX[5],dblBiliY[5];	//坐标偏移
	int		intCCDNo;						//CCD编号
	int		intImageWidth,intImageHeight;	//图象大小
	int		intWndSize;						//计算窗大小
	int		intBKThreshold;					//背景值
	int		intLightThreshold;				//光点门槛值

	
	int		m_nDui[3][2000];


	double* FFCircleX;//txt文件读取大概坐标
	double* FFCircleY;
	double FFCMax = 85;//FF圆最大探查半径
	double FFCMin = 74;//FF圆最小探查半径
	double pixcelDisThreshold = 10.0; //Q值判断正确与粗匹配距离
	double* FFSingeX;
	double* FFSingeY;
	double* centerX;//FF圆心像素坐标
	double* centerY;
	double* radius;//半径
	double* centerUmX; //FF圆心微米坐标
	double* centerUmY;

	void CircleFitting(double* FFSingeX, double* FFSingeY, double* centerX, double* centerY, double* radius);//参考光纤圆形拟合
	void FindQ();
	int biaoding = 20;//标定参数
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
