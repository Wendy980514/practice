//��
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

//��
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

//��
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