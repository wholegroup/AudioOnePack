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
    //
	public partial class EraseForm : Form
	{
		/// <summary>
		/// Ссылка на информацию о выбранном CD/DVD приводе.
		/// </summary>
		private AOPAPI.DEVICEINFO m_devInfo;

		/// <summary>
		/// загружать лоток после eject'a.
		/// </summary>
		private bool  m_bLoadTray;

        //
		private float m_fMaxBlankTime;

        //
		private float m_fCurBlankTime;

        //
		private int m_iEraseFull;

        //
		private bool m_bSilentErase;

		/// <summary>
		/// Конструктор по-умолчанию.
		/// </summary>
		public EraseForm()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Конструктор с передачей ссылки на информацию о выбранном CD/DVD приводе.
		/// </summary>
		public EraseForm(AOPAPI.DEVICEINFO devInfo, Boolean bLoadTray)
			: this()
		{
			m_devInfo      = devInfo;
			m_bLoadTray    = bLoadTray;
			m_bSilentErase = false;
		}

        //
		public EraseForm(AOPAPI.DEVICEINFO devInfo, Boolean bLoadTray, Boolean bSilentErase)
			: this(devInfo, true)
		{
			m_bSilentErase = true;
		}

		/// <summary>
		/// Загрузка формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void LoadForm(object sender, EventArgs e)
		{
			cbMethod.SelectedIndex = 0;

			if (true == m_bSilentErase)
			{
				Erase(null, null);
			}
		}

		/// <summary>
		/// Закрытие формы
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void CloseForm(object sender, EventArgs e)
		{
			Close();
		}

		/// <summary>
		/// Обработка смены метода
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ChangedMethod(object sender, EventArgs e)
		{
			if (0 == cbMethod.SelectedIndex)
			{
				textMethod.Text = Properties.Resources.IDS_ERASECDRW_QUICK;
			}
			else
			{
				textMethod.Text = Properties.Resources.IDS_ERASECDRW_FULL;
			}
		}

		/// <summary>
		/// Запуск процесса стирания
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Erase(object sender, EventArgs e)
		{
			// выключение контролов
			btnErase.Enabled  = false;
			btnCancel.Enabled = false;
			cbMethod.Enabled  = false;

			// сброс прогрессбара
			progressErase.Value = 0;

			// режим стирания
			m_iEraseFull = cbMethod.SelectedIndex;

			// получение примерного времени очистки диска
			m_fMaxBlankTime = AOPAPI.AOPGetBlankTime(ref m_devInfo, (byte)cbMethod.SelectedIndex);

			// запуск процесса стирания
			(new BlankDelegate(Blank)).BeginInvoke(null, null);

			// запуск таймера
			timerPos.Start();
		}

		/// <summary>
		/// Делегат для обработки завершения процесса стирания
		/// </summary>
		private delegate void EraseEndDelegate(bool bErased);

		/// <summary>
		/// Завершение процесса стирания
		/// </summary>
		private void EraseEnd(bool bErased)
		{
			// остановка таймера
			timerPos.Stop();

			// Вывод сообщения 
			if (true == bErased)
			{
				if (false == m_bSilentErase)
				{
					AOPAPI.AOPEjectTray(ref m_devInfo);

					if (m_bLoadTray)
					{
						AOPAPI.AOPLoadTray(ref m_devInfo);
					}

					MessageBox.Show(this, Properties.Resources.IDS_ERASECDRW_OK, 
                        Properties.Resources.IDS_ERASECDRW_OK_CAPTION, 
                        MessageBoxButtons.OK, MessageBoxIcon.Information);
				}
			}
			else
			{
				MessageBox.Show(this, Properties.Resources.IDS_ERASECDRW_NOTERASE, 
                    Properties.Resources.IDS_ERASECDRW_NOTERASE_CAPTION, 
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
			}

			// включение контролов
			btnErase.Enabled  = true;
			btnCancel.Enabled = true;
			cbMethod.Enabled  = true;

			Close();
		}

		/// <summary>
		/// Делегат для очистки диска
		/// </summary>
		private delegate void BlankDelegate();

		/// <summary>
		/// Очистка диска
		/// </summary>
		private void Blank()
		{
			if (0 != AOPAPI.AOPBlank(ref m_devInfo, (byte)m_iEraseFull))
			{
				Invoke(new EraseEndDelegate(EraseEnd), false);
			}
			else
			{
				Invoke(new EraseEndDelegate(EraseEnd), true);
			}
		}

		/// <summary>
		/// Обработка тиков таймера
		/// </summary>
		private void TickPos(object sender, EventArgs e)
		{
			// текущее время стирания
			m_fCurBlankTime += timerPos.Interval / 1000.0f;

			// текущее значение прогрессбара
			int iValue = (int)((float)(progressErase.Maximum - progressErase.Minimum) * 
                m_fCurBlankTime / m_fMaxBlankTime);

			// установка прогрессбара
			if (iValue > progressErase.Maximum)
			{
				progressErase.Value = progressErase.Maximum;
			}
			else if (iValue < progressErase.Minimum)
			{
				progressErase.Value = progressErase.Minimum;
			}
			else
			{
				progressErase.Value = iValue;
			}
		}
	}
}