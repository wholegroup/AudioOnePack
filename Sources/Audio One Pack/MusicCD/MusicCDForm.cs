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

namespace AudioOnePack
{
	//
	public partial class MusicCDForm : Form
	{
		/// <summary>
		/// Ссылка на главную форму
		/// </summary>
		AOPForm m_formAOP;

		/// <summary>
		/// Начальная позиция проигрывания текущего трека.
		/// </summary>
		private float m_fStartPos;

		/// <summary>
		/// Заключительная позиция проигрывания текущего трека.
		/// </summary>
		private float m_fStopPos;

		/// <summary>
		/// Форма для отображения размера CD.
		/// </summary>
		private MusicCDSize m_sizeCD;
		
		/// <summary>
		/// Конструктор по-умолчанию.
		/// </summary>
		public MusicCDForm()
		{
			InitializeComponent();
		}

		/// <summary>
		/// Конструктор с передачей ссылки на главную форму.
		/// </summary>
		/// <param name="formAOP"></param>
		public MusicCDForm(AOPForm formAOP)
			: this()
		{
			m_formAOP = formAOP;
		}

		/// <summary>
		/// Обработка загрузки формы.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void LoadForm(object sender, EventArgs e)
		{
			// установка шрифта по-умолчанию
			this.Font = SystemFonts.DefaultFont;

			// установка громкости
			trackVolume.Value = (int)AOPAPI.AOPGetVolume() / 5;

			// очищаем все дерево
			treeDisk.Nodes.Clear();

			// добавление корневого элемента
			DateTime dtNow = DateTime.Today;

			treeDisk.Nodes.Add(String.Format("{0:D} {1:S} {2:D04}", dtNow.Day, dtNow.ToString("MMMM"), dtNow.Year)); 

			// добавление контрола для показа размера диска
			m_sizeCD = new MusicCDSize();

			this.Controls.Add(m_sizeCD);

			m_sizeCD.Location = labelSize.Location;
			m_sizeCD.Size = labelSize.Size;
			m_sizeCD.Parent = labelSize.Parent;

			labelSize.Visible = false;
		}

		/// <summary>
		/// Обработка нажатия кнопки Quit.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Quit(object sender, EventArgs e)
		{
			Application.Exit();
		}

		/// <summary>
		/// Заполнение списка CD/DVD приводов.
		/// </summary>
		public void FillListDevices()
		{
			List<AOPAPI.DEVICEINFO> listDevice = m_formAOP.GetListDevices();

			for (int i = 0; i < listDevice.Count; i++)
			{
				cbDeviceName.Items.Add("(" + listDevice[i].strLetter + ") " + listDevice[i].strName);
			}

            cbDeviceName.SelectedIndex = 0 < listDevice.Count ? 0 : -1;
		}

		/// <summary>
		/// Заполнение выпадающего списка скоростями записи.
		/// </summary>
		public void FillWriteSpeeds()
		{
			cbSpeeds.Items.Clear();

			List<List<String>> listWriteSpeed = m_formAOP.GetWriteSpeed();
			int iDevice = cbDeviceName.SelectedIndex;

            if (-1 == iDevice)
            {
                return;
            }

			for (int i = 0; i < listWriteSpeed[iDevice].Count; i++)
			{
				cbSpeeds.Items.Add(listWriteSpeed[iDevice][i]);
			}

			cbSpeeds.SelectedIndex = cbSpeeds.Items.Count - 1;
		}

		/// <summary>
		/// Вызов диалога "About".
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void About(object sender, EventArgs e)
		{
			AboutForm formAbout = new AboutForm(m_formAOP);

			formAbout.ShowDialog();
		}

		/// <summary>
		/// Вызов диалога с информацией о диске.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void DiskInfo(object sender, EventArgs e)
		{
            if (-1 == cbDeviceName.SelectedIndex)
            {
                return;
            }

			DiscInfoForm formDiskInfo = new DiscInfoForm(GetWorkDevice());

			formDiskInfo.ShowDialog();
		}

		/// <summary>
		/// Возвращает информацию о выбранном CD/DVD устройстве.
		/// </summary>
		/// <returns></returns>
		public AOPAPI.DEVICEINFO GetWorkDevice()
		{
			List<AOPAPI.DEVICEINFO> devInfoList = m_formAOP.GetListDevices();

			return devInfoList[cbDeviceName.SelectedIndex];
		}

