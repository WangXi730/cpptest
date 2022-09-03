#include<iostream>
#include<boost/date_time.hpp>
#include<string>

int main(){
	//访问日期
	//1、创建date对象，并赋予日期
	boost::gregorian::date d1(2022,9,3);
	//2、创建ymd_type对象
	boost::gregorian::date::ymd_type vd1 = d1.year_month_day();
	//试图转化成mysql的日期类型的格式输入到流
	std::cout << vd1.year << "-" << (int)vd1.month << "-" << vd1.day << std::endl;
	int y = vd1.year;
	int m = vd1.month;
	int d = vd1.day;
	std::cout << y << "-" << m << "-" << d << std::endl;
	//使用接口转换
	std::cout << boost::gregorian::to_iso_extended_string(d1) << std::endl;

	return 0;
}
