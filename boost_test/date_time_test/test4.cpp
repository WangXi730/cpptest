#include<iostream>
#include<boost/date_time.hpp>

using namespace std;

//date_time库简单的程序编写

class Solution{
public:
	//1、计算一个人18岁的生日是星期几
	int first_adult_birthday(int year, int month, int day){
		//构造date对象
		boost::gregorian::date birthday(year,month,day);
		//计算18年之后的日期，如果生日是2月29，视为2月28
		birthday += boost::gregorian::years(18);
		int res = birthday.day_of_week();
		return res;
	}
	//2、计算当月有多少个星期天
	int account_weekends(int year, int month){
		//构造date对象
		boost::gregorian::date d1(year,month,1);
		if(month==12){
			month = 1;
		}
		else{
			month += 1;
		}
		boost::gregorian::date d2(year,month,1);
		//开始计数
		int count = 0;
		while(d1!=d2){
			if(d1.day_of_week()==0){
				++count;
			}
			d1 += boost::gregorian::days(1);
		}
		return count;
	}
	//3、计算这一年有多少天
	int days_of_year(int year){
		//构造date对象
		boost::gregorian::date d1(year,12,31);
		return d1.day_of_year();
	}

};


//测试
int main(){
	Solution test;
	std::cout << test.first_adult_birthday(2002,9,5) << std::endl; 
	std::cout << "2022年9月有" << test.account_weekends(2022,9) << "个星期天" << std::endl;
	std::cout << "2022年有" << test.days_of_year(2022) << "天" << std::endl;
	std::cout << "2020年有" << test.days_of_year(2020) << "天" << std::endl;
	return 0;
}
