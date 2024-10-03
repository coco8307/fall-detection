using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Windows.Forms;
using System.IO;

namespace SerialCommunicate
    {
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;  //检查窗体是否被阻止使用
        }
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = comboBox1.Text;//获取端口
                serialPort1.Encoding = System.Text.Encoding.GetEncoding("GB2312");   //串口编码为GB2312
                serialPort1.BaudRate = Convert.ToInt32(comboBox2.Text,10);//十进制数据转换
                serialPort1.Open();
                button1.Enabled = false;//打开串口按钮不可用
                button2.Enabled = true;//关闭串口按钮可用
            }
            catch 
            {
                MessageBox.Show("端口错误,请检查串口", "注意");
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            int sum = 0;
            for (int i = 1;i < 20;i++ )
            {
                try
                {
                    serialPort1.PortName = "COM" + i.ToString();
                    serialPort1.Encoding = System.Text.Encoding.GetEncoding("GB2312");
                    serialPort1.BaudRate = 115200;
                    serialPort1.Open();
                    serialPort1.Close();
                    comboBox1.Items.Add("COM" + i.ToString());
                }
                catch (Exception )
                {
                    serialPort1.Close();
                }

            }

            comboBox1.Text = "COM3";//串口号默认值
            comboBox2.Text = "115200";//波特率默认值
            serialPort1.ReceivedBytesThreshold = 1;//必须一定要加上这句话，意思是接收缓冲区当中如果有一个字节的话就触发接收函数，如果不加上这句话，有时触发接收都发了好多次了也没有触发接收，有时有延时现象等。
            
            /*****************非常重要************************/
            
            serialPort1.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);//必须手动添加数据接收事件,编写数据接收函数

        }
        
        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)//串口数据接收事件
        {
            string str = serialPort1.ReadExisting();//字符串方式读
            textBox1.AppendText(str);//将读到的内容显示在文本框中
        }
        private void button2_Click(object sender, EventArgs e)
        {
                serialPort1.Close();//关闭串口
                button1.Enabled = true;//打开串口按钮可用  
                button2.Enabled = false;//关闭串口按钮不可用
        }

        private void button4_Click_1(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)//判断串口是否打开，如果打开执行下一步操作
            {
                try
                {
                    serialPort1.WriteLine("$" + "D" + DateTime.Now.ToString("yyyyMMdd") + DateTime.Now.ToString("HHmmss") + "\r\n");//写入当前时间
                }
                catch (Exception )
                {
                    MessageBox.Show("发送出错！", "注意");//出错提示
                    serialPort1.Close();
                }
            }
            else
            {
                MessageBox.Show("端口未打开！","注意");//出错提示
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            label4.Text = DateTime.Now.ToString("HH:mm:ss");
            label3.Text = DateTime.Now.ToString("yyyy-MM-dd");
        }

        private void button12_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)//判断串口是否打开，如果打开执行下一步操作
            {
                try
                {
                    serialPort1.WriteLine("$"+"N" + textBox4.Text  +"\r\n");//写入手机号码
                }
                catch (Exception )
                {
                    MessageBox.Show("发送出错！", "注意");
                    serialPort1.Close();
                }
            }
            else
            {
                MessageBox.Show("端口未打开！", "注意");
            }
        }

        private void textBox4_KeyPress(object sender, System.Windows.Forms.KeyPressEventArgs e)
        {
            if (e.KeyChar < 48 || e.KeyChar > 57)   //用户输入的不是数字 or if (e.KeyChar < '0' || e.KeyChar > '9')
            {
                e.Handled = true;  
            }

            if (e.KeyChar == 8)    //退格键（ascii）
            {
                e.Handled = false;    
            }

        }

    }
}
