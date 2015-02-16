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

using ID3;
using ID3.ID3v2Frames.TextFrames;

namespace AudioOnePack
{
	//
	public partial class ConvertProcess : Form
	{
		/// <summary>
		/// делегат без параметров.
		/// </summary>
		private delegate void DelegateNoParam();

		/// <summary>
		/// Делегат для установки progress.
		/// </summary>
		/// <param name="fPercent"></param>
		private delegate void SetProgressDelegate(float fPercent);

		/// <summary>
		/// Делегат для установки информационного сообщения.
		/// </summary>
		/// <param name="strText">текст сообщения</param>
		private delegate void SetTextDelegate(String strText);

		/// <summary>
		/// Ссылка на главную форму.
		/// </summary>
		private AOPForm m_formAOP;

		/// <summary>
		/// Ссылка на форму конвертирования.
		/// </summary>
		private ConvertForm m_formConvert;

		/// <summary>
		/// Порядковый номер кодека.
		/// </summary>
		private int m_iCodec = 0;

		/// <summary>
		/// Качество сжатия.
		/// </summary>
		private int m_iQuality = 0;

		/// <summary>
		/// Список файлов для конвертирования.
		/// </summary>
		private ArrayList m_arrFileNames = new ArrayList();

		/// <summary>
		/// Список с информацией о треках для конвертирования
		/// </summary>
		private ArrayList m_arrTracks = new ArrayList();

		/// <summary>
		/// Номер обрабатываемого файла.
		/// </summary>
		private int m_iCurNumberFile = 0;

		/// <summary>
		/// Флаг остановки конвертирования
		/// </summary>
		private Boolean m_bStop = false;

		/// <summary>
		/// Конструктор по-умолчанию.
		/// </summary>
		public ConvertProcess()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Конструктор с передачей ссылки на главную форму.
		/// </summary>
		/// <param name="formAOP"></param>
		public ConvertProcess(AOPForm formAOP, ConvertForm formConvert)
			: this()
		{
			m_formAOP = formAOP;
			m_formConvert = formConvert;
		}

		/// <summary>
		/// Остановка конвертирования.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Stop(object sender, EventArgs e)
		{
			btnStop.Enabled = false;

			m_bStop = true;
		}

		/// <summary>
		/// Обработка первого показа формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ShowForm(object sender, EventArgs e)
		{
			// получение кодека
			m_iCodec = m_formConvert.GetCodec();

			// получение качества сжатия
			m_iQuality = m_formConvert.GetQuality();

			// получение списка файлов
			m_arrFileNames = m_formConvert.GetFileNames();

			// получение информации о треках
			m_arrTracks = m_formConvert.GetTracksInfo();

			// запуск процесса риппинга
			(new DelegateNoParam(Converting)).BeginInvoke(null, null);
		}

