namespace AudioOnePack
{
	partial class AudioCDForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AudioCDForm));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.cbSpeeds = new System.Windows.Forms.ComboBox();
            this.cbDeviceName = new System.Windows.Forms.ComboBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.listTrack = new System.Windows.Forms.TrackListView();
            this.columnTrack = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnArtist = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnTitle = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnLength = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.menuTracks = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.menuTracksPlay = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem4 = new System.Windows.Forms.ToolStripSeparator();
            this.menuTracksAdd = new System.Windows.Forms.ToolStripMenuItem();
            this.menuTracksRename = new System.Windows.Forms.ToolStripMenuItem();
            this.menuTracksRemove = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.menuTracksUp = new System.Windows.Forms.ToolStripMenuItem();
            this.menuTracksDown = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.selectAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.copySelectTracksToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.textTitle = new System.Windows.Forms.TextBox();
            this.textArtist = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.labelLength = new System.Windows.Forms.Label();
            this.dlgAddTrack = new System.Windows.Forms.OpenFileDialog();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.trackVolume = new System.Windows.Forms.TrackBar();
            this.trackPos = new System.Windows.Forms.TrackBar();
            this.btnPlay = new System.Windows.Forms.Button();
            this.btnStop = new System.Windows.Forms.Button();
            this.btnNextTrack = new System.Windows.Forms.Button();
            this.btnPrevTrack = new System.Windows.Forms.Button();
            this.timerPos = new System.Windows.Forms.Timer(this.components);
            this.btnRemoveTracks = new System.Windows.Forms.Button();
            this.btnSettings = new System.Windows.Forms.Button();
            this.btnAddTracks = new System.Windows.Forms.Button();
            this.btnDiscInfo = new System.Windows.Forms.Button();
            this.btnErase = new System.Windows.Forms.Button();
            this.btnAbout = new System.Windows.Forms.Button();
            this.btnBurn = new System.Windows.Forms.Button();
            this.btnQuit = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.menuTracks.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackVolume)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackPos)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.cbSpeeds);
            this.groupBox1.Controls.Add(this.cbDeviceName);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(589, 49);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "CD/DVD device list";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(454, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(72, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Writing speed";
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
            // cbSpeeds
            // 
            this.cbSpeeds.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbSpeeds.FormattingEnabled = true;
            this.cbSpeeds.Location = new System.Drawing.Point(529, 19);
            this.cbSpeeds.Name = "cbSpeeds";
            this.cbSpeeds.Size = new System.Drawing.Size(54, 21);
            this.cbSpeeds.TabIndex = 3;
            // 
            // cbDeviceName
            // 
            this.cbDeviceName.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbDeviceName.FormattingEnabled = true;
            this.cbDeviceName.Location = new System.Drawing.Point(42, 19);
            this.cbDeviceName.Name = "cbDeviceName";
            this.cbDeviceName.Size = new System.Drawing.Size(406, 21);
            this.cbDeviceName.TabIndex = 0;
            this.cbDeviceName.SelectionChangeCommitted += new System.EventHandler(this.ChangeDevice);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.listTrack);
            this.groupBox2.Controls.Add(this.textTitle);
            this.groupBox2.Controls.Add(this.textArtist);
            this.groupBox2.Location = new System.Drawing.Point(12, 67);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(589, 337);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Track list";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(10, 45);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(32, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "Title";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(6, 19);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Artist";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // listTrack
            // 
            this.listTrack.Activation = System.Windows.Forms.ItemActivation.OneClick;
            this.listTrack.AllowDrop = true;
            this.listTrack.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("listTrack.BackgroundImage")));
            this.listTrack.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnTrack,
            this.columnArtist,
            this.columnTitle,
            this.columnLength});
            this.listTrack.ContextMenuStrip = this.menuTracks;
            this.listTrack.EmptyTextColor = System.Drawing.SystemColors.WindowText;
            this.listTrack.EmptyTextFont = new System.Drawing.Font("Trebuchet MS", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.listTrack.FirstColumnAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.listTrack.Font = new System.Drawing.Font("Trebuchet MS", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.listTrack.FullRowSelect = true;
            this.listTrack.HideSelection = false;
            this.listTrack.LabelWrap = false;
            this.listTrack.Location = new System.Drawing.Point(6, 68);
            this.listTrack.Margin = new System.Windows.Forms.Padding(1);
            this.listTrack.Name = "listTrack";
            this.listTrack.OwnerDraw = true;
            this.listTrack.Size = new System.Drawing.Size(577, 263);
            this.listTrack.TabIndex = 4;
            this.listTrack.TileSize = new System.Drawing.Size(168, 34);
            this.listTrack.UseCompatibleStateImageBehavior = false;
            this.listTrack.View = System.Windows.Forms.View.Details;
            this.listTrack.ItemDrag += new System.Windows.Forms.ItemDragEventHandler(this.ItemDrag);
            this.listTrack.DragDrop += new System.Windows.Forms.DragEventHandler(this.DragDropTrack);
            this.listTrack.DragEnter += new System.Windows.Forms.DragEventHandler(this.DragDropTrackEnter);
            this.listTrack.DragOver += new System.Windows.Forms.DragEventHandler(this.DragDropTrackOver);
            this.listTrack.DragLeave += new System.EventHandler(this.DragDropTrackLeave);
            this.listTrack.DoubleClick += new System.EventHandler(this.RenameTrack);
            this.listTrack.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.KeyPressTracks);
            // 
            // columnTrack
            // 
            this.columnTrack.Text = "#";
            this.columnTrack.Width = 26;
            // 
            // columnArtist
            // 
            this.columnArtist.Text = "Artist";
            this.columnArtist.Width = 193;
            // 
            // columnTitle
            // 
            this.columnTitle.Text = "Title";
            this.columnTitle.Width = 267;
            // 
            // columnLength
            // 
            this.columnLength.Text = "Length";
            this.columnLength.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnLength.Width = 63;
            // 
            // menuTracks
            // 
            this.menuTracks.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuTracksPlay,
            this.toolStripMenuItem4,
            this.menuTracksAdd,
            this.menuTracksRename,
            this.menuTracksRemove,
            this.toolStripMenuItem3,
            this.menuTracksUp,
            this.menuTracksDown,
            this.toolStripMenuItem1,
            this.selectAllToolStripMenuItem,
            this.copySelectTracksToolStripMenuItem});
            this.menuTracks.Name = "menuTracks";
            this.menuTracks.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
            this.menuTracks.Size = new System.Drawing.Size(230, 198);
            this.menuTracks.Opening += new System.ComponentModel.CancelEventHandler(this.OpenContextMenu);
            // 
            // menuTracksPlay
            // 
            this.menuTracksPlay.Image = global::AudioOnePack.Properties.Resources.play;
            this.menuTracksPlay.Name = "menuTracksPlay";
            this.menuTracksPlay.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.P)));
            this.menuTracksPlay.Size = new System.Drawing.Size(229, 22);
            this.menuTracksPlay.Text = "Play";
            this.menuTracksPlay.Click += new System.EventHandler(this.Play);
            // 
            // toolStripMenuItem4
            // 
            this.toolStripMenuItem4.Name = "toolStripMenuItem4";
            this.toolStripMenuItem4.Size = new System.Drawing.Size(226, 6);
            // 
            // menuTracksAdd
            // 
            this.menuTracksAdd.Image = global::AudioOnePack.Properties.Resources.add;
            this.menuTracksAdd.Name = "menuTracksAdd";
            this.menuTracksAdd.ShortcutKeys = System.Windows.Forms.Keys.Insert;
            this.menuTracksAdd.Size = new System.Drawing.Size(229, 22);
            this.menuTracksAdd.Text = "Add track";
            this.menuTracksAdd.Click += new System.EventHandler(this.OpenTrack);
            // 
            // menuTracksRename
            // 
            this.menuTracksRename.Name = "menuTracksRename";
            this.menuTracksRename.ShortcutKeyDisplayString = "Enter";
            this.menuTracksRename.Size = new System.Drawing.Size(229, 22);
            this.menuTracksRename.Text = "Rename track";
            this.menuTracksRename.Click += new System.EventHandler(this.RenameTrack);
            // 
            // menuTracksRemove
            // 
            this.menuTracksRemove.Image = global::AudioOnePack.Properties.Resources.del;
            this.menuTracksRemove.Name = "menuTracksRemove";
            this.menuTracksRemove.ShortcutKeys = System.Windows.Forms.Keys.Delete;
            this.menuTracksRemove.Size = new System.Drawing.Size(229, 22);
            this.menuTracksRemove.Text = "Remove track";
            this.menuTracksRemove.Click += new System.EventHandler(this.RemoveTrack);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(226, 6);
            // 
            // menuTracksUp
            // 
            this.menuTracksUp.Name = "menuTracksUp";
            this.menuTracksUp.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Up)));
            this.menuTracksUp.Size = new System.Drawing.Size(229, 22);
            this.menuTracksUp.Text = "Up";
            this.menuTracksUp.Click += new System.EventHandler(this.UpTracks);
            // 
            // menuTracksDown
            // 
            this.menuTracksDown.Name = "menuTracksDown";
            this.menuTracksDown.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Down)));
            this.menuTracksDown.Size = new System.Drawing.Size(229, 22);
            this.menuTracksDown.Text = "Down";
            this.menuTracksDown.Click += new System.EventHandler(this.DownTracks);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(226, 6);
            // 
            // selectAllToolStripMenuItem
            // 
            this.selectAllToolStripMenuItem.Name = "selectAllToolStripMenuItem";
            this.selectAllToolStripMenuItem.ShortcutKeyDisplayString = "";
            this.selectAllToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.A)));
            this.selectAllToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.selectAllToolStripMenuItem.Text = "Select All";
            this.selectAllToolStripMenuItem.Click += new System.EventHandler(this.SelectAll);
            // 
            // copySelectTracksToolStripMenuItem
            // 
            this.copySelectTracksToolStripMenuItem.Name = "copySelectTracksToolStripMenuItem";
            this.copySelectTracksToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.copySelectTracksToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.copySelectTracksToolStripMenuItem.Text = "Copy list to clipboard";
            this.copySelectTracksToolStripMenuItem.Click += new System.EventHandler(this.AddClipboard);
            // 
            // textTitle
            // 
            this.textTitle.Location = new System.Drawing.Point(42, 42);
            this.textTitle.Name = "textTitle";
            this.textTitle.Size = new System.Drawing.Size(541, 20);
            this.textTitle.TabIndex = 3;
            // 
            // textArtist
            // 
            this.textArtist.Location = new System.Drawing.Point(42, 16);
            this.textArtist.Name = "textArtist";
            this.textArtist.Size = new System.Drawing.Size(541, 20);
            this.textArtist.TabIndex = 1;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.labelLength);
            this.groupBox3.Location = new System.Drawing.Point(618, 67);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(112, 58);
            this.groupBox3.TabIndex = 9;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "CD Length";
            // 
            // labelLength
            // 
            this.labelLength.Font = new System.Drawing.Font("Microsoft Sans Serif", 22F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelLength.Location = new System.Drawing.Point(6, 16);
            this.labelLength.Name = "labelLength";
            this.labelLength.Size = new System.Drawing.Size(102, 39);
            this.labelLength.TabIndex = 0;
            this.labelLength.Text = "00:00";
            this.labelLength.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // dlgAddTrack
            // 
            this.dlgAddTrack.Filter = "All music files|*.mp3;*.mp2;*.mp1;*.ogg;*.wav;*.aif;*.flac;*.cda;*.wma;*.aac;*.m4" +
    "a;*.mp4;*.ac3;*.ape;*.mac;*.mpc;*.mp+;*.mpp;*.ofr;*.ofs;*.spx;*.tta;*.wv;*.m3u;*" +
    ".cue;*.m3u8|All files (*.*)|*.*";
            this.dlgAddTrack.Multiselect = true;
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
            this.groupBox4.TabIndex = 12;
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
            this.btnNextTrack.Click += new System.EventHandler(this.NextTrack);
            // 
            // btnPrevTrack
            // 
            this.btnPrevTrack.Image = global::AudioOnePack.Properties.Resources.prev;
            this.btnPrevTrack.Location = new System.Drawing.Point(9, 19);
            this.btnPrevTrack.Name = "btnPrevTrack";
            this.btnPrevTrack.Size = new System.Drawing.Size(38, 38);
            this.btnPrevTrack.TabIndex = 0;
            this.btnPrevTrack.UseVisualStyleBackColor = true;
            this.btnPrevTrack.Click += new System.EventHandler(this.PrevTrack);
            // 
            // timerPos
            // 
            this.timerPos.Interval = 1000;
            this.timerPos.Tick += new System.EventHandler(this.TimerTickPos);
            // 
            // btnRemoveTracks
            // 
            this.btnRemoveTracks.Image = ((System.Drawing.Image)(resources.GetObject("btnRemoveTracks.Image")));
            this.btnRemoveTracks.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnRemoveTracks.Location = new System.Drawing.Point(616, 172);
            this.btnRemoveTracks.Name = "btnRemoveTracks";
            this.btnRemoveTracks.Size = new System.Drawing.Size(114, 31);
            this.btnRemoveTracks.TabIndex = 11;
            this.btnRemoveTracks.Text = "&Remove tracks";
            this.btnRemoveTracks.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnRemoveTracks.UseVisualStyleBackColor = true;
            this.btnRemoveTracks.Click += new System.EventHandler(this.RemoveTrack);
            // 
            // btnSettings
            // 
            this.btnSettings.Image = global::AudioOnePack.Properties.Resources.settings;
            this.btnSettings.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnSettings.Location = new System.Drawing.Point(616, 336);
            this.btnSettings.Name = "btnSettings";
            this.btnSettings.Size = new System.Drawing.Size(114, 31);
            this.btnSettings.TabIndex = 10;
            this.btnSettings.Text = "&Options";
            this.btnSettings.UseVisualStyleBackColor = true;
            this.btnSettings.Click += new System.EventHandler(this.Options);
            // 
            // btnAddTracks
            // 
            this.btnAddTracks.Image = ((System.Drawing.Image)(resources.GetObject("btnAddTracks.Image")));
            this.btnAddTracks.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnAddTracks.Location = new System.Drawing.Point(616, 135);
            this.btnAddTracks.Name = "btnAddTracks";
            this.btnAddTracks.Size = new System.Drawing.Size(114, 31);
            this.btnAddTracks.TabIndex = 7;
            this.btnAddTracks.Text = "&Add tracks";
            this.btnAddTracks.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnAddTracks.UseVisualStyleBackColor = true;
            this.btnAddTracks.Click += new System.EventHandler(this.OpenTrack);
            // 
            // btnDiscInfo
            // 
            this.btnDiscInfo.Image = global::AudioOnePack.Properties.Resources.disc_info;
            this.btnDiscInfo.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnDiscInfo.Location = new System.Drawing.Point(616, 235);
            this.btnDiscInfo.Name = "btnDiscInfo";
            this.btnDiscInfo.Size = new System.Drawing.Size(114, 31);
            this.btnDiscInfo.TabIndex = 6;
            this.btnDiscInfo.Text = "Disc &info";
            this.btnDiscInfo.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnDiscInfo.UseVisualStyleBackColor = true;
            this.btnDiscInfo.Click += new System.EventHandler(this.DiscInfo);
            // 
            // btnErase
            // 
            this.btnErase.Image = global::AudioOnePack.Properties.Resources.erasecd;
            this.btnErase.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnErase.Location = new System.Drawing.Point(616, 272);
            this.btnErase.Name = "btnErase";
            this.btnErase.Size = new System.Drawing.Size(114, 31);
            this.btnErase.TabIndex = 5;
            this.btnErase.Text = "&Erase CD-RW";
            this.btnErase.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnErase.UseVisualStyleBackColor = true;
            this.btnErase.Click += new System.EventHandler(this.Erase);
            // 
            // btnAbout
            // 
            this.btnAbout.Image = global::AudioOnePack.Properties.Resources.about;
            this.btnAbout.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnAbout.Location = new System.Drawing.Point(616, 373);
            this.btnAbout.Name = "btnAbout";
            this.btnAbout.Size = new System.Drawing.Size(114, 31);
            this.btnAbout.TabIndex = 4;
            this.btnAbout.Text = "Ab&out...";
            this.btnAbout.UseVisualStyleBackColor = true;
            this.btnAbout.Click += new System.EventHandler(this.About);
            // 
            // btnBurn
            // 
            this.btnBurn.Enabled = false;
            this.btnBurn.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnBurn.Image = global::AudioOnePack.Properties.Resources.burn;
            this.btnBurn.Location = new System.Drawing.Point(616, 16);
            this.btnBurn.Name = "btnBurn";
            this.btnBurn.Size = new System.Drawing.Size(114, 45);
            this.btnBurn.TabIndex = 0;
            this.btnBurn.Text = "Burn  Audio CD";
            this.btnBurn.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnBurn.UseVisualStyleBackColor = true;
            this.btnBurn.Click += new System.EventHandler(this.Burn);
            // 
            // btnQuit
            // 
            this.btnQuit.Image = global::AudioOnePack.Properties.Resources.quit;
            this.btnQuit.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnQuit.Location = new System.Drawing.Point(616, 442);
            this.btnQuit.Name = "btnQuit";
            this.btnQuit.Size = new System.Drawing.Size(114, 31);
            this.btnQuit.TabIndex = 1;
            this.btnQuit.Text = "&Quit";
            this.btnQuit.UseVisualStyleBackColor = true;
            this.btnQuit.Click += new System.EventHandler(this.Quit);
            // 
            // AudioCDForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(743, 485);
            this.ControlBox = false;
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.btnRemoveTracks);
            this.Controls.Add(this.btnSettings);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.btnAddTracks);
            this.Controls.Add(this.btnDiscInfo);
            this.Controls.Add(this.btnErase);
            this.Controls.Add(this.btnAbout);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btnBurn);
            this.Controls.Add(this.btnQuit);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AudioCDForm";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Audio One Pack - software for creating audio CDs with CD-Text";
            this.Load += new System.EventHandler(this.LoadForm);
            this.VisibleChanged += new System.EventHandler(this.VisibleForm);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.menuTracks.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackVolume)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackPos)).EndInit();
            this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button btnBurn;
		private System.Windows.Forms.Button btnQuit;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.ComboBox cbDeviceName;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.ComboBox cbSpeeds;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.ColumnHeader columnTrack;
		private System.Windows.Forms.ColumnHeader columnArtist;
		private System.Windows.Forms.ColumnHeader columnLength;
		private System.Windows.Forms.Button btnAbout;
		private System.Windows.Forms.Button btnErase;
		private System.Windows.Forms.Button btnDiscInfo;
		private System.Windows.Forms.Button btnAddTracks;
		private System.Windows.Forms.GroupBox groupBox3;
		private System.Windows.Forms.Label labelLength;
		private System.Windows.Forms.OpenFileDialog dlgAddTrack;
		private System.Windows.Forms.Button btnSettings;
		private System.Windows.Forms.Button btnRemoveTracks;
		private System.Windows.Forms.GroupBox groupBox4;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Button btnPlay;
		private System.Windows.Forms.Button btnStop;
		private System.Windows.Forms.Button btnNextTrack;
		private System.Windows.Forms.Button btnPrevTrack;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TrackBar trackVolume;
        private System.Windows.Forms.TrackBar trackPos;
		private System.Windows.Forms.ContextMenuStrip menuTracks;
		private System.Windows.Forms.ToolStripMenuItem menuTracksRename;
		private System.Windows.Forms.ToolStripMenuItem menuTracksRemove;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
		private System.Windows.Forms.ToolStripMenuItem selectAllToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem copySelectTracksToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem menuTracksPlay;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem4;
		private System.Windows.Forms.ToolStripMenuItem menuTracksAdd;
		private System.Windows.Forms.ToolStripMenuItem menuTracksUp;
		private System.Windows.Forms.ToolStripMenuItem menuTracksDown;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
		private System.Windows.Forms.Timer timerPos;
		public System.Windows.Forms.TrackListView listTrack;
		public System.Windows.Forms.TextBox textTitle;
		public System.Windows.Forms.TextBox textArtist;
		private System.Windows.Forms.ColumnHeader columnTitle;
	}
}
