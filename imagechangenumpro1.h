#ifndef IMAGECHANGENUMPRO1_H
#define IMAGECHANGENUMPRO1_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qmessagebox.h>
#include "ui_imagechangenumpro1.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include "Function.h"
using namespace cv;
//����ѡ��ĵ�
extern CvPoint PtRot[2];
extern CvPoint PtTPS[2][10];

//�����ж�
extern int flag1;
extern int i;
extern int j;
extern int num;
class ImageChangeNumPro1 : public QMainWindow
{
	Q_OBJECT

public:
	ImageChangeNumPro1(QWidget *parent = 0);
	~ImageChangeNumPro1();
	
private:
	Ui::ImageChangeNumPro1Class ui;
	Mat Image_Source;//�洢��ȡ��ͼ��
	Mat Image_Source_Copy;//ԭʼͼ��Ŀ���
	int change_type;//��ֵ����0-����ڣ�1-˫���ԣ�2-˫������
	int Type;//�洢ͼ������
	//ͼ����ת���κ���
	//image��ʾҪ���ı��ͼ��(X,Y)�ǽ��б仯�����ĵ㣬theta����ת�Ƕȣ�rowΪ��ת���뾶
	//ImageReturn��ʾ�任��ͼ��ľ���
	//bilinear����˫���Բ�ֵ,near����������ֵ,bicubic����˫���β�ֵ
	//Ĭ����ת�Ƕ�ȡ��135��
	void ImageRot_bilinear(Mat &image,Mat &ImageReturn,double X,double Y,double row,double theta=135);
	void ImageRot_near(Mat &image,Mat &ImageReturn,double X,double Y,double row,double theta=135);
	void ImageRot_bicubic(Mat &image,Mat &ImageReturn,double X,double Y,double row,double theta=135);
	//������亯��
	//image��ʾҪ�����ı��ͼ�񣬣�X,Y���ǽ��б仯�����ĵ㣬kΪ�������Ķ��������
	//���乫ʽ��rΪ�㵽�任���ĵ�ľ���
	//(x,y)=(x-X,y-Y)(1+k*r^2)+(X,Y);
	//ImageReturn��ʾ�任���ͼ�����
	//k������������ʱȡֵΪ1.8e-6Ч������,�����������ʱȡ-7.2e-6Ч������
	//����ı仯Ĭ�ϲ�������������
	//bilinear����˫���Բ�ֵ,near����������ֵ,bicubic����˫���β�ֵ
	void ImageRad_bilinear(Mat &image,Mat &ImageReturn,double k,double X,double Y);
	void ImageRad_near(Mat &image,Mat &ImageReturn,double k,double X,double Y);
	void ImageRad_bicubic(Mat &image,Mat &ImageReturn,double k,double X,double Y);
	//TPS��ֵ����
	//bilinear����˫���Բ�ֵ,near����������ֵ,bicubic����˫���β�ֵ
	void ImageTPS_bilinear(Mat &image,Mat &ImageReturn,int num);
	void ImageTPS_near(Mat &image,Mat &ImageReturn,int num);
	void ImageTPS_bicubic(Mat &image,Mat &ImageReturn,int num);
private slots:
	//�������εĲۺ���
	//ͼ��Ť���ۺ���
	void Rot();
	//ͼ�����ۺ���
	void Rad();
	//ͼ��TPS���εĲۺ���
	void TPS();
};

#endif // IMAGECHANGENUMPRO1_H
