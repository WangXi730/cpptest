#pragma once
#include<iostream>
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

#define leetcode using namespace std;

//LeetCodeTools_H
namespace wx {
	//在原有的字符串上进行修改，返回修改之前的字符串
	std::string subreplace(std::string& s, const std::string& src, const std::string& dest);
	//用point分割s，如果设置beg和end，则不对beg和end之间的字符进行解析
	std::vector<std::string> split(std::string& s, const std::string& point, const std::string& beg = "", const std::string& end = "");
	
	//反序列化create函数
	template<typename res_type>
	void create(const std::string& s, res_type& res);
	//序列化save
	template<typename container_t>
	void save(std::string& dest, const container_t& container);
	
	//数据结构
	template<typename _Ty>
	struct TreeNode {
		using value_type = _Ty;
		value_type val;
		TreeNode<value_type>* left;
		TreeNode<value_type>* right;
		TreeNode();
		TreeNode(value_type x);
		TreeNode(value_type x, TreeNode<value_type>* left, TreeNode<value_type>* right);
	};
	template<typename _Ty>
	struct SigleListNode {
		using value_type = _Ty;
		value_type val;
		SigleListNode<value_type>* next = nullptr;
		SigleListNode<value_type>* pre = nullptr;
		SigleListNode(value_type& x);
		SigleListNode(value_type&& x);
	};

	//实现细节
	template<typename Iterator, typename value_type>
	void create(Iterator begin, Iterator end, TreeNode<value_type>*& res);
	template<typename Iterator, typename value_type>
	void create(Iterator begin, Iterator end, SigleListNode<value_type>*& res);
	template<typename Iterator, typename container_t>
	void create(Iterator begin, Iterator end, container_t& res);
	template<typename Iterator>
	void create(Iterator begin, Iterator end, std::string& res);
	template<typename Iterator>
	void create(Iterator begin, Iterator end, bool& res);
	template<typename Iterator>
	void create(Iterator begin, Iterator end, char& res);
	template<typename Iterator>
	void create(Iterator begin, Iterator end, int& res);
	template<typename Iterator>
	void create(Iterator begin, Iterator end, long& res);
	template<typename Iterator>
	void create(Iterator begin, Iterator end, long long& res);
	template<typename Iterator>
	void create(Iterator begin, Iterator end, float& res);
	template<typename Iterator>
	void create(Iterator begin, Iterator end, double& res);
	template<typename Iterator>
	void create(Iterator begin, Iterator end, long double& res);


	template<typename value_type>
	void save(std::string& dest, const TreeNode<value_type>*& root);
	template<typename value_type>
	void save(std::string& dest, const SigleListNode<value_type>*& node_ptr);
	void save(std::string& dest, const std::string& value);
	void save(std::string& dest, const bool& value);
	void save(std::string& dest, const char& value);
	void save(std::string& dest, const int& value);
	void save(std::string& dest, const long& value);
	void save(std::string& dest, const long long& value);
	void save(std::string& dest, const float& value);
	void save(std::string& dest, const double& value);
	void save(std::string& dest, const long double& value);

}

