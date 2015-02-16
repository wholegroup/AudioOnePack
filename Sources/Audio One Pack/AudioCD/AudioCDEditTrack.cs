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
    public partial class EditNameTrack : Form
    {
        ListViewItem                            m_itemRename;
        ListView.SelectedListViewItemCollection m_lvSelected;

        /// <summary>
        /// Конструктор по-умолчанию
        /// </summary>
        public EditNameTrack()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Конструктор с переименовываемым элементом.
        /// </summary>
        /// <param name="itemRename"></param>
        public EditNameTrack(ListViewItem itemRename, ListView.SelectedListViewItemCollection lvSelected)
         : this()
        {
            m_itemRename = itemRename;
                m_lvSelected = lvSelected;

            textArtist.Text = itemRename.SubItems[1].Text;
            textTitle.Text  = itemRename.SubItems[2].Text;
        }

		/// <summary>
		/// Закрытие формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Close(object sender, EventArgs e)
		{
			this.Close();
		}

		/// <summary>
		/// Изменение названия трека и закрытие формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Rename(object sender, EventArgs e)
		{
			if ((true == cbChangeAll.Checked) && (null != m_lvSelected))
			{
				for (int i = 0; i < m_lvSelected.Count; i++)
				{
					m_lvSelected[i].SubItems[1].Text = textArtist.Text;
				}
			}

			m_itemRename.SubItems[1].Text = textArtist.Text;
			m_itemRename.SubItems[2].Text = textTitle.Text;

         this.Close();
		}
	}
}

