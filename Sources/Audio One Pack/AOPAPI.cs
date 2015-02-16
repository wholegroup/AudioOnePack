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

using System;
using System.Runtime.InteropServices;

namespace AudioOnePack
{
	static public class AOPAPI
	{
		#region Описание общих функций

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern Int32 AOPInit();

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern Int32 AOPFree();

		#endregion

		#region Описание функций работы с медиафайлами

		public enum DecodeEnum : uint { DECODE_STOP = 0, DECODE_POS, DECODE_ERROR };

		public delegate void DecodeCallbackDelegate(Int32 uiAction, Int32 uiParamOne, Int32 uiParamTwo);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPDecode(string strFileNameIn, string strFileNameOut, DecodeCallbackDelegate MyCallback);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPPlay(string strFileName);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPPlayPosition(float fPos);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPStop();

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern float AOPGetPos();

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern float AOPGetLen(string strFileName);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern UInt32 AOPGetVolume();

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPSetVolume(UInt32 uiVolume);
		
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPGetTags(string strFileName, IntPtr ptrArtist, IntPtr ptrAlbum, IntPtr ptrTitle);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPSeconds2Bytes(float fSeconds);

		#endregion

		#region Описанией функций работы с CD/DVD

		[StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Unicode)]
		public struct DEVICEINFO
		{
			[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 3)]
			public string strLetter;
			[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
			public string strName;
			public byte ucPortID;
			public byte ucBusID;
			public byte ucTargetID;
			public byte ucLUN;
		}

