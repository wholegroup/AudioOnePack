#ifndef __AOPDECODER_H
#define __AOPDECODER_H

#define AOPDLLEXPORT

//////////////////////////////////////////////////////////////////////////
//
// ����� �������
//
//////////////////////////////////////////////////////////////////////////

// �������������
AOPDLLEXPORT __int32 AOPInit();

// ������������ ��������
AOPDLLEXPORT __int32 AOPFree();

//////////////////////////////////////////////////////////////////////////
//
// ������� ������ � ������������
//
//////////////////////////////////////////////////////////////////////////

// �������������
enum {DECODE_STOP = 0, DECODE_POS, DECODE_ERROR};

typedef void (CALLBACK *PDECODECALLBACK)(__int32 dwAction, __int32 dwParamOne, __int32 dwParamTwo);

AOPDLLEXPORT __int32 AOPDecode(PWCHAR pwcInFile, PWCHAR pwcOutFile, PDECODECALLBACK pCallBack);

// ������������
AOPDLLEXPORT __int32 AOPPlay(PWCHAR pwcFileName);

// ��������� ������� ������������
AOPDLLEXPORT __int32 AOPPlayPosition(float fPos);

// ��������� ������������
AOPDLLEXPORT __int32 AOPStop();

// ��������� ������� �������
AOPDLLEXPORT float AOPGetPos();

// ��������� ����� �����
AOPDLLEXPORT float AOPGetLen(WCHAR* pwcFileName);

// ��������� �������� ���������
AOPDLLEXPORT unsigned __int32 AOPGetVolume();

// ��������� �������� ���������
AOPDLLEXPORT __int32 AOPSetVolume(unsigned __int32 uiVolume);

// ��������� ����� �����
AOPDLLEXPORT __int32 AOPGetTags(PWCHAR pwcFileName, PWCHAR pwcArtist, PWCHAR pwcAlbum, PWCHAR pwcTitle);

// ������� ������ � �����
AOPDLLEXPORT __int32 AOPSeconds2Bytes(float fSeconds);

//////////////////////////////////////////////////////////////////////////
// ������� ������ � CD/DVD
//
//////////////////////////////////////////////////////////////////////////

// ���������� �� ����������
#pragma pack(1)
typedef struct 
{
	WCHAR           pwLetter[3]; // Drive letter
	WCHAR           pwName[100]; // Drive name
	unsigned __int8 ucPortID;    // Port Id - Logical SCSI adapter ID if ASPI is used
	unsigned __int8 ucBusID;     // Bus ID - 0 if ASPI is used
	unsigned __int8 ucTargetID;  // Target Id
	unsigned __int8 ucLUN;       // LUN (Logical Unit Number)
} DEVICEINFO, *PDEVICEINFO;
#pragma pack()

typedef void (CALLBACK *PFINDCALLBACK)(DEVICEINFO pDeviceInfo);

AOPDLLEXPORT __int32 AOPGetDevices(PFINDCALLBACK pCallBack);

// ���������� � �����
#pragma pack(1)
typedef struct 
{
	__int32         iDiscType;
	WCHAR           pwcDiscType[10];
	__int64         iUsedSpace;
	__int64         iFreeSpace;
	unsigned __int8 bIsDiscBlank;
	unsigned __int8 bIsWritable;
} DISCINFO, *PDISCINFO;

typedef struct  
{
	unsigned __int8   uiTrackMode;
	unsigned __int8   uiSessionNumber;
	unsigned __int8   uiTrackNumber;
	__int32           iStartingLBA;
	__int32           iEndingLBA;
	unsigned __int32  uiLBSizeInUCHARs;
} TOCINFO, *PTOCINFO;
#pragma pack()

typedef DWORD (CALLBACK *PTOCINFOCALLBACK)(TOCINFO tocInfo);

// ��������� ���������� � �����
AOPDLLEXPORT __int32 AOPGetDiscInfo(PDEVICEINFO pDeviceInfo, PDISCINFO pDiscInfo, PTOCINFOCALLBACK pCallBack);

// load �����
AOPDLLEXPORT __int32 AOPLoadTray(PDEVICEINFO pDeviceInfo);

// eject �����
AOPDLLEXPORT __int32 AOPEjectTray(PDEVICEINFO pDeviceInfo);

// ������� ����� CD/DVD
AOPDLLEXPORT __int32 AOPBlank(PDEVICEINFO pDeviceInfo, __int8 bFull);

// ��������� ���������� �������� ������� �����
AOPDLLEXPORT float AOPGetBlankTime(PDEVICEINFO pDeviceInfo, __int8 bFull);

// ��������� ��������� ������ CD �����
AOPDLLEXPORT __int32 AOPGetWriteSpeeds(PDEVICEINFO pDeviceInfo, PWCHAR pwcSpeeds);

// ��������� ��������� ������ CD �����
AOPDLLEXPORT __int32 AOPGetReadSpeeds(PDEVICEINFO pDeviceInfo, PWCHAR pwcSpeeds);

// �������� �� ������� ������� CD
AOPDLLEXPORT __int32 AOPIsBlankCD(PDEVICEINFO pDeviceInfo);

// ���������� ����������
AOPDLLEXPORT __int32 AOPLock(PDEVICEINFO pDeviceInfo);

// ������������� ����������
AOPDLLEXPORT __int32 AOPUnLock(PDEVICEINFO pDeviceInfo);


//////////////////////////////////////////////////////////////////////////
// ������� ������ � AUDIO CD 
//
//////////////////////////////////////////////////////////////////////////

// ���� ��� ���������������� callback �������
enum {AUDIOBURN_WRITE = 0, AUDIOBURN_BUFFER, AUDIORIP_READ};

