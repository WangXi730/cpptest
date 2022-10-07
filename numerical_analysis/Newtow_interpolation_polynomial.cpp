#include<iostream>
#include<vector>
#include<cmath>
#include"Mat.hpp"


std::vector<double> Newtow_interpolation_polynomial(Mat P){
	int m = P.row();
	//m为样本数量
	//定义差商表
	Mat csb(m,m+1);
	for(int i=0;i<csb.row();++i){
		csb[i][0] = P[i][0];
		csb[i][1] = P[i][1];
	}
	for(int i=2;i<m+1;++i){
		for(int j=i-1;j<m;++j){
    		csb[j][i] = (csb[j][i-1]-csb[j-1][i-1])/(csb[j][0]-csb[j-(i-2)-1][0]);
        }
    }

	//接下来使用相同的方法，记录结果
	std::vector<double> a(m,0.0);
	a[0] = P[0][1];
	for(int i=2;i<m+1;++i){
		double k = pow(2,i-1)-1;
    	double ci = csb[i-1][i];
    	for(int j=0;j<=k;++j){
    		int kj = j;
        	double tmp = 1;
        	int ki = 0;
        	int ni = 0;
        	while(kj){
        		ki = ki + 1;
            	if(ki%2){
            		if(ki<=i){
						tmp = tmp*(-P[ki-1][0]);
                    	ni = ni+1;
                    }
                	else{
                    	tmp = tmp*(-P[ki][0]);                   	
                    	ni = ni+1;
                	}
            	}
            	kj = kj/2;//整除2作为下一次迭代的数字
        	}
        	a[m-ni-1] = a[m-ni-1]+tmp*ci;
    	}
	}
	return a;
}


int main(){
	Mat P1 = {{M_PI/6,0.5},{M_PI/4,0.7071}};
	std::vector<double> res = Newtow_interpolation_polynomial(P1);
	for(double&i:res){
		std::cout << i << std::endl;
	}
	return 0;
}
