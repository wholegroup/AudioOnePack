using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Diagnostics;
using System.Text;

namespace Freedb
{
	/// <summary>
	/// Класс описания трека
	/// </summary>
	public class Track
	{
		public string Artist;
		public string Title;
		public string ExtendedData;

		public Track(string title)
		{
			this.Title = title;
		}
	}

	/// <summary>
	/// Summary description for CDEntry.
	/// </summary>
	public class CDEntry
	{
		private string m_Discid;
		private string m_Artist;
		private string m_Title;
		private string m_Year;
		private string m_Genre;
		private string m_ExtendedData;
		private string m_PlayOrder;

		private List<Track> m_Tracks = new List<Track>();

		public string Discid
		{
			get
			{
				return this.m_Discid;
			}
			set
			{
				this.m_Discid = value;
			}
		}

		/// <summary>
		/// Property Artist (string)
		/// </summary>
		public string Artist
		{
			get
			{
				return this.m_Artist;
			}
			set
			{
				this.m_Artist = value;
			}
		}
		
		/// <summary>
		/// Property Title (string)
		/// </summary>
		public string Title
		{
			get
			{
				return this.m_Title;
			}
			set
			{
				this.m_Title = value;
			}
		}
		
		/// <summary>
		/// Property Year (string)
		/// </summary>
		public string Year
		{
			get
			{
				return this.m_Year;
			}
			set
			{
				this.m_Year = value;
			}
		}

		/// <summary>
		/// Property Genre (string)
		/// </summary>
		public string Genre
		{
			get
			{
				return this.m_Genre;
			}
			set
			{
				this.m_Genre = value;
			}
		}

		/// <summary>
		/// Property Tracks (StringCollection)
		/// </summary>
		/// 
		//public TrackCollection Tracks
		public List<Track> Tracks
		{
			get
			{
				return this.m_Tracks;
			}
			set
			{
				this.m_Tracks = value;
			}
		}

		
		/// <summary>
		/// Property ExtendedData (string)
		/// </summary>
		public string ExtendedData
		{
			get
			{
				return this.m_ExtendedData;
			}
			set
			{
				this.m_ExtendedData = value;
			}
		}

		
		/// <summary>
		/// Property PlayOrder (string)
		/// </summary>
		public string PlayOrder
		{
			get
			{
				return this.m_PlayOrder;
			}
			set
			{
				this.m_PlayOrder = value;
			}
		}

		public int NumberOfTracks
		{
			get
			{
				return m_Tracks.Count;
			}
		}

		public CDEntry(StringCollection data)
		{
			if (!Parse(data))
			{
				throw new Exception("Unable to Parse CDEntry.");
			}
		}


		private bool Parse(StringCollection data)
		{
			foreach (string line in data)
			{
				// check for comment
				if ('#' == line[0])
				{
					continue;
				}

				int index = line.IndexOf('=');
				
				// couldn't find equal sign have no clue what the data is
				if (-1 == index)
				{
					continue;
				}

				string field = line.Substring(0, index);
				
				index++; // move it past the equal sign

				switch (field)
				{
					case "DISCID":
					{
						this.m_Discid = line.Substring(index);
					
						continue;
					}

					case "DTITLE": // artist / title
					{
						this.m_Artist += line.Substring(index);
						
						continue;
					}

					case "DYEAR":
					{
						this.m_Year = line.Substring(index);
						continue;
					}

					case "DGENRE":
					{
						this.m_Genre += line.Substring(index);
						continue;
					}

					case "EXTD":
					{
						// may be more than one - just concatenate them
						this.m_ExtendedData += line.Substring(index);
						continue;
					}

					case "PLAYORDER":
					{
						this.m_PlayOrder += line.Substring(index);
						continue;
					}

					default:
						//get track info or extended track info
						if (field.StartsWith("TTITLE"))
						{
							int trackNumber = -1;

							// Parse could throw an exception
							try
							{
								trackNumber = int.Parse(field.Substring("TTITLE".Length));
							}
							
							catch (Exception ex)
							{
								Debug.WriteLine("Failed to parse track Number. Reason: " + ex.Message);
								
								continue;
							}

							//may need to concatenate track info
							if (trackNumber < m_Tracks.Count)
							{
								m_Tracks[trackNumber].Title += line.Substring(index);
							}
							else
							{
								Track track = new Track(line.Substring(index));
								
								this.m_Tracks.Add(track);
							}
							
							continue;
						}
						else 
							
						if (field.StartsWith("EXTT"))
						{
							int trackNumber = -1;
						
							// Parse could throw an exception
							try
							{
								trackNumber = int.Parse(field.Substring("EXTT".Length));
							}
							
							catch (Exception ex)
							{
								Debug.WriteLine("Failed to parse track Number. Reason: " + ex.Message);
								
								continue;
							}

							if (trackNumber < 0 || trackNumber >  m_Tracks.Count -1)
							{
								continue;
							}

							m_Tracks[trackNumber].ExtendedData += line.Substring(index);
						}

						continue;
				} 
			}

			//split the title and artist from DTITLE;
			// see if we have a slash
			int slash = this.m_Artist.IndexOf(" / ");
			if (slash == -1)
			{
				this.m_Title= m_Artist;
			}
			else
			{
				string titleArtist = m_Artist;
				this.m_Artist = titleArtist.Substring(0,slash);
				slash +=3; // move past " / "
				this.m_Title  = titleArtist.Substring(slash );
			}

			//split the title and artist from TTITLE;
			// see if we have a slash
			foreach (Track track in this.m_Tracks)
			{
				int iSlash = track.Title.IndexOf(" / ");
				
				if (-1 == iSlash)
				{
					track.Artist = this.m_Artist;
				}
				else
				{
					string strArtist = track.Title;

					track.Artist = strArtist.Substring(0, iSlash);
					track.Title  = strArtist.Substring(iSlash + 3);
				}
			}

			return true;
		}
	}
}
