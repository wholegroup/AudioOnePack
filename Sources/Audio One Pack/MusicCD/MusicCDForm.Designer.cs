namespace AudioOnePack
{
	partial class MusicCDForm
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
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("Node4");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("Node5");
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("Node1", new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode2});
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("Node2");
            System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("Node6");
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("Node7");
            System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("Node8");
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("Node3", new System.Windows.Forms.TreeNode[] {
            treeNode5,
            treeNode6,
            treeNode7});
            System.Windows.Forms.TreeNode treeNode9 = new System.Windows.Forms.TreeNode("Node0", new System.Windows.Forms.TreeNode[] {
            treeNode3,
            treeNode4,
            treeNode8});
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MusicCDForm));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.cbSpeeds = new System.Windows.Forms.ComboBox();
            this.cbDeviceName = new System.Windows.Forms.ComboBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.trackVolume = new System.Windows.Forms.TrackBar();
            this.trackPos = new System.Windows.Forms.TrackBar();
            this.btnPlay = new System.Windows.Forms.Button();
            this.btnStop = new System.Windows.Forms.Button();
            this.btnNextTrack = new System.Windows.Forms.Button();
            this.btnPrevTrack = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.button4 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.btnDelete = new System.Windows.Forms.Button();
            this.btnAddFiles = new System.Windows.Forms.Button();
            this.btnAddFolder = new System.Windows.Forms.Button();
            this.btnCreateFolder = new System.Windows.Forms.Button();
            this.treeDisk = new System.Windows.Forms.TreeView();
            this.contextMenuTree = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.playToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.createNewFolderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addTracksToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addFolderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteNodeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.leftToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.rightToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.upToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.downToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.copyListToClipboardToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.imageListTree = new System.Windows.Forms.ImageList(this.components);
            this.folderBrowserTree = new System.Windows.Forms.FolderBrowserDialog();
            this.openFileTree = new System.Windows.Forms.OpenFileDialog();
            this.timerPos = new System.Windows.Forms.Timer(this.components);
            this.labelSize = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.btnSettings = new System.Windows.Forms.Button();
            this.btnDiscInfo = new System.Windows.Forms.Button();
            this.btnErase = new System.Windows.Forms.Button();
            this.btnAbout = new System.Windows.Forms.Button();
            this.btnBurn = new System.Windows.Forms.Button();
            this.btnQuit = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackVolume)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackPos)).BeginInit();
            this.groupBox2.SuspendLayout();
            this.contextMenuTree.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
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
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Device list";
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
            this.groupBox4.TabIndex = 19;
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
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.button4);
            this.groupBox2.Controls.Add(this.button3);
            this.groupBox2.Controls.Add(this.button2);
            this.groupBox2.Controls.Add(this.button1);
            this.groupBox2.Controls.Add(this.btnDelete);
            this.groupBox2.Controls.Add(this.btnAddFiles);
            this.groupBox2.Controls.Add(this.btnAddFolder);
            this.groupBox2.Controls.Add(this.btnCreateFolder);
            this.groupBox2.Controls.Add(this.treeDisk);
            this.groupBox2.Location = new System.Drawing.Point(12, 67);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(589, 337);
            this.groupBox2.TabIndex = 20;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Music CD structure";
            // 
            // button4
            // 
            this.button4.Image = global::AudioOnePack.Properties.Resources.tree_up;
            this.button4.Location = new System.Drawing.Point(211, 19);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(31, 31);
            this.button4.TabIndex = 17;
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.UpNode);
            // 
            // button3
            // 
            this.button3.Image = global::AudioOnePack.Properties.Resources.tree_down;
            this.button3.Location = new System.Drawing.Point(248, 19);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(31, 31);
            this.button3.TabIndex = 16;
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.DownNode);
            // 
            // button2
            // 
            this.button2.Image = global::AudioOnePack.Properties.Resources.tree_right;
            this.button2.Location = new System.Drawing.Point(285, 19);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(31, 31);
            this.button2.TabIndex = 15;
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.RightNode);
            // 
            // button1
            // 
            this.button1.Image = global::AudioOnePack.Properties.Resources.tree_left;
            this.button1.Location = new System.Drawing.Point(174, 19);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(31, 31);
            this.button1.TabIndex = 14;
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.LeftNode);
            // 
            // btnDelete
            // 
            this.btnDelete.Image = global::AudioOnePack.Properties.Resources.tree_delete;
            this.btnDelete.Location = new System.Drawing.Point(130, 19);
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.Size = new System.Drawing.Size(31, 31);
            this.btnDelete.TabIndex = 13;
            this.btnDelete.UseVisualStyleBackColor = true;
            this.btnDelete.Click += new System.EventHandler(this.Delete);
            // 
            // btnAddFiles
            // 
            this.btnAddFiles.Image = global::AudioOnePack.Properties.Resources.tree_add_file;
            this.btnAddFiles.Location = new System.Drawing.Point(53, 19);
            this.btnAddFiles.Name = "btnAddFiles";
            this.btnAddFiles.Size = new System.Drawing.Size(31, 31);
            this.btnAddFiles.TabIndex = 12;
            this.btnAddFiles.UseVisualStyleBackColor = true;
            this.btnAddFiles.Click += new System.EventHandler(this.AddFiles);
            // 
            // btnAddFolder
            // 
            this.btnAddFolder.Image = global::AudioOnePack.Properties.Resources.tree_add_dirfile;
            this.btnAddFolder.Location = new System.Drawing.Point(86, 19);
            this.btnAddFolder.Name = "btnAddFolder";
            this.btnAddFolder.Size = new System.Drawing.Size(31, 31);
            this.btnAddFolder.TabIndex = 11;
            this.btnAddFolder.UseVisualStyleBackColor = true;
            this.btnAddFolder.Click += new System.EventHandler(this.AddFolder);
            // 
            // btnCreateFolder
            // 
            this.btnCreateFolder.Image = global::AudioOnePack.Properties.Resources.tree_add_dir;
            this.btnCreateFolder.Location = new System.Drawing.Point(9, 19);
            this.btnCreateFolder.Name = "btnCreateFolder";
            this.btnCreateFolder.Size = new System.Drawing.Size(31, 31);
            this.btnCreateFolder.TabIndex = 10;
            this.btnCreateFolder.UseVisualStyleBackColor = true;
            this.btnCreateFolder.Click += new System.EventHandler(this.CreateFolder);
            // 
            // treeDisk
            // 
            this.treeDisk.AllowDrop = true;
            this.treeDisk.ContextMenuStrip = this.contextMenuTree;
            this.treeDisk.FullRowSelect = true;
            this.treeDisk.HideSelection = false;
            this.treeDisk.ImageIndex = 0;
            this.treeDisk.ImageList = this.imageListTree;
            this.treeDisk.Indent = 19;
            this.treeDisk.ItemHeight = 18;
            this.treeDisk.LabelEdit = true;
            this.treeDisk.Location = new System.Drawing.Point(9, 56);
            this.treeDisk.Name = "treeDisk";
            treeNode1.Name = "Node4";
            treeNode1.Text = "Node4";
            treeNode2.Name = "Node5";
            treeNode2.Text = "Node5";
            treeNode3.Name = "Node1";
            treeNode3.Text = "Node1";
            treeNode4.Name = "Node2";
            treeNode4.Text = "Node2";
            treeNode5.Name = "Node6";
            treeNode5.Text = "Node6";
            treeNode6.Name = "Node7";
            treeNode6.Text = "Node7";
            treeNode7.Name = "Node8";
            treeNode7.Text = "Node8";
            treeNode8.Name = "Node3";
            treeNode8.Text = "Node3";
            treeNode9.Name = "Node0";
            treeNode9.Text = "Node0";
            this.treeDisk.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode9});
            this.treeDisk.SelectedImageIndex = 0;
            this.treeDisk.Size = new System.Drawing.Size(574, 275);
            this.treeDisk.TabIndex = 9;
            this.treeDisk.AfterCollapse += new System.Windows.Forms.TreeViewEventHandler(this.CollapseNode);
            this.treeDisk.AfterExpand += new System.Windows.Forms.TreeViewEventHandler(this.ExpandNode);
            this.treeDisk.ItemDrag += new System.Windows.Forms.ItemDragEventHandler(this.NodeDrag);
            this.treeDisk.Click += new System.EventHandler(this.TreeClick);
            this.treeDisk.DragDrop += new System.Windows.Forms.DragEventHandler(this.DragDropFiles);
            this.treeDisk.DragEnter += new System.Windows.Forms.DragEventHandler(this.DragEnterFiles);
            this.treeDisk.DragOver += new System.Windows.Forms.DragEventHandler(this.DragOverFiles);
            this.treeDisk.DragLeave += new System.EventHandler(this.DragLeaveFiles);
            this.treeDisk.MouseDown += new System.Windows.Forms.MouseEventHandler(this.TreeMouseDown);
            // 
            // contextMenuTree
            // 
            this.contextMenuTree.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.playToolStripMenuItem,
            this.toolStripMenuItem2,
            this.createNewFolderToolStripMenuItem,
            this.addTracksToolStripMenuItem,
            this.addFolderToolStripMenuItem,
            this.deleteNodeToolStripMenuItem,
            this.toolStripMenuItem1,
            this.leftToolStripMenuItem,
            this.rightToolStripMenuItem,
            this.upToolStripMenuItem,
            this.downToolStripMenuItem,
            this.toolStripMenuItem3,
            this.copyListToClipboardToolStripMenuItem});
            this.contextMenuTree.Name = "contextMenuTree";
            this.contextMenuTree.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
            this.contextMenuTree.Size = new System.Drawing.Size(230, 242);
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
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(226, 6);
            // 
            // createNewFolderToolStripMenuItem
            // 
            this.createNewFolderToolStripMenuItem.Image = global::AudioOnePack.Properties.Resources.tree_add_dir;
            this.createNewFolderToolStripMenuItem.Name = "createNewFolderToolStripMenuItem";
            this.createNewFolderToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.createNewFolderToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.createNewFolderToolStripMenuItem.Text = "Create new folder";
            this.createNewFolderToolStripMenuItem.Click += new System.EventHandler(this.CreateFolder);
            // 
            // addTracksToolStripMenuItem
            // 
            this.addTracksToolStripMenuItem.Image = global::AudioOnePack.Properties.Resources.tree_add_file;
            this.addTracksToolStripMenuItem.Name = "addTracksToolStripMenuItem";
            this.addTracksToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.addTracksToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.addTracksToolStripMenuItem.Text = "Add tracks";
            this.addTracksToolStripMenuItem.Click += new System.EventHandler(this.AddFiles);
            // 
            // addFolderToolStripMenuItem
            // 
            this.addFolderToolStripMenuItem.Image = global::AudioOnePack.Properties.Resources.tree_add_dirfile;
            this.addFolderToolStripMenuItem.Name = "addFolderToolStripMenuItem";
            this.addFolderToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.F)));
            this.addFolderToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.addFolderToolStripMenuItem.Text = "Add folder";
            this.addFolderToolStripMenuItem.Click += new System.EventHandler(this.AddFolder);
            // 
            // deleteNodeToolStripMenuItem
            // 
            this.deleteNodeToolStripMenuItem.Image = global::AudioOnePack.Properties.Resources.tree_delete;
            this.deleteNodeToolStripMenuItem.Name = "deleteNodeToolStripMenuItem";
            this.deleteNodeToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.Delete;
            this.deleteNodeToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.deleteNodeToolStripMenuItem.Text = "Delete track or folder";
            this.deleteNodeToolStripMenuItem.Click += new System.EventHandler(this.Delete);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(226, 6);
            // 
            // leftToolStripMenuItem
            // 
            this.leftToolStripMenuItem.Image = global::AudioOnePack.Properties.Resources.tree_left;
            this.leftToolStripMenuItem.Name = "leftToolStripMenuItem";
            this.leftToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Left)));
            this.leftToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.leftToolStripMenuItem.Text = "Left";
            this.leftToolStripMenuItem.Click += new System.EventHandler(this.LeftNode);
            // 
            // rightToolStripMenuItem
            // 
            this.rightToolStripMenuItem.Image = global::AudioOnePack.Properties.Resources.tree_right;
            this.rightToolStripMenuItem.Name = "rightToolStripMenuItem";
            this.rightToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Right)));
            this.rightToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.rightToolStripMenuItem.Text = "Right";
            this.rightToolStripMenuItem.Click += new System.EventHandler(this.RightNode);
            // 
            // upToolStripMenuItem
            // 
            this.upToolStripMenuItem.Image = global::AudioOnePack.Properties.Resources.tree_up;
            this.upToolStripMenuItem.Name = "upToolStripMenuItem";
            this.upToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Up)));
            this.upToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.upToolStripMenuItem.Text = "Up";
            this.upToolStripMenuItem.Click += new System.EventHandler(this.UpNode);
            // 
            // downToolStripMenuItem
            // 
            this.downToolStripMenuItem.Image = global::AudioOnePack.Properties.Resources.tree_down;
            this.downToolStripMenuItem.Name = "downToolStripMenuItem";
            this.downToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Down)));
            this.downToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.downToolStripMenuItem.Text = "Down";
            this.downToolStripMenuItem.Click += new System.EventHandler(this.DownNode);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(226, 6);
            // 
            // copyListToClipboardToolStripMenuItem
            // 
            this.copyListToClipboardToolStripMenuItem.Name = "copyListToClipboardToolStripMenuItem";
            this.copyListToClipboardToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.copyListToClipboardToolStripMenuItem.Size = new System.Drawing.Size(229, 22);
            this.copyListToClipboardToolStripMenuItem.Text = "Copy list to clipboard";
            this.copyListToClipboardToolStripMenuItem.Click += new System.EventHandler(this.AddClipboard);
            // 
            // imageListTree
            // 
            this.imageListTree.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageListTree.ImageStream")));
            this.imageListTree.TransparentColor = System.Drawing.Color.Transparent;
            this.imageListTree.Images.SetKeyName(0, "tree_disk.png");
            this.imageListTree.Images.SetKeyName(1, "tree_folder.png");
            this.imageListTree.Images.SetKeyName(2, "tree_folder_open.png");
            this.imageListTree.Images.SetKeyName(3, "tree_music.png");
            // 
            // openFileTree
            // 
            this.openFileTree.FileName = "openFileTree";
            this.openFileTree.Multiselect = true;
            // 
            // timerPos
            // 
            this.timerPos.Interval = 1000;
            this.timerPos.Tick += new System.EventHandler(this.TimerTickPos);
            // 
            // labelSize
            // 
            this.labelSize.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.labelSize.Location = new System.Drawing.Point(6, 19);
            this.labelSize.Name = "labelSize";
            this.labelSize.Size = new System.Drawing.Size(100, 67);
            this.labelSize.TabIndex = 21;
            this.labelSize.Text = "labelSize";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.pictureBox3);
            this.groupBox3.Controls.Add(this.pictureBox2);
            this.groupBox3.Controls.Add(this.pictureBox1);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Controls.Add(this.labelSize);
            this.groupBox3.Location = new System.Drawing.Point(618, 67);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(112, 139);
            this.groupBox3.TabIndex = 22;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Music CD size";
            // 
            // pictureBox3
            // 
            this.pictureBox3.BackColor = System.Drawing.Color.Blue;
            this.pictureBox3.Location = new System.Drawing.Point(26, 122);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(34, 6);
            this.pictureBox3.TabIndex = 27;
            this.pictureBox3.TabStop = false;
            // 
            // pictureBox2
            // 
            this.pictureBox2.BackColor = System.Drawing.Color.Green;
            this.pictureBox2.Location = new System.Drawing.Point(26, 96);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(34, 6);
            this.pictureBox2.TabIndex = 26;
            this.pictureBox2.TabStop = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.Red;
            this.pictureBox1.Location = new System.Drawing.Point(26, 109);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(34, 6);
            this.pictureBox1.TabIndex = 25;
            this.pictureBox1.TabStop = false;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(63, 117);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(27, 13);
            this.label5.TabIndex = 24;
            this.label5.Text = "Size";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(63, 104);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(32, 13);
            this.label4.TabIndex = 23;
            this.label4.Text = "Used";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(63, 91);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(28, 13);
            this.label3.TabIndex = 22;
            this.label3.Text = "Free";
            // 
            // btnSettings
            // 
            this.btnSettings.Image = global::AudioOnePack.Properties.Resources.settings;
            this.btnSettings.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnSettings.Location = new System.Drawing.Point(616, 336);
            this.btnSettings.Name = "btnSettings";
            this.btnSettings.Size = new System.Drawing.Size(114, 31);
            this.btnSettings.TabIndex = 17;
            this.btnSettings.Text = "&Options";
            this.btnSettings.UseVisualStyleBackColor = true;
            this.btnSettings.Click += new System.EventHandler(this.Options);
            // 
            // btnDiscInfo
            // 
            this.btnDiscInfo.Image = global::AudioOnePack.Properties.Resources.disc_info;
            this.btnDiscInfo.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnDiscInfo.Location = new System.Drawing.Point(616, 235);
            this.btnDiscInfo.Name = "btnDiscInfo";
            this.btnDiscInfo.Size = new System.Drawing.Size(114, 31);
            this.btnDiscInfo.TabIndex = 16;
            this.btnDiscInfo.Text = "Disc &info";
            this.btnDiscInfo.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnDiscInfo.UseVisualStyleBackColor = true;
            this.btnDiscInfo.Click += new System.EventHandler(this.DiskInfo);
            // 
            // btnErase
            // 
            this.btnErase.Image = global::AudioOnePack.Properties.Resources.erasecd;
            this.btnErase.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnErase.Location = new System.Drawing.Point(616, 272);
            this.btnErase.Name = "btnErase";
            this.btnErase.Size = new System.Drawing.Size(114, 31);
            this.btnErase.TabIndex = 15;
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
            this.btnAbout.TabIndex = 14;
            this.btnAbout.Text = "Ab&out...";
            this.btnAbout.UseVisualStyleBackColor = true;
            this.btnAbout.Click += new System.EventHandler(this.About);
            // 
            // btnBurn
            // 
            this.btnBurn.Enabled = false;
            this.btnBurn.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnBurn.Image = global::AudioOnePack.Properties.Resources.mp3;
            this.btnBurn.Location = new System.Drawing.Point(616, 16);
            this.btnBurn.Name = "btnBurn";
            this.btnBurn.Size = new System.Drawing.Size(114, 45);
            this.btnBurn.TabIndex = 3;
            this.btnBurn.Text = "Burn Music CD";
            this.btnBurn.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnBurn.UseVisualStyleBackColor = true;
            this.btnBurn.Click += new System.EventHandler(this.BurnMusic);
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
            // MusicCDForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(745, 485);
            this.ControlBox = false;
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btnSettings);
            this.Controls.Add(this.btnDiscInfo);
            this.Controls.Add(this.btnErase);
            this.Controls.Add(this.btnAbout);
            this.Controls.Add(this.btnBurn);
            this.Controls.Add(this.btnQuit);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MusicCDForm";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.Text = "MusicCDForm";
            this.Load += new System.EventHandler(this.LoadForm);
            this.VisibleChanged += new System.EventHandler(this.VisibleForm);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackVolume)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackPos)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.contextMenuTree.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button btnQuit;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.ComboBox cbSpeeds;
		private System.Windows.Forms.ComboBox cbDeviceName;
        private System.Windows.Forms.Button btnBurn;
		private System.Windows.Forms.Button btnSettings;
		private System.Windows.Forms.Button btnDiscInfo;
		private System.Windows.Forms.Button btnErase;
		private System.Windows.Forms.Button btnAbout;
		private System.Windows.Forms.GroupBox groupBox4;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TrackBar trackVolume;
		private System.Windows.Forms.TrackBar trackPos;
		private System.Windows.Forms.Button btnPlay;
		private System.Windows.Forms.Button btnStop;
		private System.Windows.Forms.Button btnNextTrack;
		private System.Windows.Forms.Button btnPrevTrack;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.TreeView treeDisk;
		private System.Windows.Forms.Button btnCreateFolder;
		private System.Windows.Forms.Button btnDelete;
		private System.Windows.Forms.Button btnAddFiles;
		private System.Windows.Forms.Button btnAddFolder;
		private System.Windows.Forms.ImageList imageListTree;
		private System.Windows.Forms.ContextMenuStrip contextMenuTree;
		private System.Windows.Forms.ToolStripMenuItem playToolStripMenuItem;
		private System.Windows.Forms.FolderBrowserDialog folderBrowserTree;
		private System.Windows.Forms.OpenFileDialog openFileTree;
		private System.Windows.Forms.Timer timerPos;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
		private System.Windows.Forms.ToolStripMenuItem createNewFolderToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem addTracksToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem addFolderToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem deleteNodeToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem upToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem downToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
		private System.Windows.Forms.ToolStripMenuItem copyListToClipboardToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem leftToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem rightToolStripMenuItem;
		private System.Windows.Forms.Label labelSize;
		private System.Windows.Forms.GroupBox groupBox3;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.PictureBox pictureBox1;
		private System.Windows.Forms.PictureBox pictureBox3;
		private System.Windows.Forms.PictureBox pictureBox2;
		private System.Windows.Forms.Button button4;
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Button button1;
	}
}
