//*****************************************/
//                                        */
//        ��43 ���� 2014011487            */
//                                        */
//*****************************************/
//�ϴθ���2016.11.16
//
//ReadME.txt����
//
//
//������
//win10 + VS2012 + Qt5.2.0 + OpenCV2.4.13
//
//
////////////////////////////////////////////
////////����ͼ��Ť������˵����//////////////
////////////////////////////////////////////
//1. �������ĸ�ֵ���м���ѡ�񣬣�1�������Ĭ����ת135�ȣ��ֶ����ѡ��
//                             ��2������ת�Ƕȣ��ֶ����ѡ��
//                             ��3�����������Ķ�������
//                             ��4�������������ִ�У�1���ͣ�2��
//2. ֻҪû�ж��������ת������0�������ĵ�ͱ任������Ҫ�������ɣ����������˵�����£�
//   ��1�������ת��ť
//   ��2����ͼ����ȡһ�㣬ʹ���������������Ҫ�ɿ���
//   ��3��Ȼ�󱣳���갴�µ�״̬���ƶ���꣬���յ㴦�ɿ�
//   ��4�������ֵ��Ծ����Կ��ܲ���Ҫ��һ�����������ⰴһ���������̣�����Ͱ��ո�ɣ���ʾȷ������ȷ��֮ǰ��������ѡ����������
//   ��5����һ�㼴Ϊ�任���ĵ㣬��һ��͵ڶ���ľ��뼴Ϊ�任����
//   ��6������������£����û����ת�Ƕȣ�Ĭ����ת�Ƕ�Ϊ135��
//3. ���ѡ�������ú�����ת��ť���ɡ��任�������ȡ0��������ֶ�ѡ��㣬�����ȡ���е����ݡ�
//
/////////////////////////////////////////////
//////////����ͼ�����˵����/////////////////
/////////////////////////////////////////////
//1. ���ĵ�������Բ������Ĭ����ͼ���е�Ϊ���Ľ��б任
//2. ����ϵ��Ϊ�������쳤�仯�������������任��0����
//3. slider��spinbox������ѡ������֮���������ġ�
//
/////////////////////////////////////////////
//////////����TPS��˵����////////////////////
/////////////////////////////////////////////
//1. ѡȡ��ʱͬͼ��Ť����ʹ���������������Ҫ�ɿ����ƶ���ƥ������ɿ�
//2. ���е�ѡ������ʾ���Ƶ��ƥ��������
//3. ���Ƶ���Ӧ�ô��ڵ���3��С�ڵ���10
//
//ѡ���ֵ��ʽʱҪ�����ֶ�����ǰ��Ŀ���Բ�㣨ǰ��Ŀ���Բ��㲻�ϡ�������
//������������Ҫ�����������һ�㣬����Ŀǰ�������������Щ�����ϱ任ǰ��Ҫ�������ȷ�ϣ���Щ����Ҫ
//
//
#include "imagechangenumpro1.h"
#include <QtWidgets/QApplication>
//һЩȫ�ֱ�������
//ע�⣡�������ļ�������ȫ�ֱ�������Ҫʹ��extern��������ʹ�Ľ�ѵ��
//static��ʹȫ�ֱ��������ڸ��ļ��п��ã��ǳ�����������һ����ӣ�
//
//���ڴ���ͨ�����õ��ĵ������ֵ
//�洢��ת��������
CvPoint PtRot[2];
//�洢TPS�Ŀ��Ƶ��ƥ���
CvPoint PtTPS[2][10];
//����һЩ�жϣ���Ҫ�ǵ�Ĵ洢
int flag1=0;
int i=0;
int j=1;
int num;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ImageChangeNumPro1 w;
	w.show();
	return a.exec();
}