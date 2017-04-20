#ifndef IMAGECHANGENUMPRO1_H
#define IMAGECHANGENUMPRO1_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qmessagebox.h>
#include "ui_imagechangenumpro1.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include "Function.h"
using namespace cv;
//储存选择的点
extern CvPoint PtRot[2];
extern CvPoint PtTPS[2][10];

//用于判断
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
	Mat Image_Source;//存储读取的图像
	Mat Image_Source_Copy;//原始图像的拷贝
	int change_type;//插值种类0-最近邻，1-双线性，2-双三次型
	int Type;//存储图像种类
	//图像旋转变形函数
	//image表示要做改变的图像，(X,Y)是进行变化的中心点，theta是旋转角度，row为旋转最大半径
	//ImageReturn表示变换后图像的矩阵
	//bilinear采用双线性插值,near采用最近领插值,bicubic采用双三次插值
	//默认旋转角度取得135度
	void ImageRot_bilinear(Mat &image,Mat &ImageReturn,double X,double Y,double row,double theta=135);
	void ImageRot_near(Mat &image,Mat &ImageReturn,double X,double Y,double row,double theta=135);
	void ImageRot_bicubic(Mat &image,Mat &ImageReturn,double X,double Y,double row,double theta=135);
	//径向畸变函数
	//image表示要做出改变的图像，（X,Y）是进行变化的中心点，k为径向畸变的二次项参数
	//畸变公式：r为点到变换中心点的距离
	//(x,y)=(x-X,y-Y)(1+k*r^2)+(X,Y);
	//ImageReturn表示变换后的图像矩阵
	//k在做收缩畸变时取值为1.8e-6效果明显,在做拉伸畸变时取-7.2e-6效果明显
	//后面的变化默认采用这两个参数
	//bilinear采用双线性插值,near采用最近领插值,bicubic采用双三次插值
	void ImageRad_bilinear(Mat &image,Mat &ImageReturn,double k,double X,double Y);
	void ImageRad_near(Mat &image,Mat &ImageReturn,double k,double X,double Y);
	void ImageRad_bicubic(Mat &image,Mat &ImageReturn,double k,double X,double Y);
	//TPS插值函数
	//bilinear采用双线性插值,near采用最近领插值,bicubic采用双三次插值
	void ImageTPS_bilinear(Mat &image,Mat &ImageReturn,int num);
	void ImageTPS_near(Mat &image,Mat &ImageReturn,int num);
	void ImageTPS_bicubic(Mat &image,Mat &ImageReturn,int num);
private slots:
	//三个变形的槽函数
	//图像扭曲槽函数
	void Rot();
	//图像畸变槽函数
	void Rad();
	//图像TPS变形的槽函数
	void TPS();
};

#endif // IMAGECHANGENUMPRO1_H
