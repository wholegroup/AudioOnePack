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
using System.Threading;
using System.Runtime.InteropServices;

namespace AudioOnePack
{
	public partial class ScanDisk : Form
	{
		/// <summary>
		/// Делегат без параметров.
		/// </summary>
		public delegate void DelegateNoParam();

		/// <summary>
		/// ссылка на главную форму.
		/// </summary>
		AOPForm m_formAOP;

		/// <summary>
		/// список устройств.
		/// </summary>
		private List<AOPAPI.DEVICEINFO> m_listDevice;

		/// <summary>
		/// список информации о дисках в приводах.
		/// </summary>
		private List<AOPAPI.DISCINFO> m_listDiscInfo;

		/// <summary>
		/// список дорожек всех дисков в приводах.
		/// </summary>
		private List<List<AOPAPI.TOCINFO>> m_listAllToc;

		/// <summary>
		/// Список доступных скоростей чтения.
		/// </summary>
		private List<List<String>> m_listReadSpeed;

		/// <summary>
		/// Список доступных скоростей записи.
		/// </summary>
		private List<List<String>> m_listWriteSpeed;

		/// <summary>
		/// Диск для получения информации.
		/// </summary>
		private String m_strLetter = "";
		
		/// <summary>
		/// Текущий порядковый номер обрабатываемого диска.
		/// </summary>
		private int m_iDisc;

		/// <summary>
		/// Конструктор.
		/// </summary>
		public ScanDisk()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Конструктор с передачей ссылки на главную форму.
		/// </summary>
		/// <param name="formAOP"></param>
		public ScanDisk(AOPForm formAOP)
			: this()
		{
			m_formAOP = formAOP;

			m_listDevice     = m_formAOP.GetListDevices();
			m_listDiscInfo   = m_formAOP.GetDiscInfo();
			m_listAllToc     = m_formAOP.GetAllToc();
			m_listReadSpeed  = m_formAOP.GetReadSpeed();
			m_listWriteSpeed = m_formAOP.GetWriteSpeed();
		}

		/// <summary>
		/// Конструктор с передачей ссылки на главную форму и букву привода для сканирования.
		/// </summary>
		/// <param name="formAOP"></param>
		/// <param name="strLetter"></param>
		public ScanDisk(AOPForm formAOP, String strLetter)
			:this(formAOP)
		{
			m_strLetter = strLetter;
		}

		/// <summary>
		/// Обработка первого показа формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ShowForm(object sender, EventArgs e)
		{
			(new DelegateNoParam(GetDiscInfo)).BeginInvoke(null, null);
		}

		/// <summary>
		/// Получение информации о треке (Callback).
		/// </summary>
		/// <param name="tocInfo"></param>
		/// <returns></returns>
		public uint TocInfoCallback(AOPAPI.TOCINFO tocInfo)
		{
			m_listAllToc[m_iDisc].Add(tocInfo);

			return 0;
		}

		/// <summary>
		/// Получение полной информации о диске.
		/// </summary>
		private void GetDiscInfo()
		{
			//if ("" == m_strLetter)
			if (true)
			{
				for (m_iDisc = 0; m_iDisc < m_listDevice.Count; m_iDisc++)
				{
					AOPAPI.DEVICEINFO devInfo  = m_listDevice[m_iDisc];
					AOPAPI.DISCINFO   discInfo = m_listDiscInfo[m_iDisc];

					if (("" == m_strLetter) || (m_strLetter == devInfo.strLetter))
					{
						// получение информации о диске
						m_listAllToc[m_iDisc].Clear();

						AOPAPI.AOPGetDiscInfo(ref devInfo, out discInfo, TocInfoCallback);

						// получение скоростей чтения и записи
						IntPtr   ptrSpeeds = Marshal.AllocHGlobal(400);
						string   strSpeeds;
						string[] arrSpeeds;

						// чтение
						m_listReadSpeed[m_iDisc].Clear();

						AOPAPI.AOPGetReadSpeeds(ref devInfo, ptrSpeeds);

						strSpeeds = Marshal.PtrToStringUni(ptrSpeeds);
						arrSpeeds = strSpeeds.Split(new char[] { ';' });

						for (int i = 0; i < arrSpeeds.Length; i++)
						{
							if (arrSpeeds[i].Length > 0)
							{
								m_listReadSpeed[m_iDisc].Add(arrSpeeds[i]);
							}
						}

						// запись
						m_listWriteSpeed[m_iDisc].Clear();

						AOPAPI.AOPGetWriteSpeeds(ref devInfo, ptrSpeeds);

						strSpeeds = Marshal.PtrToStringUni(ptrSpeeds);
						arrSpeeds = strSpeeds.Split(new char[] { ';' });

						for (int i = 0; i < arrSpeeds.Length; i++)
						{
							if (arrSpeeds[i].Length > 0)
							{
								m_listWriteSpeed[m_iDisc].Add(arrSpeeds[i]);
							}
						}

						Marshal.FreeHGlobal(ptrSpeeds);
					}
				}
			}

			Invoke(new DelegateNoParam(Close));
		}
	}
}