#include<iostream>

//抽象工厂模式
//游戏关卡模型
//假设一个游戏设有两个关卡：简单（A），困难（B）
//A难度的关卡只能有A难度的怪，B以此类推，但有些怪的种类是一样的


//怪1
//类摘要
//父类怪
class monster1 {
public:
	virtual ~monster1() = 0;
protected:
	monster1();
};
//A难度
class monster1_A : public monster1 {
public:
	monster1_A();
	~monster1_A();
};
//B难度
class monster1_B : public monster1 {
public:
	monster1_B();
	~monster1_B();
};
//方法实现
monster1::monster1() {}
monster1::~monster1() {}
monster1_A::monster1_A() {
	std::cout << "A难度，类型1，正在生成..." << std::endl;
}
monster1_A::~monster1_A(){}
monster1_B::monster1_B() {
	std::cout << "B难度，类型1，正在生成..." << std::endl;
}
monster1_B::~monster1_B() {}
//怪2
//类摘要
//父类怪
class monster2 {
public:
	virtual ~monster2() = 0;
protected:
	monster2();
};
//A难度
class monster2_A : public monster2 {
public:
	monster2_A();
	~monster2_A();
};
//B难度
class monster2_B : public monster2 {
public:
	monster2_B();
	~monster2_B();
};
//方法实现
monster2::monster2() {}
monster2::~monster2() {}
monster2_A::monster2_A() {
	std::cout << "A难度，类型2，正在生成..." << std::endl;
}
monster2_A::~monster2_A() {}
monster2_B::monster2_B() {
	std::cout << "B难度，类型2，正在生成..." << std::endl;
}
monster2_B::~monster2_B() {}

//工厂类
//类摘要
//基类
class factory {
public:
	factory();
	virtual ~factory() = 0;
	virtual monster1* create_monster1() = 0;
	virtual monster2* create_monster2() = 0;
};
//关卡工厂
class A_factory : public factory {
public:
	A_factory();
	~A_factory();
	monster1* create_monster1();
	monster2* create_monster2();
};
class B_factory : public factory {
public:
	B_factory();
	~B_factory();
	monster1* create_monster1();
	monster2* create_monster2();
};
//方法实现
factory::factory(){}
factory::~factory(){}
monster1* factory::create_monster1() { return nullptr; }
monster2* factory::create_monster2() { return nullptr; }
A_factory::A_factory(){}
A_factory::~A_factory(){}
monster1* A_factory::create_monster1() { return new monster1_A(); }
monster2* A_factory::create_monster2() { return new monster2_A(); }
B_factory::B_factory() {}
B_factory::~B_factory() {}
monster1* B_factory::create_monster1() { return new monster1_B(); }
monster2* B_factory::create_monster2() { return new monster2_B(); }


int main() {
	A_factory a;
	B_factory b;
	monster1* ma1 = a.create_monster1();
	monster2* ma2 = a.create_monster2();
	monster1* mb1 = b.create_monster1();
	monster2* mb2 = b.create_monster2();
	delete ma1;
	delete ma2;
	delete mb1;
	delete mb2;
	return 0;
}
