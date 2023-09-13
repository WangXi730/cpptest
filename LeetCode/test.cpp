#include"LeetCodeTools.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<list>



int main() {
	std::string s = "[[[1,3,4],[2,3,4],[2,4,5,4]],[[2,2,3],[1,2,3]]]";
	std::vector<std::vector<std::vector<int>>> sv;
	std::list<std::list<std::list<int>>> sl;
	wx::create(s, sv);
	wx::create(s, sl);
	std::string s1 = "[0,1,2,3,4,5,null,7,8]";
	wx::TreeNode<long double>* root;
	wx::create(s1, root);
	return 0;
}