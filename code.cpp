//��һ
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include <conio.h>
#include <time.h>
__int8 world[102][202] = {0};
IMAGE imgLive, imgEmpty;		// �����ϸ������ϸ�������ͼ��  //��������ͼ�����

MOUSEMSG m;              //���������Ϣ�ṹ��ı�����������ָ������ָ��
MOUSEMSG *_m = &m;

char s1[20] = "�ٶȣ�1", s2[20] = " ";    //�ٶ�ֵ�ַ���s1,s2
int Speed = 125;			// ��Ϸ�ٶȣ����룩

//��һ
void start();   //�����ʼ��
void kongjian(int x1, int x2, char *s);   //�ؼ�����
void zuotu(MOUSEMSG *_m);   //��ͼ
void shengsi();  //�����ж�
void shuru();   //���뺯��
void shuchu();    //�������
void dy_world();   //��ӡ����
void shubiao();   //����������
void RandWorld();  //�����������
void huitushebei();    //������ͼ�豸
void jianpanjiankong();   //���̼��

int main()
{
	

	initgraph(1800, 900);  //����һ���ߴ�Ϊ 1800x900 �Ļ�ͼ������ԭ�����꣨0��0����λ�����Ͻ�
	start();   //�����ʼ��
	huitushebei();     //������ͼ�豸
	while (true)
	{
		jianpanjiankong();  //���̼��
		shubiao();		//����������
		dy_world();			// ��������
		shengsi();			// �����ж�
		Sleep(Speed);
	}
	return 0;
}

