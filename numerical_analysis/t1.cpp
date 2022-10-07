#include<iostream>
#include<assert.h>
#include"Mat.hpp"
double _junzhi(Mat& m,int i,int j,int b);

//默认3*3边框大小
Mat junzhilvbo(Mat& m, int r=3){
	assert(r%2==1);
	assert(m.row()>r);
	assert(m.col()>r);
	int b = r/2;
	Mat res(m.row()-b*2,m.col()-b*2);
	for(int i=b;i<=m.row()-b-1;++i){
		//i是行迭代变量
		for(int j=b;j<=m.col()-b-1;++j){
			//j是列迭代变量
			//求均值
			res[i-b][j-b] = _junzhi(m,i,j,b);
		}
	}
	return res;
}

//计算一个点附近的均值
double _junzhi(Mat& m, int i, int j, int b){
	double res = 0;
	int count = 0;
	for(int it=i-b;it<=i+b;++it){
		for(int it2=j-b;it2<=j+b;++it2){
			res += m[it][it2];
			count+=1;
		}
	}
	return res/count;
}

int main(){
	Mat f = {{59,60,58,57},{61,90,59,57},{62,59,0,58},{59,61,60,56}};
	Mat res = junzhilvbo(f);
	std::cout << res << std::endl;
	return 0;
}
