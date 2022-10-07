#include<iostream>
#include<cmath>

template<class function_t>
double bin_func(double inf, double sup, function_t func, double e = 0.00001){
	double a = inf;
	double b = sup;
	if(func(a)>func(b)){
    	double t = a;
	    a = b;
    	b = t;
	}
	double x = (a+b)/2;
	while(fabs(a-b)>e){
	   	x = (a+b)/2;
    	if(func(x)>0)
        	b = x;
	    else
    	    a = x;
   	}
	return x;
}

//测试函数
double f(double x){
	return x*x*x-x-1;
}

int main(){
	std::cout << bin_func(1.0,2.0,f) << std::endl;
	return 0;
}
