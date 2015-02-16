namespace AudioOnePack
{
	partial class AnalyzerProcess
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
			this.btnStop = new System.Windows.Forms.Button();
			this.progressOne = new System.Windows.Forms.ProgressBar();
			this.progressAll = new System.Windows.Forms.ProgressBar();
			this.textOne = new System.Windows.Forms.Label();
			this.textAll = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// btnStop
			// 
			this.btnStop.Location = new System.Drawing.Point(289, 99);
			this.btnStop.Name = "btnStop";
			this.btnStop.Size = new System.Drawing.Size(75, 23);
			this.btnStop.TabIndex = 0;
			this.btnStop.Text = "&Stop";
			this.btnStop.UseVisualStyleBackColor = true;
			this.btnStop.Click += new System.EventHandler(this.Stop);
			// 
			// progressOne
			// 
			this.progressOne.Location = new System.Drawing.Point(12, 25);
			this.progressOne.Name = "progressOne";
			this.progressOne.Size = new System.Drawing.Size(352, 23);
			this.progressOne.TabIndex = 1;
			// 
			// progressAll
			// 
			this.progressAll.Location = new System.Drawing.Point(12, 70);
			this.progressAll.Name = "progressAll";
			this.progressAll.Size = new System.Drawing.Size(352, 23);
			this.progressAll.TabIndex = 2;
			// 
			// textOne
			// 
			this.textOne.AutoSize = true;
			this.textOne.Location = new System.Drawing.Point(12, 9);
			this.textOne.Name = "textOne";
			this.textOne.Size = new System.Drawing.Size(35, 13);
			this.textOne.TabIndex = 3;
			this.textOne.Text = "label1";
			// 
			// textAll
			// 
			this.textAll.AutoSize = true;
			this.textAll.Location = new System.Drawing.Point(12, 54);
			this.textAll.Name = "textAll";
			this.textAll.Size = new System.Drawing.Size(35, 13);
			this.textAll.TabIndex = 4;
			this.textAll.Text = "label2";
			// 
			// AnalyzerProcess
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(376, 132);
			this.ControlBox = false;
			this.Controls.Add(this.textAll);
			this.Controls.Add(this.textOne);
			this.Controls.Add(this.progressAll);
			this.Controls.Add(this.progressOne);
			this.Controls.Add(this.btnStop);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.Name = "AnalyzerProcess";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Sound analyzing";
			this.Shown += new System.EventHandler(this.ShowForm);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button btnStop;
		private System.Windows.Forms.ProgressBar progressOne;
		private System.Windows.Forms.ProgressBar progressAll;
		private System.Windows.Forms.Label textOne;
		private System.Windows.Forms.Label textAll;
	}
}