//LeetCodeTools_CPP
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
	SigleListNode<_Ty>::SigleListNode(value_type& x) : val(x) {}
	template<typename _Ty>
	SigleListNode<_Ty>::SigleListNode(value_type&& x) : val(x) {}
	

	template<typename _Ty>
	TreeNode<_Ty>::TreeNode() : val(0), left(nullptr), right(nullptr){}
	template<typename _Ty>
	TreeNode<_Ty>::TreeNode(value_type x) : val(x), left(nullptr), right(nullptr) {}
	template<typename _Ty>
	TreeNode<_Ty>::TreeNode(value_type x, TreeNode<value_type>* left, TreeNode<value_type>* right) : val(x), left(left), right(right) {}



	template<typename Iterator, typename value_type>
	void create(Iterator begin, Iterator end, SigleListNode<value_type>*& res) {
		std::vector<value_type> res_v;
		create(begin, end, res_v);
		SigleListNode<value_type>* root = nullptr;
		SigleListNode<value_type>** node = &root;
		for (int i = 0; i < res_v.size(); ++i) {
			*node = new SigleListNode<value_type>(std::move(res_v[i]));
			node = &((*node)->next);
		}
		res = root;
	}


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




	template<typename Iterator, typename container_t>
	void create(Iterator begin, Iterator end, container_t& res) {
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
		if (begin == end) {
			return;
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
	template<typename Iterator>
	void create(Iterator begin, Iterator end, char& res) {
		while (*begin != '\'') {
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
	template<typename Iterator>
	void create(Iterator begin, Iterator end, long long& res) {
		res = std::atoll(&*begin);
	}
	template<typename Iterator>
	void create(Iterator begin, Iterator end, long& res) {
		res = std::atol(&*begin);
	}
	template<typename Iterator>
	void create(Iterator begin, Iterator end, float& res) {
		res = std::atof(&*begin);
	}
	template<typename Iterator>
	void create(Iterator begin, Iterator end, double& res) {
		res = std::atof(&*begin);
	}
	template<typename Iterator>
	void create(Iterator begin, Iterator end, long double& res) {
		res = std::strtold(&*begin, nullptr);
	}
	template<typename res_type>
	void create(const std::string& s, res_type& res) {
		create(s.begin(), s.end(), res);
	}



	//序列化save
	template<typename value_type>
	void save(std::string& dest, TreeNode<value_type>* root) {
		std::vector<std::string> sv;
		//层次遍历
		std::queue<TreeNode<value_type>*> q;
		q.push(root);
		while (!q.empty()) {
			TreeNode<value_type>* node = q.front();
			q.pop();
			if (node == nullptr) {
				sv.emplace_back("null");
				continue;
			}
			q.push(node->left);
			q.push(node->right);
			std::string tmp;
			save(tmp, node->val);
			sv.emplace_back(std::move(tmp));
		}
		int i = sv.size() - 1;
		while (i >= 0 && sv[i] == "null") --i;
		if (i < 0) {
			dest = "[]";
			return;
		}
		dest = "[";
		for (int j = 0; j <= i; ++j) {
			dest += sv[j] + ",";
		}
		*dest.rbegin() = ']';
	}
	template<typename value_type>
	void save(std::string& dest, SigleListNode<value_type>* node_ptr) {
		if (node_ptr == nullptr) {
			dest = "[]";
			return;
		}
		dest = "[";
		while (node_ptr != nullptr) {
			std::string tmp;
			save(tmp, node_ptr->val);
			dest += tmp + ",";
			node_ptr = node_ptr->next;
		}
		*dest.rbegin() = ']';
	}
	template<typename container_t>
	void save(std::string& dest, const container_t& container) {
		if (container.empty()) {
			dest = "[]";
			return;
		}
		dest = "[";
		for (auto& e : container) {
			std::string tmp;
			save(tmp, e);
			dest += tmp + ",";
		}
		*dest.rbegin() = ']';
	}

	void save(std::string& dest, const std::string& value) {
		dest = "\"";
		dest += value;
		dest += "\"";
	}
	void save(std::string& dest, const bool& value) {
		if (value) {
			dest = "true";
		}
		else {
			dest = "false";
		}
	}
	void save(std::string& dest, const char& value) {
		dest = "'";
		dest.push_back(value);
		dest.push_back('\'');
	}
	void save(std::string& dest, const int& value) {
		dest = std::to_string(value);
	}
	void save(std::string& dest, const long& value) {
		dest = std::to_string(value);
	}
	void save(std::string& dest, const long long& value) {
		dest = std::to_string(value);
	}
	void save(std::string& dest, const float& value) {
		dest = std::to_string(value);
	}
	void save(std::string& dest, const double& value) {
		dest = std::to_string(value);
	}
	void save(std::string& dest, const long double& value) {
		dest = std::to_string(value);
	}


}