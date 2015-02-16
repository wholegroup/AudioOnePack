namespace AudioOnePack
{
   partial class EditNameTrack
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
			this.btnRename = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.textArtist = new System.Windows.Forms.TextBox();
			this.textTitle = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.cbChangeAll = new System.Windows.Forms.CheckBox();
			this.SuspendLayout();
			// 
			// btnRename
			// 
			this.btnRename.Location = new System.Drawing.Point(126, 105);
			this.btnRename.Name = "btnRename";
			this.btnRename.Size = new System.Drawing.Size(75, 23);
			this.btnRename.TabIndex = 2;
			this.btnRename.Text = "Rename";
			this.btnRename.UseVisualStyleBackColor = true;
			this.btnRename.Click += new System.EventHandler(this.Rename);
			// 
			// btnCancel
			// 
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.Location = new System.Drawing.Point(207, 105);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(75, 23);
			this.btnCancel.TabIndex = 3;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler(this.Close);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(8, 4);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(60, 13);
			this.label1.TabIndex = 2;
			this.label1.Text = "New artist:";
			// 
			// textArtist
			// 
			this.textArtist.Location = new System.Drawing.Point(8, 20);
			this.textArtist.Name = "textArtist";
			this.textArtist.Size = new System.Drawing.Size(274, 20);
			this.textArtist.TabIndex = 0;
			// 
			// textTitle
			// 
			this.textTitle.Location = new System.Drawing.Point(8, 79);
			this.textTitle.Name = "textTitle";
			this.textTitle.Size = new System.Drawing.Size(274, 20);
			this.textTitle.TabIndex = 1;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(8, 63);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(53, 13);
			this.label2.TabIndex = 5;
			this.label2.Text = "New title:";
			// 
			// cbChangeAll
			// 
			this.cbChangeAll.AutoSize = true;
			this.cbChangeAll.Location = new System.Drawing.Point(8, 43);
			this.cbChangeAll.Name = "cbChangeAll";
			this.cbChangeAll.Size = new System.Drawing.Size(276, 17);
			this.cbChangeAll.TabIndex = 6;
			this.cbChangeAll.Text = "изменить исполнителя у всех выбранных треков";
			this.cbChangeAll.UseVisualStyleBackColor = true;
			// 
			// EditNameTrack
			// 
			this.AcceptButton = this.btnRename;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.btnCancel;
			this.ClientSize = new System.Drawing.Size(291, 137);
			this.ControlBox = false;
			this.Controls.Add(this.cbChangeAll);
			this.Controls.Add(this.textTitle);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.textArtist);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.btnRename);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "EditNameTrack";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Track renaming";
			this.ResumeLayout(false);
			this.PerformLayout();

      }

      #endregion

      private System.Windows.Forms.Button btnRename;
      private System.Windows.Forms.Button btnCancel;
      private System.Windows.Forms.Label label1;
      private System.Windows.Forms.TextBox textArtist;
		private System.Windows.Forms.TextBox textTitle;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.CheckBox cbChangeAll;
   }
}
