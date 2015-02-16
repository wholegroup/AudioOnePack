#region COPYRIGHT (c) 2004 by Brian Weeres
/* Copyright (c) 2004 by Brian Weeres
 * 
 * Email: bweeres@protegra.com; bweeres@hotmail.com
 * 
 * Permission to use, copy, modify, and distribute this software for any
 * purpose is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * If you modify it then please indicate so. 
 *
 * The software is provided "AS IS" and there are no warranties or implied warranties.
 * In no event shall Brian Weeres and/or Protegra Technology Group be liable for any special, 
 * direct, indirect, or consequential damages or any damages whatsoever resulting for any reason 
 * out of the use or performance of this software
 * 
 */
#endregion
using System;
using System.Text;
using System.Net;
using System.IO;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Diagnostics;
using System.Threading;

namespace Freedb
{
	/// <summary>
	/// Summary description for FreedbHelper.
	/// </summary>
	public class FreedbHelper
	{
		private string m_cddbURL = "http://freedb.freedb.org/~cddb/cddb.cgi";
		private string m_UserName;
		private string m_Hostname;
		private string m_ClientName;
		private string m_Version;
		private string m_ProtocolLevel = "6";
		

		#region Constants for Freedb commands
		public class Commands
		{
			public const string CMD_HELLO	= "hello";
			public const string CMD_READ	= "cddb+read";
			public const string CMD_QUERY	= "cddb+query";
			public const string CMD_SITES	= "sites";
			public const string CMD_PROTO	= "proto";
			public const string CMD_CATEGORIES	= "cddb+lscat";
			public const string CMD	= "cmd="; // will never use without the equals so put it here
			public const string CMD_TERMINATOR	= "."; 
		}
		#endregion


		#region Constants for Freedb ResponseCodes
		public class ResponseCodes
		{
			public const string CODE_210 = "210"; // Okay // or in a query multiple exact matches
			public const string CODE_401 = "401"; // sites: no site information available
			public const string CODE_402 = "402"; // Server Error
			
			public const string CODE_500 = "500"; // Invalid command, invalid parameters, etc.

			//query codes
			public const string CODE_200 = "200"; // Exact match 
			public const string CODE_211 = "211"; // InExact matches found - list follows
			public const string CODE_202 = "202"; // No match 
			public const string CODE_403 = "403"; // Database entry is corrupt
			public const string CODE_409 = "409"; // No Handshake

			// our own code
			public const string CODE_INVALID = "-1"; // Invalid code 
		}
		#endregion

		
		#region Public Properties
		
		/// <summary>
		/// Property Version (string)
		/// </summary>
		public string Version
		{
			get
			{
				return this.m_Version;
			}
			set
			{
				this.m_Version = value;
			}
		}

		/// <summary>
		/// Property ClientName (string)
		/// </summary>
		public string ClientName
		{
			get
			{
				return this.m_ClientName;
			}
			set
			{
				this.m_ClientName = value;
			}
		}
		
		/// <summary>
		/// Property Hostname (string)
		/// </summary>
		public string Hostname
		{
			get
			{
				return this.m_Hostname;
			}
			set
			{
				this.m_Hostname = value;
			}
		}
		
		/// <summary>
		/// Property UserName (string)
		/// </summary>
		public string UserName
		{
			get
			{
				return this.m_UserName;
			}
			set
			{
				this.m_UserName = value;
			}
		}

		#endregion

		/// <summary>
		/// Read Entry from the database. 
		/// </summary>
		/// <param name="qr">A QueryResult object that is created by performing a query</param>
		/// <param name="cdEntry">out parameter - CDEntry object</param>
		/// <returns></returns>
		public string Read(QueryResult qr, out CDEntry cdEntry)
		{
			Debug.Assert(qr != null);
			cdEntry = null;
			
			StringCollection coll = null;
			StringBuilder builder = new StringBuilder(FreedbHelper.Commands.CMD_READ);
			builder.Append("+");
			builder.Append(qr.Category);
			builder.Append("+");
			builder.Append(qr.Discid);

			//make call
			try
			{
				coll = Call(builder.ToString());
			}
			
			catch (Exception ex)
			{
				string msg = "Error performing cddb read.";
				Exception newex = new Exception(msg,ex);
				throw newex ;
			}

			// check if results came back
			if (coll.Count < 0)
			{
				string msg = "No results returned from cddb read.";
				Exception ex = new Exception(msg,null);
				throw ex;
			}

			string code = GetCode(coll[0]);
			if (ResponseCodes.CODE_INVALID == code)
			{
				string msg = "Unable to process results for cddb read. Returned Data: " + coll[0];
				Exception ex = new Exception(msg, null);
				throw ex;
			}

			switch (code)
			{
				case ResponseCodes.CODE_500:
					return ResponseCodes.CODE_500;

				case ResponseCodes.CODE_401: // entry not found
				case ResponseCodes.CODE_402: // server error
				case ResponseCodes.CODE_403: // Database entry is corrupt
				case ResponseCodes.CODE_409: // No handshake
					return code;

				case ResponseCodes.CODE_210: // good 
				{
					coll.RemoveAt(0); // remove the 210
					cdEntry = new CDEntry(coll);
					return ResponseCodes.CODE_210;
				}
				default:
					return ResponseCodes.CODE_500;
			}
		}


