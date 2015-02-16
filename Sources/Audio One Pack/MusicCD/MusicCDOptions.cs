﻿/*
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
	public partial class MusicCDOptions : Form
	{
		//
		AOPForm m_formAOP;

		//
		public MusicCDOptions()
		{
			InitializeComponent();
		}

		//
		public MusicCDOptions(AOPForm formAOP)
			:this()
		{
			m_formAOP = formAOP;

			textFolder.Text  = m_formAOP.TempPath;
			cbLoadTray.Checked = m_formAOP.bMusicCDLoadTray;
		}

		//
		private void Ok(object sender, EventArgs e)
		{
			m_formAOP.TempPath = textFolder.Text;
			m_formAOP.bMusicCDLoadTray = cbLoadTray.Checked;

			Close();
		}

		//
		private void Cancel(object sender, EventArgs e)
		{
			Close();
		}

		//
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