		/// <summary>
		/// Стирание CD-RW.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Erase(object sender, EventArgs e)
		{
            if (-1 == cbDeviceName.SelectedIndex)
            {
                return;
            }

			EraseForm formErase = new EraseForm(GetWorkDevice(), true);

			formErase.ShowDialog();
		}

		/// <summary>
		/// Вызов диалога настроек.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Options(object sender, EventArgs e)
		{
			MusicCDOptions formOptions = new MusicCDOptions(m_formAOP);

			formOptions.ShowDialog();
		}

		/// <summary>
		/// Обработка изменения громкости.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ScrollVolume(object sender, EventArgs e)
		{
			AOPAPI.AOPSetVolume((uint)trackVolume.Value * 5);
		}

		/// <summary>
		/// Синхронизация громкости.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void VisibleForm(object sender, EventArgs e)
		{
			trackVolume.Value = (int)AOPAPI.AOPGetVolume() / 5;
		}

		/// <summary>
		/// Создание новой пустой папки.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void CreateFolder(object sender, EventArgs e)
		{
			// получение ноды, куда будет вставлена папка
			TreeNode nodeScan = treeDisk.SelectedNode;

			if (null == nodeScan)
			{
				nodeScan = treeDisk.Nodes[0];
			}
			else
			{
				if (null != nodeScan.Tag)
				{
					nodeScan = nodeScan.Parent;
				}
			}

			// генерирование уникального имени папки для конкретной ноды
			int iNumber = 1;
			String strFolder = "New Folder ";

			while (true)
			{
				Boolean bExist = false;
				String strNewFolder = strFolder + iNumber.ToString();

				for (int i = 0; i < nodeScan.Nodes.Count; i++)
				{
					if (nodeScan.Nodes[i].Text == strNewFolder)
					{
						bExist = true;

						break;
					}
				}

				if (false == bExist)
				{
					break;
				}

				iNumber++;
			}

			// создание папки
			CreateFolder(strFolder + iNumber.ToString());
		}

		/// <summary>
		/// Создание именованной папки.
		/// </summary>
		/// <param name="strFolder"></param>
		private void CreateFolder(String strFolder)
		{
			// если нода не выбрана, то добавляем папку в корень
			if (null == treeDisk.SelectedNode)
			{
				TreeNode nodeNew = treeDisk.Nodes[0].Nodes.Add(strFolder);

				nodeNew.ImageIndex         = 1;
				nodeNew.SelectedImageIndex = 1;

				nodeNew.Parent.Expand();

				treeDisk.SelectedNode = nodeNew;
			}

			// добавляем папку в выбранную ноду
			else
			{
				TreeNode nodeSel = treeDisk.SelectedNode;
				TreeNode nodeNew;

				// если выбранная нода папка, то добавляем в неё
				if (null == nodeSel.Tag)
				{
					nodeNew = nodeSel.Nodes.Add(strFolder);
				}

				// если выбранная нода файл, то добавляем в родительскую ноду файла
				else
				{
					nodeNew = nodeSel.Parent.Nodes.Add(strFolder);
				}

				nodeNew.ImageIndex         = 1;
				nodeNew.SelectedImageIndex = 1;

				nodeNew.Parent.Expand();

				treeDisk.SelectedNode = nodeNew;
			}
		}

		/// <summary>
		/// Создание именнованой папки с указанием относительного уровня вложенности.
		/// </summary>
		/// <param name="strFolder"></param>
		/// <param name="iLevel"></param>
		public void CreateFolder(String strFolder, int iLevel)
		{
			for (int i = 0; i < iLevel; i++)
			{
				if (null != treeDisk.SelectedNode.Parent)
				{
					treeDisk.SelectedNode = treeDisk.SelectedNode.Parent;
				}
			}

			CreateFolder(strFolder);
		}

		/// <summary>
		/// Добавление файлов.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void AddFiles(object sender, EventArgs e)
		{
			if (DialogResult.OK != openFileTree.ShowDialog())
			{
				return;
			}

			for (int i = 0; i < openFileTree.FileNames.Length; i++)
			{
				AddFile(openFileTree.FileNames[i]);
			}
		}

