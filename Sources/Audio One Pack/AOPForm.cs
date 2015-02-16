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
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using Microsoft.Win32;
using System.Runtime.InteropServices;

namespace AudioOnePack
{
    //
	public partial class AOPForm : Form
	{
		#region » определение закладок

		TabPage m_tabPageOne;
		TabPage m_tabPageTwo;
		TabPage m_tabPageThree;
		TabPage m_tabPageFour;
		TabPage m_tabPageFive;

		#endregion

		#region » определение форм (ctrlRipCD, ctrlAudioCD, ctrlMusicCD, ctrlConvert)

		/// <summary>
		/// форма граббинга Audio CD.
		/// </summary>
		private RipCDForm m_ctrlRipCD = null;

		/// <summary>
		/// форма записи Audio CD.
		/// </summary>
		private AudioCDForm m_ctrlAudioCD = null;

		/// <summary>
		/// Форма записи Music CD.
		/// </summary>
		private MusicCDForm m_ctrlMusicCD = null;

		/// <summary>
		/// Форма конвертирования музыки.
		/// </summary>
		private ConvertForm m_ctrlConvert = null;

		/// <summary>
		/// Форма анализа музыки.
		/// </summary>
		private AnalyzerForm m_ctrlAnalyzer = null;

		#endregion

		/// <summary>
		/// Значение громкости для восстановления при выходе.
		/// </summary>
		private uint m_uiRestoreVolume = 100;

		/// <summary>
		/// список устройств.
		/// </summary>
		private List<AOPAPI.DEVICEINFO> m_listDevice = new List<AOPAPI.DEVICEINFO>();

		/// <summary>
		/// список информации о дисках в приводах.
		/// </summary>
		private List<AOPAPI.DISCINFO> m_listDiscInfo = new List<AOPAPI.DISCINFO>();

		/// <summary>
		/// список дорожек всех дисков в приводах.
		/// </summary>
		private List<List<AOPAPI.TOCINFO>> m_listAllToc = new List<List<AOPAPI.TOCINFO>>();

		/// <summary>
		/// Список доступных скоростей чтения.
		/// </summary>
		private List<List<String>> m_listReadSpeed = new List<List<String>>();

		/// <summary>
		/// Список доступных скоростей записи.
		/// </summary>
		private List<List<String>> m_listWriteSpeed = new List<List<String>>();

		/// <summary>
		/// Возвращает путь к реестру для хранения настроек.
		/// </summary>
		protected string RegPathSettings
		{
			get
			{
				return "HKEY_CURRENT_USER\\Software\\Whole Group (www.wholegroup.com)\\" + Application.ProductName;
			}

			set { ;}
		}

		#region » общие настройки программы

		/// <summary>
		/// Директория для временных файлов.
		/// </summary>
		private String m_strTempPath = Path.GetTempPath();
		
		/// <summary>
		/// Получение/установка директории для временных файлов.
		/// </summary>
		public string TempPath
		{
			get
			{
				return m_strTempPath;
			}

			set
			{
				m_strTempPath = value.ToString();
			}
		}

		/// <summary>
		/// Номер выбранной закладки
		/// </summary>
		private int m_iTabSelected = 0;

        //
		private bool m_bShowAboutOnStart = true; 

		public bool ShowAboutOnStart
		{
			get
			{
				return m_bShowAboutOnStart;
			}

			set
			{
				m_bShowAboutOnStart = bool.Parse(value.ToString());
			}
		}

		#endregion

		#region » настройки рипинга дисков

		/// <summary>
		/// Кодек для сжатия при грабинге дисков.
		/// </summary>
		private int m_iRipCodec = 1;

		public int iRipCodec
		{
			get
			{
				return m_iRipCodec;
			}

			set
			{
				m_iRipCodec = value;
			}
		}

		/// <summary>
		/// Качество сжатия при грабинге дисков.
		/// </summary>
		private int m_iRipQuality = 2;

