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
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;
using System.Drawing.Drawing2D;

using CueSharp;

namespace AudioOnePack
{
	/// <summary>
	/// Основная форма.
	/// </summary>
	public partial class AudioCDForm : Form
	{
		/// <summary>
		/// Ссылка на главную форму.
		/// </summary>
		private AOPForm m_formAOP;
		
		/// <summary>
		/// Структура описания трека.
		/// </summary>
		public struct TRACKITEM
		{
			public string strFilename;
			public float  fStart;
			public float  fStop;
			public Int32  iStart;
			public Int32  iStop;
			public bool   bCue;
		};

        /// <summary>
		/// Номер последнего выбранного трека для drag'n'drop.
		/// </summary>
		private int m_uiLastIndex;

        /// <summary>
        /// Координаты мыши при открытии контекстного меню.
        /// </summary>
        private Point m_ptnMouseMenu;
		
		/// <summary>
		/// Начальная позиция проигрывания текущего трека.
		/// </summary>
		private float m_fStartPos;

		/// <summary>
		/// Заключительная позиция проигрывания текущего трека.
		/// </summary>
		private float m_fStopPos;

		/// <summary>
		/// Конструктор по-умолчанию.
		/// </summary>
		public AudioCDForm()
		{
			InitializeComponent();

			listTrack.EmptyText = Properties.Resources.IDS_AUDIOCD_EMPTYTEXT;
		}

		/// <summary>
		/// Конструктор с передачей ссылки на основную форму.
		/// </summary>
		public AudioCDForm(AOPForm formAOP)
			: this ()
		{
			m_formAOP = formAOP;
		}

		/// <summary>
		/// Завершение работы приложения.
		/// </summary>
		private void Quit(object sender, EventArgs e)
		{
			Application.Exit();
		}

		/// <summary>
		/// Вызов диалога о программе.
		/// </summary>
		private void About(object sender, EventArgs e)
		{
			AboutForm formAbout = new AboutForm(m_formAOP);

			formAbout.ShowDialog();
		}

		/// <summary>
		/// Открытие трека.
		/// </summary>
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

				// проверка максимального количества треков = 100 штук
				if (100 == listTrack.Items.Count)
				{
					MessageBox.Show(String.Format(Properties.Resources.IDS_AUDIOCD_UNABLEADD, 
                        dlgAddTrack.FileNames[i]), Properties.Resources.IDS_AUDIOCD_UNABLEADD_CAPTION, 
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);

					break;
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

				// обработка CUE 
				else if (".cue" == strExtension)
				{
					CueSheet cue = new CueSheet(dlgAddTrack.FileNames[i]);

					if (cue.Tracks.Length > 0)
					{
						if (File.Exists(cue.Tracks[0].DataFile.Filename))
						{
							// пукт к медиафайлу 
							string strFile = Path.GetFullPath(cue.Tracks[0].DataFile.Filename);

							// обработка треков
							for (int iTrack = 0; iTrack < cue.Tracks.Length; iTrack++)
							{
								float fStart = cue.Tracks[iTrack][cue.Tracks[iTrack].Indices.Length - 1].Minutes * 60 + 
                                    cue.Tracks[iTrack][cue.Tracks[iTrack].Indices.Length - 1].Seconds + 
                                    (float)(cue.Tracks[iTrack][cue.Tracks[iTrack].Indices.Length - 1].Frames) / 75;
								float fStop;
								Int32 iStart = ((cue.Tracks[iTrack][cue.Tracks[iTrack].Indices.Length - 1].Minutes * 60 + 
                                    cue.Tracks[iTrack][cue.Tracks[iTrack].Indices.Length - 1].Seconds) * 75 + 
                                    (cue.Tracks[iTrack][cue.Tracks[iTrack].Indices.Length - 1].Frames)) * 2352;
								Int32 iStop;

								if ((iTrack) + 1 == cue.Tracks.Length)
								{
									fStop = AOPAPI.AOPGetLen(strFile);
									iStop = (Int32)((fStop + 1) * 176400);
								}
								else
								{
									fStop = cue.Tracks[iTrack + 1][cue.Tracks[iTrack + 1].Indices.Length - 1].Minutes * 60 + 
                                        cue.Tracks[iTrack + 1][cue.Tracks[iTrack + 1].Indices.Length - 1].Seconds + 
                                        (float)(cue.Tracks[iTrack + 1][cue.Tracks[iTrack + 1].Indices.Length - 1].Frames) / 75;
									iStop = ((cue.Tracks[iTrack + 1][cue.Tracks[iTrack + 1].Indices.Length - 1].Minutes * 60 + 
                                        cue.Tracks[iTrack + 1][cue.Tracks[iTrack + 1].Indices.Length - 1].Seconds) * 75 + 
                                        (cue.Tracks[iTrack + 1][cue.Tracks[iTrack + 1].Indices.Length - 1].Frames)) * 2352;
								}

								if (fStart < fStop)
								{
									AddTrack(strFile, cue.Tracks[iTrack].Performer, cue.Tracks[iTrack].Title, fStart, fStop, 
                                        true, iStart, iStop);
								}
							}

							// добавление информации об артисте и названии диска
							if ((0 == textArtist.Text.Length) && (0 == textTitle.Text.Length))
							{
								textArtist.Text = cue.Performer;
								textTitle.Text  = cue.Title;
							}
						}
					}
				}

				// добавление файла
				else
				{
					AddTrack(dlgAddTrack.FileNames[i]);
				}
			}

