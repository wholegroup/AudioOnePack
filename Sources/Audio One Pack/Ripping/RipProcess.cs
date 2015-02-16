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
using System.Threading;
using System.IO;

using ID3;
using ID3.ID3v2Frames.TextFrames;

namespace AudioOnePack
{
    //
	public partial class RipProcess : Form
	{
		/// <summary>
		/// делегат без параметров.
		/// </summary>
		private delegate void DelegateNoParam();

		/// <summary>
		/// Делегат для установки progressBurn.
		/// </summary>
		/// <param name="fPercent"></param>
		private delegate void SetProgressDelegate(float fPercent);

		/// <summary>
		/// Делегат для установки информационного сообщения.
		/// </summary>
		/// <param name="strRip"></param>
		private delegate void SetTextDelegate(String strRip);

		/// <summary>
		/// Ссылка на главную форму приложения.
		/// </summary>
		private AOPForm m_formAOP;

		/// <summary>
		/// Ссылка на форму RipCD.
		/// </summary>
		private RipCDForm m_formRipCD;
		
		/// <summary>
		/// Номера треков для грабинга.
		/// </summary>
		private int[] m_listTracks;
		private int[] m_listRealTracks;

		/// <summary>
		/// Информация о выбранном CD/DVD приводе.
		/// </summary>
		private AOPAPI.DEVICEINFO m_devInfo;

		/// <summary>
		/// Порядковый номер кодека.
		/// </summary>
		private int m_iCodec = 0;

		/// <summary>
		/// Качество сжатия.
		/// </summary>
		private int m_iQuality = 0;

		/// <summary>
		/// Риппинг в один файл
		/// </summary>
		private Boolean m_bSingle = false;

		/// <summary>
		/// Путь к директории для сохранения файлов.
		/// </summary>
		private String m_strOutDir;

		/// <summary>
		/// Наименование каталога для альбома.
		/// </summary>
		private String m_strAlbumDir;

		/// <summary>
		/// Наименование исполнителя диска.
		/// </summary>
		private String m_strArtist;

		/// <summary>
		/// Название диска.
		/// </summary>
		private String m_strTitle;

		/// <summary>
		/// Жанр диска.
		/// </summary>
		private String m_strGenre;

		/// <summary>
		/// Год диска.
		/// </summary>
		private String m_strYear;

		/// <summary>
		/// Наименования треков - исполнитель/название.
		/// </summary>
		private ArrayList[] m_arrNameTracks;

		/// <summary>
		/// Длина треков в фреймах.
		/// </summary>
		private ArrayList m_arrLengthInFrames;

		/// <summary>
		/// Индекс скорости чтения.
		/// </summary>
		private int m_iSpeed;

		/// <summary>
		/// Конструктор.
		/// </summary>
		public RipProcess()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Конструктор с передачей ссылки на главную форму и форму RipCD
		/// </summary>
		/// <param name="formAOP"></param>
		/// <param name="formRipCD"></param>
		public RipProcess(AOPForm formAOP, RipCDForm formRipCD)
			: this()
		{
			m_formAOP   = formAOP;
			m_formRipCD = formRipCD;
		}

