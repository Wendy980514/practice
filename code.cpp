//李一，编写了所需的头文件
#include<graphics.h>//安装了EASY X才能打开这个头文件。
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include <conio.h>
#include <time.h>
__int8 world[102][202] = {0};
IMAGE imgLive, imgEmpty;		// 定义活细胞和无细胞区域的图案  //创建两个图像对象。

MOUSEMSG m;              //定义鼠标消息结构体的变量，并定义指向它的指针
MOUSEMSG *_m = &m;

char s1[20] = "速度：1", s2[20] = " ";    //速度值字符串s1,s2
int Speed = 125;			// 游戏速度（毫秒）

//王一，定义要用到的若干个函数，以及 main 函数的编写
void start();   //世界初始化
void kongjian(int x1, int x2, char *s);   //控件函数
void zuotu(MOUSEMSG *_m);   //作图
void shengsi();  //生死判断
void shuru();   //输入函数
void shuchu();    //输出函数
void dy_world();   //打印世界
void shubiao();   //鼠标监控与操作
void RandWorld();  //随机设置世界
void huitushebei();    //建立绘图设备
void jianpanjiankong();   //键盘监控

int main()
{
	

	initgraph(1800, 900);  //创建一个尺寸为 1800x900 的绘图环境，原点坐标（0，0），位于左上角
	start();   //世界初始化
	huitushebei();     //建立绘图设备
	while (true)
	{
		jianpanjiankong();  //键盘监控
		shubiao();		//鼠标监控与操作
		dy_world();			// 绘制世界
		shengsi();			// 生死判断
		Sleep(Speed);
	}
	return 0;
}