			ReCalcLengthCD();
		}

		/// <summary>
		/// Добавление трека.
		/// </summary>
		private void AddTrack(string strFilename)
		{
			IntPtr ptrArtist = Marshal.AllocHGlobal(400);
			IntPtr ptrAlbum  = Marshal.AllocHGlobal(400);
			IntPtr ptrTitle  = Marshal.AllocHGlobal(400);

			AOPAPI.AOPGetTags(strFilename, ptrArtist, ptrAlbum, ptrTitle);

			string strArtist = Marshal.PtrToStringUni(ptrArtist).Trim();
			string strAlbum  = Marshal.PtrToStringUni(ptrAlbum).Trim();
			string strTitle  = Marshal.PtrToStringUni(ptrTitle).Trim();

			// добавление информации об артисте и названии диска
			if ((0 == textArtist.Text.Length) && (0 == textTitle.Text.Length))
			{
				textArtist.Text = strArtist;
				textTitle.Text  = strAlbum;
			}

			// добавление трека
			if ((strTitle.Length > 0) || (strArtist.Length > 0))
			{
				AddTrack(strFilename, strArtist, strTitle, 0, 0, false, 0, 0);
			}
			else
			{
				AddTrack(strFilename, "", Path.GetFileNameWithoutExtension(strFilename), 0, 0, false, 0, 0);
			}
		}

		/// <summary>
		/// Добавление трека.
		/// </summary>
		/// <param name="strFilename">полный путь к файлу</param>
		private void AddTrack(string strFilename, string strArtist, string strTitle, 
            float fStart, float fStop, bool bCue, Int32 iStart, Int32 iStop)
		{
			// проверка максимального количества треков = 100 штук
			if (100 == listTrack.Items.Count)
			{
				MessageBox.Show(String.Format(Properties.Resources.IDS_AUDIOCD_UNABLEADD, strFilename), 
                    Properties.Resources.IDS_AUDIOCD_UNABLEADD_CAPTION, MessageBoxButtons.OK, MessageBoxIcon.Warning);

				return;
			}

			// проверка поддержки данного файла
			if (0 == AOPAPI.AOPGetLen(strFilename))
			{
				MessageBox.Show(this, String.Format(Properties.Resources.IDS_AUDIOCD_WRONGFORMAT, strFilename), 
                    Properties.Resources.IDS_AUDIOCD_WRONGFORMAT_CAPTION, MessageBoxButtons.OK, MessageBoxIcon.Warning);

				return;
			}

			// инициализация структуры с информацие о треке
			TRACKITEM itemTrack;

			itemTrack             = new TRACKITEM();
			itemTrack.strFilename = strFilename;
			itemTrack.bCue        = bCue;
			itemTrack.iStart      = iStart;
			itemTrack.iStop       = iStop;

			if (0 == fStop)
			{
				itemTrack.fStart = 0;
				itemTrack.fStop  = AOPAPI.AOPGetLen(strFilename);
			}
			else
			{
				itemTrack.fStart = fStart;
				itemTrack.fStop  = fStop;
			}

			float fLength = itemTrack.fStop - itemTrack.fStart;

			// добавление трека в список
			listTrack.Items.Add(string.Format("{0:D}.", listTrack.Items.Count + 1));
			listTrack.Items[listTrack.Items.Count - 1].SubItems.Add(strArtist);
			listTrack.Items[listTrack.Items.Count - 1].SubItems.Add(strTitle);
			listTrack.Items[listTrack.Items.Count - 1].SubItems.Add(string.Format("{0:D}:{1:D02}", 
                (int)(fLength / 60), (int)(fLength - (int)(fLength / 60) * 60)));
			listTrack.Items[listTrack.Items.Count - 1].Tag = itemTrack;

			if (listTrack.Items.Count > 0)
			{
				btnBurn.Enabled = true;
			}
		}

