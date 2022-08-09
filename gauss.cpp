#include<iostream>
using namespace std;
#define n 4   //ͨ�����ų����������Է�����Ĺ�ģ��С����ǰ��nֵ��ʾ���ý�nԪһ�����Է�����
void Process_of_elimination(double A[n][n], double b[n]);//��˹��Ԫ���̵ĺ�������
void Process_of_backword_steps(double A[n][n], double b[n],double x[n]);//�ش������̵ĺ�������

void main()
{ double A[n][n],b[n],x[n];//Ϊ����ϵ������A�ͳ���������b �����������ʵ�ֿ����ڴ�ռ�
  int i,j;

  //����ϵ������A������������b

  cout<<"please enter coefficent matrix A and column vector b: "<<endl;
  for (i = 0; i < n; i++) {
	  for (j = 0; j < n; j++)
		  cin >> A[i][j];
	  cin >> b[i];
  }

  //�������������Ƿ���ȷ
  cout<<"you  entered coefficent matrix A and column vector b just now : "<<endl;
  for (i=0;i<n;i++)
	{for(j=0;j<n;j++)
       cout<<A[i][j]<<"  ";
     cout<<b[i]<<endl;
     } 
 
  //���ø�˹��Ԫ���̵ĺ���������ϵ����Ԫ���� 
 
  Process_of_elimination( A,  b);

  //������Ԫ���

  cout<<"coefficent matrix A and column vector b after Process of elimination  : "<<endl;
	for (i=0;i<n;i++)
		{for(j=0;j<n;j++)
			cout<<A[i][j]<<"  ";
		 cout<<b[i]<<endl;
		} 
  //���ûش������̵ĺ���

  Process_of_backword_steps(A,b,x);

  //���������
 cout<<"the solution of the linear equations Ax=b : "<<endl;
   for(i=n-1;i>=0;i--)
      cout<<"x["<<i+1<<"]="<<x[i]<<endl;


} ///�������������


void Process_of_elimination(double A[n][n], double b[n]) //��˹��Ԫ���̵ĺ�������
{   int k,i,j,i1;
    double L;
    for (i=0;i<n-1;i++)      //�Ե�i��Ϊ������
		{for(k=i+1;k<n;k++)   //�Ե�K��Ϊ��������
			{L=-A[k][i]/A[i][i];
             cout<<"when to use row "<<i+1<<" act as tool to Procss row "<<k+1<<", calculated out multiply factor L="<<L<<"..."<<endl;
		     A[k][i]=0;
			 for(j=i+1;j<n;j++) //j����ʾA�б������Ԫ�ص��к�
			    A[k][j]=L*A[i][j]+A[k][j];
			 b[k]=L*b[i]+b[k];
			}
		 
	    //������Ԫ�м����

        cout<<"coefficent matrix A and column vector b after step "<<i+1<<"  Process of elimination  : "<<endl;
			for (i1=0;i1<n;i1++)
				{for(j=0;j<n;j++)
					cout<<A[i1][j]<<"  ";
				 cout<<b[i1]<<endl;
				} 
		}

}//��˹��Ԫ���̵ĺ����������


void Process_of_backword_steps(double A[n][n], double b[n],double x[n])//�ش������̵ĺ�������
{int i,j;
 double sum;
 x[n-1]=b[n-1]/A[n-1][n-1];
 for (i=n-2;i>=0;i--)
	{sum=0;
	  for(j=i+1;j<n;j++)
		 sum=sum+A[i][j]*x[j];
	 x[i]=(b[i]-sum)/A[i][i];
	}

}//�ش������̵ĺ����������



