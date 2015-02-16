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
	public partial class RipEditTrack : Form
	{
        //
		private RipCDForm m_formRipCD;

        //
		private int m_iTrack;

        //
		public RipEditTrack()
		{
			InitializeComponent();
		}

        //
		public RipEditTrack(RipCDForm formRipCD, int iTrack, String strArtist, String strTitle)
			: this()
		{
			m_formRipCD = formRipCD;
			m_iTrack    = iTrack;

			textArtist.Text = strArtist;
			textTitle.Text  = strTitle;

			Text = String.Format(Text, iTrack + 1);
		}

        //
		private void OnOk(object sender, EventArgs e)
		{
			m_formRipCD.SetDiskNameTrack(m_iTrack, textArtist.Text, textTitle.Text);

			Close();
		}

        //
		private void OnCancel(object sender, EventArgs e)
		{
			Close();
		}
	}
}