//���
void start()
{
	memset(world, 0, 102 * 202 * sizeof(bool));   //��ʼ��world����
	setbkcolor(WHITE);// ���ñ���ɫΪ��ɫ
	cleardevice();// �ñ���ɫ�����Ļ
	setfillcolor(BLACK);   //���������ɫΪ��ɫ
	kongjian(0, 0, " ");
	setcolor(BROWN);    // ����������ɫΪ��ɫ
	outtextxy(900, 5, s1); //��ӡ�ٶ�ֵ
	setcolor(BLACK);    // ����������ɫΪ��ɫ
	outtextxy(400, 5, "Q/���  W/����  E/����  S/���"); //��ӡ����
}
void jianpanjiankong()   //���̼��
{
	if (_kbhit())   
	{
		char c = _getch();    //��ȡ����    //Speed����450ʱ���˴���ͣ

		if (c >='0' && c <= '9')
		{
			sprintf(s2, "%d", c - '0');      //���ٶ�ֵд���ַ�����s2��
			strcpy(s1, "�ٶȣ�");     //��ʼ��s1
			strcat(s1, s2);          //��s2���ӵ�s1��
			setcolor(BROWN);    // ����������ɫΪ��ɫ
			outtextxy(900, 5, s1); //��ӡ�ٶ�ֵ
			if (c == '0')
				Speed = 900;
			else
				Speed = ('9' - c) * 25;  //�����������ֵ����ٶ�
		}
		switch (c)
		{
		case 'q':
			start();  //�����ʼ��
			break;
		case 'w':
			shuchu();     //�������
			break;
		case 'e':
			shuru();     //�������
			break;

		case 's':
			RandWorld();   // ����һ��ϸ������ֲ�������
			dy_world();			// ��������
			break;

		case ' ':
			c = '/';
			setcolor(LIGHTRED);    // ����������ɫΪ����ɫ
			outtextxy(1400, 5, "��ͣ"); //��ӡ����
			while (c != ' ')
			{
				shubiao();  //����������
				Sleep(500);
				if (_kbhit())
				{
					c = _getch();
					dy_world();			// ��������	
					shengsi();			// �����ж�	
				}
			}
			setfillcolor(WHITE);        //���õ�ǰ�����ɫΪ��ɫ
			solidrectangle(1400, 5, 1450, 20);    //��ӡ��ɫ����,���ǡ���ͣ������
			setfillcolor(BLACK);        //���õ�ǰ�����ɫΪ��ɫ
			break;
		}
	}
}
//����
void huitushebei()     //������ͼ�豸
{
	// ��������ͼ���Ĵ�С
	Resize(&imgLive, 9, 9);    //
	Resize(&imgEmpty, 9, 9);   //���ڵ���ָ����ͼ�豸�ĳߴ硣

	// ���������������ͼ��
	SetWorkingImage(&imgLive);   //�����趨��ǰ�Ļ�ͼ�豸��
	setfillcolor(BLACK);        //���õ�ǰ�����ɫΪ��ɫ
	setcolor(LIGHTGRAY);        //���ñ߿���ɫΪ��ɫ
	fillrectangle(0, 0, 8, 8);    //��ӡ��ɫ�����б߿�

	// ���������������ͼ��
	SetWorkingImage(&imgEmpty);
	setfillcolor(WHITE);        //���õ�ǰ�����ɫΪ��ɫ
	solidrectangle(0, 0, 8, 8);    //��ӡ��ɫ����

	// �ָ���Ĭ�ϴ��ڵĻ�ͼ
	SetWorkingImage(NULL);
}
void shubiao()    //����������
{
	

	int x1 = 0, x2 = 0;      //x1,x2�洢�����ؼ������ұߵ�X����λ��
	while (MouseHit())   //����Ƿ��������Ϣ
	{
		m = GetMouseMsg();       //��ȡ�����Ϣ
		if (m.mkLButton || m.mkRButton)   //������Ҽ��Ƿ��а���
		{

			if (m.y > 26)      //m.y>26˵�����λ����ͼ��������λ�ڿؼ���
			{
				do
				{
					if (m.y > 26)
						zuotu(_m);  //�������Ϣ���ݸ���ͼ����
					m = GetMouseMsg();       //��ȡ�����Ϣ
				} while (m.mkLButton || m.mkRButton);   //ֱ���ɿ������Ž�����ͼ
			}
			else      //�ж����λ���ĸ��ؼ�
			{
				if (2 < m.x&&m.x < 63)
				{
					x1 = 2; x2 = 63;      //��һ���ؼ���λ��
					char s[] = "���";
					kongjian(x1, x2, s);  //ʵ�ֿؼ�����
					x1 = 0; x2 = 0;

					start();

				}
				if (72 < m.x&&m.x < 133)
				{
					x1 = 72; x2 = 133;     //�ڶ����ؼ���λ��
					char s[] = "����";
					kongjian(x1, x2, s);  //ʵ�ֿؼ�����
					x1 = 0;  x2 = 0;

					shuchu();     //�������

				}
				if (142 < m.x&&m.x < 203)
				{
					x1 = 142; x2 = 203;     //�������ؼ���λ��
					char s[] = "����";
					kongjian(x1, x2, s);  //ʵ�ֿؼ�����
					x1 = 0;  x2 = 0;

					shuru();     //�������
				}
				if (212 < m.x&&m.x < 273)
				{
					x1 = 212; x2 = 273;     //�������ؼ���λ��
					char s[] = "���";
					kongjian(x1, x2, s);  //ʵ�ֿؼ�����
					x1 = 0;  x2 = 0;

					RandWorld();   // ����һ��ϸ������ֲ�������
					dy_world();			// ��������

				}
				if (282 < m.x&&m.x < 343)
				{
					x1 = 142; x2 = 203;     //�������ؼ���λ��
					char s[] = "����";
					kongjian(x1, x2, s);  //ʵ�ֿؼ�����
					x1 = 0;  x2 = 0;

					exit(0);     //��������
				}

			};
		}
	}
	FlushMouseMsgBuffer();   //��������Ϣ������
}
void zuotu(MOUSEMSG *_m)   //��ͼ
{
	int x, y, xb, yb;

	xb = _m->x / 9+1;
	yb = (_m->y - 26) / 9+1;
	x = (xb - 1) * 9;
	y = (yb - 1) * 9 + 26;
	if (_m->mkLButton)
	{
		putimage(x, y, &imgLive);   //�����ʱ����ӡ�����б߿�
		world[yb][xb] = 1;
	}
	if (_m->mkRButton)
	{
		putimage(x, y, &imgEmpty);	//���Ҽ�ʱ��ɾ������
		world[yb][xb] = 0;
	}

}