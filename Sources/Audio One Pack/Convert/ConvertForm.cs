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
using System.Runtime.InteropServices;

namespace AudioOnePack
{
	//
	public partial class ConvertForm : Form
	{
		/// <summary>
		/// Ссылка на главную форму.
		/// </summary>
		AOPForm m_formAOP;

		/// <summary>
		/// Массив кодеков
		/// </summary>
		private String[] m_strCodecs = { "WAV", "MP3", "WMA", "OGG" };

		/// <summary>
		/// Массив форматов для кодирования.
		/// </summary>
		private String[][] m_strOutFormats = {
			new String[] {"Original"},
			new String[] {"Presentation", "Medium", "Good", "Perfect", "The Best"},
			new String[] {"Presentation", "Medium", "Good", "Perfect", "The Best"},
			new String[] {"Presentation", "Medium", "Good", "Perfect", "The Best"}};

		/// <summary>
		/// Структура описания трека.
		/// </summary>
		public struct TRACKITEM
		{
			public string strPath;
			public string strFilename;
			public string strTrackname;
			public float  fStop;
			public string strArtist;
			public string strAlbum;
			public string strTitle;
		};

		/// <summary>
		/// Заключительная позиция проигрывания текущего трека.
		/// </summary>
		private float m_fStopPos;

		/// <summary>
		/// Конструктор по-умолчанию.
		/// </summary>
		public ConvertForm()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Конструктор с передачей ссылки на главную форму.
		/// </summary>
		/// <param name="formAOP"></param>
		public ConvertForm(AOPForm formAOP)
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
			// установка шрифта по-умолчанию
			this.Font = SystemFonts.DefaultFont;

			// заполнение списка форматов
			cbFormat.Items.Clear();

			foreach (String strCodec in m_strCodecs)
			{
				cbFormat.Items.Add(strCodec);
			}

			if (m_formAOP.iConvertCodec < cbFormat.Items.Count)
			{
				cbFormat.SelectedIndex = m_formAOP.iConvertCodec;
			}
			else
			{
				cbFormat.SelectedIndex = 1;
			}

			// заполнение списка качества сжатия
			ChangeFormat(null, null);

			if (m_formAOP.iConvertQuality < cbQuality.Items.Count)
			{
				cbQuality.SelectedIndex = m_formAOP.iConvertQuality;
			}
			else
			{
				ChangeFormat(null, null);
			}

