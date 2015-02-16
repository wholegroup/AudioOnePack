namespace AudioOnePack
{
	partial class SendError
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SendError));
			this.m_btnSend = new System.Windows.Forms.Button();
			this.m_btnQuit = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// m_btnSend
			// 
			this.m_btnSend.Location = new System.Drawing.Point(253, 73);
			this.m_btnSend.Name = "m_btnSend";
			this.m_btnSend.Size = new System.Drawing.Size(94, 23);
			this.m_btnSend.TabIndex = 0;
			this.m_btnSend.Text = "Выслать отчет";
			this.m_btnSend.UseVisualStyleBackColor = true;
			this.m_btnSend.Click += new System.EventHandler(this.SendReport);
			// 
			// m_btnQuit
			// 
			this.m_btnQuit.Location = new System.Drawing.Point(172, 73);
			this.m_btnQuit.Name = "m_btnQuit";
			this.m_btnQuit.Size = new System.Drawing.Size(75, 23);
			this.m_btnQuit.TabIndex = 1;
			this.m_btnQuit.Text = "Quit";
			this.m_btnQuit.UseVisualStyleBackColor = true;
			this.m_btnQuit.Click += new System.EventHandler(this.Quit);
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(12, 9);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(335, 61);
			this.label1.TabIndex = 2;
			this.label1.Text = resources.GetString("label1.Text");
			// 
			// SendError
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(359, 107);
			this.ControlBox = false;
			this.Controls.Add(this.label1);
			this.Controls.Add(this.m_btnQuit);
			this.Controls.Add(this.m_btnSend);
			this.Name = "SendError";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Error :: Audio One Pack";
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button m_btnSend;
		private System.Windows.Forms.Button m_btnQuit;
		private System.Windows.Forms.Label label1;
	}
}