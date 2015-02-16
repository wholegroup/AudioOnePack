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
	public partial class ConvertOptions : Form
	{
		/// <summary>
		/// Ссылка на главную форму.
		/// </summary>
		AOPForm m_formAOP;

		/// <summary>
		/// Конструктор по умолчанию.
		/// </summary>
		public ConvertOptions()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Конструктор с передачей ссылки на главное окно.
		/// </summary>
		/// <param name="formAOP"></param>
		public ConvertOptions(AOPForm formAOP)
			: this()
		{
			m_formAOP = formAOP;

			if (true == m_formAOP.bConvertDestinationDir)
			{
				rbNotDestination.Checked = false;
				rbDestination.Checked = true;
			}
			else
			{
				rbNotDestination.Checked = true;
				rbDestination.Checked = false;
			}

			cbNotRequestOutput.Checked = m_formAOP.bConvertNotRequestOutput;
			textOutput.Text = m_formAOP.strConvertOutPath;
			ClickNotRequest(null, null);

			cbDelete.Checked = m_formAOP.bConvertDelete;
		}

		/// <summary>
		/// Обработка нажатия кнопки "OK".
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void OnOK(object sender, EventArgs e)
		{
			if (true == rbNotDestination.Checked)
			{
				m_formAOP.bConvertDestinationDir = false;
			}
			else
			{
				m_formAOP.bConvertDestinationDir = true;
			}
			
			m_formAOP.bConvertNotRequestOutput = cbNotRequestOutput.Checked;
			m_formAOP.strConvertOutPath = textOutput.Text;

			m_formAOP.bConvertDelete = cbDelete.Checked;

			Close();
		}

		/// <summary>
		/// Обработка нажатия кнопки "Cancel".
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void OnCancel(object sender, EventArgs e)
		{
			Close();
		}

		/// <summary>
		/// Выбор выходной директории.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ClickBtnOutput(object sender, EventArgs e)
		{
			folderBrowser.SelectedPath = textOutput.Text;

			if (DialogResult.OK == folderBrowser.ShowDialog())
			{
				textOutput.Text = folderBrowser.SelectedPath;
			}
		}

		/// <summary>
		/// Обработка cbNotRequestOutput.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ClickNotRequest(object sender, EventArgs e)
		{
			if (true == cbNotRequestOutput.Checked)
			{
				textOutput.ReadOnly = false;
				btnSetOutput.Enabled = true;
			}
			else
			{
				textOutput.ReadOnly = true;
				btnSetOutput.Enabled = false;
			}
		}
	}
}