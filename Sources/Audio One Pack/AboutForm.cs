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
	public partial class AboutForm : Form
	{
		/// <summary>
		/// ссылка на главную форму.
		/// </summary>
		AOPForm m_formAOP;

		/// <summary>
		/// Конструктор с передачей ссылки на главную форму.
		/// </summary>
		public AboutForm(AOPForm formAOP)
		{
			m_formAOP = formAOP;

			InitializeComponent();
		}

		/// <summary>
		/// Обработка нажатия кнопки OK.
		/// </summary>
		private void OnOk(object sender, EventArgs e)
		{
			DialogResult = DialogResult.OK;
		}

		/// <summary>
		/// Обработчка переключателя "не показывать при старте".
		/// </summary>
		private void ShowOnStart(object sender, EventArgs e)
		{
			m_formAOP.ShowAboutOnStart = !m_cbShowOnStart.Checked;
		}
	}
}