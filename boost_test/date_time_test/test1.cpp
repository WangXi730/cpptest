#include<iostream>
#include<string>
#include<boost/date_time.hpp>

//练习使用date_time
int main(){
	//空构造函数，生成一个not_available_date_time
	boost::gregorian::date d1;
	std::cout << "无效日期：" << d1 << std::endl;
	//使用时间构造
	boost::gregorian::date d2(2022,9,3);
	boost::gregorian::date d3(2022,boost::gregorian::Sep,3);
	std::cout << "通过时间构造1：" << d2 << std::endl << "通过时间构造2：" << d3 << std::endl;
	//使用工厂类day_clock构造本地日期
	boost::gregorian::date d4 = boost::gregorian::day_clock::local_day();
	std::cout << "通过工厂day_clock构造当地时间：" << d4 << std::endl;
	boost::gregorian::date d5 = boost::gregorian::day_clock::universal_day();
	std::cout << "通过工厂day_clock构造世界时间：" << d5 << std::endl;
	
	return 0;
}

