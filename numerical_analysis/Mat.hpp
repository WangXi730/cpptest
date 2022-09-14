#include<iostream>
#include<vector>
#include<cstdlib>
#include<cmath>

//矩阵类摘要
class Mat{
//构造方法
public:
	//空构造方法
	Mat();
	//构造一个m行n列全0矩阵
	Mat(int m, int n);
	//构造一个n阶全0矩阵
	Mat(int n);
	//使用向量类型构造矩阵
	Mat(std::vector<std::vector<double>>& m);
	//拷贝构造
	Mat(const Mat& cp);
//变换方法,transformation系列函数
public:
	//行变换：第i行乘k加到第j行
	void trans_row(int i, int j, double k);
	//列变换：第i列乘k加到第j列
	void trans_col(int i, int j, double k);
	//行变换：第i行乘k
	void trans_row(int i, double k);
	//列变换：第i行乘k
	void trans_col(int i, double k);
	//行变换：交换i、j两行
	void trans_row(int i, int j);
	//列变换：交换i、j两列
	void trans_col(int i, int j);
	//矩阵的转置
	Mat trans();
	//矩阵转置操作
	Mat& be_trans();
//矩阵运算
public:
	//矩阵加法
	Mat operator+(Mat& m);
	Mat& operator+=(Mat& m);
	//矩阵乘法
	Mat operator*(Mat& m);
	Mat& operator*=(Mat& m);
	//矩阵数乘
	Mat operator*(double k);
	Mat& operator*=(double k);
	//矩阵乘向量，如果是方阵，默认v为列向量
	std::vector<double> operator*(std::vector<double>& v);
	//矩阵除法（乘逆）
	Mat operator/(Mat& m);
	Mat& operator/=(Mat& m);
	//矩阵求逆
	Mat inv();
	//矩阵变乘逆
	Mat& be_inv();
	//矩阵的行列式
	operator double();
	//矩阵的Doolittle三角分解
	void Doolittle(Mat& L,Mat& U);
public:
//访问操作，返回第i行
	std::vector<double>& operator[](int i);
//访问行列
	int row();
	int col();
	void swap(Mat& m);
//打印矩阵
	friend std::ostream&  operator <<(std::ostream& out, Mat& c);
private:
	//成员变量mat，存放矩阵
	std::vector<std::vector<double>> _mat;
};

//构造方法
//空构造
Mat::Mat(){}
//n阶矩阵
Mat::Mat(int n):_mat(n, std::vector<double>(n,0.0))
{}
//m行n列矩阵
Mat::Mat(int m,int n):_mat(m, std::vector<double>(n,0.0)){}
//使用向量类型构造矩阵
Mat::Mat(std::vector<std::vector<double>>& m){
	int col = m[0].size();
	for(auto &v:m){
		if(v.size()>col){
			col = v.size();
		}
	}
	//拷贝
	_mat = std::vector<std::vector<double>>(m.size(),std::vector<double>(col,0.0));
	int i = 0;
	for(auto &v:m){
		for(int j=0;j<v.size();++j){
			_mat[i][j] = v[j];
		}
		++i;
	}
}
//拷贝构造	
Mat::Mat(const Mat& cp){
	_mat = cp._mat;
}

//变换方法
//行变换：第i行乘k加到第j行
void Mat::trans_row(int i, int j, double k){
	for(int it=0;it<col();++it){
		_mat[j][it] += _mat[i][it]*k;
	}
}
//列变换：第i列乘k加到第j列
void Mat::trans_col(int i, int j, double k){
	for(int it=0;it<row();++it){
		_mat[it][j] += _mat[it][i]*k;
	}
}
//行变换：第i行乘k
void Mat::trans_row(int i, double k){
	for(int it=0;it<col();++it){
		_mat[i][it] *= k;
	}
}
//列变换：第i列乘k
void Mat::trans_col(int i, double k){
	for(int it=0;it<row();++it){
		_mat[it][i] *= k;
	}
}
//行变换：交换i、j两行
void Mat::trans_row(int i, int j){
	//调用std::vector::swap即可
	_mat[i].swap(_mat[j]);
}
//列变换：交换i、j两列
void Mat::trans_col(int i, int j){
	//逐一交换
	for(int k=0;k<row();++k){
		//交换三连
		double tmp = _mat[k][i];
		_mat[k][i] = _mat[k][j];
		_mat[k][j] = tmp;
	}
}
//矩阵的转置
Mat Mat::trans(){
	Mat res(col(),row());
	for(int i=0;i<col();++i){
		for(int j=0;j<row();++j){
			res[i][j] = _mat[j][i];
		}
	}
	return res;
}
//矩阵转置操作
Mat& Mat::be_trans(){
	Mat m = trans();
	swap(m);
	return *this;
}