		/// <summary>
		/// Query the freedb server to see if there is information on this cd
		/// </summary>
		/// <param name="querystring"></param>
		/// <param name="queryResult"></param>
		/// <param name="queryResultsColl"></param>
		/// <returns></returns>
		public string Query(string querystring, out QueryResult queryResult, out List<QueryResult> queryResultsColl)
		{
			queryResult = null;
			queryResultsColl = null;
			StringCollection coll = null;

			StringBuilder builder = new StringBuilder(FreedbHelper.Commands.CMD_QUERY);
			builder.Append("+");
			builder.Append(querystring);
			
			//make call
			try
			{
				coll = Call(builder.ToString());
			}
			
			catch (Exception ex)
			{
				Exception newex = new Exception("Unable to perform cddb query.", ex);
				throw newex ;
			}
			
			// check if results came back
			if (0 > coll.Count)
			{
				Exception ex = new Exception("No results returned from cddb query.", null);
				throw ex;
			}

			//coll[0]	"200 misc a60e780e Depeche Mode / Music For The Masses"	string
			string code = GetCode(coll[0]);
			//code = GetCode("200 misc a60e780e Depeche Mode / Music For The Masses");

			if (code == ResponseCodes.CODE_INVALID)
			{
				string msg = "Unable to process results returned for query: Data returned: " + coll[0];
				Exception ex = new Exception (msg,null);
				throw ex;
			}

			switch (code)
			{
				case ResponseCodes.CODE_500:
					return ResponseCodes.CODE_500;
			
				// Multiple results were returned
				// Put them into a queryResultCollection object
				case ResponseCodes.CODE_211:
				case ResponseCodes.CODE_210:
				{
					queryResultsColl = new List<QueryResult>();
					
					//remove the 210 or 211
					coll.RemoveAt(0);
					
					foreach (string line in coll)
					{
						QueryResult result = new QueryResult(line,true);
						queryResultsColl.Add(result);
					}
				
					return ResponseCodes.CODE_211;
				}
			
				// exact match 
				case ResponseCodes.CODE_200:
				{
					queryResult = new QueryResult(coll[0]);
					
					return ResponseCodes.CODE_200;
				}

				//not found
				case ResponseCodes.CODE_202:
					return ResponseCodes.CODE_202;

				//Database entry is corrupt
				case ResponseCodes.CODE_403:
					return ResponseCodes.CODE_403;

					//no handshake
				case ResponseCodes.CODE_409:
					return ResponseCodes.CODE_409;
					
				default:
					return ResponseCodes.CODE_500;
			}
		}


		/// <summary>
		/// Call the Freedb server using the specified command and the current site
		/// If the current site is null use the default server
		/// </summary>
		/// <param name="command">The command to be exectued</param>
		/// <returns>StringCollection</returns>
		private StringCollection Call(string command)
		{
			return Call(command, m_cddbURL);
		}


		/// <summary>
		/// Call the Freedb server using the specified command and the specified url
		/// The command should not include the cmd= and hello and proto parameters.
		/// They will be added automatically
		/// </summary>
		/// <param name="command">The command to be exectued</param>
		/// <param name="url">The Freedb server to use</param>
		/// <returns>StringCollection</returns>
		private StringCollection Call(string commandIn, string url)
		{
			StringCollection coll     = new StringCollection();
			StreamReader     reader   = null;
			HttpWebResponse  response = null;

			try
			{
				string command = BuildCommand(Commands.CMD + commandIn);

				HttpWebRequest req = (HttpWebRequest)WebRequest.Create(url + "?" + command);
				//req.ContentType = "text/plain";
				// we are using th POST method of calling the http server. We could have also used the GET method
				//req.Method = "POST";

				//Make the call. Note this is a synchronous call
				response = (HttpWebResponse)req.GetResponse();

				//put the results into a StreamReader
				reader = new StreamReader(response.GetResponseStream(), System.Text.Encoding.UTF8);
				
				// add each line to the StringCollection until we get the terminator
				string line;

				while (null != (line = reader.ReadLine()))
				{
					if (line.StartsWith(Commands.CMD_TERMINATOR))
					{
						break;
					}
					else
					{
						coll.Add(line);
					}
				}
			}
			catch (System.Exception ex)
			{
				throw ex;
			}
			finally
			{
				if (null != response)
				{
					response.Close();
				}

				if (null != reader)
				{
					reader.Close();
				}
			}

			return coll;
		}


		/// <summary>
		/// Given a specific command add on the hello and proto which are requied for an http call
		/// </summary>
		/// <param name="command"></param>
		/// <returns></returns>
		public string BuildCommand(string command)
		{
			StringBuilder builder = new StringBuilder(command);

			builder.Append("&");
			builder.Append(Commands.CMD_HELLO);
			builder.Append("=");
			builder.Append(m_UserName);
			builder.Append("+");
			builder.Append(this.m_Hostname);
			builder.Append("+");
			builder.Append(this.ClientName);
			builder.Append("+");
			builder.Append(this.m_Version);
			builder.Append("&");
			builder.Append(Commands.CMD_PROTO);
			builder.Append("=");
			builder.Append(m_ProtocolLevel);

			return builder.ToString();
		}


		/// <summary>
		/// given the first line of a result set return the CDDB code
		/// </summary>
		/// <param name="firstLine"></param>
		/// <returns></returns>
		private string GetCode(string firstLine)
		{
			firstLine = firstLine.Trim();
			
			int index = firstLine.IndexOf(' ');

			if (-1 != index)
			{
				firstLine = firstLine.Substring(0, index);
			}
			else
			{
				return ResponseCodes.CODE_INVALID;
			}

			return firstLine;
		}
	}
}