		public int iRipQuality 
		{
			get
			{
				return m_iRipQuality;
			}

			set
			{
				m_iRipQuality = value;
			}
		}

		/// <summary>
		/// Флажок для запроса информации с FreeDB.
		/// 0 - не получать после чтения диска
		/// 1 - выдавать запрос на получение
		/// 2 - запрашивать после чтения диска
		/// </summary>
		private int m_iRipGetFreeDB = 1;

		public int iRipGetFreeDB
		{
			get
			{
				return m_iRipGetFreeDB;
			}

			set
			{
				m_iRipGetFreeDB = value;
			}
		}

		/// <summary>
		/// Выходной путь для сграбленных файлов.
		/// </summary>
		private string m_strRipOutPath = "";

		public string strRipOutPath
		{
			get
			{
				return m_strRipOutPath;
			}

			set
			{
				m_strRipOutPath = value.ToString();
			}
		}

		/// <summary>
		/// Сохранять треки в один файл.
		/// </summary>
		private bool m_bRipSingle = false;

		public bool bRipSingle
		{
			get
			{
				return m_bRipSingle;
			}

			set
			{
				m_bRipSingle = (bool)value;
			}
		}

		/// <summary>
		/// Не запрашивать выходной каталог для треков.
		/// </summary>
		private bool m_bRipNotRequestOutput = false;

		public bool bRipNotRequestOutput
		{
			get
			{
				return m_bRipNotRequestOutput;
			}

			set
			{
				m_bRipNotRequestOutput = (bool)value;
			}
		}

		/// <summary>
		/// Извлекать диск после риппинга.
		/// </summary>
		private bool m_bRipEject = true;

		public bool bRipEject
		{
			get
			{
				return m_bRipEject;
			}

			set
			{
				m_bRipEject = (bool)value;
			}
		}

		/// <summary>
		/// Открыть выходной каталог после граббинга.
		/// </summary>
		private bool m_bRipOpenDir = true;

		public bool bRipOpenDir
		{
			get
			{
				return m_bRipOpenDir;
			}

			set
			{
				m_bRipOpenDir = (bool)value;
			}
		}

        //
		public void RipSetDefaultOption()
		{
			m_bRipOpenDir          = true;
			m_bRipEject            = true;
			m_bRipNotRequestOutput = false;
			m_strRipOutPath        = "";
			m_iRipGetFreeDB        = 1;
		}

		#endregion

		#region » настройки записи Audio CD

		/// <summary>
		/// Загружать лоток сразу после eject'a.
		/// </summary>
		private bool m_bAudioCDLoadTray = false;

		public bool bAudioCDLoadTray
		{
			get
			{
				return m_bAudioCDLoadTray;
			}

			set
			{
				m_bAudioCDLoadTray = (bool)value;
			}
		}

        //
		private bool m_bClearListAfterBurn = true;

		public bool bClearListAfterBurn
		{
			get
			{
				return m_bClearListAfterBurn;
			}

			set
			{
				m_bClearListAfterBurn = (bool)value;
			}
		}

		#endregion 

		#region » настройки записи Music CD

		/// <summary>
		/// Загружать лоток сразу после eject'a.
		/// </summary>
		private bool m_bMusicCDLoadTray = false;

		public bool bMusicCDLoadTray
		{
			get
			{
				return m_bMusicCDLoadTray;
			}

			set
			{
				m_bMusicCDLoadTray = (bool)value;
			}
		}

		#endregion

		#region » настройки конвертирования музыки 

		/// <summary>
		/// Кодек для сжатия при конвертировании музыки.
		/// </summary>
		private int m_iConvertCodec = 1;

		public int iConvertCodec
		{
			get
			{
				return m_iConvertCodec;
			}

			set
			{
				m_iConvertCodec = value;
			}
		}

		/// <summary>
		/// Качество сжатия при грабинге дисков.
		/// </summary>
		private int m_iConvertQuality = 2;