		/// <summary>
		/// Обработка первого показа формы
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ShowForm(object sender, EventArgs e)
		{
			// получение списка треков для грабинга
			m_listTracks     = m_formRipCD.GetTrackIndices();
			m_listRealTracks = m_formRipCD.GetTrackRealIndices();

			// получение информации о нужном CD/DVD приводе
			m_devInfo = m_formRipCD.GetWorkDevice();

			// получение кодека
			m_iCodec = m_formRipCD.GetCodec();

			// получение качества сжатия
			m_iQuality = m_formRipCD.GetQuality();

			// получение значения сохранять в один файл или несколько
			m_bSingle = m_formRipCD.GetSingleFile();

			// путь к директории для сохранения файлов
			m_strOutDir = m_formRipCD.OutDir;

			// получение названия диска
			m_strArtist = m_formRipCD.GetDiskArtist();
			m_strTitle  = m_formRipCD.GetDiskTitle();

			// получение жанра диска
			m_strGenre = m_formRipCD.GetDiskGenre();

			// получение года диска
			m_strYear = m_formRipCD.GetDiskYear();

			// получение названия треков диска
			m_arrNameTracks = m_formRipCD.GetDiskNameTracks();

			// получение длины трека в фреймах
			m_arrLengthInFrames = m_formRipCD.GetLengthTracksInFrames();

			// получение индекса скорости чтения
			m_iSpeed = m_formRipCD.GetReadSpeed();

			// создание выходного каталога
			String strNewDir;
			int i = 1;

			m_strAlbumDir = m_strArtist + " - " + m_strTitle;
			strNewDir     = m_strOutDir + "\\" + m_strAlbumDir;

			while (Directory.Exists(strNewDir))
			{
				i++;

				strNewDir = m_strOutDir + "\\" + m_strAlbumDir + "." + i.ToString();
			}

			m_formRipCD.RealOutDir = m_strOutDir = strNewDir;

			try
			{
				Directory.CreateDirectory(m_strOutDir);
			}
			catch (System.Exception exp)
			{
				MessageBox.Show(exp.Message);

				DialogResult = DialogResult.Abort;

				return;
			}

			// запуск процесса риппинга
			(new DelegateNoParam(Ripping)).BeginInvoke(null, null);
		}

