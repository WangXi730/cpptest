#include<iostream>
#include<vector>
#include"Mat.hpp"

//牛顿下山法解非线性方程组
template<class function1_t, class function2_t>
std::vector<double> Newtow(std::vector<double> &x0, double e, function1_t F, function2_t J){
	//牛顿方法解非线性方程组
	//初始值x(0)
	Mat x(1,x0.size());
	x[0] = x0;
	// m恒为1，n为维度
	//开始迭代
	int i = 0;
	while(1){
		std::vector<double> xi;
		xi = (J(x[i]).inv() * F(x[i]).trans()).trans()[0];
		for (int j = 0; j < x[i].size(); ++j) {
			xi[j] = x[i][j] - xi[j];
		}
   	    x.push_row(xi);
    	i += 1;
	    //判断误差是否小于0.001
    	Mat f = F(x[i]);
	    for(int j=0;j<x0.size();++j){
    	    std::vector<double> ev(x0.size(),0.0);
        	ev[j] = e;
			std::vector<double> tmp = x[i];	
			for(int it=0;it<tmp.size();++it){
				tmp[it] = ev[j];
			}
	        Mat fj = F(tmp);
    	    int ee = 1;
			for(int k=0;k<x0.size();++k){
        	    if(fj[0][k]*f[0][k]<0){
            	    ee = 0;
                	break;
	            }
    	    }
        	if(ee){
            	return x[i];
	        }
    	    ev[j] = -e;
			tmp = x[i];	
			for(int it=0;it<tmp.size();++it){
				tmp[it] = ev[j];
			}
	        fj = F(tmp);
			for(int k=0;k<x0.size();++k){
    	        if(fj[0][k]*f[0][k]<0){
        	        ee = 0;
            	    break;
	            }
    	    }
	        if(ee){
    	        return x[i];
        	}
	    }
	}
	return std::vector<double>();
}

Mat F(std::vector<double>& x){
	Mat y(1,2);
	y[0][0] = x[0]*x[0] - 2*x[0] - x[1] + 0.5;
	y[0][1] = x[0]*x[0] + 4*x[1]*x[1] - 4;
	return y;
}

Mat J(std::vector<double>& x){
	Mat y(2,2);
	// 雅可比矩阵
	y[0][0] = 2*x[0] - 2;
	y[0][1] = -1;
	y[1][0] = 2*x[0];
	y[1][1] = 8*x[1];
	return y;
}

//测试
int main(){
	std::vector<double> P0 = {2,0.25};
	std::vector<double> P = Newtow(P0,0.001,F,J);
	Mat p(1,P.size());
	p[0] = P;
	std::cout << p << std::endl;
	return 0;
}
