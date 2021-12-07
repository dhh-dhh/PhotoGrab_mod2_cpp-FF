// SeekFiber.cpp : Defines the class behaviors for the application.
//
#include <Eigen/Dense>
//using Eigen::MatrixXd;
using namespace Eigen;
using namespace Eigen::internal;
using namespace Eigen::Architecture;

#include "stdafx.h"
#include "LSeekFiber.h"

#include <iostream>
#include "math.h"
#include <string>
#include <fstream>
#include <vector> 
#include <set>
#include <algorithm>
#include<numeric>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#ifndef FFLILUNPATH		
#define FFLILUNPATH "F:\\Paohe\\bin\\FFLilun.txt"	 //參考光纖理論位置
#endif	
#ifndef FFCIRCLEPATH		
#define FFCIRCLEPATH "F:\\Paohe\\bin\\FFCircle.txt" //FFCircle file path	 //參考光纖像素位置
#endif	


/////////////////////////////////////////////////////////////////////////////
// LSeekFiber construction

LSeekFiber::LSeekFiber()
{
	intUnitNum=0;
	intSolidNum=0;
	intLightNum=0;//实际找到的点数
	intMemAlloc=0;//从配置文件读的点数，用于分配内存
	intUnitTotal=0;
	intRepeatTimes=0;

	for(int i=0;i<5;i++)
	{
		dblCenterX[i]=0;
		dblCenterY[i]=0;
		dblXiangX[i]=0;
		dblXiangY[i]=0;
		dblXiangA[i]=0;
		dblBiliX[i]=0;
		dblBiliY[i]=0;
	}
	intImageWidth=0;
	intImageHeight=0;
	intWndSize=0;
	intBKThreshold=0;
	intLightThreshold=0;
}

LSeekFiber::~LSeekFiber()
{
}

void LSeekFiber::Close()
{
	MemRelease();
}

/////////////////////////////////////////////////////////////////////////////
// LSeekFiber initialization

BOOL LSeekFiber::Init()
{
	if (!GetConfig())
	{
		AfxMessageBox(_T("Failed to read config file."));
		return FALSE;
	}
	if (!MemAlloc())
	{
		AfxMessageBox(_T("Failed to allocate memory."));
		return FALSE;
	}
	//if (!Py_IsInitialized())
	//{
	//  AfxMessageBox(_T("Failed to Py_IsInitialized."));
	//	return FALSE;
	//}
	if (!GetFFLilun())
	{
		AfxMessageBox(_T("Failed to read FFLilun file."));
		return FALSE;
	}

	
	return TRUE;
}

BOOL LSeekFiber::GetFFLilun() //放入相機初始化中
{
	//char* FFLiLunPath;
	//FFLiLunPath = "F:\\Paohe\\bin\\FFLilun.txt";//FFCircle file path
	FILE* FFLiLunFile;
	if ((FFLiLunFile = fopen(FFLILUNPATH, "rt")) <= 0)//open file
	{
		return false;
	}
	//fscanf(FFCFile, "%lf", &FFNum);
	char c;
	char buf[100] = { 0 };
	int numQL = 0;
	while (!feof(FFLiLunFile))
	{
		fscanf_s(FFLiLunFile, "%lf %lf", &FFLilunX[numQL], &FFLilunY[numQL]);//读取Q的理论坐标
		numQL++;
		//fgets(buf, 100, FFLiLunFile);
		c = fgetc(FFLiLunFile);//防止多读一次

	}
	fclose(FFLiLunFile);

	//double test1;
	//double test2;
	//for (int i = 0; i < numQL; i++)
	//{
	//	test1 = FFLilunX[i];
	//	test2 = FFLilunY[i];
	//}
	return true;
}

BOOL LSeekFiber::MemAlloc()
{
	lpRawBuffer = new unsigned short[intImageWidth*intImageHeight];
	if (!lpRawBuffer)return FALSE;
	dblX = new double[intMemAlloc];
	if (!dblX)return FALSE;
	dblY = new double[intMemAlloc];
	if (!dblY)return FALSE;
	dblX1 = new double[intMemAlloc];
	if (!dblX1)return FALSE;
	dblY1 = new double[intMemAlloc];
	if (!dblY1)return FALSE;
	dblCoorX = new double[intMemAlloc];
	if (!dblCoorX)return FALSE;
	dblCoorY = new double[intMemAlloc];
	if (!dblCoorY)return FALSE;
	dblCoorX1 = new double[intMemAlloc];
	if (!dblCoorX1)return FALSE;
	dblCoorY1 = new double[intMemAlloc];
	if (!dblCoorY1)return FALSE;
	dblDist=new double[intMemAlloc*intMemAlloc];
	if (!dblDist)return FALSE;
	dblDist1=new double[intMemAlloc*intMemAlloc];
	if (!dblDist1)return FALSE;
	dblDistM=new int[intMemAlloc*intMemAlloc];
	if (!dblDistM)return FALSE;
	dblDistN=new int[intMemAlloc*intMemAlloc];
	if (!dblDistN)return FALSE;
	bFlag1=new BOOL[intMemAlloc];
	if (!bFlag1)return FALSE;
	bFlag2=new BOOL[intMemAlloc];
	if (!bFlag2)return FALSE;
	intMM = new int[intMemAlloc];
	if (!intMM)return FALSE;
	intMM1 = new int[intMemAlloc];
	if (!intMM1)return FALSE;
	intNum = new int[intMemAlloc];
	if (!intNum)return FALSE;
	intNum1 = new int[intMemAlloc];
	if (!intNum1)return FALSE;

	dblZBCoorX = new double[intMemAlloc];
	if (!dblZBCoorX)return FALSE;
	dblZBCoorY = new double[intMemAlloc];
	if (!dblZBCoorY)return FALSE;
	dblZBCenA = new double[intMemAlloc];
	if (!dblZBCenA)return FALSE;
	dblZBEccA = new double[intMemAlloc];
	if (!dblZBEccA)return FALSE;
	//dsp add python
	pixelPCoorX = new double[intMemAlloc];
	if (!pixelPCoorX)return FALSE;
	pixelPCoorY = new double[intMemAlloc];
	if (!pixelPCoorY)return FALSE;
	micronPCoorX = new double[intMemAlloc];
	if (!micronPCoorX)return FALSE;
	micronPCoorY = new double[intMemAlloc];
	if (!micronPCoorY)return FALSE;

	dblQCoorX = new double[intMemAlloc];
	if (!dblQCoorX)return FALSE;
	dblQCoorY = new double[intMemAlloc];
	if (!dblQCoorY)return FALSE;
	dblQCenA = new double[intMemAlloc];
	if (!dblQCenA)return FALSE;
	dblQEccA = new double[intMemAlloc];
	if (!dblQEccA)return FALSE;
	pixelQCoorX = new double[intMemAlloc];
	if (!pixelQCoorX)return FALSE;
	pixelQCoorY = new double[intMemAlloc];
	if (!pixelQCoorY)return FALSE;
	temp = new double[intMemAlloc];
	if (!temp)return FALSE;

	//FF
	FFCircleX = new double[intMemAlloc];
	if (!FFCircleX)return FALSE;
	FFCircleY = new double[intMemAlloc];
	if (!FFCircleY)return FALSE;
	FFSingeX = new double[intMemAlloc];
	if (!FFSingeX)return FALSE;
	FFSingeY = new double[intMemAlloc];
	if (!FFSingeY)return FALSE;
	centerX = new double[intMemAlloc];
	if (!centerX)return FALSE;
	centerY = new double[intMemAlloc];
	if (!centerY)return FALSE;
	radius = new double[intMemAlloc];
	if (!radius)return FALSE;
	centerUmX = new double[intMemAlloc];
	if (!centerUmX)return FALSE;
	centerUmY = new double[intMemAlloc];
	if (!centerUmY)return FALSE;

	paramX = new double[intMemAlloc];
	if (!paramX)return FALSE;
	paramY = new double[intMemAlloc];
	if (!paramY)return FALSE;

	FFLilunX = new double[intMemAlloc];
	if (!FFLilunX)return FALSE;
	FFLilunY = new double[intMemAlloc];
	if (!FFLilunY)return FALSE;
	micronQCoorX = new double[intMemAlloc];
	if (!micronQCoorX)return FALSE;
	micronQCoorY = new double[intMemAlloc];
	if (!micronQCoorY)return FALSE;

	//Py_SetPythonHome(L"D:\\anaconda");  //系统的python路径
	//Py_Initialize();			//使用python之前，要调用Py_Initialize();这个函数进行初始化 

	//double* pixelPCoorX;					//工作光纤点角度坐标，intPNum个，预存
	//double* pixelPCoorY;					//工作光纤点角度坐标，intPNum个，预存
	//double* dblQCoorX;				//参考光纤理论坐标，intQNum个，预存
	//double* dblQCoorY;				//参考光纤理论坐标，intQNum个，预存
	//double* dblQCenA;					//参考光纤点角度坐标，intQNum个，预存
	//double* dblQEccA;					//参考光纤点角度坐标，intQNum个，预存
	//double* pixelQCoorX;			//参考光纤像素坐标，intQNum个，预存
	//double* pixelQCoorY;			//参考光纤像素坐标，intQNum个，预存
	//vector<string> sCellNameQ;				//CellName，intUnitNum个，预存
	//vector<string> sCellNameP;				//CellName，intUnitNum个，预存

//	sCellName = new char[20*intMemAlloc];
//	if (!sCellName)return FALSE;
	return TRUE;
}

