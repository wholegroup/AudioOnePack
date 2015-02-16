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

namespace AudioOnePack
{
    //
	public partial class DiscInfoForm : Form
	{
		/// <summary>
		/// Информация о выбранном CD/DVD приводе.
		/// </summary>
		AOPAPI.DEVICEINFO m_devInfo;
		 
		/// <summary>
		/// Информация о диске.
		/// </summary>
		AOPAPI.DISCINFO m_discInfo = new AOPAPI.DISCINFO();

		/// <summary>
		/// Делегат без параметров.
		/// </summary>
		public delegate void DelegateNoParam();

		/// <summary>
		/// Конструктор.
		/// </summary>
		public DiscInfoForm()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Конструктор с передачей ссылки на структуру с информацией о приводе.
		/// </summary>
		public DiscInfoForm(AOPAPI.DEVICEINFO devInfo)
			: this()
		{
			m_devInfo = devInfo;
		}

		/// <summary>
		/// Обработка нажатия кнопки OK.
		/// </summary>
		private void OnOk(object sender, EventArgs e)
		{
			Close();
		}

		/// <summary>
		/// Обработка нажатия кнопки Refresh.
		/// </summary>
		private void Refresh(object sender, EventArgs e)
		{
			btnRefresh.Enabled = false;
			btnOK.Enabled      = false;

			(new DelegateNoParam(GetDiscInfo)).BeginInvoke(null, null);
		}

		/// <summary>
		/// Обработка первого показа формы.
		/// </summary>
		private void FirstShow(object sender, EventArgs e)
		{
			btnRefresh.Enabled = false;
			btnOK.Enabled      = false;

			(new DelegateNoParam(GetDiscInfo)).BeginInvoke(null, null);
		}

		/// <summary>
		/// Устанавливает курсор ожидания.
		/// </summary>
		private void CursorWait()
		{
			this.Cursor = System.Windows.Forms.Cursors.WaitCursor;
		}

		/// <summary>
		/// Устанавливает курсор по-умолчанию.
		/// </summary>
		private void CursorDefault()
		{
			this.Cursor = System.Windows.Forms.Cursors.Default;
		}

		/// <summary>
		/// Получение информации о треке (Callback)
		/// </summary>
		public uint TocInfoCallback(AOPAPI.TOCINFO tocInfo)
		{
			Invoke(new SetTrackInfoDelegate(SetTrackInfo), tocInfo);

			return 0;
		}

		/// <summary>
		/// Получение полной информации о диске.
		/// </summary>
		private void GetDiscInfo()
		{
			Invoke(new DelegateNoParam(CursorWait));

			AOPAPI.AOPGetDiscInfo(ref m_devInfo, out m_discInfo, TocInfoCallback);

			Invoke(new DelegateNoParam(EndGetDiskInfo));

			Invoke(new DelegateNoParam(CursorDefault));
		}

		/// <summary>
		/// Вывод полученной информации о диске.
		/// </summary>
		private void EndGetDiskInfo()
		{
			// инфа о диске
			labelDiscType.Text  = m_discInfo.strDiscType;
			labelUsedSpace.Text = m_discInfo.iUsedSpace.ToString();
			labelFreeSpace.Text = m_discInfo.iFreeSpace.ToString();
			labelSessions.Text  = treeDiscInfo.Nodes[0].Nodes.Count.ToString();

			// инфа о дорожках
			int iTracks = 0;

			for (int i = 0; i < treeDiscInfo.Nodes[0].Nodes.Count; i++)
			{
				iTracks += treeDiscInfo.Nodes[0].Nodes[i].Nodes.Count;
			}

			labelTracks.Text = iTracks.ToString();

			treeDiscInfo.Nodes[0].Text = labelDiscType.Text;

			// раскрытие дерева с информацией о дорожках
			treeDiscInfo.ExpandAll();

			// включение кнопок Refresh и OK
			btnRefresh.Enabled = true;
			btnOK.Enabled      = true;
		}

		/// <summary>
		/// Делегат для установки информации о дорожке.
		/// </summary>
		/// <param name="tocInfo"></param>
		private delegate void SetTrackInfoDelegate(AOPAPI.TOCINFO tocInfo);

		/// <summary>
		/// Установка информации о дорожке.
		/// </summary>
		private void SetTrackInfo(AOPAPI.TOCINFO tocInfo)
		{
			if (treeDiscInfo.Nodes[0].Nodes.Count < tocInfo.ucSessionNumber)
			{
				treeDiscInfo.Nodes[0].Nodes.Add(String.Format("Session {0:D}", 
                    tocInfo.ucSessionNumber.ToString()));
			}

			string strTrack;

			strTrack = "Track " + string.Format("{0:D02}", tocInfo.ucTrackNumber) + ": ";

			if (0 == tocInfo.ucTrackMode)
			{
				int uiStartLBASec  = tocInfo.iStartingLBA / 75;
				int uiFinishLBASec = tocInfo.iEndingLBA   / 75;

				strTrack += string.Format("Start: {0:D02}:{1:D02}  Finish: {2:D02}:{3:D02}  " + 
                    "Length: {4:D02}:{5:D02}, ", (int)uiStartLBASec / 60, uiStartLBASec % 60, 
                    (int)uiFinishLBASec / 60, uiFinishLBASec % 60, (int)(uiFinishLBASec - uiStartLBASec) / 60, 
                    (uiFinishLBASec - uiStartLBASec) % 60);
			}

			strTrack += string.Format("Size: {0:F2} Mb", (float)(tocInfo.iEndingLBA - tocInfo.iStartingLBA) * 
                tocInfo.uiLBSizeInUCHARs / (1024 * 1024));

			treeDiscInfo.Nodes[0].Nodes[tocInfo.ucSessionNumber - 1].Nodes.Add(strTrack);
		}
	}
}