		public delegate void FindCallbackDelegate(DEVICEINFO deviceInfo);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall)]
		public static extern UInt32 AOPGetDevices(FindCallbackDelegate MyCallBack);

		[StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Unicode)]
		public struct DISCINFO
		{
			public Int32 iDiscType;
			[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 10)]
			public string strDiscType;
			public Int64 iUsedSpace;
			public Int64 iFreeSpace;
			public byte bIsDiscBlank;
			public byte bIsWritable;
		}

		[StructLayout(LayoutKind.Sequential, Pack = 1)]
		public struct TOCINFO
		{
			public byte ucTrackMode;
			public byte ucSessionNumber;
			public byte ucTrackNumber;
			public Int32 iStartingLBA;
			public Int32 iEndingLBA;
			public UInt32 uiLBSizeInUCHARs;
		}

		public delegate UInt32 TocInfoCallbackDelegate(TOCINFO tocInfo);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPGetDiscInfo(ref DEVICEINFO devInfo, out DISCINFO discInfo, TocInfoCallbackDelegate MyCallBack);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPBlank(ref DEVICEINFO devInfo, byte usFull);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern float AOPGetBlankTime(ref DEVICEINFO devInfo, byte usFull);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPGetReadSpeeds(ref DEVICEINFO devInfo, IntPtr ptrSpeeds);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPGetWriteSpeeds(ref DEVICEINFO devInfo, IntPtr ptrSpeeds);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPLoadTray(ref DEVICEINFO devInfo);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPEjectTray(ref DEVICEINFO devInfo);

		/// <summary>
		/// Проверка наличия чистого CD.
		/// </summary>
		/// <param name="devInfo"></param>
		/// <returns></returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPIsBlankCD(ref DEVICEINFO devInfo);

		/// <summary>
		/// Блокировка привода.
		/// </summary>
		/// <param name="devInfo"></param>
		/// <returns></returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPLock(ref DEVICEINFO devInfo);

		/// <summary>
		/// Разблокировка привода.
		/// </summary>
		/// <param name="devInfo"></param>
		/// <returns></returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPUnLock(ref DEVICEINFO devInfo);

		#endregion
		
		#region Описание функций для работы с Audio CD из библиотеки AOPAPI.DLL

		/// <summary>
		/// Коды для пользовательской callback функции.
		/// </summary>
		public enum AudioEnum : int { AUDIOBURN_WRITE = 0, AUDIOBURN_BUFFER, AUDIORIP_READ };

		/// <summary>
		/// Делегат для пользовательской callback функции прожига Audio CD.
		/// </summary>
		/// <param name="uiAction"></param>
		/// <param name="uiParamOne"></param>
		/// <param name="uiParamTwo"></param>
		public delegate void AudioBurnCallbackDelegate(Int32 uiAction, Int32 uiParamOne, Int32 uiParamTwo);

		/// <summary>
		/// Делегат для пользовательской callback функции граббинга Audio CD.
		/// </summary>
		/// <param name="uiAction"></param>
		/// <param name="uiParamOne"></param>
		/// <param name="uiParamTwo"></param>
		public delegate void AudioRipCallbackDelegate(Int32 uiAction, Int32 uiParamOne, Int32 uiParamTwo);

		/// <summary>
		/// cоздание Audio CD.
		/// </summary>
		/// <param name="devInfo"></param>
		/// <param name="UserCallback"></param>
		/// <returns></returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPAudioCDInit(ref DEVICEINFO devInfo);

		/// <summary>
		/// Освобождение ресурсов занятых при создании Audio CD.
		/// </summary>
		/// <returns>код ошибки, иначе 0</returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPAudioCDFree();

		/// <summary>
		/// Добавление трека.
		/// </summary>
		/// <param name="strPath">полный путь к треку</param>
		/// <returns>код ошибки, иначе 0</returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPAudioCDAddTrack(string strPath);

		/// <summary>
		/// Установка тегов аудио трека.
		/// </summary>
		/// <param name="nTrack">номер трека. 0 - тег диска</param>
		/// <param name="strArtist">имя исполнителя</param>
		/// <param name="strTitle">наименование трека</param>
		/// <returns>код ошибки, иначе 0</returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPAudioCDSetTitle(byte nTrack, string strArtist, string strTitle);

		/// <summary>
		/// Прожиг Audio CD.
		/// </summary>
		/// <returns>код ошибки, иначе 0</returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPAudioCDBurn(AudioBurnCallbackDelegate pUserCallback, Int32 iSpeed);

		/// <summary>
		/// Риппинг Audio CD.
		/// </summary>
		/// <param name="iTrack">номер трека начиная с 1</param>
		/// <param name="strPath">выходной путь с именем файла</param>
		/// <param name="pUserCallback">указатель на callback функцию</param>
		/// <returns></returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPAudioCDRip(Int32 iTrack, string strPath, AudioRipCallbackDelegate pUserCallback, Int32 iSpeed);

		/// <summary>
		/// Отмена операции риппинга.
		/// </summary>
		/// <returns></returns>
		[DllImport("AOPAPI.dll", CallingConvention=CallingConvention.StdCall, CharSet=CharSet.Unicode)]
		public static extern Int32 AOPAudioCDRipCancel();

		/// <summary>
		/// Проигрывание выбранного трека AudioCD.
		/// </summary>
		/// <param name="iDevice"></param>
		/// <param name="iTrack"></param>
		/// <returns></returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPAudioCDPlay(Int32 iDevice, Int32 iTrack);

		/// <summary>
		/// Чтение CD-Text.
		/// </summary>
		/// <param name="iDevice"></param>
		/// <param name="ptrText"></param>
		/// <returns></returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPAudioCDGetText(Int32 iDevice, IntPtr ptrText);

		/// <summary>
		/// Получение CDDB идентификатора для указанного диска.
		/// </summary>
		/// <param name="iDevice"></param>
		/// <param name="ptrCDDB"></param>
		/// <returns></returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPAudioCDGetCDDB(Int32 iDevice, IntPtr ptrCDDB);

		#endregion

		#region Описание функций для работы с Music CD из библиотеки AOPAPI.DLL

		/// <summary>
		/// Коды для пользовательской callback функции.
		/// </summary>
		public enum MusicEnum : int { MUSICBURN_WRITE = 0, MUSICBURN_BUFFER };

		/// <summary>
		/// Делегат для пользовательской callback функции прожига Music CD.
		/// </summary>
		/// <param name="uiAction"></param>
		/// <param name="uiParamOne"></param>
		/// <param name="uiParamTwo"></param>
		public delegate void MusicBurnCallbackDelegate(Int32 uiAction, Int32 uiParamOne, Int32 uiParamTwo);

		/// <summary>
		/// cоздание Music CD.
		/// </summary>
		/// <param name="devInfo"></param>
		/// <param name="UserCallback"></param>
		/// <returns></returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPMusicCDInit(ref DEVICEINFO devInfo);

		/// <summary>
		/// Освобождение ресурсов занятых при создании Music CD.
		/// </summary>
		/// <returns>код ошибки, иначе 0</returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPMusicCDFree();

		/// <summary>
		/// добавление каталога.
		/// </summary>
		/// <param name="strFolder">имя каталога</param>
		/// <returns>код ошибки, иначе 0</returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPMusicCDAddFolder(string strFolder);

		/// <summary>
		/// добавление файла.
		/// </summary>
		/// <param name="strFilePath">полный путь к файлу</param>
		/// <returns>код ошибки, иначе 0</returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPMusicCDAddFile(string strFilePath);

		/// <summary>
		/// подняться на один уровень вверх структуры диска.
		/// </summary>
		/// <returns>код ошибки, иначе 0</returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPMusicCDTreeUp();

		/// <summary>
		/// Прожиг Music CD.
		/// </summary>
		/// <returns>код ошибки, иначе 0</returns>
		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPMusicCDBurn(MusicBurnCallbackDelegate pUserCallback, Int32 iSpeed, string strVolume);

		#endregion 

		#region Описание функций кодирования звука

		/// <summary>
		/// Коды для пользовательской callback функции 
		/// </summary>
		public enum EncodeEnum : int { ENCODE_POS = 0 };

		public delegate void EncodeCallbackDelegate(Int32 uiAction, Int32 uiParamOne, Int32 uiParamTwo);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPEncodeWMA(string strInFile, string strOutFile, string strTitle, string strAuthor, string strAlbumTitle, string strGenre, string strYear, Int32 iBitrate, EncodeCallbackDelegate pUserCallback);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPEncodeMP3(string strInFile, string strOutFile, Int32 iBitrate, EncodeCallbackDelegate pUserCallback);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPEncodeOGG(string strInFile, string strOutFile, string strTitle, string strAuthor, string strAlbumTitle, string strGenre, string strYear, Int32 iBitrate, EncodeCallbackDelegate pUserCallback);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPEncodeWAV(string strInFile, string strOutFile, EncodeCallbackDelegate pUserCallback);

		[DllImport("AOPAPI.dll", CallingConvention=CallingConvention.StdCall, CharSet=CharSet.Unicode)]
		public static extern Int32 AOPEncodeFLAC(string strInFile, string strOutFile, EncodeCallbackDelegate pUserCallback);

		[DllImport("AOPAPI.dll", CallingConvention=CallingConvention.StdCall, CharSet=CharSet.Unicode)]
		public static extern Int32 AOPEncodeAPE(string strInFile, string strOutFile, EncodeCallbackDelegate pUserCallback);

		// [DllImport("AOPAPI.dll", CallingConvention=CallingConvention.StdCall, CharSet=CharSet.Unicode)]
		// public static extern Int32 AOPEncodeTTA(string strInFile, string strOutFile, EncodeCallbackDelegate pUserCallback);

		[DllImport("AOPAPI.dll", CallingConvention=CallingConvention.StdCall, CharSet=CharSet.Unicode)]
		public static extern Int32 AOPEncodeWV(string strInFile, string strOutFile, EncodeCallbackDelegate pUserCallback);
		
		#endregion 

		#region Описание функция анализа музыки

		public delegate void AnalyzeCallbackDelegate(Int32 uiAction, Int32 uiParamOne, Int32 uiParamTwo);

		[DllImport("AOPAPI.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
		public static extern Int32 AOPAnalyzerTrack(string strFile, ref float fK, AnalyzeCallbackDelegate pUserCallback);

		#endregion
	}
}
