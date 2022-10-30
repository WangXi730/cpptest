#include<iostream>
#include<mutex>
using namespace std;

//����ģʽ���ȳ�ʼ����ϣ��ռ任ʱ��
class Singleton1 {
public:
	//��ȡʵ������
	static Singleton1* getinstance() {
		return &_eton;
	}
	//���ÿ������췽��
	Singleton1(Singleton1& e) = delete;
	//��ӡ����(�÷����Ǳ�Ҫ)
	void print() {
		cout << data << endl;
	}
private:
	//�ڲ�ʵ�����Լ���ͨ���ؼ���static��֤�ڳ�������֮���ͳ�ʼ��
	static Singleton1 _eton;
	//����(����Ϊ����)
	int data;
	//���췽��˽�л�����֤�ⲿ�޷�ʵ��������
	Singleton1(int a):data(a) {}
};

//��ʼ����̬��Ա����
Singleton1 Singleton1::_eton(1);

//����ģʽ���ӳټ���
class Singleton2 {
public:
	//Ϊ�������ⲿ���ã�ʹ�þ�̬����
	static Singleton2* getinstance() {
		//ʵ��������
		//Ϊ�����Ч�ʣ�����double check
		if (_eton == nullptr) {
			_mutex.lock();
			if (_eton == nullptr)_eton = new Singleton2(2);
			_mutex.unlock();
		}
		//���س�Աָ��
		return _eton;
	}
	void print() {
		cout << data << endl;
	}
private:
	//��Ա����ָ�뻯����֤�õ�ʱ��Ż����
	//������getinstance�з�������_eton��Ϊ�˱�������Ż�����Ĭ��_eton == nullptr���ӹؼ���volatile
	static Singleton2* _eton;
	//����(����Ϊ����)
	int data;
	//���췽��˽�л�����֤�ⲿ�޷�ʵ��������
	Singleton2(int a) :data(a){}
	//��������
	static mutex _mutex;
};

//��ʼ����̬��Ա����
Singleton2* Singleton2::_eton = nullptr;
mutex Singleton2::_mutex;

int main() {
	Singleton1* p1 = Singleton1::getinstance();
	p1->print();
	Singleton2* p2 = Singleton2::getinstance();
	p2->print();
	return 0;
}