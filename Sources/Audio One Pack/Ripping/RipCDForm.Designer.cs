namespace AudioOnePack
{
	partial class RipCDForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(RipCDForm));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label10 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.cbSpeeds = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.cbDeviceName = new System.Windows.Forms.ComboBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.cbGenre = new System.Windows.Forms.ComboBox();
            this.textYear = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.listTrack = new System.Windows.Forms.TrackListView();
            this.columnTrack = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnArtist = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnTitle = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnLength = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnStart = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.menuRip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.playToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem4 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.selectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.selectAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.copyListToClipboardToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.textTitle = new System.Windows.Forms.TextBox();
            this.textArtist = new System.Windows.Forms.TextBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.trackVolume = new System.Windows.Forms.TrackBar();
            this.trackPos = new System.Windows.Forms.TrackBar();
            this.btnPlay = new System.Windows.Forms.Button();
            this.btnStop = new System.Windows.Forms.Button();
            this.btnNextTrack = new System.Windows.Forms.Button();
            this.btnPrevTrack = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.cbQuality = new System.Windows.Forms.ComboBox();
            this.cbFormat = new System.Windows.Forms.ComboBox();
            this.cbSingle = new System.Windows.Forms.CheckBox();
            this.timerPos = new System.Windows.Forms.Timer(this.components);
            this.folderRip = new System.Windows.Forms.FolderBrowserDialog();
            this.btnSettings = new System.Windows.Forms.Button();
            this.btnAbout = new System.Windows.Forms.Button();
            this.btnQuit = new System.Windows.Forms.Button();
            this.btnStartRip = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.menuRip.SuspendLayout();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackVolume)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackPos)).BeginInit();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.button2);
            this.groupBox1.Controls.Add(this.cbSpeeds);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.cbDeviceName);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(589, 49);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "CD/DVD device list";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(407, 22);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(79, 13);
            this.label10.TabIndex = 20;
            this.label10.Text = "Reading speed";
            // 
            // button2
            // 
            this.button2.FlatAppearance.BorderSize = 3;
            this.button2.Image = global::AudioOnePack.Properties.Resources.refresh;
            this.button2.Location = new System.Drawing.Point(549, 12);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(34, 33);
            this.button2.TabIndex = 5;
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.RefreshInfo);
            // 
            // cbSpeeds
            // 
            this.cbSpeeds.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbSpeeds.FormattingEnabled = true;
            this.cbSpeeds.Location = new System.Drawing.Point(489, 19);
            this.cbSpeeds.Name = "cbSpeeds";
            this.cbSpeeds.Size = new System.Drawing.Size(54, 21);
            this.cbSpeeds.TabIndex = 19;
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
            // cbDeviceName
            // 
            this.cbDeviceName.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbDeviceName.FormattingEnabled = true;
            this.cbDeviceName.Location = new System.Drawing.Point(42, 19);
            this.cbDeviceName.Name = "cbDeviceName";
            this.cbDeviceName.Size = new System.Drawing.Size(359, 21);
            this.cbDeviceName.TabIndex = 0;
            this.cbDeviceName.SelectedIndexChanged += new System.EventHandler(this.ChangeDevice);
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Transparent;
            this.groupBox2.Controls.Add(this.cbGenre);
            this.groupBox2.Controls.Add(this.textYear);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.listTrack);
            this.groupBox2.Controls.Add(this.textTitle);
            this.groupBox2.Controls.Add(this.textArtist);
            this.groupBox2.Location = new System.Drawing.Point(12, 67);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(589, 337);
            this.groupBox2.TabIndex = 5;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Track list";
            // 
            // cbGenre
            // 
            this.cbGenre.DropDownHeight = 206;
            this.cbGenre.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbGenre.FormattingEnabled = true;
            this.cbGenre.IntegralHeight = false;
            this.cbGenre.Location = new System.Drawing.Point(479, 16);
            this.cbGenre.Name = "cbGenre";
            this.cbGenre.Size = new System.Drawing.Size(104, 21);
            this.cbGenre.TabIndex = 10;
            // 
            // textYear
            // 
            this.textYear.Location = new System.Drawing.Point(535, 42);
            this.textYear.Name = "textYear";
            this.textYear.Size = new System.Drawing.Size(48, 20);
            this.textYear.TabIndex = 9;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label8.Location = new System.Drawing.Point(496, 45);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(33, 13);
            this.label8.TabIndex = 8;
            this.label8.Text = "Year";
            this.label8.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.Location = new System.Drawing.Point(432, 19);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 13);
            this.label5.TabIndex = 7;
            this.label5.Text = "Genre";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
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
            this.listTrack.CheckBoxes = true;
            this.listTrack.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnTrack,
            this.columnArtist,
            this.columnTitle,
            this.columnLength,
            this.columnStart});
            this.listTrack.ContextMenuStrip = this.menuRip;
            this.listTrack.EmptyText = "Please insert Audio CD";
            this.listTrack.EmptyTextColor = System.Drawing.SystemColors.WindowText;
            this.listTrack.EmptyTextFont = new System.Drawing.Font("Trebuchet MS", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.listTrack.FirstColumnAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.listTrack.Font = new System.Drawing.Font("Trebuchet MS", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.listTrack.FullRowSelect = true;
            this.listTrack.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.listTrack.HideSelection = false;
            this.listTrack.LabelWrap = false;
            this.listTrack.Location = new System.Drawing.Point(6, 68);
            this.listTrack.Margin = new System.Windows.Forms.Padding(1);
            this.listTrack.MultiSelect = false;
            this.listTrack.Name = "listTrack";
            this.listTrack.OwnerDraw = true;
            this.listTrack.Size = new System.Drawing.Size(577, 263);
            this.listTrack.TabIndex = 4;
            this.listTrack.TileSize = new System.Drawing.Size(168, 34);
            this.listTrack.UseCompatibleStateImageBehavior = false;
            this.listTrack.View = System.Windows.Forms.View.Details;
            this.listTrack.ItemChecked += new System.Windows.Forms.ItemCheckedEventHandler(this.CheckedTrack);
            this.listTrack.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.KeyPressTrack);
            // 
            // columnTrack
            // 
            this.columnTrack.Text = "#";
            this.columnTrack.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.columnTrack.Width = 44;
            // 
            // columnArtist
            // 
            this.columnArtist.Text = "Artist";
            this.columnArtist.Width = 169;
            // 
            // columnTitle
            // 
            this.columnTitle.Text = "Title";
            this.columnTitle.Width = 211;
            // 
            // columnLength
            // 
            this.columnLength.Text = "Length";
            this.columnLength.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // columnStart
            // 
            this.columnStart.Text = "Start";
            this.columnStart.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnStart.Width = 67;
            // 
            // menuRip
            // 
            this.menuRip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.playToolStripMenuItem,
            this.toolStripSeparator1,
            this.toolStripMenuItem3,
            this.toolStripMenuItem4,
            this.toolStripMenuItem1,
            this.editToolStripMenuItem,
            this.selectToolStripMenuItem,
            this.selectAllToolStripMenuItem,
            this.toolStripMenuItem2,
            this.copyListToClipboardToolStripMenuItem});
            this.menuRip.Name = "contextMenuStrip1";
            this.menuRip.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
            this.menuRip.Size = new System.Drawing.Size(230, 176);
            this.menuRip.Opened += new System.EventHandler(this.OpenMenu);
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
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(226, 6);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Image = global::AudioOnePack.Properties.Resources.refresh_small;
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.R)));
            this.toolStripMenuItem3.Size = new System.Drawing.Size(229, 22);
            this.toolStripMenuItem3.Text = "Refresh";
            this.toolStripMenuItem3.Click += new System.EventHandler(this.RefreshInfo);
            // 
            // toolStripMenuItem4
            // 
            this.toolStripMenuItem4.Name = "toolStripMenuItem4";
            this.toolStripMenuItem4.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.G)));
            this.toolStripMenuItem4.Size = new System.Drawing.Size(229, 22);
            this.toolStripMenuItem4.Text = "To receive CDDB info";
            this.toolStripMenuItem4.Click += new System.EventHandler(this.GetCDDBInfo);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(226, 6);
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.ShortcutKeyDisplayString = "Enter";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.editToolStripMenuItem.Text = "Edit name";
            this.editToolStripMenuItem.Click += new System.EventHandler(this.EditTitleTrack);
            // 
            // selectToolStripMenuItem
            // 
            this.selectToolStripMenuItem.Image = global::AudioOnePack.Properties.Resources.add;
            this.selectToolStripMenuItem.Name = "selectToolStripMenuItem";
            this.selectToolStripMenuItem.ShortcutKeyDisplayString = "Space";
            this.selectToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.selectToolStripMenuItem.Text = "Select";
            this.selectToolStripMenuItem.Click += new System.EventHandler(this.SelectTrack);
            // 
            // selectAllToolStripMenuItem
            // 
            this.selectAllToolStripMenuItem.Name = "selectAllToolStripMenuItem";
            this.selectAllToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.A)));
            this.selectAllToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.selectAllToolStripMenuItem.Text = "Select All";
            this.selectAllToolStripMenuItem.Click += new System.EventHandler(this.SelectAllTracks);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(226, 6);
            // 
            // copyListToClipboardToolStripMenuItem
            // 
            this.copyListToClipboardToolStripMenuItem.Name = "copyListToClipboardToolStripMenuItem";
            this.copyListToClipboardToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.copyListToClipboardToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.copyListToClipboardToolStripMenuItem.Text = "Copy list to clipboard";
            this.copyListToClipboardToolStripMenuItem.Click += new System.EventHandler(this.ListToClipboard);
            // 
            // textTitle
            // 
            this.textTitle.Location = new System.Drawing.Point(42, 42);
            this.textTitle.Name = "textTitle";
            this.textTitle.Size = new System.Drawing.Size(444, 20);
            this.textTitle.TabIndex = 3;
            // 
            // textArtist
            // 
            this.textArtist.Location = new System.Drawing.Point(42, 16);
            this.textArtist.Name = "textArtist";
            this.textArtist.Size = new System.Drawing.Size(384, 20);
            this.textArtist.TabIndex = 1;
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
            this.groupBox4.Text = "CD Player";
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
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label9);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Controls.Add(this.cbQuality);
            this.groupBox3.Controls.Add(this.cbFormat);
            this.groupBox3.Location = new System.Drawing.Point(618, 67);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(112, 104);
            this.groupBox3.TabIndex = 17;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Output to";
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
            // cbSingle
            // 
            this.cbSingle.AutoSize = true;
            this.cbSingle.Location = new System.Drawing.Point(619, 176);
            this.cbSingle.Name = "cbSingle";
            this.cbSingle.Size = new System.Drawing.Size(104, 17);
            this.cbSingle.TabIndex = 18;
            this.cbSingle.Text = "Single file output";
            this.cbSingle.UseVisualStyleBackColor = true;
            // 
            // timerPos
            // 
            this.timerPos.Interval = 300;
            this.timerPos.Tick += new System.EventHandler(this.TickPos);
            // 
            // btnSettings
            // 
            this.btnSettings.Image = global::AudioOnePack.Properties.Resources.settings;
            this.btnSettings.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnSettings.Location = new System.Drawing.Point(616, 336);
            this.btnSettings.Name = "btnSettings";
            this.btnSettings.Size = new System.Drawing.Size(114, 31);
            this.btnSettings.TabIndex = 16;
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
            this.btnAbout.TabIndex = 15;
            this.btnAbout.Text = "&About";
            this.btnAbout.UseVisualStyleBackColor = true;
            this.btnAbout.Click += new System.EventHandler(this.About);
            // 
            // btnQuit
            // 
            this.btnQuit.Image = global::AudioOnePack.Properties.Resources.quit;
            this.btnQuit.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnQuit.Location = new System.Drawing.Point(616, 442);
            this.btnQuit.Name = "btnQuit";
            this.btnQuit.Size = new System.Drawing.Size(114, 31);
            this.btnQuit.TabIndex = 4;
            this.btnQuit.Text = "&Quit";
            this.btnQuit.UseVisualStyleBackColor = true;
            this.btnQuit.Click += new System.EventHandler(this.Quit);
            // 
            // btnStartRip
            // 
            this.btnStartRip.Enabled = false;
            this.btnStartRip.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnStartRip.Image = global::AudioOnePack.Properties.Resources.rip;
            this.btnStartRip.Location = new System.Drawing.Point(616, 16);
            this.btnStartRip.Name = "btnStartRip";
            this.btnStartRip.Size = new System.Drawing.Size(114, 45);
            this.btnStartRip.TabIndex = 0;
            this.btnStartRip.Text = "Rip Audio CD";
            this.btnStartRip.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnStartRip.UseVisualStyleBackColor = true;
            this.btnStartRip.Click += new System.EventHandler(this.Rip);
            // 
            // RipCDForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(742, 485);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.btnSettings);
            this.Controls.Add(this.cbSingle);
            this.Controls.Add(this.btnAbout);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btnQuit);
            this.Controls.Add(this.btnStartRip);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "RipCDForm";
            this.Text = "RipCD";
            this.TransparencyKey = System.Drawing.SystemColors.Control;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ClosingForm);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.CloseForm);
            this.Load += new System.EventHandler(this.LoadForm);
            this.VisibleChanged += new System.EventHandler(this.VisibleForm);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.menuRip.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackVolume)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackPos)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button btnStartRip;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.ComboBox cbDeviceName;
		private System.Windows.Forms.Button btnQuit;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label3;
		public System.Windows.Forms.TrackListView listTrack;
		private System.Windows.Forms.ColumnHeader columnTrack;
		private System.Windows.Forms.ColumnHeader columnArtist;
		private System.Windows.Forms.ColumnHeader columnTitle;
		public System.Windows.Forms.TextBox textTitle;
        public System.Windows.Forms.TextBox textArtist;
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
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.ComboBox cbGenre;
		public System.Windows.Forms.TextBox textYear;
		private System.Windows.Forms.GroupBox groupBox3;
		private System.Windows.Forms.ComboBox cbQuality;
		private System.Windows.Forms.ComboBox cbFormat;
		private System.Windows.Forms.CheckBox cbSingle;
		private System.Windows.Forms.ColumnHeader columnStart;
		private System.Windows.Forms.ColumnHeader columnLength;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.ContextMenuStrip menuRip;
		private System.Windows.Forms.Timer timerPos;
		private System.Windows.Forms.FolderBrowserDialog folderRip;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.ToolStripMenuItem playToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem selectToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem selectAllToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem copyListToClipboardToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
		private System.Windows.Forms.Label label10;
		private System.Windows.Forms.ComboBox cbSpeeds;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem3;
		private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem4;
	}
}
