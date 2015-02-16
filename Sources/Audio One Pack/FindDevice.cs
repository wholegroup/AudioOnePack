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
using System.Threading;

namespace AudioOnePack
{
	public partial class FindDevice : Form
	{
		/// <summary>
		/// делегат без параметров.
		/// </summary>
		private delegate void DelegateNoParam();
		
		/// <summary>
		/// Конструктор.
		/// </summary>
		public FindDevice()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Первый показ формы - запуск обнаружений приводов.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ShowForm(object sender, EventArgs e)
		{
			(new DelegateNoParam(GetDevices)).BeginInvoke(null, null);
		}

		/// <summary>
		/// Обнаружение приводов.
		/// </summary>
		private void GetDevices()
		{
			AOPAPI.AOPGetDevices(FindCallback);

			Invoke(new DelegateNoParam(Close));
		}

		/// <summary>
		/// Callback с найденным устройством.
		/// </summary>
		/// <param name="deviceInfo"></param>
		/// <returns></returns>
		public void FindCallback(AOPAPI.DEVICEINFO deviceInfo)
		{
			(Owner as AOPForm).AddDevice(deviceInfo);
		}
	}
}