//李二，完成了 start() 和 jianpanjiankong()函数的编写
void start()
{
	memset(world, 0, 102 * 202 * sizeof(bool));   //初始化world数组
	setbkcolor(WHITE);// 设置背景色为白色
	cleardevice();// 用背景色清空屏幕
	setfillcolor(BLACK);   //设置填充颜色为黑色
	kongjian(0, 0, " ");
	setcolor(BROWN);    // 设置字体颜色为棕色
	outtextxy(900, 5, s1); //打印速度值
	setcolor(BLACK);    // 设置字体颜色为黑色
	outtextxy(400, 5, "Q/清空  W/保存  E/加载  S/随机"); //打印文字
}
void jianpanjiankong()   //键盘监控
{
	if (_kbhit())   
	{
		char c = _getch();    //读取键盘    //Speed等于450时，此处暂停

		if (c >='0' && c <= '9')
		{
			sprintf(s2, "%d", c - '0');      //将速度值写入字符数组s2中
			strcpy(s1, "速度：");     //初始化s1
			strcat(s1, s2);          //将s2连接到s1后
			setcolor(BROWN);    // 设置字体颜色为棕色
			outtextxy(900, 5, s1); //打印速度值
			if (c == '0')
				Speed = 900;
			else
				Speed = ('9' - c) * 25;  //根据输入数字调整速度
		}
		switch (c)
		{
		case 'q':
			start();  //世界初始化
			break;
		case 'w':
			shuchu();     //输出操作
			break;
		case 'e':
			shuru();     //输入操作
			break;

		case 's':
			RandWorld();   // 创建一个细胞随机分布的世界
			dy_world();			// 绘制世界
			break;

		case ' ':
			c = '/';
			setcolor(LIGHTRED);    // 设置字体颜色为亮红色
			outtextxy(1400, 5, "暂停"); //打印文字
			while (c != ' ')
			{
				shubiao();  //鼠标监控与操作
				Sleep(500);
				if (_kbhit())
				{
					c = _getch();
					dy_world();			// 绘制世界	
					shengsi();			// 生死判断	
				}
			}
			setfillcolor(WHITE);        //设置当前填充颜色为白色
			solidrectangle(1400, 5, 1450, 20);    //打印白色方格,覆盖“暂停”文字
			setfillcolor(BLACK);        //设置当前填充颜色为黑色
			break;
		}
	}
}
//王二，完成了 huitushebei() ，shubiao()，zuotu(MOUSEMSG *_m)函数的编写
void huitushebei()     //建立绘图设备
{
	// 调整世界图案的大小
	Resize(&imgLive, 9, 9);    //
	Resize(&imgEmpty, 9, 9);   //用于调整指定绘图设备的尺寸。

	// 绘制有生命世界的图案
	SetWorkingImage(&imgLive);   //用于设定当前的绘图设备。
	setfillcolor(BLACK);        //设置当前填充颜色为黑色
	setcolor(LIGHTGRAY);        //设置边框颜色为白色
	fillrectangle(0, 0, 8, 8);    //打印黑色方格，有边框

	// 绘制无生命世界的图案
	SetWorkingImage(&imgEmpty);
	setfillcolor(WHITE);        //设置当前填充颜色为白色
	solidrectangle(0, 0, 8, 8);    //打印白色方格

	// 恢复对默认窗口的绘图
	SetWorkingImage(NULL);
}
void shubiao()    //鼠标监控与操作
{
	

	int x1 = 0, x2 = 0;      //x1,x2存储单个控件的左右边的X坐标位置
	while (MouseHit())   //检测是否有鼠标消息
	{
		m = GetMouseMsg();       //获取鼠标消息
		if (m.mkLButton || m.mkRButton)   //鼠标左右键是否有按下
		{

			if (m.y > 26)      //m.y>26说明鼠标位于作图区，否则位于控件区
			{
				do
				{
					if (m.y > 26)
						zuotu(_m);  //将鼠标信息传递给做图函数
					m = GetMouseMsg();       //获取鼠标消息
				} while (m.mkLButton || m.mkRButton);   //直到松开按键才结束作图
			}
			else      //判断鼠标位于哪个控件
			{
				if (2 < m.x&&m.x < 63)
				{
					x1 = 2; x2 = 63;      //第一个控件的位置
					char s[] = "清空";
					kongjian(x1, x2, s);  //实现控件动画
					x1 = 0; x2 = 0;

					start();

				}
				if (72 < m.x&&m.x < 133)
				{
					x1 = 72; x2 = 133;     //第二个控件的位置
					char s[] = "保存";
					kongjian(x1, x2, s);  //实现控件动画
					x1 = 0;  x2 = 0;

					shuchu();     //输出操作

				}
				if (142 < m.x&&m.x < 203)
				{
					x1 = 142; x2 = 203;     //第三个控件的位置
					char s[] = "加载";
					kongjian(x1, x2, s);  //实现控件动画
					x1 = 0;  x2 = 0;

					shuru();     //输入操作
				}
				if (212 < m.x&&m.x < 273)
				{
					x1 = 212; x2 = 273;     //第三个控件的位置
					char s[] = "随机";
					kongjian(x1, x2, s);  //实现控件动画
					x1 = 0;  x2 = 0;

					RandWorld();   // 创建一个细胞随机分布的世界
					dy_world();			// 绘制世界

				}
				if (282 < m.x&&m.x < 343)
				{
					x1 = 142; x2 = 203;     //第三个控件的位置
					char s[] = "结束";
					kongjian(x1, x2, s);  //实现控件动画
					x1 = 0;  x2 = 0;

					exit(0);     //结束程序
				}

			};
		}
	}
	FlushMouseMsgBuffer();   //清空鼠标消息缓冲区
}
void zuotu(MOUSEMSG *_m)   //作图
{
	int x, y, xb, yb;

	xb = _m->x / 9+1;
	yb = (_m->y - 26) / 9+1;
	x = (xb - 1) * 9;
	y = (yb - 1) * 9 + 26;
	if (_m->mkLButton)
	{
		putimage(x, y, &imgLive);   //按左键时，打印方格，有边框
		world[yb][xb] = 1;
	}
	if (_m->mkRButton)
	{
		putimage(x, y, &imgEmpty);	//按右键时，删除方格
		world[yb][xb] = 0;
	}

}
//李三 完成kongjian(int x1, int x2, char *s)，shengsi()函数的编写
void kongjian(int x1, int x2, char *s)     //控件函数
{
	if (x1 == 0 && x2 == 0)  //若x1,x2==0,则初始化控件
	{
		setcolor(BLACK);// 设置字体颜色为黑色
		setfillcolor(WHITE);   //设置填充颜色为白色

		fillrectangle(2, 2, 63, 23);  //画白色填充矩形
		outtextxy(15, 5, "清空"); //打印文字

		fillrectangle(72, 2, 133, 23);  //画白色填充矩形
		outtextxy(85, 5, "保存"); //打印文字

		fillrectangle(142, 2, 203, 23);  //画白色填充矩形
		outtextxy(155, 5, "加载"); //打印文字

		fillrectangle(212, 2, 273, 23);  //画白色填充矩形
		outtextxy(225, 5, "随机"); //打印文字

		fillrectangle(282, 2, 343, 23);  //画白色填充矩形
		outtextxy(295, 5, "结束"); //打印文字

		setfillcolor(BLACK);   //设置填充颜色为黑色
	}
	if (x1 != 0 && x2 != 0)    //控件反馈效果
	{
		MOUSEMSG m;    //定义鼠标消息结构体的变量

		setcolor(BLACK);// 设置字体颜色为黑色

		setfillcolor(LIGHTGRAY);   //设置填充颜色为浅灰色
		fillrectangle(x1, 2, x2, 23);  //画浅灰色填充矩形

		setbkcolor(LIGHTGRAY);// 设置背景色为浅灰色
		outtextxy(x1 + 15, 5, s); //打印文字，与初始化相比向右移动2像素，实现动画效果
		setbkcolor(WHITE);// 设置背景色为白色

		do  { m = GetMouseMsg(); } while (m.mkLButton || m.mkRButton);

		setfillcolor(WHITE);   //设置填充颜色为白色
		fillrectangle(x1, 2, x2, 23);  //画白色填充矩形
		outtextxy(x1 + 15 - 2, 5, s); //打印文字，返回初始化位置

		setfillcolor(BLACK);   //设置填充颜色为黑色
	}
}
void shengsi()  //生死判断
{
	__int8 tmp[102][202] = { 0 };		// 临时数组
	int i, j;
	int sum=0;
	for (i = 1; i < 101;i++)
	for (j = 1; j < 201; j++)
	{
		// 计算周围活着的生命数量
		sum = world[i + 1][j] + world[i + 1][j - 1] + world[i][j - 1] + world[i- 1][j - 1]
			+ world[i - 1][j] + world[i - 1][j + 1] + world[i][j + 1] + world[i + 1][j + 1];

		// 计算当前位置的生命状态
		switch (sum)
		{
		case 3:		tmp[i][j] = 1;				break;
		case 2:		tmp[i][j] = world[i][j];	break;
		default:	tmp[i][j] = 0;				break;
		}
	}
	memcpy(world, tmp, 102 * 202 * sizeof(bool));  //从tmp中复制102 * 102 * sizeof(__int8)长度的数据给world

	
}
//王三，完成 打印，输入，输出函数
void dy_world()   //打印世界
{
	int x, y;
	int i, j;
	for (i = 1; i <101; i++)
	{
		for (j = 1; j <201; j++)     //两层循环根据方格状态存储器处理方格
		{
			x = (j - 1) * 9;
			y = (i - 1) * 9+26;
			putimage(x, y, world[i][j] ? &imgLive : &imgEmpty);   //用于在指定位置，当前设备上绘制指定图像
		}
	}
}

