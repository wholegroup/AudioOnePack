namespace AudioOnePack
{
	partial class ConvertForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ConvertForm));
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
            this.addTrackToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.removeTracksToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.selectAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.copyListToClipboardToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.cbQuality = new System.Windows.Forms.ComboBox();
            this.cbFormat = new System.Windows.Forms.ComboBox();
            this.dlgAddTrack = new System.Windows.Forms.OpenFileDialog();
            this.btnRemoveTracks = new System.Windows.Forms.Button();
            this.btnAddTracks = new System.Windows.Forms.Button();
            this.btnSettings = new System.Windows.Forms.Button();
            this.btnAbout = new System.Windows.Forms.Button();
            this.btnConvert = new System.Windows.Forms.Button();
            this.btnQuit = new System.Windows.Forms.Button();
            this.timerPos = new System.Windows.Forms.Timer(this.components);
            this.folderBrowser = new System.Windows.Forms.FolderBrowserDialog();
            this.listTrack = new System.Windows.Forms.TrackListView();
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackVolume)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackPos)).BeginInit();
            this.menuTracks.SuspendLayout();
            this.groupBox3.SuspendLayout();
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
            this.groupBox4.TabIndex = 23;
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
            this.addTrackToolStripMenuItem,
            this.removeTracksToolStripMenuItem,
            this.toolStripMenuItem2,
            this.selectAllToolStripMenuItem,
            this.copyListToClipboardToolStripMenuItem});
            this.menuTracks.Name = "contextMenuStrip1";
            this.menuTracks.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
            this.menuTracks.Size = new System.Drawing.Size(230, 126);
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
            // addTrackToolStripMenuItem
            // 
            this.addTrackToolStripMenuItem.Image = global::AudioOnePack.Properties.Resources.add;
            this.addTrackToolStripMenuItem.Name = "addTrackToolStripMenuItem";
            this.addTrackToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.Insert;
            this.addTrackToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.addTrackToolStripMenuItem.Text = "Add track";
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
            // copyListToClipboardToolStripMenuItem
            // 
            this.copyListToClipboardToolStripMenuItem.Name = "copyListToClipboardToolStripMenuItem";
            this.copyListToClipboardToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.copyListToClipboardToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.copyListToClipboardToolStripMenuItem.Text = "Copy list to clipboard";
            this.copyListToClipboardToolStripMenuItem.Click += new System.EventHandler(this.AddClipboard);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label9);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Controls.Add(this.cbQuality);
            this.groupBox3.Controls.Add(this.cbFormat);
            this.groupBox3.Location = new System.Drawing.Point(616, 62);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(112, 104);
            this.groupBox3.TabIndex = 25;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Convert to";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 57);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(42, 13);
            this.label9.TabIndex = 3;
            this.label9.Text = "Quality:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 16);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(42, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Format:";
            // 
            // cbQuality
            // 
            this.cbQuality.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbQuality.FormattingEnabled = true;
            this.cbQuality.Location = new System.Drawing.Point(6, 74);
            this.cbQuality.Name = "cbQuality";
            this.cbQuality.Size = new System.Drawing.Size(99, 21);
            this.cbQuality.TabIndex = 1;
            // 
            // cbFormat
            // 
            this.cbFormat.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbFormat.FormattingEnabled = true;
            this.cbFormat.Location = new System.Drawing.Point(6, 33);
            this.cbFormat.Name = "cbFormat";
            this.cbFormat.Size = new System.Drawing.Size(99, 21);
            this.cbFormat.TabIndex = 0;
            this.cbFormat.SelectionChangeCommitted += new System.EventHandler(this.ChangeFormat);
            // 
            // dlgAddTrack
            // 
            this.dlgAddTrack.Filter = "All music files|*.mp3;*.mp2;*.mp1;*.ogg;*.wav;*.aif;*.flac;*.cda;*.wma;*.aac;*.m4" +
    "a;*.mp4;*.ac3;*.ape;*.mac;*.mpc;*.mp+;*.mpp;*.ofr;*.ofs;*.spx;*.tta;*.wv;*.m3u;*" +
    ".m3u8|All files (*.*)|*.*";
            this.dlgAddTrack.Multiselect = true;
            // 
            // btnRemoveTracks
            // 
            this.btnRemoveTracks.Image = ((System.Drawing.Image)(resources.GetObject("btnRemoveTracks.Image")));
            this.btnRemoveTracks.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnRemoveTracks.Location = new System.Drawing.Point(616, 209);
            this.btnRemoveTracks.Name = "btnRemoveTracks";
            this.btnRemoveTracks.Size = new System.Drawing.Size(114, 31);
            this.btnRemoveTracks.TabIndex = 13;
            this.btnRemoveTracks.Text = "&Remove tracks";
            this.btnRemoveTracks.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnRemoveTracks.UseVisualStyleBackColor = true;
            this.btnRemoveTracks.Click += new System.EventHandler(this.RemoveTrack);
            // 
            // btnAddTracks
            // 
            this.btnAddTracks.Image = ((System.Drawing.Image)(resources.GetObject("btnAddTracks.Image")));
            this.btnAddTracks.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnAddTracks.Location = new System.Drawing.Point(616, 172);
            this.btnAddTracks.Name = "btnAddTracks";
            this.btnAddTracks.Size = new System.Drawing.Size(114, 31);
            this.btnAddTracks.TabIndex = 12;
            this.btnAddTracks.Text = "&Add tracks";
            this.btnAddTracks.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnAddTracks.UseVisualStyleBackColor = true;
            this.btnAddTracks.Click += new System.EventHandler(this.OpenTrack);
            // 
            // btnSettings
            // 
            this.btnSettings.Image = global::AudioOnePack.Properties.Resources.settings;
            this.btnSettings.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnSettings.Location = new System.Drawing.Point(616, 336);
            this.btnSettings.Name = "btnSettings";
            this.btnSettings.Size = new System.Drawing.Size(114, 31);
            this.btnSettings.TabIndex = 21;
            this.btnSettings.Text = "&Options";
            this.btnSettings.UseVisualStyleBackColor = true;
            this.btnSettings.Click += new System.EventHandler(this.Options);
            // 
            // btnAbout
            // 
            this.btnAbout.Image = global::AudioOnePack.Properties.Resources.about;
            this.btnAbout.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnAbout.Location = new System.Drawing.Point(616, 373);
            this.btnAbout.Name = "btnAbout";
            this.btnAbout.Size = new System.Drawing.Size(114, 31);
            this.btnAbout.TabIndex = 20;
            this.btnAbout.Text = "Ab&out...";
            this.btnAbout.UseVisualStyleBackColor = true;
            this.btnAbout.Click += new System.EventHandler(this.About);
            // 
            // btnConvert
            // 
            this.btnConvert.Enabled = false;
            this.btnConvert.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnConvert.Image = global::AudioOnePack.Properties.Resources.convert;
            this.btnConvert.Location = new System.Drawing.Point(616, 11);
            this.btnConvert.Name = "btnConvert";
            this.btnConvert.Size = new System.Drawing.Size(114, 45);
            this.btnConvert.TabIndex = 4;
            this.btnConvert.Text = "Start converting";
            this.btnConvert.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnConvert.UseVisualStyleBackColor = true;
            this.btnConvert.Click += new System.EventHandler(this.Convert);
            // 
            // btnQuit
            // 
            this.btnQuit.Image = global::AudioOnePack.Properties.Resources.quit;
            this.btnQuit.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnQuit.Location = new System.Drawing.Point(616, 442);
            this.btnQuit.Name = "btnQuit";
            this.btnQuit.Size = new System.Drawing.Size(114, 31);
            this.btnQuit.TabIndex = 2;
            this.btnQuit.Text = "&Quit";
            this.btnQuit.UseVisualStyleBackColor = true;
            this.btnQuit.Click += new System.EventHandler(this.Quit);
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
            this.columnHeader4,
            this.columnHeader1,
            this.columnHeader2});
            this.listTrack.ContextMenuStrip = this.menuTracks;
            this.listTrack.EmptyTextColor = System.Drawing.SystemColors.WindowText;
            this.listTrack.EmptyTextFont = new System.Drawing.Font("Tahoma", 8F);
            this.listTrack.FirstColumnAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.listTrack.Font = new System.Drawing.Font("Trebuchet MS", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.listTrack.FullRowSelect = true;
            this.listTrack.HideSelection = false;
            this.listTrack.Location = new System.Drawing.Point(12, 12);
            this.listTrack.Margin = new System.Windows.Forms.Padding(1);
            this.listTrack.Name = "listTrack";
            this.listTrack.OwnerDraw = true;
            this.listTrack.Size = new System.Drawing.Size(589, 392);
            this.listTrack.TabIndex = 24;
            this.listTrack.UseCompatibleStateImageBehavior = false;
            this.listTrack.View = System.Windows.Forms.View.Details;
            this.listTrack.DragDrop += new System.Windows.Forms.DragEventHandler(this.DragDropTrack);
            this.listTrack.DragEnter += new System.Windows.Forms.DragEventHandler(this.DragEnterTrack);
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "#";
            this.columnHeader4.Width = 24;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "File name";
            this.columnHeader1.Width = 274;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Track name";
            this.columnHeader2.Width = 261;
            // 
            // ConvertForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(743, 485);
            this.ControlBox = false;
            this.Controls.Add(this.listTrack);
            this.Controls.Add(this.btnRemoveTracks);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.btnAddTracks);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.btnConvert);
            this.Controls.Add(this.btnSettings);
            this.Controls.Add(this.btnAbout);
            this.Controls.Add(this.btnQuit);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ConvertForm";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.Text = "ConvertForm";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ClosingForm);
            this.Load += new System.EventHandler(this.LoadForm);
            this.VisibleChanged += new System.EventHandler(this.VisibleForm);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackVolume)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackPos)).EndInit();
            this.menuTracks.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button btnQuit;
		private System.Windows.Forms.Button btnConvert;
		private System.Windows.Forms.GroupBox groupBox4;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TrackBar trackVolume;
		private System.Windows.Forms.TrackBar trackPos;
		private System.Windows.Forms.Button btnPlay;
		private System.Windows.Forms.Button btnStop;
		private System.Windows.Forms.Button btnNextTrack;
        private System.Windows.Forms.Button btnPrevTrack;
		private System.Windows.Forms.Button btnSettings;
		private System.Windows.Forms.Button btnAbout;
		private System.Windows.Forms.TrackListView listTrack;
		private System.Windows.Forms.GroupBox groupBox3;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.ComboBox cbQuality;
		private System.Windows.Forms.ComboBox cbFormat;
		private System.Windows.Forms.Button btnRemoveTracks;
		private System.Windows.Forms.Button btnAddTracks;
		private System.Windows.Forms.ColumnHeader columnHeader1;
		private System.Windows.Forms.ColumnHeader columnHeader2;
		private System.Windows.Forms.OpenFileDialog dlgAddTrack;
		private System.Windows.Forms.ContextMenuStrip menuTracks;
		private System.Windows.Forms.ToolStripMenuItem playToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem addTrackToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem removeTracksToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
		private System.Windows.Forms.ToolStripMenuItem selectAllToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem copyListToClipboardToolStripMenuItem;
		private System.Windows.Forms.ColumnHeader columnHeader4;
		private System.Windows.Forms.Timer timerPos;
		private System.Windows.Forms.FolderBrowserDialog folderBrowser;
	}
}
