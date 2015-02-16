#ifndef __AOPDECODER_H
#define __AOPDECODER_H

#define AOPDLLEXPORT

//////////////////////////////////////////////////////////////////////////
//
// ОБЩИЕ ФУНКЦИИ
//
//////////////////////////////////////////////////////////////////////////

// инициализация
AOPDLLEXPORT __int32 AOPInit();

// освобождение ресурсов
AOPDLLEXPORT __int32 AOPFree();

//////////////////////////////////////////////////////////////////////////
//
// ФУНКЦИИ РАБОТЫ С МЕДИАФАЙЛАМИ
//
//////////////////////////////////////////////////////////////////////////

// декодирование
enum {DECODE_STOP = 0, DECODE_POS, DECODE_ERROR};

typedef void (CALLBACK *PDECODECALLBACK)(__int32 dwAction, __int32 dwParamOne, __int32 dwParamTwo);

AOPDLLEXPORT __int32 AOPDecode(PWCHAR pwcInFile, PWCHAR pwcOutFile, PDECODECALLBACK pCallBack);

// проигрывание
AOPDLLEXPORT __int32 AOPPlay(PWCHAR pwcFileName);

// установка позиции проигрывания
AOPDLLEXPORT __int32 AOPPlayPosition(float fPos);

// остановка проигрывания
AOPDLLEXPORT __int32 AOPStop();

// получение текущей позиции
AOPDLLEXPORT float AOPGetPos();

// получение длины трека
AOPDLLEXPORT float AOPGetLen(WCHAR* pwcFileName);

// получение значения громкости
AOPDLLEXPORT unsigned __int32 AOPGetVolume();

// установка значения громкости
AOPDLLEXPORT __int32 AOPSetVolume(unsigned __int32 uiVolume);

// получение тегов трека
AOPDLLEXPORT __int32 AOPGetTags(PWCHAR pwcFileName, PWCHAR pwcArtist, PWCHAR pwcAlbum, PWCHAR pwcTitle);

// перевод секунд в байты
AOPDLLEXPORT __int32 AOPSeconds2Bytes(float fSeconds);

//////////////////////////////////////////////////////////////////////////
// ФУНКЦИИ РАБОТЫ С CD/DVD
//
//////////////////////////////////////////////////////////////////////////

// информация об устройстве
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

// информация о диске
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

// получение информации о диске
AOPDLLEXPORT __int32 AOPGetDiscInfo(PDEVICEINFO pDeviceInfo, PDISCINFO pDiscInfo, PTOCINFOCALLBACK pCallBack);

// load диска
AOPDLLEXPORT __int32 AOPLoadTray(PDEVICEINFO pDeviceInfo);

// eject диска
AOPDLLEXPORT __int32 AOPEjectTray(PDEVICEINFO pDeviceInfo);

// очистка диска CD/DVD
AOPDLLEXPORT __int32 AOPBlank(PDEVICEINFO pDeviceInfo, __int8 bFull);

// получение примерного времение очистки диска
AOPDLLEXPORT float AOPGetBlankTime(PDEVICEINFO pDeviceInfo, __int8 bFull);

// получение скоростей записи CD диска
AOPDLLEXPORT __int32 AOPGetWriteSpeeds(PDEVICEINFO pDeviceInfo, PWCHAR pwcSpeeds);

// получение скоростей чтения CD диска
AOPDLLEXPORT __int32 AOPGetReadSpeeds(PDEVICEINFO pDeviceInfo, PWCHAR pwcSpeeds);

// проверка на наличие чистого CD
AOPDLLEXPORT __int32 AOPIsBlankCD(PDEVICEINFO pDeviceInfo);

// блокировка устройства
AOPDLLEXPORT __int32 AOPLock(PDEVICEINFO pDeviceInfo);

// разблокировка устройства
AOPDLLEXPORT __int32 AOPUnLock(PDEVICEINFO pDeviceInfo);


//////////////////////////////////////////////////////////////////////////
// ФУНКЦИИ РАБОТЫ С AUDIO CD 
//
//////////////////////////////////////////////////////////////////////////

// коды для пользовательской callback функции
enum {AUDIOBURN_WRITE = 0, AUDIOBURN_BUFFER, AUDIORIP_READ};

// указатель на пользовательскую callback функцию для прожига Audio CD
typedef VOID (CALLBACK *PAUDIOBURNCALLBACK)(__int32 iAction, __int32 iParamOne, __int32 iParamTwo);

// создание Audio CD
AOPDLLEXPORT __int32 AOPAudioCDInit(PDEVICEINFO pDeviceInfo);

// освобождение ресурсов занятых при создании Audio CD
AOPDLLEXPORT __int32 AOPAudioCDFree();

// добавление трека
AOPDLLEXPORT __int32 AOPAudioCDAddTrack(PWCHAR pwcPath);

// установка тегов аудио трека
AOPDLLEXPORT __int32 AOPAudioCDSetTitle(unsigned __int8 ucTrack, PWCHAR pwcArtist, PWCHAR pwcTitle);

