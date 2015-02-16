namespace AudioOnePack
{
	partial class DiscInfoForm
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
			System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("n/a");
			this.btnOK = new System.Windows.Forms.Button();
			this.btnRefresh = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.labelDiscType = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.labelTracks = new System.Windows.Forms.Label();
			this.labelSessions = new System.Windows.Forms.Label();
			this.label7 = new System.Windows.Forms.Label();
			this.label8 = new System.Windows.Forms.Label();
			this.treeDiscInfo = new System.Windows.Forms.TreeView();
			this.labelUsedSpace = new System.Windows.Forms.Label();
			this.labelFreeSpace = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// btnOK
			// 
			this.btnOK.Location = new System.Drawing.Point(372, 208);
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size(75, 23);
			this.btnOK.TabIndex = 0;
			this.btnOK.Text = "OK";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new System.EventHandler(this.OnOk);
			// 
			// btnRefresh
			// 
			this.btnRefresh.Location = new System.Drawing.Point(291, 208);
			this.btnRefresh.Name = "btnRefresh";
			this.btnRefresh.Size = new System.Drawing.Size(75, 23);
			this.btnRefresh.TabIndex = 1;
			this.btnRefresh.Text = "Refresh";
			this.btnRefresh.UseVisualStyleBackColor = true;
			this.btnRefresh.Click += new System.EventHandler(this.Refresh);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(10, 12);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(51, 13);
			this.label1.TabIndex = 2;
			this.label1.Text = "Disc type";
			// 
			// labelDiscType
			// 
			this.labelDiscType.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.labelDiscType.Location = new System.Drawing.Point(67, 12);
			this.labelDiscType.Name = "labelDiscType";
			this.labelDiscType.Size = new System.Drawing.Size(84, 15);
			this.labelDiscType.TabIndex = 3;
			this.labelDiscType.Text = "Empty";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(12, 35);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(49, 13);
			this.label3.TabIndex = 4;
			this.label3.Text = "Sessions";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(22, 57);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(40, 13);
			this.label4.TabIndex = 5;
			this.label4.Text = "Tracks";
			// 
			// labelTracks
			// 
			this.labelTracks.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.labelTracks.Location = new System.Drawing.Point(68, 55);
			this.labelTracks.Name = "labelTracks";
			this.labelTracks.Size = new System.Drawing.Size(26, 15);
			this.labelTracks.TabIndex = 6;
			this.labelTracks.Text = "n/a";
			// 
			// labelSessions
			// 
			this.labelSessions.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.labelSessions.Location = new System.Drawing.Point(68, 33);
			this.labelSessions.Name = "labelSessions";
			this.labelSessions.Size = new System.Drawing.Size(26, 15);
			this.labelSessions.TabIndex = 7;
			this.labelSessions.Text = "n/a";
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point(157, 12);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(64, 13);
			this.label7.TabIndex = 8;
			this.label7.Text = "Used space";
			// 
			// label8
			// 
			this.label8.AutoSize = true;
			this.label8.Location = new System.Drawing.Point(161, 33);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(60, 13);
			this.label8.TabIndex = 9;
			this.label8.Text = "Free space";
			// 
			// treeDiscInfo
			// 
			this.treeDiscInfo.Location = new System.Drawing.Point(12, 81);
			this.treeDiscInfo.Name = "treeDiscInfo";
			treeNode1.Name = "Node0";
			treeNode1.Text = "n/a";
			this.treeDiscInfo.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode1});
			this.treeDiscInfo.Size = new System.Drawing.Size(435, 121);
			this.treeDiscInfo.TabIndex = 10;
			// 
			// labelUsedSpace
			// 
			this.labelUsedSpace.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.labelUsedSpace.Location = new System.Drawing.Point(227, 12);
			this.labelUsedSpace.Name = "labelUsedSpace";
			this.labelUsedSpace.Size = new System.Drawing.Size(87, 15);
			this.labelUsedSpace.TabIndex = 11;
			this.labelUsedSpace.Text = "n/a";
			// 
			// labelFreeSpace
			// 
			this.labelFreeSpace.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.labelFreeSpace.Location = new System.Drawing.Point(227, 35);
			this.labelFreeSpace.Name = "labelFreeSpace";
			this.labelFreeSpace.Size = new System.Drawing.Size(87, 15);
			this.labelFreeSpace.TabIndex = 12;
			this.labelFreeSpace.Text = "n/a";
			// 
			// DiscInfoForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(459, 243);
			this.ControlBox = false;
			this.Controls.Add(this.labelFreeSpace);
			this.Controls.Add(this.labelUsedSpace);
			this.Controls.Add(this.treeDiscInfo);
			this.Controls.Add(this.label8);
			this.Controls.Add(this.label7);
			this.Controls.Add(this.labelSessions);
			this.Controls.Add(this.labelTracks);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.labelDiscType);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.btnRefresh);
			this.Controls.Add(this.btnOK);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "DiscInfoForm";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Disc Info";
			this.Shown += new System.EventHandler(this.FirstShow);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.Button btnRefresh;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label labelDiscType;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label labelTracks;
		private System.Windows.Forms.Label labelSessions;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.TreeView treeDiscInfo;
		private System.Windows.Forms.Label labelUsedSpace;
		private System.Windows.Forms.Label labelFreeSpace;
	}
}