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