#include<iostream>
#include<boost/date_time.hpp>

//ptime的练习使用

int main(){
	//创建ptime对象
	//使用date对象和time_duration对象创建
	boost::posix_time::ptime pt1(boost::gregorian::date(2022,9,4),boost::posix_time::hours(13)+boost::posix_time::minutes(5));
	std::cout << "使用date对象和time_duration对象创建ptime：" << pt1 << std::endl;
	//使用时钟构造当前时间(北京时间)
	boost::posix_time::ptime pt2 = boost::posix_time::second_clock::universal_time() +boost::posix_time::hours(8);
	std::cout << "使用时钟构造当前时间（北京时间）的ptime对象：" << pt2 << std::endl;
	//使用string创建对象
	boost::posix_time::ptime pt3 = boost::posix_time::time_from_string("2022-9-4 13:09:00");
	std::cout << "使用sting创建的对象：" << pt3 << std::endl;
	return 0;
}