		/// <summary>
		/// Добавление файла.
		/// </summary>
		/// <param name="strFile"></param>
		private void AddFile(String strFile)
		{
			// проверка наличия файла
			if (false == File.Exists(strFile))
			{
				return;
			}

			// получение очередного расширения файла
			string strExtension = Path.GetExtension(strFile);

			// обработка playlist от WinAmp
			if (".m3u" == strExtension)
			{
				Directory.SetCurrentDirectory(Path.GetDirectoryName(strFile)); 

				StreamReader streamIn = new StreamReader(strFile, System.Text.ASCIIEncoding.Default);

				while (false == streamIn.EndOfStream)
				{
					string strLine = streamIn.ReadLine();

					if ((strLine.Length > 0) && ('#' != strLine[0]))
					{
						if (File.Exists(strLine))
						{
							strLine = Path.GetFullPath(strLine);

							AddTrack(strLine);
						}
					}
				}

				streamIn.Close();
			}

			// обработка playlist от WinAmp в кодировке UTF-8
			else if (".m3u8" == strExtension)
			{
				StreamReader streamIn = new StreamReader(strFile);

				while (false == streamIn.EndOfStream)
				{
					string strLine = streamIn.ReadLine();

					if ((strLine.Length > 0) && ('#' != strLine[0]))
					{
						if (File.Exists(strLine))
						{
							strLine = Path.GetFullPath(strLine);

							AddTrack(strLine);
						}
					}
				}

				streamIn.Close();
			}

			// обработка CUE 
			else if (".cue" == strExtension)
			{
			}

			// добавление музыкального файла
			else
			{
				AddTrack(strFile);
			}
		}

		/// <summary>
		/// Добавление папки и всех подпапок с муз.файлами.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void AddFolder(object sender, EventArgs e)
		{
			if (DialogResult.OK != folderBrowserTree.ShowDialog())
			{
				return;
			}

			MusicCDAddFolder formAddFolder = new MusicCDAddFolder(this, folderBrowserTree.SelectedPath);
			
			formAddFolder.ShowDialog();
		}

		/// <summary>
		/// Удаление выбранного элемента дерева
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Delete(object sender, EventArgs e)
		{
			if ((null != treeDisk.SelectedNode) && (treeDisk.Nodes[0] != treeDisk.SelectedNode))
			{
				if (DialogResult.Yes == MessageBox.Show(this, Properties.Resources.IDS_MUSICCD_DELNODE, 
					Properties.Resources.IDS_MUSICCD_DELNODE_CAPTION, MessageBoxButtons.YesNo, MessageBoxIcon.Question))
				{
					// вычитание размера всех файлов в удаляемой ноде
					Stack stackNode = new Stack();

					stackNode.Push(treeDisk.SelectedNode);

					while (stackNode.Count > 0)
					{
						TreeNode nodeCur = (TreeNode)stackNode.Pop();

						for (int i = nodeCur.Nodes.Count - 1; i >= 0; i--)
						{
							if (null != nodeCur.Nodes[i].Tag)
							{
								m_sizeCD.iUsed -= (int)(new FileInfo((String)nodeCur.Nodes[i].Tag)).Length;
							}

							stackNode.Push(nodeCur.Nodes[i]);
						}
					}

					m_sizeCD.Invalidate();

					// удаление ноды со всеми поднодами
					treeDisk.SelectedNode.Remove();

					// выключение кнопки burn, если нет нод
					if (treeDisk.Nodes[0].Nodes.Count == 0)
					{
						btnBurn.Enabled = false;
					}
				}
			}
		}

		/// <summary>
		/// Обработка открытия ноды.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ExpandNode(object sender, TreeViewEventArgs e)
		{
			if (e.Node != treeDisk.Nodes[0])
			{
				e.Node.ImageIndex = 2;
				e.Node.SelectedImageIndex = 2;
			}
		}

		/// <summary>
		/// Обработка закрытия ноды.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void CollapseNode(object sender, TreeViewEventArgs e)
		{
			if (e.Node != treeDisk.Nodes[0])
			{
				e.Node.ImageIndex = 1;
				e.Node.SelectedImageIndex = 1;
			}
		}

