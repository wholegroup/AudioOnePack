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

namespace AudioOnePack
{
	//
	public partial class AnalyzerProcess : Form
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
		AOPForm m_formAOP;

		/// <summary>
		/// Ссылка на форму анализа музыки.
		/// </summary>
		AnalyzerForm m_formAnalyzer;

		/// <summary>
		/// Список с информацией о треках для конвертирования.
		/// </summary>
		private ArrayList m_arrTracks = new ArrayList();

		/// <summary>
		/// Номер обрабатываемого файла.
		/// </summary>
		private int m_iCurNumberFile = 0;
		
		/// <summary>
		/// Флаг остановки конвертирования.
		/// </summary>
		private Boolean m_bStop = false;
		
		/// <summary>
		/// Конструктор по-умолчанию.
		/// </summary>
		public AnalyzerProcess()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Конструктор с передачей ссылок на главную форму и форму анализа музыки.
		/// </summary>
		/// <param name="formAOP"></param>
		/// <param name="formAnalyzer"></param>
		public AnalyzerProcess(AOPForm formAOP, AnalyzerForm formAnalyzer, ArrayList arrTracks)
			: this()
		{
			m_formAOP      = formAOP;
			m_formAnalyzer = formAnalyzer;
			m_arrTracks    = arrTracks;
		}

		/// <summary>
		/// Остановка анализа.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Stop(object sender, EventArgs e)
		{
			m_bStop = true;
			btnStop.Enabled = false;
		}

		/// <summary>
		/// Обработка первого показа формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ShowForm(object sender, EventArgs e)
		{
			// запуск процесса риппинга
			(new DelegateNoParam(Analyzing)).BeginInvoke(null, null);
		}

		/// <summary>
		/// Процесс анализа
		/// </summary>
		private void Analyzing()
		{
			AOPAPI.AnalyzeCallbackDelegate delegateAnalyzing = new AOPAPI.AnalyzeCallbackDelegate(AnalyzingCallback);

			try
			{
				while (true)
				{
					for (int i = 0; i < m_arrTracks.Count; i++)
					{
						// номер обрабатываемого трека
						m_iCurNumberFile = i;

						// вывод информации о анализе
						Invoke(new SetTextDelegate(SetTextOne), String.Format(
							Properties.Resources.IDS_ANALYZEPROCESS_CURRENTFILE, 
							((AnalyzerForm.TRACKITEM)m_arrTracks[i]).strFilename));
						Invoke(new SetTextDelegate(SetTextAll), String.Format(
							Properties.Resources.IDS_ANALYZEPROCESS_ANALYZE, i + 1, m_arrTracks.Count));

						// анализ очередного файла
						float fK = -1;

						AOPAPI.AOPAnalyzerTrack(((AnalyzerForm.TRACKITEM)m_arrTracks[i]).strPath, ref fK, delegateAnalyzing);

						AnalyzerForm.TRACKITEM tI = (AnalyzerForm.TRACKITEM)m_arrTracks[i];
						tI.fK = fK;

						// выход, если была нажата кнопка останова
						if (true == m_bStop)
						{
							break;
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
		private void AnalyzingCallback(Int32 uiAction, Int32 uiParamOne, Int32 uiParamTwo)
		{
			Invoke(new SetProgressDelegate(SetProgressOne), (float)(uiParamOne) / uiParamTwo);
			Invoke(new SetProgressDelegate(SetProgressAll), (float)(uiParamOne) / uiParamTwo / m_arrTracks.Count + 
				(float)m_iCurNumberFile / m_arrTracks.Count);
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

