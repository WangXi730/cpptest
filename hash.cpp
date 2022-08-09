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
	//构造方法
	Hash_node1():data(Type()),s(nil) {}
	Hash_node1(Type val):data(val),s(used){}
private:
	Type data;
	state s;
};

//闭散列法（开放定址法）
template<class Type>
class Hash_1 {
public:
	//构造方法
	Hash_1() : _hash(10) ,_capacity(10) {}
	Hash_1(size_t size) : _hash(size),_capacity(size){}
	
	//插入方法，使用除留余数法、线性探测法
	bool push(Type val) {
		size_t key =  % _capacity;
		//判断是否需要扩容
		if (_size >= (_capacity * 7 / 10)) {
			reserve(3*_capacity);//设定每次扩大三倍
		}
		//查看是否有空
		while (hash[key].s != used) {
			key += 1;
			key %= _capacity;
		}
		//现在的key的位置就是需要存储的位置
		_hash[key].s = used;
		_hash[key].data = val;
		size += 1;
		return true;
	}
	//弹出元素
	bool pop(Type val) {
		size_t key = find(val);
		if (key == -1)
			return false;
		--_size;
		_hash[key].s = del;
		return true;
	}
	//查找元素
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
	//元素个数
	size_t size() {
		return _size;
	}
	//判断空
	bool empty() {
		return _size == 0;
	}
	//预设容量
	bool reserve(size_t size) {
		//创建一个哈希表
		Hash_1<Type> has(size);
		//将所有的元素都插入这个表中
		for (auto& e : _hash) {
			if (e.s == used) {
				has.push(e.data);
			}
		}
		//交换两个哈希表
		swap(has);
		return true;
	}
	//交换哈希表
	void swap(Hash_1& has) {
		//交换参数
		size_t tmp = has._size;
		has._size = _size;
		_size = tmp;
		tmp = _capacity;
		_capacity = has._capacity;
		has._capacity = tmp;
		//交换容器适配器
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