		/// <summary>
		/// Информация о диске.
		/// </summary>
		private void DiscInfo(object sender, EventArgs e)
		{
            if (-1 == cbDeviceName.SelectedIndex)
            {
                return;
            }

			AOPAPI.DEVICEINFO devInfo = GetWorkDevice();
			DiscInfoForm      formDiscInfo;

			formDiscInfo = new DiscInfoForm(devInfo);
			formDiscInfo.ShowDialog();
		}

		/// <summary>
		/// Стирание CD-RW.
		/// </summary>
		private void Erase(object sender, EventArgs e)
		{
            if (-1 == cbDeviceName.SelectedIndex)
            {
                return;
            }

			AOPAPI.DEVICEINFO devInfo = GetWorkDevice();
			EraseForm         formErase;

			formErase = new EraseForm(devInfo, m_formAOP.bAudioCDLoadTray);
			formErase.ShowDialog();
		}

		/// <summary>
		/// Настройки программы.
		/// </summary>
		private void Options(object sender, EventArgs e)
		{
			AudioCDOptions formSettings;

			formSettings = new AudioCDOptions(m_formAOP);
			formSettings.ShowDialog();
		}

		/// <summary>
		/// Обработка загрузки форма.
		/// </summary>
		private void LoadForm(object sender, EventArgs e)
		{
			// установка шрифта по-умолчанию
			this.Font = SystemFonts.DefaultFont;

			// установка громкости
			trackVolume.Value = (int)AOPAPI.AOPGetVolume() / 5;
		}

		/// <summary>
		/// обработка входа в зону listTracks для drag'n'drop.
		/// </summary>
		private void DragDropTrackEnter(object sender, DragEventArgs e)
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
		/// Завершение drag'n'drop.
		/// </summary>
		private void DragDropTrack(object sender, DragEventArgs e)
		{
			if (e.Data.GetDataPresent(typeof(System.Windows.Forms.ListViewItem)))
			{
				listTrack.Invalidate();

				Point        ptnTarget  = listTrack.PointToClient(new Point(e.X, e.Y));
				ListViewItem itemTarget = listTrack.GetItemAt(ptnTarget.X, ptnTarget.Y);

				if (null != itemTarget)
				{
					if (itemTarget.Selected)
					{
						return;
					}

					if ((itemTarget.Index > 0) && (listTrack.Items[itemTarget.Index - 1].Selected))
					{
						return;
					}

					if (itemTarget.Index < listTrack.SelectedIndices[0])
					{
						// перемещение
						int iTmp = listTrack.SelectedIndices[0];

						for (int i = itemTarget.Index; i < iTmp; i++)
						{
							UpTracks(null, null);
						}
					}
					else
					{
						// перемещение
						for (int i = listTrack.SelectedIndices[0] + 1; i < itemTarget.Index; i++)
						{
							DownTracks(null, null);
						}
					}
				}
				else
				{
					if (listTrack.SelectedItems[listTrack.SelectedItems.Count - 1].Index == (listTrack.Items.Count - 1))
					{
						return;
					}

					// перемещение
					for (int i = listTrack.SelectedItems[listTrack.SelectedItems.Count - 1].Index + 1; 
                        i < listTrack.Items.Count; i++)
					{
						DownTracks(null, null);
					}
				}

				// перерисовываем список
				Invalidate();

				// пересчет треков
				ReNumberTracks();

				m_uiLastIndex = -1;
			}
			else

			if (e.Data.GetDataPresent(DataFormats.FileDrop))
			{
				string[] strFiles = (string[])e.Data.GetData(DataFormats.FileDrop);

				for (int i = 0; i < strFiles.Length; i++)
				{
					AddTrack(strFiles[i]);
				}

				ReCalcLengthCD();
			}
		}

