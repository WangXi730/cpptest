#include<iostream>
#include<boost/timer.hpp>


int main(){
	boost::timer t;
	while(1){
		//休眠时的t不变
		std::cout<<t.elapsed()<<std::endl;
		sleep(1);
	}
	return 0;
}