// прожиг Audio CD
AOPDLLEXPORT __int32 AOPAudioCDBurn(PAUDIOBURNCALLBACK pCallback, __int32 iSpeed);

// указатель на пользовательскую функцию
typedef VOID (CALLBACK *PAUDIORIPCALLBACK)(__int32 iAction, __int32 iParamOne, __int32 iParamTwo);

// Rip Audio CD
AOPDLLEXPORT __int32 AOPAudioCDRip(__int32 iTrack, PWCHAR pwcPath, PAUDIORIPCALLBACK pCallback, __int32 iSpeed);

// Отмена операции риппинга
AOPDLLEXPORT __int32 AOPAudioCDRipCancel();

// проигрывание трека Audio CD
AOPDLLEXPORT __int32 AOPAudioCDPlay(__int32 iDrive, __int32 iTrack);

// получение CD-Text
AOPDLLEXPORT __int32 AOPAudioCDGetText(__int32 iDrive, PWCHAR pwcText);

// получение CDDB identifier
AOPDLLEXPORT __int32 AOPAudioCDGetCDDB(__int32 iDrive, PWCHAR pwcCDDB);

//////////////////////////////////////////////////////////////////////////
// ФУНКЦИИ РАБОТЫ С МУЗЫКАЛЬНЫМИ (MP3) ДИСКАМИ
//
//////////////////////////////////////////////////////////////////////////

// коды для пользовательской callback функции
enum {MUSICBURN_WRITE = 0, MUSICBURN_BUFFER};

// указатель на пользовательскую callback функцию для прожига Music CD
typedef VOID (CALLBACK *PMUSICBURNCALLBACK)(__int32 iAction, __int32 iParamOne, __int32 iParamTwo);

// создание Music CD
AOPDLLEXPORT __int32 AOPMusicCDInit(PDEVICEINFO pDeviceInfo);

// освобождение ресурсов занятых при создании Music CD
AOPDLLEXPORT __int32 AOPMusicCDFree();

// добавление каталога
AOPDLLEXPORT __int32 __stdcall AOPMusicCDAddFolder(PWCHAR pwcFolder);

// добавление файла
AOPDLLEXPORT __int32 AOPMusicCDAddFile(PWCHAR pwcFilePath);

// подняться на один уровень вверх структуры диска
AOPDLLEXPORT __int32 AOPMusicCDTreeUp();

// прожиг Music CD
AOPDLLEXPORT __int32 AOPMusicCDBurn(PMUSICBURNCALLBACK pCallback, __int32 iSpeed, PWCHAR pwcVolume);


//////////////////////////////////////////////////////////////////////////
// ФУНКЦИИ КОДИРОВАНИЯ ЗВУКА
//
//////////////////////////////////////////////////////////////////////////

enum {ENCODE_POS = 0};

// указатель на пользовательскую callback функцию для кодирования
typedef VOID (CALLBACK *PENCODECALLBACK)(__int32 iAction, __int32 iParamOne, __int32 iParamTwo);

// кодирование в WMA
AOPDLLEXPORT __int32 AOPEncodeWMA(PWCHAR pwcInFile, PWCHAR pwcOutFile, PWCHAR pwcTitle, PWCHAR pwcAuthor, PWCHAR pwcAlbumTitle, PWCHAR pwcGenre, PWCHAR pwcYear, __int32 iBitrate, PENCODECALLBACK pCallback);

// кодирование в MP3
AOPDLLEXPORT __int32 AOPEncodeMP3(PWCHAR pwcInFile, PWCHAR pwcOutFile, __int32 iBitrate, PENCODECALLBACK pCallback);

// кодирование в OGG
AOPDLLEXPORT __int32 AOPEncodeOGG(PWCHAR pwcInFile, PWCHAR pwcOutFile, PWCHAR pwcTitle, PWCHAR pwcAuthor, PWCHAR pwcAlbumTitle, PWCHAR pwcGenre, PWCHAR pwcYear, __int32 iBitrate, PENCODECALLBACK pCallback);

// кодирование в WAV
AOPDLLEXPORT __int32 AOPEncodeWAV(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback);

// кодирование в FLAC
AOPDLLEXPORT __int32 AOPEncodeFLAC(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback);

// кодирование в APE
AOPDLLEXPORT __int32 AOPEncodeAPE(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback);

// кодирование в WV
AOPDLLEXPORT __int32 AOPEncodeWV(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback);

// кодирование в TTA
// AOPDLLEXPORT __int32 AOPEncodeTTA(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback);

//////////////////////////////////////////////////////////////////////////
// ФУНКЦИИ АНАЛИЗА ЗВУКА
//
//////////////////////////////////////////////////////////////////////////

// указатель на пользовательскую callback функцию для анализа файла
typedef VOID (CALLBACK *PANALYZECALLBACK)(__int32 iAction, __int32 iParamOne, __int32 iParamTwo);

// анализ указанного файла
AOPDLLEXPORT __int32 AOPAnalyzerTrack(PWCHAR pwcFile, PFLOAT pfK, PANALYZECALLBACK pCallBack);

#endif
