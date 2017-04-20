//要用到的一些函数
#ifndef FUNCTION_H
#define FUNCTION_H
#define pi 3.1415926
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<cmath>
#include <QtWidgets/qmessagebox.h>
using namespace cv;
//储存选择的点
extern CvPoint PtRot[2];
extern CvPoint PtTPS[2][10];

//用于判断
extern int flag1;
extern int i;
extern int j;
extern int num;
//鼠标交互函数
//Rot是图像旋转时用的
//TPS是图像做TPS变形时用的
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
		j=1;//保证在没有操作的情况下，不会直接结束循环
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

//TPS中会用到的函数
//矩阵乘法
//A,B为相乘的两个矩阵
//A矩阵大小为(m,n),B矩阵大小为(n,l)
double** xMatrix(double** A,double** B,int m,int n,int l);
//矩阵拼接
//A矩阵和B矩阵拼接
//A矩阵大小为(m,n),B矩阵大小为(m,l)或者(l,n)
//flag=0表示矩阵加长,flag=1表示矩阵增宽
double** IncMatrix(double** A,double** B,int m,int n,int l,int flag);
//矩阵求逆
double** InvMatrix(double** A,int n);
//矩阵转置
//A矩阵大小为(m,n)
double** TMatrix(double** A,int m,int n);
//求取TPS变换矩阵
double** TPS_Change(int num);
//双三次插值矩阵函数
double **Bicubic(double u);
double S(double x);
#endif // FUNCTION_H