		public int iConvertQuality
		{
			get
			{
				return m_iConvertQuality;
			}

			set
			{
				m_iConvertQuality = value;
			}
		}

		/// <summary>
		/// Конвертирование в указанную директорию.
		/// </summary>
		private bool m_bConvertDestinationDir = true;

		public bool bConvertDestinationDir
		{
			get
			{
				return m_bConvertDestinationDir;
			}

			set
			{
				m_bConvertDestinationDir = (bool)value;
			}
		}

		/// <summary>
		/// Выходной путь для сграбленных файлов.
		/// </summary>
		private string m_strConvertOutPath = "";

		public string strConvertOutPath
		{
			get
			{
				return m_strConvertOutPath;
			}

			set
			{
				m_strConvertOutPath = value.ToString();
			}
		}

		/// <summary>
		/// Не запрашивать выходной каталог для треков.
		/// </summary>
		private bool m_bConvertNotRequestOutput = false;

		public bool bConvertNotRequestOutput
		{
			get
			{
				return m_bConvertNotRequestOutput;
			}

			set
			{
				m_bConvertNotRequestOutput = (bool)value;
			}
		}

		/// <summary>
		/// удалять исходный файл, после конвертирования.
		/// </summary>
		private bool m_bConvertDelete = false;

		public bool bConvertDelete
		{
			get
			{
				return m_bConvertDelete;
			}

			set
			{
				m_bConvertDelete = (bool)value;
			}
		}

		#endregion

		/// <summary>
		/// Конструктор.
		/// </summary>
		public AOPForm()
		{
			InitializeComponent();

			Application.ThreadException += new System.Threading.ThreadExceptionEventHandler(ThreadException);
		}

		/// <summary>
		/// Обработка исключений.
		/// </summary>
		void ThreadException(object sender, System.Threading.ThreadExceptionEventArgs e)
		{
			throw (new System.Exception(e.Exception.ToString()));
		}

		/// <summary>
		/// Обработка загрузки формы.
		/// </summary>
		private void LoadForm(object sender, EventArgs e)
		{
			// чтение настроек
			LoadSettings();

			// удаление всех закладок
			tabMain.TabPages.Clear();

			// создание контролов для закладок
			m_ctrlRipCD = new RipCDForm(this);

			m_ctrlRipCD.Dock = DockStyle.Fill;
			m_ctrlRipCD.TopLevel = false;
			m_ctrlRipCD.Show();

            //
			m_ctrlAudioCD = new AudioCDForm(this);

			m_ctrlAudioCD.Dock = DockStyle.Fill;
			m_ctrlAudioCD.TopLevel = false;
			m_ctrlAudioCD.Show();

			//
			m_ctrlMusicCD = new MusicCDForm(this);

			m_ctrlMusicCD.Dock = DockStyle.Fill;
			m_ctrlMusicCD.TopLevel = false;
			m_ctrlMusicCD.Show();

			//
			m_ctrlConvert = new ConvertForm(this);

			m_ctrlConvert.Dock = DockStyle.Fill;
			m_ctrlConvert.TopLevel = false;
			m_ctrlConvert.Show();

			//
			m_ctrlAnalyzer = new AnalyzerForm(this);

			m_ctrlAnalyzer.Dock = DockStyle.Fill;
			m_ctrlAnalyzer.TopLevel = false;
			m_ctrlAnalyzer.Show();

			// создание новых закладок
			m_tabPageOne = new TabPage(Properties.Resources.IDS_TABRIP);
			m_tabPageOne.Controls.Add(m_ctrlRipCD);
			m_tabPageOne.UseVisualStyleBackColor = true;

			//
			m_tabPageTwo = new TabPage(Properties.Resources.IDS_TABAUDIO);
			m_tabPageTwo.Controls.Add(m_ctrlAudioCD);

			//
			m_tabPageThree = new TabPage(Properties.Resources.IDS_TABMUSIC);
			m_tabPageThree.Controls.Add(m_ctrlMusicCD);

			//
			m_tabPageFour = new TabPage(Properties.Resources.IDS_TABCONVERTER);
			m_tabPageFour.Controls.Add(m_ctrlConvert);

			//
			m_tabPageFive = new TabPage(Properties.Resources.IDS_TABANALYZER);
			m_tabPageFive.Controls.Add(m_ctrlAnalyzer);

			// добавление закладок на форму
			m_tabPageOne.ImageIndex = 0;
			tabMain.TabPages.Add(m_tabPageOne);
			tabMain.SelectTab(m_tabPageOne);

			//
			m_tabPageTwo.ImageIndex = 1;
			tabMain.TabPages.Add(m_tabPageTwo);
			tabMain.SelectTab(m_tabPageTwo);

			//
			m_tabPageThree.ImageIndex = 2;
			tabMain.TabPages.Add(m_tabPageThree);
			tabMain.SelectTab(m_tabPageThree);

			m_tabPageFour.ImageIndex = 3;
			tabMain.TabPages.Add(m_tabPageFour);
			tabMain.SelectTab(m_tabPageFour);

			//
			m_tabPageFive.ImageIndex = 4;
			tabMain.TabPages.Add(m_tabPageFive);
			tabMain.SelectTab(m_tabPageFive);

			if (tabMain.TabCount < (m_iTabSelected + 1))
			{
				tabMain.SelectTab(0);
			}
			else
			{
				tabMain.SelectTab(m_iTabSelected);
			}

			TabChanged(null, null);

			// запоминание громкости
			m_uiRestoreVolume = AOPAPI.AOPGetVolume();
		}

