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
using System.Collections.Specialized;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.IO;

namespace AudioOnePack
{
	//
	public partial class AudioCDBurn : Form
	{
		/// <summary>
		/// Ссылка на главную форму.
		/// </summary>
		private AOPForm m_formAOP;

		/// <summary>
		/// Ссылка на форму создания AudioCD.
		/// </summary>
		private AudioCDForm m_formAudioCD;

		/// <summary>
		/// Информация о выбранном устройстве.
		/// </summary>
		private AOPAPI.DEVICEINFO m_devInfo;

		/// <summary>
		/// Список треков.
		/// </summary>
		private ListView m_listTrack;

		/// <summary>
		/// список треков для обработки.
		/// </summary>
		private List<AudioCDForm.TRACKITEM> m_arrTracks = new List<AudioCDForm.TRACKITEM>();

		/// <summary>
		/// список WAV файлов соответствующий списку треков.
		/// </summary>
		private StringCollection m_arrFiles = new StringCollection();

		/// <summary>
		/// Список исполнителей треков.
		/// </summary>
		private StringCollection m_arrArtist = new StringCollection();

		/// <summary>
		/// Список наименований треков.
		/// </summary>
		private StringCollection m_arrTitle = new StringCollection();

		/// <summary>
		/// Исполнитель.
		/// </summary>
		private string m_strArtistCD;

		/// <summary>
		/// Название диска.
		/// </summary>
		private string m_strTitleCD;

		/// <summary>
		/// событие для декодирования.
		/// </summary>
		private AutoResetEvent m_eventDecode = new AutoResetEvent(false);

		/// <summary>
		/// флаг выхода.
		/// </summary>
		private bool m_bExit = false;

		/// <summary>
		/// каталог для временных файлов.
		/// </summary>
		private string m_strTempDir;

		/// <summary>
		/// Индекс скорости записи.
		/// </summary>
		private int m_iSpeed;

		/// <summary>
		/// Делегат без параметров.
		/// </summary>
		private delegate void DelegateNoParam();

		/// <summary>
		/// Конструктор по-умолчанию.
		/// </summary>
		public AudioCDBurn()
		{
			InitializeComponent();
		}

		//
		public AudioCDBurn(AOPForm formAOP, AudioCDForm formAudioCD)
			: this()
		{
			m_formAOP     = formAOP;
			m_formAudioCD = formAudioCD;
			m_devInfo     = m_formAudioCD.GetWorkDevice();
			m_listTrack   = m_formAudioCD.GetListTrack();
			m_iSpeed      = m_formAudioCD.GetWriteSpeed();
		}

		/// <summary>
		/// Отмена прожига.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Cancel(object sender, EventArgs e)
		{
			btnCancel.Enabled = false;

			m_bExit = true;
		}

		/// <summary>
		/// Вызывает при показе формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void FirstShow(object sender, EventArgs e)
		{
			// формирование наименования диска
			m_strArtistCD = m_formAudioCD.GetArtistDisk();
			m_strTitleCD  = m_formAudioCD.GetTitleDisk();

			// получение треков для декодирования
			for (int i = 0; i < m_listTrack.Items.Count; i++)
			{
				AudioCDForm.TRACKITEM itemTrack = (AudioCDForm.TRACKITEM)m_listTrack.Items[i].Tag;

				m_arrTracks.Add(itemTrack);
				m_arrArtist.Add(m_listTrack.Items[i].SubItems[1].Text);
				m_arrTitle.Add(m_listTrack.Items[i].SubItems[2].Text);
			}

			// создание каталога для временных файлов
			m_strTempDir = m_formAOP.TempPath + "\\" + GetHashCode().ToString() + "\\";

			Directory.CreateDirectory(m_strTempDir);

			if (false == Directory.Exists(m_strTempDir))
			{
				MessageBox.Show(this, Properties.Resources.IDS_AUDIOBURN_ERRORTMP, 
					Properties.Resources.IDS_AUDIOBURN_ERRORTMP_CAPTION, 
					MessageBoxButtons.OK, MessageBoxIcon.Error);

				Close();
			}

			// запуск процесса декодирования
			(new DelegateNoParam(Decode)).BeginInvoke(null, null);
		}

