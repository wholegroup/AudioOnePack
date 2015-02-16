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
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace AudioOnePack
{
	//
	public partial class MusicCDBurn : Form
	{
		/// <summary>
		/// Ссылка на главную форму.
		/// </summary>
		private AOPForm m_formAOP;

		/// <summary>
		/// Ссылка на форму создания MusicCD.
		/// </summary>
		private MusicCDForm m_formMusicCD;

		/// <summary>
		/// Информация о выбранном устройстве.
		/// </summary>
		private AOPAPI.DEVICEINFO m_devInfo;

		/// <summary>
		/// Список треков.
		/// </summary>
		private TreeView m_treeDisk;

		/// <summary>
		/// флаг выхода.
		/// </summary>
		private bool m_bExit = false;
		
		/// <summary>
		/// Индекс скорости записи.
		/// </summary>
		private int m_iSpeed;

		/// <summary>
		/// Делегат без параметров.
		/// </summary>
		private delegate void DelegateNoParam();

		/// <summary>
		/// Структура описания файла.
		/// </summary>
		private struct MUSICFILEINFO 
		{
			public string strName;
			public string strPath;
			public int    iLevel;
			public bool   bFolder;
		};

		/// <summary>
		/// Список файлов.
		/// </summary>
		private List<MUSICFILEINFO> m_arrFiles = new List<MUSICFILEINFO>();
		
		/// <summary>
		/// Конструктор по-умолчанию.
		/// </summary>
		public MusicCDBurn()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Конструктор с передачей ссылки на главную форму и форму создания MusicCD.
		/// </summary>
		/// <param name="formAOP"></param>
		/// <param name="formMusicCD"></param>
		public MusicCDBurn(AOPForm formAOP, MusicCDForm formMusicCD)
			: this()
		{
			m_formAOP     = formAOP;
			m_formMusicCD = formMusicCD;
			m_devInfo     = m_formMusicCD.GetWorkDevice();
			m_treeDisk    = m_formMusicCD.GetTreeDisk();
			m_iSpeed      = m_formMusicCD.GetWriteSpeed();
		}

		/// <summary>
		/// Отмена прожига.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Cancel(object sender, EventArgs e)
		{
			btnCancel.Enabled = false;

			m_bExit = true;
		}

		/// <summary>
		/// Обработка при первом выводе формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void FirstShow(object sender, EventArgs e)
		{
			// подготовка списка файлов для записи
			Stack stackNode = new Stack();

			stackNode.Push(m_treeDisk.Nodes[0]);

			while (stackNode.Count > 0)
			{
				TreeNode nodeCur = (TreeNode)stackNode.Pop();

				if (nodeCur != m_treeDisk.Nodes[0])
				{
					MUSICFILEINFO fiMusic;
				
					fiMusic.strName = nodeCur.Text;
					fiMusic.iLevel = nodeCur.Level;

					if (null != nodeCur.Tag)
					{
						fiMusic.bFolder = false;
						fiMusic.strPath = (String)nodeCur.Tag;
					}
					else
					{
						fiMusic.bFolder = true;
						fiMusic.strPath = "";
					}

					m_arrFiles.Add(fiMusic);
				}

				for (int i = nodeCur.Nodes.Count - 1; i >= 0; i--)
				{
					stackNode.Push(nodeCur.Nodes[i]);
				}
			}

			// запуск процесса добавления файлов
			(new DelegateNoParam(Recode)).BeginInvoke(null, null);
		}

		/// <summary>
		/// Добавление файлов.
		/// </summary>
		private void Recode()
		{
			Invoke(new DelegateNoParam(EndRecode));
		}

		/// <summary>
		/// Обработка завершения формирования структуры Music CD.
		/// </summary>
		private void EndRecode()
		{
			// отключаем кнопку Cancel
			btnCancel.Enabled = false;

			// запуск процесса прожига
			(new DelegateNoParam(BurnMusicCD)).BeginInvoke(null, null);
		}

		/// <summary>
		/// Прожиг диска.
		/// </summary>
		private void BurnMusicCD()
		{
			// инициализация Music CD
			if (0 != AOPAPI.AOPMusicCDInit(ref m_devInfo))
			{
				MessageBox.Show("ERROR::AOPMusicCDInit", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);

				Invoke(new DelegateNoParam(Close));

				return;
			}

			// подготовка диска
			Invoke(new SetInfoLineDelegate(SetInfoLineOne), Properties.Resources.IDS_MUSICBURN_ADDINGFILES);

			for (int i = 0; i < m_arrFiles.Count; i++)
			{
				// получение информации об очередном файле
				MUSICFILEINFO fiMusic = m_arrFiles[i];

				// вывод имени
				Invoke(new SetInfoLineDelegate(SetInfoLineTwo), fiMusic.strName);

				// установка уровня
				if (i > 0)
				{
					if (true == fiMusic.bFolder)
					{
						int iUp = m_arrFiles[i - 1].iLevel - fiMusic.iLevel;

						if (true == m_arrFiles[i - 1].bFolder)
						{
							iUp++;
						}

						if (0 < iUp)
						{
							for (int j = 0; j < iUp; j++)
							{
								AOPAPI.AOPMusicCDTreeUp();
							}
						}
					}
				}

				// добавление файла или каталога
				if (true == fiMusic.bFolder)
				{
					AOPAPI.AOPMusicCDAddFolder(fiMusic.strName);
				}
				else
				{
					AOPAPI.AOPMusicCDAddFile(fiMusic.strPath);
				}

				// установка значения прогресса
				Invoke(new SetProgressDelegate(SetProgress), (float)(i + 1) / (m_arrFiles.Count));

				// выход, если была нажата кнопка Cancel
				if (true == m_bExit)
				{
					Invoke(new DelegateNoParam(Close));

					return;
				}
			}

			// прожиг
			Invoke(new SetInfoLineDelegate(SetInfoLineOne), "Burning Music CD...");
			Invoke(new SetInfoLineDelegate(SetInfoLineTwo), "Please wait.");
			Invoke(new SetProgressDelegate(SetProgress), 0);

			while (true)
			{
				AOPAPI.MusicBurnCallbackDelegate delegateBurn = new AOPAPI.MusicBurnCallbackDelegate(BurnMusicCDCallback);

				// прожиг диска
				if (0 != AOPAPI.AOPMusicCDBurn(delegateBurn, m_iSpeed, "TEST"))
				{
					MessageBox.Show("ERROR::AOPMusicCDBurn", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);

					break;
				}

				break;
			}

			MessageBox.Show("Burning is complete!");

			// освобождение ресурсов
			if (0 != AOPAPI.AOPMusicCDFree())
			{
				MessageBox.Show("ERROR::AOPMusicCDFree", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}

			Invoke(new DelegateNoParam(Close));
		}

		/// <summary>
		/// Callback Функция прожига.
		/// </summary>
		/// <param name="uiAction"></param>
		/// <param name="uiParamOne"></param>
		/// <param name="uiParamTwo"></param>
		private void BurnMusicCDCallback(Int32 uiAction, Int32 uiParamOne, Int32 uiParamTwo)
		{
			switch (uiAction)
			{
				case (int)AOPAPI.MusicEnum.MUSICBURN_WRITE:
					Invoke(new SetProgressDelegate(SetProgress), (float)(uiParamOne / 100.0));
					break;
			}
		}
		
		/// <summary>
		/// Делегат для установки текста.
		/// </summary>
		/// <param name="strText"></param>
		private delegate void SetInfoLineDelegate(string strText);

		/// <summary>
		/// Установка текста в labelOne.
		/// </summary>
		/// <param name="strText"></param>
		private void SetInfoLineOne(string strText)
		{
			labelOne.Text = strText;
		}

		/// <summary>
		/// Установка текста в labelTwo.
		/// </summary>
		/// <param name="strText"></param>
		private void SetInfoLineTwo(string strText)
		{
			labelTwo.Text = strText;
		}

		/// <summary>
		/// Делегат для установки progressBurn.
		/// </summary>
		/// <param name="fPercent"></param>
		private delegate void SetProgressDelegate(float fPercent);
		
		/// <summary>
		/// Установка progressBurn.
		/// </summary>
		/// <param name="fPercent"></param>
		private void SetProgress(float fPercent)
		{
			int iValue = progressBurn.Minimum + (int)((progressBurn.Maximum - progressBurn.Minimum) * fPercent);

			if (iValue < progressBurn.Minimum)
			{
				progressBurn.Value = progressBurn.Minimum;
			}
			else if (iValue > progressBurn.Maximum)
			{
				progressBurn.Value = progressBurn.Maximum;
			}
			else
			{
				progressBurn.Value = iValue;
			}
		}
	}
}