		/// <summary>
		/// Обработка закрытия формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void CloseForm(object sender, FormClosedEventArgs e)
		{
			// сохранение настроек
			SaveSettings();

			// восстановление громкости
			AOPAPI.AOPSetVolume(m_uiRestoreVolume);
		}
		
		/// <summary>
		/// Обработка первого вывода формы
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ShowForm(object sender, EventArgs e)
		{
			// загрузка формы поиска CD/DVD
			FindDevice formFindDevice;

			formFindDevice = new FindDevice();
			formFindDevice.Owner = this;
			formFindDevice.ShowDialog();

			// проверка наличия CD/DVD приводов
			if (0 == m_listDevice.Count)
			{
				MessageBox.Show(this, Properties.Resources.IDS_DEVICENOTFOUND, 
                    Properties.Resources.IDS_DEVICENOTFOUND_CAPTION, 
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
			}

			// заполнение списка приводов на закладках
			if (null != m_ctrlRipCD)
			{
				m_ctrlRipCD.FillListDevices();
			}

			if (null != m_ctrlAudioCD)
			{
				m_ctrlAudioCD.FillListDevices();
			}

			if (null != m_ctrlMusicCD)
			{
				m_ctrlMusicCD.FillListDevices();
			}

			if (null != m_ctrlAnalyzer)
			{
				m_ctrlAnalyzer.FillListDevices();
			}

			ScanDisk("");
		}

		/// <summary>
		/// Добавление в список CD/DVD привода.
		/// </summary>
		public void AddDevice(AOPAPI.DEVICEINFO deviceInfo)
		{
			m_listDevice.Add(deviceInfo);
			m_listDiscInfo.Add(new AOPAPI.DISCINFO());
			m_listAllToc.Add(new List<AOPAPI.TOCINFO>());
			m_listReadSpeed.Add(new List<String>());
			m_listWriteSpeed.Add(new List<String>());
		}

		/// <summary>
		/// Возвращает список найденных CD/DVD приводов.
		/// </summary>
		/// <returns></returns>
		public List<AOPAPI.DEVICEINFO> GetListDevices()
		{
			return m_listDevice;
		}

		/// <summary>
		/// Возвращает информацию о дисках.
		/// </summary>
		/// <returns></returns>
		public List<AOPAPI.DISCINFO> GetDiscInfo()
		{
			return m_listDiscInfo;
		}

		/// <summary>
		/// Возвращает всю информацию о дорожках всех дисков.
		/// </summary>
		/// <returns></returns>
		public List<List<AOPAPI.TOCINFO>> GetAllToc()
		{
			return m_listAllToc;
		}

		/// <summary>
		/// Возвращает информацию о доступных скоростях чтения.
		/// </summary>
		/// <returns></returns>
		public List<List<String>> GetReadSpeed()
		{
			return m_listReadSpeed;
		}

		/// <summary>
		/// Возвращает информацию о доступных скоростях записи.
		/// </summary>
		/// <returns></returns>
		public List<List<String>> GetWriteSpeed()
		{
			return m_listWriteSpeed;
		}

		[StructLayout(LayoutKind.Sequential)]
		public struct DEV_BROADCAST_VOLUME
		{
			public int dbcv_size;
			public int dbcv_devicetype;
			public int dbcv_reserved;
			public int dbcv_unitmask;
		}
		
		/// <summary>
		/// Обработка системных событий Windows.
		/// </summary>
		/// <param name="m"></param>
		protected override void WndProc(ref Message m)
		{
			int devType;

			switch (m.Msg)
			{
                // WM_DEVICECHANGE
				case 0x0219: 
					switch ((int)m.WParam)
					{
                        // DBT_DEVICEARRIVAL
						case 0x8000: 
							devType = Marshal.ReadInt32(m.LParam, 4);

                            // DBT_DEVTYP_VOLUME
							if (0x00000002 == devType) 
							{
								DEV_BROADCAST_VOLUME vol = (DEV_BROADCAST_VOLUME)Marshal.PtrToStructure(
                                    m.LParam, typeof(DEV_BROADCAST_VOLUME));

								char cLetter = 'A';
								int  iMask   = vol.dbcv_unitmask;
								
								cLetter--;
								while (0 != iMask)
								{
									cLetter++;

									iMask >>= 1;
								}

								ScanDisk(cLetter.ToString() + ":");
							}

							break;

                        // DBT_DEVICEREMOVECOMPLETE
						case 0x8004: 
							devType = Marshal.ReadInt32(m.LParam, 4);

							if (0x00000002 == devType) // DBT_DEVTYP_VOLUME
							{
								DEV_BROADCAST_VOLUME vol = (DEV_BROADCAST_VOLUME)Marshal.PtrToStructure(
                                    m.LParam, typeof(DEV_BROADCAST_VOLUME));

								char cLetter = 'A';
								int iMask   = vol.dbcv_unitmask;

								cLetter--;
								while (0 != iMask)
								{
									cLetter++;

									iMask >>= 1;
								}

								ScanDisk(cLetter.ToString() + ":");
							}

							break;
					}

					break;
			}

			base.WndProc(ref m);
		}

		/// <summary>
		/// Сканирование диска(ов).
		/// </summary>
		/// <param name="m_strDisk">буква устройства с двоеточием (C:)</param>
		public void ScanDisk(String strDisk)
		{
			// диалог сканирования диска
			ScanDisk formScanDisk;

			formScanDisk       = new ScanDisk(this, strDisk);
			formScanDisk.Owner = this;
			formScanDisk.ShowDialog();

			// заполнение списка аудио треков и скоростей чтения
			if (null != m_ctrlRipCD)
			{
				m_ctrlRipCD.FillNotEmptyListTracks(strDisk);
				m_ctrlRipCD.FillReadSpeeds();
			}

			// заполнение списка скоростей записи
			if (null != m_ctrlAudioCD)
			{
				m_ctrlAudioCD.FillWriteSpeeds();
			}

            //
			if (null != m_ctrlMusicCD)
			{
				m_ctrlMusicCD.FillWriteSpeeds();
			}
		}

		/// <summary>
		/// Чтение настроек программы из реестра.
		/// </summary>
		private void LoadSettings()
		{
			try
			{
				// временная директория
				TempPath = (String)Registry.GetValue(RegPathSettings, "TempPath", "");

				if (false == Directory.Exists(TempPath))
				{
					TempPath = Path.GetTempPath();
				}

				// выбранная закладка
				m_iTabSelected = (int)Registry.GetValue(RegPathSettings, "TabSelected", m_iTabSelected);

				// чтение и установка координат окна
				int iX = (int)Registry.GetValue(RegPathSettings, "LocationX", 0);
				int iY = (int)Registry.GetValue(RegPathSettings, "LocationY", 0);

				if ((Screen.PrimaryScreen.WorkingArea.X <= iX) &&
					(Screen.PrimaryScreen.WorkingArea.Y <= iY) &&
					((Screen.PrimaryScreen.WorkingArea.Right >= (iX + Width))) &&
					(Screen.PrimaryScreen.WorkingArea.Bottom >= (iY + Height)))
				{
					SetDesktopLocation(iX, iY);
				}

				// показывать About при старте
				m_bShowAboutOnStart = bool.Parse((string)Registry.GetValue(RegPathSettings, 
                    "bShowAboutOnStart", m_bShowAboutOnStart.ToString()));

				// настройки Audio CD Ripper
				iRipCodec            = (int)Registry.GetValue(RegPathSettings, "iRipCodec", iRipCodec);
				iRipQuality          = (int)Registry.GetValue(RegPathSettings, "iRipQuality", iRipQuality);
				iRipGetFreeDB        = (int)Registry.GetValue(RegPathSettings, "iRipGetFreeDB", iRipGetFreeDB);
				strRipOutPath        = (string)Registry.GetValue(RegPathSettings, "strRipOutPath", strRipOutPath);
				bRipSingle           = Boolean.Parse((string)Registry.GetValue(RegPathSettings, 
                    "bRipSingle", bRipSingle.ToString()));
				bRipNotRequestOutput = Boolean.Parse((string)Registry.GetValue(RegPathSettings, 
                    "bNotRipRequestOutput", bRipNotRequestOutput.ToString()));
				bRipEject            = Boolean.Parse((string)Registry.GetValue(RegPathSettings, 
                    "bRipEject", bRipEject.ToString()));
				bRipOpenDir          = Boolean.Parse((string)Registry.GetValue(RegPathSettings, 
                    "bRipOpenDir", bRipOpenDir.ToString()));

				if (false == Directory.Exists(strRipOutPath))
				{
					strRipOutPath = "";
				}

				// настройки Audio CD Creator
				bAudioCDLoadTray    = Boolean.Parse((string)Registry.GetValue(RegPathSettings, 
                    "bAudioCDLoadTray", bAudioCDLoadTray.ToString()));
				bClearListAfterBurn = Boolean.Parse((string)Registry.GetValue(RegPathSettings, 
                    "bClearListAfterBurn", bClearListAfterBurn.ToString()));

				// настройки Music CD Creator
				bMusicCDLoadTray = Boolean.Parse((string)Registry.GetValue(RegPathSettings, 
                    "bMusicCDLoadTray", bMusicCDLoadTray.ToString()));

				// настройки Music Converter
				iConvertCodec            = (int)Registry.GetValue(RegPathSettings, "iConvertCodec", iConvertCodec);
				iConvertQuality          = (int)Registry.GetValue(RegPathSettings, "iConvertQuality", iConvertQuality);
				bConvertDestinationDir   = Boolean.Parse((string)Registry.GetValue(RegPathSettings, 
                    "bConvertDestinationDir", bConvertDestinationDir.ToString()));
				bConvertNotRequestOutput = Boolean.Parse((string)Registry.GetValue(RegPathSettings, 
                    "bConvertNotRequestOutput", bConvertNotRequestOutput.ToString()));
				strConvertOutPath        = (string)Registry.GetValue(RegPathSettings, 
                    "strConvertOutPath", strConvertOutPath);
				bConvertDelete           = Boolean.Parse((string)Registry.GetValue(RegPathSettings, 
                    "bConvertDelete", bConvertDelete.ToString()));

				if (false == Directory.Exists(strConvertOutPath))
				{
					strConvertOutPath = "";
				}
			}
			catch (System.Exception)
			{
			}
		}

		/// <summary>
		/// Сохранение настрое в реестре.
		/// </summary>
		private void SaveSettings()
		{
            //
			Registry.SetValue(RegPathSettings, "TempPath", TempPath.ToString());
			Registry.SetValue(RegPathSettings, "TabSelected", tabMain.SelectedIndex);
			Registry.SetValue(RegPathSettings, "LocationX", Location.X);
			Registry.SetValue(RegPathSettings, "LocationY", Location.Y);
			Registry.SetValue(RegPathSettings, "bShowAboutOnStart", m_bShowAboutOnStart);

            //
			Registry.SetValue(RegPathSettings, "iRipCodec", iRipCodec);
			Registry.SetValue(RegPathSettings, "iRipQuality", iRipQuality);
			Registry.SetValue(RegPathSettings, "iRipGetFreeDB", iRipGetFreeDB);
			Registry.SetValue(RegPathSettings, "strRipOutPath", strRipOutPath);
			Registry.SetValue(RegPathSettings, "bRipSingle", bRipSingle);
			Registry.SetValue(RegPathSettings, "bNotRipRequestOutput", bRipNotRequestOutput);
			Registry.SetValue(RegPathSettings, "bRipEject", bRipEject);
			Registry.SetValue(RegPathSettings, "bRipOpenDir", bRipOpenDir);

            //
			Registry.SetValue(RegPathSettings, "bAudioCDLoadTray", bAudioCDLoadTray);
			Registry.SetValue(RegPathSettings, "bClearListAfterBurn", bClearListAfterBurn);

            //
			Registry.SetValue(RegPathSettings, "bMusicCDLoadTray", bMusicCDLoadTray);

            //
			Registry.SetValue(RegPathSettings, "iConvertCodec", iConvertCodec);
			Registry.SetValue(RegPathSettings, "iConvertQuality", iConvertQuality);
			Registry.SetValue(RegPathSettings, "bConvertDestinationDir", bConvertDestinationDir);
			Registry.SetValue(RegPathSettings, "bConvertNotRequestOutput", bConvertNotRequestOutput);
			Registry.SetValue(RegPathSettings, "strConvertOutPath", strConvertOutPath);
			Registry.SetValue(RegPathSettings, "bConvertDelete", bConvertDelete);
		}

		/// <summary>
		/// Обработка смены закладки.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void TabChanged(object sender, EventArgs e)
		{
			// остановка проигрывания звука при смене закладки
			m_ctrlRipCD.Stop(null, null);
			m_ctrlAudioCD.Stop(null, null);
			m_ctrlMusicCD.Stop(null, null);
			m_ctrlConvert.Stop(null, null);
			m_ctrlAnalyzer.Stop(null, null);

			// смена заголовка окна
			if (m_tabPageOne == tabMain.SelectedTab)
			{
				Text = Properties.Resources.IDS_CAPTION_RIP;
			}

			if (m_tabPageTwo == tabMain.SelectedTab)
			{
				Text = Properties.Resources.IDS_CAPTION_AUDIO;
			}

			if (m_tabPageThree == tabMain.SelectedTab)
			{
				Text = Properties.Resources.IDS_CAPTION_MUSIC;
			}

			if (m_tabPageFour == tabMain.SelectedTab)
			{
				Text = Properties.Resources.IDS_CAPTION_CONVERT;
			}

			if (m_tabPageFive == tabMain.SelectedTab)
			{
				Text = Properties.Resources.IDS_CAPTION_ANALYZE;
			}
		}
	}
}

