namespace AudioOnePack
{
	partial class ConvertOptions
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
			this.cbDelete = new System.Windows.Forms.CheckBox();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.rbDestination = new System.Windows.Forms.RadioButton();
			this.rbNotDestination = new System.Windows.Forms.RadioButton();
			this.cbNotRequestOutput = new System.Windows.Forms.CheckBox();
			this.btnSetOutput = new System.Windows.Forms.Button();
			this.textOutput = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.folderBrowser = new System.Windows.Forms.FolderBrowserDialog();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(176, 158);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(75, 23);
			this.button1.TabIndex = 0;
			this.button1.Text = "OK";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.OnOK);
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(257, 158);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(75, 23);
			this.button2.TabIndex = 1;
			this.button2.Text = "Cancel";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new System.EventHandler(this.OnCancel);
			// 
			// cbDelete
			// 
			this.cbDelete.AutoSize = true;
			this.cbDelete.Location = new System.Drawing.Point(19, 135);
			this.cbDelete.Name = "cbDelete";
			this.cbDelete.Size = new System.Drawing.Size(228, 17);
			this.cbDelete.TabIndex = 2;
			this.cbDelete.Text = "To replace original files with converted files";
			this.cbDelete.UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.rbDestination);
			this.groupBox1.Controls.Add(this.rbNotDestination);
			this.groupBox1.Location = new System.Drawing.Point(12, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(320, 68);
			this.groupBox1.TabIndex = 3;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "To place converted files:";
			// 
			// rbDestination
			// 
			this.rbDestination.AutoSize = true;
			this.rbDestination.Location = new System.Drawing.Point(7, 44);
			this.rbDestination.Name = "rbDestination";
			this.rbDestination.Size = new System.Drawing.Size(133, 17);
			this.rbDestination.TabIndex = 1;
			this.rbDestination.TabStop = true;
			this.rbDestination.Text = "to the chosen directory";
			this.rbDestination.UseVisualStyleBackColor = true;
			// 
			// rbNotDestination
			// 
			this.rbNotDestination.AutoSize = true;
			this.rbNotDestination.Location = new System.Drawing.Point(7, 20);
			this.rbNotDestination.Name = "rbNotDestination";
			this.rbNotDestination.Size = new System.Drawing.Size(114, 17);
			this.rbNotDestination.TabIndex = 0;
			this.rbNotDestination.TabStop = true;
			this.rbNotDestination.Text = "next to original files";
			this.rbNotDestination.UseVisualStyleBackColor = true;
			// 
			// cbNotRequestOutput
			// 
			this.cbNotRequestOutput.AutoSize = true;
			this.cbNotRequestOutput.Location = new System.Drawing.Point(19, 86);
			this.cbNotRequestOutput.Name = "cbNotRequestOutput";
			this.cbNotRequestOutput.Size = new System.Drawing.Size(213, 17);
			this.cbNotRequestOutput.TabIndex = 15;
			this.cbNotRequestOutput.Text = "Without request for the output directory ";
			this.cbNotRequestOutput.UseVisualStyleBackColor = true;
			this.cbNotRequestOutput.CheckedChanged += new System.EventHandler(this.ClickNotRequest);
			// 
			// btnSetOutput
			// 
			this.btnSetOutput.Image = global::AudioOnePack.Properties.Resources.folder;
			this.btnSetOutput.Location = new System.Drawing.Point(306, 107);
			this.btnSetOutput.Name = "btnSetOutput";
			this.btnSetOutput.Size = new System.Drawing.Size(26, 22);
			this.btnSetOutput.TabIndex = 14;
			this.btnSetOutput.UseVisualStyleBackColor = true;
			this.btnSetOutput.Click += new System.EventHandler(this.ClickBtnOutput);
			// 
			// textOutput
			// 
			this.textOutput.Location = new System.Drawing.Point(104, 109);
			this.textOutput.Name = "textOutput";
			this.textOutput.Size = new System.Drawing.Size(196, 20);
			this.textOutput.TabIndex = 13;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(16, 112);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(82, 13);
			this.label2.TabIndex = 12;
			this.label2.Text = "Output directory";
			// 
			// ConvertOptions
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(341, 187);
			this.ControlBox = false;
			this.Controls.Add(this.cbNotRequestOutput);
			this.Controls.Add(this.btnSetOutput);
			this.Controls.Add(this.textOutput);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.cbDelete);
			this.Controls.Add(this.button2);
			this.Controls.Add(this.button1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "ConvertOptions";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Options";
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.CheckBox cbDelete;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.RadioButton rbDestination;
		private System.Windows.Forms.RadioButton rbNotDestination;
		private System.Windows.Forms.CheckBox cbNotRequestOutput;
		private System.Windows.Forms.Button btnSetOutput;
		private System.Windows.Forms.TextBox textOutput;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.FolderBrowserDialog folderBrowser;
	}
}