		/// <summary>
		/// Процесс конвертирования.
		/// </summary>
		private void Converting()
		{
			AOPAPI.EncodeCallbackDelegate delegateEncode = new AOPAPI.EncodeCallbackDelegate(EncodeCallback);

			try
			{
				while (true)
				{
					String strName;
					int iNumber;

					for (int i = 0; i < m_arrFileNames.Count; i++)
					{
						m_iCurNumberFile = i;

						// вывод информации о конвертации
						Invoke(new SetTextDelegate(SetTextOne), String.Format(
							Properties.Resources.IDS_CONVERTPROCESS_CURRENTFILE, Path.GetFileName((String)m_arrFileNames[i])));
						Invoke(new SetTextDelegate(SetTextAll), String.Format(
							Properties.Resources.IDS_CONVERTPROCESS_CONVERT, i + 1, m_arrFileNames.Count));

						// формирование выходного каталога
						String strDirectoryName;

						if (true == m_formAOP.bConvertDestinationDir)
						{
							strDirectoryName = m_formAOP.strConvertOutPath;
						}
						else
						{
							strDirectoryName = Path.GetDirectoryName((String)m_arrFileNames[i]);
						}

						switch (m_iCodec)
						{
							// WAV
							case 0:
								// формирование имени выходного файла файла
								strName = strDirectoryName + "\\" + Path.GetFileNameWithoutExtension(
									(String)m_arrFileNames[i]) + ".wav";
								iNumber = 2;

								while (true == File.Exists(strName))
								{
									strName = strDirectoryName + "\\" + Path.GetFileNameWithoutExtension(
										(String)m_arrFileNames[i]) + "_" + iNumber.ToString() + ".wav";

									iNumber++;
								}

								AOPAPI.AOPEncodeWAV((String)m_arrFileNames[i], strName, delegateEncode);

								break;

							// MP3
							case 1:
								// формирование имени выходного файла файла
								strName = strDirectoryName + "\\" + Path.GetFileNameWithoutExtension(
									(String)m_arrFileNames[i]) + ".mp3";
								iNumber = 2;

								while (true == File.Exists(strName))
								{
									strName = strDirectoryName + "\\" + Path.GetFileNameWithoutExtension(
										(String)m_arrFileNames[i]) + "_" + iNumber.ToString() + ".mp3";

									iNumber++;
								}

								// запуск конвертации
								AOPAPI.AOPEncodeMP3((String)m_arrFileNames[i], strName, m_iQuality, delegateEncode);

								// прописывание тегов
								ID3Info id3File = new ID3Info(strName, true);

								id3File.ID3v1Info.HaveTag = true;

								id3File.ID3v1Info.Album = ((ConvertForm.TRACKITEM)m_arrTracks[i]).strAlbum;
								id3File.ID3v1Info.Artist = ((ConvertForm.TRACKITEM)m_arrTracks[i]).strArtist;
								id3File.ID3v1Info.Title = ((ConvertForm.TRACKITEM)m_arrTracks[i]).strTitle;
								id3File.ID3v1Info.Year = "";
								id3File.ID3v1Info.TrackNumber = 1;
								id3File.ID3v1Info.Comment = "by Audio One Pack";
								id3File.ID3v1Info.Genre = 255;

								id3File.ID3v2Info.HaveTag = true;

								id3File.ID3v2Info.SetMinorVersion(3);
								id3File.ID3v2Info.SetTextFrame("TPE2", ((ConvertForm.TRACKITEM)m_arrTracks[i]).strArtist);
								id3File.ID3v2Info.SetTextFrame("TALB", ((ConvertForm.TRACKITEM)m_arrTracks[i]).strAlbum);
								id3File.ID3v2Info.SetTextFrame("TPE1", "");
								id3File.ID3v2Info.SetTextFrame("TIT2", ((ConvertForm.TRACKITEM)m_arrTracks[i]).strTitle);
								id3File.ID3v2Info.SetTextFrame("TRCK", "");
								id3File.ID3v2Info.SetTextFrame("TYER", "");
								id3File.ID3v2Info.SetTextFrame("TENC", "by Audio One Pack");
								id3File.ID3v2Info.SetTextFrame("TCON", "");

								id3File.Save();

								break;

							// WMA
							case 2:
								// формирование имени выходного файла файла
								strName = strDirectoryName + "\\" + Path.GetFileNameWithoutExtension(
									(String)m_arrFileNames[i]) + ".wma";
								iNumber = 2;

								while (true == File.Exists(strName))
								{
									strName = strDirectoryName + "\\" + Path.GetFileNameWithoutExtension(
										(String)m_arrFileNames[i]) + "_" + iNumber.ToString() + ".wma";

									iNumber++;
								}

								AOPAPI.AOPEncodeWMA((String)m_arrFileNames[i], strName, 
									((ConvertForm.TRACKITEM)m_arrTracks[i]).strTitle,
									((ConvertForm.TRACKITEM)m_arrTracks[i]).strArtist, 
									((ConvertForm.TRACKITEM)m_arrTracks[i]).strAlbum, 
									"", "", m_iQuality, delegateEncode);

								break;

							// OGG
							case 3:
								// формирование имени выходного файла файла
								strName = strDirectoryName + "\\" + Path.GetFileNameWithoutExtension(
									(String)m_arrFileNames[i]) + ".ogg";
								iNumber = 2;

								while (true == File.Exists(strName))
								{
									strName = strDirectoryName + "\\" + Path.GetFileNameWithoutExtension(
										(String)m_arrFileNames[i]) + "_" + iNumber.ToString() + ".ogg";

									iNumber++;
								}

								AOPAPI.AOPEncodeOGG((String)m_arrFileNames[i], strName, 
									((ConvertForm.TRACKITEM)m_arrTracks[i]).strTitle, 
									((ConvertForm.TRACKITEM)m_arrTracks[i]).strArtist, 
									((ConvertForm.TRACKITEM)m_arrTracks[i]).strAlbum, 
									"", "", m_iQuality, delegateEncode);

								break;
						}

						// выход, если была нажата кнопка останова
						if (true == m_bStop)
						{
							break;
						}

						if (true == m_formAOP.bConvertDelete)
						{
							try
							{
								File.Delete((String)m_arrFileNames[i]);
							}
							catch (System.Exception)
							{
								MessageBox.Show(this, String.Format(
									Properties.Resources.IDS_CONVERTPROCESS_UNABLEDELETE, m_arrFileNames[i]));
							}
						}
					}

					break;
				}
			}
			catch (System.Exception exp)
			{
				MessageBox.Show(exp.Message);
			}
			
			Invoke(new DelegateNoParam(Close));
		}

