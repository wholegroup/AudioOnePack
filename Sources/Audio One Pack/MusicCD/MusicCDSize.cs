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
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace AudioOnePack
{
	//
	public partial class MusicCDSize : UserControl
	{
		/// <summary>
		/// Полный размер диска.
		/// </summary>
		private int m_iSize = 700000000;

		public int iSize
		{
			get
			{
				return m_iSize;
			}

			set
			{
				iSize = value;
			}
		}

		/// <summary>
		/// Количество занятого места.
		/// </summary>
		private int m_iUsed = 0;

		public int iUsed
		{
			get
			{
				return m_iUsed;
			}

			set
			{
				m_iUsed = value;
			}
		}

		/// <summary>
		/// Конструктор по-умолчанию без параметров.
		/// </summary>
		public MusicCDSize()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Отрисовка.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void OnPaint(object sender, PaintEventArgs e)
		{
			// вычисление максимальной высоты колонки
			int iMax = 0;

			if (iUsed > iMax)
			{
				iMax = iUsed;
			}

			if (iSize > iMax)
			{
				iMax = iSize;
			}

			// вычисление колонки с размером свободного места
			int iFree = iSize - iUsed;

			if (0 > iFree)
			{
				iFree = 0;
			}

			// первый столбец
			int iX = (int)((this.Size.Width / 3.0) * 0.2);
			int iY = this.Size.Height - (int)(this.Size.Height * (double)iFree / iMax);
			int iWidth  = (int)((this.Size.Width / 3.0) * 0.6);
			int iHeight = (int)(this.Size.Height * (double)iFree / iMax);

			e.Graphics.FillRectangle(new SolidBrush(Color.Green), iX, iY, iWidth, iHeight);

			// второй столбец
			iX = (int)((this.Size.Width / 3.0) * (1 + 0.2));
			iY = this.Size.Height - (int)(this.Size.Height * (double)iUsed / iMax);
			iWidth  = (int)((this.Size.Width / 3.0) * 0.6);
			iHeight = (int)(this.Size.Height * (double)iUsed / iMax);

			e.Graphics.FillRectangle(new SolidBrush(Color.Red), iX, iY, iWidth, iHeight);

			// второй столбец
			iX = (int)((this.Size.Width / 3.0) * (2 + 0.2));
			iY = this.Size.Height - (int)(this.Size.Height * (double)iSize / iMax);
			iWidth  = (int)((this.Size.Width / 3.0) * 0.6);
			iHeight = (int)(this.Size.Height * (double)iSize / iMax);

			e.Graphics.FillRectangle(new SolidBrush(Color.Blue), iX, iY, iWidth, iHeight);
		}
	}
}
