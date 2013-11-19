using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;


namespace FootplinkClientSettingApp
{
    public partial class Form1 : Form
    {
        static public string CSVfilename = "";
        public Form1()
        {
            InitializeComponent();

            button1.Text = "参照";
            button2.Text = "OK";
            label1.Text = "FootplinkClientの初期設定を行います。CSVファイルのパスを入力してください。";
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                textBox1.Text = openFileDialog1.FileName;
                CSVfilename = openFileDialog1.FileName;
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (System.IO.File.Exists(CSVfilename))
            {
                StreamWriter writer = new StreamWriter(@"CSVPath.conf", false);
                writer.WriteLine(CSVfilename);
                writer.Close();
                Environment.Exit(0);
            }
            else
            {
                MessageBox.Show("'" + CSVfilename + "'は存在しません。正しいパスを入力してください。");
            }
        }
    }
}