void RandWorld()   // 创建一个细胞随机分布的世界
{
	
	srand((unsigned)time(NULL));  // 设置随机种子

	for (int i = 1; i < 101; i++)
	for (int j = 1; j <= 201; j++)
		world[i][j] = rand() % 2;
}
void shuru()   //输入函数
{
	FILE *fp;
	if ((fp = fopen("data", "r")) == NULL)        //打开文件
	{
		setcolor(LIGHTRED);    // 设置字体颜色为亮红色
		outtextxy(1600, 5, "错误！"); //打印文字
		exit(0);
	}

	int i, j;
	char ch;
	for (i = 1; i <101; i++)   //两层循环赋值给tu[][]
	{
		for (j =1; j<201; j++)
		{
			ch=fgetc(fp);
			switch (ch)
			{
			case 48: world[i][j]=0; break;       //设置方格状态
			case 49: world[i][j] = 1; break;    //设置方格状态
			}

		}
	}
	dy_world();  //绘制世界
	setcolor(LIGHTRED);    // 设置字体颜色为亮红色
	outtextxy(1600, 5, "加载成功！"); //打印文字


}
void shuchu()    //输出函数
{
	FILE *fp;   //定义文件指针
	if ((fp = fopen("data", "w")) == NULL)       //打开文件并使fp指向文件
	{
		setcolor(LIGHTRED);    // 设置字体颜色为亮红色
		outtextxy(1600, 5, "错误！"); //打印文字
		exit(0);
	}

	char ch;
	int i, j;
	for (i = 1; i<101; i++)          //用两层循环向文件中输入数据
	{
		for (j = 1; j <201; j++)
		{
			switch (world[i][j])
			{
			case 0: ch = '0'; break;
			case 1: ch = '1'; break;
			}
			fputc(ch, fp);
		}
	}
	fclose(fp);      //关闭

	setcolor(LIGHTRED);    // 设置字体颜色为亮红色
	outtextxy(1600, 5, "保存成功！"); //打印文字
}