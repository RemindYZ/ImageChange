//Ҫ�õ���һЩ����
#ifndef FUNCTION_H
#define FUNCTION_H
#define pi 3.1415926
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<cmath>
#include <QtWidgets/qmessagebox.h>
using namespace cv;
//����ѡ��ĵ�
extern CvPoint PtRot[2];
extern CvPoint PtTPS[2][10];

//�����ж�
extern int flag1;
extern int i;
extern int j;
extern int num;
//��꽻������
//Rot��ͼ����תʱ�õ�
//TPS��ͼ����TPS����ʱ�õ�
static void onmouse_Rot(int event,int x,int y,int flags,void* ustc)
{
	if(event==CV_EVENT_LBUTTONUP)
	{
		PtRot[1]=cvPoint(x,y);
		flag1=1;
	}
	else if(event==CV_EVENT_LBUTTONDOWN)
	{
		PtRot[0]=cvPoint(x,y);
		flag1=0;
	}
}
static void onmouse_TPS(int event,int x,int y,int flags,void* ustc)
{
	
	if(i<num)
	{
		j=1;//��֤��û�в���������£�����ֱ�ӽ���ѭ��
		if(event==CV_EVENT_LBUTTONDOWN)
		{
			j=1;
			PtTPS[j][i]=cvPoint(x,y);
		}
		else if(event==CV_EVENT_LBUTTONUP)
		{
			j=0;
			PtTPS[j][i]=cvPoint(x,y);
			i++;
		}
	}
	/*for(i=0;i<num;i++)
	{
		for(j=0;j<2;j++)
		{
			cout<<endl<<PtTPS[j][i].x<<"  "<<PtTPS[j][i].y<<endl;
		}
	}*/
}

//TPS�л��õ��ĺ���
//����˷�
//A,BΪ��˵���������
//A�����СΪ(m,n),B�����СΪ(n,l)
double** xMatrix(double** A,double** B,int m,int n,int l);
//����ƴ��
//A�����B����ƴ��
//A�����СΪ(m,n),B�����СΪ(m,l)����(l,n)
//flag=0��ʾ����ӳ�,flag=1��ʾ��������
double** IncMatrix(double** A,double** B,int m,int n,int l,int flag);
//��������
double** InvMatrix(double** A,int n);
//����ת��
//A�����СΪ(m,n)
double** TMatrix(double** A,int m,int n);
//��ȡTPS�任����
double** TPS_Change(int num);
//˫���β�ֵ������
double **Bicubic(double u);
double S(double x);
#endif // FUNCTION_H
