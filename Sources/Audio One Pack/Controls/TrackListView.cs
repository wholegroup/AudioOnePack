/*
 * Copyright (C) 2015 Andrey Rychkov <wholegroup@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Runtime.InteropServices;
using System.Reflection;
using System.ComponentModel;

namespace System.Windows.Forms
{
	//
	public class TrackListView 
		: ListView
	{
		// шрифт текста
		Font m_fontReal;

		// формат строки для временного использования
		StringFormat m_sfTemp;

		// кисть для фона четных элементов
		SolidBrush m_sbBackColorEven;

		// кисть для фона нечетных элементов
		SolidBrush m_sbBackColorOdd;

		// кисть для текста
		SolidBrush m_sbForeColor;

		// текст для вывода, если нет элементов
		String m_strEmptyText = "";

		[DefaultValue(""), Localizable(true), Description("EmptyText")]
		public String EmptyText
		{
			get
			{
				return m_strEmptyText;
			}

			set
			{
				m_strEmptyText = value.ToString();
			}
		}

		// шрифт для вывода m_strEmptyText
		Font m_fontEmptyText = SystemFonts.DefaultFont;

		[DefaultValue(0), Description("Font for EmptyText")]
		public Font EmptyTextFont
		{
			get
			{
				return m_fontEmptyText;
			}

			set
			{
				m_fontEmptyText = (Font)value;

				if (null == value)
				{
					m_fontEmptyText = SystemFonts.DefaultFont;
				}
			}
		}

		// цвет текста для вывода m_strEmptyText
		Color m_colorEmptyText = SystemColors.WindowText;
		
		[DefaultValue(0), Description("Font for EmptyText")]
		public Color EmptyTextColor
		{
			get
			{
				return m_colorEmptyText;
			}
			set
			{
				m_colorEmptyText = (Color)value;
			}
		}

		// высота заголовка
		int m_iHeaderHeight = 0;
		
		// выравнивание первой колонки
		HorizontalAlignment m_alignFirstColumn;

		public HorizontalAlignment FirstColumnAlign
		{
			get
			{
				return m_alignFirstColumn;
			}

			set
			{
				m_alignFirstColumn = (HorizontalAlignment)value;
			}
		}

		// фон при отсутствии элементов
		Image m_imageEmpty;

		// Флаг смены шрифта
		Boolean m_bFontChanged = true;

		/// <summary>
		/// Конструктор.
		/// </summary>
		public TrackListView()
		{
			Margin = new System.Windows.Forms.Padding(0);

			SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
			SetStyle(ControlStyles.Opaque, true);

			OnBackColorChanged(null);
			OnForeColorChanged(null);
		}

		/// <summary>
		/// Обработка смены фона.
		/// </summary>
		protected override void OnBackColorChanged(EventArgs e)
		{
			if (null != e)
			{
				base.OnBackColorChanged(e);
			}

			m_sbBackColorEven = new SolidBrush(System.Windows.Forms.ControlPaint.Dark(this.BackColor, -0.4f));
			m_sbBackColorOdd  = new SolidBrush(this.BackColor);
		}

		/// <summary>
		/// Обработка смены цвета текста.
		/// </summary>
		protected override void OnForeColorChanged(EventArgs e)
		{
			if (null != e)
			{
				base.OnForeColorChanged(e);
			}

			m_sbForeColor = new SolidBrush(this.ForeColor);
		}

		/// <summary>
		/// Обработка смены шрифта.
		/// </summary>
		protected override void OnFontChanged(EventArgs e)
		{
			if (null != e)
			{
				base.OnFontChanged(e);
			}

			if (DesignMode)
			{
				return;
			}

			if (Margin.Top > 0)
			{
				if (m_bFontChanged)
				{
					m_bFontChanged = false;

					// сохраняем шрифт
					m_fontReal = this.Font;

					// устанавливаем с учетом Margin
					this.Font = new Font(this.Font.FontFamily, this.Font.GetHeight() + Margin.All * 2, GraphicsUnit.Pixel);
				}
				else
				{
					m_bFontChanged = true;
				}
			}
			else
			{
				m_fontReal = this.Font;
			}
		}

		/// <summary>
		/// Обработка изменения поля Margin.
		/// </summary>
		/// <param name="e"></param>
		protected override void OnMarginChanged(EventArgs e)
		{
			base.OnMarginChanged(e);

			OnFontChanged(null);
		}

		/// <summary>
		/// Перерисовка после изменения выделения элементов.
		/// </summary>
		protected override void OnItemSelectionChanged(ListViewItemSelectionChangedEventArgs e)
		{
			base.OnItemSelectionChanged(e);

			// обновляем область вне элементов
			if (this.Width > e.Item.Bounds.Width)
			{
				Rectangle rectTmp = e.Item.Bounds;

				rectTmp.X     = e.Item.Bounds.Width;
				rectTmp.Width = this.Width - e.Item.Bounds.Width;

				this.Invalidate(rectTmp, false);
			}
		}

		/// <summary>
		/// Вывод шапки.
		/// </summary>
		protected override void OnDrawColumnHeader(DrawListViewColumnHeaderEventArgs e)
		{
			base.OnDrawColumnHeader(e);

			// AntiAliasing
			e.Graphics.TextRenderingHint = System.Drawing.Text.TextRenderingHint.ClearTypeGridFit;

			// вывод бекграунда
			e.DrawBackground();

			// вывод текста
			Font headerFont = new Font(e.Font.FontFamily, 8, e.Font.Style);

			m_sfTemp               = StringFormat.GenericDefault;
			m_sfTemp.Alignment     = StringAlignment.Center;
			m_sfTemp.LineAlignment = StringAlignment.Near;

			e.Graphics.DrawString(e.Header.Text, headerFont, new SolidBrush(e.ForeColor), e.Bounds, m_sfTemp);

			if (0 == m_iHeaderHeight)
			{
				m_iHeaderHeight = e.Bounds.Height;

				OnResize(null);
			}
		}

		/// <summary>
		/// Зарисовка области вне элемента.
		/// </summary>
		/// <param name="e"></param>
		protected override void OnDrawItem(DrawListViewItemEventArgs e)
		{
			// закрашивание области после всех элементов в строке
			if (e.Bounds.Width < this.Width)
			{
				Rectangle rectBack = e.Bounds;
				
				rectBack.X     = e.Bounds.Width;
				rectBack.Width = this.Width - e.Bounds.Width;

				if (e.Item.Selected)
				{
					e.Graphics.FillRectangle(SystemBrushes.Highlight, rectBack);
				}
				else
				{
					if (0 == (e.ItemIndex % 2))
					{
						e.Graphics.FillRectangle(m_sbBackColorEven, rectBack);
					}
					else
					{
						e.Graphics.FillRectangle(m_sbBackColorOdd, rectBack);
					}
				}
			}

			// вывод грида после элементов
			if ((e.ItemIndex + 1) == this.Items.Count)
			{
				int       iNext    = 1;
				Rectangle rectFill = e.Bounds;

				rectFill.Width = this.Width;
				rectFill.Y    += rectFill.Height;

				while (rectFill.Y < this.Height)
				{
					if (0 == ((e.ItemIndex + iNext) % 2))
					{
						e.Graphics.FillRectangle(m_sbBackColorEven, rectFill);
					}
					else
					{
						e.Graphics.FillRectangle(m_sbBackColorOdd, rectFill);
					}

					iNext++;

					rectFill.Y += rectFill.Height;
				}
			}
		}

		/// <summary>
		/// Вывод SubItem.
		/// </summary>
		protected override void OnDrawSubItem(DrawListViewSubItemEventArgs e)
		{
			base.OnDrawSubItem(e);

			Rectangle rectOut = e.Bounds;

			e.Graphics.TextRenderingHint = System.Drawing.Text.TextRenderingHint.ClearTypeGridFit;

			if (e.Item.Selected)
			{
				e.Graphics.FillRectangle(SystemBrushes.Highlight, rectOut);
			}
			else
			{
				// закрашиваем фон subitem'а
				if (0 == (e.ItemIndex % 2))
				{
					e.Graphics.FillRectangle(m_sbBackColorEven, rectOut);
				}
				else
				{
					e.Graphics.FillRectangle(m_sbBackColorOdd, rectOut);
				}
			}
			
			// вывод чекбоксов
			if (0 == e.ColumnIndex)
			{
				if (this.CheckBoxes)
				{
					Size  sizeCheckBox  = CheckBoxRenderer.GetGlyphSize(e.Graphics, 
						System.Windows.Forms.VisualStyles.CheckBoxState.CheckedNormal);
					Point pointCheckBox = rectOut.Location;
					int   d             = (rectOut.Height - sizeCheckBox.Height) / 2;

					pointCheckBox.X += d;
					pointCheckBox.Y += d;

					if (e.Item.Checked)
					{
						CheckBoxRenderer.DrawCheckBox(e.Graphics, pointCheckBox, 
							System.Windows.Forms.VisualStyles.CheckBoxState.CheckedNormal);
					}
					else
					{
						CheckBoxRenderer.DrawCheckBox(e.Graphics, pointCheckBox, 
							System.Windows.Forms.VisualStyles.CheckBoxState.UncheckedNormal);
					}

					rectOut.X     += sizeCheckBox.Width + d + 1;
					rectOut.Width -= sizeCheckBox.Width + d + 1;
				}
			}

			// вывод текста
			m_sfTemp               = StringFormat.GenericDefault;
			m_sfTemp.LineAlignment = StringAlignment.Center;
			m_sfTemp.FormatFlags  |= StringFormatFlags.NoWrap;

			HorizontalAlignment alignTmp;
			
			if (0 == e.ColumnIndex)
			{
				alignTmp = m_alignFirstColumn;
			}
			else
			{
				alignTmp = this.Columns[e.ColumnIndex].TextAlign;
			}

			if (HorizontalAlignment.Left == alignTmp)
			{
				m_sfTemp.Alignment = StringAlignment.Near;
			}
			else

			if (HorizontalAlignment.Center == alignTmp)
			{
				m_sfTemp.Alignment = StringAlignment.Center;
			}

			else
			{
				m_sfTemp.Alignment = StringAlignment.Far;
			}

			if (e.Item.Selected)
			{
				e.Graphics.DrawString(e.SubItem.Text, m_fontReal, 
					SystemBrushes.HighlightText, rectOut, m_sfTemp);
			}
			else
			{
				e.Graphics.DrawString(e.SubItem.Text, m_fontReal, m_sbForeColor, rectOut, m_sfTemp);
			}
		}

		/// <summary>
		/// Обработка изменения размеров.
		/// </summary>
		protected override void OnResize(EventArgs e)
		{
			if (null != e)
			{
				base.OnResize(e);
			}

			// перерисовка картинки фона при отсутствии элементов
			m_imageEmpty = new Bitmap(Size.Width, Size.Height - m_iHeaderHeight);

			Graphics  gImage    = Graphics.FromImage(m_imageEmpty);
			Rectangle rectImage = new Rectangle(0, 0, Size.Width, Size.Height - m_iHeaderHeight);

			gImage.FillRectangle(m_sbBackColorOdd, rectImage);

			gImage.TextRenderingHint = System.Drawing.Text.TextRenderingHint.ClearTypeGridFit;

			m_sfTemp               = StringFormat.GenericDefault;
			m_sfTemp.Alignment     = StringAlignment.Center;
			m_sfTemp.LineAlignment = StringAlignment.Center;

			gImage.DrawString(m_strEmptyText, m_fontEmptyText, new SolidBrush(m_colorEmptyText), rectImage, m_sfTemp);

			this.BackgroundImage = m_imageEmpty;
		}

		/// <summary>
		/// Обработка уведомления о перерисовке.
		/// </summary>
		/// <param name="invalidatedArea"></param>
		protected override void NotifyInvalidate(Rectangle invalidatedArea)
		{
			base.NotifyInvalidate(invalidatedArea);
			
			if ((0 == invalidatedArea.Width) || (0 == invalidatedArea.Height))
			{
				if (0 < Items.Count)
				{
					Invalidate(new Rectangle(0, 0, Width, Height));

					this.RedrawItems(Items.Count - 1, Items.Count - 1, true);
				}
			}
		}

		/// <summary>
		/// Обработка сообщений.
		/// </summary>
		protected override void WndProc(ref Message m)
		{
			if (0x14 == m.Msg) // WM_ERASEBKGND
			{
				//if (0 < Items.Count)
				{
					//this.RedrawItems(0, 0, true);
					//this.RedrawItems(Items.Count - 1, Items.Count - 1, false);
					//Invalidate(Items[Items.Count - 1].Bounds);
					//return;
					//listViewState = 1;
					//RedrawItems(Items.Count - 1, Items.Count - 1, true);
					//this.Invalidate(Items[0].Bounds);
					
				}
			}

			base.WndProc(ref m);
		}

		//
		protected override void OnMouseUp(MouseEventArgs e)
		{
			base.OnMouseUp(e);

			if (0 < Items.Count)
			{
				Invalidate(new Rectangle(0, 0, Width, Height));

				this.RedrawItems(Items.Count - 1, Items.Count - 1, true);
			}
		}
	}
}