		/// <summary>
		/// Добавление трека.
		/// </summary>
		/// <param name="strFilename"></param>
		public void AddTrack(string strFilename)
		{
			String strWithoutExt = Path.GetFileNameWithoutExtension(strFilename);

			// если нода не выбрана, то добавляем папку в корень
			if (null == treeDisk.SelectedNode)
			{
				TreeNode nodeNew = treeDisk.Nodes[0].Nodes.Add(strWithoutExt);

				nodeNew.ImageIndex         = 3;
				nodeNew.SelectedImageIndex = 3;
				nodeNew.Tag                = strFilename;

				nodeNew.Parent.Expand();
			}

			// добавляем папку в выбранную ноду
			else
			{
				TreeNode nodeSel = treeDisk.SelectedNode;
				TreeNode nodeNew;

				// если выбранная нода папка, то добавляем в неё
				if (null == nodeSel.Tag)
				{
					nodeNew = nodeSel.Nodes.Add(strWithoutExt);
				}

				// если выбранная нода файл, то добавляем в родительскую ноду файла
				else
				{
					nodeNew = nodeSel.Parent.Nodes.Add(strWithoutExt);
				}

				nodeNew.ImageIndex         = 3;
				nodeNew.SelectedImageIndex = 3;
				nodeNew.Tag                = strFilename;

				nodeNew.Parent.Expand();
			}

			// прибавление размера
			m_sizeCD.iUsed += (int)(new FileInfo(strFilename)).Length;

			m_sizeCD.Invalidate();

			// включение кнопки прожига
			if (null != treeDisk.Nodes[0])
			{
				btnBurn.Enabled = true;
			}
		}

		/// <summary>
		/// проигрывание выбранного трека.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Play(object sender, EventArgs e)
		{
			Stop(null, null);

			if ((null != treeDisk.SelectedNode) && (null != treeDisk.SelectedNode.Tag))
			{
				m_fStartPos = 0;
				m_fStopPos  = AOPAPI.AOPGetLen((String)treeDisk.SelectedNode.Tag);

				trackPos.Value = 0;

				AOPAPI.AOPPlay((String)treeDisk.SelectedNode.Tag);

				timerPos.Start();
			}
		}

		/// <summary>
		/// остановка проигрывания.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		public void Stop(object sender, EventArgs e)
		{
			timerPos.Stop();

			AOPAPI.AOPStop();

			trackPos.Value = 0;
		}

		/// <summary>
		/// Переход к следующему треку.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Next(object sender, EventArgs e)
		{
			ArrayList listNodes = new ArrayList();
			Stack stackNodes = new Stack();

			stackNodes.Push(treeDisk.Nodes[0]);

			while (stackNodes.Count > 0)
			{
				TreeNode nodeCur = (TreeNode)stackNodes.Pop();

				if (null != nodeCur.Tag)
				{
					listNodes.Add(nodeCur);

					if ((listNodes.Count > 1) && (listNodes[listNodes.Count - 2] == treeDisk.SelectedNode))
					{
						treeDisk.SelectedNode = nodeCur;

						Play(null, null);

						return;
					}
				}

				for (int i = nodeCur.Nodes.Count - 1; i >= 0; i--)
				{
					stackNodes.Push(nodeCur.Nodes[i]);
				}
			}
		}

		/// <summary>
		/// Переход к предыдущему треку.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Prev(object sender, EventArgs e)
		{
			ArrayList listNodes = new ArrayList();
			Stack stackNodes = new Stack();

			stackNodes.Push(treeDisk.Nodes[0]);

			while (stackNodes.Count > 0)
			{
				TreeNode nodeCur = (TreeNode)stackNodes.Pop();

				if (null != nodeCur.Tag)
				{
					listNodes.Add(nodeCur);

					if ((listNodes.Count > 1) && (treeDisk.SelectedNode == nodeCur))
					{
						treeDisk.SelectedNode = (TreeNode)listNodes[listNodes.Count - 2];

						Play(null, null);

						return;
					}
				}

				for (int i = nodeCur.Nodes.Count - 1; i >= 0; i--)
				{
					stackNodes.Push(nodeCur.Nodes[i]);
				}
			}
		}

		/// <summary>
		/// Таймер измения позиции проигрывания .
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void TimerTickPos(object sender, EventArgs e)
		{
			float fPos = AOPAPI.AOPGetPos();

			if (fPos >= m_fStopPos)
			{
				Stop(null, null);
			}
			else
			{
				int iValue = (int)((trackPos.Maximum - trackPos.Minimum) * 
					((fPos - m_fStartPos) / (m_fStopPos - m_fStartPos)));

				if (iValue < trackPos.Minimum)
				{
					trackPos.Value = trackPos.Minimum;
				}
				else if (iValue > trackPos.Maximum)
				{
					trackPos.Value = trackPos.Maximum;
				}
				else
				{
					trackPos.Value = iValue;
				}
			}
		}