//矩阵运算
//矩阵加法
Mat Mat::operator+(Mat& m){
	Mat res(row(),col());
	for(int i=0;i<row();++i){
		for(int j=0;j<col();++j){
			res[i][j] = _mat[i][j] + m[i][j];
		}
	}
	return res;
}
Mat& Mat::operator+=(Mat& m){
	for(int i=0;i<row();++i){
		for(int j=0;j<col();++j){
			_mat[i][j] += m[i][j];
		}
	}
}
//矩阵乘法
Mat Mat::operator*(Mat& m){
	Mat res(row(),m.col());
	for(int i=0;i<row();++i){
		for(int j=0;j<m.col();++j){
			//每一行对应每一列
			for(int k=0;k<col();++k){
				res[i][j] += _mat[i][k] * m[k][j];
			}
		}
	}
	return res;
}
Mat& Mat::operator*=(Mat& m){	
	Mat tmp = (*this)*m;
	swap(tmp);
	return *this;
}
//矩阵数乘
Mat Mat::operator*(double k){
	Mat res(row(),col());
	for(int i=0;i<row();++i){
		for(int j=0;j<col();++j){
			res[i][j] *= k;
		}
	}
	return res;
}
Mat& Mat::operator*=(double k){
	for(int i=0;i<row();++i){
		for(int j=0;j<col();++j){
			_mat[i][j] *= k;
		}
	}
}
//矩阵乘向量，如果是方阵，默认v为列向量
std::vector<double> Mat::operator*(std::vector<double>& v){
	if(v.size()==col()){
		std::vector<double> res(row(),0.0);
		for(int i=0;i<row();++i){
			for(int j=0;j<col();++j){
				res[i] += (_mat[i][j]*v[j]);
			}
		}
		return res;
	}
	else{
		std::vector<double> res(col(),0.0);
		for(int i=0;i<col();++i){
			for(int j=0;j<row();++j){
				res[i] += (_mat[j][i]*v[j]);
			}
		}
		return res;
	}
	return std::vector<double>();
}
//矩阵除法（乘逆）
Mat Mat::operator/(Mat& m){
	return (*this)*m.inv();
}
Mat& Mat::operator/=(Mat& m){
	Mat res = (*this)/m;
	swap(res);
	return (*this);
}
//矩阵求逆
Mat Mat::inv(){
	//矩阵乘自己的逆，结果是一个单位矩阵
	//逆是一个n阶矩阵
	Mat res(row());
	//使用Doolittle三角分解求逆
	Mat L;
	Mat U;
	Doolittle(L,U);
	//接下来套公式，无论是y，还是x都存放在res中
	for(int it=0;it<col();++it){
		//右端向量b
		std::vector<double> b(row(),0.0);
		b[it] = 1.0;
		//构造y
		std::vector<double> y(row(),0.0);
		y[0] = b[0];
		for(int k=1;k<row();++k){
			y[k] = b[k];
			for(int i=0;i<k;++i){
				y[k] -= L[k][i]*y[i];
			}
		}
		//构造x
		res[it][row()-1] = y[row()-1]/U[row()-1][row()-1];
		for(int i=row()-2;i>=0;--i){
			res[it][i] = y[i];
			for(int j=i+1;j<row();++j){
				res[it][i] -= U[i][j]*res[it][j];
			}
			res[it][i] /= U[i][i];
		}
	}
	return res;
}
//矩阵变乘逆
Mat& Mat::be_inv(){
	Mat tmp = inv();
	swap(tmp);
	return (*this);
}
//矩阵Doolittle分解
void Mat::Doolittle(Mat& L, Mat& U){
	L = Mat(row(),col());
	U = Mat(row(),col());
	for(int i=0;i<col();++i){
		U[0][i] = _mat[0][i];
		L[i][i] = 1.0;
		L[i][0] = _mat[i][0] / U[0][0];
	}
	for(int k=1;k<row();++k){
		for(int j=k;j<row();++j){
			U[k][j] = _mat[k][j];
			for(int m=0;m<k;++m){
				U[k][j] -= L[k][m]*U[m][j];
			}
		}
		for(int i=k+1;i<row();++i){
			L[i][k] = _mat[i][k];	
			for(int m=0;m<k;++m){
				L[i][k] -= L[i][m]*U[m][k];
			}
			L[i][k] /= U[k][k];
		}
	}
}
//求行列式
Mat::operator double(){	
	//首先复制一个等价矩阵，以此来保证原矩阵不改变
	Mat m = (*this);
	//通过列主元变换，将矩阵变成下三角矩阵
	for(int i=0;i<row();++i){
		//找到最大列主元
		double max_mem = std::fabs(m[i][i]);
		int mem_addr = i;
		for(int j=i+1;j<row();++j){
			if(std::fabs(m[j][i])>max_mem){
				max_mem = std::fabs(m[j][i]);
				mem_addr = j;
			}
		}
		//最终找到了最大列主元，如果是0，那么直接返回0
		if(max_mem == 0.0){
			return 0.0;
		}
		//如果不是0，那么交换列主元的位置
		if(mem_addr != i){
			trans_row(mem_addr,i);
		}
		//之后消元
		for(int j=i+1;j<row();++j){
			//求出行变换的倍数
			double k = -m[j][i]/m[i][i];
			//行变换
			trans_row(i,j,k);
		}
	}
	//主元相乘即为结果
	double res = m[0][0];
	for(int i=1;i<row();++i){
		res *= m[i][i];
	}
	return res;
}
//访问操作，返回第i行
std::vector<double>& Mat::operator[](int i){
	return _mat[i];
}
//访问行列
int Mat::row(){
	return _mat.size();
}
int Mat::col(){
	return _mat[0].size();
}
void Mat::swap(Mat& m){
	_mat.swap(m._mat);
}
//通过流输出矩阵
std::ostream&  operator <<(std::ostream& out, Mat& c){
	for(int i=0;i<c.row();++i){
		for(int j=0;j<c.col();++j){
			//同一行相邻的元素使用制表符隔开
			out << c[i][j] << "\t";
		}
		//每一行隔开
		out << std::endl;
	}
	return out;
}
