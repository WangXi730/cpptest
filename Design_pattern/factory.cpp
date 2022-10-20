#include<iostream>
#include<stddef.h>
//����ģʽ��ϰ
//������
class Base {
public:
	virtual ~Base() = 0;
protected:
	Base(){}
};
Base::~Base() {

}
//������
//����1
class Concrete_1 : public Base {
public:
	~Concrete_1(){
		std::cout << "����1" << std::endl;
	}
	Concrete_1() {}
};
//����2
class Concrete_2 : public Base {
public:
	~Concrete_2() {
		std::cout << "����2" << std::endl;
	}
	Concrete_2(){}
};
//����������
class Factory {
public:
	virtual Base* create() = 0;
	virtual ~Factory() = 0;
protected:
	Factory() {}
};
Factory::~Factory() {

}
//��������
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

