#include<iostream>
#include"Mat.hpp"

//测试所有功能
int main(){
	//构造2阶全0矩阵
	Mat zeromat(2);
	std::cout << zeromat << std::endl;
	//构造2行3列全0矩阵
	Mat zeromat2(2,3);
	std::cout << zeromat2 << std::endl;
	//通过一个二维数组构造
	std::vector<std::vector<double>> v {{1,0,0},{0,1,0},{0,0,1}};
	Mat mat1(v);
	std::cout << mat1 << std::endl;
	//拷贝构造
	Mat mat1cp = mat1;
	std::cout << "拷贝构造单位阵：" << std::endl;
	std::cout << mat1cp << std::endl;
	//列表构造
	Mat mat1list = {{1,0,0},{0,1,0},{0,0,1}};
	std::cout << "列表构造单位阵：" << std::endl;
	std::cout << mat1list << std::endl;
	//变换
	std::cout << "行变换：第1行乘3加到第2行" << std::endl;
	mat1.trans_row(1,2,3.0);
	std::cout << mat1 << std::endl;
	std::cout << "列变换：第1列乘3加到第2列" << std::endl;
	mat1.trans_col(1,2,3.0);
	std::cout << mat1 << std::endl;
	std::cout << "行变换：第1行乘2" << std::endl;
	mat1.trans_row(1,2.0);
	std::cout << mat1 << std::endl;
	std::cout << "列变换：第1列乘2" << std::endl;
	mat1.trans_col(1,2.0);
	std::cout << mat1 << std::endl;
	std::cout << "行变换：交换1、2两行" << std::endl;
	mat1.trans_row(1,2);
	std::cout << mat1 << std::endl;
	std::cout << "列变换：交换1、2两列" << std::endl;
	mat1.trans_col(1,2);
	std::cout << mat1 << std::endl;
	//这个矩阵的逆
	std::cout << "这个矩阵的逆" << std::endl;
	Mat i = mat1.inv();
	std::cout << i << std::endl;
	std::cout << "乘自己的逆为单位阵" <<std::endl;
	i *= mat1;
	std::cout << i << std::endl;
	//行列式
	double val = mat1;
	std::cout << "这个矩阵行列式的值：" << std::endl;
	std::cout << val <<std::endl;
	std::vector<std::vector<double>> v2{{1,2,3},{4,5,6},{7,8,9}};
	std::cout << "矩阵：" << std::endl;
	Mat mat2(v2);
	std::cout << mat2 << std::endl;
	//转置
	std::cout << "的转置为" <<std::endl;
	Mat mat2t = mat2.trans();
	std::cout << mat2t << std::endl;
	//矩阵加法
	std::cout << "这个矩阵加上单位矩阵为：" << std::endl;
	mat2 += mat1cp;
	std::cout << mat2 << std::endl;
	//数乘
	std::cout << "数乘5：" << std::endl;
	mat2 *= 5;
	std::cout << mat2 << std::endl;
	//矩阵乘法
	mat2 *= mat1;
	std::cout << "两矩阵相乘" << std::endl;
	std::cout << mat2 << std::endl;
	return 0;	
}