			// установка громкости
			trackVolume.Value = (int)AOPAPI.AOPGetVolume() / 5;
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
		/// Вызов диалога о программе.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void About(object sender, EventArgs e)
		{
			AboutForm formAbout = new AboutForm(m_formAOP);

			formAbout.ShowDialog();
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
		/// Обработка изменения громкости.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ScrollVolume(object sender, EventArgs e)
		{
			AOPAPI.AOPSetVolume((uint)trackVolume.Value * 5);
		}

		/// <summary>
		/// Открытие трека.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void OpenTrack(object sender, EventArgs e)
		{
			// вызов стандартного диалога открытия файлов
			if (DialogResult.OK != dlgAddTrack.ShowDialog())
			{
				return;
			}

			for (int i = 0; i < dlgAddTrack.FileNames.Length; i++)
			{
				// проверка наличия файла
				if (false == File.Exists(dlgAddTrack.FileNames[i]))
				{
					continue;
				}

				// получение очередного расширения файла
				string strExtension = Path.GetExtension(dlgAddTrack.FileNames[i]);

				// обработка playlist от WinAmp
				if (".m3u" == strExtension)
				{
					StreamReader streamIn = new StreamReader(dlgAddTrack.FileNames[i], System.Text.ASCIIEncoding.Default);

					while (false == streamIn.EndOfStream)
					{
						string strLine = streamIn.ReadLine();

						if ((strLine.Length > 0) && ('#' != strLine[0]))
						{
							if (File.Exists(strLine))
							{
								strLine = Path.GetFullPath(strLine);

								AddTrack(strLine);
							}
						}
					}

					streamIn.Close();
				}

				// обработка playlist от WinAmp в кодировке UTF-8
				else if (".m3u8" == strExtension)
				{
					StreamReader streamIn = new StreamReader(dlgAddTrack.FileNames[i]);

					while (false == streamIn.EndOfStream)
					{
						string strLine = streamIn.ReadLine();

						if ((strLine.Length > 0) && ('#' != strLine[0]))
						{
							if (File.Exists(strLine))
							{
								strLine = Path.GetFullPath(strLine);

								AddTrack(strLine);
							}
						}
					}

					streamIn.Close();
				}

				// добавление файла
				else
				{
					AddTrack(dlgAddTrack.FileNames[i]);
				}
			}
		}

		/// <summary>
		/// Добавление трека.
		/// </summary>
		/// <param name="strFilename">Полный путь к файлу</param>
		private void AddTrack(string strFilename)
		{
			// проверка поддержки данного файла
			if (0 == AOPAPI.AOPGetLen(strFilename))
			{
				MessageBox.Show(this, "File '" + strFilename + "' is in wrong format", "Wrong format", 
					MessageBoxButtons.OK, MessageBoxIcon.Warning);

				return;
			}

			// получение тегов файла
			IntPtr ptrArtist = Marshal.AllocHGlobal(400);
			IntPtr ptrAlbum = Marshal.AllocHGlobal(400);
			IntPtr ptrTitle = Marshal.AllocHGlobal(400);

			AOPAPI.AOPGetTags(strFilename, ptrArtist, ptrAlbum, ptrTitle);

			string strArtist = Marshal.PtrToStringUni(ptrArtist).Trim();
			string strAlbum = Marshal.PtrToStringUni(ptrAlbum).Trim();
			string strTitle = Marshal.PtrToStringUni(ptrTitle).Trim();

			// создание экземпляра структуры с информацией о файле
			TRACKITEM itemTrack;

			itemTrack = new TRACKITEM();
			itemTrack.strPath = strFilename;
			itemTrack.strFilename = Path.GetFileName(strFilename); 
			itemTrack.strTrackname = strArtist + " - " + strTitle;
			itemTrack.fStop = AOPAPI.AOPGetLen(strFilename);
			itemTrack.strArtist = strArtist;
			itemTrack.strAlbum = strAlbum;
			itemTrack.strTitle = strTitle;

			// добавление файла в список
			listTrack.Items.Add(string.Format("{0:D02}", listTrack.Items.Count + 1));
			listTrack.Items[listTrack.Items.Count - 1].SubItems.Add(itemTrack.strFilename);
			listTrack.Items[listTrack.Items.Count - 1].SubItems.Add(itemTrack.strTrackname);
			listTrack.Items[listTrack.Items.Count - 1].Tag = itemTrack;

			if (listTrack.Items.Count > 0)
			{
				btnConvert.Enabled = true;
			}
		}
			
		/// <summary>
		/// Удаление выбранного трека.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void RemoveTrack(object sender, EventArgs e)
		{
			ListView.SelectedListViewItemCollection itemsSel = listTrack.SelectedItems;

			foreach (ListViewItem item in itemsSel)
			{
				listTrack.Items.Remove(item);
			}

			if (0 == listTrack.Items.Count)
			{
				btnConvert.Enabled = false;
			}
		}

		/// <summary>
		/// Вызов диалога настроек.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Options(object sender, EventArgs e)
		{
			ConvertOptions form = new ConvertOptions(m_formAOP);

			form.ShowDialog();
		}

		/// <summary>
		/// Обработка смены формата.
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

			if (0 == cbFormat.SelectedIndex)
			{
				cbQuality.SelectedIndex = 0;
			}
			else
			{
				cbQuality.SelectedIndex = 2;
			}
		}

		/// <summary>
		/// Обработка перед закрытием формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ClosingForm(object sender, FormClosingEventArgs e)
		{
			m_formAOP.iConvertCodec = cbFormat.SelectedIndex;
			m_formAOP.iConvertQuality = cbQuality.SelectedIndex;
		}

		/// <summary>
		/// Выделение всех треков.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void SelectAll(object sender, EventArgs e)
		{
			for (int i = 0; i < listTrack.Items.Count; i++)
			{
				listTrack.Items[i].Selected = true;
			}
		}

		/// <summary>
		/// Вставка списка в Clipboard.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void AddClipboard(object sender, EventArgs e)
		{
			string strTextToClipboard = "";

			for (int i = 0; i < listTrack.Items.Count; i++)
			{
				strTextToClipboard += listTrack.Items[i].SubItems[0].Text + ". " + 
					listTrack.Items[i].SubItems[1].Text + " [" + listTrack.Items[i].SubItems[2].Text + "]\r\n";
			}

			strTextToClipboard += "\r\n";
			strTextToClipboard += "Create by Audio One Pack";

			if (strTextToClipboard.Length > 0)
			{
				Clipboard.SetText(strTextToClipboard);
			}
		}

		/// <summary>
		/// Завершение drag'n'drop.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void DragDropTrack(object sender, DragEventArgs e)
		{
			if (e.Data.GetDataPresent(DataFormats.FileDrop))
			{
				string[] strFiles = (string[])e.Data.GetData(DataFormats.FileDrop);

				for (int i = 0; i < strFiles.Length; i++)
				{
					AddTrack(strFiles[i]);
				}
			}
		}

		/// <summary>
		/// Обработка входа в зону listTracks для drag'n'drop.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void DragEnterTrack(object sender, DragEventArgs e)
		{
			if (e.Data.GetDataPresent(DataFormats.FileDrop))
			{
				e.Effect = DragDropEffects.Copy;
			}
			else
			{
				e.Effect = DragDropEffects.None;
			}
		}

