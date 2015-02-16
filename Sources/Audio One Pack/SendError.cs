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
using System.Net.Mail;
using Win32Mapi;

namespace AudioOnePack
{
	public partial class SendError : Form
	{
        //
		String m_strError;

        //
		public SendError(String strError)
		{
			InitializeComponent();

			m_strError = strError;
		}

        //
		private void Quit(object sender, EventArgs e)
		{
			Close();
		}

        //
		private void SendReport(object sender, EventArgs e)
		{
			Mapi ma = new Mapi();
			
			ma.Logon(IntPtr.Zero);
			ma.AddRecip("support@wholegroup.com", null, false);
			ma.Send("Audio One Pack :: Report error", m_strError);
			ma.Logoff();

			Close();
		}
	}
}