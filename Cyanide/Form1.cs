using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using CSNamedPipe;

namespace Cyanide
{
    public partial class Form1 : Form
    {
        private NamedPipeServer PipeInSpew = null;
        private NamedPipeServer PipeInMsg = null;
        private NamedPipeServer PipeInDevMsg = null;
        private NamedPipeServer PipeInWarning = null;
        private NamedPipeServer PipeInData1 = null;
        private NamedPipeServer PipeOutCommand = null;
        private Thread keepAlive = null;
        private bool bRunning = true;
        private bool pinged = false;
        PlayerData player = new PlayerData();

        public Form1()
        {
            InitializeComponent();

            PipeInSpew = new NamedPipeServer("\\\\.\\pipe\\myNamedPipe1", 0);
            PipeInSpew.DataArrived += new NamedPipeServer.DataArrivedEventHandler(PipeInSpew_DataArrived);
            PipeInSpew.Start();

            PipeInMsg = new NamedPipeServer("\\\\.\\pipe\\myNamedPipe2", 0);
            PipeInMsg.DataArrived += new NamedPipeServer.DataArrivedEventHandler(PipeInMsg_DataArrived);
            PipeInMsg.Start();

            //PipeInDevMsg = new NamedPipeServer("\\\\.\\pipe\\myNamedPipe3", 0);
            //PipeInDevMsg.DataArrived += new NamedPipeServer.DataArrivedEventHandler(PipeInDevMsg_DataArrived);
            //PipeInDevMsg.Start();

            PipeInWarning = new NamedPipeServer("\\\\.\\pipe\\myNamedPipe4", 0);
            PipeInWarning.DataArrived += new NamedPipeServer.DataArrivedEventHandler(PipeInWarning_DataArrived);
            PipeInWarning.Start();

            PipeInData1 = new NamedPipeServer("\\\\.\\pipe\\myNamedPipe6", 0);
            PipeInData1.DataArrived += new NamedPipeServer.DataArrivedEventHandler(PipeInData1_DataArrived);
            PipeInData1.Start();

            PipeOutCommand = new NamedPipeServer("\\\\.\\pipe\\myNamedPipe5", 1);
            PipeOutCommand.Start();
            keepAlive = new Thread(new ThreadStart(KeepAlive));
            keepAlive.Start();

            player.PositionUpdated += new PlayerData.PositionUpdatedEventHandler(Player_PositionUpdated);
        }

        private void KeepAlive()
        {
            while (bRunning)
            {
                PipeOutCommand.SendMessage("getpos\n", PipeOutCommand.clientse);
                if (!pinged)
                {
                    PipeOutCommand.SendMessage("ping", PipeOutCommand.clientse);
                }
                Thread.Sleep(250);
            }
        }

        private void PipeInSpew_DataArrived(object sender, DataArrivedEventArgs e)
        {
            this.Invoke(new MethodInvoker(delegate()
            {
                listBox1.Items.Add("S " + e.Text);
                listBox1.SelectedIndex = listBox1.Items.Count - 1;
            }));
        }
        private void PipeInMsg_DataArrived(object sender, DataArrivedEventArgs e)
        {
            this.Invoke(new MethodInvoker(delegate()
            {
                listBox1.Items.Add("M " + e.Text);
                listBox1.SelectedIndex = listBox1.Items.Count - 1;
            }));
        }
        private void PipeInDevMsg_DataArrived(object sender, DataArrivedEventArgs e)
        {
            //this.Invoke(new MethodInvoker(delegate()
            //{
            //    listBox1.Items.Add("D " + e.Text);
            //    listBox1.SelectedIndex = listBox1.Items.Count - 1;
            //}));
        }
        private void PipeInWarning_DataArrived(object sender, DataArrivedEventArgs e)
        {
            string data = e.Text.Substring(0, e.Text.IndexOf('\0') - 1); ;
            string data6 = data.Substring(0, 6);
            
            string[] nums;

            switch (data6)
            {
                case "setpos":
                    //trailing semi-colon
                    data = data.Substring(0, data.Length - 1);
                    nums = data.Substring(7).Split(' ');
                    player.position.X = Convert.ToDecimal(nums[0]);
                    player.position.Y = Convert.ToDecimal(nums[1]);
                    player.position.Z = Convert.ToDecimal(nums[2]);
                    break;
                case "setang":
                    nums = data.Substring(7).Split(' ');
                    player.rotation.U = Convert.ToDecimal(nums[0]);
                    player.rotation.V = Convert.ToDecimal(nums[1]);
                    player.rotation.W = Convert.ToDecimal(nums[2]);
                    player.PositionChanged();
                    break;

            }
        }
        private void PipeInData1_DataArrived(object sender, DataArrivedEventArgs e)
        {
            string data = e.Text.Substring(0, e.Text.IndexOf('\0') - 1);
            this.Invoke(new MethodInvoker(delegate()
            {
                listBox1.Items.Add(data);
            }));
            if (data.Substring(0, 4) == "map:")
            {
                data = data.Substring(4, data.Length - 5);
                this.Invoke(new MethodInvoker(delegate()
                                                  {
                                                      lblMap.Text = "Map: " + data;
                                                  }));
                player.map = data;
                pinged = true;
            }
        }

        private void Player_PositionUpdated(object sender, PositionUpdatedEventArgs e)
        {
            this.Invoke(new MethodInvoker(delegate()
            {
                lblPosX.Text = "X: " + e.position.X;
                lblPosY.Text = "Y: " + e.position.Y;
                lblPosZ.Text = "Z: " + e.position.Z;
            }));
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            bRunning = false;
            PipeInSpew.StopServer();
            PipeInMsg.StopServer();
            PipeInDevMsg.StopServer();
            PipeInWarning.StopServer();
            PipeInData1.StopServer();
            PipeOutCommand.StopServer();

            Application.Exit();
        }

    }
}
