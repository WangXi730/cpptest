#include<iostream>
#include<boost/date_time.hpp>

//时间段的使用

int main(){
	boost::gregorian::date d1(2000,2,29);
	std::cout << d1 << "星期" << d1.day_of_week() << std::endl;
	d1 += boost::gregorian::years(18);
	std::cout << d1 << "星期" << d1.day_of_week() << std::endl;	
	return 0;
}
