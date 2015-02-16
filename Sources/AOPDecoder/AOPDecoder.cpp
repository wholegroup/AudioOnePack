/*
 * Copyright (C) 2015 Andrey Rychkov <wholegroup@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <math.h>

#include "AOPDecoder.h"

//
#include "../bass24/c/bass.h"
#include "../tags17/c/tags.h"
#include "../basswm24/c/basswma.h"
#include "../basscd24/c/basscd.h"

//
#define _BLADEDLL

#include "../lame-3.99.5/Dll/BladeMP3EncDLL.h"

//
#include "../libvorbis-1.3.4/include/vorbis/vorbisenc.h"

// needs to be upgraded v2 to support unicode filenames
// #include "../ttalib-1.1-src/TTALib.h"

//
#include "../wavpackdll/wavpack.h"

//
#include "../flac-1.3.1/include/FLAC/metadata.h"
#include "../flac-1.3.1/include/FLAC/stream_encoder.h"

//
#define PLATFORM_WINDOWS

#include "../MAC_SDK_413/Shared/All.h"

typedef APE::str_ansi  str_ansi;
typedef APE::str_utf16 str_utf16;

#include "../MAC_SDK_413/Shared/MACLib.h"

typedef APE::APE_DECOMPRESS_FIELDS APE_DECOMPRESS_FIELDS;

#include "../MAC_SDK_413/Shared/MACDll.h"

//
#include "../StarBurn/StarBurn.h"
#include "../StarBurn/StarBurnKey.h"

////////////////////////////////	//////////////////////////////////////////
// ДЛЯ ОТЛАДКИ
//
#if _DEBUG
	#define MYDEBUGMSG(...)                                    \
	{                                                          \
		FILE *hFile;                                            \
		hFile = _wfopen(L"c:\\aopapi.txt", L"a");               \
		SYSTEMTIME st;                                          \
		ZeroMemory(&st, sizeof(st));                            \
		GetLocalTime(&st);                                      \
		fwprintf(hFile,                                         \
		L"[%02i.%02i.%04i %02i:%02i.%02i] ",                    \
		st.wDay,                                                \
		st.wMonth,                                              \
		st.wYear,                                               \
		st.wHour,                                               \
		st.wMinute,                                             \
		st.wSecond);                                            \
		fwprintf(hFile, __VA_ARGS__);                           \
		fwprintf(hFile, L"\n");                                 \
		fclose(hFile);                                          \
	}
#else
	#define MYDEBUGMSG(...)
#endif


//////////////////////////////////////////////////////////////////////////

struct CDDVD_SPEED
{		
	ULONG ulSpeedInKBps;  
	PCHAR pSpeedX;     
};

#define CD_STANDARD_SPEED_COUNT 16

CDDVD_SPEED g_CDStandardSpeeds[CD_STANDARD_SPEED_COUNT] =
{
	{CD_SPEED_IN_KBPS_1X,   "1.0x"},
	{CD_SPEED_IN_KBPS_2X,   "2.0x"},
	{CD_SPEED_IN_KBPS_2P2X, "2.2x"},
	{CD_SPEED_IN_KBPS_3X,   "3.0x"},
	{CD_SPEED_IN_KBPS_4X,   "4.0x"},
	{CD_SPEED_IN_KBPS_8X,   "8.0x"},
	{CD_SPEED_IN_KBPS_10X,  "10.0x"},
	{CD_SPEED_IN_KBPS_12X,  "12.0x"},
	{CD_SPEED_IN_KBPS_16X,  "16.0x"},
	{CD_SPEED_IN_KBPS_20X,  "20.0x"},
	{CD_SPEED_IN_KBPS_24X,  "24.0x"},
	{CD_SPEED_IN_KBPS_32X,  "32.0x"},
	{CD_SPEED_IN_KBPS_40X,  "40.0x"},
	{CD_SPEED_IN_KBPS_44X,  "44.0x"},
	{CD_SPEED_IN_KBPS_48X,  "48.0x"},
	{CD_SPEED_IN_KBPS_52X,"  52.0x"}
};


//
HSTREAM hPlayStream;

//
HSTREAM hDecodeStream;

//
HANDLE hDecodeThread;

//
DWORD dwDecodeThreadID;

//
PDECODECALLBACK DecodeCallBack;

//
PWCHAR pwcDecodeOut;

//
PFINDCALLBACK UserFindCallback;

//
DWORD WINAPI DecodeThread(LPVOID lpParam);

//
void __stdcall FindCallback(IN CALLBACK_NUMBER p__CALLBACK_NUMBER, IN PVOID p__PVOID__CallbackContext, 
	IN PVOID p__PVOID__CallbackSpecial1, IN PVOID p__PVOID__CallbackSpecial2);

// размер TOC на CD
#define CD_TOC_SIZE_IN_MB  40

// размер TOC на DVD
#define DVD_TOC_SIZE_IN_MB 700

//////////////////////////////////////////////////////////////////////////
// входная точка в DLL
//
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:

			break;

		case DLL_PROCESS_DETACH:
			break;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// Инициализация
//
AOPDLLEXPORT __int32 AOPInit()
{
	// проверка версии BASS
	if (BASSVERSION != HIWORD(BASS_GetVersion()))
	{
		MessageBox(HWND_DESKTOP, L"An incorrect version of BASS.DLL was loaded", 0, MB_OK | MB_ICONERROR);

		return ERROR_ACCESS_DENIED;
	}

	// инициализация BASS
	if (FALSE == BASS_Init(-1, 44100, 0, 0, NULL))
	{
		MessageBox(HWND_DESKTOP, L"Can't initialize sound device", 0, MB_OK | MB_ICONERROR);
	
		return ERROR_ACCESS_DENIED;
	}

	// загрузка плагинов
	if (0 == BASS_PluginLoad((char*)L"bass_aac.dll", BASS_UNICODE))
	{
		MessageBox(HWND_DESKTOP, L"Error loading bass_aac.dll", 0, MB_OK | MB_ICONERROR);

		return ERROR_OPEN_FAILED;
	}

	/*
	if (0 == BASS_PluginLoad((char*)L"bass_aach.dll", BASS_UNICODE))
	{
		MessageBox(HWND_DESKTOP, L"Error loading bass_aach.dll", 0, MB_OK | MB_ICONERROR);

		return ERROR_OPEN_FAILED;
	}
	*/

	if (0 == BASS_PluginLoad((char*)L"bass_ac3.dll", BASS_UNICODE))
	{
		MessageBox(HWND_DESKTOP, L"Error loading bass_ac3.dll", 0, MB_OK | MB_ICONERROR);

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"bass_alac.dll", BASS_UNICODE))
	{
		MessageBox(HWND_DESKTOP, L"Error loading bass_alac.dll", 0, MB_OK | MB_ICONERROR);

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"bass_ape.dll", BASS_UNICODE))
	{
		MessageBox(HWND_DESKTOP, L"Error loading bass_ape.dll", 0, MB_OK | MB_ICONERROR);

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"bass_mpc.dll", BASS_UNICODE))
	{
		MessageBox(HWND_DESKTOP, L"Error loading bass_mpc.dll", 0, MB_OK | MB_ICONERROR);

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"bass_ofr.dll", BASS_UNICODE))
	{
		MessageBox(HWND_DESKTOP, L"Error loading bass_ofr.dll", 0, MB_OK | MB_ICONERROR);

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"bass_spx.dll", BASS_UNICODE))
	{
		MessageBox(HWND_DESKTOP, L"Error loading bass_spx.dll", 0, MB_OK | MB_ICONERROR);

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"bass_tta.dll", BASS_UNICODE))
	{
		MessageBox(HWND_DESKTOP, L"Error loading bass_tta.dll", 0, MB_OK | MB_ICONERROR);

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"basswv.dll", BASS_UNICODE))
	{
		MessageBox(HWND_DESKTOP, L"Error loading bass_wv.dll", 0, MB_OK | MB_ICONERROR);

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"basscd.dll", BASS_UNICODE))
	{
		MessageBox(HWND_DESKTOP, L"Error loading basscd.dll", 0, MB_OK | MB_ICONERROR);

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"bassflac.dll", BASS_UNICODE))
	{
		MessageBox(HWND_DESKTOP, L"Error loading bassflac.dll", 0, MB_OK | MB_ICONERROR);

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"basswma.dll", BASS_UNICODE))
	{
		MessageBox(HWND_DESKTOP, L"Error loading basswma.dll", 0, MB_OK | MB_ICONERROR);

		return ERROR_OPEN_FAILED;
	}

	// инициализация StarBurn
	if (EN_SUCCESS != StarBurn_UpStartEx(&g__UCHAR__RegistrationKey, sizeof(g__UCHAR__RegistrationKey)))
	{
		MessageBox(HWND_DESKTOP, L"Error loading StarBurn.dll", 0, MB_OK | MB_ICONERROR);

		return ERROR_OPEN_FAILED;
	}

	// инициализация переменных
	hPlayStream    = 0;
	hDecodeStream  = 0;
	hDecodeThread  = NULL;
	DecodeCallBack = NULL;
	pwcDecodeOut   = NULL;

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// Освобождение используемых ресурсов
//
AOPDLLEXPORT __int32 AOPFree()
{
	if (NULL != hDecodeThread)
	{
		CloseHandle(hDecodeThread);
	}

	if (hPlayStream)
	{
		BASS_StreamFree(hPlayStream);
	}

	if (hDecodeStream)
	{
		BASS_StreamFree(hDecodeStream);
	}

	// деинициализация BASS
	BASS_PluginFree(0);
	BASS_Free();

	// деинициализация StarBurn
	StarBurn_DownShut();

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// проигрывание
//
AOPDLLEXPORT __int32 AOPPlay(PWCHAR pwcFileName)
{
	if (hPlayStream)
	{
		BASS_StreamFree(hPlayStream);
	}

	if (NULL == pwcFileName)
	{
		return ERROR_OPEN_FAILED;
	}

	hPlayStream = BASS_StreamCreateFile(FALSE, pwcFileName, 0, 0, BASS_SAMPLE_FLOAT | BASS_UNICODE);

	if (0 == hPlayStream)
	{
		return ERROR_INVALID_HANDLE;
	}

	BASS_ChannelPlay(hPlayStream, TRUE);

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// проигрывание трека Audio CD
//
AOPDLLEXPORT __int32 AOPAudioCDPlay(__int32 iDrive, __int32 iTrack)
{
	if (hPlayStream)
	{
		BASS_StreamFree(hPlayStream);
	}

	hPlayStream = BASS_CD_StreamCreate(iDrive, iTrack, BASS_SAMPLE_FLOAT);

	if (0 == hPlayStream)
	{
		return ERROR_INVALID_HANDLE;
	}

	BASS_ChannelPlay(hPlayStream, TRUE);

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// получение CD-Text
//
AOPDLLEXPORT __int32 AOPAudioCDGetText(__int32 iDrive, PWCHAR pwcText)
{
	const char* pcText = NULL;
	PWCHAR pwcTmp;

	pcText = BASS_CD_GetID(iDrive, BASS_CDID_TEXT);

	if (pcText)
	{
		while (*pcText)
		{
			int iLen = (int)strlen(pcText) + 1; 

			pwcTmp = new WCHAR[iLen];

			ZeroMemory(pwcTmp, iLen * sizeof(WCHAR));

			wsprintf(pwcTmp, L"%S", pcText);
			wcscat(pwcText, pwcTmp);
			wcscat(pwcText, L"\n");
			
			pcText += iLen;

			delete [] pwcTmp;
		}

		BASS_CD_Release(iDrive);

		return ERROR_SUCCESS;
	}

	BASS_CD_Release(iDrive);

	return ERROR_READ_FAULT;
}

//////////////////////////////////////////////////////////////////////////
// получение CDDB identifier
//
AOPDLLEXPORT __int32 AOPAudioCDGetCDDB(__int32 iDrive, PWCHAR pwcCDDB)
{
	const char* pcCDDB = NULL;

	pcCDDB = BASS_CD_GetID(iDrive, BASS_CDID_CDDB);

	if (pcCDDB)
	{
		wsprintf(pwcCDDB, L"%S", pcCDDB);

		BASS_CD_Release(iDrive);

		return ERROR_SUCCESS;
	}

	BASS_CD_Release(iDrive);

	return ERROR_READ_FAULT;
}

//////////////////////////////////////////////////////////////////////////
// установка позиции проигрывания
//
AOPDLLEXPORT __int32 AOPPlayPosition(float fPos)
{
	if (hPlayStream)
	{
		BASS_ChannelSetPosition(hPlayStream, BASS_ChannelSeconds2Bytes(hPlayStream, fPos), 
			BASS_POS_BYTE);

		return ERROR_SUCCESS;
	}

	return ERROR_ACCESS_DENIED;
}

//////////////////////////////////////////////////////////////////////////
// текущая позиция
//
AOPDLLEXPORT float AOPGetPos()
{
	if (hPlayStream)
	{
		return (float)BASS_ChannelBytes2Seconds(hPlayStream, 
			BASS_ChannelGetPosition(hPlayStream, BASS_POS_BYTE));
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// длина трека
//
AOPDLLEXPORT float AOPGetLen(PWCHAR pwcFileName)
{
	if (NULL == pwcFileName)
	{
		if (hPlayStream)
		{
			return (float)BASS_ChannelBytes2Seconds(hPlayStream, 
				BASS_ChannelGetLength(hPlayStream, BASS_POS_BYTE));
		}

		return 0;
	}

	HSTREAM hStream;
	FLOAT   fLen;

	hStream = BASS_StreamCreateFile(FALSE, pwcFileName, 0, 0, BASS_DATA_AVAILABLE | BASS_UNICODE);

	if (0 == hStream)
	{
		return 0;
	}

	fLen = (float)BASS_ChannelBytes2Seconds(hStream, 
		BASS_ChannelGetLength(hStream, BASS_POS_BYTE));

	BASS_StreamFree(hStream);

	return fLen;
}

//////////////////////////////////////////////////////////////////////////
// остановка проигрывания
//
AOPDLLEXPORT __int32 AOPStop()
{
	if (hPlayStream)
	{
		BASS_ChannelStop(hPlayStream);
		BASS_StreamFree(hPlayStream);

		hPlayStream = NULL;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// декодирование
//
AOPDLLEXPORT __int32 AOPDecode(PWCHAR pwcInFile, PWCHAR pwcOutFile, PDECODECALLBACK pCallBack)
{
	DecodeCallBack = pCallBack;
	pwcDecodeOut   = pwcOutFile;

	// создание потока
	if (hDecodeStream)
	{
		BASS_StreamFree(hDecodeStream);
	}

	hDecodeStream = BASS_StreamCreateFile(FALSE, pwcInFile, 0, 0, 
		BASS_STREAM_DECODE | BASS_DATA_AVAILABLE | BASS_UNICODE);

	if (0 == hDecodeStream)
	{
		return ERROR_INVALID_HANDLE;
	}

	// создание треда
	if (NULL != hDecodeThread)
	{
		CloseHandle(hDecodeThread);
	}

	hDecodeThread = CreateThread(NULL, 0, DecodeThread, NULL, 0, &dwDecodeThreadID);

	if (NULL == hDecodeThread)
	{
		return ERROR_INVALID_HANDLE;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// тред декодирует файл
//
DWORD WINAPI DecodeThread(LPVOID lpParam)
{
	FILE* fpDecode;

	// открывает файл
	if (_wfopen_s(&fpDecode, pwcDecodeOut, L"wb"))
	{
		if (NULL != DecodeCallBack)
		{
			DecodeCallBack(DECODE_ERROR, 0, 0);
		}

		return ERROR_INVALID_HANDLE;
	}

	// формируем заголовок WAV
	BASS_CHANNELINFO channelInfo;
	WAVEFORMATEX     waveFormat;

	ZeroMemory(&channelInfo, sizeof(channelInfo));
	ZeroMemory(&waveFormat, sizeof(waveFormat));

	BASS_ChannelGetInfo(hDecodeStream, &channelInfo);

	waveFormat.wFormatTag      = 1;
	waveFormat.nChannels       = (WORD)channelInfo.chans;
	waveFormat.wBitsPerSample  = (channelInfo.flags & BASS_SAMPLE_8BITS ? 8 : 16);
	waveFormat.nBlockAlign     = waveFormat.nChannels * waveFormat.wBitsPerSample / 8;
	waveFormat.nSamplesPerSec  = channelInfo.freq;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

	fwrite("RIFF\0\0\0\0WAVEfmt \20\0\0\0", 20, 1, fpDecode);
	fwrite(&waveFormat, 16, 1, fpDecode);
	fwrite("data\0\0\0\0", 8, 1, fpDecode);

	// пишем данные
	INT   iCount;
	QWORD qwPos;
	DWORD dwLength; 
	CHAR  *cBuf;

	dwLength = (DWORD)BASS_ChannelGetLength(hDecodeStream, BASS_POS_BYTE);
	qwPos    = 0;
	cBuf     = new CHAR[65536 * 8];

	while (BASS_ChannelIsActive(hDecodeStream) && ((DWORD)qwPos < dwLength))
	{
		iCount = BASS_ChannelGetData(hDecodeStream, cBuf, 65536 * 8);

		if (((DWORD)qwPos + iCount) < dwLength)
		{
			fwrite(cBuf, 1, iCount, fpDecode);
		}
		else
		{
			fwrite(cBuf, 1, dwLength - (DWORD)qwPos, fpDecode);
		}

		qwPos = BASS_ChannelGetPosition(hDecodeStream, BASS_POS_BYTE);

		if (NULL != DecodeCallBack)
		{
			DecodeCallBack(DECODE_POS, (DWORD)qwPos, dwLength);
		}
	}

	delete [] cBuf;

	fflush(fpDecode);

	// запись информации начала и конца трека 
	DWORD dwPos;

	dwPos = ftell(fpDecode);
	fseek(fpDecode, 4, SEEK_SET);
	_putw(dwPos - 8, fpDecode);
	fflush(fpDecode);

	fseek(fpDecode, 40, SEEK_SET);
	_putw(dwPos - 44, fpDecode);
	fflush(fpDecode);

	fclose(fpDecode);

	// остановка
	if (NULL != DecodeCallBack)
	{
		DecodeCallBack(DECODE_STOP, 0, 0);
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// получение списка устройств
//
AOPDLLEXPORT __int32 AOPGetDevices(PFINDCALLBACK pCallBack)
{
	UserFindCallback = pCallBack;

	StarBurn_FindDevice(SCSI_DEVICE_RO_DIRECT_ACCESS, FALSE, (PCALLBACK)(FindCallback), NULL);

	return ERROR_SUCCESS;
}

//
VOID __stdcall FindCallback(IN CALLBACK_NUMBER cbNumber, IN PVOID pvContext, 
	IN PVOID pvSpecial1, IN PVOID pvSpecial2)
{
	EXCEPTION_NUMBER        expNum = EN_SUCCESS;  //
	PSCSI_DEVICE_ADDRESS    pDevice;              // инфа о девайсе
	PVOID                   pvGrabber = NULL;     // 
	ULONG                   ulStatus;             //
	CDB_FAILURE_INFORMATION cdbInf;               //
	CHAR                    cVendorID[1024];      // производитель
	CHAR                    cProductID[1024];     // продукт 
	CHAR                    cProductRL[1024];     // номер
	ULONG                   ulSizeBuf;            // размер кэша
	CHAR                    cDeviceName[1024];    // буква устройства

	switch (cbNumber)
	{
		// найдено устройство
		case CN_FIND_DEVICE:
			pDevice = (PSCSI_DEVICE_ADDRESS)pvSpecial1;

			__try	
			{
				// открытие девайса
				expNum = StarBurn_CdvdBurnerGrabber_Create(&pvGrabber, 
					NULL, 0, &ulStatus, &cdbInf, NULL, NULL, 
					pDevice->m__UCHAR__PortID, 
					pDevice->m__UCHAR__BusID,
					pDevice->m__UCHAR__TargetID,
					pDevice->m__UCHAR__LUN, 1);

				if (EN_SUCCESS != expNum)
				{
					__leave;
				}

				// получение информации о девайсе
				RtlZeroMemory(&cVendorID,  sizeof(cVendorID));
				RtlZeroMemory(&cProductID, sizeof(cProductID));
				RtlZeroMemory(&cProductRL, sizeof(cProductRL));

				StarBurn_CdvdBurnerGrabber_GetDeviceInformation(pvGrabber, 
					(PCHAR)&cVendorID, (PCHAR)&cProductID, (PCHAR)&cProductRL, &ulSizeBuf);

				while (strlen(cVendorID) && (' ' == cVendorID[strlen(cVendorID) - 1]))
				{
					cVendorID[strlen(cVendorID) - 1] = 0;
				}

				while (strlen(cProductID) && (' ' == cProductID[strlen(cProductID) - 1]))
				{
					cProductID[strlen(cProductID) - 1] = 0;
				}

				while (strlen(cProductRL) && (' ' == cProductRL[strlen(cProductRL) - 1]))
				{
					cProductRL[strlen(cProductRL) - 1] = 0;
				}

				RtlZeroMemory(&cDeviceName, sizeof(cDeviceName));

				// получение буквы устройства
				expNum = StarBurn_GetDeviceNameByDeviceAddress(
					pDevice->m__UCHAR__PortID, pDevice->m__UCHAR__BusID, pDevice->m__UCHAR__TargetID, 
					pDevice->m__UCHAR__LUN, (PCHAR)&cDeviceName);

				if (EN_SUCCESS != expNum)
				{
					__leave;
				}

				DEVICEINFO devNew;

				devNew.ucBusID    = pDevice->m__UCHAR__BusID;
				devNew.ucLUN      = pDevice->m__UCHAR__LUN;
				devNew.ucPortID   = pDevice->m__UCHAR__PortID;
				devNew.ucTargetID = pDevice->m__UCHAR__TargetID;

				_swprintf(devNew.pwName, L"%S %S", cVendorID, cProductID);
				_swprintf(devNew.pwLetter, L"%S", &cDeviceName[4]);

				if (NULL != UserFindCallback)
				{
					UserFindCallback(devNew);
				}
			}
			__finally
			{
				if (NULL != pvGrabber)
				{
					StarBurn_Destroy(&pvGrabber);
				}
			}
			break;
	}
}

//////////////////////////////////////////////////////////////////////////
// получение информации о диске
//
AOPDLLEXPORT __int32 AOPGetDiscInfo(PDEVICEINFO pDeviceInfo, PDISCINFO pDiscInfo, 
	PTOCINFOCALLBACK pCallBack)
{
	EXCEPTION_NUMBER           expNum = EN_SUCCESS;  //
	PVOID                      pvGrabber = NULL;     // 
	ULONG                      ulStatus;             //
	CDB_FAILURE_INFORMATION    cdbInf;               //
	TOC_INFORMATION            tocEntry;             //
	BOOLEAN                    bTOCRead;
	STARBURN_TRACK_INFORMATION sbTrackInfo;

	pDiscInfo->iFreeSpace   = 0;
	pDiscInfo->iUsedSpace   = 0;
	pDiscInfo->bIsWritable  = FALSE;
	pDiscInfo->bIsDiscBlank = TRUE;

	__try	
	{
		// открытие девайса
		expNum = StarBurn_CdvdBurnerGrabber_Create(&pvGrabber, 
			NULL, 0, &ulStatus, &cdbInf, NULL, NULL, 
			pDeviceInfo->ucPortID, 
			pDeviceInfo->ucBusID,
			pDeviceInfo->ucTargetID,
			pDeviceInfo->ucLUN, 1);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}

		DISC_TYPE discType = StarBurn_CdvdBurnerGrabber_GetInsertedDiscType(pvGrabber);
		switch (discType)
		{
			case DISC_TYPE_UNKNOWN:
				_swprintf(pDiscInfo->pwcDiscType, L"Unknown");
				break;

			case DISC_TYPE_CDROM:
			case DISC_TYPE_DDCDROM:
				_swprintf(pDiscInfo->pwcDiscType, L"CD-ROM");
				break;

			case DISC_TYPE_DDCDR:
			case DISC_TYPE_CDR:
				_swprintf(pDiscInfo->pwcDiscType, L"CD-R");
				break;

			case DISC_TYPE_CDRW:
			case DISC_TYPE_DDCDRW:
				_swprintf(pDiscInfo->pwcDiscType, L"CD-RW");
				break;

			case DISC_TYPE_DVDROM:
				_swprintf(pDiscInfo->pwcDiscType, L"DVD-ROM");
				break;

			case DISC_TYPE_DVDR:
				_swprintf(pDiscInfo->pwcDiscType, L"DVD-R");
				break;

			case DISC_TYPE_DVDRAM:
				_swprintf(pDiscInfo->pwcDiscType, L"DVD-RAM");
				break;

			case DISC_TYPE_DVDRWRO:
			case DISC_TYPE_DVDRWSR:
				_swprintf(pDiscInfo->pwcDiscType, L"DVD-RW");
				break;

			case DISC_TYPE_DVDPLUSRW:
				_swprintf(pDiscInfo->pwcDiscType, L"DVD+RW");
				break;

			case DISC_TYPE_DVDPLUSR:
				_swprintf(pDiscInfo->pwcDiscType, L"DVD+R");
				break;

			default:
				_swprintf(pDiscInfo->pwcDiscType, L"Empty");
				__leave;
				break;
		}

		pDiscInfo->iDiscType = discType;

		// 
		StarBurn_SetFastReadTOC(FALSE); 

		// информация о дорожках
		expNum = StarBurn_CdvdBurnerGrabber_GetTOCInformation(pvGrabber, 
			NULL, 0, &ulStatus, &cdbInf, &tocEntry);

		if (EN_SUCCESS == expNum)
		{	
			bTOCRead = TRUE;
		}
		else
		{
			bTOCRead = FALSE;
		}

		expNum = StarBurn_CdvdBurnerGrabber_GetTrackInformation(pvGrabber, NULL, 0, &ulStatus, 
			&cdbInf, TRACK_NUMBER_INVISIBLE, &sbTrackInfo);

		if (EN_SUCCESS == expNum)
		{
			pDiscInfo->iFreeSpace   = (__int64)sbTrackInfo.m__LONG__FreeLBs * MODE1_LB_SIZE_IN_UCHARS; 
			pDiscInfo->iUsedSpace   = (__int64)sbTrackInfo.m__LONG__NextWritableAddress * MODE1_LB_SIZE_IN_UCHARS; 
			pDiscInfo->bIsDiscBlank = (sbTrackInfo.m__LONG__NextWritableAddress == 0);
			pDiscInfo->bIsWritable  = sbTrackInfo.m__BOOLEAN__IsNextWritableAddressValid;
		}
		else
		{
			pDiscInfo->bIsDiscBlank = FALSE;
			pDiscInfo->bIsWritable  = FALSE;
		}

		if (bTOCRead)
		{
			expNum = EN_SUCCESS;

			if (FALSE == pDiscInfo->bIsWritable)
			{
				pDiscInfo->iFreeSpace = 0;
				pDiscInfo->iUsedSpace = 0;
			}

			for (INT i = 0; i < tocEntry.m__UCHAR__NumberOfTracks; i++)
			{
				if (FALSE == pDiscInfo->bIsWritable)
				{
					__int64 liTrackSpace;

					liTrackSpace  = tocEntry.m__TOC_ENTRY[i].m__LONG__EndingLBA - tocEntry.m__TOC_ENTRY[i].m__LONG__StartingLBA;
					liTrackSpace *= tocEntry.m__TOC_ENTRY[i].m__ULONG__LBSizeInUCHARs;

					pDiscInfo->iUsedSpace += liTrackSpace;
				}

				if (NULL != pCallBack)
				{
					TOCINFO tocInfo;

					tocInfo.uiTrackMode      = tocEntry.m__TOC_ENTRY[i].m__UCHAR__TrackMode;
					tocInfo.uiSessionNumber  = tocEntry.m__TOC_ENTRY[i].m__UCHAR__SessionNumber;
					tocInfo.uiTrackNumber    = tocEntry.m__TOC_ENTRY[i].m__UCHAR__TrackNumber;
					tocInfo.iStartingLBA     = tocEntry.m__TOC_ENTRY[i].m__LONG__StartingLBA;
					tocInfo.iEndingLBA       = tocEntry.m__TOC_ENTRY[i].m__LONG__EndingLBA;
					tocInfo.uiLBSizeInUCHARs = tocEntry.m__TOC_ENTRY[i].m__ULONG__LBSizeInUCHARs;

					pCallBack(tocInfo);
				}
			}
		}
	}
	__finally
	{
		if (NULL != pvGrabber)
		{
			StarBurn_Destroy(&pvGrabber);
		}
	}

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// load tray
//
AOPDLLEXPORT __int32 AOPLoadTray(PDEVICEINFO pDeviceInfo)
{
	EXCEPTION_NUMBER           expNum = EN_SUCCESS;  //
	PVOID                      pvGrabber = NULL;     // 
	ULONG                      ulStatus;             //
	CDB_FAILURE_INFORMATION    cdbInf;               //

	__try	
	{
		// открытие девайса
		expNum = StarBurn_CdvdBurnerGrabber_Create(&pvGrabber, 
			NULL, 0, &ulStatus, &cdbInf, NULL, NULL, 
			pDeviceInfo->ucPortID, 
			pDeviceInfo->ucBusID,
			pDeviceInfo->ucTargetID,
			pDeviceInfo->ucLUN, 1);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}

		// load
		expNum = StarBurn_CdvdBurnerGrabber_Load(pvGrabber, NULL, 0, &ulStatus, &cdbInf);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}
	}
	__finally
	{
		if (NULL != pvGrabber)
		{
			StarBurn_Destroy(&pvGrabber);
		}
	}

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// eject диска
//
AOPDLLEXPORT __int32 AOPEjectTray(PDEVICEINFO pDeviceInfo)
{
	EXCEPTION_NUMBER           expNum = EN_SUCCESS;  //
	PVOID                      pvGrabber = NULL;     // 
	ULONG                      ulStatus;             //
	CDB_FAILURE_INFORMATION    cdbInf;               //

	__try	
	{
		// открытие девайса
		expNum = StarBurn_CdvdBurnerGrabber_Create(&pvGrabber, 
			NULL, 0, &ulStatus, &cdbInf, NULL, NULL, 
			pDeviceInfo->ucPortID, 
			pDeviceInfo->ucBusID,
			pDeviceInfo->ucTargetID,
			pDeviceInfo->ucLUN, 1);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}

		// eject
		expNum = StarBurn_CdvdBurnerGrabber_Eject(pvGrabber, NULL, 0, &ulStatus, &cdbInf);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}
	}
	__finally
	{
		if (NULL != pvGrabber)
		{
			StarBurn_Destroy(&pvGrabber);
		}
	}

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	return ERROR_SUCCESS;
}

// получение скоростей записи диска
AOPDLLEXPORT __int32 AOPGetWriteSpeeds(PDEVICEINFO pDeviceInfo, PWCHAR pwcSpeeds)
{
	if (NULL == pwcSpeeds)
	{
		return ERROR_ACCESS_DENIED;
	}

	((CHAR*)pwcSpeeds)[0] = 0;
	((CHAR*)pwcSpeeds)[1] = 0;

	EXCEPTION_NUMBER           expNum = EN_SUCCESS;  //
	PVOID                      pvGrabber = NULL;     // 
	ULONG                      ulStatus;             //
	CDB_FAILURE_INFORMATION    cdbInf;               //

	__try	
	{
		// открытие девайса
		expNum = StarBurn_CdvdBurnerGrabber_Create(&pvGrabber, 
			NULL, 0, &ulStatus, &cdbInf, NULL, NULL, 
			pDeviceInfo->ucPortID, 
			pDeviceInfo->ucBusID,
			pDeviceInfo->ucTargetID,
			pDeviceInfo->ucLUN, 1);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}

		// считывание максимальных скоростей
		ULONG ulCurrentReadSpeed;
		ULONG ulMaximumReadSpeed;
		ULONG ulCurrentWriteSpeed;
		ULONG ulMaximumWriteSpeed;

		expNum = StarBurn_CdvdBurnerGrabber_GetSpeeds(pvGrabber, NULL, 0, &ulStatus, 
			&cdbInf, &ulCurrentReadSpeed, &ulMaximumReadSpeed, &ulCurrentWriteSpeed, &ulMaximumWriteSpeed);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}

		for(int i = 0; g_CDStandardSpeeds[i].ulSpeedInKBps <= ulMaximumWriteSpeed && CD_STANDARD_SPEED_COUNT > i; i++)
		{
			WCHAR pwcTmp[10];

			wsprintf(pwcTmp, L"%S\0", g_CDStandardSpeeds[i].pSpeedX);
			wcscat(pwcSpeeds, pwcTmp);
			wcscat(pwcSpeeds, L";");
		}
	}

	__finally
	{
		if (NULL != pvGrabber)
		{
			StarBurn_Destroy(&pvGrabber);
		}
	}

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	return ERROR_SUCCESS;
}


// получение скоростей записи диска
AOPDLLEXPORT __int32 AOPGetReadSpeeds(PDEVICEINFO pDeviceInfo, PWCHAR pwcSpeeds)
{
	if (NULL == pwcSpeeds)
	{
		return ERROR_ACCESS_DENIED;
	}

	((CHAR*)pwcSpeeds)[0] = 0;
	((CHAR*)pwcSpeeds)[1] = 0;

	EXCEPTION_NUMBER           expNum = EN_SUCCESS;  //
	PVOID                      pvGrabber = NULL;     // 
	ULONG                      ulStatus;             //
	CDB_FAILURE_INFORMATION    cdbInf;               //

	__try	
	{
		// открытие девайса
		expNum = StarBurn_CdvdBurnerGrabber_Create(&pvGrabber, 
			NULL, 0, &ulStatus, &cdbInf, NULL, NULL, 
			pDeviceInfo->ucPortID, 
			pDeviceInfo->ucBusID,
			pDeviceInfo->ucTargetID,
			pDeviceInfo->ucLUN, 1);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}

		// считывание максимальных скоростей
		ULONG ulCurrentReadSpeed;
		ULONG ulMaximumReadSpeed;
		ULONG ulCurrentWriteSpeed;
		ULONG ulMaximumWriteSpeed;

		expNum = StarBurn_CdvdBurnerGrabber_GetSpeeds(pvGrabber, NULL, 0, &ulStatus, 
			&cdbInf, &ulCurrentReadSpeed, &ulMaximumReadSpeed, &ulCurrentWriteSpeed, &ulMaximumWriteSpeed);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}

		for(int i = 0; g_CDStandardSpeeds[i].ulSpeedInKBps <= ulMaximumReadSpeed && CD_STANDARD_SPEED_COUNT > i; i++)
		{
			WCHAR pwcTmp[10];

			wsprintf(pwcTmp, L"%S\0", g_CDStandardSpeeds[i].pSpeedX);
			wcscat(pwcSpeeds, pwcTmp);
			wcscat(pwcSpeeds, L";");
		}
	}
	__finally
	{
		if (NULL != pvGrabber)
		{
			StarBurn_Destroy(&pvGrabber);
		}
	}

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// получение значения громкости
//
AOPDLLEXPORT unsigned __int32 AOPGetVolume()
{
	return (unsigned __int32)(BASS_GetVolume() * 100.0);
}

//////////////////////////////////////////////////////////////////////////
// установка значения громкости
//
AOPDLLEXPORT __int32 AOPSetVolume(unsigned __int32 uiVolume)
{
	if (BASS_SetVolume(uiVolume / 100.f))
	{
		return ERROR_SUCCESS;
	}

	return ERROR_ACCESS_DENIED;
}

//////////////////////////////////////////////////////////////////////////
// очистка диска
//
AOPDLLEXPORT __int32 AOPBlank(PDEVICEINFO pDeviceInfo, __int8 bFull)
{
	EXCEPTION_NUMBER           expNum = EN_SUCCESS;  //
	PVOID                      pvGrabber = NULL;     // 
	ULONG                      ulStatus;             //
	CDB_FAILURE_INFORMATION    cdbInf;               //

	__try	
	{
		// открытие девайса
		expNum = StarBurn_CdvdBurnerGrabber_Create(&pvGrabber, 
			NULL, 0, &ulStatus, &cdbInf, NULL, NULL, 
			pDeviceInfo->ucPortID, 
			pDeviceInfo->ucBusID,
			pDeviceInfo->ucTargetID,
			pDeviceInfo->ucLUN, 1);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}

		if (bFull > 0)
		{
			expNum = StarBurn_CdvdBurnerGrabber_Blank(pvGrabber, NULL, 0, &ulStatus, 
				&cdbInf, ERASE_TYPE_BLANK_DISC_FULL);
		}
		else
		{
			expNum = StarBurn_CdvdBurnerGrabber_Blank(pvGrabber, NULL, 0, &ulStatus, 
				&cdbInf, ERASE_TYPE_BLANK_DISC_FAST);
		}
	}
	__finally
	{
		if (NULL != pvGrabber)
		{
			StarBurn_Destroy(&pvGrabber);
		}
	}

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// получение примерного времение очистки диска
//
AOPDLLEXPORT float AOPGetBlankTime(PDEVICEINFO pDeviceInfo, __int8 bFull)
{
	EXCEPTION_NUMBER           expNum = EN_SUCCESS;  //
	PVOID                      pvGrabber = NULL;     // 
	ULONG                      ulStatus;             //
	CDB_FAILURE_INFORMATION    cdbInf;               //
	FLOAT                      fBlankTime;

	fBlankTime = 0.;

	__try	
	{
		DISCINFO discInfo;

		if (ERROR_SUCCESS != AOPGetDiscInfo(pDeviceInfo, &discInfo, NULL))
		{
			__leave;
		}

		switch (discInfo.iDiscType)
		{
			case DISC_TYPE_CDRW:
				if (bFull > 0)
				{
					//fBlankTime = (FLOAT)((discInfo.iFreeSpace + discInfo.iUsedSpace) / 1024 + CD_TOC_SIZE_IN_MB * 1024);
					fBlankTime = (FLOAT)((800000000) / 1024 + CD_TOC_SIZE_IN_MB * 1024);
				}
				else
				{
					fBlankTime = CD_TOC_SIZE_IN_MB * 1024;
				}
				break;

			case DISC_TYPE_DDCDRW:
			case DISC_TYPE_DVDRWRO:
			case DISC_TYPE_DVDRWSR:
			case DISC_TYPE_DVDRAM:
			case DISC_TYPE_DVDPLUSRW:
				if (bFull > 0)
				{
					//fBlankTime = (FLOAT)((discInfo.iFreeSpace + discInfo.iUsedSpace) / 1024 + DVD_TOC_SIZE_IN_MB * 1024);
					fBlankTime = (FLOAT)((5000000000) / 1024 + DVD_TOC_SIZE_IN_MB * 1024);
				}
				else
				{
					fBlankTime = DVD_TOC_SIZE_IN_MB * 1024;
				}
				break;
		}

		// открытие девайса
		expNum = StarBurn_CdvdBurnerGrabber_Create(&pvGrabber, 
			NULL, 0, &ulStatus, &cdbInf, NULL, NULL, 
			pDeviceInfo->ucPortID, 
			pDeviceInfo->ucBusID,
			pDeviceInfo->ucTargetID,
			pDeviceInfo->ucLUN, 1);

		// установка максимальной скорости записи
		expNum = StarBurn_CdvdBurnerGrabber_SetSpeeds(pvGrabber, NULL, 0, &ulStatus, 
			&cdbInf, CDVD_SPEED_IS_KBPS_MAXIMUM, CDVD_SPEED_IS_KBPS_MAXIMUM);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}

		// получение установленной скорости записи
		ULONG ulCurrentReadSpeed;
		ULONG ulMaximumReadSpeed;
		ULONG ulCurrentWriteSpeed;
		ULONG ulMaximumWriteSpeed;

		expNum = StarBurn_CdvdBurnerGrabber_GetSpeeds(pvGrabber, NULL, 0, &ulStatus, 
			&cdbInf, &ulCurrentReadSpeed, &ulMaximumReadSpeed, &ulCurrentWriteSpeed, &ulMaximumWriteSpeed);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}

		fBlankTime /= ulCurrentWriteSpeed;
	}
	__finally
	{
		if (NULL != pvGrabber)
		{
			StarBurn_Destroy(&pvGrabber);
		}
	}

	return fBlankTime;
}

//////////////////////////////////////////////////////////////////////////
// получение тегов трека
//
AOPDLLEXPORT __int32 AOPGetTags(PWCHAR pwcFileName, PWCHAR pwcArtist, PWCHAR pwcAlbum, PWCHAR pwcTitle)
{
	HSTREAM hStream;

	((CHAR*)pwcAlbum)[0] = ((CHAR*)pwcAlbum)[1] = ((CHAR*)pwcArtist)[0] = ((CHAR*)pwcArtist)[1] = 
		((CHAR*)pwcAlbum)[0] = ((CHAR*)pwcAlbum)[1] = 0;

	hStream = BASS_StreamCreateFile(FALSE, pwcFileName, 0, 0, BASS_SAMPLE_FLOAT | BASS_UNICODE);

	if (0 == hStream)
	{
		return ERROR_ACCESS_DENIED;
	}

	_swprintf(pwcArtist, L"%S", TAGS_Read(hStream, "%ARTI"));
	_swprintf(pwcAlbum, L"%S",  TAGS_Read(hStream, "%ALBM"));
	_swprintf(pwcTitle, L"%S",  TAGS_Read(hStream, "%TITL"));

	BASS_StreamFree(hStream);

	return ERROR_SUCCESS;
}

//
// ФУНКЦИИ РАБОТЫ С AUDIO CD 
//

PAUDIOBURNCALLBACK pAudioBurnUserCallback = NULL;
PAUDIORIPCALLBACK  pAudioRipUserCallback  = NULL;
PVOID              pvAudioCDGrabber       = NULL;
PVOID              pvAudioCDContext       = NULL;
_DAO_DISC_LAYOUT   sDAODiscLayout;

VOID __stdcall AudioCallback(CALLBACK_NUMBER p__CallbackNumber, PVOID p_CallbackContext, 
	PVOID p_CallbackSpecial1, PVOID p_CallbackSpecial2);

//////////////////////////////////////////////////////////////////////////
// создание Audio CD
//
AOPDLLEXPORT __int32 AOPAudioCDInit(PDEVICEINFO pDeviceInfo)
{
	EXCEPTION_NUMBER        expNum = EN_SUCCESS;
	ULONG                   ulStatus;
	CDB_FAILURE_INFORMATION cdbInf;

	ZeroMemory(&sDAODiscLayout, sizeof(sDAODiscLayout));

	// открытие девайса
	expNum = StarBurn_CdvdBurnerGrabber_Create(&pvAudioCDGrabber, 
		NULL, 0, &ulStatus, &cdbInf, (PCALLBACK)(AudioCallback), &pvAudioCDContext, 
		pDeviceInfo->ucPortID, 
		pDeviceInfo->ucBusID,
		pDeviceInfo->ucTargetID,
		pDeviceInfo->ucLUN, 1);

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// освобождение ресурсов занятых при создании Audio CD
//
AOPDLLEXPORT __int32 AOPAudioCDFree()
{
	if (NULL != pvAudioCDGrabber)
	{
		StarBurn_Destroy(&pvAudioCDGrabber);

		pvAudioCDGrabber       = NULL;
		pAudioBurnUserCallback = NULL;
		pAudioRipUserCallback  = NULL;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// добавление трека
//
AOPDLLEXPORT __int32 AOPAudioCDAddTrack(PWCHAR pwcPath)
{
	sprintf(sDAODiscLayout.m__DAO_DISC_LAYOUT_ENTRY[sDAODiscLayout.m__LONG__NumberOfEntries].m__CHAR__TrackName, "%S", pwcPath);

	sDAODiscLayout.m__LONG__NumberOfEntries++;

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// установка тегов аудио трека
//
AOPDLLEXPORT __int32 AOPAudioCDSetTitle(UCHAR ucTrack, PWCHAR pwcArtist, PWCHAR pwcTitle)
{
	EXCEPTION_NUMBER expNum = EN_SUCCESS;
	ULONG            ulStatus;
	CHAR             cArtist[200];
	CHAR             cTitle[200];

	ZeroMemory(cArtist, sizeof(cArtist));
	ZeroMemory(cTitle, sizeof(cTitle));

	sprintf(cArtist, "%S", pwcArtist);
	sprintf(cTitle, "%S", pwcTitle);

	expNum = StarBurn_CdvdBurnerGrabber_SetCDTextItem(pvAudioCDGrabber, ucTrack, 
		cArtist, cTitle, NULL, 0, &ulStatus);

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// прожиг Audio CD
//
AOPDLLEXPORT __int32 AOPAudioCDBurn(PAUDIOBURNCALLBACK pCallback, __int32 iSpeed)
{
	EXCEPTION_NUMBER        expNum = EN_SUCCESS;
	ULONG                   ulStatus;
	CDB_FAILURE_INFORMATION cdbInf;

	if (NULL == pvAudioCDGrabber)
	{
		return ERROR_ACCESS_DENIED;
	}

	pAudioBurnUserCallback = pCallback;

	// Try to test unit ready
	expNum =	StarBurn_CdvdBurnerGrabber_TestUnitReady(pvAudioCDGrabber, NULL, 0, &ulStatus, &cdbInf);

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	// Try to set BUP status
	expNum =	StarBurn_CdvdBurnerGrabber_SetBUP(pvAudioCDGrabber, NULL, 0, &ulStatus, &cdbInf, TRUE);

	// Try to set current write speed
	expNum =	StarBurn_CdvdBurnerGrabber_SetSpeeds(pvAudioCDGrabber, NULL, 0, &ulStatus, &cdbInf, 
		g_CDStandardSpeeds[iSpeed].ulSpeedInKBps, g_CDStandardSpeeds[iSpeed].ulSpeedInKBps);

	// Try to send OPC
	expNum =	StarBurn_CdvdBurnerGrabber_SendOPC(pvAudioCDGrabber, NULL, 0, &ulStatus, &cdbInf);

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	// Burn
	expNum = StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromFile(pvAudioCDGrabber, NULL, 0, &ulStatus, 
		&cdbInf, &sDAODiscLayout, FALSE, FALSE /*TRUE*/, FALSE, FALSE, 1, 1);

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// Callback функция прожига Audio CD
//
VOID __stdcall AudioCallback(CALLBACK_NUMBER p__CallbackNumber, PVOID p_CallbackContext, 
	PVOID p_CallbackSpecial1, PVOID p_CallbackSpecial2)
{
	LARGE_INTEGER l_FileSizeInLBs;
	LARGE_INTEGER l_LBsWritten;
	LARGE_INTEGER l_CurrentPercent;
	ULONG         l_BufferSizeInUCHARs;
	ULONG         l_BufferFreeSizeInUCHARs;
	ULONG         l_BufferPercent;
	LARGE_INTEGER l_TrackSizeInLBs;
	LARGE_INTEGER l_LBsReaden;

	switch ( p__CallbackNumber )
	{
		// If this is file analyze begin
		case CN_TARGET_FILE_ANALYZE_BEGIN:
			//wprintf(L"CN_TARGET_FILE_ANALYZE_BEGIN\n");
			break;

		// If this is file analyze end
		case CN_TARGET_FILE_ANALYZE_END:
			//wprintf(L"CN_TARGET_FILE_ANALYZE_END\n");
			break;

		// If this is cache full begin
		case CN_WAIT_CACHE_FULL_BEGIN:
			//wprintf(L"CN_WAIT_CACHE_FULL_BEGIN\n");
			break;

		// If this is cache full end
		case CN_WAIT_CACHE_FULL_END:
			//wprintf(L"CN_WAIT_CACHE_FULL_END\n");
			break;

		// If this is synchronize cache begin
		case CN_SYNCHRONIZE_CACHE_BEGIN:
			//wprintf(L"CN_SYNCHRONIZE_CACHE_BEGIN\n");
			break;

		// If this is synchronize cache end
		case CN_SYNCHRONIZE_CACHE_END:
			//wprintf(L"CN_SYNCHRONIZE_CACHE_END\n");
			break;

		// If this is packet write
		case CN_CDVD_WRITE_PROGRESS:
			// Get parameters passed with callback
			l_FileSizeInLBs = *(PLARGE_INTEGER)(p_CallbackSpecial1);
			l_LBsWritten    = *(PLARGE_INTEGER)(p_CallbackSpecial2);

			// Calculate number of percent written
			l_CurrentPercent.QuadPart = ((l_LBsWritten.QuadPart * 100) / l_FileSizeInLBs.QuadPart);

			// Update last written percent with current value
			if (NULL != pAudioBurnUserCallback)
			{
				pAudioBurnUserCallback(AUDIOBURN_WRITE, (__int32)l_CurrentPercent.QuadPart, 0);
			}
			break;

		case CN_CDVD_BUFFER_STATUS:
			// Get parameters passed with callback
			l_BufferSizeInUCHARs     = *(PULONG)(p_CallbackSpecial1);
			l_BufferFreeSizeInUCHARs = *(PULONG)(p_CallbackSpecial2);

			// Calculate buffer full ratio
			if (0 != l_BufferSizeInUCHARs)
			{
				l_BufferPercent = ((l_BufferFreeSizeInUCHARs * 100 ) / l_BufferSizeInUCHARs);
				l_BufferPercent = (100 - l_BufferPercent);
			}
			else
			{
				l_BufferPercent = 0; // Unknown if buffer size in UCHARs is zero
			}

			// Update last written percent with current value
			if (NULL != pAudioBurnUserCallback)
			{
				pAudioBurnUserCallback(AUDIOBURN_BUFFER, (__int32)l_BufferPercent, 0);
			}
			break;

		// граббинг AudioCD
		case CN_CDVD_READ_PROGRESS:
			// всего логических блоков
			l_TrackSizeInLBs = *(PLARGE_INTEGER)(p_CallbackSpecial1);

			// количество прочитанных блоков
			l_LBsReaden = *(PLARGE_INTEGER)(p_CallbackSpecial2);

			// процент прочитанного
			l_CurrentPercent.QuadPart = (l_LBsReaden.QuadPart * 100) / l_TrackSizeInLBs.QuadPart;

			// вызов пользовательской Callback функции с передачей процента прочитанного
			if (NULL != pAudioRipUserCallback)
			{
				pAudioRipUserCallback(AUDIORIP_READ, (int)l_CurrentPercent.QuadPart, 0);
			}
			break;
	}
}

//////////////////////////////////////////////////////////////////////////
// перевод секунд в байты
//
AOPDLLEXPORT __int32 AOPSeconds2Bytes(float fSeconds)
{
	if (NULL != hDecodeStream)
	{
		return (__int32)BASS_ChannelSeconds2Bytes(hDecodeStream, fSeconds);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// проверка на наличие чистого CD
//
AOPDLLEXPORT __int32 AOPIsBlankCD(PDEVICEINFO pDeviceInfo)
{
	EXCEPTION_NUMBER           expNum = EN_SUCCESS;  //
	PVOID                      pvGrabber = NULL;     // 
	ULONG                      ulStatus;             //
	CDB_FAILURE_INFORMATION    cdbInf;               //
	STARBURN_TRACK_INFORMATION sbTrackInfo;
	__int32                    iReturn = 0;

	__try	
	{
		// открытие девайса
		expNum = StarBurn_CdvdBurnerGrabber_Create(&pvGrabber, 
			NULL, 0, &ulStatus, &cdbInf, NULL, NULL, 
			pDeviceInfo->ucPortID, 
			pDeviceInfo->ucBusID,
			pDeviceInfo->ucTargetID,
			pDeviceInfo->ucLUN, 1);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}

		expNum = StarBurn_CdvdBurnerGrabber_GetTrackInformation(pvGrabber, NULL, 0, &ulStatus, 
			&cdbInf, TRACK_NUMBER_INVISIBLE, &sbTrackInfo);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}

		DISC_TYPE discType = StarBurn_CdvdBurnerGrabber_GetInsertedDiscType(pvGrabber);

		// проверка на наличие чистого CD
		if ((0 == sbTrackInfo.m__LONG__NextWritableAddress) &&  ((DISC_TYPE_DDCDR == discType) || 
			(DISC_TYPE_CDR == discType) || (DISC_TYPE_CDRW == discType) || (DISC_TYPE_DDCDRW == discType)))
		{
			iReturn = 1;
		}
	}
	__finally
	{
		if (NULL != pvGrabber)
		{
			StarBurn_Destroy(&pvGrabber);
		}
	}

	return iReturn;
}

//////////////////////////////////////////////////////////////////////////
// блокировка устройства
//
AOPDLLEXPORT __int32 AOPLock(PDEVICEINFO pDeviceInfo)
{
	EXCEPTION_NUMBER        expNum = EN_SUCCESS;  //
	PVOID                   pvGrabber = NULL;     // 
	ULONG                   ulStatus;             //
	CDB_FAILURE_INFORMATION cdbInf;               //

	__try	
	{
		// открытие девайса
		expNum = StarBurn_CdvdBurnerGrabber_Create(&pvGrabber, 
			NULL, 0, &ulStatus, &cdbInf, NULL, NULL, 
			pDeviceInfo->ucPortID, 
			pDeviceInfo->ucBusID,
			pDeviceInfo->ucTargetID,
			pDeviceInfo->ucLUN, 1);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}

		expNum = StarBurn_CdvdBurnerGrabber_Lock(pvGrabber, NULL, 0, &ulStatus, &cdbInf);
	}

	__finally
	{
		if (NULL != pvGrabber)
		{
			StarBurn_Destroy(&pvGrabber);
		}
	}

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// разблокировка устройства
AOPDLLEXPORT __int32 AOPUnLock(PDEVICEINFO pDeviceInfo)
{
	EXCEPTION_NUMBER        expNum = EN_SUCCESS;  //
	PVOID                   pvGrabber = NULL;     // 
	ULONG                   ulStatus;             //
	CDB_FAILURE_INFORMATION cdbInf;               //

	__try	
	{
		// открытие девайса
		expNum = StarBurn_CdvdBurnerGrabber_Create(&pvGrabber, 
			NULL, 0, &ulStatus, &cdbInf, NULL, NULL, 
			pDeviceInfo->ucPortID, 
			pDeviceInfo->ucBusID,
			pDeviceInfo->ucTargetID,
			pDeviceInfo->ucLUN, 1);

		if (EN_SUCCESS != expNum)
		{
			__leave;
		}

		expNum = StarBurn_CdvdBurnerGrabber_Release(pvGrabber, NULL, 0, &ulStatus, &cdbInf);
	}
	__finally
	{
		if (NULL != pvGrabber)
		{
			StarBurn_Destroy(&pvGrabber);
		}
	}

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// Rip Audio CD
//
AOPDLLEXPORT __int32 AOPAudioCDRip(__int32 iTrack, PWCHAR pwcPath, 
	PAUDIORIPCALLBACK pCallback, __int32 iSpeed)
{
	EXCEPTION_NUMBER        expNum = EN_SUCCESS;  //
	ULONG                   ulStatus;             //
	CDB_FAILURE_INFORMATION cdbInf;               //
	CHAR                    pcPath[MAX_PATH];     // 

	if (NULL == pvAudioCDGrabber)
	{
		return ERROR_ACCESS_DENIED;
	}

	pAudioRipUserCallback = pCallback;
	pvAudioCDContext      = pwcPath;

	// установка типа чтения TOC
	StarBurn_SetFastReadTOC(FALSE); 

	// установка скорости чтения диска
	expNum =	StarBurn_CdvdBurnerGrabber_SetSpeeds(pvAudioCDGrabber, NULL, 0, &ulStatus, 
		&cdbInf, g_CDStandardSpeeds[iSpeed].ulSpeedInKBps, g_CDStandardSpeeds[iSpeed].ulSpeedInKBps);

	// граббинг трека
	sprintf(pcPath, "%S", pwcPath);

	expNum = StarBurn_CdvdBurnerGrabber_GrabTrack(pvAudioCDGrabber, NULL, 0, &ulStatus, 
		&cdbInf, iTrack, pcPath, 10, TRUE, FALSE, READ_REPORT_DELAY_IN_SECONDS);

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// Отмена операции риппинга
//
AOPDLLEXPORT __int32 AOPAudioCDRipCancel()
{
	if (NULL == pvAudioCDGrabber)
	{
		return ERROR_ACCESS_DENIED;
	}

	StarBurn_CdvdBurnerGrabber_Cancel(pvAudioCDGrabber);

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// кодирование в WAV
//
AOPDLLEXPORT __int32 AOPEncodeWAV(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback)
{
	HSTREAM hStreamWAV;
	FILE*   fpDecode;

	// открывает выходной файл
	if (_wfopen_s(&fpDecode, pwcOutFile, L"wb"))
	{
		return ERROR_INVALID_HANDLE;
	}

	// открывает исходный файл
	hStreamWAV = BASS_StreamCreateFile(FALSE, pwcInFile, 0, 0, 
		BASS_STREAM_DECODE | BASS_DATA_AVAILABLE | BASS_UNICODE);

	if (0 == hStreamWAV)
	{
		return ERROR_INVALID_HANDLE;
	}

	// формируем заголовок WAV
	BASS_CHANNELINFO channelInfo;
	WAVEFORMATEX     waveFormat;

	ZeroMemory(&channelInfo, sizeof(channelInfo));
	ZeroMemory(&waveFormat, sizeof(waveFormat));

	BASS_ChannelGetInfo(hStreamWAV, &channelInfo);

	waveFormat.wFormatTag      = 1;
	waveFormat.nChannels       = (WORD)channelInfo.chans;
	waveFormat.wBitsPerSample  = (channelInfo.flags & BASS_SAMPLE_8BITS ? 8 : 16);
	waveFormat.nBlockAlign     = waveFormat.nChannels * waveFormat.wBitsPerSample / 8;
	waveFormat.nSamplesPerSec  = channelInfo.freq;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

	fwrite("RIFF\0\0\0\0WAVEfmt \20\0\0\0", 20, 1, fpDecode);
	fwrite(&waveFormat, 16, 1, fpDecode);
	fwrite("data\0\0\0\0", 8, 1, fpDecode);

	// пишем данные
	INT   iCount;
	QWORD qwPos;
	DWORD dwLength; 
	CHAR  *cBuf;

	dwLength = (DWORD)BASS_ChannelGetLength(hStreamWAV, BASS_POS_BYTE);
	qwPos    = 0;
	cBuf     = new CHAR[65536 * 8];

	while (BASS_ChannelIsActive(hStreamWAV) && ((DWORD)qwPos < dwLength))
	{
		iCount = BASS_ChannelGetData(hStreamWAV, cBuf, 65536 * 8);

		if (((DWORD)qwPos + iCount) < dwLength)
		{
			fwrite(cBuf, 1, iCount, fpDecode);
		}
		else
		{
			fwrite(cBuf, 1, dwLength - (DWORD)qwPos, fpDecode);
		}

		qwPos = BASS_ChannelGetPosition(hStreamWAV, BASS_POS_BYTE);

		if (NULL != pCallback)
		{
			pCallback(ENCODE_POS, (DWORD)qwPos, dwLength);
		}
	}

	delete [] cBuf;

	fflush(fpDecode);

	// запись информации начала и конца трека 
	DWORD dwPos;

	dwPos = ftell(fpDecode);
	fseek(fpDecode, 4, SEEK_SET);
	_putw(dwPos - 8, fpDecode);
	fflush(fpDecode);

	fseek(fpDecode, 40, SEEK_SET);
	_putw(dwPos - 44, fpDecode);
	fflush(fpDecode);

	fclose(fpDecode);

	BASS_StreamFree(hStreamWAV);

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// кодирование в WMA
//
AOPDLLEXPORT __int32 AOPEncodeWMA(PWCHAR pwcInFile, PWCHAR pwcOutFile, PWCHAR pwcTitle, 
	PWCHAR pwcAuthor, PWCHAR pwcAlbumTitle, PWCHAR pwcGenre, PWCHAR pwcYear, 
	__int32 iBitrate, PENCODECALLBACK pCallback)
{
	HSTREAM   hStreamWAV;
	HWMENCODE hEncoderWMA;

	// открывает исходный файл
	hStreamWAV = BASS_StreamCreateFile(FALSE, pwcInFile, 0, 0, 
		BASS_STREAM_DECODE | BASS_DATA_AVAILABLE | BASS_UNICODE);

	if (0 == hStreamWAV)
	{
		return ERROR_INVALID_HANDLE;
	}

	hEncoderWMA = BASS_WMA_EncodeOpenFile(44100, 2, BASS_UNICODE, iBitrate, (PCHAR)pwcOutFile);

	if (FALSE == hEncoderWMA)
	{
		return ERROR_INVALID_HANDLE;
	}

	BASS_WMA_EncodeSetTag(hEncoderWMA, (PCHAR)L"Title", (PCHAR)pwcTitle, BASS_WMA_TAG_UNICODE);
	BASS_WMA_EncodeSetTag(hEncoderWMA, (PCHAR)L"Description", (PCHAR)L"Audio One Pack", BASS_WMA_TAG_UNICODE);
	BASS_WMA_EncodeSetTag(hEncoderWMA, (PCHAR)L"Author", (PCHAR)pwcAuthor, BASS_WMA_TAG_UNICODE);
	BASS_WMA_EncodeSetTag(hEncoderWMA, (PCHAR)L"WM/AlbumTitle", (PCHAR)pwcAlbumTitle, BASS_WMA_TAG_UNICODE);
	BASS_WMA_EncodeSetTag(hEncoderWMA, (PCHAR)L"WM/Genre", (PCHAR)pwcGenre, BASS_WMA_TAG_UNICODE);
	BASS_WMA_EncodeSetTag(hEncoderWMA, (PCHAR)L"WM/Year", (PCHAR)pwcYear, BASS_WMA_TAG_UNICODE);

	// пишем данные
	INT   iCount;
	QWORD qwPos;
	DWORD dwLength; 
	CHAR  *cBuf;

	dwLength = (DWORD)BASS_ChannelGetLength(hStreamWAV, BASS_POS_BYTE);
	qwPos    = 0;
	cBuf     = new CHAR[65536 * 8];

	while (BASS_ChannelIsActive(hStreamWAV) && ((DWORD)qwPos < dwLength))
	{
		iCount = BASS_ChannelGetData(hStreamWAV, cBuf, 65536 * 8);

		if (((DWORD)qwPos + iCount) < dwLength)
		{
			BASS_WMA_EncodeWrite(hEncoderWMA, cBuf, iCount);
		}
		else
		{
			BASS_WMA_EncodeWrite(hEncoderWMA, cBuf, dwLength - (DWORD)qwPos);
		}

		qwPos = BASS_ChannelGetPosition(hStreamWAV, BASS_POS_BYTE);

		if (NULL != pCallback)
		{
			pCallback(ENCODE_POS, (DWORD)qwPos, dwLength);
		}
	}

	delete [] cBuf;

	BASS_WMA_EncodeClose(hEncoderWMA);
	BASS_StreamFree(hStreamWAV);

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// кодирование в MP3
//
AOPDLLEXPORT __int32 AOPEncodeMP3(PWCHAR pwcInFile, PWCHAR pwcOutFile, 
	__int32 iBitrate, PENCODECALLBACK pCallback)
{
	HSTREAM    hStreamWAV;
	DWORD      dwSamples;
	DWORD      dwMP3Buffer;
	HBE_STREAM hEncoderMP3;
	BE_CONFIG  beConfig;
	PBYTE      pMP3Buffer = NULL;
	PSHORT     pWAVBuffer = NULL;
	FILE*      hFileOut   = NULL;

	// use the LAME config structure
	ZeroMemory(&beConfig, sizeof(beConfig));

	beConfig.dwConfig                      = BE_CONFIG_LAME;
	beConfig.format.LHV1.dwStructVersion   = 1;
	beConfig.format.LHV1.dwStructSize      = sizeof(beConfig);		
	beConfig.format.LHV1.dwSampleRate      = 44100;               // INPUT FREQUENCY
	beConfig.format.LHV1.dwReSampleRate    = 0;                   // DON"T RESAMPLE
	beConfig.format.LHV1.nMode             = BE_MP3_MODE_STEREO;  // OUTPUT IN STREO
	beConfig.format.LHV1.dwBitrate         = iBitrate;            // MINIMUM BIT RATE
	beConfig.format.LHV1.nPreset           = LQP_HIGH_QUALITY;    // QUALITY PRESET SETTING
	beConfig.format.LHV1.dwMpegVersion     = MPEG1;               // MPEG VERSION (I or II)
	beConfig.format.LHV1.dwPsyModel        = 0;                   // USE DEFAULT PSYCHOACOUSTIC MODEL 
	beConfig.format.LHV1.dwEmphasis        = 0;                   // NO EMPHASIS TURNED ON
	beConfig.format.LHV1.bOriginal         = TRUE;                // SET ORIGINAL FLAG
	beConfig.format.LHV1.bWriteVBRHeader   = FALSE;               // Write INFO tag
	beConfig.format.LHV1.bNoRes            = TRUE;                // No Bit resorvoir

	// открывает исходный файл
	hStreamWAV = BASS_StreamCreateFile(FALSE, pwcInFile, 0, 0, 
		BASS_STREAM_DECODE | BASS_DATA_AVAILABLE | BASS_UNICODE);

	if (0 == hStreamWAV)
	{
		return ERROR_INVALID_HANDLE;
	}

	// Open MP3 file
	hFileOut= _wfopen(pwcOutFile, L"wb+");

	// Init the MP3 Stream
	if(BE_ERR_SUCCESSFUL != beInitStream(&beConfig, &dwSamples, &dwMP3Buffer, &hEncoderMP3))
	{
		return ERROR_ACCESS_DENIED;
	}

	// Allocate MP3 buffer
	pMP3Buffer = new BYTE[dwMP3Buffer];

	// Allocate WAV buffer
	pWAVBuffer = new SHORT[dwSamples];

	// Check if Buffer are allocated properly
	if(!pMP3Buffer || !pWAVBuffer)
	{
		return ERROR_OUTOFMEMORY;
	}

	// пишем данные
	INT   iCount;
	QWORD qwPos;
	DWORD dwLength; 
	DWORD dwWrite;

	dwLength = (DWORD)BASS_ChannelGetLength(hStreamWAV, BASS_POS_BYTE);
	qwPos    = 0;

	while (BASS_ChannelIsActive(hStreamWAV) && ((DWORD)qwPos < dwLength))
	{
		iCount = BASS_ChannelGetData(hStreamWAV, pWAVBuffer, dwSamples * sizeof(SHORT));

		if (((DWORD)qwPos + iCount) < dwLength)
		{
			beEncodeChunk(hEncoderMP3, iCount >> 1, pWAVBuffer, pMP3Buffer, &dwWrite);
		}
		else
		{
			beEncodeChunk(hEncoderMP3, (dwLength - (DWORD)qwPos) >> 1, pWAVBuffer, pMP3Buffer, &dwWrite);
		}

		fwrite(pMP3Buffer, 1, dwWrite, hFileOut);

		qwPos = BASS_ChannelGetPosition(hStreamWAV, BASS_POS_BYTE);

		if (NULL != pCallback)
		{
			pCallback(ENCODE_POS, (DWORD)qwPos, dwLength);
		}
	}

	beDeinitStream(hEncoderMP3, pMP3Buffer, &dwWrite);

	if (dwWrite)
	{
		fwrite(pMP3Buffer, 1, dwWrite, hFileOut);
	}

	beCloseStream(hEncoderMP3);

	BASS_StreamFree(hStreamWAV);

	// Delete WAV buffer
	delete [] pWAVBuffer;

	// Delete MP3 Buffer
	delete [] pMP3Buffer;

	// Close output file
	fclose(hFileOut);

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// кодирование в OGG
//
#define READFOROGG 32768

AOPDLLEXPORT __int32 AOPEncodeOGG(PWCHAR pwcInFile, PWCHAR pwcOutFile, PWCHAR pwcTitle, 
	PWCHAR pwcAuthor, PWCHAR pwcAlbumTitle, PWCHAR pwcGenre, PWCHAR pwcYear, 
	__int32 iBitrate, PENCODECALLBACK pCallback)
{
	HSTREAM          hStreamWAV;
	FILE*            hFileOut   = NULL;
	vorbis_info      vi;
	vorbis_comment   vc;
	vorbis_dsp_state vd;
	vorbis_block     vb;
	ogg_stream_state os;
	ogg_page         og;
	ogg_packet       op;
	int              eos = 0;

	// открывает исходный файл
	hStreamWAV = BASS_StreamCreateFile(FALSE, pwcInFile, 0, 0, 
		BASS_STREAM_DECODE | BASS_DATA_AVAILABLE | BASS_UNICODE);

	if (0 == hStreamWAV)
	{
		return ERROR_INVALID_HANDLE;
	}

	// Open OGG file
	hFileOut= _wfopen(pwcOutFile, L"wb+");

	// encode setup
	vorbis_info_init(&vi);
	
	// choose an encoding mode
	if (vorbis_encode_init(&vi, 2, 44100, -1, iBitrate, -1))
	{
		return ERROR_INVALID_HANDLE;
	}

	// add a comment
	{
		CHAR pcTmp[400];

		vorbis_comment_init(&vc);

		vorbis_comment_add_tag(&vc, "COMMENT", "Audio One Pack");

		WideCharToMultiByte(CP_UTF8, 0, pwcTitle, -1, pcTmp, 400, NULL, NULL);
		vorbis_comment_add_tag(&vc, "TITLE", pcTmp);

		WideCharToMultiByte(CP_UTF8, 0, pwcAuthor, -1, pcTmp, 400, NULL, NULL);
		vorbis_comment_add_tag(&vc, "ARTIST", pcTmp);

		WideCharToMultiByte(CP_UTF8, 0, pwcAlbumTitle, -1, pcTmp, 400, NULL, NULL);
		vorbis_comment_add_tag(&vc, "ALBUM", pcTmp);

		WideCharToMultiByte(CP_UTF8, 0, pwcYear, -1, pcTmp, 400, NULL, NULL);
		vorbis_comment_add_tag(&vc, "DATE", pcTmp);

		WideCharToMultiByte(CP_UTF8, 0, pwcGenre, -1, pcTmp, 400, NULL, NULL);
		vorbis_comment_add_tag(&vc, "GENRE", pcTmp);
	}

	// set up the analysis state and auxiliary encoding storage
	vorbis_analysis_init(&vd, &vi);
	vorbis_block_init(&vd, &vb);

	// set up our packet->stream encoder
	srand((unsigned int)time(NULL));
	
	ogg_stream_init(&os, rand());

	// vorbis streams begin with three headers
	{
		ogg_packet header;
		ogg_packet header_comm;
		ogg_packet header_code;

		vorbis_analysis_headerout(&vd, &vc, &header, &header_comm, &header_code);

		ogg_stream_packetin(&os, &header);
		ogg_stream_packetin(&os, &header_comm);
		ogg_stream_packetin(&os, &header_code);

		// This ensures the actual audio data will start on a new page, as per spec
		while(!eos)
		{
			int result;
			
			result = ogg_stream_flush(&os, &og);
			if (0 == result)
			{
				break;
			}

			fwrite(og.header, 1, og.header_len, hFileOut);
			fwrite(og.body, 1, og.body_len, hFileOut);
		}
	}

	// пишем данные
	INT   iCount;
	QWORD qwPos;
	DWORD dwLength; 
	CHAR  *cBuf;
	long  i;

	dwLength = (DWORD)BASS_ChannelGetLength(hStreamWAV, BASS_POS_BYTE);
	qwPos    = 0;
	cBuf     = new CHAR[READFOROGG * 4 + 44];

	while (!eos)
	{
		iCount = BASS_ChannelGetData(hStreamWAV, cBuf, READFOROGG * 4);

		if (((DWORD)qwPos + iCount) >= dwLength)
		{
			iCount = dwLength - (DWORD)qwPos;
		}

		if (0 == iCount)
		{
			vorbis_analysis_wrote(&vd, 0);
		}
		else
		{
			// expose the buffer to submit data
			float **buffer = vorbis_analysis_buffer(&vd, READFOROGG);

			// uninterleave samples
			for(i = 0; i < (iCount / 4); i++)
			{
				buffer[0][i] = ((cBuf[i * 4 + 1]<< 8) | (0x00ff & (int)cBuf[i * 4])) / 32768.f;
				buffer[1][i] = ((cBuf[i * 4 + 3] << 8) | (0x00ff & (int)cBuf[i * 4 + 2])) / 32768.f;
			}
		}

		// tell the library how much we actually submitted
		vorbis_analysis_wrote(&vd, i);

		while(1 == vorbis_analysis_blockout(&vd, &vb))
		{
			// analysis, assume we want to use bitrate management
			vorbis_analysis(&vb, NULL);
			vorbis_bitrate_addblock(&vb);

			while(vorbis_bitrate_flushpacket(&vd, &op))
			{
				// weld the packet into the bitstream
				ogg_stream_packetin(&os, &op);

				// write out pages (if any)
				while(!eos)
				{
					int result;
					
					result = ogg_stream_pageout(&os, &og);

					if(0 == result)
					{
						break;
					}

					fwrite(og.header, 1, og.header_len, hFileOut);
					fwrite(og.body, 1, og.body_len, hFileOut);

					if(ogg_page_eos(&og))
					{
						eos = 1;
					}
				}
			}
		}

		qwPos = BASS_ChannelGetPosition(hStreamWAV, BASS_POS_BYTE);

		if (NULL != pCallback)
		{
			pCallback(ENCODE_POS, (DWORD)qwPos, dwLength);
		}
	}

	delete [] cBuf;

	// clean up and exit. vorbis_info_clear() must be called last
	ogg_stream_clear(&os);
	vorbis_block_clear(&vb);
	vorbis_dsp_clear(&vd);
	vorbis_comment_clear(&vc);
	vorbis_info_clear(&vi);

	// 
	BASS_StreamFree(hStreamWAV);

	// Close output file
	fclose(hFileOut);

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// кодирование в FLAC
//
#define FLAC_INPUT_BYTES 65536

struct
{
	PENCODECALLBACK pCallback;
} FLACWRITECFG, *PFLACWRITECFG;

FLAC__StreamEncoderWriteStatus AOPEncodeFLACWrite(const FLAC__StreamEncoder *encoder, 
	const FLAC__byte buffer[], size_t bytes, unsigned samples, unsigned current_frame, void *client_data);

AOPDLLEXPORT __int32 AOPEncodeFLAC(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback)
{
	FILE*           hFileWAV  = NULL;
	FILE*           hFileFLAC = NULL;
	RiffChunkHeader riff_chunk_header;
	ChunkHeader     chunk_header;
	WaveHeader      WaveHeader;
	uint32_t        total_samples = 0;

	FLAC__bool                               ok = true;
	FLAC__StreamEncoder                      *encoder = 0;
	FLAC__StreamEncoderInitStatus            init_status;
	//FLAC__StreamMetadata                     *metadata[2];
	//FLAC__StreamMetadata_VorbisComment_Entry entry;
	unsigned                                 sample_rate = 0;
	unsigned                                 channels = 0;
	unsigned                                 bps = 0;
	FLAC__byte                               *buffer;
	FLAC__int32                              *pcm;

	// входной файл
	hFileWAV = _wfopen(pwcInFile, L"rb");

	if (NULL == hFileWAV)
	{
		return ERROR_OPEN_FAILED;
	}

	// выходной файл 
	hFileFLAC = _wfopen(pwcOutFile, L"w+b");

	if (NULL == hFileFLAC)
	{
		fclose(hFileWAV);

		return ERROR_CREATE_FAILED;
	}

	// чтение заголовка WAV файла
	if ((0 == fread(&riff_chunk_header, sizeof(RiffChunkHeader), 1, hFileWAV)) || 
		strncmp(riff_chunk_header.ckID, "RIFF", 4) ||
		strncmp(riff_chunk_header.formType, "WAVE", 4))
	{
		fclose(hFileWAV);
		fclose(hFileFLAC);

		return ERROR_READ_FAULT;
	}

	while (1)
	{
		if (0 == fread(&chunk_header, sizeof(ChunkHeader), 1, hFileWAV))
		{
			fclose(hFileWAV);
			fclose(hFileFLAC);

			return ERROR_READ_FAULT;
		}

		WavpackLittleEndianToNative(&chunk_header, ChunkHeaderFormat);

		if (!strncmp(chunk_header.ckID, "fmt ", 4))
		{
			if (chunk_header.ckSize < 16 || chunk_header.ckSize > sizeof (WaveHeader) ||
				0 == fread(&WaveHeader, chunk_header.ckSize, 1, hFileWAV))
			{
				fclose(hFileWAV);
				fclose(hFileFLAC);

				return ERROR_READ_FAULT;
			}
		}
		else 

			if (!strncmp(chunk_header.ckID, "data", 4))
			{
				total_samples = chunk_header.ckSize / WaveHeader.BlockAlign;

				break;
			}
	}

	encoder = FLAC__stream_encoder_new();

	if (0 == encoder)
	{
		fclose(hFileWAV);
		fclose(hFileFLAC);

		return ERROR_CREATE_FAILED;
	}

	channels    = 2;
	bps         = 16;
	sample_rate = 44100;

	ok &= FLAC__stream_encoder_set_verify(encoder, true);
	ok &= FLAC__stream_encoder_set_channels(encoder, channels);
	ok &= FLAC__stream_encoder_set_bits_per_sample(encoder, bps);
	ok &= FLAC__stream_encoder_set_sample_rate(encoder, sample_rate);
	ok &= FLAC__stream_encoder_set_compression_level(encoder, (unsigned)-1);
	ok &= FLAC__stream_encoder_set_total_samples_estimate(encoder, total_samples);

	// добавление метаданных
	/*
	if (ok)
	{
		if((metadata[0] = FLAC__metadata_object_new(FLAC__METADATA_TYPE_VORBIS_COMMENT)) == NULL ||
			(metadata[1] = FLAC__metadata_object_new(FLAC__METADATA_TYPE_PADDING)) == NULL ||
			!FLAC__metadata_object_vorbiscomment_entry_from_name_value_pair(&entry, "ARTIST", "Some Artist") ||
			!FLAC__metadata_object_vorbiscomment_append_comment(metadata[0], entry, false) ||
			!FLAC__metadata_object_vorbiscomment_entry_from_name_value_pair(&entry, "YEAR", "1984") ||
			!FLAC__metadata_object_vorbiscomment_append_comment(metadata[0], entry, false))
		{
				ok = false;
		}

		metadata[1]->length = 1234;

		ok = FLAC__stream_encoder_set_metadata(encoder, metadata, 2);
	}
	*/

	// инициализация енкодера
	if (ok)
	{
		init_status = FLAC__stream_encoder_init_stream(encoder, AOPEncodeFLACWrite, NULL, NULL, NULL, hFileFLAC);

		if(FLAC__STREAM_ENCODER_INIT_STATUS_OK != init_status)
		{
			ok = false;
		}
	}

	// кодирование
	if(ok)
	{
		buffer = new FLAC__byte[FLAC_INPUT_BYTES * bps * channels];
		pcm    = new FLAC__int32[FLAC_INPUT_BYTES * channels];

		size_t left = (size_t)total_samples;

		while (ok && left)
		{
			size_t need = (left > FLAC_INPUT_BYTES ? (size_t)FLAC_INPUT_BYTES : (size_t)left);

			if (fread(buffer, channels * (bps / 8), need, hFileWAV) != need)
			{
				fprintf(stderr, "ERROR: reading from WAVE file\n");
				
				ok = false;
			}
			else {
				size_t i;
				for(i = 0; i < need * channels; i++) {
					
					pcm[i] = (FLAC__int32)(((FLAC__int16)(FLAC__int8)buffer[2*i+1] << 8) | (FLAC__int16)buffer[2*i]);
				}

				ok = FLAC__stream_encoder_process_interleaved(encoder, pcm, (uint32_t)need);
			}

			left -= need;

			if (NULL != pCallback)
			{
				pCallback(ENCODE_POS, (total_samples - left) * 2 * (bps >> 3), total_samples * 2 * (bps >> 3));
			}
		}

		delete [] buffer;
		delete [] pcm;
	}

	ok &= FLAC__stream_encoder_finish(encoder);

	//FLAC__metadata_object_delete(metadata[0]);
	//FLAC__metadata_object_delete(metadata[1]);

	FLAC__stream_encoder_delete(encoder);

	fclose(hFileWAV);
	fclose(hFileFLAC);

	return ERROR_SUCCESS;
}

//
FLAC__StreamEncoderWriteStatus AOPEncodeFLACWrite(const FLAC__StreamEncoder *encoder, 
	const FLAC__byte buffer[], size_t bytes, unsigned samples, unsigned current_frame, void *client_data)
{
	FILE *f = (FILE*)client_data;

	fwrite(buffer, 1, bytes, f);

	return FLAC__STREAM_ENCODER_WRITE_STATUS_OK;
};


//////////////////////////////////////////////////////////////////////////
// кодирование в APE
//
/***************************************************************************************
MAC_DLL structure (holds function pointers)
***************************************************************************************/
struct MAC_COMPRESS_DLL
{
	// APECompress functions
	proc_APECompress_Create        Create;
	proc_APECompress_Destroy       Destroy;
	proc_APECompress_StartW        StartW;
	proc_APECompress_AddData       AddData;
	proc_APECompress_Finish        Finish;
	proc_APECompress_LockBuffer    LockBuffer;
	proc_APECompress_UnlockBuffer  UnlockBuffer;
};

/***************************************************************************************
GetFunctions - helper that gets the function addresses for the functions we need
***************************************************************************************/
int APEGetFunctions(HMODULE hMACDll, MAC_COMPRESS_DLL * pMACDll)
{
	// clear
	memset(pMACDll, 0, sizeof(MAC_COMPRESS_DLL));

	// load the functions
	if (hMACDll != NULL)
	{	
		pMACDll->Create       = (proc_APECompress_Create) GetProcAddress(hMACDll, "c_APECompress_Create");
		pMACDll->Destroy      = (proc_APECompress_Destroy) GetProcAddress(hMACDll, "c_APECompress_Destroy");
		pMACDll->StartW       = (proc_APECompress_StartW) GetProcAddress(hMACDll, "c_APECompress_StartW");
		pMACDll->AddData      = (proc_APECompress_AddData) GetProcAddress(hMACDll, "c_APECompress_AddData");
		pMACDll->Finish       = (proc_APECompress_Finish) GetProcAddress(hMACDll, "c_APECompress_Finish");
		pMACDll->LockBuffer   = (proc_APECompress_LockBuffer) GetProcAddress(hMACDll, "c_APECompress_LockBuffer");
		pMACDll->UnlockBuffer = (proc_APECompress_UnlockBuffer) GetProcAddress(hMACDll, "c_APECompress_UnlockBuffer");
	}

	// error check
	if ((pMACDll->Create == NULL) ||
		(pMACDll->Destroy == NULL) ||
		(pMACDll->StartW == NULL) ||
		(pMACDll->AddData == NULL) ||
		(pMACDll->Finish == NULL) || 
		(pMACDll->LockBuffer == NULL) ||
		(pMACDll->UnlockBuffer == NULL))
	{
		return -1;
	}

	return 0;
}

/***************************************************************************************
Version checks the dll / interface
***************************************************************************************/
int APEVersionCheckInterface(HMODULE hMACDll)
{
	int nRetVal = -1;
	proc_GetInterfaceCompatibility GetInterfaceCompatibility = (proc_GetInterfaceCompatibility)
		GetProcAddress(hMACDll, "GetInterfaceCompatibility");
	if (GetInterfaceCompatibility)
	{
		nRetVal = GetInterfaceCompatibility(MAC_FILE_VERSION_NUMBER, TRUE, NULL);
	}

	return nRetVal;
}

/***************************************************************************************
Fill a WAVEFORMATEX structure
***************************************************************************************/
int APEFillWaveFormatExStructure(WAVEFORMATEX *pWaveFormatEx, int nSampleRate, int nBitsPerSample, int nChannels)
{
	pWaveFormatEx->cbSize         = 0;
	pWaveFormatEx->nSamplesPerSec = nSampleRate;
	pWaveFormatEx->wBitsPerSample = nBitsPerSample;
	pWaveFormatEx->nChannels      = nChannels;
	pWaveFormatEx->wFormatTag     = 1;

	pWaveFormatEx->nBlockAlign     = (pWaveFormatEx->wBitsPerSample / 8) * pWaveFormatEx->nChannels;
	pWaveFormatEx->nAvgBytesPerSec = pWaveFormatEx->nBlockAlign * pWaveFormatEx->nSamplesPerSec;

	return 0;
}

//
#define APE_INPUT_BYTES 65536

//
AOPDLLEXPORT __int32 AOPEncodeAPE(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback)
{
	int nRetVal;

	// load the DLL
	HMODULE hMACDll = LoadLibrary(L"MACDll.dll");

	if (NULL == hMACDll)
	{
		return ERROR_LOADINGAPE_DLL;
	}

	// always check the interface version (so we don't crash if something changed)
	if (APEVersionCheckInterface(hMACDll) != 0)
	{
		FreeLibrary(hMACDll);

		return ERROR_LOADINGAPE_INFO_DLL;
	}

	// get the functions
	MAC_COMPRESS_DLL MACDll; 
	
	if (APEGetFunctions(hMACDll, &MACDll) != 0)
	{
		FreeLibrary(hMACDll);

		return -1;
	}

	// set the input WAV format
	WAVEFORMATEX wfeAudioFormat; 
	
	APEFillWaveFormatExStructure(&wfeAudioFormat, 44100, 16, 2);

	// create the encoder interface
	APE_COMPRESS_HANDLE hAPECompress = MACDll.Create(&nRetVal);

	if (NULL == hAPECompress)
	{
		FreeLibrary(hMACDll);

		return -1;
	}

	// start the encoder
	nRetVal = MACDll.StartW(hAPECompress, (char*)pwcOutFile, &wfeAudioFormat, 
		-1 /* MAX_AUDIO_BYTES_UNKNOWN */, COMPRESSION_LEVEL_HIGH, NULL, 
		CREATE_WAV_HEADER_ON_DECOMPRESSION);

	if (0 != nRetVal)
	{
		MACDll.Destroy(hAPECompress);

		FreeLibrary(hMACDll);

		return -1;
	}

	// pump through and feed the encoder audio data (white noise for the sample)
	// входной файл
	FILE *hFileWAV;
	RiffChunkHeader riff_chunk_header;
	ChunkHeader     chunk_header;
	WaveHeader      WaveHeader;
	uint32_t        total_samples = 0;
	
	hFileWAV = _wfopen(pwcInFile, L"rb");

	if (NULL == hFileWAV)
	{
		MACDll.Destroy(hAPECompress);

		FreeLibrary(hMACDll);

		return ERROR_OPEN_FAILED;
	}

	// чтение заголовка WAV файла
	if ((0 == fread(&riff_chunk_header, sizeof(RiffChunkHeader), 1, hFileWAV)) || 
		strncmp(riff_chunk_header.ckID, "RIFF", 4) ||
		strncmp(riff_chunk_header.formType, "WAVE", 4))
	{
		fclose(hFileWAV);

		MACDll.Destroy(hAPECompress);

		FreeLibrary(hMACDll);

		return ERROR_READ_FAULT;
	}

	while (1)
	{
		if (0 == fread(&chunk_header, sizeof(ChunkHeader), 1, hFileWAV))
		{
			fclose(hFileWAV);

			MACDll.Destroy(hAPECompress);

			FreeLibrary(hMACDll);

			return ERROR_READ_FAULT;
		}

		WavpackLittleEndianToNative(&chunk_header, ChunkHeaderFormat);

		if (!strncmp(chunk_header.ckID, "fmt ", 4))
		{
			if (chunk_header.ckSize < 16 || chunk_header.ckSize > sizeof (WaveHeader) ||
				0 == fread(&WaveHeader, chunk_header.ckSize, 1, hFileWAV))
			{
				fclose(hFileWAV);
				MACDll.Destroy(hAPECompress);

				FreeLibrary(hMACDll);

				return ERROR_READ_FAULT;
			}
		}
		else 

			if (!strncmp(chunk_header.ckID, "data", 4))
			{
				total_samples = chunk_header.ckSize / WaveHeader.BlockAlign;

				break;
			}
	}

	int nAudioBytesLeft = total_samples << 2;
	unsigned char *cBuffer;

	cBuffer = new unsigned char[APE_INPUT_BYTES];

	while (nAudioBytesLeft > 0)
	{
		//
		int nBytesToAdd = min(APE_INPUT_BYTES, nAudioBytesLeft);

		fread(cBuffer, 1, nBytesToAdd, hFileWAV);

		//
		nRetVal = MACDll.AddData(hAPECompress, &cBuffer[0], nBytesToAdd);

		if (nRetVal)
		{
			break;
		}

		nAudioBytesLeft -= nBytesToAdd;

		//
		if (NULL != pCallback)
		{
			pCallback(ENCODE_POS, (total_samples << 2) - nAudioBytesLeft, (total_samples << 2));
		}
	}

	delete [] cBuffer;

	fclose(hFileWAV);

	// finalize the file (could append a tag, or WAV terminating data)
	MACDll.Finish(hAPECompress, NULL, 0, 0);

	// clean up and quit
	MACDll.Destroy(hAPECompress);
	FreeLibrary(hMACDll);

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// кодирование в WV
//
#define WV_INPUT_SAMPLES 65536

//
int AOPEncodeWVWrite(void *id, void *data, int32_t length);

//
AOPDLLEXPORT __int32 AOPEncodeWV(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback)
{
	FILE*           hFileWAV  = NULL;
	FILE*           hFileWV   = NULL;

	WavpackConfig   wvConfig;
	WavpackContext  *wpc;
	RiffChunkHeader riff_chunk_header;
	ChunkHeader     chunk_header;
	WaveHeader      WaveHeader;
	uint32_t        total_samples = 0;

	// инициализация
	ZeroMemory(&wvConfig, sizeof(WavpackConfig));
	
	// входной файл
	hFileWAV = _wfopen(pwcInFile, L"rb");

	if (NULL == hFileWAV)
	{
		return ERROR_OPEN_FAILED;
	}

	// выходной файл 
	hFileWV = _wfopen(pwcOutFile, L"wb+");

	if (NULL == hFileWV)
	{
		fclose(hFileWAV);

		return ERROR_CREATE_FAILED;
	}

	// чтение заголовка WAV файла
	if ((0 == fread(&riff_chunk_header, sizeof(RiffChunkHeader), 1, hFileWAV)) || 
		strncmp(riff_chunk_header.ckID, "RIFF", 4) ||
		strncmp(riff_chunk_header.formType, "WAVE", 4))
	{
		fclose(hFileWAV);
		fclose(hFileWV);

		return ERROR_READ_FAULT;
	}

	while (1)
	{
		if (0 == fread(&chunk_header, sizeof(ChunkHeader), 1, hFileWAV))
		{
			fclose(hFileWAV);
			fclose(hFileWV);

			return ERROR_READ_FAULT;
		}

		WavpackLittleEndianToNative(&chunk_header, ChunkHeaderFormat);

		if (!strncmp(chunk_header.ckID, "fmt ", 4))
		{
			if (chunk_header.ckSize < 16 || chunk_header.ckSize > sizeof (WaveHeader) ||
				 0 == fread(&WaveHeader, chunk_header.ckSize, 1, hFileWAV))
			{
				fclose(hFileWAV);
				fclose(hFileWV);

				return ERROR_READ_FAULT;
			}

			wvConfig.bits_per_sample = 16;
			wvConfig.channel_mask    = 2;
		}
		else 
			
		if (!strncmp(chunk_header.ckID, "data", 4))
		{
			total_samples = chunk_header.ckSize / WaveHeader.BlockAlign;

			break;
		}
	}

	wvConfig.bytes_per_sample = WaveHeader.BlockAlign / WaveHeader.NumChannels;
	wvConfig.num_channels     = WaveHeader.NumChannels;
	wvConfig.sample_rate      = WaveHeader.SampleRate;

	wpc = WavpackOpenFileOutput(AOPEncodeWVWrite, hFileWV, NULL);

	if (FALSE == WavpackSetConfiguration(wpc, &wvConfig, total_samples))
	{
		fclose(hFileWAV);
		fclose(hFileWV);

		WavpackCloseFile(wpc);

		return ERROR_CREATE_FAILED;
	}

	WavpackPackInit(wpc);

	uint32_t uiSamplesRemaining;
	uint32_t uiSamplesRead;
	uint32_t uiSamplesAllCount;
	int      iBytesPerSample;
	int      iChannelsCount;
	int32_t  *sample_buffer;
	UCHAR    *input_buffer;

	uiSamplesRead      = 0;
	uiSamplesAllCount  = WavpackGetNumSamples(wpc);
	uiSamplesRemaining = uiSamplesAllCount;
	iBytesPerSample    = 4;
	iChannelsCount     = 2;
	input_buffer       = (UCHAR*)malloc(WV_INPUT_SAMPLES * iBytesPerSample);
	sample_buffer      = (__int32*)malloc(WV_INPUT_SAMPLES * sizeof(int32_t) * iChannelsCount);

	// кодирование
	while (1)
	{
		uint32_t uiBytesToRead, uiBytesRead = 0;
		uint32_t uiSampleCount;

		// вычисление размера очередной порции для чтения
		if (WV_INPUT_SAMPLES < uiSamplesRemaining)
		{
			uiBytesToRead = WV_INPUT_SAMPLES * iBytesPerSample;
		}
		else
		{
			uiBytesToRead = uiSamplesRemaining * iBytesPerSample;
		}

		uiSamplesRemaining = uiBytesToRead / iBytesPerSample;

		// чтение очередной порции
		uiSampleCount = (uint32_t)fread(input_buffer, 1, uiBytesToRead, hFileWAV) / iBytesPerSample;

		if (0 == uiSampleCount)
		{
			break;
		}

		uiSamplesRead += uiSampleCount;

		// формирование буфера для кодирования
		UINT    uiCount = uiSampleCount * iChannelsCount;
		UCHAR   *sptr   = input_buffer;
		int32_t *dptr   = sample_buffer;

		while (uiCount--)
		{
			*dptr++ = sptr [0] | ((int32_t)(signed char) sptr [1] << 8);
			sptr += 2;
		}

		WavpackPackSamples(wpc, sample_buffer, uiSampleCount);

		if (NULL != pCallback)
		{
			pCallback(ENCODE_POS, uiSamplesRead * iBytesPerSample, uiSamplesAllCount * iBytesPerSample);
		}

		if (uiSamplesRead >= total_samples)
		{
			break;
		}
	}

	WavpackFlushSamples(wpc);
	WavpackCloseFile(wpc);

	free(sample_buffer);
	free(input_buffer);

	fclose(hFileWAV);
	fclose(hFileWV);

	return ERROR_SUCCESS;
}

//
int AOPEncodeWVWrite(void *id, void *data, int32_t length)
{
	FILE* fOutWV = (FILE*)id;

	if (fOutWV && data && length)
	{
		fwrite(data, 1, length, fOutWV);
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// кодирование в TTA
//
/*
DWORD   dwTTALength;
BOOL    AOPEncodeTTACallback(const TTAStat &stat, void *uParam);

AOPDLLEXPORT __int32 AOPEncodeTTA(PWCHAR pwcInFile, PWCHAR pwcOutFile, PENCODECALLBACK pCallback)
{
	// получение размера WAV файла
	HSTREAM hStreamWAV;

	hStreamWAV = BASS_StreamCreateFile(FALSE, pwcInFile, 0, 0, BASS_STREAM_DECODE | BASS_DATA_AVAILABLE | BASS_UNICODE);
	if (0 == hStreamWAV)
	{
		return ERROR_INVALID_HANDLE;
	}

	dwTTALength = (DWORD)BASS_ChannelGetLength(hStreamWAV, BASS_POS_BYTE);

	BASS_StreamFree(hStreamWAV);

	// запуск кодирования
	TTALib::TTAError result = TTALib::Wav2TTA(pwcInFile, pwcOutFile, false, (TTALib::TTACALLBACK)AOPEncodeTTACallback, pCallback); 
	
	if (result > 0)
	{
		return ERROR_CREATE_FAILED;
	}

	return ERROR_SUCCESS;
}

/*
BOOL AOPEncodeTTACallback(const TTAStat &stat, void *uParam)
{
	if (NULL != uParam)
	{
		PENCODECALLBACK pCallback = (PENCODECALLBACK)uParam;

		if ((stat.input_bytes >= (DWORD)(dwTTALength * 0.3)) && (0 == iTTATrial))
		{
			if (NULL != pCallback)
			{
				pCallback(ENCODE_POS, dwTTALength, dwTTALength);
			}

			return FALSE;
		}

		pCallback(ENCODE_POS, stat.input_bytes, dwTTALength);
	}

	return TRUE;
}
*/


//
// ФУНКЦИИ РАБОТЫ С MUSIC CD 
//

PAUDIOBURNCALLBACK pMusicBurnUserCallback = NULL;
PVOID              pvMusicCDGrabber       = NULL;
PVOID              pvJolietFileTree       = NULL;
PVOID              pvParentNode           = NULL;
INT                iMusicCDSize           = 0;    // размер в кБ

VOID __stdcall MusicCallback(CALLBACK_NUMBER p__CallbackNumber, PVOID p_CallbackContext, 
	PVOID p_CallbackSpecial1, PVOID p_CallbackSpecial2);

//////////////////////////////////////////////////////////////////////////
// создание Music CD
//
AOPDLLEXPORT __int32 AOPMusicCDInit(PDEVICEINFO pDeviceInfo)
{
	EXCEPTION_NUMBER        expNum = EN_SUCCESS;
	ULONG                   ulStatus;
	CDB_FAILURE_INFORMATION cdbInf;

	// открытие девайса
	expNum = StarBurn_CdvdBurnerGrabber_Create(&pvMusicCDGrabber, 
		NULL, 0, &ulStatus, &cdbInf, (PCALLBACK)(MusicCallback), NULL, 
		pDeviceInfo->ucPortID, 
		pDeviceInfo->ucBusID,
		pDeviceInfo->ucTargetID,
		pDeviceInfo->ucLUN, 1);

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	// создание файловой системы
	expNum = StarBurn_ISO9660JolietFileTree_Create(&pvJolietFileTree,	NULL, 0, &ulStatus, 
		(PCALLBACK)(MusicCallback), NULL, TRUE, FALSE, TRUE, FILE_TREE_JOLIET);

	if (EN_SUCCESS != expNum)
	{
		return ERROR_CREATE_FAILED;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// освобождение ресурсов занятых при создании Music CD
//
AOPDLLEXPORT __int32 AOPMusicCDFree()
{
	if (NULL != pvMusicCDGrabber)
	{
		StarBurn_Destroy(&pvMusicCDGrabber);

		pvMusicCDGrabber       = NULL;
		pMusicBurnUserCallback = NULL;
		iMusicCDSize           = 0;
	}

	if (NULL != pvJolietFileTree)
	{
		StarBurn_Destroy(&pvJolietFileTree);

		pvParentNode = NULL;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// добавление каталога
//
AOPDLLEXPORT __int32 __stdcall AOPMusicCDAddFolder(PWCHAR pwcFolder)
{
	EXCEPTION_NUMBER expNum = EN_SUCCESS;
	ULONG            ulStatus;
	PVOID            pvNewChild = NULL;

	expNum = StarBurn_ISO9660JolietFileTree_AddW(pvJolietFileTree, NULL, 0, &ulStatus, 
		NULL, pwcFolder, FILE_TIME_LAST_WRITE, &pvParentNode, &pvNewChild);
	
	if (EN_SUCCESS != expNum)
	{
		return ERROR_CREATE_FAILED;
	}

	if (NULL == pvNewChild)
	{
		return ERROR_CREATE_FAILED;
	}

	pvParentNode = pvNewChild;

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// добавление файла
//
AOPDLLEXPORT __int32 AOPMusicCDAddFile(PWCHAR pwcFilePath)
{
	// добавление файла
	EXCEPTION_NUMBER expNum = EN_SUCCESS;
	ULONG            ulStatus;
	PVOID            pvNewChild = NULL;

	expNum = StarBurn_ISO9660JolietFileTree_AddW(pvJolietFileTree, NULL, 0, &ulStatus, 
		pwcFilePath, NULL, FILE_TIME_LAST_WRITE, &pvParentNode, &pvNewChild);

	if (EN_SUCCESS != expNum)
	{
		return ERROR_CREATE_FAILED;
	}

	// прибавляем счетчик размера структуры
	LARGE_INTEGER liSize;

	liSize.QuadPart = 0;

	if (EN_SUCCESS == StarBurn_ISO9660JolietFileTree_GetFileSizeInUCHARs(pvJolietFileTree, pvNewChild, &liSize))
	{
		iMusicCDSize += (INT)(liSize.QuadPart / 1024);
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// подняться на один уровень вверх структуры диска
//
AOPDLLEXPORT __int32 AOPMusicCDTreeUp()
{
	PVOID pvNode = NULL;

	pvNode = StarBurn_ISO9660JolietFileTree_GetParent(pvJolietFileTree, pvParentNode);

	if (NULL != pvNode)
	{
		pvParentNode = pvNode;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// прожиг Audio CD
//
AOPDLLEXPORT __int32 AOPMusicCDBurn(PMUSICBURNCALLBACK pCallback, __int32 iSpeed, PWCHAR pwcVolume)
{
	EXCEPTION_NUMBER        expNum = EN_SUCCESS;
	ULONG                   ulStatus;
	CDB_FAILURE_INFORMATION cdbInf;
	CHAR                    cVolume[200];

	ZeroMemory(cVolume, sizeof(cVolume));
	sprintf(cVolume, "%S", pwcVolume);

	expNum = StarBurn_ISO9660JolietFileTree_BuildImage(pvJolietFileTree, NULL, 0, &ulStatus, 
		0, 0, FALSE, "July 26, 2007", "Whole Group", "Audio One Pack");

	if (EN_SUCCESS != expNum)
	{
		return ERROR_CREATE_FAILED;
	}

	pMusicBurnUserCallback = pCallback;

	// Try to test unit ready
	expNum =	StarBurn_CdvdBurnerGrabber_TestUnitReady(pvMusicCDGrabber, NULL, 0, &ulStatus, &cdbInf);
	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	// Try to set BUP status
	expNum =	StarBurn_CdvdBurnerGrabber_SetBUP(pvMusicCDGrabber, NULL, 0, &ulStatus, &cdbInf, TRUE);

	//Try to set current write speed
	expNum =	StarBurn_CdvdBurnerGrabber_SetSpeeds(pvMusicCDGrabber, NULL, 0, &ulStatus, &cdbInf, 
		g_CDStandardSpeeds[iSpeed].ulSpeedInKBps, g_CDStandardSpeeds[iSpeed].ulSpeedInKBps);

	// Try to send OPC
	expNum =	StarBurn_CdvdBurnerGrabber_SendOPC(pvMusicCDGrabber, NULL, 0, &ulStatus, &cdbInf);

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	// Burn
	expNum = StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromTree(pvMusicCDGrabber, NULL, 0, &ulStatus, 
		&cdbInf, pvJolietFileTree, FALSE, FALSE /*Test*/, FALSE, WRITE_REPORT_DELAY_IN_SECONDS, 
BUFFER_STATUS_REPORT_DELAY_IN_SECONDS);

	if (EN_SUCCESS != expNum)
	{
		return ERROR_ACCESS_DENIED;
	}

	return ERROR_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// Callback функция прожига Music CD
//
VOID __stdcall MusicCallback(CALLBACK_NUMBER p__CallbackNumber, PVOID p_CallbackContext, 
	PVOID p_CallbackSpecial1, PVOID p_CallbackSpecial2)
{
	LARGE_INTEGER l_FileSizeInLBs;
	LARGE_INTEGER l_LBsWritten;
	LARGE_INTEGER l_CurrentPercent;
	ULONG         l_BufferSizeInUCHARs;
	ULONG         l_BufferFreeSizeInUCHARs;
	ULONG         l_BufferPercent;

	switch ( p__CallbackNumber )
	{
		// If this is file analyze begin
		case CN_TARGET_FILE_ANALYZE_BEGIN:
			//wprintf(L"CN_TARGET_FILE_ANALYZE_BEGIN\n");
			break;

		// If this is file analyze end
		case CN_TARGET_FILE_ANALYZE_END:
			//wprintf(L"CN_TARGET_FILE_ANALYZE_END\n");
			break;

		// If this is cache full begin
		case CN_WAIT_CACHE_FULL_BEGIN:
			//wprintf(L"CN_WAIT_CACHE_FULL_BEGIN\n");
			break;

		// If this is cache full end
		case CN_WAIT_CACHE_FULL_END:
			//wprintf(L"CN_WAIT_CACHE_FULL_END\n");
			break;

		// If this is synchronize cache begin
		case CN_SYNCHRONIZE_CACHE_BEGIN:
			//wprintf(L"CN_SYNCHRONIZE_CACHE_BEGIN\n");
			break;

		// If this is synchronize cache end
		case CN_SYNCHRONIZE_CACHE_END:
			//wprintf(L"CN_SYNCHRONIZE_CACHE_END\n");
			break;

		// If this is packet write
		case CN_CDVD_WRITE_PROGRESS:
			// Get parameters passed with callback
			l_FileSizeInLBs = *(PLARGE_INTEGER)(p_CallbackSpecial1);
			l_LBsWritten    = *(PLARGE_INTEGER)(p_CallbackSpecial2);

			// Calculate number of percent written
			l_CurrentPercent.QuadPart = ((l_LBsWritten.QuadPart * 100) / l_FileSizeInLBs.QuadPart);

			// Update last written percent with current value
			if (NULL != pMusicBurnUserCallback)
			{
				pMusicBurnUserCallback(MUSICBURN_WRITE, (__int32)l_CurrentPercent.QuadPart, 0);
			}
			break;

		case CN_CDVD_BUFFER_STATUS:
			// Get parameters passed with callback
			l_BufferSizeInUCHARs     = *(PULONG)(p_CallbackSpecial1);
			l_BufferFreeSizeInUCHARs = *(PULONG)(p_CallbackSpecial2);

			// Calculate buffer full ratio
			if (0 != l_BufferSizeInUCHARs)
			{
				l_BufferPercent = ((l_BufferFreeSizeInUCHARs * 100 ) / l_BufferSizeInUCHARs);
				l_BufferPercent = (100 - l_BufferPercent);
			}
			else
			{
				l_BufferPercent = 0; // Unknown if buffer size in UCHARs is zero
			}

			// Update last written percent with current value
			if (NULL != pMusicBurnUserCallback)
			{
				pMusicBurnUserCallback(MUSICBURN_BUFFER, (__int32)l_BufferPercent, 0);
			}
			break;

			case CN_CDVD_READ_PROGRESS:
				break;
	}
}

//
// ФУНКЦИИ ДЛЯ АНАЛИЗА МУЗЫКИ
//

//////////////////////////////////////////////////////////////////////////
// анализ указанного файла
//
AOPDLLEXPORT __int32 AOPAnalyzerTrack(PWCHAR pwcFile, PFLOAT pfK, PANALYZECALLBACK pCallBack)
{
	HSTREAM hStream;
	PFLOAT  pfFFT;
	PFLOAT  pfFFTAvr;

	// создание потока из медиафайла
	hStream = BASS_StreamCreateFile(FALSE, (PCHAR)pwcFile, 0, 0, BASS_STREAM_DECODE | BASS_UNICODE);

	if (0 == hStream)
	{
		return ERROR_OPEN_FAILED;
	}

	// выделение памяти для FFT4096
	pfFFT = new FLOAT[2048];

	if (NULL == pfFFT)
	{
		BASS_StreamFree(hStream);

		return ERROR_OUTOFMEMORY;
	}

	ZeroMemory(pfFFT, sizeof(FLOAT) * 2048);

	pfFFTAvr = new FLOAT[2048];

	if (NULL == pfFFTAvr)
	{
		delete [] pfFFT;

		BASS_StreamFree(hStream);

		return ERROR_OUTOFMEMORY;
	}

	ZeroMemory(pfFFTAvr, sizeof(FLOAT) * 2048);

	// расчет усредненного спектра
	UINT  uiCycle    = 0;
	UINT  uiMaxCycle = (UINT)(BASS_ChannelGetLength(hStream, BASS_POS_BYTE) / (4096 * 4)) ;

	while (BASS_ChannelIsActive(hStream))
	{
		if ((4096 * 4) == BASS_ChannelGetData(hStream, pfFFT, BASS_DATA_FFT4096))
		{
			for (int i = 0 ; i < 2048; i++)
			{
				pfFFTAvr[i] += pfFFT[i];
			}

			uiCycle++;

			if (NULL != pCallBack)
			{
				pCallBack(0, (__int32)(80 * ((float)uiCycle / uiMaxCycle)), 100);
			}
		}
	}

	for (int i = 0 ; i < 2048; i++)
	{
		pfFFTAvr[i] /= uiCycle;

		if (NULL != pCallBack)
		{
			pCallBack(0, (__int32)(80 + 5 * (i / 2048.0f)), 100);
		}
	}

	// расчет и анализ АЧХ
	FLOAT fMax = 0;

	for (int i = 0 ; i < 2048; i++)
	{
		if (fMax < pfFFTAvr[i])
		{
			fMax = pfFFTAvr[i];
		}

		if (NULL != pCallBack)
		{
			pCallBack(0, (__int32)(85 + 5 * (i / 2048.0f)), 100);
		}
	}

	// вычисление среднего dB на промежутке 20000Hz - 22050Hz
	float fDBAvr = 0.;
	int iCount = 0;
	for (int i = (int)(2048.f * 20000.0f / 22050.f); i < 2048; i++, iCount++)
	{
		fDBAvr += 20.0f * log10f(pfFFTAvr[i] / fMax);
	}

	fDBAvr /= iCount;

	// подсчет коэффициента CD-Quality
	if (fDBAvr > -80.)
	{
		*pfK = 1.0;
	}
	else

	if (fDBAvr < -90.)
	{
		*pfK = 0.0;
	}

	else
	{
		*pfK = (fDBAvr + 90) / 10;
	}

	// освобождение памяти для FFT
	delete [] pfFFT;

	delete [] pfFFTAvr;

	// удаление потока 
	BASS_StreamFree(hStream);

	if (NULL != pCallBack)
	{
		pCallBack(0, 100, 100);
	}

	return ERROR_SUCCESS;
}