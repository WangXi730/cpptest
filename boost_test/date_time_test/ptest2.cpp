#include<iostream>
#include<boost/date_time.hpp>
#include<unistd.h>


//实现一个高精度计时器
template<class Clock = boost::posix_time::microsec_clock>
class my_clock{
public:
	//从实例化对象后的第seconds秒后开始计时
	my_clock(int seconds = 0):_later(seconds){
		_clock = Clock::universal_time();
	}
	//重新开始
	bool re_start(){
		_clock = Clock::universal_time();
	}
	//重载输出
	template<class type>
	friend std::ostream& operator<<(std::ostream& ostr, my_clock<type>& t);
	//析构
	~my_clock(){
		std::cout << (Clock::universal_time()  - _clock) << std::endl;
	}
private:
	boost::posix_time::ptime _clock;
	int _later;
};

template<class type>
std::ostream& operator<<(std::ostream& ostr, my_clock<type>&t){
	ostr << (type::universal_time() - t._clock);
	return ostr;
}

int main(){
	my_clock<> a_clock;
	sleep(5);
	std::cout << a_clock << std::endl;
	sleep(5);
	return 0;
}
