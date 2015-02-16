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
	public partial class AudioCDOptions : Form
	{
		/// <summary>
		/// Ссылка на главную форму.
		/// </summary>
		private AOPForm m_formAOP;

		/// <summary>
		/// Конструктор по-умолчанию.
		/// </summary>
		public AudioCDOptions()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Конструктор с передачей ссылки на главную форму.
		/// </summary>
		public AudioCDOptions(AOPForm formAOP)
			: this()
		{
			m_formAOP = formAOP;

			// инициализация контролов формы
			textFolder.Text              = m_formAOP.TempPath;
			cbLoadTray.Checked           = m_formAOP.bAudioCDLoadTray;
			cbClearListAfterBurn.Checked = m_formAOP.bClearListAfterBurn;
		}

		/// <summary>
		/// Принять изменения.
		/// </summary>
		private void OnOK(object sender, EventArgs e)
		{
			m_formAOP.TempPath            = textFolder.Text;
			m_formAOP.bAudioCDLoadTray    = cbLoadTray.Checked;
			m_formAOP.bClearListAfterBurn = cbClearListAfterBurn.Checked;

			Close();
		}

		/// <summary>
		/// Отменить изменения.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void OnCancel(object sender, EventArgs e)
		{
			Close();
		}

		/// <summary>
		/// Выбор каталога для создания временных файлов.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void SelectFolder(object sender, EventArgs e)
		{
			folderBrowser.SelectedPath = textFolder.Text;

			if (DialogResult.OK == folderBrowser.ShowDialog())
			{
				textFolder.Text = folderBrowser.SelectedPath;
			}
		}
	}
}

