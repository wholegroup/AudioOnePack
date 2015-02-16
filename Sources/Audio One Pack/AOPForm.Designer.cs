namespace AudioOnePack
{
	partial class AOPForm
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AOPForm));
			this.tabMain = new System.Windows.Forms.TabControl();
			this.imgMainList = new System.Windows.Forms.ImageList(this.components);
			this.SuspendLayout();
			// 
			// tabMain
			// 
			resources.ApplyResources(this.tabMain, "tabMain");
			this.tabMain.ImageList = this.imgMainList;
			this.tabMain.Name = "tabMain";
			this.tabMain.SelectedIndex = 0;
			this.tabMain.SelectedIndexChanged += new System.EventHandler(this.TabChanged);
			// 
			// imgMainList
			// 
			this.imgMainList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imgMainList.ImageStream")));
			this.imgMainList.TransparentColor = System.Drawing.Color.Transparent;
			this.imgMainList.Images.SetKeyName(0, "rip.png");
			this.imgMainList.Images.SetKeyName(1, "burn.png");
			this.imgMainList.Images.SetKeyName(2, "mp3.png");
			this.imgMainList.Images.SetKeyName(3, "convert.png");
			this.imgMainList.Images.SetKeyName(4, "analyze.png");
			// 
			// AOPForm
			// 
			resources.ApplyResources(this, "$this");
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.tabMain);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.Name = "AOPForm";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.CloseForm);
			this.Shown += new System.EventHandler(this.ShowForm);
			this.Load += new System.EventHandler(this.LoadForm);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.TabControl tabMain;
		private System.Windows.Forms.ImageList imgMainList;



	}
}