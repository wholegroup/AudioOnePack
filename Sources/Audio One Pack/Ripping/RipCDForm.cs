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
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace AudioOnePack
{
    //
	public partial class RipCDForm : Form
	{
		/// <summary>
		/// Ссылка на главную форму.
		/// </summary>
		private AOPForm m_formAOP;

		/// <summary>
		/// Структура описания трека.
		/// </summary>
		private class TRACKINFO
		{
			public int    iRealTrack;
			public string strArtist;
			public string strTitle;

			public TRACKINFO(int iNewRealTrack)
			{
				iRealTrack = iNewRealTrack;
				strArtist  = "";
				strTitle   = "";
			}
		};

		/// <summary>
		/// Структура описания диска.
		/// </summary>
		private class DISCINFO
		{
			public bool      bFill;
			public ArrayList listTracks;
			public string    strArtist;
			public string    strTitle;
			public string    strGenre;
			public string    strYear;

            //
			public DISCINFO()
			{
				bFill      = false;
				listTracks = new ArrayList();
				strArtist  = "";
				strTitle   = "";
				strGenre   = "";
				strYear    = "";
			}

            //
			public void Clear()
			{
				bFill      = false;
				listTracks = new ArrayList();
				strArtist  = "";
				strTitle   = "";
				strGenre   = "";
				strYear    = "";
			}
		};

		/// <summary>
		/// Выходной путь для файлов.
		/// </summary>
		private String m_strOutDir;

		public String OutDir
		{
			get
			{
				return m_strOutDir;
			}

			set
			{
				m_strOutDir = value.ToString();
			}
		}

		/// <summary>
		/// Реальная выходная директория.
		/// </summary>
		private String m_strRealOutDir;

		public String RealOutDir
		{
			get
			{
				return m_strRealOutDir;
			}

			set
			{
				m_strRealOutDir = value.ToString();
			}
		}

		/// <summary>
		/// Массив кодеков.
		/// </summary>
		private String[] m_strCodecs = { "WAV", "MP3", "WMA", "OGG", "FLAC (lossless)", "APE (lossless)", "WV (lossless)" };

		/// <summary>
		/// Массив форматов для кодирования.
		/// </summary>
		private String[][] m_strOutFormats = { new String[] {"Audio CD"}, 
			new String[] {"Presentation", "Medium", "Good", "Perfect", "The Best"},
			new String[] {"Presentation", "Medium", "Good", "Perfect", "The Best"},
			new String[] {"Presentation", "Medium", "Good", "Perfect", "The Best"},
			new String[] {"Audio CD"},
			new String[] {"Audio CD"},
			new String[] {"Audio CD"}};

		/// <summary>
		/// Жанры.
		/// </summary>
		private String[] m_strGenre = {"", "A Cappella", "Acid", "Acid Jazz", "Acid Punk", "Acoustic", "Alt.Rock", "Alternative", 
			"Ambient", "Anime", "Avantgarde", "Ballad", "Bass", "Beat", "Bebob", "Big Band", "Black Metal", "Bluegrass",
			"Blues", "Booty Bass", "BritPop", "Cabaret", "Celtic", "Chamber Music", "Chanson", "Chorus", "Christian Gangsta",
			"Christian Rap", "Christian Rock", "Classic Rock", "Classical", "Club", "Club-House", "Comedy", "Contemporary", 
			"Country", "Grossover", "Cult", "Dance", "Dance Hall", "Darkwave", "Death Metal", "Disco", "Dream", "Drum & Bass", 
			"Drum Solo", "Duet", "Easy Listening", "Electronic", "Ethnic", "Eurodance", "Euro-House", "Euro-Techno", 
			"Fast-Fusion", "Folk", "Folk/Rock", "Floklore", "Freestyle", "Funk", "Fusion", "Game", "Gangsta Rap",	"Goa",
			"Gospel", "Gothic", "Gothic Rock", "Grundge", "Hard Rock", "Hardcore", "Heavy Metal", "Hip-Hop", "House", 
			"Humour", "Indie", "Industrial", "Instrumental", "Instrumental Pop", "Instrumental Rock", "Jazz", "Jazz+Funk",
			"JPop", "Jungle", "Latin", "Lo-Fi", "Meditative", "Merengue", "Metal", "Musical", "National Folk", 
			"Native American", "Negerpunk", "New Age", "New Wave", "Noise", "Oldies", "Opera", "Other", "Polka", 
			"Polsk Punk", "Pop", "Pop/Funk", "Pop-Folk", "Porn Groove", "Power Ballad", "Pranks", "Primus", 
			"Progressive Rock", "Psychedelic", "Psychedelic Rock", "Punk", "Punk Rock", "R&B", "Rap", "Rave", "Reggae",
			"Retro", "Revival", "Rhythmic Soul", "Rock", "Rock & Roll", "Salsa", "Samba", "Satire", "Showtunes", "Ska",
			"Slow Jam", "Slow Rock", "Sonata", "Soul", "Sound Clip", "Soundtrack", "Sound Clip", "Soundtrack", 
			"Southern Rock", "Space", "Speech", "Swing", "Symphonic Rock", "Symphony", "Synthpop", "Tango", "Techno",
			"Techno-Industrial", "Terror", "Thrash Metal", "Top 40", "Trailer", "Trance", "Tribal", "Trip-Hop",
			"Vocal"};

		/// <summary>
		/// Номер проигрываемого трека.
		/// </summary>
		private int m_iPlayIndex = 0;

		/// <summary>
		/// Номер предыдущего устройства.
		/// </summary>
		private int m_iPrevDevice = -1;

		/// <summary>
		/// Конструктор.
		/// </summary>
		public RipCDForm()
		{
			InitializeComponent();

			listTrack.EmptyText = Properties.Resources.IDS_RIPCD_EMPTYTEXT;
		}

		/// <summary>
		/// Конструктор с передачей ссылки на главную форму.
		/// </summary>
		/// <param name="formAOP"></param>
		public RipCDForm(AOPForm formAOP)
			: this()
		{
			m_formAOP = formAOP;
		}

		/// <summary>
		/// Обработка загрузки формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void LoadForm(object sender, EventArgs e)
		{
			// установка шрифта по умолчанию
			this.Font = SystemFonts.DefaultFont;

			// заполнение списка форматов
			cbFormat.Items.Clear();

			foreach (String strCodec in m_strCodecs)
			{
				cbFormat.Items.Add(strCodec);
			}

			if (m_formAOP.iRipCodec < cbFormat.Items.Count)
			{
				cbFormat.SelectedIndex = m_formAOP.iRipCodec;
			}
			else
			{
				cbFormat.SelectedIndex = 1;
			}

			// заполнение списка качества сжатия
			ChangeFormat(null, null);

			if (m_formAOP.iRipQuality < cbQuality.Items.Count)
			{
				cbQuality.SelectedIndex = m_formAOP.iRipQuality;
			}
			else
			{
				ChangeFormat(null, null);
			}

			// заполнение списк жанров
			cbGenre.Items.Clear();
			for (int i = 0; i < m_strGenre.Length; i++)
			{
				cbGenre.Items.Add(m_strGenre[i]);
			}

			cbGenre.SelectedIndex = 0;

			// установка позиции громкости звука
			trackVolume.Value = (int)AOPAPI.AOPGetVolume() / 5;

			// установка флага - запись в один файл
			cbSingle.Checked =  m_formAOP.bRipSingle;
		}

		/// <summary>
		/// Обработка нажатия кнопки Quit.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Quit(object sender, EventArgs e)
		{
			Application.Exit();
		}

		/// <summary>
		/// Заполнение списка CD/DVD приводов.
		/// </summary>
		public void FillListDevices()
		{
			List<AOPAPI.DEVICEINFO> listDevice = m_formAOP.GetListDevices();

			ArrayList listDiscs = new ArrayList();

			for (int i = 0; i < listDevice.Count; i++)
			{
				cbDeviceName.Items.Add("(" + listDevice[i].strLetter + ") " + listDevice[i].strName);

				listDiscs.Add(new DISCINFO());
			}

			cbDeviceName.Tag = listDiscs;
            cbDeviceName.SelectedIndex = 0 < listDiscs.Count ? 0 : -1;
		}

		/// <summary>
		/// Выбор первого не пустого диска и заполнение его списка треков.
		/// </summary>
		public void FillNotEmptyListTracks(String strDevice)
		{
			// поиск номера устройства по букве
			if (0 < strDevice.Length)
			{
				List<AOPAPI.DEVICEINFO> listDevices = m_formAOP.GetListDevices();

				for (int i = 0; i < listDevices.Count; i++)
				{
					if (listDevices[i].strLetter == strDevice)
					{
						// очистка информации
						((DISCINFO)((ArrayList)cbDeviceName.Tag)[i]).Clear();

						i = listDevices.Count;
					}
				}
			}

			// получение информации о треках
			List<List<AOPAPI.TOCINFO>> listAllToc = m_formAOP.GetAllToc();

			// номер текущенного выбранного устройства
			int iDevice = cbDeviceName.SelectedIndex;

            if (-1 == iDevice)
            {
                return;
            }

			// обнуление информации о текущем диске
			DISCINFO discInfo = (DISCINFO)((ArrayList)cbDeviceName.Tag)[iDevice];

			discInfo.Clear();

			// проверка наличия треков у выбранного диска
			if (0 < listAllToc[iDevice].Count)
			{
				FillListTracks();

				return;
			}
			
			// выбор устройства, где есть диск
			for (int i = 0; i < listAllToc.Count; i++)
			{
				if (0 < listAllToc[i].Count)
				{
					cbDeviceName.SelectedIndex = i;

					return;
				}
			}

			// очистка списка
			FillListTracks();
		}

		/// <summary>
		/// Заполнение списка треков.
		/// </summary>
		public void FillListTracks()
		{
			// остановка проигрывания
			Stop(null, null);

			// получении информации о дисках
			int iDevice = cbDeviceName.SelectedIndex;

			List<List<AOPAPI.TOCINFO>> listAllToc    = m_formAOP.GetAllToc();
			List<AOPAPI.DEVICEINFO>    listDevices   = m_formAOP.GetListDevices();
			List<AOPAPI.DISCINFO>      listDiscInfo  = m_formAOP.GetDiscInfo();
			DISCINFO                   discInfo      = (DISCINFO)((ArrayList)cbDeviceName.Tag)[iDevice];
			ArrayList                  listTrackInfo = discInfo.listTracks;

			// очищаем список треков
			listTrack.Items.Clear();

			// добавляем треки в список
			for (int i = 0; i < listAllToc[iDevice].Count; i++)
			{
				// проверка на аудиотрек
				if (0 != listAllToc[iDevice][i].ucTrackMode)
				{
					continue;
				}

				// расчет старта и длительности трека
				int iStartMin   = (int)(listAllToc[iDevice][i].iStartingLBA / 75.0f / 60.0f);
				int iStartSec   = (int)(listAllToc[iDevice][i].iStartingLBA / 75.0f - iStartMin * 60);
				int iStartFrame = listAllToc[iDevice][i].iStartingLBA % 75;
				int iLength     = listAllToc[iDevice][i].iEndingLBA - listAllToc[iDevice][i].iStartingLBA;
				int iLenMin     = (int)(iLength / 75.0f / 60.0f);
				int iLenSec     = (int)(iLength / 75.0f - iLenMin * 60);
				int iLenFrame   = iLength % 75;

				// добавление нового элемента
				ListViewItem item = listTrack.Items.Add(String.Format("{0:D}.", listTrack.Items.Count + 1));

				// добавление информации к треку
				if (true == discInfo.bFill)
				{
					TRACKINFO trackInfo = (TRACKINFO)discInfo.listTracks[i];

					item.SubItems.Add(trackInfo.strArtist);
					item.SubItems.Add(trackInfo.strTitle);
				}
				else
				{
					item.SubItems.Add(String.Format(Properties.Resources.IDS_RIPCD_ARTIST, listTrackInfo.Count + 1));
					item.SubItems.Add(String.Format(Properties.Resources.IDS_RIPCD_TRACK, listTrackInfo.Count + 1));

					listTrackInfo.Add(new TRACKINFO(i));
				}

				item.SubItems.Add(String.Format("{0:D02}:{1:D02}.{2:D02}", iLenMin, iLenSec, iLenFrame));
				item.SubItems.Add(String.Format("{0:D02}:{1:D02}.{2:D02}", iStartMin, iStartSec, iStartFrame));

				item.Checked = true;
			}

			// установка значений диска
			SetDiskArtist(discInfo.strArtist);
			SetDiskTitle(discInfo.strTitle);
			SetDiskGenre(discInfo.strGenre);
			SetDiskYear(discInfo.strYear);

			if (true == discInfo.bFill)
			{
				return;
			}

			discInfo.bFill = true;

			// получение CD-Text
			GetCDText();

			// получение информации с freedb сервера
			if (listTrack.Items.Count > 0)
			{
				if (1 == m_formAOP.iRipGetFreeDB)
				{
					if (DialogResult.Yes == MessageBox.Show(Properties.Resources.IDS_RIPCD_GETCDDB, 
                        Properties.Resources.IDS_RIPCD_GETCDDB_CAPTION, 
                        MessageBoxButtons.YesNo, MessageBoxIcon.Question))
					{
						GetCDDBInfo();
					}
				}
				else

				if (2 == m_formAOP.iRipGetFreeDB)
				{
					GetCDDBInfo();
				}
			}
		}

		/// <summary>
		/// Проигрывание выбранного трека.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Play(object sender, EventArgs e)
		{
			// выход, если в списке нет треков
			if (listTrack.Items.Count <= 0)
			{
				return;
			}

			// остановка текущего проигрывания
			Stop(null, null);

			if (listTrack.SelectedIndices.Count > 0)
			{
				// запуск нового проигрывания
				int       iDevice      = cbDeviceName.SelectedIndex;
				DISCINFO  discInfo     = (DISCINFO)((ArrayList)cbDeviceName.Tag)[iDevice];
				ArrayList arrTrackInfo = discInfo.listTracks;
				TRACKINFO trackInfo    = (TRACKINFO)arrTrackInfo[listTrack.SelectedIndices[0]];

				m_iPlayIndex = trackInfo.iRealTrack;

				AOPAPI.AOPAudioCDPlay(iDevice, m_iPlayIndex);
			}
			else
			{
				listTrack.SelectedIndices.Add(0);
				
				Play(null, null);
			}

			timerPos.Start();
		}

		/// <summary>
		/// Остановка проигрывания.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		public void Stop(object sender, EventArgs e)
		{
			timerPos.Stop();
			
			AOPAPI.AOPStop();

			trackPos.Value = 0;
		}

		/// <summary>
		/// Переключение на следующий трек
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Next(object sender, EventArgs e)
		{
			// выход, если в списке нет треков
			if (listTrack.Items.Count <= 0)
			{
				return;
			}

			if (listTrack.SelectedIndices.Count > 0)
			{
				int i = listTrack.SelectedIndices[0];

				if ((i + 1) >= listTrack.Items.Count)
				{
					return;
				}

				listTrack.SelectedIndices.Clear();
				listTrack.SelectedIndices.Add(i + 1);
			}
			else
			{
				listTrack.SelectedIndices.Add(0);
			}

			Play(null, null);
		}

		/// <summary>
		/// Возврат к предыдущему треку.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Prev(object sender, EventArgs e)
		{
			// выход, если в списке нет треков
			if (listTrack.Items.Count <= 0)
			{
				return;
			}

			if (listTrack.SelectedIndices.Count > 0)
			{
				int i = listTrack.SelectedIndices[0];

				if (i <= 0)
				{
					return;
				}

				listTrack.SelectedIndices.Add(i - 1);
			}
			else
			{
				listTrack.SelectedIndices.Add(listTrack.Items.Count - 1);
			}

			Play(null, null);
		}

		/// <summary>
		/// Изменение громкости.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ScrollVolume(object sender, EventArgs e)
		{
			AOPAPI.AOPSetVolume((uint)trackVolume.Value * 5);
		}

		/// <summary>
		/// Изменение позиции проигрывания.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ScrollPosition(object sender, EventArgs e)
		{
			if (timerPos.Enabled)
			{
				List<List<AOPAPI.TOCINFO>> listAllToc = m_formAOP.GetAllToc();
				int iDevice = cbDeviceName.SelectedIndex;
				float fLen = (listAllToc[iDevice][m_iPlayIndex].iEndingLBA - 
                    listAllToc[iDevice][m_iPlayIndex].iStartingLBA) / 75.0f;

				AOPAPI.AOPPlayPosition((float)trackPos.Value / (trackPos.Maximum - trackPos.Minimum) * fLen);
			}
		}

		/// <summary>
		/// Обновление позиции проигрывания по таймеру.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void TickPos(object sender, EventArgs e)
		{
			// получение позиции проигрывания
			float fPos = AOPAPI.AOPGetPos();

			// получение длины трека
			List<List<AOPAPI.TOCINFO>> listAllToc = m_formAOP.GetAllToc();
			int iDevice = cbDeviceName.SelectedIndex;
			float fLen = (listAllToc[iDevice][m_iPlayIndex].iEndingLBA - 
                listAllToc[iDevice][m_iPlayIndex].iStartingLBA) / 75.0f;

			// установка позиции
			if (fPos >= fLen)
			{
				Stop(null, null);
			}
			else
			{
				int iValue = (int)((trackPos.Maximum - trackPos.Minimum) * fPos / fLen);

				if (iValue < trackPos.Minimum)
				{
					trackPos.Value = trackPos.Minimum;
				}
				else if (iValue > trackPos.Maximum)
				{
					trackPos.Value = trackPos.Maximum;
				}
				else
				{
					trackPos.Value = iValue;
				}
			}

		}

		/// <summary>
		/// Вызов формы "О программе".
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void About(object sender, EventArgs e)
		{
			AboutForm formAbout = new AboutForm(m_formAOP);

			formAbout.ShowDialog();
		}

		/// <summary>
		/// Обновление информации о диске.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void RefreshInfo(object sender, EventArgs e)
		{
			Stop(null, null);

            if (-1 == cbDeviceName.SelectedIndex)
            {
                return;
            }

            List<AOPAPI.DEVICEINFO> devInfo = m_formAOP.GetListDevices();
            
            m_formAOP.ScanDisk(devInfo[cbDeviceName.SelectedIndex].strLetter);
		}

		/// <summary>
		/// Обработка смены выходного формата.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ChangeFormat(object sender, EventArgs e)
		{
			cbQuality.Items.Clear();

			foreach (String strFormat in m_strOutFormats[cbFormat.SelectedIndex])
			{
				cbQuality.Items.Add(strFormat);
			}

			if (1 == cbQuality.Items.Count)
			{
				cbQuality.SelectedIndex = 0;
			}
			else
			{
				cbQuality.SelectedIndex = 2;
			}
		}

		/// <summary>
		/// Rip диска.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Rip(object sender, EventArgs e)
		{
			// выбор каталога для сохранения музыки
			if (m_formAOP.bRipNotRequestOutput)
			{
				OutDir = m_formAOP.strRipOutPath;
			}
			else
			{
				folderRip.SelectedPath = m_formAOP.strRipOutPath;

				if (DialogResult.OK != folderRip.ShowDialog())
				{
					return;
				}

				m_formAOP.strRipOutPath = OutDir = folderRip.SelectedPath;
			}

			// запуск процесса граббинга
			RipProcess formRipProcess = new RipProcess(m_formAOP, this);

			if (DialogResult.OK == formRipProcess.ShowDialog())
			{
				// открытие папки с грабленными файлами
				if (true == m_formAOP.bRipOpenDir)
				{
					Process.Start(RealOutDir);
				}

				// eject диска и обновление информации
				if (true == m_formAOP.bRipEject)
				{
					AOPAPI.DEVICEINFO devInfo = GetWorkDevice();

					AOPAPI.AOPEjectTray(ref devInfo);

					RefreshInfo(null, null);
				}
			}
		}

		/// <summary>
		/// Возвращает информацию о выбранном CD/DVD устройстве.
		/// </summary>
		/// <returns></returns>
		public AOPAPI.DEVICEINFO GetWorkDevice()
		{
			List<AOPAPI.DEVICEINFO> devInfoList = m_formAOP.GetListDevices();

			return devInfoList[cbDeviceName.SelectedIndex];
		}

		/// <summary>
		/// Возвращает номера треков.
		/// </summary>
		/// <returns></returns>
		public int[] GetTrackIndices()
		{
			int[] listTrackIndices = new int[listTrack.CheckedIndices.Count];

			for (int i = 0; i < listTrackIndices.Length; i++)
			{
				listTrackIndices[i] = listTrack.CheckedIndices[i] + 1;
			}

			return listTrackIndices;
		}

        //
		public int[] GetTrackRealIndices()
		{
			int       iDevice      = cbDeviceName.SelectedIndex;
			DISCINFO  discInfo     = (DISCINFO)((ArrayList)cbDeviceName.Tag)[iDevice];
			ArrayList arrTrackInfo = discInfo.listTracks;

            //
			int[] listTrackIndices = new int[listTrack.CheckedIndices.Count];

			for (int i = 0; i < listTrackIndices.Length; i++)
			{
				listTrackIndices[i] = ((TRACKINFO)arrTrackInfo[listTrack.CheckedIndices[i]]).iRealTrack + 1;
			}

			return listTrackIndices;
		}

		/// <summary>
		/// Обработка переключения checkbox у треков.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void CheckedTrack(object sender, ItemCheckedEventArgs e)
		{
			if (listTrack.CheckedIndices.Count > 0)
			{
				btnStartRip.Enabled = true;
			}
			else
			{
				btnStartRip.Enabled = false;
			}
		}

		/// <summary>
		/// Возвращает true, если запись должна быть в один файл, иначе false.
		/// </summary>
		/// <returns></returns>
		public Boolean GetSingleFile()
		{
			return cbSingle.Checked;
		}

		/// <summary>
		/// Возвращает порядковый номер кодека.
		/// </summary>
		/// <returns></returns>
		public int GetCodec()
		{
			return cbFormat.SelectedIndex;
		}

		/// <summary>
		/// Возвращает коэффициент качества сжатия.
		/// </summary>
		/// <returns></returns>
		public int GetQuality()
		{
			int iReturn = 0;

			switch (cbFormat.SelectedIndex)
			{
				// MP3
				case 1:
					switch (cbQuality.SelectedIndex)
					{
						case 0: // presentation
							iReturn = 96;
							break;

						case 1: // medium
							iReturn = 160;
							break;

						case 2: // good
							iReturn = 192;
							break;

						case 3: // perfect
							iReturn = 256;
							break;

						case 4: // the best 
							iReturn = 320;
							break;
					}
					break;

				// WMA
				case 2:
					switch (cbQuality.SelectedIndex)
					{
						case 0: // presentation
							iReturn = 96000;
							break;

						case 1: // medium
							iReturn = 128000;
							break;

						case 2: // good
							iReturn = 192000;
							break;

						case 3: // perfect
							iReturn = 256000;
							break;

						case 4: // the best 
							iReturn = 320000;
							break;
					}
					break;

				// OGG
				case 3:
					switch (cbQuality.SelectedIndex)
					{
						case 0: // presentation
							iReturn = 96000;
							break;

						case 1: // medium
							iReturn = 128000;
							break;

						case 2: // good
							iReturn = 192000;
							break;

						case 3: // perfect
							iReturn = 256000;
							break;

						case 4: // the best 
							iReturn = 320000;
							break;
					}
					break;
			}

			return iReturn;
		}
		
		/// <summary>
		/// Возвращает наименование исполнителя/группы/название сборника.
		/// </summary>
		/// <returns></returns>
		public String GetDiskArtist()
		{
			if (0 == textArtist.TextLength)
			{
				return Properties.Resources.IDS_RIPCD_UNKNOWARTIST;
			}

			return textArtist.Text;
		}

		/// <summary>
		/// Устанавливает наименование исполнителя/группы/названия сборника.
		/// </summary>
		/// <param name="strArtist"></param>
		public void SetDiskArtist(String strArtist)
		{
			textArtist.Text = strArtist;
		}

		/// <summary>
		/// Возвращает наименование альбома.
		/// </summary>
		/// <returns></returns>
		public String GetDiskTitle()
		{
			if (0 == textTitle.TextLength)
			{
				return Properties.Resources.IDS_RIPCD_UNKNOWTITLE;
			}

			return textTitle.Text;
		}

		/// <summary>
		/// Устанавливает наименование альбома.
		/// </summary>
		/// <param name="strTitle"></param>
		public void SetDiskTitle(String strTitle)
		{
			textTitle.Text = strTitle;
		}

		/// <summary>
		/// Возвращает год диска.
		/// </summary>
		/// <returns></returns>
		public String GetDiskYear()
		{
			if (0 == textYear.TextLength)
			{
				return DateTime.Today.Year.ToString();
			}

			return textYear.Text;
		}

		/// <summary>
		/// Устанавливает год диска.
		/// </summary>
		/// <param name="strYear"></param>
		public void SetDiskYear(String strYear)
		{
			textYear.Text = strYear;
		}

		/// <summary>
		/// Возвращает жанр диска.
		/// </summary>
		/// <returns></returns>
		public String GetDiskGenre()
		{
			return m_strGenre[cbGenre.SelectedIndex];
		}

		/// <summary>
		/// Устанавливает жанр диска.
		/// </summary>
		/// <param name="strGenre"></param>
		public void SetDiskGenre(String strGenre)
		{
			for (int i = 0; i < m_strGenre.Length; i++)
			{
				if (m_strGenre[i].ToUpper() == strGenre.ToUpper())
				{
					cbGenre.SelectedIndex = i;

					break;
				}
			}
		}

		/// <summary>
		/// Возвращает наименование треков диска.
		/// </summary>
		public ArrayList[] GetDiskNameTracks()
		{
			ArrayList[] arrNameTracks = new ArrayList[2] { new ArrayList(), new ArrayList()};

			foreach (ListViewItem item in listTrack.Items)
			{
				arrNameTracks[0].Add(item.SubItems[1].Text);
				arrNameTracks[1].Add(item.SubItems[2].Text);
			}

			return arrNameTracks;
		}

		/// <summary>
		/// Устанавливает наименования треков.
		/// </summary>
		/// <param name="strArtist"></param>
		/// <param name="arrTracks"></param>
		public void SetDiskNameTracks(ArrayList arrArtistTracks, ArrayList arrTitleTracks)
		{
			foreach (ListViewItem item in listTrack.Items)
			{
				if (item.Index < arrArtistTracks.Count)
				{
					item.SubItems[1].Text = arrArtistTracks[item.Index].ToString(); ;
					item.SubItems[2].Text = arrTitleTracks[item.Index].ToString();
				}
			}
		}

		/// <summary>
		/// Установка наименования указанного трека.
		/// </summary>
		/// <param name="iTrack"></param>
		/// <param name="strArtist"></param>
		/// <param name="strTitle"></param>
		public void SetDiskNameTrack(int iTrack, String strArtist, String strTitle)
		{
			if (iTrack < listTrack.Items.Count)
			{
				listTrack.Items[iTrack].SubItems[1].Text = strArtist;
				listTrack.Items[iTrack].SubItems[2].Text = strTitle;
			}
		}

		/// <summary>
		/// Получение информации о диске с freeDB сервера.
		/// </summary>
		private void GetCDDBInfo()
		{
			String strCDDB;
			IntPtr ptrCDDB;

			// выделение памяти
			ptrCDDB = Marshal.AllocHGlobal(1000);

			// обнуление первого байта (чтобы строка пустая была)
			Marshal.WriteInt16(ptrCDDB, 0);

			// получение указателя на текст
			AOPAPI.AOPAudioCDGetCDDB(cbDeviceName.SelectedIndex, ptrCDDB);

			// получение строки
			strCDDB = Marshal.PtrToStringUni(ptrCDDB);
			strCDDB = strCDDB.Replace(' ', '+');

			// освобождение памяти
			Marshal.FreeHGlobal(ptrCDDB);

			// вызов диалога получения информации CDDB
			RipFreeDb formFreeDb = new RipFreeDb(m_formAOP, this, strCDDB);

			formFreeDb.ShowDialog();
		}

		/// <summary>
		/// Обработка открытия меню.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void OpenMenu(object sender, EventArgs e)
		{
			menuRip.Items[6].Text = Properties.Resources.IDS_RIPCD_MENU_SELECT;
			menuRip.Items[6].Image = global::AudioOnePack.Properties.Resources.add;

			if (listTrack.SelectedItems.Count > 0)
			{
				if (listTrack.SelectedItems[0].Checked)
				{
					menuRip.Items[6].Text = Properties.Resources.IDS_RIPCD_MENU_UNSELECT;
					menuRip.Items[6].Image = global::AudioOnePack.Properties.Resources.del;
				}
			}

			menuRip.Items[7].Text = Properties.Resources.IDS_RIPCD_MENU_UNSELECTALL;

			foreach (ListViewItem item in listTrack.Items)
			{
				if (false == item.Checked)
				{
					menuRip.Items[7].Text = Properties.Resources.IDS_RIPCD_MENU_SELECTALL;

					break;
				}
			}
		}

		/// <summary>
		/// Скопировать список в clipboard.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ListToClipboard(object sender, EventArgs e)
		{
			string strTextToClipboard = "";

			strTextToClipboard += "Artist: " + textArtist.Text + "\r\n";
			strTextToClipboard += "Title : " + textTitle.Text + "\r\n";
			strTextToClipboard += "Year  : " + textYear.Text + "\r\n";
			strTextToClipboard += "Genre : " + m_strGenre[cbGenre.SelectedIndex] + "\r\n";
			strTextToClipboard += "\r\n";

			for (int i = 0; i < listTrack.Items.Count; i++)
			{
				strTextToClipboard += String.Format("{0:D02}. ", i + 1) + 
                    listTrack.Items[i].SubItems[1].Text + " - " + 
                    listTrack.Items[i].SubItems[2].Text + "\r\n";
			}

			strTextToClipboard += "\r\n";
			strTextToClipboard += "Create by Audio One Pack";

			Clipboard.SetText(strTextToClipboard);
		}

		/// <summary>
		/// Поставить/снять галку у выбранного трека.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void SelectTrack(object sender, EventArgs e)
		{
			if (listTrack.SelectedItems.Count > 0)
			{
				listTrack.SelectedItems[0].Checked = listTrack.SelectedItems[0].Checked ? false : true;
			}
		}

		/// <summary>
		/// Поставить/снять галки у всех треков.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void SelectAllTracks(object sender, EventArgs e)
		{
			Boolean bUnselect = true;

            //
			foreach (ListViewItem item in listTrack.Items)
			{
				if (false == item.Checked)
				{
					bUnselect = false;

					break;
				}
			}

            //
			foreach (ListViewItem item in listTrack.Items)
			{
				if (bUnselect)
				{
					item.Checked = false;
				}
				else
				{
					item.Checked = true;
				}
			}
		}

		/// <summary>
		/// Редактирование наименования трека.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void EditTitleTrack(object sender, EventArgs e)
		{
			if (listTrack.SelectedItems.Count > 0)
			{
				RipEditTrack formEdit = new RipEditTrack(this, listTrack.SelectedIndices[0], 
                    listTrack.SelectedItems[0].SubItems[1].Text, 
                    listTrack.SelectedItems[0].SubItems[2].Text);

				formEdit.ShowDialog();
			}
		}

		/// <summary>
		/// Вызов диалога настроек.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Options(object sender, EventArgs e)
		{
			RipOptions formOptions = new RipOptions(m_formAOP);

			formOptions.ShowDialog();
		}

		/// <summary>
		/// Возвращает длину трека в фреймах.
		/// </summary>
		/// <returns></returns>
		public ArrayList GetLengthTracksInFrames()
		{
			ArrayList                  listLengths = new ArrayList();
			List<List<AOPAPI.TOCINFO>> listAllToc  = m_formAOP.GetAllToc();

			int iDevice = cbDeviceName.SelectedIndex;

			foreach (AOPAPI.TOCINFO tocInfo in listAllToc[iDevice])
			{
				listLengths.Add(tocInfo.iEndingLBA - tocInfo.iStartingLBA);
			}

			return listLengths;
		}

		/// <summary>
		/// Обработка после закрытия формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void CloseForm(object sender, FormClosedEventArgs e)
		{
		}

		/// <summary>
		/// Обработка перед закрытием формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ClosingForm(object sender, FormClosingEventArgs e)
		{
			m_formAOP.iRipCodec   = cbFormat.SelectedIndex;
			m_formAOP.iRipQuality = cbQuality.SelectedIndex;
			m_formAOP.bRipSingle  = cbSingle.Checked;
		}

		/// <summary>
		/// Синхронизация громкости.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void VisibleForm(object sender, EventArgs e)
		{
			trackVolume.Value = (int)AOPAPI.AOPGetVolume() / 5;
		}

		/// <summary>
		/// Обработка смены привода.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ChangeDevice(object sender, EventArgs e)
		{
			// выход, если это инициализация списка устройств
			if (0 > m_iPrevDevice)
			{
				m_iPrevDevice = cbDeviceName.SelectedIndex;

				return;
			}

			// запоминаем значения полей
			DISCINFO discInfo = (DISCINFO)(((ArrayList)cbDeviceName.Tag)[m_iPrevDevice]);

			discInfo.strArtist = textArtist.Text;
			discInfo.strTitle  = textTitle.Text;
			discInfo.strGenre  = cbGenre.SelectedItem.ToString();
			discInfo.strYear   = textYear.Text;

			if (true == discInfo.bFill)
			{
				for (int i = 0; i < discInfo.listTracks.Count; i++)
				{
					TRACKINFO trackInfo = (TRACKINFO)discInfo.listTracks[i];

					trackInfo.strArtist = listTrack.Items[i].SubItems[1].Text;
					trackInfo.strTitle  = listTrack.Items[i].SubItems[2].Text; ;
				}
			}

			// обновляем список треков
			FillListTracks();

			// обновляем список скоростей чтения
			FillReadSpeeds();

			// запоминаем выбранный индекс устройства
			m_iPrevDevice = cbDeviceName.SelectedIndex;
		}

		/// <summary>
		/// Заполнение выпадающего списка скоростями записи.
		/// </summary>
		public void FillReadSpeeds()
		{
			cbSpeeds.Items.Clear();

			List<List<String>> listReadSpeed = m_formAOP.GetReadSpeed();

			int iDevice = cbDeviceName.SelectedIndex;

            if (-1 == iDevice)
            {
                return;
            }

			for (int i = 0; i < listReadSpeed[iDevice].Count; i++)
			{
				cbSpeeds.Items.Add(listReadSpeed[iDevice][i]);
			}

			cbSpeeds.SelectedIndex = cbSpeeds.Items.Count - 1;
		}

		/// <summary>
		/// Возвращает индекс скорости чтения.
		/// </summary>
		/// <returns></returns>
		public int GetReadSpeed()
		{
			return cbSpeeds.SelectedIndex;
		}

		/// <summary>
		/// Получение CDDB информации.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void GetCDDBInfo(object sender, EventArgs e)
		{
			GetCDDBInfo();
		}

		/// <summary>
		/// Обработка нажатия клавиш в списке треков.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void KeyPressTrack(object sender, KeyPressEventArgs e)
		{
			if ((char)Keys.Return == e.KeyChar)
			{
				EditTitleTrack(null, null);
			}
		}

		/// <summary>
		/// Чтение CD-Text.
		/// </summary>
		private void GetCDText()
		{
			String strText;
			IntPtr ptrText; 
			
			// выделение памяти
			ptrText = Marshal.AllocHGlobal(20000);

			// обнуление первого байта (чтобы строка пустая была)
			Marshal.WriteInt16(ptrText, 0);

			// получение указателя на текст
			AOPAPI.AOPAudioCDGetText(cbDeviceName.SelectedIndex, ptrText);

			// получение строки
			strText = Marshal.PtrToStringUni(ptrText);

			// освобождение памяти
			Marshal.FreeHGlobal(ptrText);

			// парсим текст
			if (0 < strText.Length)
			{
				string[] split = strText.Split(new char[] { '\n' });

				for (int i = 0; i < split.Length; i++)
				{
					string[] strParam = split[i].Split(new char[] {'='});

					if ((2 == strParam.Length) && (0 < strParam[0].Length) && (0 < strParam[1].Length))
					{
						// исполнитель диска
						if ("PERFORMER0" == strParam[0])
						{
							textArtist.Text = strParam[1];
						}
						else

						// название диска
						if ("TITLE0" == strParam[0])
						{
							textTitle.Text = strParam[1];
						}
						else

						// исполнитель трека
						if (0 == strParam[0].LastIndexOf("PERFORMER"))
						{
							strParam[0] = strParam[0].Replace("PERFORMER", "");

							int iTrack;

							if (true == int.TryParse(strParam[0], out iTrack))
							{
								if ((1 <= iTrack) && (listTrack.Items.Count >= iTrack))
								{
									listTrack.Items[iTrack - 1].SubItems[1].Text = strParam[1];
								}
							}
						}
						else

						// название трека
						if (0 == strParam[0].LastIndexOf("TITLE"))
						{
							strParam[0] = strParam[0].Replace("TITLE", "");

							int iTrack;

							if (true == int.TryParse(strParam[0], out iTrack))
							{
								if ((1 <= iTrack) && (listTrack.Items.Count >= iTrack))
								{
									listTrack.Items[iTrack - 1].SubItems[2].Text = strParam[1];
								}
							}
						}
					}
				}
			}
		}
	}
}