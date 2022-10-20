#include<iostream>
#include<stddef.h>
//工厂模式练习
//抽象类
class Base {
public:
	virtual ~Base() = 0;
protected:
	Base(){}
};
Base::~Base() {

}
//具体类
//子类1
class Concrete_1 : public Base {
public:
	~Concrete_1(){
		std::cout << "子类1" << std::endl;
	}
	Concrete_1() {}
};
//子类2
class Concrete_2 : public Base {
public:
	~Concrete_2() {
		std::cout << "子类2" << std::endl;
	}
	Concrete_2(){}
};
//工厂抽象类
class Factory {
public:
	virtual Base* create() = 0;
	virtual ~Factory() = 0;
protected:
	Factory() {}
};
Factory::~Factory() {

}
//工厂子类
class Concrete1_Factory : public Factory{
public:
	Base* create() {
		return new Concrete_1();
	}
	Concrete1_Factory() {}
};
class Concrete2_Factory : public Factory {
public:
	Base* create() {
		return new Concrete_2();
	}
	Concrete2_Factory() {}
};



int main() {
	return 0;
}

