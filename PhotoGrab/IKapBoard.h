/************************************************************************/
/*	Image Capture Library       --- ITEK Electronics 
/*
/*  Copyright (c) 2015-2017
/************************************************************************/
#ifndef __IKAPBOARDLIB__
#define __IKAPBOARDLIB__

#ifdef IKAPBOARD_EXPORTS
#define IKAPBOARDDLL __declspec(dllexport)
#else
#define IKAPBOARDDLL __declspec(dllimport)
#endif	/*IKAPBOARD_EXPROTS*/

#include <windows.h>
#ifdef __cplusplus
extern "C"{
#endif  /* __cplusplus*/


/************************************************************************/
/* Hook Function
*/
/************************************************************************/
#define IKEvent_GrabStart				(0x00000000)
#define IKEvent_FrameReady				(0x00000001)
#define IKEvent_GrabStop				(0x00000002)
#define	IKEvent_FrameLost				(0x00000003)
#define IKEvent_TimeOut					(0x00000004)
#define IKEvent_GrabLine				(0x00100000)
#define IKEvent_GrabLineEnd				(0x00200000)

typedef void (CALLBACK* HookFnPtr)( void* pParam );


/************************************************************************/
/*Parameter Information
*/
/************************************************************************/
#define IKP_IMAGE_WIDTH							(0x10000001)
#define IKP_IMAGE_HEIGHT						(0x10000002)
#define IKP_DATA_FORMAT							(0x10000003)
#define IKP_BOARD_BIT							(0x10000004)
#define IKP_TIME_OUT							(0x10000005)
#define IKP_SCAN_TYPE							(0x10000006)
#define IKP_FPGA_VERSION						(0x10000007)
#define IKP_INTERNEL_BUFFER_SIZE				(0x10000008)
#define IKP_FRAME_SIZE							(0x10000009)
#define IKP_IMAGE_TYPE							(0x1000000a)
#define IKP_FRAME_COUNT							(0x1000000b)
#define IKP_FRAME_TRANSFER_MODE					(0x1000000c)
#define IKP_FRAME_AUTO_CLEAR					(0x1000000d)
#define IKP_GRAB_MODE							(0x1000000e)
#define	IKP_FRAME_TIME_STAMP_LOW				(0x1000000f)
#define IKP_FRAME_TIME_STAMP_HIGH				(0x10000010)
#define IKP_BLOCK_TIME_STAMP_LOW				(0x10000011)
#define IKP_BLOCK_TIME_STAMP_HIGH				(0x10000012)
#define IKP_TAP_NUMBER							(0x10000013)
#define IKP_TAP_ARRANGEMENT						(0x10000014)
#define IKP_BAYER_PATTERN						(0x10000015)
#define IKP_PIXEL_CLOCK							(0x10000016)
#define IKP_DATA_VALID_ENABLE					(0x10000017)
#define IKP_CC1_SOURCE							(0x10000018)
#define IKP_CC2_SOURCE							(0x10000019)
#define IKP_CC3_SOURCE							(0x1000001a)
#define IKP_CC4_SOURCE							(0x1000001b)
#define IKP_BOARD_TRIGGER_MODE					(0x1000001c)
#define IKP_BOARD_TRIGGER_SOURCE				(0x1000001d)
#define IKP_GENERAL_INPUT1_SAMPLE_MODE			(0x1000001e)
#define IKP_GENERAL_INPUT1_PROTECT_MODE			(0x1000001f)
#define IKP_GENERAL_INPUT1_MINIMUM_INTERVAL		(0x10000020)
#define IKP_GENERAL_INPUT2_SAMPLE_MODE			(0x10000021)
#define IKP_GENERAL_INPUT2_PROTECT_MODE			(0x10000022)
#define IKP_GENERAL_INPUT2_MINIMUM_INTERVAL		(0x10000023)
#define IKP_SHAFT_ENCODER1_PULSE_DROP			(0x10000024)
#define IKP_SHAFT_ENCODER1_PROTECT_MODE			(0x10000025)
#define IKP_SHAFT_ENCODER1_MINIMUM_INTERVAL		(0x10000026)
#define IKP_INTEGRATION_TRIGGER_SOURCE			(0x10000027)
#define IKP_INTEGRATION_TRIGGER_FREQUENCY		(0x10000028)
#define IKP_STROBE_TRIGGER_SOURCE				(0x10000029)
#define IKP_BOARD_SYNC_OUTPUT1_SOURCE			(0x1000002a)
#define IKP_BOARD_SYNC_OUTPUT2_SOURCE			(0x1000002b)
#define IKP_GENERAL_OUTPUT1_SOURCE				(0x1000002c)
#define IKP_GENERAL_OUTPUT2_SOURCE				(0x1000002d)
#define IKP_INTEGRATION_METHOD					(0x1000002e)
#define IKP_INTEGRATION_PARAM1					(0x1000002f)
#define IKP_INTEGRATION_PARAM2					(0x10000030)
#define IKP_INTEGRATION_PARAM3					(0x10000031)
#define IKP_INTEGRATION_PARAM4					(0x10000032)
#define IKP_INTEGRATION_POLARITY1				(0x10000033)
#define IKP_INTEGRATION_POLARITY2				(0x10000034)
#define IKP_STROBE_METHOD						(0x10000035)
#define IKP_STROBE_PARAM1						(0x10000036)
#define IKP_STROBE_PARAM2						(0x10000037)
#define IKP_STROBE_PARAM3						(0x10000038)
#define IKP_STROBE_PARAM4						(0x10000039)
#define IKP_STROBE_POLARITY						(0x1000003a)
#define IKP_GENERAL_OUTPUT1_POLARITY			(0x1000003b)
#define IKP_GENERAL_OUTPUT1_DELAY				(0x1000003c)
#define IKP_GENERAL_OUTPUT2_POLARITY			(0x1000003d)
#define IKP_GENERAL_OUTPUT2_DELAY				(0x1000003e)
#define IKP_FPGA_SERIAL_NUMBER					(0x20000001)
#define IKP_INTERNAL_BUFFER_SIZE                (0x10000008)

/************************************************************************/
/*Resource Type
/************************************************************************/
#define	IKBoardUnknown				0xFFFFFFFF
#define	IKBoardALL					0x00000000
#define	IKBoardUSB30				0x00000001
#define	IKBoardPCIE					0x00000002

/************************************************************************/
/*Data Format
/************************************************************************/
#define IKP_DATA_FORMAT_VAL_8Bit				(8)
#define IKP_DATA_FORMAT_VAL_10Bit				(10)
#define IKP_DATA_FORMAT_VAL_12Bit				(12)
#define IKP_DATA_FORMAT_VAL_14Bit				(14)
#define IKP_DATA_FORMAT_VAL_16Bit				(16)

/************************************************************************/
/*Image Type
/************************************************************************/
#define IKP_IMAGE_TYPE_VAL_MONOCHROME			(0)
#define IKP_IMAGE_TYPE_VAL_COLORFUL				(1)

/************************************************************************/
/*Scan Type
/************************************************************************/
#define IKP_SCAN_TYPE_VAL_LINEAR				(0)
#define IKP_SCAN_TYPE_VAL_AREA					(1)

/************************************************************************/
/*Grab Start Mode                                                                      
/************************************************************************/
#define	IKP_GRAB_BLOCK  						(0)
#define	IKP_GRAB_NON_BLOCK						(1)

/************************************************************************/
/*Frame Transfer Mode                                                                      
/************************************************************************/
#define	IKP_FRAME_TRANSFER_SYNCHRONOUS							(0)
#define	IKP_FRAME_TRANSFER_ASYNCHRONOUS							(1)
#define	IKP_FRAME_TRANSFER_SYNCHRONOUS_NEXT_EMPTY_WITH_PROTECT	(2)

/************************************************************************/
/*Frame Auto Clear                                                                   
/************************************************************************/
#define IKP_FRAME_AUTO_CLEAR_VAL_DISABLE						(0)
#define IKP_FRAME_AUTO_CLEAR_VAL_ENABLE							(1)

/************************************************************************/
/*Bayer Pattern
/************************************************************************/
#define	IKP_BAYER_PATTERN_VAL_NULL								(0)
#define	IKP_BAYER_PATTERN_VAL_BGGR								(1)
#define IKP_BAYER_PATTERN_VAL_RGGB								(2)
#define IKP_BAYER_PATTERN_VAL_GBRG								(3)
#define IKP_BAYER_PATTERN_VAL_GRBG								(4)

/************************************************************************/
/*CC<i> Source
/************************************************************************/
#define IKP_CC_SOURCE_VAL_NOT_USE								(0)
#define IKP_CC_SOURCE_VAL_INTEGRATION_SIGNAL1					(1)
#define IKP_CC_SOURCE_VAL_INTEGRATION_SIGNAL2					(2)
#define IKP_CC_SOURCE_VAL_LOW									(3)
#define IKP_CC_SOURCE_VAL_HIGH									(4)

/************************************************************************/
/*Board Trigger Mode
/************************************************************************/
#define IKP_BOARD_TRIGGER_MODE_VAL_INNER						(0)
#define IKP_BOARD_TRIGGER_MODE_VAL_OUTTER						(1)

/************************************************************************/
/*Board Trigger Source
/************************************************************************/
#define IKP_BOARD_TRIGGER_SOURCE_VAL_GENERAL_INPUT1				(0)
#define IKP_BOARD_TRIGGER_SOURCE_VAL_GENERAL_INPUT2				(1)
#define IKP_BOARD_TRIGGER_SOURCE_VAL_SHAFT_ENCODER1				(2)
#define IKP_BOARD_TRIGGER_SOURCE_VAL_BOARD_SYNC1				(3)
#define IKP_BOARD_TRIGGER_SOURCE_VAL_BOARD_SYNC2				(4)

/************************************************************************/
/*General Input<i> Sample Mode
/************************************************************************/
#define IKP_GENERAL_INPUT_SAMPLE_MODE_VAL_ACTIVE_HIGH			(0)
#define IKP_GENERAL_INPUT_SAMPLE_MODE_VAL_ACTIVE_LOW			(1)
#define IKP_GENERAL_INPUT_SAMPLE_MODE_VAL_RISING_EDGE			(2)
#define IKP_GENERAL_INPUT_SAMPLE_MODE_VAL_FALLING_EDGE			(3)

/************************************************************************/
/*General Input<i> Protect Mode
/************************************************************************/
#define IKP_GENERAL_INPUT_PROTECT_MODE_VAL_NOT_USE				(0)
#define IKP_GENERAL_INPUT_PROTECT_MODE_VAL_DELETE				(1)
#define IKP_GENERAL_INPUT_PROTECT_MODE_VAL_MEMORIZE				(2)

/************************************************************************/
/*Shaft Encoder<i> Protect Mode
/************************************************************************/
#define IKP_SHAFT_ENCODER_PROTECT_MODE_VAL_NOT_USE				(0)
#define IKP_SHAFT_ENCODER_PROTECT_MODE_VAL_DELETE				(1)
#define IKP_SHAFT_ENCODER_PROTECT_MODE_VAL_MEMORIZE				(2)

/************************************************************************/
/*Integration Trigger Source
/************************************************************************/
#define IKP_INTEGRATION_TRIGGER_SOURCE_VAL_INTERNAL				(0)
#define IKP_INTEGRATION_TRIGGER_SOURCE_VAL_GENERAL_INPUT1		(1)
#define IKP_INTEGRATION_TRIGGER_SOURCE_VAL_GENERAL_INPUT2		(2)
#define IKP_INTEGRATION_TRIGGER_SOURCE_VAL_SHAFT_ENCODER1		(5)
#define IKP_INTEGRATION_TRIGGER_SOURCE_VAL_BOARD_SYNC1			(7)
#define IKP_INTEGRATION_TRIGGER_SOURCE_VAL_BOARD_SYNC2			(8)

/************************************************************************/
/*Strobe Trigger Source
/************************************************************************/
#define IKP_STROBE_TRIGGER_SOURCE_VAL_GENERAL_INPUT1			(1)
#define IKP_STROBE_TRIGGER_SOURCE_VAL_GENERAL_INPUT2			(2)
#define IKP_STROBE_TRIGGER_SOURCE_VAL_SHAFT_ENCODER1			(5)
#define IKP_STROBE_TRIGGER_SOURCE_VAL_BOARD_SYNC1				(7)
#define IKP_STROBE_TRIGGER_SOURCE_VAL_BOARD_SYNC2				(8)

/************************************************************************/
/*Board Sync Output Source
/************************************************************************/
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_NOT_USE				(0)
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_INTERNAL				(1)
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_GENERAL_INPUT1			(2)
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_GENERAL_INPUT2			(3)
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_SHAFT_ENCODER1			(4)
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_INTEGRATION_SIGNAL1	(5)
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_INTEGRATION_SIGNAL2	(6)
#define IKP_BOARD_SYNC_OUTPUT_SOURCE_VAL_STROBLE_SIGNAL1		(7)

/************************************************************************/
/*General Output<i> Source
/************************************************************************/
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_INTERNAL					(0)
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_GENERAL_INPUT1			(1)
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_GENERAL_INPUT2			(2)
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_SHAFT_ENCODER1			(3)
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_INTEGRATION_SIGNAL1		(4)
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_INTEGRATION_SIGNAL2		(5)
#define IKP_GENERAL_OUTPUT_SOURCE_VAL_STROBLE_SIGNAL1			(6)

/************************************************************************/
/*General Output<i> Polarity
/************************************************************************/
#define IKP_GENERAL_OUTPUT_POLARITY_VAL_SAME_TO_SOURCE			(0)
#define IKP_GENERAL_OUTPUT_POLARITY_VAL_OPPOSITE_TO_SOURCE		(1)

/************************************************************************/
/*Integration Method 
/************************************************************************/
#define IKP_INTEGRATION_METHOD_VAL_1							(0)
#define IKP_INTEGRATION_METHOD_VAL_2							(1)
#define IKP_INTEGRATION_METHOD_VAL_3							(2)
#define IKP_INTEGRATION_METHOD_VAL_4							(3)

/************************************************************************/
/*Integration Polarity
/************************************************************************/
#define IKP_INTEGRATION_POLARITY_VAL_LOW						(0)
#define IKP_INTEGRATION_POLARITY_VAL_HIGH						(1)

/************************************************************************/
/*Strobe Method
/************************************************************************/
#define IKP_STROBE_METHOD_VAL_1									(0)
#define IKP_STROBE_METHOD_VAL_2									(1)
#define IKP_STROBE_METHOD_VAL_3									(2)
#define IKP_STROBE_METHOD_VAL_4									(3)

/************************************************************************/
/*Strobe Polarity
/************************************************************************/
#define IKP_STROBE_POLARITY_VAL_LOW								(0)
#define IKP_STROBE_POLARITY_VAL_HIGH							(1)

/************************************************************************/
/*Buffer Status                                                                      
/************************************************************************/
typedef struct {
	unsigned int uFull;
	unsigned int uEmpty;
	unsigned int uTransfer;
	unsigned int uOverflow;
	unsigned int uLineNum;
} IKAPBUFFERSTATUS, *PIKAPBUFFERSTATUS;


/************************************************************************/
/* Error Handle                                                                      
/************************************************************************/
typedef struct {
	unsigned int uBoardType;
	unsigned int uBoardIndex;
	unsigned int uErrorCode;

} IKAPERRORINFO, *PIKAPERRORINFO;


#define IK_RTN_OK							(1)
#define IK_RTN_ERROR						(0)

#define	IKStatus_Success					0x00000001

#define	IKStatus_BoardNotFound				0x00000002
#define	IKStatus_AllocMemoryFail			0x00000003
#define	IKStatus_InvalidParameter			0x00000004
#define	IKStatus_OpenBoardFail				0x00000005
#define	IKStatus_TimeOut					0x00000006
#define	IKStatus_WinError					0x00000007
#define	IKStatus_BoardNotOpen				0x00000008
#define	IKStatus_ConfigFilePathInvalid		0x00000009
#define	IKStatus_ConfigParameterInvalid		0x0000000a
#define	IKStatus_ZLP						0x0000000b
#define	IKStatus_ThreadUnsetup				0x0000000c
#define	IKStatus_ThreadExist				0x0000000d
#define	IKStatus_CameraUnsupport			0x0000000e
#define	IKStatus_XMLFileLoadFail			0x0000000f
#define	IKStatus_NodeNotExist				0x00000010
#define	IKStatus_WriteSerialFail			0x00000011
#define	IKStatus_CommandNotExist			0x00000012
#define	IKStatus_CommandCollision			0x00000013
#define	IKStatus_CommandMissRequirement		0x00000014
#define	IKStatus_CommandNotAllow			0x00000015
#define	IKStatus_CommandSyntaxError			0x00000016
#define	IKStatus_NodeTypeDismatch			0x00000017
#define	IKStatus_FeatureUnSupport			0x00000018
#define	IKStatus_CommandResultNoExit		0x00000019
#define	IKStatus_CLRegPathNotFound			0x0000001a
#define	IKStatus_CLDLLNotFound				0x0000001b
#define	IKStatus_CameraNotFound				0x0000001c
#define	IKStatus_BufferTooSmall				0x0000001d
#define	IKStatus_BaudrateNotSupport			0x0000001e
#define	IKStatus_CameraInUse				0x0000001f
#define	IKStatus_FPGA_EraseFlashFail		0x00000020
#define	IKStatus_FPGA_CheckFail				0x00000021
#define	IKStatus_BoardNotBindingCOM			0x00000022
#define	IKStatus_ReadRegFail				0x00000023
#define	IKStatus_Invalid_Mutex				0x00000024
#define IKStatus_Mutex_Locked				0x00000025
#define IKStatus_Invalid_Handle				0x00000026
#define IKStatus_Set_Info_Error				0x00000027
#define IKStatus_Grab_Pending				0x00000028
#define IKStatus_Insufficient_Resource		0x00000029
#define IKStatus_Grab_Abort					0x0000002a

//Get the count of acquisition device
IKAPBOARDDLL int WINAPI IKapGetBoardCount( unsigned int resourceType, unsigned int* resourceCount );

//Get the name of acquisition device
IKAPBOARDDLL int WINAPI IKapGetBoardName( unsigned int resourceType, unsigned int resourceIndex, char* resourceName, unsigned int* resoureceNameSize );

//Open the acquisition device
IKAPBOARDDLL HANDLE WINAPI IKapOpen( unsigned int resourceType, unsigned int resourceIndex );

//Close the acquisition device
IKAPBOARDDLL int WINAPI IKapClose( HANDLE hDev );

//Load and Verify Configuration 
IKAPBOARDDLL int WINAPI IKapLoadConfigurationFromFile( HANDLE hDev, char* lpFileName );

//Save Configuration
IKAPBOARDDLL int WINAPI IKapSaveConfigurationToFile( HANDLE hDev, char* lpFileName );

//Get Parameter Information
IKAPBOARDDLL int WINAPI IKapGetInfo( HANDLE hDev, unsigned int uType, int* npValue);

//Set Parameter Information
IKAPBOARDDLL int WINAPI IKapSetInfo( HANDLE hDev, unsigned int uType, int nValue);

//Register the Callback
IKAPBOARDDLL int WINAPI IKapRegisterCallback( HANDLE hDev, unsigned int uEventType, HookFnPtr fEventFunc, void* pParam );

//Unregister the Callback
IKAPBOARDDLL int WINAPI IKapUnRegisterCallback( HANDLE hDev, unsigned int uEventType );

//Start Grab Image
IKAPBOARDDLL int WINAPI IKapStartGrab( HANDLE hDev, int nFrameCount );

//Stop Grab Image
IKAPBOARDDLL int WINAPI IKapStopGrab( HANDLE hDev );

//Get Transfer Buffer Address
IKAPBOARDDLL int WINAPI IKapGetBufferAddress( HANDLE hDev, int nFrameNum, void** pAddress );

//Get Transfer Buffer Status
IKAPBOARDDLL int WINAPI IKapGetBufferStatus( HANDLE hDev, int nFrameNum, PIKAPBUFFERSTATUS pIKapBufferStatus);

//Release Transfer Buffer 
IKAPBOARDDLL int WINAPI IKapReleaseBuffer( HANDLE hDev, int nFrameNum );

//Get The Camera Status
IKAPBOARDDLL int WINAPI IKapGetCameraStatus( HANDLE hDev, int* npValue );

//Get the Error Code
IKAPBOARDDLL void WINAPI IKapGetLastError( PIKAPERRORINFO pIKapErrorInfo, bool bErrorReset );

//Get the serial port number
IKAPBOARDDLL int WINAPI IKapGetSerialPort( HANDLE hDev, int* npPortNumber );

//Get the frame rate
IKAPBOARDDLL int WINAPI IKapGetFrameRate( HANDLE hDev, double* dpFrameRate );

#ifdef  __cplusplus
}		/* extern "C" */
#endif	/* __cplusplus */

#endif