		/// <summary>
		/// Изменение позиции проигрывания.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ScrollPosition(object sender, EventArgs e)
		{
			AOPAPI.AOPPlayPosition(m_fStartPos + (float)trackPos.Value / 
				(trackPos.Maximum - trackPos.Minimum) * (m_fStopPos - m_fStartPos));
		}

		/// <summary>
		/// Обработка нажатия на дерево.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void TreeClick(object sender, EventArgs e)
		{
			//treeDisk.SelectedNode = treeDisk.GetNodeAt(treeDisk.PointToClient(Cursor.Position));
		}

		/// <summary>
		/// Добавление дерева в clipboard.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void AddClipboard(object sender, EventArgs e)
		{
			String strText   = "";
			Stack stackNode  = new Stack();
			Stack stackLevel = new Stack();

			stackNode.Push(treeDisk.Nodes[0]);
			stackLevel.Push(0);

			while (stackNode.Count > 0)
			{
				TreeNode nodeCur = (TreeNode)stackNode.Pop();
				int iLevelNode = (int)Convert.ToInt32(stackLevel.Pop());

				for (int i = 0; i < iLevelNode; i++)
				{
					strText += "\t";
				}

				strText += nodeCur.Text;
				strText += "\r\n";

				for (int i = nodeCur.Nodes.Count - 1; i >= 0; i--)
				{
					stackNode.Push(nodeCur.Nodes[i]);
					stackLevel.Push(iLevelNode + 1);
				}
			}

			strText += "\r\n";
			strText += "Create by Audio One Pack";

			if (strText.Length > 0)
			{
				Clipboard.SetText(strText);
			}
		}

		/// <summary>
		/// Возврат выделенной ноды.
		/// </summary>
		/// <returns></returns>
		public TreeNode GetSelectedNode()
		{
			return treeDisk.SelectedNode;
		}

		/// <summary>
		/// Удаление пустых нод.
		/// </summary>
		/// <param name="nodeStart">нода, для сканирования ее дочерних нод</param>
		public void DeleteEmptyNodes(TreeNode nodeStart)
		{
			// получаем список всех дочерних нод
			List<TreeNode> arrNodes = new List<TreeNode>();

			Stack stackNodes = new Stack();

			stackNodes.Push(nodeStart);

			while (stackNodes.Count > 0)
			{
				TreeNode nodeCur = (TreeNode)stackNodes.Pop();

				if (null == nodeCur.Tag)
				{
					arrNodes.Add(nodeCur);
				}

				for (int i = nodeCur.Nodes.Count - 1; i >= 0; i--)
				{
					stackNodes.Push(nodeCur.Nodes[i]);
				}
			}

			// сортируем
			arrNodes.Sort(CompareNodes);

			// удаляем
			for (int i = 0; i < arrNodes.Count; i++)
			{
				if (0 == arrNodes[i].Nodes.Count)
				{
					treeDisk.Nodes.Remove(arrNodes[i]);
				}
			}
		}

		/// <summary>
		/// Функция сравнения двух нод для сортировки.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		private static int CompareNodes(TreeNode x, TreeNode y)
		{
			if (x.Level > y.Level)
			{
				return -1;
			}
			else

				if (x.Level == y.Level)
			{
				return 0;
			}
			
			return 1;
		}

		/// <summary>
		/// Поднять выбранную ноду вверх.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void UpNode(object sender, EventArgs e)
		{
			TreeNode nodeUp = treeDisk.SelectedNode.PrevNode;

			if (null != nodeUp)
			{
				TreeNode nodeParent = treeDisk.SelectedNode.Parent;
				TreeNode nodeSave   = treeDisk.SelectedNode;

				nodeParent.Nodes.Remove(nodeSave);
				nodeParent.Nodes.Insert(nodeUp.Index, nodeSave);

				treeDisk.SelectedNode = nodeSave;
			}
		}

