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