// ��������� �� ���������������� callback ������� ��� ������� Audio CD
typedef VOID (CALLBACK *PAUDIOBURNCALLBACK)(__int32 iAction, __int32 iParamOne, __int32 iParamTwo);

// �������� Audio CD
AOPDLLEXPORT __int32 AOPAudioCDInit(PDEVICEINFO pDeviceInfo);

// ������������ �������� ������� ��� �������� Audio CD
AOPDLLEXPORT __int32 AOPAudioCDFree();

// ���������� �����
AOPDLLEXPORT __int32 AOPAudioCDAddTrack(PWCHAR pwcPath);

// ��������� ����� ����� �����
AOPDLLEXPORT __int32 AOPAudioCDSetTitle(unsigned __int8 ucTrack, PWCHAR pwcArtist, PWCHAR pwcTitle);

// ������ Audio CD
AOPDLLEXPORT __int32 AOPAudioCDBurn(PAUDIOBURNCALLBACK pCallback, __int32 iSpeed);

// ��������� �� ���������������� �������
typedef VOID (CALLBACK *PAUDIORIPCALLBACK)(__int32 iAction, __int32 iParamOne, __int32 iParamTwo);

// Rip Audio CD
AOPDLLEXPORT __int32 AOPAudioCDRip(__int32 iTrack, PWCHAR pwcPath, PAUDIORIPCALLBACK pCallback, __int32 iSpeed);

// ������ �������� ��������
AOPDLLEXPORT __int32 AOPAudioCDRipCancel();

// ������������ ����� Audio CD
AOPDLLEXPORT __int32 AOPAudioCDPlay(__int32 iDrive, __int32 iTrack);

// ��������� CD-Text
AOPDLLEXPORT __int32 AOPAudioCDGetText(__int32 iDrive, PWCHAR pwcText);

// ��������� CDDB identifier
AOPDLLEXPORT __int32 AOPAudioCDGetCDDB(__int32 iDrive, PWCHAR pwcCDDB);

//////////////////////////////////////////////////////////////////////////
// ������� ������ � ������������ (MP3) �������
//
//////////////////////////////////////////////////////////////////////////

// ���� ��� ���������������� callback �������
enum {MUSICBURN_WRITE = 0, MUSICBURN_BUFFER};

// ��������� �� ���������������� callback ������� ��� ������� Music CD
typedef VOID (CALLBACK *PMUSICBURNCALLBACK)(__int32 iAction, __int32 iParamOne, __int32 iParamTwo);

// �������� Music CD
AOPDLLEXPORT __int32 AOPMusicCDInit(PDEVICEINFO pDeviceInfo);

// ������������ �������� ������� ��� �������� Music CD
AOPDLLEXPORT __int32 AOPMusicCDFree();

// ���������� ��������
AOPDLLEXPORT __int32 __stdcall AOPMusicCDAddFolder(PWCHAR pwcFolder);

// ���������� �����
AOPDLLEXPORT __int32 AOPMusicCDAddFile(PWCHAR pwcFilePath);

// ��������� �� ���� ������� ����� ��������� �����
AOPDLLEXPORT __int32 AOPMusicCDTreeUp();

// ������ Music CD
AOPDLLEXPORT __int32 AOPMusicCDBurn(PMUSICBURNCALLBACK pCallback, __int32 iSpeed, PWCHAR pwcVolume);


//////////////////////////////////////////////////////////////////////////
// ������� ����������� �����
//
//////////////////////////////////////////////////////////////////////////

enum {ENCODE_POS = 0};

// ��������� �� ���������������� callback ������� ��� �����������
typedef VOID (CALLBACK *PENCODECALLBACK)(__int32 iAction, __int32 iParamOne, __int32 iParamTwo);

// ����������� � WMA
AOPDLLEXPORT __int32 AOPEncodeWMA(PWCHAR pwcInFile, PWCHAR pwcOutFile, PWCHAR pwcTitle, PWCHAR pwcAuthor, PWCHAR pwcAlbumTitle, PWCHAR pwcGenre, PWCHAR pwcYear, __int32 iBitrate, PENCODECALLBACK pCallback);

// ����������� � MP3
AOPDLLEXPORT __int32 AOPEncodeMP3(PWCHAR pwcInFile, PWCHAR pwcOutFile, __int32 iBitrate, PENCODECALLBACK pCallback);

// ����������� � OGG
AOPDLLEXPORT __int32 AOPEncodeOGG(PWCHAR pwcInFile, PWCHAR pwcOutFile, PWCHAR pwcTitle, PWCHAR pwcAuthor, PWCHAR pwcAlbumTitle, PWCHAR pwcGenre, PWCHAR pwcYear, __int32 iBitrate, PENCODECALLBACK pCallback);

// ����������� � WAV
AOPDLLEXPORT __int32 AOPEncodeWAV(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback);

// ����������� � FLAC
AOPDLLEXPORT __int32 AOPEncodeFLAC(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback);

// ����������� � APE
AOPDLLEXPORT __int32 AOPEncodeAPE(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback);

// ����������� � WV
AOPDLLEXPORT __int32 AOPEncodeWV(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback);

// ����������� � TTA
// AOPDLLEXPORT __int32 AOPEncodeTTA(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback);

//////////////////////////////////////////////////////////////////////////
// ������� ������� �����
//
//////////////////////////////////////////////////////////////////////////

// ��������� �� ���������������� callback ������� ��� ������� �����
typedef VOID (CALLBACK *PANALYZECALLBACK)(__int32 iAction, __int32 iParamOne, __int32 iParamTwo);

// ������ ���������� �����
AOPDLLEXPORT __int32 AOPAnalyzerTrack(PWCHAR pwcFile, PFLOAT pfK, PANALYZECALLBACK pCallBack);

#endif
