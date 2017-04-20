#include "imagechangenumpro1.h"
using namespace cv;

//���캯��
ImageChangeNumPro1::ImageChangeNumPro1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//��ȡ��ɫͼ��
	//ע���޸�·��
	Image_Source=imread("lena.jpg");
	Image_Source_Copy=Image_Source.clone();
	Type=Image_Source.type();
	//����rationButton��ID�������ж��ĸ�ratioButton������
	ui.buttonGroup->setId(ui.radioButton,0);//�����
	ui.buttonGroup->setId(ui.radioButton_2,1);//˫����
	ui.buttonGroup->setId(ui.radioButton_3,2);//˫������
	ui.radioButton->setChecked(true);
}
//��������
ImageChangeNumPro1::~ImageChangeNumPro1()
{
}

//ͼ��Ť���ۺ���
void ImageChangeNumPro1::Rot()
{
	ui.progressBar->setValue(0);//����������
	destroyAllWindows();
	Image_Source_Copy=Image_Source.clone();
	change_type=ui.buttonGroup->checkedId();//��ȡ��ֵ��ʽ
	flag1=0;
	namedWindow("source.jpg");
	imshow("source.jpg",Image_Source_Copy);
	//��ȡ�����е�����
	//ת��Ϊint�ͱ���
	QString X_cen=ui.XlineEditRot->text();
	QString Y_cen=ui.YlineEditRot->text();
	QString Len=ui.LlineEdit->text();
	QString Zeta=ui.AlineEdit->text();
	int x_cen = atoi(X_cen.toStdString().c_str());
	int y_cen = atoi(Y_cen.toStdString().c_str());
	int len = atoi(Len.toStdString().c_str());
	int zeta = atoi(Zeta.toStdString().c_str());
	//һЩԭʼͼ�����
	int x_central=Image_Source.rows/2;
	int y_central=Image_Source.cols/2;

	//������Χ����
	if(x_cen<0||x_cen>Image_Source.rows||y_cen<0||y_cen>Image_Source.cols)
	{
		QMessageBox::critical(this,"Error!!","SomeNumIncorrect!",QMessageBox::Yes,QMessageBox::Cancel);
	}
	else
	{
	   //���������ԭͼ����ȡ�е����ת�뾶
		//len==0��ʾ����û����ȣ���ʾҪ��ͼ����ѡ���
	   if(len==0)
	   {
		   while(true)
			{
				cvSetMouseCallback("source.jpg",onmouse_Rot,0);
				waitKey();
				if(flag1==1)
				{
					flag1=0;break;
				}
			}
			double distance=sqrt(pow(double(PtRot[1].x-PtRot[0].x),2)+pow(double(PtRot[1].y-PtRot[0].y),2));
			ui.progressBar->setValue(30);
			//�������߿հ�ͼ��Ȼ��ͨ����ֵ����
			Mat Image_Change1=Mat::zeros(Image_Source.rows,Image_Source.cols,Type);
			destroyAllWindows();
			if(zeta==0)
			{
				switch(change_type)
				{
					case 0:ImageRot_near(Image_Source,Image_Change1,PtRot[0].y,PtRot[0].x,distance);break;
					case 1:ImageRot_bilinear(Image_Source,Image_Change1,PtRot[0].y,PtRot[0].x,distance);break;
					case 2:ImageRot_bicubic(Image_Source,Image_Change1,PtRot[0].y,PtRot[0].x,distance);break;
				}
			}
			else
			{
			    switch(change_type)
				{
				    case 0:ImageRot_near(Image_Source,Image_Change1,PtRot[0].y,PtRot[0].x,distance,zeta);break;
					case 1:ImageRot_bilinear(Image_Source,Image_Change1,PtRot[0].y,PtRot[0].x,distance,zeta);break;
					case 2:ImageRot_bicubic(Image_Source,Image_Change1,PtRot[0].y,PtRot[0].x,distance,zeta);break;
				}
			}
			ui.progressBar->setValue(90);
			namedWindow("Rot_1.jpg");
			imshow("Rot_1.jpg",Image_Change1);
			ui.progressBar->setValue(100);
	   }
	   else
	   {
	      Mat Image_Change1=Mat::zeros(Image_Source.rows,Image_Source.cols,Type);
		  destroyAllWindows();
		  switch(change_type)
			{
			case 0:ImageRot_near(Image_Source,Image_Change1,x_cen,y_cen,len,zeta);break;
			case 1:ImageRot_bilinear(Image_Source,Image_Change1,x_cen,y_cen,len,zeta);break;
			case 2:ImageRot_bicubic(Image_Source,Image_Change1,x_cen,y_cen,len,zeta);break;
			}
		  ui.progressBar->setValue(90);
	      namedWindow("Rot_1.jpg");
	      imshow("Rot_1.jpg",Image_Change1);
	      ui.progressBar->setValue(100);
	   }
	   waitKey();
	}
}
//ͼ�����ۺ���
void ImageChangeNumPro1::Rad()
{
	ui.progressBar->setValue(0);
	destroyAllWindows();
	Image_Source_Copy=Image_Source.clone();
	change_type=ui.buttonGroup->checkedId();
	namedWindow("source.jpg");
	imshow("source.jpg",Image_Source_Copy);
	//��ȡ�����е�����
	//ת��Ϊint�ͱ���
	QString X_cen=ui.XlineEditRad->text();
	QString Y_cen=ui.YlineEditRad->text();
	int x_cen = atoi(X_cen.toStdString().c_str());
	int y_cen = atoi(Y_cen.toStdString().c_str());
	int k=ui.spinBox->value();
	//һЩԭʼͼ�����
	int x_central=Image_Source.rows/2;
	int y_central=Image_Source.cols/2;
	//�½��հ�ͼ��
	Mat Image_Change1=Mat::zeros(Image_Source.rows,Image_Source.cols,Type);
	//������������Χ
	if(x_cen<0||x_cen>Image_Source.rows||y_cen<0||y_cen>Image_Source.cols)
	{
		QMessageBox::critical(this,"Error!!","SomeNumIncorrect!",QMessageBox::Yes,QMessageBox::Cancel);
	}
	else
	{
		ui.progressBar->setValue(30);
		destroyAllWindows();
		//X_cen==""��ʾ������δ������
		//Ĭ��������ת
		if(X_cen=="")
		{
			switch(change_type)
			{
			case 0:
				ImageRad_near(Image_Source,Image_Change1,k*6e-7,x_central,y_central);
				break;
			case 1:
				ImageRad_bilinear(Image_Source,Image_Change1,k*6e-7,x_central,y_central);
				break;
			case 2:
				 ImageRad_bicubic(Image_Source,Image_Change1,k*6e-7,x_central,y_central);
				 break;
			}
		}
		else
		{
			switch(change_type)
			{
			case 0:
				ImageRad_near(Image_Source,Image_Change1,k*6e-7,x_cen,y_cen);
				break;
			case 1:
				ImageRad_bilinear(Image_Source,Image_Change1,k*6e-7,x_cen,y_cen);
				break;
			case 2:
				ImageRad_bicubic(Image_Source,Image_Change1,k*6e-7,x_cen,y_cen);
				break;
			}
		}
		ui.progressBar->setValue(100);
		namedWindow("Rad_1.jpg");
		imshow("Rad_1.jpg",Image_Change1);
		waitKey();
	}
}
//TPS�ۺ���
void ImageChangeNumPro1::TPS()
{
	ui.progressBar->setValue(0);
	destroyAllWindows();
	Image_Source_Copy=Image_Source.clone();
	change_type=ui.buttonGroup->checkedId();
	namedWindow("source.jpg");
	imshow("source.jpg",Image_Source_Copy);
	//QString Num=ui.NumlineEdit->text();
	num = ui.spinBox_2->value();
	//���Ƶ���Ŀ����10�������Ի��򱨴�
	if(num>10)
		QMessageBox::critical(this,"Error!!","TheNumMust<=10!!",QMessageBox::Yes,QMessageBox::Cancel);
	else
	{
		while(true)
		{
			cvSetMouseCallback("source.jpg",onmouse_TPS,0);
			waitKey();
			if(i==num)
				break;
		}
		//����ѡ�������ͼ��������ֱ��
		for(int i=0;i<num;i++)
		{
			line(Image_Source_Copy,PtTPS[0][i],PtTPS[1][i],Scalar(0,0,255),2);
		}
		ui.progressBar->setValue(30);
	    Mat Image_Change1=Mat::zeros(Image_Source.rows,Image_Source.cols,Type);
		destroyAllWindows();
		switch(change_type)
		{
		case 0:ImageTPS_near(Image_Source,Image_Change1,num);break;
		case 1:ImageTPS_bilinear(Image_Source,Image_Change1,num);break;
		case 2:ImageTPS_bicubic(Image_Source,Image_Change1,num);break;
		}
		ui.progressBar->setValue(100);
		namedWindow("source.jpg");
        imshow("source.jpg",Image_Source_Copy);
		namedWindow("ImageTPS_1.jpg");
		imshow("ImageTPS_1.jpg",Image_Change1);
		i=0;j=0;
	    waitKey(0);
	}
}
void ImageChangeNumPro1::ImageRot_bilinear(Mat &image,Mat &ImageReturn,double X,double Y,double row,double theta)
{
	//�洢ͼ�񳤶ȺͿ����Ϣ
	int lenth=image.rows;
	int width=image.cols;
	
	int i=0,j=0;
	//�ǶȺͻ���ת��
	//���׳���ĵط�
	double theta1=theta*pi/180;

	//���ò����OpenCV����Ҫ�����ɫͼ����Ҫ�ı�������
	Mat_<Vec3b> _image=image;
	Mat_<Vec3b> _ImageReturn=ImageReturn;
	for(i=0;i<lenth;i++)  //�����������ص�
	{
 		for(j=0;j<width;j++)
		{
			double r=sqrt((i-X)*(i-X)+(j-Y)*(j-Y));//����
			if(r<=row&&(i!=X||j!=Y))
			{
				//��ȡ��ʼλ�õķ�λ��
				//����i,j��X,Y�Ĺ�ϵ���ڲ�ͬ�����޷�������
				//�õ���ȷ�ĽǶ�ֵ
				double Alpha=0;
				if(i>=X&&j>Y)
					Alpha=atan((i-X)/(j-Y));
				else if(i>X&&j<=Y)
				{
					if(j==Y) Alpha=90*pi/180;
					else Alpha=atan((i-X)/(j-Y))+pi;
				}
				else if(i<=X&&j<Y)
				{
					Alpha=atan((i-X)/(j-Y))+180*pi/180;
				}
				else if(i<X&&j>=Y)
				{
					if(j==Y)Alpha=270*pi/180;
					else Alpha=atan((i-X)/(j-Y));
				}
				//��ת�任
				double x=r*sin(Alpha+theta1*(row-r)/row)+X;
				double y=r*cos(Alpha+theta1*(row-r)/row)+Y;
				//��ʼ��ֵ
				//˫���Բ�ֵ
				if(x>=0&&x<lenth-1&&y>=0&&y<width-1)
				{
				    int m=floor(x);
				    int n=floor(y);
				    double u=x-m;
				    double v=y-n;
				    for(int c=0;c<3;c++) //����ͨ���ֱ��ֵ
				    {
					    double s1=_image(m,n)[c]*(1-v)+_image(m,n+1)[c]*v;
					    double s2=_image(m+1,n)[c]*(1-v)+_image(m+1,n+1)[c]*v;
				        _ImageReturn(i,j)[c]=s1*(1-u)+s2*u;
				    }
				}
			}
			else
			{
				_ImageReturn(i,j)[0]=_image(i,j)[0];
				_ImageReturn(i,j)[1]=_image(i,j)[1];
				_ImageReturn(i,j)[2]=_image(i,j)[2];
			}
		}
	}
	ImageReturn=_ImageReturn;
}
void ImageChangeNumPro1::ImageRot_near(Mat &image,Mat &ImageReturn,double X,double Y,double row,double theta)
{
	//�����溯��һ��
	//������ϸ˵��
	int lenth=image.rows;
	int width=image.cols;
	int i=0,j=0;
	double theta1=theta*pi/180;
	Mat_<Vec3b> _image=image;
	Mat_<Vec3b> _ImageReturn=ImageReturn;
	for(i=0;i<lenth;++i)
	{
		for(j=0;j<width;++j)
		{
			double r=sqrt((i-X)*(i-X)+(j-Y)*(j-Y));
			if(r<=row&&(i!=X||j!=Y))
			{
				double Alpha=0;
				if(i>=X&&j>Y)
					Alpha=atan((i-X)/(j-Y));
				else if(i>X&&j<=Y)
				{
					if(j==Y) Alpha=90*pi/180;
					else Alpha=atan((i-X)/(j-Y))+pi;
				}
				else if(i<=X&&j<Y)
				{
					Alpha=atan((i-X)/(j-Y))+180*pi/180;
				}
				else if(i<X&&j>=Y)
				{
					if(j==Y)Alpha=270*pi/180;
					else Alpha=atan((i-X)/(j-Y));
				}
				double x=r*sin(Alpha+theta1*(row-r)/row)+X;
				double y=r*cos(Alpha+theta1*(row-r)/row)+Y;
				//����ڲ�ֵ
				if(x>=0&&x<lenth&&y>=0&&y<width)
				{
				   int m=floor(x);
				   int n=floor(y);
				   for(int c=0;c<3;c++)
				   {
					 _ImageReturn(i,j)[c]=_image(m,n)[c];
				   }
				}
			}
			else
			{
				_ImageReturn(i,j)[0]=_image(i,j)[0];
				_ImageReturn(i,j)[1]=_image(i,j)[1];
				_ImageReturn(i,j)[2]=_image(i,j)[2];
			}
		}
	}
	ImageReturn=_ImageReturn;
}
void ImageChangeNumPro1::ImageRot_bicubic(Mat &image,Mat &ImageReturn,double X,double Y,double row,double theta)
{
	//�����溯��һ��
	//������ϸ˵��
	int lenth=image.rows;
	int width=image.cols;
	int i=0,j=0;
	double theta1=theta*pi/180;
	Mat_<Vec3b> _image=image;
	Mat_<Vec3b> _ImageReturn=ImageReturn;
	for(i=0;i<lenth;++i)
	{
		for(j=0;j<width;++j)
		{
			double r=sqrt((i-X)*(i-X)+(j-Y)*(j-Y));
			if(r<=row&&(i!=X||j!=Y))
			{
				double Alpha=0;
				if(i>=X&&j>Y)
					Alpha=atan((i-X)/(j-Y));
				else if(i>X&&j<=Y)
				{
					if(j==Y) Alpha=90*pi/180;
					else Alpha=atan((i-X)/(j-Y))+pi;
				}
				else if(i<=X&&j<Y)
				{
					Alpha=atan((i-X)/(j-Y))+180*pi/180;
				}
				else if(i<X&&j>=Y)
				{
					if(j==Y)Alpha=270*pi/180;
					else Alpha=atan((i-X)/(j-Y));
				}
				double x=r*sin(Alpha+theta1*(row-r)/row)+X;
				double y=r*cos(Alpha+theta1*(row-r)/row)+Y;
				
				if(x>=2&&x<lenth-3&&y>=2&&y<width-3)
				{
				   //˫���β�ֵ
				   int m=floor(x);
				   int n=floor(y);
				   double u=x-m;
				   double v=y-n;
				   double **A=Bicubic(u);
				   double **B=Bicubic(v);
				   for(int c=0;c<3;c++)
				   {
					   double **C=new double *[4];
					   for(int i=0;i<4;i++)
					   {
						   C[i]=new double [4];
					   }
					   for(int i=0;i<4;i++)
					   {
						   for(int j=0;j<4;j++)
						   {
							   C[i][j]=_image(m-1+i,n-1+j)[c];
						   }
					   }
					   _ImageReturn(i,j)[c]=**xMatrix(xMatrix(A,C,1,4,4),TMatrix(B,1,4),1,4,1);
				   }
				}
			}
			else
			{
				_ImageReturn(i,j)[0]=_image(i,j)[0];
				_ImageReturn(i,j)[1]=_image(i,j)[1];
				_ImageReturn(i,j)[2]=_image(i,j)[2];
			}
		}
		ui.progressBar->setValue(30+i/6);
	}
	ImageReturn=_ImageReturn;
}
void ImageChangeNumPro1::ImageRad_bilinear(Mat &image,Mat &ImageReturn,double k,double X,double Y)
{
	int lenth=image.rows;
	int width=image.cols;
	int i=0,j=0;
	Mat_<Vec3b> _image=image;
	Mat_<Vec3b> _ImageReturn=ImageReturn;
	for(i=0;i<lenth;i++)
	{
		for(j=0;j<width;j++)
		{
			double distance=sqrt((i-X)*(i-X)+(j-Y)*(j-Y));
			/*double x=0,y=0;
			if(i+j>=X+Y-1)
			{
			     x=i*(1+k*distance*distance);
			     y=j*(1+k*distance*distance);
			}
			else
			{
				x=(2*X-i)*(1+k*distance*distance);
				y=(2*Y-j)*(1+k*distance*distance);
				x=2*X-x;
				y=2*Y-y;
			}*/
			
			//���ҵ���ͼ������乫ʽ
			double x=(i-X)*(1+k*distance*distance)+X;
			double y=(j-Y)*(1+k*distance*distance)+Y;
			//˫���Բ�ֵ
			if(x>=0&&x<lenth-1&&y>=0&&y<width-1)
				{
				    int m=floor(x);
				    int n=floor(y);
				    double u=x-m;
				    double v=y-n;
				    for(int c=0;c<3;c++)
				    {
					    double s1=_image(m,n)[c]*(1-v)+_image(m,n+1)[c]*v;
					    double s2=_image(m+1,n)[c]*(1-v)+_image(m+1,n+1)[c]*v;
				        _ImageReturn(i,j)[c]=s1*(1-u)+s2*u;
				    }
				}
		}
	}
	ImageReturn=_ImageReturn;
}
void ImageChangeNumPro1::ImageRad_near(Mat &image,Mat &ImageReturn,double k,double X,double Y)
{
	int lenth=image.rows;
	int width=image.cols;
	int i=0,j=0;
	Mat_<Vec3b> _image=image;
	Mat_<Vec3b> _ImageReturn=ImageReturn;
	for(i=0;i<lenth;i++)
	{
		for(j=0;j<width;j++)
		{
			double distance=sqrt((i-X)*(i-X)+(j-Y)*(j-Y));
			/*double x=0,y=0;
			if(i+j>X+Y-1)
			{
			     x=i*(1+k*distance*distance);
			     y=j*(1+k*distance*distance);
			}
			else
			{
				x=(2*X-i)*(1+k*distance*distance);
				y=(2*Y-j)*(1+k*distance*distance);
				x=2*X-x;
				y=2*Y-y;
			}*/
			double x=(i-X)*(1+k*distance*distance)+X;
			double y=(j-Y)*(1+k*distance*distance)+Y;
			//����ڲ�ֵ
			if(x>=0&&x<lenth&&y>=0&&y<width)
				{
				   int m=floor(x);
				   int n=floor(y);
				   for(int c=0;c<3;c++)
				   {
					 _ImageReturn(i,j)[c]=_image(m,n)[c];
				   }
				}
		}
	}
	ImageReturn=_ImageReturn;
}
void ImageChangeNumPro1::ImageRad_bicubic(Mat &image,Mat &ImageReturn,double k,double X,double Y)
{
	int val=ui.progressBar->value();
	int lenth=image.rows;
	int width=image.cols;
	int i=0,j=0;
	Mat_<Vec3b> _image=image;
	Mat_<Vec3b> _ImageReturn=ImageReturn;
	for(i=0;i<lenth;i++)
	{
		for(j=0;j<width;j++)
		{
			double distance=sqrt((i-X)*(i-X)+(j-Y)*(j-Y));
			/*double x=0,y=0;
			if(i+j>X+Y-1)
			{
			     x=i*(1+k*distance*distance);
			     y=j*(1+k*distance*distance);
			}
			else
			{
				x=(2*X-i)*(1+k*distance*distance);
				y=(2*Y-j)*(1+k*distance*distance);
				x=2*X-x;
				y=2*Y-y;
			}*/
			double x=(i-X)*(1+k*distance*distance)+X;
			double y=(j-Y)*(1+k*distance*distance)+Y;
			if(x>=1&&x<lenth-3&&y>=1&&y<width-3)
				{
				   //˫���β�ֵ
				   int m=floor(x);
				   int n=floor(y);
				   double u=x-m;
				   double v=y-n;
				   double **A=Bicubic(u);
				   double **B=Bicubic(v);
				   for(int c=0;c<3;c++)
				   {
					   double **C=new double *[4];
					   for(int i=0;i<4;i++)
					   {
						   C[i]=new double [4];
					   }
					   for(int i=0;i<4;i++)
					   {
						   for(int j=0;j<4;j++)
						   {
							   C[i][j]=_image(m-1+i,n-1+j)[c];
						   }
					   }
					   _ImageReturn(i,j)[c]=**xMatrix(xMatrix(A,C,1,4,4),TMatrix(B,1,4),1,4,1);
				   }
				}
		}
		ui.progressBar->setValue(val+i/6);
	}
	ImageReturn=_ImageReturn;
}
void ImageChangeNumPro1::ImageTPS_bilinear(Mat &image,Mat &ImageReturn,int num)
{
    double** W=TPS_Change(num);
	double* Y=new double[num+3];
	int lenth=image.rows;
	int width=image.cols;
	int i=0,j=0;
	Mat_<Vec3b> _image=image;
	Mat_<Vec3b> _ImageReturn=ImageReturn;
	for(i=0;i<lenth;i++)
	{
		for(j=0;j<width;j++)
		{
			double h=0,z=0;
			for(int k=0;k<num+3;k++)
			{
				if(k<num)
				{
					double r=pow(PtTPS[0][k].x-j,2)+pow(PtTPS[0][k].y-i,2);
					if(r>0)
						Y[k]=r*log(r);
					else 
						Y[k]=0;
				}
				else if(k==num)
					Y[k]=1;
				else if(k==num+1)
					Y[k]=j;
				else
					Y[k]=i;
			}
			for(int k=0;k<num+3;k++)
			{
				h=h+W[k][0]*Y[k];
				z=z+W[k][1]*Y[k];
			}
			if(z>=0&&z<lenth-1&&h>=0&&h<width-1)
				{
					int m=floor(z);
				    int n=floor(h);
					double u=z-m;
				    double v=h-n;
				    for(int c=0;c<3;c++)
				    {
					    double s1=_image(m,n)[c]*(1-v)+_image(m,n+1)[c]*v;
					    double s2=_image(m+1,n)[c]*(1-v)+_image(m+1,n+1)[c]*v;
				        _ImageReturn(i,j)[c]=s1*(1-u)+s2*u;
				    }
				}
		}
	}
	ImageReturn=_ImageReturn;
}
void ImageChangeNumPro1::ImageTPS_near(Mat &image,Mat &ImageReturn,int num)
{
	double** W=TPS_Change(num);
	double* Y=new double[num+3];
	int lenth=image.rows;
	int width=image.cols;
	int i=0,j=0;
	Mat_<Vec3b> _image=image;
	Mat_<Vec3b> _ImageReturn=ImageReturn;
	for(i=0;i<lenth;i++)
	{
		for(j=0;j<width;j++)
		{
			double h=0,z=0;
			for(int k=0;k<num+3;k++)
			{
				if(k<num)
				{
					double r=pow(PtTPS[0][k].x-j,2)+pow(PtTPS[0][k].y-i,2);
					if(r>0)
						Y[k]=r*log(r);
					else 
						Y[k]=0;
				}
				else if(k==num)
					Y[k]=1;
				else if(k==num+1)
					Y[k]=j;
				else
					Y[k]=i;
			}
			for(int k=0;k<num+3;k++)
			{
				h=h+W[k][0]*Y[k];
				z=z+W[k][1]*Y[k];
			}
			if(z>=0&&z<lenth-1&&h>=0&&h<width-1)
				{
					int m=floor(z);
				    int n=floor(h);
				    for(int c=0;c<3;c++)
				    {
						_ImageReturn(i,j)[c]=_image(m,n)[c];
				    }
				}
		}
	}
	ImageReturn=_ImageReturn;
}
void ImageChangeNumPro1::ImageTPS_bicubic(Mat &image,Mat &ImageReturn,int num)
{
	double** W=TPS_Change(num);
	double* Y=new double[num+3];
	int lenth=image.rows;
	int width=image.cols;
	int i=0,j=0;
	Mat_<Vec3b> _image=image;
	Mat_<Vec3b> _ImageReturn=ImageReturn;
	for(i=0;i<lenth;i++)
	{
		for(j=0;j<width;j++)
		{
			double h=0,z=0;
			for(int k=0;k<num+3;k++)
			{
				if(k<num)
				{
					double r=pow(PtTPS[0][k].x-j,2)+pow(PtTPS[0][k].y-i,2);
					if(r>0)
						Y[k]=r*log(r);
					else 
						Y[k]=0;
				}
				else if(k==num)
					Y[k]=1;
				else if(k==num+1)
					Y[k]=j;
				else
					Y[k]=i;
			}
			for(int k=0;k<num+3;k++)
			{
				h=h+W[k][0]*Y[k];
				z=z+W[k][1]*Y[k];
			}
			if(z>=1&&z<lenth-3&&h>=1&&h<width-3) //ע��ȡֵ��Χ��ֹ��ֵԽ��
				{
					 //˫���β�ֵ
				   int m=floor(z);
				   int n=floor(h);
				   double u=z-m;
				   double v=h-n;
				   double **A=Bicubic(u);
				   double **B=Bicubic(v);
				   for(int c=0;c<3;c++)
				   {
					   double **C=new double *[4];
					   for(int i=0;i<4;i++)
					   {
						   C[i]=new double [4];
					   }
					   for(int i=0;i<4;i++)
					   {
						   for(int j=0;j<4;j++)
						   {
							   C[i][j]=_image(m-1+i,n-1+j)[c];
						   }
					   }
					   _ImageReturn(i,j)[c]=**xMatrix(xMatrix(A,C,1,4,4),TMatrix(B,1,4),1,4,1);
				   }
				}
		}
		ui.progressBar->setValue(30+i/6);
	}
	ImageReturn=_ImageReturn;
}