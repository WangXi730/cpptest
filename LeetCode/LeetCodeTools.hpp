#pragma once
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<string>
#include<stack>

namespace wx {
	//在原有的字符串上进行修改，返回修改之前的字符串
	std::string subreplace(std::string& s, const std::string& src, const std::string& dest);
	//用point分割s，如果设置beg和end，则不对beg和end之间的字符进行解析
	std::vector<std::string> split(std::string& s, const std::string& point, const std::string& beg = "", const std::string& end = "");
	
	//leetcode系列create函数
	template<typename res_type>
	void create(const std::string& s, res_type& res);
	template<typename _Ty>
	struct TreeNode;
	template<typename Iterator, typename value_type>
	void create(Iterator begin, Iterator end, TreeNode<value_type>*& res);
	template<typename Iterator>
	void create(Iterator begin, Iterator end, char& res);
	template<typename Iterator>
	void create(Iterator begin, Iterator end, int& res);
	template<typename Iterator>
	void create(Iterator begin, Iterator end, std::string& res);
	template<typename Iterator, typename res_type>
	void create(Iterator begin, Iterator end, res_type& res);
	template<typename Iterator>
	void create(Iterator begin, Iterator end, bool& res);


}


namespace wx {


	//在原有的字符串上进行修改，返回修改之前的字符串
	std::string subreplace(std::string& s, const std::string& src, const std::string& dest) {
		if (src.size() > s.size()) {
			return s;
		}
		std::string res;
		int i = 0;
		for (i = 0; i < s.size() - src.size();) {
			if (s.substr(i, src.size()) == src) {
				res += dest;
				i += src.size();
			}
			else {
				res.push_back(s[i++]);
			}
		}
		res += s.substr(i);
		res.swap(s);
		return res;
	}

	//用point分割s，如果设置beg和end，则不对beg和end之间的字符进行解析
	std::vector<std::string> split(std::string& s, const std::string& point, const std::string& beg, const std::string& end) {
		int begin = 0;
		std::vector<std::string> res;
		for (int i = 0; i < s.size(); ++i) {
			if (beg != "" && s.substr(i, beg.size()) == beg) {
				i += beg.size();
				int st = 1;
				while (i < s.size() && st != 0) {
					if (s.substr(i, end.size()) == end) {
						--st;
						i += end.size();
					}
					else if (s.substr(i, beg.size()) == beg) {
						++st;
						i += beg.size();
					}
					else {
						++i;
					}
				}
			}
			if (s.substr(i, point.size()) == point && i != begin) {
				res.push_back(s.substr(begin, i - begin));
				begin = i + 1;
			}
		}
		res.push_back(s.substr(begin));
		return res;
	}

	template<typename _Ty>
	struct TreeNode {
		using value_type = _Ty;
		value_type val;
		TreeNode<value_type>* left;
		TreeNode<value_type>* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(value_type x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(value_type x, TreeNode<value_type>* left, TreeNode<value_type>* right) : val(x), left(left), right(right) {}

	};

	template<typename Iterator, typename value_type>
	void create(Iterator begin, Iterator end, TreeNode<value_type>*& res) {
		while (begin != end) {
			if (*begin == '[') {
				++begin;
				break;
			}
			++begin;
		}
		while (begin != end) {
			--end;
			if (*end == ']') {
				break;
			}
		}
		//层次遍历构造
		res = new TreeNode<value_type>();
		std::queue<TreeNode<value_type>**> q;
		q.push(&res);
		auto it = begin;
		while (it != end) {
			//避免分解[]内的
			if (*it == '[') {
				++it;
				int st = 1;
				while (it != end && st != 0) {
					if (*it == '[') {
						++st;
					}
					else if (*it == ']') {
						--st;
					}
					++it;
				}
			}
			if (it == end) {
				break;
			}
			else if (*it == ',') {
				//取出节点
				TreeNode<value_type>** node = q.front();
				q.pop();
				//判空
				std::string val(begin, it);
				if (val.find("null") == std::string::npos) {
					//构造
					*node = new TreeNode<value_type>();
					//赋值
					create(begin, it, (*node)->val);
					//添加子节点
					q.push(&((*node)->left));
					q.push(&((*node)->right));
				}
				//迭代
				begin = it + 1;
			}
			++it;
		}
		//取出节点
		TreeNode<value_type>** node = q.front();
		q.pop();
		//判空
		std::string val(begin, it);
		if (val.find("null") == std::string::npos) {
			//构造
			*node = new TreeNode<value_type>();
			//赋值
			create(begin, it, (*node)->val);
			//添加子节点
			q.push(&((*node)->left));
			q.push(&((*node)->right));
		}
	}

	template<typename Iterator>
	void create(Iterator begin, Iterator end, char& res) {
		while(*begin != '\''){
			++begin;
		}
		res = *begin;
	}
	template<typename Iterator>
	void create(Iterator begin, Iterator end, int& res) {
		res = std::atoi(&*begin);
	}
	template<typename Iterator>
	void create(Iterator begin, Iterator end, bool& res) {
		std::string s(begin, end);
		if (s.find("true") != std::string::npos) {
			res = true;
		}
		else {
			res = false;
		}
	}
	template<typename Iterator>
	void create(Iterator begin, Iterator end, std::string& res) {
		while (*begin != '"')++begin;
		--end;
		while (*end != '"')--end;
		++begin;
		res = std::string(begin, end);
	}


	template<typename Iterator, typename res_type>
	void create(Iterator begin, Iterator end, res_type& res) {
		while (begin != end) {
			if (*begin == '[') {
				++begin;
				break;
			}
			++begin;
		}
		while (begin != end) {
			--end;
			if (*end == ']') {
				break;
			}
		}
		auto it = begin;
		while (it != end) {
			//避免分解[]内的
			if (*it == '[') {
				++it;
				int st = 1;
				while (it != end && st != 0) {
					if (*it == '[') {
						++st;
					}
					else if (*it == ']') {
						--st;
					}
					++it;
				}
			}
			if (it == end) {
				break;
			}
			else if (*it == ',') {
				res.resize(res.size() + 1);
				create(begin, it, *res.rbegin());
				begin = it + 1;
			}
			++it;
		}
		res.resize(res.size() + 1);
		create(begin, it, *res.rbegin());
	}


	template<typename res_type>
	void create(const std::string& s, res_type& res) {
		create(s.begin(), s.end(), res);
	}


}