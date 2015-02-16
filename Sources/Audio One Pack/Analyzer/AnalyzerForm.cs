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
	public partial class AnalyzerForm : Form
	{
		/// <summary>
		/// Ссылка на главную форму.
		/// </summary>
		AOPForm m_formAOP;

		/// <summary>
		/// Структура описания трека.
		/// </summary>
		public class TRACKITEM
		{
			public string strPath;
			public string strFilename;
			public string strTrackname;
			public float  fStop;
			public float  fK;
			public ListViewItem itemView;
		};

		/// <summary>
		/// Заключительная позиция проигрывания текущего трека.
		/// </summary>
		private float m_fStopPos;
		
		/// <summary>
		/// Конструктор по-умолчанию.
		/// </summary>
		public AnalyzerForm()
		{
			InitializeComponent();
		}
		
		/// <summary>
		/// Конструктор с передачей ссылки на главную форму.
		/// </summary>
		/// <param name="formAOP"></param>
		public AnalyzerForm(AOPForm formAOP)
			: this()
		{
			m_formAOP = formAOP;
		}

		/// <summary>
		/// Загрузка формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void LoadForm(object sender, EventArgs e)
		{
			// установка шрифта по-умолчанию
			this.Font = SystemFonts.DefaultFont;
		}

		/// <summary>
		/// Обработка кнопки Quit.
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

			for (int i = 0; i < listDevice.Count; i++)
			{
				cbDeviceName.Items.Add("(" + listDevice[i].strLetter + ") " + listDevice[i].strName);
			}

			cbDeviceName.SelectedIndex = 0 < listDevice.Count ? 0 : -1;
		}

		/// <summary>
		/// Вызов диалога с информацией о программе.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void About(object sender, EventArgs e)
		{
			AboutForm formAbout = new AboutForm(m_formAOP);

			formAbout.ShowDialog();
		}

		/// <summary>
		/// Вызов диалога с информацией о диске.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void DiscInfo(object sender, EventArgs e)
		{
			if (-1 == cbDeviceName.SelectedIndex)
			{
				return;
			}

			DiscInfoForm formDiskInfo = new DiscInfoForm(GetWorkDevice());

			formDiskInfo.ShowDialog();
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
		/// Добавление новых треков.
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

			// цикл 
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
					StreamReader streamIn = new StreamReader(dlgAddTrack.FileNames[i], 
						System.Text.ASCIIEncoding.Default);

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
				MessageBox.Show(this, String.Format(Properties.Resources.IDS_ANALYZE_WRONGFILE, strFilename), 
					Properties.Resources.IDS_ANALYZE_WRONGFILE_CAPTION, MessageBoxButtons.OK, MessageBoxIcon.Warning);

				return;
			}

			// получение тегов файла
			IntPtr ptrArtist = Marshal.AllocHGlobal(400);
			IntPtr ptrAlbum  = Marshal.AllocHGlobal(400);
			IntPtr ptrTitle  = Marshal.AllocHGlobal(400);

			AOPAPI.AOPGetTags(strFilename, ptrArtist, ptrAlbum, ptrTitle);

			string strArtist = Marshal.PtrToStringUni(ptrArtist).Trim();
			string strAlbum  = Marshal.PtrToStringUni(ptrAlbum).Trim();
			string strTitle  = Marshal.PtrToStringUni(ptrTitle).Trim();

			// создание экземпляра структуры с информацией о файле
			TRACKITEM itemTrack;

			itemTrack = new TRACKITEM();
			itemTrack.strPath = strFilename;
			itemTrack.strFilename = Path.GetFileName(strFilename);
			itemTrack.strTrackname = strArtist + " - " + strTitle;
			itemTrack.fStop = AOPAPI.AOPGetLen(strFilename);
			//itemTrack.strArtist = strArtist;
			//itemTrack.strAlbum = strAlbum;
			//itemTrack.strTitle = strTitle;

			// добавление файла в список
			listTrack.Items.Add(string.Format("{0:D02}", listTrack.Items.Count + 1));
			listTrack.Items[listTrack.Items.Count - 1].SubItems.Add(itemTrack.strFilename);
			listTrack.Items[listTrack.Items.Count - 1].SubItems.Add(itemTrack.strTrackname);
			listTrack.Items[listTrack.Items.Count - 1].SubItems.Add("unknown");
			listTrack.Items[listTrack.Items.Count - 1].Tag = itemTrack;

			itemTrack.itemView = listTrack.Items[listTrack.Items.Count - 1];

			// включение кнопки анализа, при наличии файлов
			if (listTrack.Items.Count > 0)
			{
				btnAnalyze.Enabled = true;
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
				btnAnalyze.Enabled = false;
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
		/// Запуск анализа.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Analyze(object sender, EventArgs e)
		{
			// список треков для анализа
			ArrayList arrTracks = GetTracksInfo(false);

			// запуск процесса анализа
			AnalyzerProcess formProcess = new AnalyzerProcess(m_formAOP, this, arrTracks);

			formProcess.ShowDialog();

			// обновление коэффициентов
			RefreshCoef(arrTracks);
		}

		/// <summary>
		/// Возвращает список с информацией о треках.
		/// </summary>
		/// <returns></returns>
		private ArrayList GetTracksInfo(Boolean bOnlySelected)
		{
			ArrayList arrTracks = new ArrayList();

			if (true == bOnlySelected)
			{
				for (int i = 0; i < listTrack.SelectedItems.Count; i++)
				{
					TRACKITEM trackCur = ((TRACKITEM)listTrack.SelectedItems[i].Tag);
	
					arrTracks.Add(trackCur);
				}
			}
			else
			{
				for (int i = 0; i < listTrack.Items.Count; i++)
				{
					TRACKITEM trackCur = ((TRACKITEM)listTrack.Items[i].Tag);
	
					arrTracks.Add(trackCur);
				}
			}

			return arrTracks;
		}

		/// <summary>
		/// Обновление коэффициентов качества у указанных треков.
		/// </summary>
		/// <param name="arrTracks"></param>
		private void RefreshCoef(ArrayList arrTracks)
		{
			for (int i = 0; i < arrTracks.Count; i++)
			{
				TRACKITEM itemTrack = (TRACKITEM)arrTracks[i];
				ListViewItem itemView = itemTrack.itemView;

				if (itemTrack.fK < 0)
				{
					itemView.SubItems[3].Text = Properties.Resources.IDS_ANALYZE_UNKNOWQUALITY;
				}
				else
				{
					itemView.SubItems[3].Text = String.Format("{0:F0}%", itemTrack.fK * 100);
				}
			}
		}

		/// <summary>
		/// Анализ выбранных треков.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void AnalyzeSelected(object sender, EventArgs e)
		{
			// список треков для анализа
			ArrayList arrTracks = GetTracksInfo(true);

			// запуск процесса анализа
			AnalyzerProcess formProcess = new AnalyzerProcess(m_formAOP, this, arrTracks);

			formProcess.ShowDialog();

			// обновление коэффициентов
			RefreshCoef(arrTracks);
		}

		/// <summary>
		/// Анализ выбранного диска.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void AnalyzeCD(object sender, EventArgs e)
		{
			Boolean bIsAudioCD = false;
			List<List<AOPAPI.TOCINFO>> listAllToc = m_formAOP.GetAllToc();
			List<AOPAPI.DEVICEINFO> listDevices = m_formAOP.GetListDevices();
			
			int iDevice = cbDeviceName.SelectedIndex;

			if (-1 == iDevice)
			{
				return;
			}

			// цикл по всем трекам диска
			for (int i = 0; i < listAllToc[iDevice].Count; i++)
			{
				// проверка на аудиотрек
				if (0 != listAllToc[iDevice][i].ucTrackMode)
				{
					return;
				}

				// добавление трека в список
				AddTrack(listDevices[iDevice].strLetter + "\\\\Track" + String.Format("{0:D02}", i + 1) + ".cda");

				if (false == bIsAudioCD)
				{
					// снятие выделения со всех треков
					listTrack.SelectedItems.Clear();

					bIsAudioCD = true;
				}

				// выделение трека
				listTrack.Items[listTrack.Items.Count - 1].Selected = true;
			}

			// вывод сообщения, если на диске аудио треков не обнаружено
			if (false == bIsAudioCD)
			{
				MessageBox.Show(this, Properties.Resources.IDS_ANALYZE_NOTAUDIOCD);

				return;
			}

			// анализ треков на диске
			AnalyzeSelected(null, null);
		}

		/// <summary>
		/// Выделение всех треков в списке.
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
					listTrack.Items[i].SubItems[1].Text + " [" + listTrack.Items[i].SubItems[2].Text + "] " +
					listTrack.Items[i].SubItems[3].Text + "\r\n";
			}

			strTextToClipboard += "\r\n";
			strTextToClipboard += "Create by Audio One Pack";

			if (strTextToClipboard.Length > 0)
			{
				Clipboard.SetText(strTextToClipboard);
			}
		}
	}
}
