#include"Function.h"
double S(double x)
{
	double A;
	double X=fabs(x);
	if(X<1)
		//A=1+0.5*pow(X,3)-1.5*X*X;
		A=2/3.0+0.5*X*X*X-X*X;
	else if(X>=1&&X<2)
		//A=6-12*X+7.5*X*X-1.5*pow(X,3);
		A=pow((2-X),3)/6;
	else
		A=0;
	return A;
}
double **Bicubic(double u)
{
	double **A=new double*[1];
	A[0]=new double [4];
	for(int i=0;i<4;i++)
	{
	    A[0][i]=S(u-i+1);
	}
	return A;
}
//矩阵乘法
//A,B为相乘的两个矩阵
//A矩阵大小为(m,n),B矩阵大小为(n,l)
double** xMatrix(double** A,double** B,int m,int n,int l)
{
	int k=0,s=0;
	double **x=new double*[m];
	for(int k=0;k<m;k++)
	{
		x[k]=new double [l];
	}
	for(k=0;k<m;k++)
	{
		for(s=0;s<l;s++)
		{
			x[k][s]=0;
			for(int p=0;p<n;p++)
			x[k][s]=x[k][s]+A[k][p]*B[p][s];
		}
	}
	return x;
}
//矩阵拼接
//A矩阵和B矩阵拼接
//A矩阵大小为(m,n),B矩阵大小为(m,l)或者(l,n)
//flag=0表示矩阵加长,flag=1表示矩阵增宽
double** IncMatrix(double** A,double** B,int m,int n,int l,int flag)
{
	int k=0,s=0;
	if(flag==0)
	{
		double **x=new double*[m+l];
		for(int k=0;k<m+l;k++)
		{
			x[k]=new double [n];
		}
		for(k=0;k<m;k++)
		{
			for(s=0;s<n;s++)
			{
				x[k][s]=A[k][s];
			}
		}
		for(k=m;k<m+l;k++)
		{
			for(s=0;s<n;s++)
			{
				x[k][s]=B[k-m][s];
			}
		}
		return x;
	}
	else
	{
		double **x=new double*[m];
		for(int k=0;k<m;k++)
		{
			x[k]=new double [n+l];
		}
		for(k=0;k<m;k++)
		{
			for(s=0;s<n+l;s++)
			{
				if(s<n)
					x[k][s]=A[k][s];
				else
					x[k][s]=B[k][s-n];
			}
		}
		return x;
	}
}
//矩阵求逆
double** InvMatrix(double** A,int n)
{
	int i, j, k;
    double max, temp;
	double **B=new double *[n];               
	for(int i=0;i<n;i++)
	{
		B[i]=new double [n];
	}
    double **t=new double *[n];                //临时矩阵
	for(int i=0;i<n;i++)
	{
		t[i]=new double [n];
	}
    //将A矩阵存放在临时矩阵t[n][n]中
    for (i = 0; i < n; i++)        
    {
        for (j = 0; j < n; j++)
        {
            t[i][j] = A[i][j];
        }
    }
    //初始化B矩阵为单位阵
    for (i = 0; i < n; i++)        
    {
        for (j = 0; j < n; j++)
        {
            B[i][j] = (i == j) ? (double)1 : 0;
        }
    }
    for (i = 0; i < n; i++)
    {
        //寻找主元
        max = t[i][i];
        k = i;
        for (j = i+1; j < n; j++)
        {
            if (fabs(t[j][i]) > fabs(max))
            {
                max = t[j][i];
                k = j;
            }
        }
        //如果主元所在行不是第i行，进行行交换
        if (k != i)
        {
            for (j = 0; j < n; j++)
            {
                temp = t[i][j];
                t[i][j] = t[k][j];
                t[k][j] = temp;
                //B伴随交换
                temp = B[i][j];
                B[i][j] = B[k][j];
                B[k][j] = temp; 
            }
        }
        //消去A的第i列除去i行以外的各行元素
        temp = t[i][i];
        for (j = 0; j < n; j++)
        {
            t[i][j] = t[i][j] / temp;        //主对角线上的元素变为1
            B[i][j] = B[i][j] / temp;        //伴随计算
        }
        for (j = 0; j < n; j++)        //第0行->第n行
        {
            if (j != i)                //不是第i行
            {
                temp = t[j][i];
                for (k = 0; k < n; k++)        //第j行元素 - i行元素*j列i行元素
                {
                    t[j][k] = t[j][k] - t[i][k]*temp;
                    B[j][k] = B[j][k] - B[i][k]*temp;
                }
            }
        }
    }
	return B;
}
//矩阵转置
//A矩阵大小为(m,n)
double** TMatrix(double** A,int m,int n)
{
	double **x=new double*[n];
	for(int k=0;k<n;k++)
	{
		x[k]=new double [m];
	}
	int k=0,p=0;
	for(k=0;k<m;k++)
	{
		for(p=0;p<n;p++)
		{
			x[p][k]=A[k][p];
		}
	}
	return x;
}
double** TPS_Change(int num)
{
	//按照文献，构造矩阵K
	double **K=new double *[num];
	int k=0,q=0;
	for(k=0;k<num;k++)
	{
		K[k]=new double [num];
	}
	for(k=0;k<num;k++)
	{
		for(q=0;q<num;q++)
		{
			if(k==q)
				K[k][q]=0;
			else
			{
				double t=PtTPS[0][k].x;
				double test=PtTPS[0][k].x-PtTPS[0][q].x;
				double r=(PtTPS[0][k].x-PtTPS[0][q].x)*(PtTPS[0][k].x-PtTPS[0][q].x)+(PtTPS[0][k].y-PtTPS[0][q].y)*(PtTPS[0][k].y-PtTPS[0][q].y);
				double u=r*log(r);
				K[k][q]=u;
			}
		}
	}
	//构造矩阵P
	double **P=new double *[num];
	for(int k=0;k<num;k++)
	{
		P[k]=new double [3];
	}
	for(int k=0;k<num;k++)
	{
		for(int q=0;q<3;q++)
		{
			if(q==0)
				P[k][q]=1;
			else if(q==1)
				P[k][q]=PtTPS[0][k].x;
			else
				P[k][q]=PtTPS[0][k].y;
		}
	}
	//转置矩阵P
	double **PT=TMatrix(P,num,3);
	double **O=new double*[3];
	for(int k=0;k<3;k++)
	{
		O[k]=new double [3];
	}
	for(int k=0;k<3;k++)
	{
		for(int q=0;q<3;q++)
		{
				O[k][q]=0;
		}
	}
	double **L1=IncMatrix(K,P,num,num,3,1);
	double **L2=IncMatrix(PT,O,3,num,3,1);
	double **L=IncMatrix(L1,L2,num,num+3,3,0);
	double **V=new double *[2];
	V[0]=new double [num+3];
	V[1]=new double [num+3];
	for(int k=0;k<2;k++)
	{
		for(int q=0;q<num+3;q++)
		{
			if(k==0&&q<num)
				V[k][q]=PtTPS[1][q].x;
			else if(k==1&&q<num)
				V[k][q]=PtTPS[1][q].y;
			else
				V[k][q]=0;
		}
	}
	double **VT=TMatrix(V,2,num+3);
	double **LL=InvMatrix(L,num+3);
	double **W=xMatrix(LL,VT,num+3,num+3,2);

	for(int i=1;i>=0;i--)
	{
		delete[] V[i];
	}
	delete[] V;
	for(int i=2;i>=0;i--)
	{
		delete[] O[i];
	}
	delete[] O;
	for(int i=num-1;i>=0;i--)
	{
		delete[] K[i];
	}
	delete[] K;
	for(int i=num-1;i>=0;i--)
	{
		delete[] P[i];
	}
	delete[] P;
	return W;
}
