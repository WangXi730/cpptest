#include"LeetCodeTools.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<forward_list>

using TreeNode = wx::TreeNode<int>;


struct A { int a; };
struct B : A
{
	void func() {
		std::cout << this->a;
	}
};



int main() {
	std::string s = "[[[1,3 ,4],[],[2,4,5,4]],[[2,2,3],[1,2,3]]]";
	std::vector<std::vector<std::vector<int>>> sv;
	std::list<std::list<std::list<int>>> sl;
	wx::create(s, sv);
	wx::create(s, sl);
	std::string s1 = "[0,1,2,3,4,5,null,7,8]";
	wx::TreeNode<long double>* root;
	wx::create(s1, root);
	std::vector<wx::SigleListNode<std::list<int>>*> slv;
	wx::create(s, slv);
	wx::SigleListNode<std::vector<std::list<int>>>* vsl = nullptr;
	wx::create(s, vsl);


	std::string s_sv;
	wx::save(s_sv, sv);
	std::string s_sl;
	wx::save(s_sl, sv);
	std::string s1_root;
	wx::save(s1_root, root);
	//
	std::string s_slv;
	wx::save(s_slv, slv);
	std::string s_vsl;
	wx::save(s_vsl, vsl);

	return 0;
}