		/// <summary>
		/// Реализация drag'n'drop для элементов listTracks.
		/// </summary>
		private void ItemDrag(object sender, ItemDragEventArgs e)
		{
			if (listTrack.Items.Count > 1)
			{
				DoDragDrop(e.Item, DragDropEffects.Move);
			}
		}

		/// <summary>
		/// Обработка движения элементов при drag'n'drop.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void DragDropTrackOver(object sender, DragEventArgs e)
		{
			if (e.Data.GetDataPresent(typeof(System.Windows.Forms.ListViewItem)))
			{
				e.Effect = DragDropEffects.Move;

				// получение элемента
				Point        ptnTarget  = listTrack.PointToClient(new Point(e.X, e.Y));
				ListViewItem itemTarget = listTrack.GetItemAt(ptnTarget.X, ptnTarget.Y);

				int iIndex;
				int iY;
				if (null != itemTarget)
				{
					iIndex = itemTarget.Index;

					iY = itemTarget.Position.Y;
				}
				else
				{
					iIndex = listTrack.Items.Count;

					iY = listTrack.Items[listTrack.Items.Count - 1].Position.Y + listTrack.Items[1].Position.Y - 
                        listTrack.Items[0].Position.Y;
				}

				// перерисовка при необходимости
				if (m_uiLastIndex != iIndex)
				{
					if (m_uiLastIndex >= 0)
					{
						if (m_uiLastIndex < listTrack.Items.Count)
						{
							listTrack.Invalidate(new Rectangle(0, listTrack.Items[m_uiLastIndex].Position.Y - 4, 
                                listTrack.ClientSize.Width, 7));
						}
						else
						{
							int iLastY = listTrack.Items[listTrack.Items.Count - 1].Position.Y + 
                                listTrack.Items[1].Position.Y - listTrack.Items[0].Position.Y;

							listTrack.Invalidate(new Rectangle(0, iLastY - 4, listTrack.ClientSize.Width, 7));
						}
					}

					m_uiLastIndex = iIndex;
				}

				// вывод линии вставки
				Graphics g = Graphics.FromHwnd(listTrack.Handle);
				g.DrawLine(new Pen(Color.Black), 0, iY - 1, listTrack.ClientRectangle.Width, iY - 1);
				g.DrawLine(new Pen(Color.Black), 0, iY, listTrack.ClientRectangle.Width, iY);

				Point ptnPoligonL1 = new Point(0, iY - 5);
				Point ptnPoligonL2 = new Point(4, iY - 1);
				Point ptnPoligonL3 = new Point(0, iY + 3);
				Point[] arrPointsL = {ptnPoligonL1, ptnPoligonL2, ptnPoligonL3};
				g.FillPolygon(new SolidBrush(Color.Black), arrPointsL);

				Point ptnPoligonR1 = new Point(listTrack.ClientRectangle.Width, iY - 5);
				Point ptnPoligonR2 = new Point(listTrack.ClientRectangle.Width - 4, iY - 1);
				Point ptnPoligonR3 = new Point(listTrack.ClientRectangle.Width, iY + 3);
				Point[] arrPointsR = { ptnPoligonR1, ptnPoligonR2, ptnPoligonR3 };
				g.FillPolygon(new SolidBrush(Color.Black), arrPointsR);
			}
		}

		/// <summary>
		/// Обработка выхода из зоны dran'n'drop.
		/// </summary>
		private void DragDropTrackLeave(object sender, EventArgs e)
		{
			listTrack.Invalidate();
		}
		
