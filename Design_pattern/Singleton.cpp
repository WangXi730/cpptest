#include<iostream>
#include<mutex>
using namespace std;

//饿汉模式：先初始化完毕，空间换时间
class Singleton1 {
public:
	//获取实例方法
	static Singleton1* getinstance() {
		return &_eton;
	}
	//禁用拷贝构造方法
	Singleton1(Singleton1& e) = delete;
	//打印数据(该方法非必要)
	void print() {
		cout << data << endl;
	}
private:
	//内部实例化自己，通过关键词static保证在程序启动之初就初始化
	static Singleton1 _eton;
	//数据(不必为整型)
	int data;
	//构造方法私有化，保证外部无法实例化对象
	Singleton1(int a):data(a) {}
};

//初始化静态成员变量
Singleton1 Singleton1::_eton(1);

//懒汉模式，延迟加载
class Singleton2 {
public:
	//为了能在外部调用，使用静态方法
	static Singleton2* getinstance() {
		//实例化对象
		//为了提高效率，进行double check
		if (_eton == nullptr) {
			_mutex.lock();
			if (_eton == nullptr)_eton = new Singleton2(2);
			_mutex.unlock();
		}
		//返回成员指针
		return _eton;
	}
	void print() {
		cout << data << endl;
	}
private:
	//成员变量指针化，保证用的时候才会加载
	//由于在getinstance中反复调用_eton，为了避免过度优化导致默认_eton == nullptr，加关键词volatile
	static Singleton2* _eton;
	//数据(不必为整型)
	int data;
	//构造方法私有化，保证外部无法实例化对象
	Singleton2(int a) :data(a){}
	//加锁保护
	static mutex _mutex;
};

//初始化静态成员方法
Singleton2* Singleton2::_eton = nullptr;
mutex Singleton2::_mutex;

int main() {
	Singleton1* p1 = Singleton1::getinstance();
	p1->print();
	Singleton2* p2 = Singleton2::getinstance();
	p2->print();
	return 0;
}