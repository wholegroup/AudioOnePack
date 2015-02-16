namespace AudioOnePack
{
	partial class AnalyzerForm
	{

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AnalyzerForm));
			this.groupBox4 = new System.Windows.Forms.GroupBox();
			this.label7 = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.trackVolume = new System.Windows.Forms.TrackBar();
			this.trackPos = new System.Windows.Forms.TrackBar();
			this.btnPlay = new System.Windows.Forms.Button();
			this.btnStop = new System.Windows.Forms.Button();
			this.btnNextTrack = new System.Windows.Forms.Button();
			this.btnPrevTrack = new System.Windows.Forms.Button();
			this.menuTracks = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.playToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
			this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.addTrackToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.removeTracksToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
			this.selectAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.copyLitToClipboardToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.cbDeviceName = new System.Windows.Forms.ComboBox();
			this.label1 = new System.Windows.Forms.Label();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.button1 = new System.Windows.Forms.Button();
			this.btnQuit = new System.Windows.Forms.Button();
			this.btnSettings = new System.Windows.Forms.Button();
			this.btnAbout = new System.Windows.Forms.Button();
			this.btnAnalyze = new System.Windows.Forms.Button();
			this.btnRemoveTracks = new System.Windows.Forms.Button();
			this.btnAddTracks = new System.Windows.Forms.Button();
			this.btnDiscInfo = new System.Windows.Forms.Button();
			this.dlgAddTrack = new System.Windows.Forms.OpenFileDialog();
			this.timerPos = new System.Windows.Forms.Timer(this.components);
			this.listTrack = new System.Windows.Forms.TrackListView();
			this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.groupBox4.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackVolume)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackPos)).BeginInit();
			this.menuTracks.SuspendLayout();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox4
			// 
			this.groupBox4.Controls.Add(this.label7);
			this.groupBox4.Controls.Add(this.label6);
			this.groupBox4.Controls.Add(this.trackVolume);
			this.groupBox4.Controls.Add(this.trackPos);
			this.groupBox4.Controls.Add(this.btnPlay);
			this.groupBox4.Controls.Add(this.btnStop);
			this.groupBox4.Controls.Add(this.btnNextTrack);
			this.groupBox4.Controls.Add(this.btnPrevTrack);
			this.groupBox4.Location = new System.Drawing.Point(12, 410);
			this.groupBox4.Name = "groupBox4";
			this.groupBox4.Size = new System.Drawing.Size(589, 63);
			this.groupBox4.TabIndex = 13;
			this.groupBox4.TabStop = false;
			this.groupBox4.Text = "Music player";
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point(187, 40);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(42, 13);
			this.label7.TabIndex = 7;
			this.label7.Text = "Volume";
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point(185, 19);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(44, 13);
			this.label6.TabIndex = 6;
			this.label6.Text = "Position";
			// 
			// trackVolume
			// 
			this.trackVolume.AutoSize = false;
			this.trackVolume.LargeChange = 3;
			this.trackVolume.Location = new System.Drawing.Point(235, 40);
			this.trackVolume.Maximum = 20;
			this.trackVolume.Name = "trackVolume";
			this.trackVolume.Size = new System.Drawing.Size(348, 20);
			this.trackVolume.TabIndex = 14;
			this.trackVolume.Scroll += new System.EventHandler(this.ScrollVolume);
			// 
			// trackPos
			// 
			this.trackPos.AutoSize = false;
			this.trackPos.LargeChange = 30;
			this.trackPos.Location = new System.Drawing.Point(235, 19);
			this.trackPos.Maximum = 300;
			this.trackPos.Name = "trackPos";
			this.trackPos.Size = new System.Drawing.Size(348, 20);
			this.trackPos.TabIndex = 34;
			this.trackPos.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackPos.Scroll += new System.EventHandler(this.ScrollPosition);
			// 
			// btnPlay
			// 
			this.btnPlay.Image = global::AudioOnePack.Properties.Resources.play;
			this.btnPlay.Location = new System.Drawing.Point(141, 19);
			this.btnPlay.Name = "btnPlay";
			this.btnPlay.Size = new System.Drawing.Size(38, 38);
			this.btnPlay.TabIndex = 3;
			this.btnPlay.UseVisualStyleBackColor = true;
			this.btnPlay.Click += new System.EventHandler(this.Play);
			// 
			// btnStop
			// 
			this.btnStop.Image = global::AudioOnePack.Properties.Resources.stop;
			this.btnStop.Location = new System.Drawing.Point(97, 19);
			this.btnStop.Name = "btnStop";
			this.btnStop.Size = new System.Drawing.Size(38, 38);
			this.btnStop.TabIndex = 2;
			this.btnStop.UseVisualStyleBackColor = true;
			this.btnStop.Click += new System.EventHandler(this.Stop);
			// 
			// btnNextTrack
			// 
			this.btnNextTrack.Image = global::AudioOnePack.Properties.Resources.next;
			this.btnNextTrack.Location = new System.Drawing.Point(53, 19);
			this.btnNextTrack.Name = "btnNextTrack";
			this.btnNextTrack.Size = new System.Drawing.Size(38, 38);
			this.btnNextTrack.TabIndex = 1;
			this.btnNextTrack.UseVisualStyleBackColor = true;
			this.btnNextTrack.Click += new System.EventHandler(this.Next);
			// 
			// btnPrevTrack
			// 
			this.btnPrevTrack.Image = global::AudioOnePack.Properties.Resources.prev;
			this.btnPrevTrack.Location = new System.Drawing.Point(9, 19);
			this.btnPrevTrack.Name = "btnPrevTrack";
			this.btnPrevTrack.Size = new System.Drawing.Size(38, 38);
			this.btnPrevTrack.TabIndex = 0;
			this.btnPrevTrack.UseVisualStyleBackColor = true;
			this.btnPrevTrack.Click += new System.EventHandler(this.Prev);
			// 
			// menuTracks
			// 
			this.menuTracks.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.playToolStripMenuItem,
            this.toolStripMenuItem1,
            this.toolStripMenuItem3,
            this.toolStripSeparator1,
            this.addTrackToolStripMenuItem,
            this.removeTracksToolStripMenuItem,
            this.toolStripMenuItem2,
            this.selectAllToolStripMenuItem,
            this.copyLitToClipboardToolStripMenuItem});
			this.menuTracks.Name = "menuTracks";
			this.menuTracks.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
			this.menuTracks.Size = new System.Drawing.Size(230, 154);
			// 
			// playToolStripMenuItem
			// 
			this.playToolStripMenuItem.Image = global::AudioOnePack.Properties.Resources.play;
			this.playToolStripMenuItem.Name = "playToolStripMenuItem";
			this.playToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.P)));
			this.playToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
			this.playToolStripMenuItem.Text = "Play";
			this.playToolStripMenuItem.Click += new System.EventHandler(this.Play);
			// 
			// toolStripMenuItem1
			// 
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new System.Drawing.Size(226, 6);
			// 
			// toolStripMenuItem3
			// 
			this.toolStripMenuItem3.Image = global::AudioOnePack.Properties.Resources.analyze;
			this.toolStripMenuItem3.Name = "toolStripMenuItem3";
			this.toolStripMenuItem3.Size = new System.Drawing.Size(229, 22);
			this.toolStripMenuItem3.Text = "Analyze selected tracks";
			this.toolStripMenuItem3.Click += new System.EventHandler(this.AnalyzeSelected);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(226, 6);
			// 
			// addTrackToolStripMenuItem
			// 
			this.addTrackToolStripMenuItem.Image = global::AudioOnePack.Properties.Resources.add;
			this.addTrackToolStripMenuItem.Name = "addTrackToolStripMenuItem";
			this.addTrackToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.Insert;
			this.addTrackToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
			this.addTrackToolStripMenuItem.Text = "Add tracks";
			this.addTrackToolStripMenuItem.Click += new System.EventHandler(this.OpenTrack);
			// 
			// removeTracksToolStripMenuItem
			// 
			this.removeTracksToolStripMenuItem.Image = global::AudioOnePack.Properties.Resources.del;
			this.removeTracksToolStripMenuItem.Name = "removeTracksToolStripMenuItem";
			this.removeTracksToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.Delete;
			this.removeTracksToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
			this.removeTracksToolStripMenuItem.Text = "Remove tracks";
			this.removeTracksToolStripMenuItem.Click += new System.EventHandler(this.RemoveTrack);
			// 
			// toolStripMenuItem2
			// 
			this.toolStripMenuItem2.Name = "toolStripMenuItem2";
			this.toolStripMenuItem2.Size = new System.Drawing.Size(226, 6);
			// 
			// selectAllToolStripMenuItem
			// 
			this.selectAllToolStripMenuItem.Name = "selectAllToolStripMenuItem";
			this.selectAllToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.A)));
			this.selectAllToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
			this.selectAllToolStripMenuItem.Text = "Select All";
			this.selectAllToolStripMenuItem.Click += new System.EventHandler(this.SelectAll);
			// 
			// copyLitToClipboardToolStripMenuItem
			// 
			this.copyLitToClipboardToolStripMenuItem.Name = "copyLitToClipboardToolStripMenuItem";
			this.copyLitToClipboardToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
			this.copyLitToClipboardToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
			this.copyLitToClipboardToolStripMenuItem.Text = "Copy list to clipboard";
			this.copyLitToClipboardToolStripMenuItem.Click += new System.EventHandler(this.AddClipboard);
			// 
			// cbDeviceName
			// 
			this.cbDeviceName.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cbDeviceName.FormattingEnabled = true;
			this.cbDeviceName.Location = new System.Drawing.Point(42, 19);
			this.cbDeviceName.Name = "cbDeviceName";
			this.cbDeviceName.Size = new System.Drawing.Size(425, 21);
			this.cbDeviceName.TabIndex = 0;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(6, 22);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(35, 13);
			this.label1.TabIndex = 4;
			this.label1.Text = "Name";
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.button1);
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Controls.Add(this.cbDeviceName);
			this.groupBox1.Location = new System.Drawing.Point(12, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(589, 49);
			this.groupBox1.TabIndex = 15;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "CD/DVD device list";
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(473, 17);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(110, 23);
			this.button1.TabIndex = 5;
			this.button1.Text = "Start CD analyzing";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.AnalyzeCD);
			// 
			// btnQuit
			// 
			this.btnQuit.Image = global::AudioOnePack.Properties.Resources.quit;
			this.btnQuit.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.btnQuit.Location = new System.Drawing.Point(616, 442);
			this.btnQuit.Name = "btnQuit";
			this.btnQuit.Size = new System.Drawing.Size(114, 31);
			this.btnQuit.TabIndex = 16;
			this.btnQuit.Text = "&Quit";
			this.btnQuit.UseVisualStyleBackColor = true;
			this.btnQuit.Click += new System.EventHandler(this.Quit);
			// 
			// btnSettings
			// 
			this.btnSettings.Image = global::AudioOnePack.Properties.Resources.settings;
			this.btnSettings.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.btnSettings.Location = new System.Drawing.Point(616, 336);
			this.btnSettings.Name = "btnSettings";
			this.btnSettings.Size = new System.Drawing.Size(114, 31);
			this.btnSettings.TabIndex = 19;
			this.btnSettings.Text = "&Options";
			this.btnSettings.UseVisualStyleBackColor = true;
			this.btnSettings.Visible = false;
			// 
			// btnAbout
			// 
			this.btnAbout.Image = global::AudioOnePack.Properties.Resources.about;
			this.btnAbout.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.btnAbout.Location = new System.Drawing.Point(616, 373);
			this.btnAbout.Name = "btnAbout";
			this.btnAbout.Size = new System.Drawing.Size(114, 31);
			this.btnAbout.TabIndex = 18;
			this.btnAbout.Text = "Ab&out...";
			this.btnAbout.UseVisualStyleBackColor = true;
			this.btnAbout.Click += new System.EventHandler(this.About);
			// 
			// btnAnalyze
			// 
			this.btnAnalyze.Enabled = false;
			this.btnAnalyze.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.btnAnalyze.Image = global::AudioOnePack.Properties.Resources.analyze;
			this.btnAnalyze.Location = new System.Drawing.Point(616, 16);
			this.btnAnalyze.Name = "btnAnalyze";
			this.btnAnalyze.Size = new System.Drawing.Size(114, 45);
			this.btnAnalyze.TabIndex = 20;
			this.btnAnalyze.Text = "Analyze";
			this.btnAnalyze.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
			this.btnAnalyze.UseVisualStyleBackColor = true;
			this.btnAnalyze.Click += new System.EventHandler(this.Analyze);
			// 
			// btnRemoveTracks
			// 
			this.btnRemoveTracks.Image = ((System.Drawing.Image)(resources.GetObject("btnRemoveTracks.Image")));
			this.btnRemoveTracks.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.btnRemoveTracks.Location = new System.Drawing.Point(616, 104);
			this.btnRemoveTracks.Name = "btnRemoveTracks";
			this.btnRemoveTracks.Size = new System.Drawing.Size(114, 31);
			this.btnRemoveTracks.TabIndex = 22;
			this.btnRemoveTracks.Text = "&Remove tracks";
			this.btnRemoveTracks.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
			this.btnRemoveTracks.UseVisualStyleBackColor = true;
			this.btnRemoveTracks.Click += new System.EventHandler(this.RemoveTrack);
			// 
			// btnAddTracks
			// 
			this.btnAddTracks.Image = ((System.Drawing.Image)(resources.GetObject("btnAddTracks.Image")));
			this.btnAddTracks.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.btnAddTracks.Location = new System.Drawing.Point(616, 67);
			this.btnAddTracks.Name = "btnAddTracks";
			this.btnAddTracks.Size = new System.Drawing.Size(114, 31);
			this.btnAddTracks.TabIndex = 21;
			this.btnAddTracks.Text = "&Add tracks";
			this.btnAddTracks.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
			this.btnAddTracks.UseVisualStyleBackColor = true;
			this.btnAddTracks.Click += new System.EventHandler(this.OpenTrack);
			// 
			// btnDiscInfo
			// 
			this.btnDiscInfo.Image = global::AudioOnePack.Properties.Resources.disc_info;
			this.btnDiscInfo.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.btnDiscInfo.Location = new System.Drawing.Point(616, 159);
			this.btnDiscInfo.Name = "btnDiscInfo";
			this.btnDiscInfo.Size = new System.Drawing.Size(114, 31);
			this.btnDiscInfo.TabIndex = 23;
			this.btnDiscInfo.Text = "Disc &info";
			this.btnDiscInfo.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
			this.btnDiscInfo.UseVisualStyleBackColor = true;
			this.btnDiscInfo.Click += new System.EventHandler(this.DiscInfo);
			// 
			// dlgAddTrack
			// 
			this.dlgAddTrack.Filter = "All music files|*.mp3;*.mp2;*.mp1;*.ogg;*.wav;*.aif;*.flac;*.cda;*.wma;*.aac;*.m4" +
    "a;*.mp4;*.ac3;*.ape;*.mac;*.mpc;*.mp+;*.mpp;*.ofr;*.ofs;*.spx;*.tta;*.wv;*.m3u;*" +
    ".m3u8|All files (*.*)|*.*";
			this.dlgAddTrack.Multiselect = true;
			// 
			// timerPos
			// 
			this.timerPos.Interval = 1000;
			this.timerPos.Tick += new System.EventHandler(this.TimerTickPos);
			// 
			// listTrack
			// 
			this.listTrack.AllowDrop = true;
			this.listTrack.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("listTrack.BackgroundImage")));
			this.listTrack.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3,
            this.columnHeader4});
			this.listTrack.ContextMenuStrip = this.menuTracks;
			this.listTrack.EmptyTextColor = System.Drawing.SystemColors.WindowText;
			this.listTrack.EmptyTextFont = new System.Drawing.Font("Tahoma", 8F);
			this.listTrack.FirstColumnAlign = System.Windows.Forms.HorizontalAlignment.Right;
			this.listTrack.Font = new System.Drawing.Font("Trebuchet MS", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.listTrack.FullRowSelect = true;
			this.listTrack.HideSelection = false;
			this.listTrack.Location = new System.Drawing.Point(12, 67);
			this.listTrack.Margin = new System.Windows.Forms.Padding(1);
			this.listTrack.Name = "listTrack";
			this.listTrack.OwnerDraw = true;
			this.listTrack.Size = new System.Drawing.Size(589, 334);
			this.listTrack.TabIndex = 14;
			this.listTrack.UseCompatibleStateImageBehavior = false;
			this.listTrack.View = System.Windows.Forms.View.Details;
			this.listTrack.DragDrop += new System.Windows.Forms.DragEventHandler(this.DragDropTrack);
			this.listTrack.DragEnter += new System.Windows.Forms.DragEventHandler(this.DragEnterTrack);
			// 
			// columnHeader1
			// 
			this.columnHeader1.Text = "#";
			this.columnHeader1.Width = 24;
			// 
			// columnHeader2
			// 
			this.columnHeader2.Text = "File name";
			this.columnHeader2.Width = 198;
			// 
			// columnHeader3
			// 
			this.columnHeader3.Text = "Track name";
			this.columnHeader3.Width = 232;
			// 
			// columnHeader4
			// 
			this.columnHeader4.Text = "Audio CD quality";
			this.columnHeader4.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
			this.columnHeader4.Width = 102;
			// 
			// AnalyzerForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(742, 485);
			this.ControlBox = false;
			this.Controls.Add(this.btnDiscInfo);
			this.Controls.Add(this.btnRemoveTracks);
			this.Controls.Add(this.btnSettings);
			this.Controls.Add(this.btnAddTracks);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.listTrack);
			this.Controls.Add(this.btnAbout);
			this.Controls.Add(this.btnAnalyze);
			this.Controls.Add(this.groupBox4);
			this.Controls.Add(this.btnQuit);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "AnalyzerForm";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.Text = "AnalyzerForm";
			this.Load += new System.EventHandler(this.LoadForm);
			this.VisibleChanged += new System.EventHandler(this.VisibleForm);
			this.groupBox4.ResumeLayout(false);
			this.groupBox4.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackVolume)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackPos)).EndInit();
			this.menuTracks.ResumeLayout(false);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox4;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TrackBar trackVolume;
		private System.Windows.Forms.TrackBar trackPos;
		private System.Windows.Forms.Button btnPlay;
		private System.Windows.Forms.Button btnStop;
		private System.Windows.Forms.Button btnNextTrack;
		private System.Windows.Forms.Button btnPrevTrack;
		private System.Windows.Forms.TrackListView listTrack;
		private System.Windows.Forms.ComboBox cbDeviceName;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Button btnQuit;
		private System.Windows.Forms.Button btnSettings;
		private System.Windows.Forms.Button btnAbout;
		private System.Windows.Forms.Button btnAnalyze;
		private System.Windows.Forms.Button btnRemoveTracks;
		private System.Windows.Forms.Button btnAddTracks;
		private System.Windows.Forms.ColumnHeader columnHeader1;
		private System.Windows.Forms.ColumnHeader columnHeader2;
		private System.Windows.Forms.ColumnHeader columnHeader3;
		private System.Windows.Forms.Button btnDiscInfo;
		private System.Windows.Forms.ContextMenuStrip menuTracks;
		private System.Windows.Forms.ToolStripMenuItem playToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem addTrackToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem removeTracksToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
		private System.Windows.Forms.ToolStripMenuItem selectAllToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem copyLitToClipboardToolStripMenuItem;
		private System.Windows.Forms.OpenFileDialog dlgAddTrack;
		private System.Windows.Forms.ColumnHeader columnHeader4;
		private System.Windows.Forms.Timer timerPos;
		private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem3;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
	}
}