		/// <summary>
		/// Удаление выбранного трека.
		/// </summary>
		private void RemoveTrack(object sender, EventArgs e)
		{
			// удаление выбранных треков из списка
			ListView.SelectedListViewItemCollection itemsSel = listTrack.SelectedItems;

			foreach (ListViewItem item in itemsSel)
			{
				listTrack.Items.Remove(item);
			}

			// пересчет треков
			ReNumberTracks();

			// пересчет длительности CD
			ReCalcLengthCD();

			// при отсутствии треков выключаем кнопку прожига, и очищаем все поля
			if (0 == listTrack.Items.Count)
			{
				btnBurn.Enabled = false;
				
				textArtist.Text = "";
				textTitle.Text  = "";
			}
		}

		/// <summary>
		/// Пересчет треков.
		/// </summary>
		private void ReNumberTracks()
		{
			for (int i = 0; i < listTrack.Items.Count; i++)
			{
				listTrack.Items[i].Text = string.Format("{0:D}.", i + 1);
			}
		}

		/// <summary>
		/// Пересчет времени CD.
		/// </summary>
		private void ReCalcLengthCD()
		{
			float fLength = 0;

			for (int i = 0; i < listTrack.Items.Count; i++)
			{
				TRACKITEM itemTrack = (TRACKITEM)listTrack.Items[i].Tag;

				fLength += itemTrack.fStop - itemTrack.fStart;
			}

			labelLength.Text = string.Format("{0:D02}:{1:D02}", 
                (int)(fLength / 60), (int)(fLength - (int)(fLength / 60) * 60));

			// если общее время списка больше 80 минут, вывод времени красным цветом
			if (fLength > 80 * 60)
			{
				labelLength.ForeColor = Color.Red;
			}
			else
			{
				labelLength.ForeColor = Color.Black;
			}
		}

		/// <summary>
		/// Возвращает информацию о выбранном CD/DVD устройстве.
		/// </summary>
		public AOPAPI.DEVICEINFO GetWorkDevice()
		{
			List<AOPAPI.DEVICEINFO> devInfoList = m_formAOP.GetListDevices();

			return devInfoList[cbDeviceName.SelectedIndex];
		}

		/// <summary>
		/// Обработка смены устройства.
		/// </summary>
		private void ChangeDevice(object sender, EventArgs e)
		{
			FillWriteSpeeds();
		}

		/// <summary>
		/// обработка изменения громкости.
		/// </summary>
		private void ScrollVolume(object sender, EventArgs e)
		{
			AOPAPI.AOPSetVolume((uint)trackVolume.Value * 5);
		}

		/// <summary>
		/// Переименование трека.
		/// </summary>
		private void RenameTrack(object sender, EventArgs e)
		{
			if (listTrack.SelectedIndices.Count > 0)
			{
				if (null == sender)
				{
					if (listTrack.SelectedItems.Count > 0)
					{
						EditNameTrack formRename = new EditNameTrack(listTrack.SelectedItems[0], listTrack.SelectedItems);

						formRename.ShowDialog();
					}
				}
				else
				{
					Point ptnTarget;

					if (sender.GetType() == typeof(ToolStripMenuItem))
					{
						ptnTarget = listTrack.PointToClient(new Point(m_ptnMouseMenu.X, m_ptnMouseMenu.Y));
					}
					else
					{
						ptnTarget = listTrack.PointToClient(new Point(MousePosition.X, MousePosition.Y));
					}

					ListViewItem itemRename = listTrack.GetItemAt(ptnTarget.X, ptnTarget.Y);

					if (null != itemRename)
					{
						EditNameTrack formRename = new EditNameTrack(itemRename, listTrack.SelectedItems);

						formRename.ShowDialog();
					}
				}
			}
		}

		/// <summary>
		/// Выделение всех треков.
		/// </summary>
		private void SelectAll(object sender, EventArgs e)
		{
			for (int i = 0; i < listTrack.Items.Count; i++)
			{
				listTrack.Items[i].Selected = true;
			}
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
		/// Переход к предыдущему треку.
		/// </summary>
		private void PrevTrack(object sender, EventArgs e)
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
		/// Переход к следующему треку.
		/// </summary>
		private void NextTrack(object sender, EventArgs e)
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
		/// Остановка проигрывания.
		/// </summary>
		public void Stop(object sender, EventArgs e)
		{
			timerPos.Stop();

			AOPAPI.AOPStop();

			trackPos.Value = 0;
		}

		/// <summary>
		/// Проигрывание.
		/// </summary>
		private void Play(object sender, EventArgs e)
		{
			AOPAPI.AOPStop();

			if (listTrack.SelectedIndices.Count > 0)
			{
				TRACKITEM itemTrack = (TRACKITEM)listTrack.SelectedItems[0].Tag;

				m_fStartPos = itemTrack.fStart;
				m_fStopPos  = itemTrack.fStop;

				trackPos.Value = 0;

				AOPAPI.AOPPlay(itemTrack.strFilename);
				AOPAPI.AOPPlayPosition(itemTrack.fStart);

				timerPos.Start();
			}
		}

		/// <summary>
		/// Занести список треков в clipboard.
		/// </summary>
		private void AddClipboard(object sender, EventArgs e)
		{
			string strTextToClipboard = "";

			for (int i = 0; i < listTrack.Items.Count; i++)
			{
				strTextToClipboard += listTrack.Items[i].SubItems[0].Text + ". " + 
                    listTrack.Items[i].SubItems[1].Text + " - " + listTrack.Items[i].SubItems[2].Text + 
                    " [" + listTrack.Items[i].SubItems[3].Text + "]\r\n";
			}

			strTextToClipboard += "\r\n";
			strTextToClipboard += "Create by Audio One Pack";

			if (strTextToClipboard.Length > 0)
			{
				Clipboard.SetText(strTextToClipboard);
			}
		}

		/// <summary>
		/// Переместить выбранные треки на одну позицию вверх.
		/// </summary>
		private void UpTracks(object sender, EventArgs e)
		{
			// если перемещать нечего выходим
			if (0 == listTrack.SelectedItems.Count)
			{
				return;
			}

			// если перемещать некуда, выходим
			if (0 == listTrack.SelectedItems[0].Index)
			{
				return;
			}

			// перемещение
			for (int i = 0; i < listTrack.SelectedItems.Count; i++)
			{
				ListViewItem itemTmp;

				itemTmp = listTrack.Items[listTrack.SelectedItems[i].Index - 1];
				listTrack.Items.RemoveAt(listTrack.SelectedItems[i].Index - 1);
				listTrack.Items.Insert(listTrack.SelectedItems[i].Index + 1, itemTmp);
			}

			// пересчитываем треки
			ReNumberTracks();
		}

		/// <summary>
		/// Переместить выбранные треки на одну позицию вниз.
		/// </summary>
		private void DownTracks(object sender, EventArgs e)
		{
			// если перемещать нечего, выходим
			if (0 == listTrack.SelectedItems.Count)
			{
				return;
			}

			// если перемещать некуда, выходим
			if (listTrack.SelectedItems[listTrack.SelectedItems.Count - 1].Index == (listTrack.Items.Count - 1))
			{
				return;
			}

			// перемещение
			for (int i = listTrack.SelectedItems.Count - 1; i >= 0; i--)
			{
				ListViewItem itemTmp;

				itemTmp = listTrack.Items[listTrack.SelectedItems[i].Index + 1];
				listTrack.Items.RemoveAt(listTrack.SelectedItems[i].Index + 1);
				listTrack.Items.Insert(listTrack.SelectedItems[i].Index, itemTmp);
			}

			ReNumberTracks();
		}

		/// <summary>
		/// Установка текущей позиции проигрываемого трека.
		/// </summary>
		private void TimerTickPos(object sender, EventArgs e)
		{
			float fPos = AOPAPI.AOPGetPos();

			if (fPos >= m_fStopPos)
			{
				Stop(null, null);
			}
			else
			{
				int iValue = (int)((trackPos.Maximum - trackPos.Minimum) * 
                    ((fPos - m_fStartPos) / (m_fStopPos - m_fStartPos)));

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
        /// Обработка открытия контекстного меню.
        /// </summary>
        private void OpenContextMenu(object sender, CancelEventArgs e)
        {
            m_ptnMouseMenu.X = MousePosition.X;
            m_ptnMouseMenu.Y = MousePosition.Y;
        }

		/// <summary>
		/// Обработка изменения позиции проигрывания файла.
		/// </summary>
		private void ScrollPosition(object sender, EventArgs e)
		{
			AOPAPI.AOPPlayPosition(m_fStartPos + (float)trackPos.Value / 
                (trackPos.Maximum - trackPos.Minimum) * (m_fStopPos - m_fStartPos));
		}

		/// <summary>
		/// Обработка нажатия клавиши.
		/// </summary>
		private void KeyPressTracks(object sender, KeyPressEventArgs e)
		{
			if ((char)Keys.Return == e.KeyChar)
			{
				RenameTrack(null, null);
			}
		}

		/// <summary>
		/// Запуск процесса прожига диска.
		/// </summary>
		private void Burn(object sender, EventArgs e)
		{
			// структура с информацией о выбранном устройстве
			AOPAPI.DEVICEINFO devInfo = GetWorkDevice();

			// получение информации о диске
			AOPAPI.DISCINFO discInfo;

			AOPAPI.AOPGetDiscInfo(ref devInfo, out discInfo, null);

			// быстрая очистка перезаписываемого диска
			if ((1 /*TRUE*/ != discInfo.bIsDiscBlank) && (3 /*CD-RW*/ == discInfo.iDiscType))
			{
				// предложение сделать Quick Erase
				if (DialogResult.Cancel == MessageBox.Show(Properties.Resources.IDS_QUICKERASE, 
                    Properties.Resources.IDS_QUICKERASE_CAPTION, MessageBoxButtons.YesNo, MessageBoxIcon.Information))
				{
					return;
				}
				
				// выполнение быстрого стирания
				EraseForm formErase = new EraseForm(devInfo, true, true);

				formErase.ShowDialog();

				// обновление информации о диске
				AOPAPI.AOPGetDiscInfo(ref devInfo, out discInfo, null);
			}

			// проверка наличия чистого диска
			if (1 /*TRUE*/ == discInfo.bIsDiscBlank)
			{
				// блокировка
				AOPAPI.AOPLock(ref devInfo);

				// вызов формы прожига
				AudioCDBurn formBurn = new AudioCDBurn(m_formAOP, this);

				formBurn.ShowDialog();

				// разблокировка
				AOPAPI.AOPUnLock(ref devInfo);

				// eject tray
				AOPAPI.AOPEjectTray(ref devInfo);

				// load tray
				if (m_formAOP.bAudioCDLoadTray)
				{
					AOPAPI.AOPLoadTray(ref devInfo);
				}

				// очистка списка
				if (m_formAOP.bClearListAfterBurn)
				{
					SelectAll(null, null);
					
					RemoveTrack(null, null);
				}
			}

			else
			{
				MessageBox.Show(Properties.Resources.IDS_AUDIOCD_INSERTBLANK);
			}
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
		/// Возвращает исполнителя диска.
		/// </summary>
		public String GetArtistDisk()
		{
			return textArtist.Text;
		}

		/// <summary>
		/// Возвращает название диска.
		/// </summary>
		public String GetTitleDisk()
		{
			return textTitle.Text;
		}

		/// <summary>
		/// Возвращает список треков.
		/// </summary>
		public ListView GetListTrack()
		{
			return listTrack;
		}

		/// <summary>
		/// Синхронизация громкости.
		/// </summary>
		private void VisibleForm(object sender, EventArgs e)
		{
			trackVolume.Value = (int)AOPAPI.AOPGetVolume() / 5;
		}

		/// <summary>
		/// Заполнение выпадающего списка скоростями записи.
		/// </summary>
		public void FillWriteSpeeds()
		{
			cbSpeeds.Items.Clear();

			List<List<String>> listWriteSpeed = m_formAOP.GetWriteSpeed();
			int                iDevice        = cbDeviceName.SelectedIndex;

            if (-1 == iDevice)
            {
                return;
            }

			for (int i = 0; i < listWriteSpeed[iDevice].Count; i++)
			{
				cbSpeeds.Items.Add(listWriteSpeed[iDevice][i]);
			}

			cbSpeeds.SelectedIndex = cbSpeeds.Items.Count - 1;
		}

		/// <summary>
		/// Возвращает индекс скорости для записи.
		/// </summary>
		/// <returns></returns>
		public int GetWriteSpeed()
		{
			return cbSpeeds.SelectedIndex;
		}
	}
}