		/// <summary>
		/// Декодирование файлов.
		/// </summary>
		private void Decode()
		{
			// декодирование файлов
			AOPAPI.DecodeCallbackDelegate delegateDecode = new AOPAPI.DecodeCallbackDelegate(DecodeCallback);

			for (int i = 0; i < m_arrTracks.Count; i++)
			{
				if (true == m_arrTracks[i].bCue)
				{
					Invoke(new SetInfoLineOneDelegate(SetInfoLineOne), Properties.Resources.IDS_AUDIOBURN_DECODING);
					Invoke(new SetInfoLineTwoDelegate(SetInfoLineTwo), Path.GetFileName(m_arrTracks[i].strFilename));
				}
				else
				{
					Invoke(new SetInfoLineOneDelegate(SetInfoLineOne), String.Format(
						Properties.Resources.IDS_AUDIOBURN_CREATING, i + 1, m_arrTracks.Count));
					Invoke(new SetInfoLineTwoDelegate(SetInfoLineTwo), m_arrArtist[i] + " - " + m_arrTitle[i]);
				}

				string strFullFile = m_strTempDir + Path.GetFileName(m_arrTracks[i].strFilename).GetHashCode().ToString();

				// декодирование файла, если его еще не было
				if (false == File.Exists(strFullFile))
				{
					// запуск декодирования очередного файла
					AOPAPI.AOPDecode(m_arrTracks[i].strFilename, strFullFile, delegateDecode);

					// ожидание завершение декодирования очередного файла
					m_eventDecode.WaitOne();
				}
				
				try
				{
					if (true == m_arrTracks[i].bCue)
					{
						Invoke(new SetInfoLineOneDelegate(SetInfoLineOne), String.Format(
							Properties.Resources.IDS_AUDIOBURN_CREATING, i + 1, m_arrTracks.Count));
						Invoke(new SetInfoLineTwoDelegate(SetInfoLineTwo), m_arrArtist[i] + " - " + m_arrTitle[i]);

						Int32 iStart = m_arrTracks[i].iStart;
						Int32 iStop  = m_arrTracks[i].iStop;

						FileStream fsIn  = File.Open(strFullFile, FileMode.Open);
						FileStream fsOut = File.Open(strFullFile + "." + i.ToString(), FileMode.Create);

						if (null != fsIn)
						{
							// чтение и запись заголовка
							byte[] bHeader = new byte[44];

							fsIn.Read(bHeader, 0, 44);
							fsOut.Write(bHeader, 0, 44);

							// чтение и запись файла
							fsIn.Seek(44 + iStart, SeekOrigin.Begin);

							byte[] bTmp = new byte[65536 * 8];
							Int32 iPos = iStart;
							Int32 iRead = 1;

							while ((iPos < iStop) && (iRead > 0))
							{
								iRead = fsIn.Read(bTmp, 0, 65536 * 8);

								if (iRead > 0)
								{
									if ((iPos + iRead) < iStop)
									{
										fsOut.Write(bTmp, 0, iRead);
									}
									else
									{
										fsOut.Write(bTmp, 0, iStop - iPos);
									}

									iPos += iRead;
									
									Invoke(new SetProgressDelegate(SetProgress), (float)(iPos - iStart) / (iStop - iStart));
								}
							}

							fsIn.Close();

							// правка заголовка выходного файла
							BinaryWriter bwOut = new BinaryWriter(fsOut);
							Int32 iLengthWav;

							iLengthWav = (Int32)fsOut.Length;
							bwOut.Seek(4, SeekOrigin.Begin);
							bwOut.Write(iLengthWav - 8);
	
							bwOut.Seek(40, SeekOrigin.Begin);
							bwOut.Write(iLengthWav - 44);

							fsOut.Close();

							m_arrFiles.Add(strFullFile + "." + i.ToString());
						}
					}
					else
					{
						m_arrFiles.Add(strFullFile);
					}
				}
				catch (System.Exception e)
				{
					MessageBox.Show(e.Message);
				}

				// выход, если была нажата кнопка Cancel
				if (true == m_bExit)
				{
					Invoke(new DelegateNoParam(Close));

					return;
				}
			}

			Invoke(new DelegateNoParam(EndDecode));
		}

		/// <summary>
		/// Callback функция декодирования.
		/// </summary>
		private void DecodeCallback(Int32 uiAction, Int32 uiParamOne, Int32 uiParamTwo)
		{
			switch (uiAction)
			{
				case (int)AOPAPI.DecodeEnum.DECODE_STOP:
					m_eventDecode.Set();
					break;

				case (int)AOPAPI.DecodeEnum.DECODE_ERROR:
					m_eventDecode.Set();
					break;

				case (int)AOPAPI.DecodeEnum.DECODE_POS:
					Invoke(new SetProgressDelegate(SetProgress), (float)uiParamOne / uiParamTwo);
					break;
			}
		}

		/// <summary>
		/// Обработка завершения декодирования.
		/// </summary>
		private void EndDecode()
		{
			// отключаем кнопку Cancel
			btnCancel.Enabled = false;

			// запуск процесса прожига
			(new DelegateNoParam(BurnAudioCD)).BeginInvoke(null, null);
		}

