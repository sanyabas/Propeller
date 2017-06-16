using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using Propeller;

namespace PropellerVisualization
{
    public partial class PropellerForm : Form
    {
        private float time;
        private int step;
        private Data data;
        private PointF center = new Point(500, 250);
        private Rectangle propeller = new Rectangle(-100, -30, 200, 60);
        private const float NailRadius = 5;
        private RectangleF nail = new RectangleF(-NailRadius, -NailRadius, 2*NailRadius, 2*NailRadius);
        private const int Multiplier = 10000;
        private static float holeSize = PropellerMath.R * Multiplier;
        private RectangleF hole = new RectangleF(-holeSize, -holeSize, 2 * holeSize, 2 * holeSize);

        public PropellerForm()
        {
            DoubleBuffered = true;
            Size = new Size(1000, 500);
            var mathTimer = new Timer { Interval = 1 };
            var graphTimer = new Timer { Interval = 10 };
            mathTimer.Tick += (s, e) => TimerTick();
            graphTimer.Tick += (s, e) => Invalidate();
            Paint += (s, e) => PropellerFormPaint(e.Graphics);
            data = new Data(0, 0, 0, 0, 0);
            mathTimer.Start();
            graphTimer.Start();
        }

        private void PropellerFormPaint(Graphics graphics)
        {
            graphics.SmoothingMode = SmoothingMode.AntiAlias;
            graphics.TranslateTransform(center.X, center.Y);
            graphics.TranslateTransform(data.PropellerX * Multiplier, data.PropellerY * Multiplier);
            graphics.TranslateTransform(0, NailRadius * -Math.Sign(data.PropellerY - data.NailY));
            graphics.RotateTransform((float)((data.Angle - Math.PI / 2) * 180 / Math.PI));
            graphics.FillRectangle(Brushes.BurlyWood, propeller);
            graphics.FillEllipse(Brushes.White, hole);
            graphics.ResetTransform();
            graphics.TranslateTransform(center.X, center.Y);
            graphics.TranslateTransform(data.NailX * Multiplier, data.NailY * Multiplier);
            graphics.FillEllipse(Brushes.Black, nail);
            graphics.ResetTransform();
            graphics.TranslateTransform(center.X, center.Y);
            graphics.DrawLine(Pens.Red, 0, -Size.Height, 0, Size.Height);
        }

        private void TimerTick()
        {
            step++;
            data = PropellerMath.GetCurrentValues(data, step);
        }
    }
}
