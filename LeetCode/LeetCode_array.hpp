#pragma once
#include<iostream>
#include<string>
#include<vector>
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
}