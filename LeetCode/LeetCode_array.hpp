#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<queue>
namespace wx {
	void array_to_c(std::string& arr) {
		for (int i = 0; i < arr.size(); ++i) {
			if (arr[i] == '[') {
				arr[i] = '{';
			}
			else if (arr[i] == ']') {
				arr[i] = '}';
			}
		}
	}
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

	std::vector<std::string> split(const std::string& s, char c) {
		int begin = 0;
		std::vector<std::string> res;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == c && i != begin) {
				res.push_back(s.substr(begin, i - begin));
				begin = i + 1;
			}
		}
		if (begin != res.size()) {
			res.push_back(s.substr(begin));
		}
		return res;
	}
	struct TreeNode_int {
		int val;
		TreeNode_int* left;
		TreeNode_int* right;
		TreeNode_int() : val(0), left(nullptr), right(nullptr) {}
		TreeNode_int(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode_int(int x, TreeNode_int* left, TreeNode_int* right) : val(x), left(left), right(right) {}
	};
	TreeNode_int* create_tree_int(const std::string& tree) {
		TreeNode_int* res = nullptr;
		//力扣的树都是层次遍历的
		std::vector<std::string> nodes = split(tree, ',');
		for (int i = 0; i < nodes.size(); ++i) {
			subreplace(nodes[i], " ", "");
			subreplace(nodes[i], "[", "");
			subreplace(nodes[i], "]", "");
		}
		std::queue<TreeNode_int**> q;
		q.push(&res);
		for (int i = 0; i < nodes.size(); ++i) {
			TreeNode_int** node = q.front();
			q.pop();
			if (nodes[i] != "null") {
				*node = new TreeNode_int(std::atoi(nodes[i].c_str()));
				q.push(&((*node)->left));
				q.push(&((*node)->right));
			}
		}
		return res;
	}
	std::vector<int> create_vector_int(const std::string& arr) {
		std::vector<std::string> values = split(arr, ',');
		for (int i = 0; i < values.size(); ++i) {
			subreplace(values[i], " ", "");
			subreplace(values[i], "[", "");
			subreplace(values[i], "]", "");
		}
		std::vector<int> res(values.size());
		for (int i = 0; i < values.size(); ++i) {
			res[i] = std::atoi(values[i].c_str());
		}
		return res;
	}

}
