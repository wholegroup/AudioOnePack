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
using System.IO;
using System.Threading;

namespace AudioOnePack
{
	//
	public partial class MusicCDAddFolder : Form
	{
		/// <summary>
		/// Ссылка на родительскую форму.
		/// </summary>
		MusicCDForm m_formMusicCD;

		/// <summary>
		/// Путь для начала сканирования.
		/// </summary>
		String m_strStartFolder;

		/// <summary>
		/// делегат без параметров.
		/// </summary>
		private delegate void DelegateNoParam();

		/// <summary>
		/// Делегат для создания папки.
		/// </summary>
		/// <param name="strFolder"></param>
		private delegate void DelegateCreateFolder(String strFolder, int iLevel);

		/// <summary>
		/// Делегат для добавления трека.
		/// </summary>
		/// <param name="strTrack"></param>
		private delegate void DelegateAddTrack(String strTrack);

		/// <summary>
		/// Делегат для возврата выделенной ноды.
		/// </summary>
		/// <returns></returns>
		private delegate TreeNode DelegateGetSelectedNode();

		/// <summary>
		/// Делегат для удаления пустых нод.
		/// </summary>
		/// <param name="nodeStart"></param>
		private delegate void DelegateDeleteEmptyNodes(TreeNode nodeStart);
		
		/// <summary>
		/// Конструктор по умолчанию
		/// </summary>
		public MusicCDAddFolder()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Конструктор с передачей ссылки на форму и путем для начала сканирования.
		/// </summary>
		/// <param name="formMusicCD"></param>
		/// <param name="strStartFolder"></param>
		public MusicCDAddFolder(MusicCDForm formMusicCD, String strStartFolder)
			: this()
		{
			m_formMusicCD    = formMusicCD;
			m_strStartFolder = strStartFolder;
		}

		/// <summary>
		/// Отмена добавления.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Cancel(object sender, EventArgs e)
		{
			this.DialogResult = DialogResult.Cancel;

			Close();
		}

		/// <summary>
		/// Обработка первого показа формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ShowForm(object sender, EventArgs e)
		{
			(new DelegateNoParam(Scanning)).BeginInvoke(null, null);
		}

		/// <summary>
		/// Сканирование директории и всех поддиректорий
		/// </summary>
		private void Scanning()
		{
			// поддерживаемые расширения файлов
			String[] arrExt = { ".mp3", ".mp2", ".mp1", ".ogg", ".wav", ".aif", ".flac", ".cda", 
								  ".wma", ".aac", ".m4a", ".mp4", ".ac3", ".ape", ".mac", ".mpc", 
								  ".mp", ".mpp", ".ofr", ".ofs", ".spx", ".tta", ".wv" };

			ArrayList arrListExt = new ArrayList();

			foreach (String strExt in arrExt)
			{
				arrListExt.Add(strExt);
			}

			// цикл по всем директориям и поддиректориям
			TreeNode nodeFirst = null;

			Stack stackDir   = new Stack();
			Stack stackLevel = new Stack();
			int   iMaxLevel  = 0;

			stackDir.Push(m_strStartFolder);
			stackLevel.Push(iMaxLevel);

			while (stackDir.Count > 0)
			{
				// имя очередной директории для сканирования
				String strDir = (String)stackDir.Pop();

				// уровень вложенности
				int iLevelDir = (int)Convert.ToInt32(stackLevel.Pop());

				// создание директории
				Invoke(new DelegateCreateFolder(m_formMusicCD.CreateFolder), 
					Path.GetFileName(strDir), iMaxLevel - iLevelDir);
				iMaxLevel = iLevelDir + 1;

				// возврат первой созданной ноды
				if (null == nodeFirst)
				{
					nodeFirst = (TreeNode)Invoke(new DelegateGetSelectedNode(m_formMusicCD.GetSelectedNode));
				}

				// сканирование текущей директории на наличие файлов
				String[] arrFiles = Directory.GetFiles(strDir);

				for (int i = 0; i < arrFiles.Length; i++)
				{
					try
					{
						Invoke(new SetTextInfoDelegate(SetTextInfo), arrFiles[i]);

						String strExt = Path.GetExtension(arrFiles[i]);

						if (strExt.Length > 0)
						{
							if (arrListExt.IndexOf(strExt) >= 0)
							{
								Invoke(new DelegateAddTrack(m_formMusicCD.AddTrack), arrFiles[i]);
							}
						}
					}
					catch (System.Exception)
					{
					}
				}

				// поиск поддиректорий
				String[] arrChildDirs = Directory.GetDirectories(strDir);

				for (int i = (arrChildDirs.Length - 1); i >= 0; i--)
				{
					stackDir.Push(arrChildDirs[i]);
					stackLevel.Push(iLevelDir + 1);
				}
			}

			// удаление пустых нод
			if (null != nodeFirst)
			{
				Invoke(new DelegateDeleteEmptyNodes(m_formMusicCD.DeleteEmptyNodes), nodeFirst);
			}

			// закрытие диалога
			Invoke(new DelegateNoParam(Close));
		}

		/// <summary>
		/// Делегат для установки текстовой информации.
		/// </summary>
		/// <param name="strFullPath"></param>
		private delegate void SetTextInfoDelegate(String strFullPath);

		/// <summary>
		/// Установка текстовой информации.
		/// </summary>
		/// <param name="strText"></param>
		private void SetTextInfo(String strFullPath)
		{
			textFolder.Text = Path.GetDirectoryName(strFullPath);
			textFile.Text   = Path.GetFileName(strFullPath);
		}
	}
}