		/// <summary>
		/// Процесс грабинга
		/// </summary>
		private void Ripping()
		{
			AOPAPI.AudioRipCallbackDelegate delegateRip    = new AOPAPI.AudioRipCallbackDelegate(RipAudioCDCallback);
			AOPAPI.EncodeCallbackDelegate   delegateEncode = new AOPAPI.EncodeCallbackDelegate(EncodeCallback);

			String       strTempDir = m_formAOP.TempPath + "\\" + GetHashCode().ToString() + "\\";
			List<String> strTracks  = new List<string>();

			try
			{
				while (true)
				{
					// инициализация Audio CD
					if (0 != AOPAPI.AOPAudioCDInit(ref m_devInfo))
					{
						MessageBox.Show("ERROR::AOPAudioCDInit", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);

						break;
					}

					// создание каталога для временных файлов
					Directory.CreateDirectory(strTempDir);

					if (false == Directory.Exists(strTempDir))
					{
						MessageBox.Show(this, Properties.Resources.IDS_RIPPROCESS_ERRORTMP, 
                            Properties.Resources.IDS_RIPPROCESS_ERRORTMP_CAPTION, 
                            MessageBoxButtons.OK, MessageBoxIcon.Error);

						break;
					}

					// грабинг треков
					for (int i = 0; i < m_listTracks.Length; i++)
					{
						Invoke(new SetProgressDelegate(SetProgress), 0);
						Invoke(new SetTextDelegate(SetTextRip), String.Format(
                            Properties.Resources.IDS_RIPPROCESS_INFO, m_listTracks[i], i + 1, m_listTracks.Length));

						strTracks.Add(strTempDir + String.Format("out{0:D02}.wav", i + 1));

						AOPAPI.AOPAudioCDRip(m_listRealTracks[i], strTracks[i], RipAudioCDCallback, m_iSpeed);

						// выход из цикла, если была нажата кнопка Cancel
						if (false == btnCancel.Enabled)
						{
							break;
						}
					}

					// выход из цикла, если была нажата кнопка Cancel
					if (false == btnCancel.Enabled)
					{
						break;
					}

					// соединяем в один при необходимости
					if (m_bSingle)
					{
						Invoke(new SetTextDelegate(SetTextRip), String.Format(Properties.Resources.IDS_RIPPROCESS_MERGE));

						// создание выходного файла для слияния
						FileStream fsOut = File.Open(strTempDir + "single.wav", FileMode.Create);

						for (int i = 0; i < m_listTracks.Length; i++)
						{
							Invoke(new SetProgressDelegate(SetProgress), i * (1.0f / m_listTracks.Length));

							// открывает входной файл
							FileStream fsIn = File.Open(strTracks[i], FileMode.Open);

							fsIn.Seek(44, SeekOrigin.Begin);
							
							byte[] bTmp = new byte[65536 * 8];
							int iTotal = 0;
							int iRead;

							iRead = fsIn.Read(bTmp, 0, 65536 * 8);

							while (iRead > 0)
							{
								fsOut.Write(bTmp, 0, iRead);

								iTotal += iRead;

								Invoke(new SetProgressDelegate(SetProgress), (i + (float)iTotal / fsIn.Length) * 
                                    (1.0f / m_listTracks.Length));

								iRead = fsIn.Read(bTmp, 0, 65536 * 8);

								if (false == btnCancel.Enabled)
								{
									break;
								}
							}

							strTracks.Add(strTempDir + "single.wav");

							if (false == btnCancel.Enabled)
							{
								fsIn.Close();

								break;
							}

							// записываем WAV-header в fsOut
							if (m_listTracks.Length == (i + 1))
							{
								fsIn.Seek(0, SeekOrigin.Begin);
								fsOut.Seek(0, SeekOrigin.Begin);

								Byte[] bWavHeader = new Byte[44];

								fsIn.Read(bWavHeader, 0, 44);
								fsOut.Write(bWavHeader, 0, 44);
							}

							fsIn.Close();
						}

						if (false == btnCancel.Enabled)
						{
							fsOut.Close();

							break;
						}

						// правка заголовка выходного файла
						BinaryWriter bwOut = new BinaryWriter(fsOut);
						Int32        iLengthWav;

						iLengthWav = (Int32)fsOut.Length;
						bwOut.Seek(4, SeekOrigin.Begin);
						bwOut.Write(iLengthWav - 8);

						bwOut.Seek(40, SeekOrigin.Begin);
						bwOut.Write(iLengthWav - 44);

						bwOut.Close();

						fsOut.Close();
					}

					StreamWriter writePls;

					// создание CUE
					if (m_bSingle)
					{
						writePls = new StreamWriter(m_strOutDir + "\\" + m_strAlbumDir + ".cue", true, Encoding.Default);

						writePls.WriteLine("REM GENRE \"" + m_strGenre + "\"");
						writePls.WriteLine("REM DATE \"" + m_strYear + "\"");
						writePls.WriteLine("REM COMMENT \"Created by Audio One Pack\"");
						writePls.WriteLine("PERFORMER \"" + m_strArtist + "\"");
						writePls.WriteLine("TITLE \"" + m_strTitle + "\"");
					}
					// создание плейлиста
					else
					{
						writePls = new StreamWriter(m_strOutDir + "\\" + m_strAlbumDir + ".m3u", true, Encoding.Default);

						writePls.WriteLine("# Created by Audio One Pack");
					}

					// кодируем при необходимости
					switch (m_iCodec)
					{
						// WAV
						case 0:
							if (m_bSingle)
							{
								Invoke(new SetTextDelegate(SetTextRip), String.Format(
                                    Properties.Resources.IDS_RIPPROCESS_ENCODE, 1, 1));

								String strName = m_strArtist + " - " + m_strTitle + ".wav";

								AOPAPI.AOPEncodeWAV(strTracks[strTracks.Count - 1], m_strOutDir + "\\" + strName, delegateEncode);

								writePls.WriteLine("FILE \"" + strName + "\" WAVE");
							}
							else
							{
								for (int i = 0; i < strTracks.Count; i++)
								{
									Invoke(new SetTextDelegate(SetTextRip), String.Format(
                                        Properties.Resources.IDS_RIPPROCESS_ENCODE, i + 1, strTracks.Count));

									String strName = String.Format("{0:D02} - " + m_arrNameTracks[0][m_listTracks[i] - 1] + 
                                        " - " + m_arrNameTracks[1][m_listTracks[i] - 1] + ".wav", m_listTracks[i]);

									AOPAPI.AOPEncodeWAV(strTracks[i], m_strOutDir + "\\" + strName, delegateEncode);

									writePls.WriteLine(strName);

									if (false == btnCancel.Enabled)
									{
										break;
									}
								}
							}
							break;

						// MP3
						case 1:
							if (m_bSingle)
							{
								Invoke(new SetTextDelegate(SetTextRip), String.Format(
                                    Properties.Resources.IDS_RIPPROCESS_ENCODE, 1, 1));

								String strName = m_strArtist + " - " + m_strTitle + ".mp3";

								AOPAPI.AOPEncodeMP3(strTracks[strTracks.Count - 1], m_strOutDir + "\\" + 
                                    strName, m_iQuality, delegateEncode);

								// прописывание тегов
								ID3Info id3File = new ID3Info(m_strOutDir + "\\" + strName, true);

								id3File.ID3v1Info.HaveTag = true;

								id3File.ID3v1Info.Album = m_strTitle; 
								id3File.ID3v1Info.Artist = m_strArtist;
								id3File.ID3v1Info.Title = m_strTitle;
								id3File.ID3v1Info.Year = m_strYear;
								id3File.ID3v1Info.Comment = "by Audio One Pack";
								id3File.ID3v1Info.Genre = 255;

								id3File.ID3v2Info.HaveTag = true;

								id3File.ID3v2Info.SetMinorVersion(3);
								id3File.ID3v2Info.SetTextFrame("TALB", m_strTitle);
								id3File.ID3v2Info.SetTextFrame("TIT2", m_strTitle);
								id3File.ID3v2Info.SetTextFrame("TYER", m_strYear);
								id3File.ID3v2Info.SetTextFrame("TENC", "by Audio One Pack");
								id3File.ID3v2Info.SetTextFrame("TPE1", m_strArtist);
								id3File.ID3v2Info.SetTextFrame("TPE2", m_strArtist);
								id3File.ID3v2Info.SetTextFrame("TCON", m_strGenre);

								id3File.Save();

								writePls.WriteLine("FILE \"" + strName + "\" WAVE");
							}
							else
							{
								for (int i = 0; i < strTracks.Count; i++)
								{
									Invoke(new SetTextDelegate(SetTextRip), String.Format(
                                        Properties.Resources.IDS_RIPPROCESS_ENCODE, i + 1, strTracks.Count));

									String strName = String.Format("{0:D02} - " + m_arrNameTracks[0][m_listTracks[i] - 1] + 
                                        " - " + m_arrNameTracks[1][m_listTracks[i] - 1] + ".mp3", m_listTracks[i]);

									AOPAPI.AOPEncodeMP3(strTracks[i], m_strOutDir + "\\" + strName, m_iQuality, delegateEncode);

									// прописывание тегов
									ID3Info id3File = new ID3Info(m_strOutDir + "\\" + strName, true);

									id3File.ID3v1Info.HaveTag = true;

									id3File.ID3v1Info.Album = m_strTitle;
									id3File.ID3v1Info.Artist = m_arrNameTracks[0][m_listTracks[i] - 1].ToString();
									id3File.ID3v1Info.Title = m_arrNameTracks[1][m_listTracks[i] - 1].ToString();
									id3File.ID3v1Info.Year = m_strYear;
									id3File.ID3v1Info.TrackNumber = (byte)m_listTracks[i];
                                    id3File.ID3v1Info.Comment = "by Audio One Pack ";
									id3File.ID3v1Info.Genre = 255;

									id3File.ID3v2Info.HaveTag = true;

									id3File.ID3v2Info.SetMinorVersion(3);
									id3File.ID3v2Info.SetTextFrame("TPE2", m_strArtist);
									id3File.ID3v2Info.SetTextFrame("TALB", m_strTitle);
									id3File.ID3v2Info.SetTextFrame("TPE1", m_arrNameTracks[0][m_listTracks[i] - 1].ToString());
									id3File.ID3v2Info.SetTextFrame("TIT2", m_arrNameTracks[1][m_listTracks[i] - 1].ToString());
									id3File.ID3v2Info.SetTextFrame("TRCK", m_listTracks[i].ToString());
									id3File.ID3v2Info.SetTextFrame("TYER", m_strYear);
									id3File.ID3v2Info.SetTextFrame("TENC", "by Audio One Pack");
									id3File.ID3v2Info.SetTextFrame("TCON", m_strGenre);

									id3File.Save();

									writePls.WriteLine(strName);

									if (false == btnCancel.Enabled)
									{
										break;
									}
								}
							}
							break;

						// WMA
						case 2:
							if (m_bSingle)
							{
								Invoke(new SetTextDelegate(SetTextRip), String.Format(
                                    Properties.Resources.IDS_RIPPROCESS_ENCODE, 1, 1));

								String strName = m_strArtist + " - " + m_strTitle + ".wma";

								AOPAPI.AOPEncodeWMA(strTracks[strTracks.Count - 1], m_strOutDir + "\\" + 
                                    strName, m_strTitle, m_strArtist, m_strTitle, m_strGenre, m_strYear, m_iQuality, delegateEncode);

								writePls.WriteLine("FILE \"" + strName + "\" WAVE");
							}
							else
							{
								for (int i = 0; i < strTracks.Count; i++)
								{
									Invoke(new SetTextDelegate(SetTextRip), String.Format(
                                        Properties.Resources.IDS_RIPPROCESS_ENCODE, i + 1, strTracks.Count));

									String strName = String.Format("{0:D02} - " + m_arrNameTracks[0][m_listTracks[i] - 1] +
                                        " - " + m_arrNameTracks[1][m_listTracks[i] - 1] + ".wma", m_listTracks[i]);

									AOPAPI.AOPEncodeWMA(strTracks[i], m_strOutDir + "\\" + strName, 
                                        m_arrNameTracks[1][m_listTracks[i] - 1].ToString(), 
                                        m_arrNameTracks[0][m_listTracks[i] - 1].ToString(),
                                        m_strTitle, m_strGenre, m_strYear, m_iQuality, delegateEncode);

									writePls.WriteLine(strName);

									if (false == btnCancel.Enabled)
									{
										break;
									}
								}
							}
							break;

						// OGG
						case 3:
							if (m_bSingle)
							{
								Invoke(new SetTextDelegate(SetTextRip), String.Format(
                                    Properties.Resources.IDS_RIPPROCESS_ENCODE, 1, 1));

								String strName = m_strArtist + " - " + m_strTitle + ".ogg";

								AOPAPI.AOPEncodeOGG(strTracks[strTracks.Count - 1], m_strOutDir + "\\" + 
                                    strName, m_strTitle, m_strArtist, m_strTitle, m_strGenre, m_strYear,
                                    m_iQuality, delegateEncode);

								writePls.WriteLine("FILE \"" + strName + "\" WAVE");
							}
							else
							{
								for (int i = 0; i < strTracks.Count; i++)
								{
									Invoke(new SetTextDelegate(SetTextRip), String.Format(
                                        Properties.Resources.IDS_RIPPROCESS_ENCODE, i + 1, strTracks.Count));

									String strName = String.Format("{0:D02} - " + m_arrNameTracks[0][m_listTracks[i] - 1] + 
                                        " - " + m_arrNameTracks[1][m_listTracks[i] - 1] + ".ogg", m_listTracks[i]);

									AOPAPI.AOPEncodeOGG(strTracks[i], m_strOutDir + "\\" + strName, 
                                        m_arrNameTracks[1][m_listTracks[i] - 1].ToString(), 
                                        m_arrNameTracks[0][m_listTracks[i] - 1].ToString(), 
                                        m_strTitle, m_strGenre, m_strYear, m_iQuality, delegateEncode);

									writePls.WriteLine(strName);

									if (false == btnCancel.Enabled)
									{
										break;
									}
								}
							}
							break;

						// FLAC
						case 4:
							if (m_bSingle)
							{
								Invoke(new SetTextDelegate(SetTextRip), String.Format(
                                    Properties.Resources.IDS_RIPPROCESS_ENCODE, 1, 1));

								String strName = m_strArtist + " - " + m_strTitle + ".flac";

								AOPAPI.AOPEncodeFLAC(strTracks[strTracks.Count - 1], m_strOutDir + "\\" + strName, delegateEncode);

								writePls.WriteLine("FILE \"" + strName + "\" WAVE");
							}
							else
							{
								for (int i = 0; i < strTracks.Count; i++)
								{
									Invoke(new SetTextDelegate(SetTextRip), String.Format(
                                        Properties.Resources.IDS_RIPPROCESS_ENCODE, i + 1, strTracks.Count));

									String strName = String.Format("{0:D02} - " + m_arrNameTracks[0][m_listTracks[i] - 1] + 
                                        " - " + m_arrNameTracks[1][m_listTracks[i] - 1] + ".flac", m_listTracks[i]);

									AOPAPI.AOPEncodeFLAC(strTracks[i], m_strOutDir + "\\" + strName, delegateEncode);

									writePls.WriteLine(strName);

									if (false == btnCancel.Enabled)
									{
										break;
									}
								}
							}
							break;

						// APE
						case 5:
							if (m_bSingle)
							{
								Invoke(new SetTextDelegate(SetTextRip), String.Format(
                                    Properties.Resources.IDS_RIPPROCESS_ENCODE, 1, 1));

								String strName = m_strArtist + " - " + m_strTitle + ".ape";

								AOPAPI.AOPEncodeAPE(strTracks[strTracks.Count - 1], m_strOutDir + "\\" + strName, delegateEncode);

								writePls.WriteLine("FILE \"" + strName + "\" WAVE");
							}
							else
							{
								for (int i = 0; i < strTracks.Count; i++)
								{
									Invoke(new SetTextDelegate(SetTextRip), String.Format(
                                        Properties.Resources.IDS_RIPPROCESS_ENCODE, i + 1, strTracks.Count));

									String strName = String.Format("{0:D02} - " + m_arrNameTracks[0][m_listTracks[i] - 1] + 
                                        " - " + m_arrNameTracks[1][m_listTracks[i] - 1] + ".ape", m_listTracks[i]);

									AOPAPI.AOPEncodeAPE(strTracks[i], m_strOutDir + "\\" + strName, delegateEncode);

									writePls.WriteLine(strName);

									if (false == btnCancel.Enabled)
									{
										break;
									}
								}
							}
							break;

					    // TTA
                        //case 6:
                        //    if (m_bSingle)
                        //    {
                        //        Invoke(new SetTextDelegate(SetTextRip), String.Format(Properties.Resources.IDS_RIPPROCESS_ENCODE, 1, 1));

                        //        String strName = m_strArtist + " - " + m_strTitle + ".tta";

                        //        AOPAPI.AOPEncodeTTA(strTracks[strTracks.Count - 1], m_strOutDir + "\\" + strName, delegateEncode);

                        //        writePls.WriteLine("FILE \"" + strName + "\" WAVE");
                        //    }
                        //    else
                        //    {
                        //        for (int i = 0; i < strTracks.Count; i++)
                        //        {
                        //            Invoke(new SetTextDelegate(SetTextRip), String.Format(Properties.Resources.IDS_RIPPROCESS_ENCODE, i + 1, strTracks.Count));

                        //            String strName = String.Format("{0:D02} - " + m_arrNameTracks[0][m_listTracks[i] - 1] + " - " + m_arrNameTracks[1][m_listTracks[i] - 1] + ".tta", m_listTracks[i]);

                        //            AOPAPI.AOPEncodeTTA(strTracks[i], m_strOutDir + "\\" + strName, delegateEncode);

                        //            writePls.WriteLine(strName);

                        //            if (false == btnCancel.Enabled)
                        //            {
                        //                break;
                        //            }
                        //        }
                        //    }
                        //    break;

						// WV
						case 7:
							if (m_bSingle)
							{
								Invoke(new SetTextDelegate(SetTextRip), String.Format(
                                    Properties.Resources.IDS_RIPPROCESS_ENCODE, 1, 1));

								String strName = m_strArtist + " - " + m_strTitle + ".wv";

								AOPAPI.AOPEncodeWV(strTracks[strTracks.Count - 1], m_strOutDir + "\\" + strName, delegateEncode);

								writePls.WriteLine("FILE \"" + strName + "\" WAVE");
							}
							else
							{
								for (int i = 0; i < strTracks.Count; i++)
								{
									Invoke(new SetTextDelegate(SetTextRip), String.Format(
                                        Properties.Resources.IDS_RIPPROCESS_ENCODE, i + 1, strTracks.Count));

									String strName = String.Format("{0:D02} - " + m_arrNameTracks[0][m_listTracks[i] - 1] + 
                                        " - " + m_arrNameTracks[1][m_listTracks[i] - 1] + ".wv", m_listTracks[i]);

									AOPAPI.AOPEncodeWV(strTracks[i], m_strOutDir + "\\" + strName, delegateEncode);

									writePls.WriteLine(strName);

									if (false == btnCancel.Enabled)
									{
										break;
									}
								}
							}
							break;
					}

					if (false == btnCancel.Enabled)
					{
						writePls.Close();

						break;
					}

					// закрываем плейлист/CUE
					if (m_bSingle)
					{
						int iFullLength = 0;

						for (int i = 0; i < m_listTracks.Length; i++)
						{
							writePls.WriteLine(String.Format("  TRACK {0:D02} AUDIO", i + 1));
							writePls.WriteLine("    TITLE \"" + m_arrNameTracks[1][m_listTracks[i] - 1].ToString() + "\"");
							writePls.WriteLine("    PERFORMER \"" + m_arrNameTracks[0][m_listTracks[i] - 1].ToString() + "\"");
							writePls.WriteLine("    FLAGS DCP");
							writePls.WriteLine(String.Format("    INDEX 01 {0:D02}:{1:D02}:{2:D02}", 
                                (iFullLength / 75) / 60, (iFullLength / 75) % 60, iFullLength % 75));

							iFullLength += (int)m_arrLengthInFrames[m_listTracks[i] - 1];
						}
					}

					writePls.Close();

					DialogResult = DialogResult.OK;

					break;
				}
			}
			
			catch (System.Exception exp)
			{
				MessageBox.Show(exp.Message);

                DialogResult = DialogResult.Ignore;
			}
			
			finally
			{
				if (false == btnCancel.Enabled)
				{
					DialogResult = DialogResult.Cancel;
				}

				// удаление полученных файлов при необходимости
				if (DialogResult.Cancel == DialogResult)
				{
					string[] arrFiles = Directory.GetFiles(m_strOutDir);

					foreach (string strFile in arrFiles)
					{
						try
						{
							File.Delete(strFile);
						}
						catch (System.Exception exp)
						{
							MessageBox.Show(exp.Message);
						}
					}

					try
					{
						Directory.Delete(m_strOutDir);
					}
					catch (System.Exception exp)
					{
						MessageBox.Show(exp.Message);
					}
				}

				// удаление временных файлов
				foreach (String strTrack in strTracks)
				{
					try
					{
						File.Delete(strTrack);
					}
					catch (System.Exception exp)
					{
						MessageBox.Show(exp.Message);
					}
				}

				// удаление временной директории
				try
				{
					Directory.Delete(strTempDir);
				}
				catch (System.Exception exp)
				{
					MessageBox.Show(exp.Message);
				}

				// освобождение ресурсов
				if (0 != AOPAPI.AOPAudioCDFree())
				{
					MessageBox.Show("ERROR::AOPAudioCDFree", "ERROR", 
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
				}
			}

			//Invoke(new DelegateNoParam(Close));
		}

		/// <summary>
		/// Callback функция грабинга.
		/// </summary>
		/// <param name="uiAction"></param>
		/// <param name="uiParamOne"></param>
		/// <param name="uiParamTwo"></param>
		private void RipAudioCDCallback(Int32 uiAction, Int32 uiParamOne, Int32 uiParamTwo)
		{
			switch (uiAction)
			{
				case (int)AOPAPI.AudioEnum.AUDIORIP_READ:
					Invoke(new SetProgressDelegate(SetProgress), (float)(uiParamOne / 100.0));
					break;
			}
		}

		/// <summary>
		/// Установка progressRip.
		/// </summary>
		/// <param name="fPercent"></param>
		private void SetProgress(float fPercent)
		{
			int iValue = progressRip.Minimum + (int)((progressRip.Maximum - progressRip.Minimum) * fPercent);

			if (iValue < progressRip.Minimum)
			{
				progressRip.Value = progressRip.Minimum;
			}
			else if (iValue > progressRip.Maximum)
			{
				progressRip.Value = progressRip.Maximum;
			}
			else
			{
				progressRip.Value = iValue;
			}
		}

		/// <summary>
		/// Установка текста в окно риппинга.
		/// </summary>
		/// <param name="strRip"></param>
		private void SetTextRip(String strRip)
		{
			textRip.Text = strRip;
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
					Invoke(new SetProgressDelegate(SetProgress), (float)(uiParamOne) / uiParamTwo);
					break;
			}
		}

		/// <summary>
		/// Отмена всех действий.
		/// </summary>
		private void Cancel(object sender, EventArgs e)
		{
			// дизаблим кнопку Cancel
			btnCancel.Enabled = false;

			// отмена риппинга
			AOPAPI.AOPAudioCDRipCancel();
		}
	}
}