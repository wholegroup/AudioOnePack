#define WINVER 0x0501

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "../AOPDecoder/AOPDecoder.h"

//
VOID CALLBACK PlayCallBack(UINT uiTimerID, UINT uiMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

//
VOID CALLBACK DecodeCallBack(__int32 dwAction, __int32 dwParamOne, __int32 dwParamTwo);

//
VOID CALLBACK FindCallBack(DEVICEINFO pDeviceInfo);

//
VOID CALLBACK TOCCallBack(TOCINFO tocInfo);

//
VOID CALLBACK GetAudioCallBack(TOCINFO tocInfo);

//
VOID CALLBACK AudioBurnCallBack(__int32 dwAction, __int32 dwParamOne, __int32 dwParamTwo);

//
VOID CALLBACK AudioRipCallBack(__int32 dwAction, __int32 dwParamOne, __int32 dwParamTwo);

//
VOID CALLBACK EncodeCallback(__int32 dwAction, __int32 dwParamOne, __int32 dwParamTwo);

//
VOID CALLBACK MusicBurnCallBack(__int32 iAction, __int32 iParamOne, __int32 iParamTwo);

//
HANDLE hDecodeEvent; 

//
HANDLE hPlayEvent;   

//
DEVICEINFO devWork;

//
int wmain(INT iArgC, WCHAR* pwcArgv[])
{
	//
	AOPInit();

	// получение списка устройств
	AOPGetDevices(FindCallBack);

	/*
	__try
	{
		// создание музыкального диска
		if (ERROR_SUCCESS != AOPMusicCDInit(&devWork))
		{
			wprintf(L"AOPMusicCDInit\n");

			__leave;
		}

		if (ERROR_SUCCESS != AOPMusicCDAddFolder(L"TestIso"))
		{
			wprintf(L"AOPMusicCDAddFolder\n");

			__leave;
		}

		if (ERROR_SUCCESS != AOPMusicCDAddFile(L".\\TestISO\\01.mp3"))
		{
			wprintf(L"AOPMusicCDAddFile (01.mp3)\n");

			__leave;
		}

		if (ERROR_SUCCESS != AOPMusicCDTreeUp())
		{
			wprintf(L"AOPMusicCDTreeUp\n");

			__leave;
		}

		if (ERROR_SUCCESS != AOPMusicCDAddFile(L".\\TestISO\\02.mp3"))
		{
			wprintf(L"AOPMusicCDAddFile (02.mp3)\n");

			__leave;
		}

		if (ERROR_SUCCESS != AOPMusicCDBurn(MusicBurnCallBack, 1, L"July 26, 2007"))
		{
			wprintf(L"AOPMusicCDBurn\n");

			__leave;
		}
	}

	__finally
	{
		AOPMusicCDFree();
	}

	wprintf(L"Music CD is created!\n");
	*/

	/*
	AOPEjectTray(&devWork);
	AOPLoadTray(&devWork);
	*/

	/*
	printf("AOPGetLen = %f\n", AOPGetLen(L"c:\\temp\\37916227\\single2.wav"));
	*/

	// кодирование в WAV
	//AOPEncodeWAV(L"in.wav", L"out.wav", EncodeCallback);

	// кодирование в WMA
	//DWORD dwStart = GetTickCount();
	//AOPEncodeWMA(L"in.wav", L"out.wma", L"To Have And To Hold", L"Depeche Mode", 
	//	L"Music For The Masses", L"Rock", L"1999", 160000, EncodeCallback);
	//DWORD dwStop = GetTickCount();
	//printf("time = %0.1f\n", (dwStop - dwStart) / 1000.);

	// кодирование в MP3
	//DWORD dwStart = GetTickCount();
	//AOPEncodeMP3(L"in.wav", L"out.mp3", 192, EncodeCallback);
	//DWORD dwStop = GetTickCount();
	//printf("time = %0.1f\n", (dwStop - dwStart) / 1000.);

	// кодирование в OGG
	//DWORD dwStart = GetTickCount();
	//AOPEncodeOGG(L"in.wav", L"out.ogg", L"To Have And To Hold", L"Depeche Mode", 
	//	L"Music For The Masses", L"Rock", L"1999", 128000, EncodeCallback);
	//DWORD dwStop = GetTickCount();
	//printf("time = %0.1f\n", (dwStop - dwStart) / 1000.);

	// кодирование в TTA
	//DWORD dwStart = GetTickCount();
	//if (ERROR_SUCCESS != AOPEncodeTTA(L"in.wav", L"out.tta", EncodeCallback))
	//{
	//	printf("ERROR AOPEncodeTTA\n");
	//}
	//DWORD dwStop = GetTickCount();
	//printf("\ntime = %0.1f\n", (dwStop - dwStart) / 1000.);

	// кодирование в WV
	//DWORD dwStart = GetTickCount();
	//if (ERROR_SUCCESS != AOPEncodeWV(L"in.wav", L"out.wv", EncodeCallback))
	//{
	//	printf("ERROR AOPEncodeWV\n");
	//}
	//DWORD dwStop = GetTickCount();
	//printf("\ntime = %0.1f\n", (dwStop - dwStart) / 1000.);

	// кодирование в FLAC
	//DWORD dwStart = GetTickCount();
	//if (ERROR_SUCCESS != AOPEncodeFLAC(L"in.wav", L"out.flac", EncodeCallback))
	//{
	//	printf("ERROR AOPEncodeFLAC\n");
	//}
	//DWORD dwStop = GetTickCount();
	//printf("\ntime = %0.1f\n", (dwStop - dwStart) / 1000.);

	// кодирование в APE
	DWORD dwStart = GetTickCount();
	if (ERROR_SUCCESS != AOPEncodeAPE(L"in.wav", L"out.ape", EncodeCallback))
	{
		printf("ERROR AOPEncodeAPE\n");
	}
	DWORD dwStop = GetTickCount();
	printf("\ntime = %0.1f\n", (dwStop - dwStart) / 1000.);

	/*
	// получение списка аудио треков диска
	DISCINFO diskInfo;

	AOPGetDiscInfo(&devWork, &diskInfo, (PTOCINFOCALLBACK)GetAudioCallBack);
	*/

	/*
	// RIP трека
	AOPAudioCDInit(&devWork);
	AOPAudioCDRip(9, L"09.wav", AudioRipCallBack, 8);
	AOPAudioCDFree();
	*/

	/*
	// тестирование проигрывания Audio CD
	hPlayEvent = CreateEvent(NULL, FALSE, FALSE, L"{2239C044-8694-4a78-BBFC-8D8BDFA2C531}");

	if (ERROR_SUCCESS == AOPAudioCDPlay(0, 1))
	{
		AOPPlayPosition(3.);

		MMRESULT mmrTimerID;

		mmrTimerID = timeSetEvent(1000, 50, (LPTIMECALLBACK)&PlayCallBack, 0, TIME_PERIODIC);
		if (mmrTimerID)
		{
			WaitForSingleObject(hPlayEvent, INFINITE);
			timeKillEvent(mmrTimerID);

			AOPStop();
		}
	}

	CloseHandle(hPlayEvent);
	*/

	// чтение CD-Text
	/*
	PWCHAR pwcText;

	pwcText = new WCHAR[10000];
	
	ZeroMemory(pwcText, 10000 * sizeof(WCHAR));

	AOPAudioCDGetText(1, pwcText);

	printf("%S", pwcText);
	
	delete [] pwcText;
	*/

	// чтение CDDB identifier
	/*
	PWCHAR pwcCDDB;
	
	pwcCDDB = new WCHAR[10000];

	ZeroMemory(pwcCDDB, 10000 * sizeof(WCHAR));

	AOPAudioCDGetCDDB(1, pwcCDDB);

	printf("%S", pwcCDDB);
	
	delete [] pwcCDDB;
	*/

	/*
	// проверка наличия чистого CD
	if (1 == AOPIsBlankCD(&devWork))
	{
		wprintf(L"BLANK\n");
	}
	else
	{
		wprintf(L"NOT BLANK\n");
	}
	*/

	/*
	// проверка блокировки
	// AOPLock(&devWork);
	AOPUnLock(&devWork);
	*/

	/*
	// получение скоростей чтения
	WCHAR pwcSpeeds[200];

	RtlZeroMemory(pwcSpeeds, sizeof(pwcSpeeds));
	AOPGetReadSpeeds(&devWork, pwcSpeeds);
	wprintf(L"read %s\n", pwcSpeeds);
	
	// получение скоростей записи
	RtlZeroMemory(pwcSpeeds, sizeof(pwcSpeeds));
	AOPGetWriteSpeeds(&devWork, pwcSpeeds);
	wprintf(L"write %s\n", pwcSpeeds);
	*/

	/*
	// получение информации о диске
	DISCINFO diskInfo;

	AOPGetDiscInfo(&devWork, &diskInfo, (PTOCINFOCALLBACK)TOCCallBack);
	wprintf(L"\nType: %s\n", diskInfo.pwcDiscType);
	wprintf(L"Used space: %d bytes\n", diskInfo.iUsedSpace);
	wprintf(L"Free space: %d bytes\n", diskInfo.iFreeSpace);
	*/

	/*
	// создание и запись Audio CD
	while (1)
	{
		if (ERROR_SUCCESS != AOPAudioCDInit(&devWork, AudioBurnCallBack))
		{
			wprintf(L"ERROR::AOPAudioCDInit\n");

			break;
		}

		for (int i = 0; i < 1; i++)
		{
			WCHAR pwcPath[MAX_PATH];

			ZeroMemory(pwcPath, sizeof(pwcPath));
			_swprintf(pwcPath, L"%02d.wav", i + 1);

			if (ERROR_SUCCESS != AOPAudioCDAddTrack(pwcPath))
			{
				wprintf(L"ERROR::AOPAudioCDAddTrack::%s\n", pwcPath);

				break;
			}
		}

		if (ERROR_SUCCESS != AOPAudioCDSetTitle(0, L"artist", L"album"))
		{
			wprintf(L"ERROR::AOPAudioCDSetTitle::0\n");

			break;
		}

		for (int i = 0; i < 4; i++)
		{
			if (ERROR_SUCCESS != AOPAudioCDSetTitle(i + 1, L"artist", L"title"))
			{
				wprintf(L"ERROR::AOPAudioCDSetTitle::%d\n", i + 1);

				break;
			}
		}

		if (ERROR_SUCCESS != AOPAudioCDBurn())
		{
			wprintf(L"ERROR::AOPAudioCDBurn");

			break;
		}

		if (ERROR_SUCCESS != AOPAudioCDFree())
		{
			wprintf(L"ERROR::AOPAudioCDFree\n");

			break;
		}

		AOPEjectTray(&devWork);

		break;
	}
	*/

	/*
	// получение тегов трека
	WCHAR pwcArtist[200];
	WCHAR pwcAlbum[200]; 
	WCHAR pwcTitle[200]; 

	AOPGetTags(L"01.mp3", pwcArtist, pwcAlbum, pwcTitle);
	wprintf(L"%s (%s) - %s", pwcArtist, pwcAlbum, pwcTitle);
	*/

	/*
	// тестирование очистки диска
	wprintf(L"Calculate erase time = %f\n", AOPGetBlankTime(&devWork, 1));

	DWORD dwStart = GetTickCount();

	AOPBlank(&devWork, 0);

	DWORD dwStop = GetTickCount();

	wprintf(L"blank time = %0.3fs\n", (FLOAT)(dwStop - dwStart) / 1000.);
	*/

	/*
	// тестирование установки громкости
	AOPSetVolume(100);
	wprintf(L"volume = %d\n", AOPGetVolume());
	*/
	
	/*
	// eject
	AOPEjectTray(&devWork);
	*/

	/*
	// тестирование проигрывания
	hPlayEvent = CreateEvent(NULL, FALSE, FALSE, L"{2239C044-8694-4a78-BBFC-8D8BDFA2C531}");

	if (ERROR_SUCCESS == AOPPlay(L"01.flac"))
	{
		AOPPlayPosition(3.);

		MMRESULT mmrTimerID;
		
		mmrTimerID = timeSetEvent(1000, 50, (LPTIMECALLBACK)&PlayCallBack, 0, TIME_PERIODIC);
		if (mmrTimerID)
		{
			WaitForSingleObject(hPlayEvent, INFINITE);
			timeKillEvent(mmrTimerID);

			AOPStop();
		}
	}

	CloseHandle(hPlayEvent);
	*/

	/*
	// тестирование декодирования
	hDecodeEvent = CreateEvent(NULL, FALSE, FALSE, L"{0DAFB5AA-223B-4eb3-9E41-8B2064E70F67}");
	if (ERROR_SUCCESS == AOPDecode(L"out.mp3", L"out2.wav", DecodeCallBack))
	{
		// ожидаем завершение декодирования
		WaitForSingleObject(hDecodeEvent, INFINITE);
	}

	CloseHandle(hDecodeEvent);
	*/

	// получение длины трека
	// wprintf(L"%f\n", AOPGetLen(L"01.wav"));
	//wprintf(L"%d\n", AOPSeconds2Bytes(AOPGetLen(L"01.wav")));

	AOPFree();

	return 0;
}

//
VOID CALLBACK PlayCallBack(UINT uiTimerID, UINT uiMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	FLOAT fPos, fLen;

	fPos = AOPGetPos();
	fLen = AOPGetLen(NULL);

	wprintf(L"%f %f\n", fPos, fLen);

	if (fPos > 20)
	{
		SetEvent(hPlayEvent);
	}
}

//
VOID CALLBACK DecodeCallBack(__int32 dwAction, __int32 dwParamOne, __int32 dwParamTwo)
{
	switch (dwAction)
	{
		case DECODE_STOP:
			wprintf(L"STOP DECODE\n");
			SetEvent(hDecodeEvent);
			break;

		case DECODE_POS:
			wprintf(L"POS DECODE %d %d\n", dwParamOne, dwParamTwo);
			break;

		case DECODE_ERROR:
			wprintf(L"ERROR DECODE\n");
			SetEvent(hDecodeEvent);
			break;
	}
}

//
VOID CALLBACK FindCallBack(DEVICEINFO pDeviceInfo)
{
	wprintf(L"%s %s\n", pDeviceInfo.pwLetter, pDeviceInfo.pwName);

	if (0 == wcscmp(pDeviceInfo.pwLetter, L"E:"))
	{
		devWork = pDeviceInfo;
	}
}

//
VOID CALLBACK TOCCallBack(TOCINFO tocInfo)
{
	switch (tocInfo.uiTrackMode)
	{
		case 0:
			wprintf(L"Audio, ");
			break;

		case 1:
			wprintf(L"MODE1, ");
			break;

		case 2:
			wprintf(L"MODE2, ");
			break;

		default:
			wprintf(L"UNKNOW, ");
	}

	wprintf(L"Session %d, Track %02d, ", tocInfo.uiSessionNumber, tocInfo.uiTrackNumber);

	if (0 == tocInfo.uiTrackMode)
	{
		ULONG StartLBASec = tocInfo.iStartingLBA / 75;
		ULONG FinishLBASec = tocInfo.iEndingLBA /75;

		wprintf(L"Start: %.2d:%.2d  Finish: %.2d:%.2d  Length: %.2d:%.2d, ",
			(int)StartLBASec / 60,
			StartLBASec % 60,
			(int)FinishLBASec / 60,
			FinishLBASec % 60,
			(int) (FinishLBASec - StartLBASec) / 60,
			(FinishLBASec - StartLBASec) % 60);
	}

	LARGE_INTEGER SizeInUCHARs;
	SizeInUCHARs.QuadPart = tocInfo.iEndingLBA - tocInfo.iStartingLBA;
	SizeInUCHARs.QuadPart *= tocInfo.uiLBSizeInUCHARs;

	wprintf(L"Size: %.2f Mb\n", (DOUBLE)SizeInUCHARs.QuadPart/(1024*1024));
}

//
VOID CALLBACK AudioBurnCallBack(__int32 dwAction, __int32 dwParamOne, __int32 dwParamTwo)
{
	switch (dwAction)
	{
		case AUDIOBURN_WRITE:
			wprintf(L"Write %d%%\n", dwParamOne);
			break;

		case AUDIOBURN_BUFFER:
			wprintf(L"Buffer %d%%\n", dwParamOne);
			break;
	}
}

//
VOID CALLBACK GetAudioCallBack(TOCINFO tocInfo)
{
	if (0 != tocInfo.uiTrackMode)
	{
		return;
	}

	wprintf(L"Session %d, Track %02d, ", tocInfo.uiSessionNumber, tocInfo.uiTrackNumber);

	ULONG StartLBASec = tocInfo.iStartingLBA / 75;
	ULONG FinishLBASec = tocInfo.iEndingLBA /75;

	wprintf(L"%d %d\n", tocInfo.iStartingLBA, tocInfo.iEndingLBA);
	wprintf(L"Start: %02d:%02d.%02d  Finish: %02d:%02d.%02d  Length: %02d:%02d.%02d, ",
		(int)StartLBASec / 60,
		StartLBASec % 60,
		tocInfo.iStartingLBA % 75,
		(int)FinishLBASec / 60,
		FinishLBASec % 60,
		tocInfo.iEndingLBA % 75,
		(int) (tocInfo.iEndingLBA - tocInfo.iStartingLBA + 1) / (60 * 75),
		(tocInfo.iEndingLBA - tocInfo.iStartingLBA + 1) / 75 % 60,
		(tocInfo.iEndingLBA - tocInfo.iStartingLBA + 1) % 75);

	__int64 iSizeInUCHARs;

	iSizeInUCHARs = tocInfo.iEndingLBA - tocInfo.iStartingLBA;
	iSizeInUCHARs *= tocInfo.uiLBSizeInUCHARs; // 2352

	wprintf(L"Size: %.2f Mb\n", (DOUBLE)iSizeInUCHARs / (1024*1024));
}

//
VOID CALLBACK AudioRipCallBack(__int32 dwAction, __int32 dwParamOne, __int32 dwParamTwo)
{
	switch (dwAction)
	{
		case AUDIORIP_READ:
			wprintf(L"Read %d%%\n", dwParamOne);
			break;
	}
}

//
VOID CALLBACK EncodeCallback(__int32 dwAction, __int32 dwParamOne, __int32 dwParamTwo)
{
	switch (dwAction)
	{
		case ENCODE_POS:
			wprintf(L"encode %d %d\r", dwParamOne, dwParamTwo);
			break;
	}
}

//
VOID CALLBACK MusicBurnCallBack(__int32 iAction, __int32 iParamOne, __int32 iParamTwo)
{
	switch (iAction)
	{
		case MUSICBURN_WRITE:
			wprintf(L"Write %d%%\n", iParamOne);
			break;

		case MUSICBURN_BUFFER:
			wprintf(L"Buffer %d%%\n", iParamOne);
			break;
	}
}
