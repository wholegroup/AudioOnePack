#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <wchar.h>
#include <stdio.h>
#include <math.h>
#include "../bass24/c/bass.h"

// определение типа Callback функции для анализа трека
typedef VOID (CALLBACK *PANALYZECALLBACK)(__int32 iAction, __int32 iParamOne, __int32 iParamTwo);

//////////////////////////////////////////////////////////////////////////
// Вывод справки на экран
//
//////////////////////////////////////////////////////////////////////////
VOID PrintHelp()
{
	printf("\nSound Analyzer Console v1.0\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

	printf("Usage: Analyzing.exe [commands] file/directory\n\n");

	printf("Command:\n");
	printf("\t-l\t read filelist with full path to sound files\n");
	printf("\t-r\t recursive read directory\n");

	printf("\nCopyright (c) 2007 Whole Group (http://www.wholegroup.com). All rights reserved.\n");

	return;
}

//////////////////////////////////////////////////////////////////////////
// Callback функция анализа трека
//
// iAction   - код сообщения
// iParamOne - количество проанализированных у.е. 
// iParamTwo - максимальное количество у.е. = 100%
//
//////////////////////////////////////////////////////////////////////////
VOID __stdcall AnalyzeCallback(__int32 iAction, __int32 iParamOne, __int32 iParamTwo)
{
	printf("Sound analysis: [%d%%]\r", iParamOne);
}

//////////////////////////////////////////////////////////////////////////
// Анализ трека
//
//	pwcFile   - полный путь к файлу
// pfK       - вычисленный в функции коэффициент
// pCallBack - указатель на Callback функцию
// 
//////////////////////////////////////////////////////////////////////////
__int32 AnalyzerTrack(PWCHAR pwcFile, PFLOAT pfK, PANALYZECALLBACK pCallBack)
{
	HSTREAM hStream;
	PFLOAT  pfFFT;
	PFLOAT  pfFFTAvr;

	// 0%
	if (NULL != AnalyzeCallback)
	{
		AnalyzeCallback(0, 0, 100);
	}

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

	/*
	INT iCut = 0;

	for (iCut = 0 ; iCut < 2048; iCut++)
	{
		if (0 == pfFFTAvr[iCut])
		{
			pfFFTAvr[iCut] = -100;
		}
		else
		{
			pfFFTAvr[iCut] = 20.0f * log10f(pfFFTAvr[iCut] / fMax);
		}

		if (pfFFTAvr[iCut] < -80.f)
		{
			break;
		}

		if (NULL != pCallBack)
		{
			pCallBack(0, (__int32)(90 + 10 * (iCut / 2048.0f)), 100);
		}
	}

	// вычисление граничной частоты
	*pfK = 22050.0f * (iCut + 1) / 2048.0f;
	*/

	/*
	*pfK = 0;
	for (int i = 0; i < (int)(2048.f * 19500.0f / 22050.f); i++)
	{
		if (0 == pfFFTAvr[i])
		{
			pfFFTAvr[i] = -100;
		}
		else
		{
			pfFFTAvr[i] = 20.0f * log10f(pfFFTAvr[i] / fMax);
		}

		if (*pfK > pfFFTAvr[i])
		{
			*pfK = pfFFTAvr[i];
		}
	}
	*/

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

//
int wmain(int iArgC, WCHAR* pwcArgv[])
{
	// проверка версии
	if (BASSVERSION != HIWORD(BASS_GetVersion()))
	{
		wprintf(L"An incorrect version of BASS.DLL was loaded\n");

		return ERROR_ACCESS_DENIED;
	}

	// инициализация
	if (FALSE == BASS_Init(-1, 44100, 0, 0, NULL))
	{
		wprintf(L"Can't initialize sound device\n");

		return ERROR_ACCESS_DENIED;
	}

	// загрузка плагинов
	if (0 == BASS_PluginLoad((char*)L"bass_aac.dll", BASS_UNICODE))
	{
		wprintf(L"Error loading bass_aac.dll\n");

		return ERROR_OPEN_FAILED;
	}

	/*
	if (0 == BASS_PluginLoad((char*)L"bass_aach.dll", BASS_UNICODE))
	{
		wprintf(L"Error loading bass_aach.dll\n");

		return ERROR_OPEN_FAILED;
	}
	*/

	if (0 == BASS_PluginLoad((char*)L"bass_ac3.dll", BASS_UNICODE))
	{
		wprintf(L"Error loading bass_ac3.dll\n");

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"bass_alac.dll", BASS_UNICODE))
	{
		wprintf(L"Error loading bass_alac.dll\n");

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"bass_ape.dll", BASS_UNICODE))
	{
		wprintf(L"Error loading bass_ape.dll\n");

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"bass_mpc.dll", BASS_UNICODE))
	{
		wprintf(L"Error loading bass_mpc.dll\n");

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"bass_ofr.dll", BASS_UNICODE))
	{
		wprintf(L"Error loading bass_ofr.dll\n");

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"bass_spx.dll", BASS_UNICODE))
	{
		wprintf(L"Error loading bass_spx.dll\n");

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"bass_tta.dll", BASS_UNICODE))
	{
		wprintf(L"Error loading bass_tta.dll\n");

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"basswv.dll", BASS_UNICODE))
	{
		wprintf(L"Error loading basswv.dll\n");

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"basscd.dll", BASS_UNICODE))
	{
		wprintf(L"Error loading basscd.dll\n");

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"bassflac.dll", BASS_UNICODE))
	{
		wprintf(L"Error loading bassflac.dll\n");

		return ERROR_OPEN_FAILED;
	}

	if (0 == BASS_PluginLoad((char*)L"basswma.dll", BASS_UNICODE))
	{
		wprintf(L"Error loading basswma.dll\n");

		return ERROR_OPEN_FAILED;
	}

	__try
	{
		if (1 == iArgC)
		{
			PrintHelp();

			__leave;
		}

		if (0 == wcscmp(pwcArgv[1], L"-l"))
		{
			FLOAT fK     = 0;
			FLOAT fKAvr  = 0;
			FLOAT fMax   = -100;
			INT   iCount = 0;
			FILE* fList;
			WCHAR pwcStr[MAX_PATH];
			CHAR  pcStr[MAX_PATH];

			fList = _wfopen(pwcArgv[2], L"rt+");
			if (NULL == fList)
			{
				printf("ERROR open filelist\n");

				__leave;
			}

			ZeroMemory(pwcStr, MAX_PATH);
			ZeroMemory(pcStr, MAX_PATH);

			while (fgets(pcStr, MAX_PATH, fList))
			{
				// формирование пути к файлу
				wsprintf(pwcStr, L"%S", pcStr);
				if (10 == pwcStr[wcslen(pwcStr) - 1])
				{
					pwcStr[wcslen(pwcStr) - 1] = 0;
				}

				// вывод имени файла
				INT iLenStr = (INT)wcslen(pwcStr);

				while ((iLenStr > 0) && ('\\' != pwcStr[iLenStr - 1]))
				{
					iLenStr--;
				}

				if (iLenStr > 0)
				{
					wprintf(L"File: %s\n", &pwcStr[iLenStr]);
				}
				else
				{
					wprintf(L"File: %s\n", pwcStr);
				}

				// обработка
				if (AnalyzerTrack(pwcStr, &fK, (PANALYZECALLBACK)AnalyzeCallback))
				{
					wprintf(L"ERROR::AnalyzerTrack\n");
				}
				else
				{
					wprintf(L"\nK: %.0f\n", fK);

					fKAvr += fK;

					if (fK > fMax)
					{
						fMax = fK;
					}

					iCount++;
				}
				wprintf(L"\n");

				ZeroMemory(pwcStr, MAX_PATH);
				ZeroMemory(pcStr, MAX_PATH);
			}

			fclose(fList);

			wprintf(L"fAvr = %.f\n", fKAvr / iCount);
			wprintf(L"fMax = %.f\n", fMax);
		}
		else

		if (0 == wcscmp(pwcArgv[1], L"-r"))
		{
			printf("the features hasn't been realised yet.\n");
		}

		else
		{
			FLOAT fK = 0;

			if (AnalyzerTrack(pwcArgv[1], &fK, (PANALYZECALLBACK)AnalyzeCallback))
			{
				wprintf(L"ERROR::AnalyzerTrack\n");
			}
			else
			{
				wprintf(L"\nCD Quality = %.0f%%\n", fK * 100);
			}

		}
	}

	__finally
	{
		BASS_PluginFree(0);
		BASS_Free();
	}

	return 0;
}