		/// <summary>
		/// Проигрывание выбранного трека.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Play(object sender, EventArgs e)
		{
			AOPAPI.AOPStop();

			if (listTrack.SelectedIndices.Count > 0)
			{
				TRACKITEM itemTrack = (TRACKITEM)listTrack.SelectedItems[0].Tag;

				m_fStopPos = itemTrack.fStop;

				trackPos.Value = 0;

				AOPAPI.AOPPlay(itemTrack.strPath);

				timerPos.Start();
			}
		}


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
		/// Снятие выделения со всех треков.
		/// </summary>
		private void DeselectAll()
		{
			ListView.SelectedListViewItemCollection itemsSel = listTrack.SelectedItems;

			foreach (ListViewItem item in itemsSel)
			{
				item.Selected = false;
			}
		}
		
		/// <summary>
		/// Переход на следующий трек.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Next(object sender, EventArgs e)
		{
			// ничего не делать, если треков нет
			if (0 == listTrack.Items.Count)
			{
				return;
			}

			// если выделенного трека нет, выбрать первый, иначе перейти к следующему
			if (0 == listTrack.SelectedIndices.Count)
			{
				listTrack.Items[0].Selected = true;
			}
			else
			{
				if (listTrack.SelectedIndices[0] < (listTrack.Items.Count - 1))
				{
					int iSelect = listTrack.SelectedIndices[0];

					// снятие выделения со всех треков
					DeselectAll();

					// выделение следующего трека
					listTrack.Items[iSelect + 1].Selected = true;

					// проигрывание
					Play(null, null);
				}
			}
		}

		/// <summary>
		/// Возврат на предыдущий трек.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Prev(object sender, EventArgs e)
		{
			// ничего не делать, если треков нет
			if (0 == listTrack.Items.Count)
			{
				return;
			}

			// если выделенного трека нет, выбрать первый, иначе перейти к предыдущему
			if (0 == listTrack.SelectedIndices.Count)
			{
				listTrack.Items[0].Selected = true;
			}
			else
			{
				if (listTrack.SelectedIndices[0] > 0)
				{
					int iSelect = listTrack.SelectedIndices[0];

					// снятие выделения со всех треков
					DeselectAll();

					// выделение предыдущего трека
					listTrack.Items[iSelect - 1].Selected = true;

					// проигрывание
					Play(null, null);
				}
			}
		}

		/// <summary>
		/// Установка текущей позиции проигрываемого трека.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void TimerTickPos(object sender, EventArgs e)
		{
			float fPos = AOPAPI.AOPGetPos();

			if (fPos >= m_fStopPos)
			{
				Stop(null, null);
			}
			else
			{
				int iValue = (int)((trackPos.Maximum - trackPos.Minimum) * (fPos / m_fStopPos));

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
		/// Обработка изменения позиции проигрывания файла.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ScrollPosition(object sender, EventArgs e)
		{
			AOPAPI.AOPPlayPosition((float)trackPos.Value / (trackPos.Maximum - trackPos.Minimum) * m_fStopPos);
		}

		/// <summary>
		/// Запуск конвертирования.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Convert(object sender, EventArgs e)
		{
			ConvertProcess formProcess;

			// вызов диалога выбора каталога
			if (true == m_formAOP.bConvertDestinationDir)
			{
				if (false == m_formAOP.bConvertNotRequestOutput)
				{
					folderBrowser.SelectedPath = m_formAOP.strConvertOutPath;

					if (DialogResult.OK != folderBrowser.ShowDialog())
					{
						return;
					}

					m_formAOP.strConvertOutPath = folderBrowser.SelectedPath;
				}

				formProcess = new ConvertProcess(m_formAOP, this);
			}
			else
			{
				formProcess = new ConvertProcess(m_formAOP, this);
			}

			formProcess.ShowDialog();
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
				// WAV
				case 0: 
					break;

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
		/// Возвращает список файлов для конвертации.
		/// </summary>
		/// <returns></returns>
		public ArrayList GetFileNames()
		{
			ArrayList arrFiles = new ArrayList();

			for (int i = 0; i < listTrack.Items.Count; i++)
			{
				TRACKITEM trackCur = (TRACKITEM)listTrack.Items[i].Tag;

				arrFiles.Add(trackCur.strPath);
			}

			return arrFiles;
		}

		/// <summary>
		/// Возвращает список с информацией о треках для конвертирования.
		/// </summary>
		/// <returns></returns>
		public ArrayList GetTracksInfo()
		{
			ArrayList arrTracks = new ArrayList();

			for (int i = 0; i < listTrack.Items.Count; i++)
			{
				TRACKITEM trackCur = (TRACKITEM)listTrack.Items[i].Tag;

				arrTracks.Add(trackCur);
			}

			return arrTracks;
		}
	}
}