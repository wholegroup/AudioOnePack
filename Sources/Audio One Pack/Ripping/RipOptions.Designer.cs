namespace AudioOnePack
{
	partial class RipOptions
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
			this.button1 = new System.Windows.Forms.Button();
			this.button2 = new System.Windows.Forms.Button();
			this.btnTemp = new System.Windows.Forms.Button();
			this.textTemp = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.btnSetOutput = new System.Windows.Forms.Button();
			this.textOutput = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.cbNotRequestOutput = new System.Windows.Forms.CheckBox();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.rbAllways = new System.Windows.Forms.RadioButton();
			this.rbAsk = new System.Windows.Forms.RadioButton();
			this.rbNever = new System.Windows.Forms.RadioButton();
			this.folderBrowser = new System.Windows.Forms.FolderBrowserDialog();
			this.cbEject = new System.Windows.Forms.CheckBox();
			this.cbOpenDir = new System.Windows.Forms.CheckBox();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.groupBox3 = new System.Windows.Forms.GroupBox();
			this.button3 = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.groupBox3.SuspendLayout();
			this.SuspendLayout();
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(176, 231);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(75, 23);
			this.button1.TabIndex = 0;
			this.button1.Text = "OK";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.OnOk);
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(257, 231);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(75, 23);
			this.button2.TabIndex = 1;
			this.button2.Text = "Cancel";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new System.EventHandler(this.OnCancel);
			// 
			// btnTemp
			// 
			this.btnTemp.Image = global::AudioOnePack.Properties.Resources.folder;
			this.btnTemp.Location = new System.Drawing.Point(288, 38);
			this.btnTemp.Name = "btnTemp";
			this.btnTemp.Size = new System.Drawing.Size(26, 22);
			this.btnTemp.TabIndex = 7;
			this.btnTemp.UseVisualStyleBackColor = true;
			this.btnTemp.Click += new System.EventHandler(this.ClickBtnTemp);
			// 
			// textTemp
			// 
			this.textTemp.Location = new System.Drawing.Point(75, 39);
			this.textTemp.Name = "textTemp";
			this.textTemp.Size = new System.Drawing.Size(207, 20);
			this.textTemp.TabIndex = 6;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(14, 42);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(58, 13);
			this.label1.TabIndex = 5;
			this.label1.Text = "Temp path";
			// 
			// btnSetOutput
			// 
			this.btnSetOutput.Image = global::AudioOnePack.Properties.Resources.folder;
			this.btnSetOutput.Location = new System.Drawing.Point(288, 12);
			this.btnSetOutput.Name = "btnSetOutput";
			this.btnSetOutput.Size = new System.Drawing.Size(26, 22);
			this.btnSetOutput.TabIndex = 10;
			this.btnSetOutput.UseVisualStyleBackColor = true;
			this.btnSetOutput.Click += new System.EventHandler(this.ClickBtnOutput);
			// 
			// textOutput
			// 
			this.textOutput.Location = new System.Drawing.Point(75, 13);
			this.textOutput.Name = "textOutput";
			this.textOutput.Size = new System.Drawing.Size(207, 20);
			this.textOutput.TabIndex = 9;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(6, 16);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(66, 13);
			this.label2.TabIndex = 8;
			this.label2.Text = "Output path";
			// 
			// cbNotRequestOutput
			// 
			this.cbNotRequestOutput.AutoSize = true;
			this.cbNotRequestOutput.Location = new System.Drawing.Point(6, 60);
			this.cbNotRequestOutput.Name = "cbNotRequestOutput";
			this.cbNotRequestOutput.Size = new System.Drawing.Size(224, 17);
			this.cbNotRequestOutput.TabIndex = 11;
			this.cbNotRequestOutput.Text = "Without request for the output directory ";
			this.cbNotRequestOutput.UseVisualStyleBackColor = true;
			this.cbNotRequestOutput.Click += new System.EventHandler(this.ClickNotRequest);
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.rbAllways);
			this.groupBox1.Controls.Add(this.rbAsk);
			this.groupBox1.Controls.Add(this.rbNever);
			this.groupBox1.Location = new System.Drawing.Point(12, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(320, 47);
			this.groupBox1.TabIndex = 12;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Get inforomation from CDDB database";
			// 
			// rbAllways
			// 
			this.rbAllways.AutoSize = true;
			this.rbAllways.Location = new System.Drawing.Point(149, 19);
			this.rbAllways.Name = "rbAllways";
			this.rbAllways.Size = new System.Drawing.Size(59, 17);
			this.rbAllways.TabIndex = 2;
			this.rbAllways.TabStop = true;
			this.rbAllways.Text = "Always";
			this.rbAllways.UseVisualStyleBackColor = true;
			// 
			// rbAsk
			// 
			this.rbAsk.AutoSize = true;
			this.rbAsk.Location = new System.Drawing.Point(66, 19);
			this.rbAsk.Name = "rbAsk";
			this.rbAsk.Size = new System.Drawing.Size(79, 17);
			this.rbAsk.TabIndex = 1;
			this.rbAsk.TabStop = true;
			this.rbAsk.Text = "On request";
			this.rbAsk.UseVisualStyleBackColor = true;
			// 
			// rbNever
			// 
			this.rbNever.AutoSize = true;
			this.rbNever.Location = new System.Drawing.Point(6, 19);
			this.rbNever.Name = "rbNever";
			this.rbNever.Size = new System.Drawing.Size(54, 17);
			this.rbNever.TabIndex = 0;
			this.rbNever.TabStop = true;
			this.rbNever.Text = "Never";
			this.rbNever.UseVisualStyleBackColor = true;
			// 
			// cbEject
			// 
			this.cbEject.AutoSize = true;
			this.cbEject.Location = new System.Drawing.Point(6, 14);
			this.cbEject.Name = "cbEject";
			this.cbEject.Size = new System.Drawing.Size(238, 17);
			this.cbEject.TabIndex = 13;
			this.cbEject.Text = "The CD driver tray should eject after ripping";
			this.cbEject.UseVisualStyleBackColor = true;
			// 
			// cbOpenDir
			// 
			this.cbOpenDir.AutoSize = true;
			this.cbOpenDir.Location = new System.Drawing.Point(6, 37);
			this.cbOpenDir.Name = "cbOpenDir";
			this.cbOpenDir.Size = new System.Drawing.Size(243, 17);
			this.cbOpenDir.TabIndex = 14;
			this.cbOpenDir.Text = "Открывать папку с полученными файлами";
			this.cbOpenDir.UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.cbOpenDir);
			this.groupBox2.Controls.Add(this.cbNotRequestOutput);
			this.groupBox2.Controls.Add(this.cbEject);
			this.groupBox2.Location = new System.Drawing.Point(12, 65);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(320, 84);
			this.groupBox2.TabIndex = 15;
			this.groupBox2.TabStop = false;
			// 
			// groupBox3
			// 
			this.groupBox3.Controls.Add(this.textOutput);
			this.groupBox3.Controls.Add(this.label1);
			this.groupBox3.Controls.Add(this.textTemp);
			this.groupBox3.Controls.Add(this.btnSetOutput);
			this.groupBox3.Controls.Add(this.btnTemp);
			this.groupBox3.Controls.Add(this.label2);
			this.groupBox3.Location = new System.Drawing.Point(12, 155);
			this.groupBox3.Name = "groupBox3";
			this.groupBox3.Size = new System.Drawing.Size(320, 66);
			this.groupBox3.TabIndex = 16;
			this.groupBox3.TabStop = false;
			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point(12, 231);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(97, 23);
			this.button3.TabIndex = 17;
			this.button3.Text = "По-умолчанию";
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new System.EventHandler(this.SetDefault);
			// 
			// RipOptions
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(344, 265);
			this.ControlBox = false;
			this.Controls.Add(this.button3);
			this.Controls.Add(this.groupBox3);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.button2);
			this.Controls.Add(this.button1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "RipOptions";
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Options :: Audio CD Ripper";
			this.Load += new System.EventHandler(this.LoadForm);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.groupBox2.ResumeLayout(false);
			this.groupBox2.PerformLayout();
			this.groupBox3.ResumeLayout(false);
			this.groupBox3.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Button btnTemp;
		private System.Windows.Forms.TextBox textTemp;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button btnSetOutput;
		private System.Windows.Forms.TextBox textOutput;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.CheckBox cbNotRequestOutput;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.RadioButton rbAllways;
		private System.Windows.Forms.RadioButton rbAsk;
		private System.Windows.Forms.RadioButton rbNever;
		private System.Windows.Forms.FolderBrowserDialog folderBrowser;
		private System.Windows.Forms.CheckBox cbEject;
		private System.Windows.Forms.CheckBox cbOpenDir;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.GroupBox groupBox3;
		private System.Windows.Forms.Button button3;
	}
}
