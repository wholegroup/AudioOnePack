namespace AudioOnePack
{
	partial class MusicCDOptions
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
			this.cbLoadTray = new System.Windows.Forms.CheckBox();
			this.btnSelectFolder = new System.Windows.Forms.Button();
			this.textFolder = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.btnCancel = new System.Windows.Forms.Button();
			this.btnOK = new System.Windows.Forms.Button();
			this.folderBrowser = new System.Windows.Forms.FolderBrowserDialog();
			this.SuspendLayout();
			// 
			// cbLoadTray
			// 
			this.cbLoadTray.AutoSize = true;
			this.cbLoadTray.Location = new System.Drawing.Point(15, 32);
			this.cbLoadTray.Name = "cbLoadTray";
			this.cbLoadTray.Size = new System.Drawing.Size(267, 17);
			this.cbLoadTray.TabIndex = 11;
			this.cbLoadTray.Text = "The CD drive tray should close after it has ejected";
			this.cbLoadTray.UseVisualStyleBackColor = true;
			// 
			// btnSelectFolder
			// 
			this.btnSelectFolder.Image = global::AudioOnePack.Properties.Resources.folder;
			this.btnSelectFolder.Location = new System.Drawing.Point(337, 5);
			this.btnSelectFolder.Name = "btnSelectFolder";
			this.btnSelectFolder.Size = new System.Drawing.Size(26, 22);
			this.btnSelectFolder.TabIndex = 10;
			this.btnSelectFolder.UseVisualStyleBackColor = true;
			this.btnSelectFolder.Click += new System.EventHandler(this.SelectFolder);
			// 
			// textFolder
			// 
			this.textFolder.Location = new System.Drawing.Point(76, 6);
			this.textFolder.Name = "textFolder";
			this.textFolder.Size = new System.Drawing.Size(255, 20);
			this.textFolder.TabIndex = 9;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(12, 9);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(58, 13);
			this.label1.TabIndex = 8;
			this.label1.Text = "Temp path";
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point(288, 63);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(75, 23);
			this.btnCancel.TabIndex = 7;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler(this.Cancel);
			// 
			// btnOK
			// 
			this.btnOK.Location = new System.Drawing.Point(207, 63);
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size(75, 23);
			this.btnOK.TabIndex = 6;
			this.btnOK.Text = "OK";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new System.EventHandler(this.Ok);
			// 
			// MusicCDOptions
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(371, 98);
			this.ControlBox = false;
			this.Controls.Add(this.cbLoadTray);
			this.Controls.Add(this.btnSelectFolder);
			this.Controls.Add(this.textFolder);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.btnOK);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "MusicCDOptions";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Options";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.CheckBox cbLoadTray;
		private System.Windows.Forms.Button btnSelectFolder;
		private System.Windows.Forms.TextBox textFolder;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Button btnOK;
		private System.Windows.Forms.FolderBrowserDialog folderBrowser;
	}
}
