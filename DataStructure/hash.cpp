#include<iostream>
#include<vector>
#include<list>
using namespace std;


enum state {nil,del,used};
template<class Type>
class Hash_1;
template<class Type>
class Hash_node1 {
public:
	friend class Hash_1<Type>;
	//���췽��
	Hash_node1():data(Type()),s(nil) {}
	Hash_node1(Type val):data(val),s(used){}
private:
	Type data;
	state s;
};

//��ɢ�з������Ŷ�ַ����
template<class Type>
class Hash_1 {
public:
	//���췽��
	Hash_1() : _hash(10) ,_capacity(10) {}
	Hash_1(size_t size) : _hash(size),_capacity(size){}
	
	//���뷽����ʹ�ó���������������̽�ⷨ
	bool push(Type val) {
		size_t key =  % _capacity;
		//�ж��Ƿ���Ҫ����
		if (_size >= (_capacity * 7 / 10)) {
			reserve(3*_capacity);//�趨ÿ����������
		}
		//�鿴�Ƿ��п�
		while (hash[key].s != used) {
			key += 1;
			key %= _capacity;
		}
		//���ڵ�key��λ�þ�����Ҫ�洢��λ��
		_hash[key].s = used;
		_hash[key].data = val;
		size += 1;
		return true;
	}
	//����Ԫ��
	bool pop(Type val) {
		size_t key = find(val);
		if (key == -1)
			return false;
		--_size;
		_hash[key].s = del;
		return true;
	}
	//����Ԫ��
	size_t find(Type val) {
		size_t key = ;
		size_t k2 = (key + _capacity - 1) % _capacity;
		while (_hash[key].s == nil || _hash[key].data == val) {
			if (k2 == key)
				return -1;
			key += 1;
			key %= _capacity;
		}
		if (_hash[key].s == nil) {
			return -1;
		}
		return key;
	}
	//Ԫ�ظ���
	size_t size() {
		return _size;
	}
	//�жϿ�
	bool empty() {
		return _size == 0;
	}
	//Ԥ������
	bool reserve(size_t size) {
		//����һ����ϣ��
		Hash_1<Type> has(size);
		//�����е�Ԫ�ض������������
		for (auto& e : _hash) {
			if (e.s == used) {
				has.push(e.data);
			}
		}
		//����������ϣ��
		swap(has);
		return true;
	}
	//������ϣ��
	void swap(Hash_1& has) {
		//��������
		size_t tmp = has._size;
		has._size = _size;
		_size = tmp;
		tmp = _capacity;
		_capacity = has._capacity;
		has._capacity = tmp;
		//��������������
		_hash.swap(has._hash);
	}
private:
	size_t _size = 0;
	size_t _capacity;
	vector<Hash_node1<Type>> _hash;
};


int main() {

	return 0;
}