void LSeekFiber::MemRelease()
{
//	if (sCellName)delete [] sCellName;
	if (dblZBCenA)delete [] dblZBCenA;
	if (dblZBEccA)delete [] dblZBEccA;
	if (dblZBCoorX)delete [] dblZBCoorX;
	if (dblZBCoorY)delete [] dblZBCoorY;
	if (intNum1)delete [] intNum1;
	if (intNum)delete [] intNum;
	if (intMM1)delete [] intMM1;
	if (intMM)delete [] intMM;
	if (bFlag1)delete [] bFlag1;
	if (bFlag2)delete [] bFlag2;
	if (dblDist)delete [] dblDist;
	if (dblDist1)delete [] dblDist1;
	if (dblDistM)delete [] dblDistM;
	if (dblDistN)delete [] dblDistN;
	if (dblCoorX1)delete [] dblCoorX1;
	if (dblCoorY1)delete [] dblCoorY1;
	if (dblCoorX)delete [] dblCoorX;
	if (dblCoorY)delete [] dblCoorY;
	if (dblX1)delete [] dblX1;
	if (dblY1)delete [] dblY1;
	if (dblX)delete [] dblX;
	if (dblY)delete [] dblY;
	if (lpRawBuffer)delete [] lpRawBuffer;

	if (pixelPCoorX)delete[] pixelPCoorX;
	if (pixelPCoorY)delete[] pixelPCoorY;
	if (micronPCoorX)delete[] micronPCoorX;
	if (micronPCoorY)delete[] micronPCoorY;

	if (dblQCoorX)delete[] dblQCoorX;
	if (dblQCoorY)delete[] dblQCoorY;
	if (dblQCenA)delete[] dblQCenA;
	if (dblQEccA)delete[] dblQEccA;
	if (pixelQCoorX)delete[] pixelQCoorX;
	if (pixelQCoorY)delete[] pixelQCoorY;
	if (temp)delete[] temp;
	
	//Py_Finalize(); //释放资源 (已转移)
	//Py_Finalize(); //释放资源 (已转移)


	//FF
	if (FFCircleX)delete[] FFCircleX;
	if (FFCircleY)delete[] FFCircleY;
	if (FFSingeX)delete[] FFSingeX;
	if (FFSingeY)delete[] FFSingeY;
	if (centerX)delete[] centerX;
	if (centerY)delete[] centerY;
	if (radius)delete[] radius;
	if (centerUmX)delete[] centerUmX;
	if (centerUmY)delete[] centerUmX;
	if (paramX)delete[] paramX;
	if (paramY)delete[] paramY;

	if (FFLilunX)delete[] FFLilunX;
	if (FFLilunY)delete[] FFLilunY;
	if (micronQCoorX)delete[] micronQCoorX;
	if (micronQCoorY)delete[] micronQCoorY;
	
}

