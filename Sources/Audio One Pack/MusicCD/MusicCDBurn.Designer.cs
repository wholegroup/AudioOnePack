namespace AudioOnePack
{
	partial class MusicCDBurn
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
			this.progressBurn = new System.Windows.Forms.ProgressBar();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.labelTwo = new System.Windows.Forms.Label();
			this.labelOne = new System.Windows.Forms.Label();
			this.btnCancel = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// progressBurn
			// 
			this.progressBurn.Location = new System.Drawing.Point(13, 91);
			this.progressBurn.Name = "progressBurn";
			this.progressBurn.Size = new System.Drawing.Size(301, 23);
			this.progressBurn.TabIndex = 6;
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.labelTwo);
			this.groupBox1.Controls.Add(this.labelOne);
			this.groupBox1.Location = new System.Drawing.Point(12, 11);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(302, 73);
			this.groupBox1.TabIndex = 5;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Information";
			// 
			// labelTwo
			// 
			this.labelTwo.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.labelTwo.Location = new System.Drawing.Point(6, 46);
			this.labelTwo.Name = "labelTwo";
			this.labelTwo.Size = new System.Drawing.Size(290, 23);
			this.labelTwo.TabIndex = 1;
			this.labelTwo.Text = "Kino - Peremen";
			this.labelTwo.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// labelOne
			// 
			this.labelOne.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.labelOne.Location = new System.Drawing.Point(6, 16);
			this.labelOne.Name = "labelOne";
			this.labelOne.Size = new System.Drawing.Size(290, 23);
			this.labelOne.TabIndex = 0;
			this.labelOne.Text = "Adding";
			this.labelOne.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point(239, 120);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(75, 23);
			this.btnCancel.TabIndex = 4;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler(this.Cancel);
			// 
			// MusicCDBurn
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(326, 155);
			this.ControlBox = false;
			this.Controls.Add(this.progressBurn);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.btnCancel);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "MusicCDBurn";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Music CD burning";
			this.Shown += new System.EventHandler(this.FirstShow);
			this.groupBox1.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.ProgressBar progressBurn;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Label labelTwo;
		private System.Windows.Forms.Label labelOne;
		private System.Windows.Forms.Button btnCancel;
	}
}
