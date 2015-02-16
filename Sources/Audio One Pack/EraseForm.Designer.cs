namespace AudioOnePack
{
	partial class EraseForm
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
			this.label1 = new System.Windows.Forms.Label();
			this.cbMethod = new System.Windows.Forms.ComboBox();
			this.progressErase = new System.Windows.Forms.ProgressBar();
			this.btnErase = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.textMethod = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.timerPos = new System.Windows.Forms.Timer(this.components);
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(12, 9);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(178, 13);
			this.label1.TabIndex = 0;
			this.label1.Text = "Select the erase method to be used:";
			// 
			// cbMethod
			// 
			this.cbMethod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cbMethod.FormattingEnabled = true;
			this.cbMethod.Items.AddRange(new object[] {
            "Quick-erase rewritable disc",
            "Full-erase rewritable disc"});
			this.cbMethod.Location = new System.Drawing.Point(15, 25);
			this.cbMethod.Name = "cbMethod";
			this.cbMethod.Size = new System.Drawing.Size(175, 21);
			this.cbMethod.TabIndex = 1;
			this.cbMethod.SelectedIndexChanged += new System.EventHandler(this.ChangedMethod);
			// 
			// progressErase
			// 
			this.progressErase.Location = new System.Drawing.Point(15, 104);
			this.progressErase.Maximum = 300;
			this.progressErase.Name = "progressErase";
			this.progressErase.Size = new System.Drawing.Size(315, 23);
			this.progressErase.TabIndex = 2;
			// 
			// btnErase
			// 
			this.btnErase.Location = new System.Drawing.Point(174, 133);
			this.btnErase.Name = "btnErase";
			this.btnErase.Size = new System.Drawing.Size(75, 23);
			this.btnErase.TabIndex = 3;
			this.btnErase.Text = "Erase";
			this.btnErase.UseVisualStyleBackColor = true;
			this.btnErase.Click += new System.EventHandler(this.Erase);
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point(255, 133);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(75, 23);
			this.btnCancel.TabIndex = 4;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler(this.CloseForm);
			// 
			// textMethod
			// 
			this.textMethod.Location = new System.Drawing.Point(12, 49);
			this.textMethod.Name = "textMethod";
			this.textMethod.Size = new System.Drawing.Size(318, 30);
			this.textMethod.TabIndex = 5;
			this.textMethod.Text = "label2";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(12, 88);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(77, 13);
			this.label2.TabIndex = 6;
			this.label2.Text = "Erase process:";
			// 
			// timerPos
			// 
			this.timerPos.Interval = 500;
			this.timerPos.Tick += new System.EventHandler(this.TickPos);
			// 
			// EraseForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(342, 168);
			this.ControlBox = false;
			this.Controls.Add(this.label2);
			this.Controls.Add(this.textMethod);
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.btnErase);
			this.Controls.Add(this.progressErase);
			this.Controls.Add(this.cbMethod);
			this.Controls.Add(this.label1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Name = "EraseForm";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Erase Rewritable Disc";
			this.Load += new System.EventHandler(this.LoadForm);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.ComboBox cbMethod;
		private System.Windows.Forms.ProgressBar progressErase;
		private System.Windows.Forms.Button btnErase;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Label textMethod;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Timer timerPos;
	}
}