BOOL LSeekFiber::GetConfig()
{
	//得到配置文件名
	CString strFilename;
	strFilename=CFG_DIR;
	strFilename+="\\config.ini";

	//读配置
	char lpBuffer[50];
	TCHAR LpBuffer[100];
	GetPrivateProfileString(L"SYSTEM", L"CCD_No", L"0", LpBuffer, 100, strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer,50,NULL,FALSE);
	intCCDNo=atoi(lpBuffer);
	CString strCaliFactorFilename;		//lwm标定文件名
	GetPrivateProfileString(L"SYSTEM",L"cali_factors",L"",LpBuffer,100,strFilename);
	strCaliFactorFilename.Format(LpBuffer,intCCDNo);
	GetPrivateProfileString(L"SYSTEM",L"allunit",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	intAllUnit=atoi(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"needfile",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	intNeedFile=atoi(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"max_light_point_num",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	intMemAlloc=atoi(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"all_unit_num",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	intUnitTotal=atoi(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"repeat_times",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	intRepeatTimes=atoi(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"center_x0",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblCenterX[0]=atof(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"center_y0",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblCenterY[0]=atof(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"xiang_x0",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblXiangX[0]=atof(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"xiang_y0",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblXiangY[0]=atof(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"xiang_a0",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblXiangA[0]=atof(lpBuffer)*3.1415926/60/180;
	GetPrivateProfileString(L"SYSTEM",L"bili_x0",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblBiliX[0]=atof(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"bili_y0",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblBiliY[0]=atof(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"center_x1",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblCenterX[1]=atof(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"center_y1",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblCenterY[1]=atof(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"center_a1",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblXiangA[1]=atof(lpBuffer)*3.1415926/60/180;
	GetPrivateProfileString(L"SYSTEM",L"center_x2",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblCenterX[2]=atof(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"center_y2",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblCenterY[2]=atof(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"center_a2",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblXiangA[2]=atof(lpBuffer)*3.1415926/60/180;
	GetPrivateProfileString(L"SYSTEM",L"center_x3",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblCenterX[3]=atof(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"center_y3",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblCenterY[3]=atof(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"center_a3",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblXiangA[3]=atof(lpBuffer)*3.1415926/60/180;
	GetPrivateProfileString(L"SYSTEM",L"center_x4",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblCenterX[4]=atof(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"center_y4",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblCenterY[4]=atof(lpBuffer);
	GetPrivateProfileString(L"SYSTEM",L"center_a4",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	dblXiangA[4]=atof(lpBuffer)*3.1415926/60/180;
	GetPrivateProfileString(L"CALC",L"image_pixel_w",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	intImageWidth=atoi(lpBuffer);
	GetPrivateProfileString(L"CALC",L"image_pixel_h",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	intImageHeight=atoi(lpBuffer);
	GetPrivateProfileString(L"CALC",L"window_size",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	intWndSize=atoi(lpBuffer);
	GetPrivateProfileString(L"CALC",L"image_background_threshold_value",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	intBKThreshold=atoi(lpBuffer);
	GetPrivateProfileString(L"CALC",L"light_threshold",L"",LpBuffer,100,strFilename);
	WideCharToMultiByte(CP_OEMCP, 0, LpBuffer, -1, lpBuffer, 50, NULL, FALSE);
	intLightThreshold=atoi(lpBuffer);

	//读标定系数
	CFile file;
	CFileException e;
	char chrBuffer[1024];
	if(!file.Open(strCaliFactorFilename,CFile::modeRead,&e))
	{
		AfxMessageBox(_T("Failed to read calibration factor file."));
		return FALSE;
	}
	file.Seek(0L,CFile::begin);
	if(!file.Read(chrBuffer,1024))
	{
		AfxMessageBox(_T("Failed to read calibration factor file."));
		file.Close();
		return FALSE;
	}
	sscanf_s(chrBuffer," %le  %le  %le  %le  %le  %le  %le  %le  %le  %le  %le  %le  %le  %le  %le\r\n %le  %le  %le  %le  %le  %le  %le  %le  %le  %le  %le  %le  %le  %le  %le\r\n",
		&dblCaliFactor[0][0],&dblCaliFactor[0][1],&dblCaliFactor[0][2],&dblCaliFactor[0][3],&dblCaliFactor[0][4],&dblCaliFactor[0][5],&dblCaliFactor[0][6],&dblCaliFactor[0][7],&dblCaliFactor[0][8],&dblCaliFactor[0][9],&dblCaliFactor[0][10],&dblCaliFactor[0][11],&dblCaliFactor[0][12],&dblCaliFactor[0][13],&dblCaliFactor[0][14],
		&dblCaliFactor[1][0],&dblCaliFactor[1][1],&dblCaliFactor[1][2],&dblCaliFactor[1][3],&dblCaliFactor[1][4],&dblCaliFactor[1][5],&dblCaliFactor[1][6],&dblCaliFactor[1][7],&dblCaliFactor[1][8],&dblCaliFactor[1][9],&dblCaliFactor[1][10],&dblCaliFactor[1][11],&dblCaliFactor[1][12],&dblCaliFactor[1][13],&dblCaliFactor[1][14]);
	file.Close();

	return TRUE;
}
BOOL LSeekFiber::SeekPoints(CString fn)  //计算所有光点的像素坐标
{
#define MAP(i,j) lpRawBuffer[(i)*intImageHeight+ (j)]

	
	if (!ReadZBdata(fn))	return FALSE;

	int p,q,g;
	int i,j,m,m1,m2,n,n1,n2,mm;
	double sumRow,sumCol,SumGray;
	int intCounter=-1;
	CString rawfn,ss,str;
	for(int rep=0;rep<intRepeatTimes;rep++)
	{
		ss.Format(_T("%02d.raw"),rep);
		rawfn=fn.Left(fn.GetLength() - 6)+ss;
		if (!ReadRawData(rawfn))	return FALSE;

		ZeroMemory(dblCoorX,intMemAlloc*8);//it's essential
		ZeroMemory(dblCoorY,intMemAlloc*8);//it's essential
		ZeroMemory(dblX,intMemAlloc*8);//it's essential
		ZeroMemory(dblY,intMemAlloc*8);//it's essential
		ZeroMemory(intMM,intMemAlloc*4);//it's essential
		ZeroMemory(intMM1,intMemAlloc*4);//it's essential
		ZeroMemory(intNum,intMemAlloc*4);//it's essential
		ZeroMemory(intNum1,intMemAlloc*4);//it's essential

		intCounter=0;

		//阈值筛选
		long long meanGray = 0;
		for (int row = 0; row < intImageWidth; ++row)
		{
			for (int col = 0; col < intImageHeight; ++col)
			{
				int t = MAP(row, col);
				meanGray += MAP(row, col);
			}
		}
		meanGray /= (intImageWidth * intImageHeight);
		//int meanGray1 = std::accumulate(lpRawBuffer.begin(), lpRawBuffer.end(), 0)/ (intImageWidth * intImageHeight);

		intBKThreshold = max((int)(meanGray * 1.2), intBKThreshold);
		intLightThreshold = max(intBKThreshold,min((int)(meanGray * 4), intLightThreshold));
		

		for (i = 0; i < intImageWidth; i++)
		{
			for (j = 0; j<intImageHeight; j++)
			{
				if (MAP(i, j)>intLightThreshold)//可能存在一个亮点
				{
					sumRow = 0; sumCol = 0; SumGray = 0;

					m_nTop = 0;
					m_nBottom = 0;
					mm = 0;
					m_nDui[0][m_nBottom] = i;
					m_nDui[1][m_nBottom] = j;
					m_nDui[2][m_nBottom] = MAP(i, j);
					MAP(i, j) = 0;
					m_nBottom++; if (m_nBottom >= 2000)m_nBottom = 0;

					while (m_nTop != m_nBottom)
					{
						p = m_nDui[0][m_nTop];
						q = m_nDui[1][m_nTop];
						g = m_nDui[2][m_nTop];
						if (mm < g)mm = g;
						sumRow += p * g;
						sumCol += q * g;
						SumGray += g;
						m_nTop++; if (m_nTop >= 2000)m_nTop = 0;

						m1 = p - 1;	if (m1 < 0)m1 = 0;
						m2 = p + 1; if (m2 >= intImageWidth)m2 = intImageWidth - 1;
						n1 = q - 1;	if (n1<0)n1 = 0;
						n2 = q + 1;	if (n2 >= intImageHeight)n2 = intImageHeight - 1;
						for (m = m1; m <= m2; m++)
						for (n = n1; n <= n2; n++)
						if (MAP(m, n)>intBKThreshold)
						{
							m_nDui[0][m_nBottom] = m;
							m_nDui[1][m_nBottom] = n;
							m_nDui[2][m_nBottom] = MAP(m, n);
							MAP(m, n) = 0;
							m_nBottom++; if (m_nBottom >= 2000)m_nBottom = 0;
						}
					}
					//ASSERT(SumGray > 0);//正常情况下分母不会为0
					if (m_nTop > 6)
					{
						// + 1是为了和matlab一致，坐标从1开始
						dblCoorY[intCounter] = intImageWidth/2-(sumRow / SumGray + 1);//y
						dblCoorX[intCounter] = sumCol / SumGray + 1 - intImageHeight/2;//x
						intMM[intCounter] = mm;//mm
						intNum[intCounter] = m_nTop ;//mm
						intCounter++;
					}
					
				}

				//就要超出内存分配限制了，中止循环
				if (intCounter >= intMemAlloc)
				{
					i = intImageWidth;
					j = intImageHeight;
				}
			}
		}
		intLightNum = intCounter;//实际的点数

		//SortPoints();
		//从 circle txt文件找到像素坐标，进行圆心拟合，结果存放在变量 &centerX[i], &centerY[i] 中
		FindQ();
		//像素坐标进行粗匹配参数（5参数）匹配
		CaliPoints();
		SortPoints2(); //排序计算
		str =(LPCSTR)(rawfn.Left(rawfn.GetLength() - 4) + ".txt");
		//写匹配好的坐标文件 像素坐标
		WriteTxtData(str);
		//TxtReadQ(str);

		//实现读取txt中像素坐标与单元号 与Q的（參與匹配的）理论坐标
		TxtReadQ(str);
		//计算参数文件
		NiheParamCpp(biaoding);
		//P坐标转换为微米坐标
		PixelToMicron(biaoding);
		//写最终文件
		WriteMicronTxtData(str);
	}

	return TRUE;
}

//计算参数文件
void LSeekFiber::NiheParamCpp(int biaoding)
{
	int Num = intQNum;
	//进一步筛选Q值，防止参数拟合错误
	//vector<double> dis(intQNum, 0);
	//double pixcelDisThreshold = 50.0;
	for (int i = 0; i < intQNum; i++)
	{
		//dis[i]=sqrt((FFCircleX[i]- pixelQCoorX[i])* (FFCircleX[i] - pixelQCoorX[i])+ (FFCircleY[i]- pixelQCoorY[i])* (FFCircleY[i] - pixelQCoorY[i]));
		if (radius[i] == -1.0)
		{
			Num--;
		}
	}
	
	MatrixXd x(Num, 1);
	MatrixXd y(Num, 1);
	MatrixXd lilun_x(Num, 1);
	MatrixXd lilun_y(Num, 1);
	MatrixXd paramX_array(Num, 1);
	MatrixXd paramY_array(Num, 1);

	MatrixXd A(biaoding/2, biaoding/2);
	MatrixXd BX(biaoding/2, 1);
	MatrixXd BY(biaoding/2, 1);

	for (int i = 0,j=0; i < intQNum; i++)
	{
		if (radius[i] == -1.0)
		{
			continue;
		}
		else
		{
			x(j, 0) = pixelQCoorX[i];
			y(j, 0) = pixelQCoorY[i];
			lilun_x(j, 0) = FFLilunX[i];
			lilun_y(j, 0) = FFLilunY[i];
			j++;
		}
		
		
		//lilun_x(i, 0) = dblQCoorX[i];
		//lilun_y(i, 0) = dblQCoorY[i];
		
		//double test3 = dblQCoorX[i];
		//double test4 = dblQCoorY[i];
		
		//double test1 = FFLilunX[i];
		//double test2 = FFLilunY[i];
	}

	if (biaoding == 6)
	{
	
		A << Num, x.sum(), y.sum(),
			x.sum(), (x.array() * x.array()).sum(), (x.array() *y.array()).sum(),
			y.sum(), (y.array() *x.array()).sum(), (y.array() *y.array()).sum();

		BX <<(lilun_x).sum(),
			(lilun_x.array() *x.array()).sum(),
			(lilun_x.array() *y.array()).sum();

		BY <<(lilun_y).sum(),
			(lilun_y.array() *x.array()).sum(),
			(lilun_y.array() *y.array()).sum();
		
	}
	if (biaoding == 20)
	{
		//MatrixXd test1(1, 1);
		//test1 << (lilun_x.array() * x.array() * x.array()).sum() ;
		//MatrixXd test2(1, 1);
		//test2 << (lilun_x.array() * (x.array().cube()).array()).sum();
		//MatrixXd test3(1, 1);
		//test3 << (lilun_x.array() * x.array() * x.array() * y.array()).sum();
		//MatrixXd test4(1, 1);
		//test4 << (lilun_x.array() * (y.array().cube()).array());
		//MatrixXd test5(1, 1);
		//test5 << (lilun_x.array() * (x.array().cube()).array()).sum();

		BX << (lilun_x).sum(),
			(lilun_x.array() * x.array()).sum(),
			(lilun_x.array() * y.array()).sum(),
			(lilun_x.array() * x.array() * x.array()).sum(),
			(lilun_x.array() * x.array() * y.array()).sum(),
			(lilun_x.array() * y.array() * y.array()).sum(),
			(lilun_x.array() * (x.array().cube()).array()).sum(),
			(lilun_x.array() * x.array() * x.array() * y.array()).sum(),
			(lilun_x.array() * x.array() * y.array() * y.array()).sum(),
			(lilun_x.array() * (y.array().cube()).array()).sum();

		BY << (lilun_y).sum(),
			(lilun_y.array() * x.array()).sum(),
			(lilun_y.array() * y.array()).sum(),
			(lilun_y.array() * x.array() * x.array()).sum(),
			(lilun_y.array() * x.array() * y.array()).sum(),
			(lilun_y.array() * y.array() * y.array()).sum(),
			(lilun_y.array() * (x.array().cube()).array()).sum(),
			(lilun_y.array() * x.array() * x.array() * y.array()).sum(),
			(lilun_y.array() * x.array() * y.array() * y.array()).sum(),
			(lilun_y.array() * (y.array().cube()).array()).sum();

		A << Num, x.sum(), y.sum(), (x.array()*x.array()).sum(), (x.array()*y.array()).sum(), (y.array() *y.array()).sum(), (x.array().cube() ).sum(), (x.array().square().array() * y.array()).sum(), (y.array().square().array() * x.array()).sum(), (y.array().cube() ).sum(),
			x.sum(), (x.array() *x.array()).sum(), (x.array() *y.array()).sum(), (x.array().cube() ).sum(), ((x.array().square()).array() *y.array()).sum(), ((y.array().square()).array() *x.array()).sum(), (x.array().pow(4)).sum(), (x.array().cube().array() * y.array()).sum(), (x.array().square().array() * y.array().square().array()).sum(), (x.array() *y.array().cube().array()).sum(),
			y.sum(), (y.array() *x.array()).sum(), (y.array() *y.array()).sum(), ((x.array().square()).array() *y.array()).sum(), (x.array() *(y.array().square()).array()).sum(), (y.array().cube()).sum(), (x.array().cube().array() * y.array()).sum(), (x.array().square().array() * y.array().square().array()).sum(), (x.array() *(y.array().cube()).array()).sum(), (y.array().pow(4)).sum(),
			(x.array() *x.array()).sum(), (x.array().cube() ).sum(), ((x.array().square()).array() *y.array()).sum(), (x.array().pow(4)).sum(), ((x.array().cube() ).array() *y.array()).sum(), ((x.array().square()).array() *(y.array().square()).array()).sum(), (x.array().pow(5)).sum(), (x.array().pow(4).array() * y.array()).sum(), ((x.array().cube()).array() * (y.array().square()).array()).sum(), (x.array().square().array() * (y.array().cube()).array()).sum(),
			(x.array() *y.array()).sum(), ((x.array().square()).array() *(y.array()).array()).sum(), (x.array() *(y.array().square()).array()).sum(), ((x.array().cube() ).array() *y.array()).sum(), ((x.array().square()).array() *(y.array().square()).array()).sum(), (x.array() *(y.array().cube() ).array()).sum(), (x.array().pow(4).array() * y.array()).sum(), (x.array().cube().array() * (y.array().square()).array()).sum(), (x.array().square().array() * (y.array().cube()).array()).sum(), (x.array() *(y.array().pow(4)).array()).sum(),
			(y.array() *y.array()).sum(), ((y.array().square()).array() * x.array()).sum(), (y.array().cube() ).sum(), ((x.array().square()).array() *(y.array().square()).array()).sum(), ((y.array().cube() ).array() *x.array()).sum(), (y.array().pow(4)).sum(), (x.array().cube().array() * (y.array().square()).array()).sum(), (x.array().square().array() * (y.array().cube()).array()).sum(), (x.array() *(y.array().pow(4)).array()).sum(), (y.array().pow(5)).sum(),
			(x.array().cube() ).sum(), (x.array().pow(4)).sum(), ((x.array().cube() ).array() *y.array()).sum(), (x.array().pow(5)).sum(), (x.array().pow(4).array() * y.array()).sum(), ((x.array().cube()).array() * (y.array().square()).array()).sum(), (x.array().pow(6)).sum(), (x.array().pow(5).array() * y.array()).sum(), ((x.array().pow(4)).array() * (y.array().square()).array()).sum(), ((x.array().cube()).array() * (y.array().cube()).array()).sum(),
			((x.array().square()).array() *(y.array())).sum(), ((x.array().cube() ).array() *y.array()).sum(), ((x.array().square()).array() *(y.array().square()).array()).sum(), (x.array().pow(4).array() * y.array()).sum(), (x.array().cube().array() * (y.array().square()).array()).sum(), (x.array().square().array() * (y.array().cube()).array()).sum(), (x.array().pow(5).array() * y.array()).sum(), (x.array().pow(4).array() * (y.array().square()).array()).sum(), (x.array().cube().array() * (y.array().cube()).array()).sum(), (x.array().square().array() * (y.array().pow(4)).array()).sum(),
			(x.array() *(y.array().square()).array()).sum(), ((x.array().square()).array() *(y.array().square()).array()).sum(), (x.array() *(y.array().cube() ).array()).sum(), (x.array().cube().array() * y.array().square().array()).sum(), (x.array().square().array() * (y.array().cube()).array()).sum(), (x.array() *(y.array().pow(4)).array()).sum(), (x.array().pow(4).array() * (y.array().square()).array()).sum(), (x.array().cube().array() * (y.array().cube()).array()).sum(), (x.array().square().array() * (y.array().pow(4)).array()).sum(), (x.array() *(y.array().pow(5)).array()).sum(),
			(y.array().cube() ).sum(), (x.array().array() *(y.array().cube()).array()).sum(), (y.array().pow(4)).sum(), (x.array().square().array() * (y.array().cube()).array()).sum(), (x.array() *(y.array().pow(4)).array()).sum(), (y.array().pow(5)).sum(), (x.array().cube().array() * (y.array().cube()).array()).sum(), (x.array().square().array() * (y.array().pow(4)).array()).sum(), (x.array() *(y.array().pow(5)).array()).sum(), (y.array().pow(6)).sum();
	}

	paramX_array = A.inverse() * BX;
	paramY_array = A.inverse() * BY;

	for (int i = 0; i < biaoding / 2; i++)
	{
		double a = paramX_array(i, 0);
		double b = paramY_array(i, 0);
		paramX[i] = paramX_array(i,0);
		paramY[i] = paramY_array(i, 0);
	}
	return;
	
}

//P坐标转换为微米坐标
void LSeekFiber::PixelToMicron(int biaoding)
{

	/*三十个参数 */
	if (biaoding == 30)
	{
		/*
		*X=paramX[0]+paramX[1]*x+paramX[2]*y+paramX[3]*x*x+paramX[4]*x*y\
			+paramX[5]*y*y+paramX[6]*pow(x,3)+paramX[7]*pow(x,2)*y+paramX[8]*x*pow(y,2)\
			+paramX[9]*pow(y,3)+paramX[10]*pow(x,4)+paramX[11]*pow(x,3)*y+paramX[12]*pow(x,2)*pow(y,2)+paramX[13]*x*pow(y,3)+paramX[14]*pow(y,4);
		*Y=paramY[0]+paramY[1]*x+paramY[2]*y+paramY[3]*x*x+paramY[4]*x*y\
			+paramY[5]*y*y+paramY[6]*pow(x,3)+paramY[7]*pow(x,2)*y+paramY[8]*x*pow(y,2)\
			+paramY[9]*pow(y,3)+paramY[10]*pow(x,4)+paramY[11]*pow(x,3)*y+paramY[12]*pow(x,2)*pow(y,2)+paramY[13]*x*pow(y,3)+paramY[14]*pow(y,4);
		*X/=1000.0;
		*Y/=1000.0;
		*/
	}	
	//20个参数
	else if (biaoding == 20)
	{
		for (int i = 0; i < intPNum; i++)
		{
			micronPCoorX[i] = (paramX[0] + paramX[1] * pixelPCoorX[i] + paramX[2] * pixelPCoorY[i] + paramX[3] * pixelPCoorX[i] * pixelPCoorX[i] + paramX[4] * pixelPCoorX[i] * pixelPCoorY[i]\
				+ paramX[5] * pixelPCoorY[i] * pixelPCoorY[i] + paramX[6] * pow(pixelPCoorX[i], 3) + paramX[7] * pow(pixelPCoorX[i], 2) * pixelPCoorY[i] + paramX[8] * pixelPCoorX[i] * pow(pixelPCoorY[i], 2)\
				+ paramX[9] * pow(pixelPCoorY[i], 3));
			micronPCoorY[i] = (paramY[0] + paramY[1] * pixelPCoorX[i] + paramY[2] * pixelPCoorY[i] + paramY[3] * pixelPCoorX[i] * pixelPCoorX[i] + paramY[4] * pixelPCoorX[i] * pixelPCoorY[i]\
				+ paramY[5] * pixelPCoorY[i] * pixelPCoorY[i] + paramY[6] * pow(pixelPCoorX[i], 3) + paramY[7] * pow(pixelPCoorX[i], 2) * pixelPCoorY[i] + paramY[8] * pixelPCoorX[i] * pow(pixelPCoorY[i], 2)\
				+ paramY[9] * pow(pixelPCoorY[i], 3)) ;
		}
		for (int i = 0; i < intQNum; i++)
		{
			micronQCoorX[i] = (paramX[0] + paramX[1] * pixelQCoorX[i] + paramX[2] * pixelQCoorY[i] + paramX[3] * pixelQCoorX[i] * pixelQCoorX[i] + paramX[4] * pixelQCoorX[i] * pixelQCoorY[i]\
				+ paramX[5] * pixelQCoorY[i] * pixelQCoorY[i] + paramX[6] * pow(pixelQCoorX[i], 3) + paramX[7] * pow(pixelQCoorX[i], 2) * pixelQCoorY[i] + paramX[8] * pixelQCoorX[i] * pow(pixelQCoorY[i], 2)\
				+ paramX[9] * pow(pixelQCoorY[i], 3));
			micronQCoorY[i] = (paramY[0] + paramY[1] * pixelQCoorX[i] + paramY[2] * pixelQCoorY[i] + paramY[3] * pixelQCoorX[i] * pixelQCoorX[i] + paramY[4] * pixelQCoorX[i] * pixelQCoorY[i]\
				+ paramY[5] * pixelQCoorY[i] * pixelQCoorY[i] + paramY[6] * pow(pixelQCoorX[i], 3) + paramY[7] * pow(pixelQCoorX[i], 2) * pixelQCoorY[i] + paramY[8] * pixelQCoorX[i] * pow(pixelQCoorY[i], 2)\
				+ paramY[9] * pow(pixelQCoorY[i], 3));
		}
	}
	else if (biaoding == 6)
	{
		for (int i = 0; i < intPNum; i++)
		{
			micronPCoorX[i] = (paramX[0] + paramX[1] * pixelPCoorX[i] + paramX[2] * pixelPCoorY[i] + paramX[3] * pixelPCoorX[i] * pixelPCoorX[i] + paramX[4] * pixelPCoorX[i] * pixelPCoorY[i]\
				+ paramX[5] * pixelPCoorY[i] * pixelPCoorY[i]);
			micronPCoorY[i] = (paramY[0] + paramY[1] * pixelPCoorX[i] + paramY[2] * pixelPCoorY[i] + paramY[3] * pixelPCoorX[i] * pixelPCoorX[i] + paramY[4] * pixelPCoorX[i] * pixelPCoorY[i]\
				+ paramY[5] * pixelPCoorY[i] * pixelPCoorY[i] );
		}
	}
	return;
}

void LSeekFiber::WriteMicronTxtData(CString str) 
{
	USES_CONVERSION;
	CString path_Micron = (str.Left(str.GetLength() - 4) + "_xy.txt");
	LPCSTR Path_Micron = (LPCSTR)T2A(path_Micron);//转化CString到const char*

	int i;
	FILE* ff;
	errno_t err;
	err = fopen_s(&ff, Path_Micron, "w+");

	for (i = 0; i < intPNum; i++)
	{
		if (pixelPCoorX[i] == 0.0 && pixelPCoorY[i] == 0)
		{
			fprintf_s(ff, "%s\t%12.6f\t%12.6f\t%12.6f\t%12.6f\n", sCellNameP[i].c_str(), 0.0, 0.0, pixelPCoorX[i], pixelPCoorY[i]);
		}
		else
		{
			fprintf_s(ff, "%s\t%12.6f\t%12.6f\t%12.6f\t%12.6f\n", sCellNameP[i].c_str(), micronPCoorX[i], micronPCoorY[i], pixelPCoorX[i], pixelPCoorY[i]);
		}
		
	}
	for (i=0; i < intQNum; i++)
	{
		double dis = sqrt((micronQCoorX[i] - FFLilunX[i]) * (micronQCoorX[i] - FFLilunX[i]) + (micronQCoorY[i] - FFLilunY[i]) * (micronQCoorY[i] - FFLilunY[i]));
		if (dis < 3000.0)
		{
			fprintf_s(ff, "%s\t%12.6f\t%12.6f\t%12.6f\t%12.6f\n", sCellNameQ[i].c_str(), micronQCoorX[i], micronQCoorY[i], pixelQCoorX[i], pixelQCoorY[i]);
		}
		else
		{
			fprintf_s(ff, "%s\t%12.6f\t%12.6f\t%12.6f\t%12.6f\n", sCellNameQ[i].c_str(), FFLilunX[i], FFLilunY[i], pixelQCoorX[i], pixelQCoorY[i]);
		}
		
	}
	fclose(ff);
	return ;

}


void LSeekFiber::NiheParam(CString path)//调用python 程序处理文件 计算参数 (改为cpp)
{
	
	//Py_Initialize();			//使用python之前，要调用Py_Initialize();这个函数进行初始化 
	//Py_Finalize(); //释放资源 (已转移)
	
	
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.argv = ['python.py']");
		TCHAR buff[MAX_PATH];
		GetModuleFileName(NULL, buff, MAX_PATH);

		PyRun_SimpleString("sys.path.append('./')");//这一步很重要，为了获取下面py文件的路径
		
		PyObject* pModule = NULL;     //声明模块变量
		PyObject* pFunc = NULL;       // 声明调用函数变量
 		pModule = PyImport_ImportModule("handle");//这里是要调用的文件名handle.py

   		if (pModule == NULL)
		{
			printf("没找到该Python文件");
		}
		else {
			pFunc = PyObject_GetAttrString(pModule, "handle");		//这里是要调用的函数名fiber
			USES_CONVERSION;
			char* p = T2A(path);
			PyObject* args = Py_BuildValue("(s)", p);	//s:字符串，传入刚拍好的raw图片的路径
			PyObject* pRet = PyObject_CallObject(pFunc, args);		//调用函数
			int res = 0;
			PyArg_Parse(pRet, "i", &res);			//i:整形，转换返回类型
			if (res == 1) {
				printf("Python：处理完毕！");//输出结果
			}
		}
		
	
	return;
}

void LSeekFiber::FindQ()
{
	//char* FFCirclePath;
	//FFCirclePath = "F:\\Paohe\\bin\\FFCircle.txt";//FFCircle file path
	FILE* FFCFile;
	if ((FFCFile = fopen(FFCIRCLEPATH, "rt")) <= 0)//open file
	{
		//Sleep(1500);
		printf("FF文件无法打开！");
		return;
	}
	char unuse[100];
	int FFNum = 0;
	//fscanf(FFCFile, "%lf", &FFNum);
	while (!feof(FFCFile))
	{
		fscanf(FFCFile, "%lf", &FFCircleX[FFNum]);
		fscanf(FFCFile, "%lf", &FFCircleY[FFNum]);
		//fgets(unuse,1000, FFCFile);
		FFNum++;
	}
	fclose(FFCFile);
	int nn;
	for (int i = 0; i < FFNum; i++)
	{
		ZeroMemory(FFSingeX, intMemAlloc * sizeof(double));
		ZeroMemory(FFSingeY, intMemAlloc * sizeof(double));
		nn = 0;
		for (int j = 0; j < intLightNum; j++)
		{
			dblDist[i * intLightNum + j] = (dblCoorX[j] - FFCircleX[i]) * (dblCoorX[j] - FFCircleX[i])
				+ (dblCoorY[j] - FFCircleY[i]) * (dblCoorY[j] - FFCircleY[i]);
			if (dblDist[i * intLightNum + j] < FFCMax * FFCMax && dblDist[i * intLightNum + j] > FFCMin * FFCMin)
			{
				FFSingeX[nn] = dblCoorX[j];
				FFSingeY[nn] = dblCoorY[j];
				nn++;
			}
		}
		CircleFitting(FFSingeX, FFSingeY, &centerX[i], &centerY[i], &radius[i]); //CircleFitting
		//加入Q的距离判断，如果大于阈值pixcelDisThreshold ，则不参与匹配
		double disRight = sqrt((centerX[i] - FFCircleX[i]) * (centerX[i] - FFCircleX[i])+ (centerY[i] - FFCircleY[i]) * (centerY[i] - FFCircleY[i]));
		if (_isnan(disRight) || disRight > pixcelDisThreshold)
		{
			//centerX[i] = -1.0; centerY[i] = -1.0; 
			radius[i] = -1.0;
		}
		for (int j=0; j < intLightNum; j++)
		{
			//double a = dblCoorX[i];
			double disDel= sqrt((centerX[i] - dblCoorX[j]) * (centerX[i] - dblCoorX[j]) + (centerY[i] - dblCoorY[j]) * (centerY[i] - dblCoorY[j]));
			if (disDel< (FFCMax+10))
			{
				dblCoorX[j] = 0;
				dblCoorY[j] = 0;
			}
		}
	}
	return;
}


void LSeekFiber::CircleFitting(double* FFSingeX, double* FFSingeY, double* centerX, double* centerY, double* radius)
{
	std::set<int> deleteIndexSet; //剔除光点下标集合
	double distanceSigma = DBL_MAX;
	double distanceSigmaThreshold = 0.5;  //方差的阈值
	do
	{
		//1.先拟合圆心数据
		double sumX = 0, sumY = 0;
		double sumXX = 0, sumYY = 0, sumXY = 0;
		double sumXXX = 0, sumXXY = 0, sumXYY = 0, sumYYY = 0;
		int i = 0;
		while (FFSingeX[i] != 0)
		{
			if (deleteIndexSet.count(i))
			{
				i++;
				continue;
			}
			double p0 = FFSingeY[i];
			double p1 = FFSingeX[i];
			sumX += p0;
			sumY += p1;
			sumXX += p0 * p0;
			sumYY += p1 * p1;
			sumXY += p0 * p1;
			sumXXX += p0 * p0 * p0;
			sumXXY += p0 * p0 * p1;
			sumXYY += p0 * p1 * p1;
			sumYYY += p1 * p1 * p1;
			i++;
		}
		int pCount = i - deleteIndexSet.size();
		double M1 = pCount * sumXY - sumX * sumY;
		double M2 = pCount * sumXX - sumX * sumX;
		double M3 = pCount * (sumXXX + sumXYY) - sumX * (sumXX + sumYY);
		double M4 = pCount * sumYY - sumY * sumY;
		double M5 = pCount * (sumYYY + sumXXY) - sumY * (sumXX + sumYY);

		double a = (M1 * M5 - M3 * M4) / (M2 * M4 - M1 * M1);
		double b = (M1 * M3 - M2 * M5) / (M2 * M4 - M1 * M1);
		double c = -(a * sumX + b * sumY + sumXX + sumYY) / pCount;

		//圆心XY 半径
		double xCenter = -0.5 * a;
		double yCenter = -0.5 * b;
		double ra = 0.5 * sqrt(a * a + b * b - 4 * c);
		*radius = ra;
		*centerX = yCenter; 
		*centerY = xCenter;

		//2.计算均值和方差
		int k = 0;
		std::vector<double> distanceList;
		while (FFSingeX[k] != 0)
		{
			if (deleteIndexSet.count(k))
			{
				k++;
				continue;
			}
			double dist = sqrt((FFSingeX[k] - yCenter) * (FFSingeX[k] - yCenter) + (FFSingeY[k] - xCenter) * (FFSingeY[k] - xCenter));
			distanceList.push_back(dist);
			k++;
		}
		k = distanceList.size();
		double sum = std::accumulate(std::begin(distanceList), std::end(distanceList), 0.0);
		double mean = sum / k; //均值
		double accum = 0.0;
		std::for_each(std::begin(distanceList), std::end(distanceList), [&](const double d) {
			accum += (d - mean) * (d - mean);
		});
		distanceSigma = sqrt(accum / k); //方差

		//3.根据方差去剔除
		if (distanceSigma <= distanceSigmaThreshold) break;
		for (int i = 0; i < distanceList.size(); i++)
		{
			if (distanceList[i] < mean - 3 * distanceSigma || distanceList[i] > mean + 3 * distanceSigma)
			{
				deleteIndexSet.insert(i);
			}
		}
		
	} 
	while (distanceSigma > distanceSigmaThreshold);
	return;
}

//void LSeekFiber::CircleFitting_old(double* FFSingeX, double* FFSingeY, double* centerX, double* centerY, double* radius)
//{
//	double sumX = 0, sumY = 0;
//	double sumXX = 0, sumYY = 0, sumXY = 0;
//	double sumXXX = 0, sumXXY = 0, sumXYY = 0, sumYYY = 0;
//	int i = 0;
//	while (FFSingeX[i] != 0)
//	{
//		double p0 = FFSingeY[i];
//		double p1 = FFSingeX[i];
//
//		sumX += p0;
//		sumY += p1;
//		sumXX += p0 * p0;
//		sumYY += p1 * p1;
//		sumXY += p0 * p1;
//		sumXXX += p0 * p0 * p0;
//		sumXXY += p0 * p0 * p1;
//		sumXYY += p0 * p1 * p1;
//		sumYYY += p1 * p1 * p1;
//		i++;
//	}
//
//	int pCount = i;
//	double M1 = pCount * sumXY - sumX * sumY;
//	double M2 = pCount * sumXX - sumX * sumX;
//	double M3 = pCount * (sumXXX + sumXYY) - sumX * (sumXX + sumYY);
//	double M4 = pCount * sumYY - sumY * sumY;
//	double M5 = pCount * (sumYYY + sumXXY) - sumY * (sumXX + sumYY);
//
//	double a = (M1 * M5 - M3 * M4) / (M2 * M4 - M1 * M1);
//	double b = (M1 * M3 - M2 * M5) / (M2 * M4 - M1 * M1);
//	double c = -(a * sumX + b * sumY + sumXX + sumYY) / pCount;
//
//	//圆心XY 半径
//	double xCenter = -0.5 * a;
//	double yCenter = -0.5 * b;
//	double ra = 0.5 * sqrt(a * a + b * b - 4 * c);
//	*radius = ra;
//	*centerX = yCenter;
//	*centerY = xCenter;
//	return;
//}

/*
	名称：cpp
	功能：在拍摄文件中提取出Q理论与像素坐标参与多项式计算出P的实际坐标 （使用）
	修改时间：20211027
	修改人：段哈哈
	*/

void LSeekFiber::TxtReadQ(CString strFileName)
{


	FILE* fid;
	errno_t err;
	char cell;
	USES_CONVERSION;
	LPCSTR StrFileName = (LPCSTR)T2A(strFileName);//转化CString到const char*
	err = fopen_s(&fid, StrFileName, "rt");
	if (fid == NULL)
	{
		AfxMessageBox(strFileName + " : Failed to read  file.");
		return;
	}

	char buf[100] = { 0 };
	intQNum = 0;
	intPNum = 0;
	char c;
	c = fgetc(fid);
	sCellNameP = {};
	sCellNameQ = {};
	while (!feof(fid))
	{
		char cellName[11];
		fscanf_s(fid, "%10c", cellName);
		cellName[10] = '\0';
		
		//string s(cellName);
		//s = s.substr(3, 6);
		//sCellName.push_back(s);
 		for (int i = 0; i < 11; i++)
		{
			if (cellName[i] != ' ')
			{
				cell = cellName[i];
				break;
			}
		}
		if (intCCDNo == 0)
		{
			if (cell == 'P')
			{
				string unit_P(cellName);
				sCellNameP.push_back(unit_P);
				//fscanf_s(fid, "%2c", buf);
				fscanf_s(fid, "%lf %lf", &pixelPCoorX[intPNum], &pixelPCoorY[intPNum]);//读取P的像素坐标
				intPNum++;
			}
			else if (cell == 'Q')
			{
				string unit_Q(cellName);
				sCellNameQ.push_back(unit_Q);
				//fscanf_s(fid, "%2c", buf);
				fscanf_s(fid, "%lf %lf", &pixelQCoorX[intQNum], &pixelQCoorY[intQNum]);//读取Q的像素坐标
				
				fscanf_s(fid, "%lf %lf %lf %lf", &temp[intQNum], &temp[intQNum], &temp[intQNum], &temp[intQNum]);//无用
				fscanf_s(fid, "%lf %lf", &dblQCoorX[intQNum], &dblQCoorY[intQNum]);//读取Q的理论坐标
				fscanf_s(fid, "%lf %lf", &dblQCenA[intQNum], &dblQEccA[intQNum]);
				intQNum++;
				
			}
		}
		fgets(buf, 100, fid);
		c = fgetc(fid);//防止多读一次
	}
	fclose(fid);
	//delete[] temp;
	return;
}

BOOL LSeekFiber::SeekPointsTxt(CString fn)
{
	if (!ReadZBdata(fn))	return FALSE;

	int p,q,g;
	int i,j,m,m1,m2,n,n1,n2,mm;
	int sumRow,sumCol,SumGray;
	int intCounter=-1;
	CString rawfn,ss,str;

	errno_t err;
	FILE*	ff;
	double	dd[11];
	int		nn[2];
	char	buf[100];

	for(int rep=0;rep<intRepeatTimes;rep++)
	{
		ss.Format(_T("%02d.txt",rep));
		rawfn=fn.Left(fn.GetLength() - 6)+ss;
		USES_CONVERSION;
		LPCSTR RawFN = (LPCSTR)T2A(rawfn);//转化CString到const char*
		err = fopen_s(&ff, RawFN, "rt");

		ZeroMemory(dblCoorX,intMemAlloc*8);//it's essential
		ZeroMemory(dblCoorY,intMemAlloc*8);//it's essential
		ZeroMemory(dblX,intMemAlloc*8);//it's essential
		ZeroMemory(dblY,intMemAlloc*8);//it's essential
		ZeroMemory(intMM,intMemAlloc*4);//it's essential
		ZeroMemory(intMM1,intMemAlloc*4);//it's essential
		ZeroMemory(intNum,intMemAlloc*4);//it's essential
		ZeroMemory(intNum1,intMemAlloc*4);//it's essential

		intCounter=0;
		for (i=0;i<intUnitNum;i++)
		{
			fscanf_s(ff,"%s : %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %d %d",buf,&(dd[0]),&(dd[1]),&(dd[2]),&(dd[3]),&(dd[4]),&(dd[5]),&(dd[6]),&(dd[7]),&(dd[8]),&(dd[9]),&(dd[10]),&(nn[0]),&(nn[1]));
			fgets(buf,100,ff);

			dblCoorX[intCounter] = dd[9];//x
			dblCoorY[intCounter] = dd[10];//y
			intMM[intCounter] = nn[1];//mm
			intNum[intCounter] =nn[0] ;//mm 
			intCounter ++;
		}
		while(!feof(ff))
		{
			fscanf_s(ff,"%s : %lf %lf %lf %lf %d %d",buf,&(dd[0]),&(dd[1]),&(dd[2]),&(dd[3]),&(nn[0]),&(nn[1]));
			fgets(buf,100,ff);

			dblCoorX[intCounter] = dd[2];//x
			dblCoorY[intCounter] = dd[3];//y
			intMM[intCounter] = nn[1];//mm
			intNum[intCounter] =nn[0] ;//mm
			intCounter ++;
		}
		intLightNum = intCounter;//实际的点数

		//SortPoints();
		CaliPoints();
		SortPoints2(); //排序计算
		str = (LPCSTR)(rawfn.Left(rawfn.GetLength() - 4) + ".txt");
		WriteTxtData(str);
		fclose(ff);

	}

	return TRUE;
}

BOOL LSeekFiber::ReadZBdata(CString strFileName)
{
	FILE* fid;
	errno_t err;
	char cell;
	USES_CONVERSION;
	LPCSTR StrFileName = (LPCSTR)T2A(strFileName);//转化CString到const char*
	err = fopen_s(&fid,StrFileName, "rt");
	if(fid==NULL)
	{
		AfxMessageBox(strFileName+" : Failed to read ZB file.");
		return FALSE;
	}
	
	char buf[100] = {0};
	intUnitNum=0;
	intSolidNum=0;
	intQNum0 = 0;
	sCellName = {};
	char c;
	c = fgetc(fid);
	while (!feof(fid))
	{
		char cellName[11];
		fscanf_s(fid, "%10c", cellName);
		cellName[10] = '\0';
		//string s(cellName);
		//s = s.substr(3, 6);
		//sCellName.push_back(s);
		for (int i =0; i <11; i++)
		{
			if (cellName[i] != ' ')
			{
				cell = cellName[i];
				break;
			}
		}
		if (intCCDNo == 0)
		{
			if (cell == 'P' || cell == 'Q')
			{
				string s(cellName);
				sCellName.push_back(s);
				fscanf_s(fid,"%2c",buf);
				fscanf_s(fid,"%lf %lf",&dblZBCoorX[intUnitNum],&dblZBCoorY[intUnitNum]);
				fscanf_s(fid,"%lf %lf",&dblZBCenA[intUnitNum],&dblZBEccA[intUnitNum]);
				intUnitNum++;
				intSolidNum++;
			}
			if (cell == 'Q')
			{
				intQNum0++;
			}

		}
		else if(intAllUnit||(cell=='Q')||(cell=='D'+intCCDNo))
		{
			fscanf_s(fid,"%2c",buf);
			fscanf_s(fid,"%lf %lf",&dblZBCoorX[intUnitNum],&dblZBCoorY[intUnitNum]);
			fscanf_s(fid,"%lf %lf",&dblZBCenA[intUnitNum],&dblZBEccA[intUnitNum]);
			intUnitNum++;
			intSolidNum++;
		}
		/*else if(i<12)
		{lpRawBuffer
			if (((intCCDNo==0))||
				((intCCDNo==1)&&(i==3||i==7||i==11||i==0||i==4||i==8 ))||
				((intCCDNo==2)&&(i==0||i==4||i==8 ||i==1||i==5||i==9 ))||
				((intCCDNo==3)&&(i==1||i==5||i==9 ||i==2||i==6||i==10))||
				((intCCDNo==4)&&(i==2||i==6||i==10||i==3||i==7||i==11)))
			{
				fscanf_s(fid,"%2c",buf);
				fscanf_s(fid,"%lf %lf",&dblZBCoorX[intUnitNum],&dblZBCoorY[intUnitNum]);
				fscanf_s(fid,"%lf %lf",&dblZBCenA[intUnitNum],&dblZBEccA[intUnitNum]);
				intUnitNum++;
			}
		}*/
		fgets(buf,100,fid);
		c = fgetc(fid);//防止多读一次
	}	
	fclose(fid);

}

BOOL LSeekFiber::ReadRawData(CString strFileName)
{
	CFile file;
	CFileException e;
	if(!file.Open(strFileName,CFile::modeRead,&e))
	{
//		AfxMessageBox("Failed to read raw file.");
		return FALSE;
	}
	
	file.Seek(0L,CFile::begin);
	if(!file.Read(lpRawBuffer,intImageWidth*intImageHeight* sizeof(unsigned short)))
	{
		AfxMessageBox(_T("Failed to read raw data."));
		file.Close();
		return FALSE;
	}

	file.Close();

	if(intNeedFile==0)
		DeleteFile(strFileName);
	return TRUE;
}

BOOL LSeekFiber::WriteTxtData(CString strFileName)
{
	CString strPrint,strTemp;
	int i;

	CFile file;
	CFileException e;
	double ddd;

	for (i=0;i<intUnitNum;i++)
	{
		dblCoorX[i] = dblCoorX1[i]*3.1415926;
		dblCoorY[i] = dblCoorY1[i]*3.1415926;
	}

	double xx=0,yy=0;
	for (i=intUnitNum-intQNum;i<intUnitNum;i++)
	{
		xx+=dblX1[i];
		yy+=dblY1[i];
	}
	xx/=intSolidNum;
	yy/=intSolidNum;

	CString fname;
	FILE*	ff;
	errno_t err;
	double	dd[11];
	int		nn[2];
	char	buf[1000];
	double dx,dy,t1,t2;
	double xcoor,ycoor;
	int fn=strFileName.GetLength();
	USES_CONVERSION;
	LPCSTR StrFileName = (LPCSTR)T2A(strFileName);//转化CString到const char*
	err = fopen_s(&ff, StrFileName, "w+");

// 7 个单元的求和平均，可以在此处修改加入所有的求平均；

/* for (i=intUnitNum-intSolidNum;i<intUnitNum;i++)
	{
		xx+=dblCoorX1[i];
		yy+=dblCoorY1[i];
	}*/

	// 此处加入 对于固定光点取平均 功能




	
	xx/=intSolidNum;  // 经过5个参数计算过的 微米坐标，用于看是否匹配成功
	yy/=intSolidNum;
	


 	for (i=0;i<intUnitNum;i++)
	{
		ddd= sqrt((dblCoorX1[i]-xx-dblZBCoorX[i])*(dblCoorX1[i]-xx-dblZBCoorX[i])+(dblCoorY1[i]-yy-dblZBCoorY[i])*(dblCoorY1[i]-yy-dblZBCoorY[i]));
		//		 XY像素坐标    光点像素数    光点最大值			XY坐标              XY理论坐标       XY转角           XY处理过的坐标   距离  
		//strTemp.Format(_T("%6s\t%12.6f\t%12.6f\t%5d\t%5d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\t%10.6f\t%10.6f\t%15.6f\t%15.6f\t%15.6f\n"),
			//sCellName[i],dblX1[i],dblY1[i],intNum1[i],intMM1[i],dblCoorX1[i],dblCoorY1[i],dblZBCoorX[i],dblZBCoorY[i],dblZBCenA[i],dblZBEccA[i],
			//dblCoorX[i]-xx,dblCoorY[i]-yy,ddd);
		//strPrint = strPrint + strTemp;
		fprintf_s(ff, "%s\t%12.6f\t%12.6f\t%5d\t%5d\t%15.6f\t%15.6f\t%15.6f\t%15.6f\t%10.6f\t%10.6f\t%15.6f\t%15.6f\t%15.6f\n", 
			sCellName[i].c_str(), dblX1[i], dblY1[i], intNum1[i], intMM1[i], dblCoorX1[i], dblCoorY1[i], dblZBCoorX[i], dblZBCoorY[i], dblZBCenA[i], dblZBEccA[i],
			dblCoorX[i] - xx, dblCoorY[i] - yy, ddd);
	}
	for (;i<intLightNum-(intUnitNum- intQNum0);i++)
	{
		//strTemp.Format(_T(" nouse\t%12.6f\t%12.6f\t%5d\t%5d\t%15.6f\t%15.6f\n"),dblX1[i],dblY1[i],intNum1[i],intMM1[i],dblCoorX1[i],dblCoorY1[i]);
		//strPrint = strPrint + strTemp;
		fprintf_s(ff, "nouse  \t%12.6f\t%12.6f\t%5d\t%5d\t%15.6f\t%15.6f\n", dblX1[i], dblY1[i], intNum1[i], intMM1[i], dblCoorX1[i], dblCoorY1[i]);
	}
	fclose(ff);
	return TRUE;
}

void LSeekFiber::CaliPoints()
{
	int i, j;
	double dblTemp[15],X,Y,t1,t2;

	for (i=0;i<intLightNum;i++)
	{  
		//
		Y=dblCoorX[i]/1000;
		X=dblCoorY[i]/1000;
		dblX[i]=dblCoorX[i];
		dblY[i]=dblCoorY[i];


		dblCoorX[i]=dblBiliX[intCCDNo]*(dblXiangX[intCCDNo]+dblCoorX[i]);
		dblCoorY[i]=dblBiliY[intCCDNo]*(dblXiangY[intCCDNo]+dblCoorY[i]);
		t1 = dblCoorX[i];			
		t2 = dblCoorY[i];
		dblCoorX[i]=t2*sin(dblXiangA[intCCDNo])+t1*cos(dblXiangA[intCCDNo])  - dblCenterX[intCCDNo];
		dblCoorY[i]=t2*cos(dblXiangA[intCCDNo])-t1*sin(dblXiangA[intCCDNo])  - dblCenterY[intCCDNo];
	}
	for (; i < intLightNum + intSolidNum; i++)
	{
		Y = centerX[i] / 1000;
		X = centerY[i] / 1000;
		//FFCirclePixelX[i] = centerX[i];
		//FFCirclePixelY[i] = centerY[i];
		j = i - intLightNum;
		dblX[i] = centerX[j];
		dblY[i] = centerY[j];
		centerUmX[j] = dblBiliX[intCCDNo] * (dblXiangX[intCCDNo] + centerX[j]);//5参数的比例x（像素点x+5参数的平移）
		centerUmY[j] = dblBiliY[intCCDNo] * (dblXiangY[intCCDNo] + centerY[j]);
		t1 = centerUmX[j];
		t2 = centerUmY[j];
		dblCoorX[i] = t2 * sin(dblXiangA[intCCDNo]) + t1 * cos(dblXiangA[intCCDNo]) - dblCenterX[intCCDNo];
		dblCoorY[i] = t2 * cos(dblXiangA[intCCDNo]) - t1 * sin(dblXiangA[intCCDNo]) - dblCenterY[intCCDNo];
		intMM[i] = 3500;
		intNum[i] = 30;
	}
	intLightNum += intSolidNum;

}

void LSeekFiber::SortPoints()
{
	int i,j;
	double dblTemp;

	//按y坐标升序冒泡
	for (i=0; i<intLightNum-1; i++)
	{
		for (j=0; j < intLightNum - 1; j++)
		{
			if (dblCoorY[j] > dblCoorY[j+1])
			{
				dblTemp = dblCoorY[j];
				dblCoorY[j] = dblCoorY[j+1];
				dblCoorY[j+1] = dblTemp;

				dblTemp = dblCoorX[j];
				dblCoorX[j] = dblCoorX[j+1];
				dblCoorX[j+1] = dblTemp;
			}
		}
	}


	//数一下有多少行
	int * intCounter = new int[intLightNum];
	int n=0;
	for (i=0; i<intLightNum; i++)
	{
		intCounter[i]=1;
	}
	for (i=0; i < intLightNum -1; i++)
	{
		if (fabs(dblCoorY[i] - dblCoorY[i+1]) < 70)
			intCounter[n]++;
		else
			n++;
	}


	//行内按x坐标升序冒泡
	int k,low,high;
	low = 0;
	for (k=0;k<=n;k++)
	{
		low = k>0 ? high + 1 : 0;
		high = low + intCounter[k] - 1;

		for (i=low; i < high; i++)
		{
			for (j=low; j < high; j++)
			{
				ASSERT(j+1 < intLightNum);

				if (dblCoorX[j] > dblCoorX[j+1])
				{
					dblTemp = dblCoorY[j];
					dblCoorY[j] = dblCoorY[j+1];
					dblCoorY[j+1] = dblTemp;
					
					dblTemp = dblCoorX[j];
					dblCoorX[j] = dblCoorX[j+1];
					dblCoorX[j+1] = dblTemp;
				}
			}
		}
	}

	delete [] intCounter;
}

void LSeekFiber::SortPoints2()
{
	int i,j,k,m,n;
	double dblMinDist,dblMaxDouble,dblMaxDouble1;

	ZeroMemory(bFlag1,intMemAlloc*sizeof(BOOL));
	ZeroMemory(bFlag2,intMemAlloc*sizeof(BOOL));
	ZeroMemory(dblCoorX1,intMemAlloc*sizeof(double));
	ZeroMemory(dblCoorY1,intMemAlloc*sizeof(double));
	ZeroMemory(dblX1,intMemAlloc*sizeof(double));
	ZeroMemory(dblY1,intMemAlloc*sizeof(double));
	
	dblMaxDouble = double(MAXLONGLONG);
	dblMaxDouble1= double(33000*33000);

	//calc dblDist and get dblDist1
	int nn=0;
	for (i=0;i<intUnitNum;i++)
	{ 
		for (j=0;j<intLightNum;j++)
		{
			dblDist[i*intLightNum+j]= (dblCoorX[j] - dblZBCoorX[i])*(dblCoorX[j] - dblZBCoorX[i])
					+ (dblCoorY[j] - dblZBCoorY[i])*(dblCoorY[j] - dblZBCoorY[i]);
			if(dblDist[i*intLightNum+j]<dblMaxDouble1)
			{
				dblDist1[nn]=dblDist[i*intLightNum+j];
				dblDistM[nn]=i; //i表示单元
				dblDistN[nn]=j; //j表示光点
				nn++;
			}
		}
	}
	//sort dblDist1  //这个就是根据dblDist1排序
	double dd;
	for (i=0;i<nn-1;i++)
	{
		k=i;
        for (j=i+1;j<nn;j++)
			//对于当前i 找到距离最小的 和他交换
			if(dblDist1[j]<dblDist1[k])
				k=j;
		if(k!=i)
		{
			//将最小的值依次给i
			dd=dblDist1[i];dblDist1[i]=dblDist1[k];dblDist1[k]=dd;
			m=dblDistM[i];dblDistM[i]=dblDistM[k];dblDistM[k]=m;
			n=dblDistN[i];dblDistN[i]=dblDistN[k];dblDistN[k]=n;
		}
	}
	//proc dblDist1
	for (i=0;i<nn;i++)
	{
		//dblDistM里面存的单元  dblDistN存的光点  都已经按照dblDist1排序了
		m=dblDistM[i];
		n=dblDistN[i];
		if(!(bFlag1[m] || bFlag2[n]))
		{
			//为什么把n的给了m
			dblCoorX1[m] = dblCoorX[n];
			dblCoorY1[m] = dblCoorY[n];
			dblX1[m] = dblX[n];
			dblY1[m] = dblY[n];
			intMM1[m] = intMM[n];
			intNum1[m] = intNum[n];
			bFlag1[m]=1;
			bFlag2[n]=1;
		}
	}
	for (j=0,k=intUnitNum;j<intLightNum;j++)
		if(!bFlag2[j])
	{
		intMM1[k] = intMM[j];
		intNum1[k] = intNum[j];
		dblX1[k] = dblX[j];
		dblY1[k] = dblY[j];
		dblCoorX1[k] = dblCoorX[j];
		dblCoorY1[k++] = dblCoorY[j];
	}
	intLightNum=k;
}
