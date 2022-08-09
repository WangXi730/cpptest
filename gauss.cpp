#include<iostream>
using namespace std;
#define n 4   //通过符号常量定义线性方程组的规模大小，当前的n值表示适用解n元一次线性方程组
void Process_of_elimination(double A[n][n], double b[n]);//高斯消元过程的函数声明
void Process_of_backword_steps(double A[n][n], double b[n],double x[n]);//回代求解过程的函数声明

void main()
{ double A[n][n],b[n],x[n];//为输入系数矩阵A和常数列向量b ，定义数组而实现开辟内存空间
  int i,j;

  //输入系数矩阵A，常数列向量b

  cout<<"please enter coefficent matrix A and column vector b: "<<endl;
  for (i = 0; i < n; i++) {
	  for (j = 0; j < n; j++)
		  cin >> A[i][j];
	  cin >> b[i];
  }

  //查验输入数据是否正确
  cout<<"you  entered coefficent matrix A and column vector b just now : "<<endl;
  for (i=0;i<n;i++)
	{for(j=0;j<n;j++)
       cout<<A[i][j]<<"  ";
     cout<<b[i]<<endl;
     } 
 
  //调用高斯消元过程的函数，进行系列消元工作 
 
  Process_of_elimination( A,  b);

  //观赏消元结果

  cout<<"coefficent matrix A and column vector b after Process of elimination  : "<<endl;
	for (i=0;i<n;i++)
		{for(j=0;j<n;j++)
			cout<<A[i][j]<<"  ";
		 cout<<b[i]<<endl;
		} 
  //调用回代求解过程的函数

  Process_of_backword_steps(A,b,x);

  //输出解向量
 cout<<"the solution of the linear equations Ax=b : "<<endl;
   for(i=n-1;i>=0;i--)
      cout<<"x["<<i+1<<"]="<<x[i]<<endl;


} ///主函数程序结束


void Process_of_elimination(double A[n][n], double b[n]) //高斯消元过程的函数定义
{   int k,i,j,i1;
    double L;
    for (i=0;i<n-1;i++)      //以第i行为工具行
		{for(k=i+1;k<n;k++)   //以第K行为被处理行
			{L=-A[k][i]/A[i][i];
             cout<<"when to use row "<<i+1<<" act as tool to Procss row "<<k+1<<", calculated out multiply factor L="<<L<<"..."<<endl;
		     A[k][i]=0;
			 for(j=i+1;j<n;j++) //j仅表示A中被处理的元素的列号
			    A[k][j]=L*A[i][j]+A[k][j];
			 b[k]=L*b[i]+b[k];
			}
		 
	    //观赏消元中间过程

        cout<<"coefficent matrix A and column vector b after step "<<i+1<<"  Process of elimination  : "<<endl;
			for (i1=0;i1<n;i1++)
				{for(j=0;j<n;j++)
					cout<<A[i1][j]<<"  ";
				 cout<<b[i1]<<endl;
				} 
		}

}//高斯消元过程的函数程序结束


void Process_of_backword_steps(double A[n][n], double b[n],double x[n])//回代求解过程的函数定义
{int i,j;
 double sum;
 x[n-1]=b[n-1]/A[n-1][n-1];
 for (i=n-2;i>=0;i--)
	{sum=0;
	  for(j=i+1;j<n;j++)
		 sum=sum+A[i][j]*x[j];
	 x[i]=(b[i]-sum)/A[i][i];
	}

}//回代求解过程的函数程序结束



