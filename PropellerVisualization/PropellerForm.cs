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
        private PointF center = new Point(300, 250);
        private Rectangle propeller = new Rectangle(-100, -30, 200, 60);
        private const float NailRadius = 5;
        private RectangleF nail = new RectangleF(-NailRadius, -NailRadius, 2*NailRadius, 2*NailRadius);
        private const int Multiplier = 10000;
        private static float holeSize = PropellerMath.R * Multiplier;
        private RectangleF hole = new RectangleF(-holeSize, -holeSize, 2 * holeSize, 2 * holeSize);
        private static PointF gCenter = new Point(800,350);
        private static PointF gSign=new Point(730,200);
        private static Font font=new Font(FontFamily.GenericSansSerif, 20);
        private static Pen gPen = new Pen(Color.Black, 3) { CustomEndCap = new AdjustableArrowCap(5, 5) };
        private const string gString = "g effective";
        private static PointF NailOmegaPoint=new PointF(630,20);
        private static PointF NailAmplPoint=new PointF(630,50);
        private string nailOmegaString;
        private string nailAmplString;
        private static PropellerConsts values;

        private object locker=new object();

        public PropellerForm()
        {
            DoubleBuffered = true;
            Size = new Size(1000, 500);
            var mathTimer = new Timer { Interval = 20};
            var graphTimer = new Timer { Interval = 10 };
            mathTimer.Tick += (s, e) => TimerTick();
            graphTimer.Tick += (s, e) => Invalidate();
            Paint += (s, e) => PropellerFormPaint(e.Graphics);
            data = new Data(0, 0, 0, 0, 0,0,0);
            mathTimer.Start();
            graphTimer.Start();
        }

        private void PropellerFormPaint(Graphics graphics)
        {
            graphics.SmoothingMode = SmoothingMode.AntiAlias;
            DrawValues(graphics);
            DrawPropeller(graphics);
            DrawNail(graphics);
            DrawLine(graphics);
            DrawG(graphics);
        }

        private void DrawPropeller(Graphics graphics)
        {
            graphics.TranslateTransform(center.X, center.Y);
            graphics.TranslateTransform(data.PropellerX * Multiplier, data.PropellerY * Multiplier);
            graphics.TranslateTransform(0, NailRadius * -Math.Sign(data.PropellerY - data.NailY));
            graphics.RotateTransform((float)((data.Angle - Math.PI / 2) * 180 / Math.PI));
            graphics.FillRectangle(Brushes.BurlyWood, propeller);
            graphics.FillEllipse(Brushes.White, hole);
            graphics.ResetTransform();
        }

        private void DrawNail(Graphics graphics)
        {
            graphics.TranslateTransform(center.X, center.Y);
            graphics.TranslateTransform(data.NailX * Multiplier, data.NailY * Multiplier);
            graphics.FillEllipse(Brushes.Black, nail);
            graphics.ResetTransform();
        }

        private void DrawLine(Graphics graphics)
        {
            graphics.TranslateTransform(center.X, center.Y);
            graphics.DrawLine(Pens.Black, 0, -Size.Height, 0, Size.Height);
            graphics.ResetTransform();
            graphics.TranslateTransform(center.X, center.Y);
            graphics.DrawLine(Pens.Black,-Size.Width,0,gCenter.X-500,0);
            graphics.ResetTransform();

        }

        private void DrawG(Graphics graphics)
        {
            graphics.DrawLine(Pens.Black,gCenter.X-200,0,gCenter.X-200,Size.Height);
            graphics.TranslateTransform(gCenter.X,gCenter.Y);
            graphics.DrawLine(gPen,0,0,data.Gx*100,data.Gy*100);
            graphics.ResetTransform();
            graphics.DrawString(gString,font,Brushes.Black,gSign);
        }

        private void DrawValues(Graphics graphics)
        {
            if (step == 0)
            {
                values = PropellerMath.GetConsts();
                nailOmegaString = $"ω_nail={values.NailOmega} rad/s";
                nailAmplString= $"A_nail={values.NailAmplitude} m";
            }
            graphics.DrawString(nailOmegaString,font,Brushes.Black, NailOmegaPoint);
            graphics.DrawString(nailAmplString,font,Brushes.Black, NailAmplPoint);
        }

        private void TimerTick()
        {
            step++;
            //lock (locker)
            //{
                data = PropellerMath.GetCurrentValues(data, step);
            //}
        }
    }
}
