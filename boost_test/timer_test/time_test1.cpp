#include<iostream>
#include<boost/timer.hpp>
#include<unistd.h>


int main(){
	boost::timer t;
	double pret = 0.0;
	//首次测试timer的基本功能：计时	
	while(1){
		//if(pret+1<=t.elapsed()){
		//	pret = t.elapsed();
		//	std::cout<<	pret<<std::endl;
		//}
		printf("%7lf\n",t.elapsed());
	}
	return 0;
}

