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
using System.Windows.Forms;
using System.Threading;
using System.IO;

//
namespace AudioOnePack
{
	static class main
	{
		/// <summary>
		/// Входная точка приложения
		/// </summary>
		[STAThread]
		static void Main()
		{
			// имя мутекса
			string strMutex = "CE5666CD-DD45-43d6-B7D5-8EE337ED399C";

			// проверка существования мутекса с именем strMutex
			try
			{
				Mutex.OpenExisting(strMutex);

				MessageBox.Show(Properties.Resources.IDS_ISRUN_WARNING, Properties.Resources.IDS_ISRUN_CAPTION, 
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);

				return;
			}
			catch (UnauthorizedAccessException ex)
			{
				MessageBox.Show(ex.Message);

				return;
			}
			catch (WaitHandleCannotBeOpenedException)
			{
				
			}
			
			// создание мутекса
			Mutex mutexRun = new Mutex(true, strMutex);

			try
			{
				// инициализация AOPAPI
				if (0 == AOPAPI.AOPInit())
				{
					// запуск программы
					Application.EnableVisualStyles();
					Application.SetCompatibleTextRenderingDefault(false);
					Application.Run(new AOPForm());
				}

				// освобождение ресурсов библиотеки AOPAPI.DLL
				AOPAPI.AOPFree();
			}
			catch (System.Exception exp)
			{
                // Send to e-mail
				Application.Run(new SendError(exp.ToString()));
				
				// запись стека в файл
                //StreamWriter swOut = new StreamWriter(Path.GetDirectoryName(Application.ExecutablePath) + "\\aopstack.err", true);
                //swOut.WriteLine(DateTime.Now);
                //swOut.WriteLine(exp.Message);
                //swOut.WriteLine(exp.StackTrace);
                //swOut.WriteLine("");
                //swOut.Close();
            }

			// удаление мутекса
			mutexRun.ReleaseMutex();
		}
	}
}