		/// <summary>
		/// Опустить выбранную ноду вниз.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void DownNode(object sender, EventArgs e)
		{
			TreeNode nodeDown = treeDisk.SelectedNode.NextNode;

			if (null != nodeDown)
			{
				TreeNode nodeParent = treeDisk.SelectedNode.Parent;
				TreeNode nodeSave   = treeDisk.SelectedNode;

				nodeParent.Nodes.Remove(nodeSave);
				nodeParent.Nodes.Insert(nodeDown.Index + 1, nodeSave);

				treeDisk.SelectedNode = nodeSave;
			}
		}

		/// <summary>
		/// Сдвинуть ноду влево.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void LeftNode(object sender, EventArgs e)
		{
			TreeNode nodeParent = treeDisk.SelectedNode.Parent;

			if ((null != nodeParent) && (null != nodeParent.Parent))
			{
				TreeNode nodeSave = treeDisk.SelectedNode;

				nodeParent.Nodes.Remove(nodeSave);
				nodeParent.Parent.Nodes.Insert(nodeParent.Index + 1, nodeSave);

				treeDisk.SelectedNode = nodeSave;
			}
		}

		/// <summary>
		/// Сдвинуть ноду вправо.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void RightNode(object sender, EventArgs e)
		{
			TreeNode nodeSave = treeDisk.SelectedNode;
			TreeNode nodeCur  = treeDisk.SelectedNode.PrevNode;

			while ((null != nodeCur) && (null != nodeCur.Tag))
			{
				nodeCur = nodeCur.PrevNode;
			}

			if (null != nodeCur)
			{
				nodeSave.Parent.Nodes.Remove(nodeSave);
				nodeCur.Nodes.Add(nodeSave);

				treeDisk.SelectedNode = nodeSave;
			}
		}

		/// <summary>
		/// Завершение операции Drag'n'Drop.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void DragDropFiles(object sender, DragEventArgs e)
		{
			if (e.Data.GetDataPresent(DataFormats.FileDrop))
			{
				string[] strFiles = (string[])e.Data.GetData(DataFormats.FileDrop);

				for (int i = 0; i < strFiles.Length; i++)
				{
					FileAttributes fa = File.GetAttributes(strFiles[i]);

					// директория
					if (FileAttributes.Directory == (FileAttributes.Directory & fa))
					{
						MusicCDAddFolder formAddFolder = new MusicCDAddFolder(this, strFiles[i]);

						formAddFolder.ShowDialog();
					}

					// файл
					else
					{
						AddFile(strFiles[i]);
					}
				}
			}
			else

			if (e.Data.GetDataPresent(typeof(System.Windows.Forms.TreeNode)))
			{
				// перетаскиваемая нода
				TreeNode nodeDrag = (TreeNode)e.Data.GetData(typeof(System.Windows.Forms.TreeNode));

				if (null == nodeDrag)
				{
					return;
				}

				// проверяем возможность перетаскивания (нода назначения не должна быть дочерней)
				TreeNode nodeCur = treeDisk.SelectedNode;
				
				while (null != nodeCur)
				{
					if (nodeCur == nodeDrag)
					{
						return;
					}

					nodeCur = nodeCur.Parent;
				}

				// изменяем позицию ноды
				nodeDrag.Remove();
				treeDisk.SelectedNode.Nodes.Add(nodeDrag);
			}
		}

		/// <summary>
		/// Обработка входа в зону TreeView.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void DragEnterFiles(object sender, DragEventArgs e)
		{
			if (e.Data.GetDataPresent(DataFormats.FileDrop))
			{
				e.Effect = DragDropEffects.Copy;
			}
			else
			{
				e.Effect = DragDropEffects.None;
			}
		}

		/// <summary>
		/// Обработка выхода из зоны dran'n'drop.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void DragLeaveFiles(object sender, EventArgs e)
		{
			treeDisk.Invalidate();
		}