		/// <summary>
		/// Callback функция кодирования.
		/// </summary>
		/// <param name="uiAction"></param>
		/// <param name="uiParamOne"></param>
		/// <param name="uiParamTwo"></param>
		private void EncodeCallback(Int32 uiAction, Int32 uiParamOne, Int32 uiParamTwo)
		{
			switch (uiAction)
			{
				case (int)AOPAPI.EncodeEnum.ENCODE_POS:
					Invoke(new SetProgressDelegate(SetProgressOne), (float)(uiParamOne) / uiParamTwo);
					Invoke(new SetProgressDelegate(SetProgressAll), 
						(float)(uiParamOne) / uiParamTwo / m_arrFileNames.Count + 
						(float)m_iCurNumberFile / m_arrFileNames.Count);
					break;
			}
		}

		/// <summary>
		/// Установка progressOne.
		/// </summary>
		/// <param name="fPercent"></param>
		private void SetProgressOne(float fPercent)
		{
			int iValue = progressOne.Minimum + (int)((progressOne.Maximum - progressOne.Minimum) * fPercent);

			if (iValue < progressOne.Minimum)
			{
				progressOne.Value = progressOne.Minimum;
			}
			else if (iValue > progressOne.Maximum)
			{
				progressOne.Value = progressOne.Maximum;
			}
			else
			{
				progressOne.Value = iValue;
			}
		}

		/// <summary>
		/// Установка progressAll.
		/// </summary>
		/// <param name="fPercent"></param>
		private void SetProgressAll(float fPercent)
		{
			int iValue = progressAll.Minimum + (int)((progressAll.Maximum - progressAll.Minimum) * fPercent);

			if (iValue < progressAll.Minimum)
			{
				progressAll.Value = progressAll.Minimum;
			}
			else if (iValue > progressAll.Maximum)
			{
				progressAll.Value = progressAll.Maximum;
			}
			else
			{
				progressAll.Value = iValue;
			}
		}

		/// <summary>
		/// Установка текста перед прогрессбаром для одного файла.
		/// </summary>
		/// <param name="strText"></param>
		private void SetTextOne(String strText)
		{
			textOne.Text = strText;
		}

		/// <summary>
		/// Установка текста перед прогрессбаром для всех файла.
		/// </summary>
		/// <param name="strText"></param>
		private void SetTextAll(String strText)
		{
			textAll.Text = strText;
		}
	}
}