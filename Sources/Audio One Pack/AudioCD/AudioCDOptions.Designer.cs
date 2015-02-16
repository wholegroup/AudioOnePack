namespace AudioOnePack
{
	partial class AudioCDOptions
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
			this.btnOK = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.textFolder = new System.Windows.Forms.TextBox();
			this.folderBrowser = new System.Windows.Forms.FolderBrowserDialog();
			this.cbLoadTray = new System.Windows.Forms.CheckBox();
			this.btnSelectFolder = new System.Windows.Forms.Button();
			this.cbClearListAfterBurn = new System.Windows.Forms.CheckBox();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.SuspendLayout();
			// 
			// btnOK
			// 
			this.btnOK.Location = new System.Drawing.Point(220, 113);
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size(75, 23);
			this.btnOK.TabIndex = 0;
			this.btnOK.Text = "OK";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new System.EventHandler(this.OnOK);
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point(301, 113);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(75, 23);
			this.btnCancel.TabIndex = 1;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler(this.OnCancel);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(6, 16);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(58, 13);
			this.label1.TabIndex = 2;
			this.label1.Text = "Temp path";
			// 
			// textFolder
			// 
			this.textFolder.Location = new System.Drawing.Point(70, 13);
			this.textFolder.Name = "textFolder";
			this.textFolder.Size = new System.Drawing.Size(258, 20);
			this.textFolder.TabIndex = 3;
			// 
			// cbLoadTray
			// 
			this.cbLoadTray.AutoSize = true;
			this.cbLoadTray.Location = new System.Drawing.Point(6, 33);
			this.cbLoadTray.Name = "cbLoadTray";
			this.cbLoadTray.Size = new System.Drawing.Size(267, 17);
			this.cbLoadTray.TabIndex = 5;
			this.cbLoadTray.Text = "The CD drive tray should close after it has ejected";
			this.cbLoadTray.UseVisualStyleBackColor = true;
			// 
			// btnSelectFolder
			// 
			this.btnSelectFolder.Image = global::AudioOnePack.Properties.Resources.folder;
			this.btnSelectFolder.Location = new System.Drawing.Point(331, 12);
			this.btnSelectFolder.Name = "btnSelectFolder";
			this.btnSelectFolder.Size = new System.Drawing.Size(26, 22);
			this.btnSelectFolder.TabIndex = 4;
			this.btnSelectFolder.UseVisualStyleBackColor = true;
			this.btnSelectFolder.Click += new System.EventHandler(this.SelectFolder);
			// 
			// cbClearListAfterBurn
			// 
			this.cbClearListAfterBurn.AutoSize = true;
			this.cbClearListAfterBurn.Location = new System.Drawing.Point(6, 11);
			this.cbClearListAfterBurn.Name = "cbClearListAfterBurn";
			this.cbClearListAfterBurn.Size = new System.Drawing.Size(218, 17);
			this.cbClearListAfterBurn.TabIndex = 6;
			this.cbClearListAfterBurn.Text = "Очищать список треков после записи";
			this.cbClearListAfterBurn.UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.cbClearListAfterBurn);
			this.groupBox1.Controls.Add(this.cbLoadTray);
			this.groupBox1.Location = new System.Drawing.Point(12, 7);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(364, 54);
			this.groupBox1.TabIndex = 7;
			this.groupBox1.TabStop = false;
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.textFolder);
			this.groupBox2.Controls.Add(this.label1);
			this.groupBox2.Controls.Add(this.btnSelectFolder);
			this.groupBox2.Location = new System.Drawing.Point(12, 67);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(364, 40);
			this.groupBox2.TabIndex = 8;
			this.groupBox2.TabStop = false;
			// 
			// AudioCDOptions
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(388, 146);
			this.ControlBox = false;
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.btnOK);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "AudioCDOptions";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Options :: Audio CD Creator";
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.groupBox2.ResumeLayout(false);
			this.groupBox2.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox textFolder;
		private System.Windows.Forms.Button btnSelectFolder;
		private System.Windows.Forms.FolderBrowserDialog folderBrowser;
		private System.Windows.Forms.CheckBox cbLoadTray;
		private System.Windows.Forms.CheckBox cbClearListAfterBurn;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.GroupBox groupBox2;
	}
}
