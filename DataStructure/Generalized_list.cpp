#include<iostream>
#include<vector>



struct node_base {
};

template<typename _Ty>
struct node_child: public node_base
{
	node_child(_Ty v):value(v) {

	}
	using value_type = _Ty;
	value_type value;
};

struct node {
	template<typename _Ty>
	node(_Ty arg) {
		val = new node_child<_Ty>(arg);
	}
	template<typename _Ty>
	_Ty& get() {
		return dynamic_cast<node_child<_Ty>>(val)->value;
	}
	node_base* val;

};

template<typename Container = std::vector<node>>
class Generalized_list : node_base
{
public:
	template<class ... Args>
	Generalized_list(Args&&... args) {
		container = new Container(std::forward<_Args>(__args)...);
	}
	Container* operator->() {
		return container;
	}
private:
	Container* container;
};

int main() {
	Generalized_list<> l;
	l->emplace_back(1);
	return 0;
}