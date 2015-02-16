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
	public partial class RipOptions : Form
	{
		/// <summary>
		/// Ссылка на главную форму.
		/// </summary>
		AOPForm m_formAOP;

		/// <summary>
		/// Конструктор по-умолчанию.
		/// </summary>
		public RipOptions()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Конструктор с передачей ссылки на главную формы.
		/// </summary>
		/// <param name="formAOP"></param>
		public RipOptions(AOPForm formAOP)
			: this()
		{
			m_formAOP = formAOP;
		}

		/// <summary>
		/// Обработка нажатия Ok.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void OnOk(object sender, EventArgs e)
		{
			if (rbNever.Checked)
			{
				m_formAOP.iRipGetFreeDB = 0;
			}
			else
			if (rbAsk.Checked)
			{
				m_formAOP.iRipGetFreeDB = 1;
			}
			else
			if (rbAllways.Checked)
			{
				m_formAOP.iRipGetFreeDB = 2;
			}

			m_formAOP.bRipEject            = cbEject.Checked;
			m_formAOP.bRipOpenDir          = cbOpenDir.Checked;

			m_formAOP.bRipNotRequestOutput = cbNotRequestOutput.Checked;
			m_formAOP.strRipOutPath        = textOutput.Text;
			m_formAOP.TempPath             = textTemp.Text;

			Close();
		}

		/// <summary>
		/// Обработка нажатия Cancel.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void OnCancel(object sender, EventArgs e)
		{
			Close();
		}

		/// <summary>
		/// Загрузка формы.
		/// </summary>
		private void LoadForm(object sender, EventArgs e)
		{
			switch (m_formAOP.iRipGetFreeDB)
			{
				case 0:
					rbNever.Checked   = true;
					rbAsk.Checked     = false;
					rbAllways.Checked = false;
					break;

				case 1:
					rbNever.Checked   = false;
					rbAsk.Checked     = true;
					rbAllways.Checked = false;
					break;

				case 2:
					rbNever.Checked   = false;
					rbAsk.Checked     = false;
					rbAllways.Checked = true;
					break;
			}

			cbEject.Checked   = m_formAOP.bRipEject;
			cbOpenDir.Checked = m_formAOP.bRipOpenDir;

			cbNotRequestOutput.Checked = m_formAOP.bRipNotRequestOutput;
			ClickNotRequest(null, null);
			
			textOutput.Text = m_formAOP.strRipOutPath;
			textTemp.Text   = m_formAOP.TempPath;
		}

		/// <summary>
		/// обработка клика cbNotRequest.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ClickNotRequest(object sender, EventArgs e)
		{
			if (cbNotRequestOutput.Checked)
			{
				textOutput.ReadOnly  = false;
				btnSetOutput.Enabled = true;
			}
			else
			{
				textOutput.ReadOnly  = true;
				btnSetOutput.Enabled = false;
			}
		}

		/// <summary>
		/// Выбор выходного пути.
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
		/// Выбор временного пути.
		/// </summary>
		private void ClickBtnTemp(object sender, EventArgs e)
		{
			folderBrowser.SelectedPath = textTemp.Text;

			if (DialogResult.OK == folderBrowser.ShowDialog())
			{
				textTemp.Text = folderBrowser.SelectedPath;
			}
		}

		/// <summary>
		/// Установка настроек по умолчанию.
		/// </summary>
		private void SetDefault(object sender, EventArgs e)
		{
			m_formAOP.RipSetDefaultOption();

			LoadForm(null, null);
		}
	}
}