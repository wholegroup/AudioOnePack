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
using System.Runtime.Remoting.Messaging;

using Freedb;

namespace AudioOnePack
{
	public partial class RipFreeDb : Form
	{
		/// <summary>
		/// делегат без параметров.
		/// </summary>
		private delegate void DelegateNoParam();
		
		/// <summary>
		/// Ссылка на главную форму приложения.
		/// </summary>
		private AOPForm m_formAOP;

		/// <summary>
		/// Ссылка на форму RipCD.
		/// </summary>
		private RipCDForm m_formRipCD;

		/// <summary>
		/// Идентификатор CDDB.
		/// </summary>
		private string m_strCDDB;

		/// <summary>
		/// Название исполнителя диска.
		/// </summary>
		private String m_strArtist;

		/// <summary>
		/// Название диска.
		/// </summary>
		private String m_strTitle;

		/// <summary>
		/// Жанр.
		/// </summary>
		private String m_strGenre;

		/// <summary>
		/// Год.
		/// </summary>
		private String m_strYear;

		/// <summary>
		/// Исполнители треков.
		/// </summary>
		private ArrayList m_arrArtistTracks = new ArrayList();

		/// <summary>
		/// Наименования треков.
		/// </summary>
		private ArrayList m_arrTitleTracks = new ArrayList();

		/// <summary>
		/// конструктор
		/// </summary>
		public RipFreeDb()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Конструктор с передачей ссылки на главную форму и форму RipCD
		/// </summary>
		/// <param name="formAOP"></param>
		/// <param name="formRipCD"></param>
		public RipFreeDb(AOPForm formAOP, RipCDForm formRipCD, string strCDDB)
			: this()
		{
			m_formAOP   = formAOP;
			m_formRipCD = formRipCD;
			m_strCDDB   = strCDDB;
		}

        /// <summary>
		/// Обработка первого показа формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ShowForm(object sender, EventArgs e)
		{
			(new DelegateNoParam(GetInfo)).BeginInvoke(null, null);
		}

		/// <summary>
		/// Получение инфы
		/// </summary>
		void GetInfo()
		{
			try
			{
				FreedbHelper      freedb = new FreedbHelper();
				QueryResult       queryResult;
				List<QueryResult> coll;
				string            code = string.Empty;
				CDEntry           cdEntry;

				// инициализация
				freedb.UserName   = "AudioOnePack";
				freedb.ClientName = "AudioOnePack";
				freedb.Hostname   = "www.WholeGroup.com";
				freedb.Version    = "1.0";

				// запрос
				try
				{
					code = freedb.Query(m_strCDDB, out queryResult, out coll);
				}
				catch (Exception ex)
				{
					throw new Exception(Properties.Resources.IDS_RIPFREEDB_ERRORCDDB + ex.Message);
				}

				if (FreedbHelper.ResponseCodes.CODE_210 == code ||
					FreedbHelper.ResponseCodes.CODE_211 == code)
				{
					queryResult = coll[0];
				}
				else 
					
				if (FreedbHelper.ResponseCodes.CODE_200 != code)
				{
					throw new Exception(Properties.Resources.IDS_RIPFREEDB_ERRORQUERY + code);
				}
	
				// парсинг 
				code = freedb.Read(queryResult, out cdEntry);

				if (code != FreedbHelper.ResponseCodes.CODE_210)
				{
					throw new Exception(Properties.Resources.IDS_RIPFREEDB_ERRORRESULT + code);
				}

				// сохранение
				m_strArtist = cdEntry.Artist;
				m_strTitle  = cdEntry.Title;
				m_strGenre  = cdEntry.Genre;
				m_strYear   = cdEntry.Year;

				for (int i = 0; i < cdEntry.Tracks.Count; i++)
				{
					m_arrArtistTracks.Add(cdEntry.Tracks[i].Artist);
					m_arrTitleTracks.Add(cdEntry.Tracks[i].Title);
				}

                Invoke(new DelegateNoParam(Close));
            }

			catch (System.Exception e)
			{
				MessageBox.Show(e.Message);

				this.DialogResult = DialogResult.Ignore;
			}
		}

		/// <summary>
		/// Обработка закрытия формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void CloseForm(object sender, FormClosedEventArgs e)
		{
			if (DialogResult.Ignore != this.DialogResult)
			{
				m_formRipCD.SetDiskArtist    (m_strArtist);
				m_formRipCD.SetDiskTitle     (m_strTitle);
				m_formRipCD.SetDiskGenre     (m_strGenre);
				m_formRipCD.SetDiskYear      (m_strYear);
				m_formRipCD.SetDiskNameTracks(m_arrArtistTracks, m_arrTitleTracks);
			}
		}
	}
}