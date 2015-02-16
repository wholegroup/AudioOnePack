namespace AudioOnePack
{
	partial class RipProcess
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
			this.btnCancel = new System.Windows.Forms.Button();
			this.progressRip = new System.Windows.Forms.ProgressBar();
			this.textRip = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point(252, 62);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(75, 23);
			this.btnCancel.TabIndex = 0;
			this.btnCancel.Text = "&Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler(this.Cancel);
			// 
			// progressRip
			// 
			this.progressRip.Location = new System.Drawing.Point(12, 33);
			this.progressRip.Name = "progressRip";
			this.progressRip.Size = new System.Drawing.Size(315, 23);
			this.progressRip.TabIndex = 1;
			// 
			// textRip
			// 
			this.textRip.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.textRip.Location = new System.Drawing.Point(12, 9);
			this.textRip.Name = "textRip";
			this.textRip.Size = new System.Drawing.Size(315, 21);
			this.textRip.TabIndex = 2;
			this.textRip.Text = "Process Audio Track #1 (7/14)";
			this.textRip.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// RipProcess
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(339, 95);
			this.ControlBox = false;
			this.Controls.Add(this.textRip);
			this.Controls.Add(this.progressRip);
			this.Controls.Add(this.btnCancel);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "RipProcess";
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Audio CD ripping";
			this.Shown += new System.EventHandler(this.ShowForm);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.ProgressBar progressRip;
		private System.Windows.Forms.Label textRip;
	}
}