		/// <summary>
		/// Обработка движения элементов при Drag'n'Drop.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void DragOverFiles(object sender, DragEventArgs e)
		{
			if (e.Data.GetDataPresent(DataFormats.FileDrop))
			{
				// получение элемента
				Point    ptnTarget = treeDisk.PointToClient(new Point(e.X, e.Y));
				TreeNode itemNode  = treeDisk.GetNodeAt(ptnTarget.X, ptnTarget.Y);

				if (null != itemNode)
				{
					if (null == itemNode.Tag)
					{
						treeDisk.SelectedNode = itemNode;
					}
					else
					{
						treeDisk.SelectedNode = itemNode.Parent;
					}
				}
				else
				{
					treeDisk.SelectedNode = treeDisk.Nodes[0];
				}
			}
			else

			if (e.Data.GetDataPresent(typeof(System.Windows.Forms.TreeNode)))
			{
				e.Effect = DragDropEffects.Move;

				// получение элемента
				Point    ptnTarget = treeDisk.PointToClient(new Point(e.X, e.Y));
				TreeNode itemNode  = treeDisk.GetNodeAt(ptnTarget.X, ptnTarget.Y);

				if (null != itemNode)
				{
					if (null == itemNode.Tag)
					{
						treeDisk.SelectedNode = itemNode;
					}
					else
					{
						treeDisk.SelectedNode = itemNode.Parent;
					}
				}
				else
				{
					treeDisk.SelectedNode = treeDisk.Nodes[0];
				}
			}
		}

		/// <summary>
		/// Реализация Drag'n'Drop для элементов treeDisk.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void NodeDrag(object sender, ItemDragEventArgs e)
		{
			DoDragDrop(e.Item, DragDropEffects.Move);
		}

		/// <summary>
		/// Обработка нажатия мыши на дереве.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void TreeMouseDown(object sender, MouseEventArgs e)
		{
			treeDisk.SelectedNode = treeDisk.GetNodeAt(treeDisk.PointToClient(Cursor.Position));
		}

		/// <summary>
		/// Прожиг Music CD.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void BurnMusic(object sender, EventArgs e)
		{
			// поиск одноименных нод
			Stack stackNode = new Stack();

			stackNode.Push(treeDisk.Nodes[0]);

			while (stackNode.Count > 0)
			{
				TreeNode nodeCur = (TreeNode)stackNode.Pop();

				if ((null == nodeCur.Tag) && (null != nodeCur.Parent))
				{
					for (int i = 0; i < nodeCur.Parent.Nodes.Count; i++)
					{
						if ((nodeCur != nodeCur.Parent.Nodes[i]) && (nodeCur.Text == nodeCur.Parent.Nodes[i].Text))
						{
							MessageBox.Show(Properties.Resources.IDS_MUSICCD_EXISTDIR);

							if (nodeCur.Index > nodeCur.Parent.Nodes[i].Index)
							{
								treeDisk.SelectedNode = nodeCur;
							}
							else
							{
								treeDisk.SelectedNode = nodeCur.Parent.Nodes[i];
							}

							return;
						}
					}
				}

				for (int i = nodeCur.Nodes.Count - 1; i >= 0; i--)
				{
					stackNode.Push(nodeCur.Nodes[i]);
				}
			}

			// проверка переполнения диска
			if (m_sizeCD.iUsed > m_sizeCD.iSize)
			{
				MessageBox.Show(Properties.Resources.IDS_MUSICCD_ERRORCDSIZE);

				return;
			}
			
			// получение выбранного CD/DVD привода
			AOPAPI.DEVICEINFO devInfo = GetWorkDevice();

			// проверка наличия чистого диска
			if (1 != AOPAPI.AOPIsBlankCD(ref devInfo))
			{
				MessageBox.Show(Properties.Resources.IDS_MUSICCD_INSERTBLANK);

				return;
			}

			// блокировка
			AOPAPI.AOPLock(ref devInfo);

			// вызов формы прожига
			MusicCDBurn formBurn = new MusicCDBurn(m_formAOP, this);

			formBurn.ShowDialog();

			// разблокировка
			AOPAPI.AOPUnLock(ref devInfo);

			// eject tray
			AOPAPI.AOPEjectTray(ref devInfo);

			// load tray
			if (m_formAOP.bMusicCDLoadTray)
			{
				AOPAPI.AOPLoadTray(ref devInfo);
			}
		}

		/// <summary>
		/// Возвращает индекс скорости записи.
		/// </summary>
		/// <returns></returns>
		public int GetWriteSpeed()
		{
			return cbSpeeds.SelectedIndex;
		}

		/// <summary>
		/// Возвращает структуру диска.
		/// </summary>
		/// <returns></returns>
		public TreeView GetTreeDisk()
		{
			return treeDisk;
		}
	}
}