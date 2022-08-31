#include<iostream>
#include<boost/timer.hpp>

int main(){
	//接下来测试timer的两个功能,这两个功能可以帮助程序员使用timer
	boost::timer t;
	//1、最小测量单位
	std::cout<<t.elapsed_min()<<std::endl;
	//2、最大可测量的时间
	std::cout<<t.elapsed_max()<<std::endl;
	return 0;
}
