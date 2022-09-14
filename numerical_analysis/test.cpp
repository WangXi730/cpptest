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
	//这个矩阵的逆
	std::cout << "这个矩阵的逆" << std::endl;
	Mat i = mat1.inv();
	std::cout << i << std::endl;
	//这个矩阵的行列式的值
	double val = mat1;
	std::cout << "这个矩阵行列式的值：" << std::endl;
	std::cout << val <<std::endl;
	std::vector<std::vector<double>> v2{{1,2,3},{4,5,6},{7,8,9}};
	std::cout << "矩阵：" << std::endl;
	Mat mat2(v2);
	std::cout << mat2 << std::endl;
	std::cout << "的转置为" <<std::endl;
	Mat mat2t = mat2.trans();
	std::cout << mat2t << std::endl;
	std::cout << "这个矩阵加上单位矩阵为：" << std::endl;
	mat2 += mat1;
	std::cout << mat2 << std::endl;
	std::cout << "数乘5：" << std::endl;
	mat2 *= 5;
	std::cout << mat2 << std::endl;
	return 0;	
}
