using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Propeller;

namespace PropellerVisualization
{
    public partial class PropellerForm : Form
    {
        private float time;
        private int step;
        private Data data;
        private PointF center=new Point(500,250);
        private Rectangle propeller = new Rectangle(-100,-30,200,60);
        private Rectangle nail = new Rectangle(-5,-5,10,10);
        private Rectangle hole = new Rectangle(-PropellerMath.L,-PropellerMath.L,2*PropellerMath.L,2*PropellerMath.L);

        public PropellerForm()
        {
            DoubleBuffered = true;
            Size = new Size(1000, 500);
            var timer = new Timer {Interval = 10};
            timer.Tick += (s, e) => TimerTick();
            Paint += (s, e) => PropellerFormPaint(e.Graphics);
            data=new Data(0,0,0,0,0);
            timer.Start();
        }

        private void PropellerFormPaint(Graphics graphics)
        {
            graphics.SmoothingMode = SmoothingMode.AntiAlias;
            graphics.TranslateTransform(center.X,center.Y);
            graphics.TranslateTransform(data.PropellerX,data.PropellerY);
            graphics.RotateTransform(data.Angle);
            graphics.FillRectangle(Brushes.BurlyWood,propeller);
            graphics.FillEllipse(Brushes.White,hole);
            graphics.ResetTransform();
            graphics.TranslateTransform(center.X,center.Y);
            graphics.TranslateTransform(data.NailX,data.NailY);
            graphics.FillEllipse(Brushes.Black,nail);
            graphics.ResetTransform();
        }

        private void TimerTick()
        {
            time += (float)2e-4;
            step++;
            data = PropellerMath.GetCurrentValues(data, step);
            Invalidate();
        }
    }
}
