#include<iostream>
#include<cmath>
#include"Mat.hpp"

void print(Mat A, std::vector<double> b, Mat X);

//列主元高斯消去法解线性方程组
//若无解，返回0行0列矩阵
Mat Gauss(Mat A, std::vector<double> b){
	//若有解，A为m*n矩阵，则返回一个n*(n+1)的矩阵，末列是常数向量，第i列为自由未知量i的系数
	Mat X(A.col(),A.col()+1);
	//print(A,b,X);
	//消元，使得A变成阶梯型矩阵
	int j = -1;//用j表示无需消元的最大行
	for(int i=0;i<A.col();++i){
		//找列主元
		double max_num = std::fabs(A[j+1][i]);
		int num_addr = j+1;
		for(int k=j+2;k<A.row();++k){
			if(std::fabs(A[k][i]) > max_num){
				max_num = std::fabs(A[k][i]);
				num_addr = k;
			}
		}
		//如果绝对值最大的元素是0，则不需要消元
		if(max_num == 0){
			continue;
		}
		//交换两行
		if(num_addr != j+1){
			A.trans_row(num_addr, j+1);
			//右端向量b做同样的事情
			double tmp = b[num_addr];
			b[num_addr] = b[j+1];
			b[j+1] = tmp;
		}
		//print(A,b,X);
		//消元
		for(int k=j+2;k<A.col();++k){
			double tmp = -A[k][i]/A[j+1][i];
			A.trans_row(j+1,k,tmp);
			//右端向量做相同的事情
			b[k] += tmp*b[j+1];
			A[k][i] = 0;
			//print(A,b,X);
		}
		//改变j
		++j;
		//判断是否所有的式子都用过了
		if(j == A.row()-2){
			break;
		}
	}
	//回代并归一
	//这次以i代表行
	for(int i=j+1;i>0;--i){
		//k代表主元列
		int k = i;
		while(k<A.col() && A[i][k]==0){
			++k;
		}
		//归一
		double t = 1/A[i][k];
		A.trans_row(i,t);
		A[i][k] = 1;
		//右端向量做相同的事情
		b[i] *= t;
		//print(A,b,X);
		//回代
		for(j=i-1;j>=0;--j){
			double tmp = -A[j][k];
			A.trans_row(i,j,tmp);
			A[j][k] = 0;
			//右端向量做相同的事情
			b[j] += b[i]*tmp;
			//print(A,b,X);
		}
	}
	//第一行归一
	double t = 1/A[0][0];
	A.trans_row(0,t);
	A[0][0] = 1;
	b[0] *= t;
	//print(A,b,X);
	//接下来判断是否无解
	//如果右端向量的相应位置的数字不为0，且A在这一行的数字全为0，那么无解
	for(int i=0;i<A.row();++i){
		if(b[i]!=0){
			bool is_zero = true;
			for(int k=0;k<A.col();++k){
				if(A[i][k]!=0){
					is_zero = false;
				}
			}
			//如果无解，返回一个0*0的矩阵
			if(is_zero){
				return Mat();
			}
		}
	}
	//有解，计算解
	j = -1;
	//这次i继续代表列，也就是X的分量
	for(int i=0;i<A.row();++i){
		//如果对应位置是0，那么代表这个元是个自由未知量
		if(A[i][j+1]==0){
			//对应位置上扣1
			X[i][i] = 1;
			//print(A,b,X);
			continue;
		}
		//如果不是自由未知量，将其组成填入
		//填入常向量的值
		X[i][X.col()-1] = b[i];
		//print(A,b,X);
		//填入自由未知量向量系数
		for(int k=i+1;k<A.row();++k){
			X[i][k] = -A[i][k];
			//print(A,b,X);
		}
		//计算完成后，行迭代
		++j;
	}
	//返回
	return X;
}

void print(Mat A, std::vector<double> b, Mat X){
	std::cout << "增广矩阵：" << std::endl;
	for(int i=0;i<A.row();++i){
		for(int j=0;j<A.col();++j){
			std::cout << A[i][j] << "\t\t";
		}
		std::cout << b[i] << std::endl;
	}
	std::cout << "结果：" << std::endl;
	std::cout << X << std::endl;
}

//测试
int main(){
	//构造一个矩阵
	Mat A = {{1,2,1,4},{2,0,4,3},{4,2,2,1},{-3,1,3,2}};
	//构造右端向量
	std::vector<double> b = {13,28,20,6};
	//运算
	Mat X = Gauss(A,b);
	//打印
	std::cout << X << std::endl;
	return 0;
}