		/// <summary>
		/// Прожиг диска.
		/// </summary>
		private void BurnAudioCD()
		{
			try
			{
			Invoke(new SetInfoLineOneDelegate(SetInfoLineOne), Properties.Resources.IDS_AUDIOBURN_BURN);
			Invoke(new SetInfoLineTwoDelegate(SetInfoLineTwo), Properties.Resources.IDS_AUDIOBURN_WAIT);
			Invoke(new SetProgressDelegate(SetProgress), 0);

			while (true)
			{
				AOPAPI.AudioBurnCallbackDelegate delegateBurn = new AOPAPI.AudioBurnCallbackDelegate(BurnAudioCDCallback);

				// инициализация Audio CD
				if (0 != AOPAPI.AOPAudioCDInit(ref m_devInfo))
				{
					MessageBox.Show("ERROR::AOPAudioCDInit", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);

					break;
				}

				// формирование треков
				for (int i = 0; i < m_arrFiles.Count; i++)
				{
					if (0 != AOPAPI.AOPAudioCDAddTrack(m_arrFiles[i]))
					{
						MessageBox.Show("ERROR::AOPAudioCDAddTrack", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);

						break;
					}

					if (0 != AOPAPI.AOPAudioCDSetTitle((byte)(i + 1), m_arrArtist[i], m_arrTitle[i]))
					{
						MessageBox.Show("ERROR::AOPAudioCDSetTitle", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);

						break;
					}
				}

				if (0 != AOPAPI.AOPAudioCDSetTitle(0, m_strArtistCD, m_strTitleCD))
				{
					MessageBox.Show("ERROR::AOPAudioCDSetTitle", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);

					break;
				}

				// прожиг диска
				if (0 != AOPAPI.AOPAudioCDBurn(delegateBurn, m_iSpeed))
				{
					MessageBox.Show("ERROR::AOPAudioCDBurn", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);

					break;
				}

				// освобождение ресурсов
				if (0 != AOPAPI.AOPAudioCDFree())
				{
					MessageBox.Show("ERROR::AOPAudioCDFree", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);

					break;
				}

				break;
			}
			}
			catch (System.Exception ex)
			{
				MessageBox.Show(ex.Message);
			}

			MessageBox.Show(Properties.Resources.IDS_AUDIOBURN_COMPLETE);

			Invoke(new DelegateNoParam(Close));
		}

		/// <summary>
		/// Callback Функция прожига.
		/// </summary>
		/// <param name="uiAction"></param>
		/// <param name="uiParamOne"></param>
		/// <param name="uiParamTwo"></param>
		private void BurnAudioCDCallback(Int32 uiAction, Int32 uiParamOne, Int32 uiParamTwo)
		{
			switch (uiAction)
			{
				case (int)AOPAPI.AudioEnum.AUDIOBURN_WRITE:
					Invoke(new SetProgressDelegate(SetProgress), (float)(uiParamOne / 100.0));
					break;
			}
		}

		/// <summary>
		/// Делегат для установки текста #1.
		/// </summary>
		private delegate void SetInfoLineOneDelegate(string strText);

		/// <summary>
		/// Установка текста в labelOne.
		/// </summary>
		/// <param name="strText"></param>
		private void SetInfoLineOne(string strText)
		{
			labelOne.Text = strText;
		}

		/// <summary>
		/// Делегат для установки текста #2.
		/// </summary>
		private delegate void SetInfoLineTwoDelegate(string strText);

		/// <summary>
		/// Установка текста в labelTwo.
		/// </summary>
		/// <param name="strText"></param>
		private void SetInfoLineTwo(string strText)
		{
			labelTwo.Text = strText;
		}

		/// <summary>
		/// Делегат для установки progressBurn.
		/// </summary>
		/// <param name="fPercent"></param>
		private delegate void SetProgressDelegate(float fPercent);

		/// <summary>
		/// Установка progressBurn.
		/// </summary>
		/// <param name="fPercent"></param>
		private void SetProgress(float fPercent)
		{
			int iValue = progressBurn.Minimum + (int)((progressBurn.Maximum - progressBurn.Minimum) * fPercent);

			if (iValue < progressBurn.Minimum)
			{
				progressBurn.Value = progressBurn.Minimum;
			}
			else if (iValue > progressBurn.Maximum)
			{
				progressBurn.Value = progressBurn.Maximum;
			}
			else
			{
				progressBurn.Value = iValue;
			}
		}

		/// <summary>
		/// Вызывает при закрытии формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void CloseForm(object sender, FormClosedEventArgs e)
		{
			// удаление временных файлов
			for (int i = 0; i < m_arrFiles.Count; i++)
			{
				File.Delete(m_arrFiles[i]);
			}

			for (int i = 0; i < m_arrTracks.Count; i++)
			{
				File.Delete(m_strTempDir + Path.GetFileName(m_arrTracks[i].strFilename).GetHashCode().ToString());
			}

			// удаление временной директории
			try
			{
				Directory.Delete(m_strTempDir);
			}
			catch (System.Exception error)
			{
				MessageBox.Show(this, String.Format(Properties.Resources.IDS_AUDIOBURN_ERRORDELTEMP, 
					m_strTempDir, error.Message), "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
	}
}

